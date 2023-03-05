rule TutorialTerrainGoat
highFrequency
inactive
{
	if (trTime() > cActivationTime + 1) {
		trCameraCut(vector(-65.460060,123.743729,-65.460060), vector(0.500000,-0.707107,0.500000), vector(0.500000,0.707107,0.500000), vector(0.707107,0.000000,-0.707107));
		xsDisableRule("DeerTutorialDone");
		xsDisableRule("RhinoTutorialDone");
		xsDisableRule("Jump");
		xsDisableRule("JumpEnd");
		NewDestroyNumber = trGetNextUnitScenarioNameNumber()-1;
		TutorialMode = true;
		Stage = 3;
		CliffType = 2;
		CliffSubType = 3;
		//trLetterBox(false);
		clearMap("black", 5.0);
		trPaintTerrain(0,0,45,cNumberNonGaiaPlayers*8,CliffType,CliffSubType);
		xResetDatabase(dChests);
		int temp = 0;
		//trees
		for(t=0 ; < cNumberNonGaiaPlayers){
			for(x=0 ; < 46){
				if(iModulo(7,x) == 0){
					temp = trGetNextUnitScenarioNameNumber();
					UnitCreate(0, "Cinematic Block", x*2, t*16+8, 90);
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitChangeProtoUnit("Rock River Icy");
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trSetScale(1.65);
				}
				else{
					temp = trGetNextUnitScenarioNameNumber();
					UnitCreate(0, "Cinematic Block", x*2, t*16+8, 90);
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitChangeProtoUnit("Pine Snow");
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trSetScale(0.75);
				}
			}
		}
		trQuestVarSet("PlayersDoneTutorial", 0);
		for(p=1 ; < cNumberNonGaiaPlayers){
			trQuestVarSet("P"+p+"DoneTutorial", 0);
			trQuestVarSet("P"+p+"FountainMsg", 0);
			trPaintTerrain(5,((p*8)-2),40,((p*8+4)-2),0,50);
			//trPaintTerrain(7,p*8,7,p*8,0,73); //start sq
			PaintAtlantisArea(6,p*8-1,8,p*8+1,0,53);  //start sq
			trPaintTerrain(28,p*8+2,28,p*8-2,0,74); //end line
			// cliff
			trChangeTerrainHeight(12,p*8+2,16,p*8-2,10,false);
			trPaintTerrain(11,p*8+2,16,p*8-2,CliffType,CliffSubType);
			trPaintTerrain(12,p*8+1,15,p*8-2,0,50);
			
			trChangeTerrainHeight(20,p*8+2,24,p*8-2,10,false);
			trPaintTerrain(19,p*8+2,24,p*8-2,CliffType,CliffSubType);
			trPaintTerrain(20,p*8+1,23,p*8-2,0,50);
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(cNumberNonGaiaPlayers, "Cinematic Block", 28*2, p*16-4, 0);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Fence Stone");
			xAddDatabaseBlock(dTemp, true);
			xSetInt(dTemp, xUnitID, temp);
			xSetInt(dTemp, xExtra, p);
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(cNumberNonGaiaPlayers, "Cinematic Block", 28*2, p*16, 0);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Fence Stone");
			xAddDatabaseBlock(dTemp, true);
			xSetInt(dTemp, xUnitID, temp);
			xSetInt(dTemp, xExtra, p);
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(cNumberNonGaiaPlayers, "Cinematic Block", 28*2, p*16+4, 180);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Fence Stone");
			xAddDatabaseBlock(dTemp, true);
			xSetInt(dTemp, xUnitID, temp);
			xSetInt(dTemp, xExtra, p);
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(0, "Cinematic Block", 34*2, p*16, 270);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Shrine");
			//trUnitSelectClear();
			//trUnitSelect(""+temp);
			//trMutateSelected(kbGetProtoUnitID("Shrine"));
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitSetAnimationPath("2,0,0,0,0");
			xAddDatabaseBlock(dTemp, true);
			xSetInt(dTemp, xUnitID, temp);
			xSetInt(dTemp, xExtra, p);
			CreateGoat(p,14,16*p,90);
			xSetPointer(dPlayerData, xPlayerUnitID);
			xSetInt(dPlayerData, xPlayerUnitID, 1*trQuestVarGet("P"+p+"Unit"));
			xSetInt(dPlayerData, xTarget, 0);
			xSetInt(dPlayerData, xTimeout, trTimeMS()*2);
			if(trCurrentPlayer() == p){
				trCounterAddTime("cdtutorial", -100, -200, "<color={PlayerColor("+p+")}>Press 'Q' to jump to the cursor.", -1);
			}
		}
		
		refreshPassability();
		xsEnableRule("Animations");
		xsEnableRule("GoatJump");
		xsEnableRule("GoatJumpEnd");
		xsEnableRule("ExtraJumpTech");
		//	xsEnableRule("Charge");
		//	xsDisableRule("VectorFirst");
		//	xsDisableRule("VectorSecond");
		xsEnableRule("GoatTutorialDone");
		trDelayedRuleActivation("GoatTutorialLoops");
		if(QuickStart == 0){
			startNPCDialog(8);
		}
		refreshPassability();
		uiZoomToProto(""+GoatProto);
		uiLookAtProto(""+GoatProto);
		playSound("\xpack\xcinematics\2_in\music.mp3");
		xsDisableSelf();
	}
}

rule ExtraJumpTech
highFrequency
inactive
{
	//+6 jump range
	int jumps = 0;
	while(jumps < 21){
		for(p=1; < cNumberNonGaiaPlayers){
			trTechSetStatus(p, 115, 4);
			jumps = jumps +1;
		}
	}
	xsDisableSelf();
}

void SquareHeight(int sq = 0){
	int StartX = xsVectorGetX(StageVector);
	int StartZ = xsVectorGetZ(StageVector);
	int x = 0;
	int z = 0;
	vector dir = vector(0,0,0);
	if((sq > 0) && (sq < 10)){
		if((sq >= 1) && (sq <= 3)){
			z = StartZ+5;
		}
		if((sq >= 4) && (sq <= 6)){
			z = StartZ-2;
		}
		if((sq >= 7) && (sq <= 9)){
			z = StartZ-9;
		}
		int d = iModulo(3, sq)+1;
		x = StartX+(d*7-16);
		float height = trGetTerrainHeight(x+2,z+2);
		if(height > 0){
			trChangeTerrainHeight(x,z,x+5,z+5,height-1,false);
		}
		if(height == 2){
			trPaintTerrain(x,z,x+4,z+4,0,6,false);
		}
		if(height == 1){
			trPaintTerrain(x,z,x+5,z+5,5,7,false);
			SquaresDown = SquaresDown+1;
			playSound("fireball fall 2.wav");
		}
	}
}

rule GoatJump
highFrequency
inactive
{
	int anim = 0;
	for(p=1 ; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		if(trPlayerResourceCount(p, "Gold") > 0){
			trPlayerGrantResources(p, "Gold", -100000);
			if(xGetBool(dPlayerData, xReadyToLeave) == false){
				if(xGetFloat(dPlayerData, xGoatJumpDist) < 225){
					trUnitSelectClear();
					trUnitSelectByQV("P"+p+"Unit");
					trMutateSelected(kbGetProtoUnitID("Anubite"));
					//trUnitChangeProtoUnit("Hero Greek Bellerophon");
					//LOS MAINTAINED
					trSetSelectedScale(0,1,0);
					xSetInt(dPlayerData, xOldAnim, -10);
					trUnitSelectClear();
					trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
					trUnitOverrideAnimation(24, 0, true, false, -1, 0);
					xSetInt(dPlayerData, xTarget, trGetNextUnitScenarioNameNumber());
					//Greta heading 0 to player heading
					UnitCreate(cNumberNonGaiaPlayers, "Female", xsVectorGetX(xGetVector(dPlayerData,xGoatTarget)), xsVectorGetZ(xGetVector(dPlayerData,xGoatTarget)), 0);
					xUnitSelect(dPlayerData, xTarget);
					trSetSelectedScale(0.1,0.1,0.1);
					trSetUnitOrientation(trVectorQuestVarGet("V"+p+"dir"), vector(0,1,0), true);
					trUnitSelectClear();
					trUnitSelectByQV("P"+p+"Unit");
					trUnitDoWorkOnUnit(""+xGetInt(dPlayerData, xTarget),-1);
					xAddDatabaseBlock(dDestroyMe, true);
					xSetInt(dDestroyMe, xDestroyName, xGetInt(dPlayerData, xTarget));
					xSetInt(dDestroyMe, xDestroyTime, trTimeMS()+4000);
					xSetInt(dPlayerData, xTimeout, trTimeMS()+900);
					//32 is anim
				}
				else{
					//jump too far
					ColouredChatToPlayer(p, "1,0,0", "Jump distance too far!");
					if(trCurrentPlayer() == p){
						playSound("cantdothat.wav");
					}
				}
			}
		}
		if(trPlayerResourceCount(p, "Wood") > 0){
			trPlayerGrantResources(p, "Wood", -100000);
			int temp = trGetNextUnitScenarioNameNumber();
			tempV = kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit"));
			UnitCreate(0, "Dwarf", xsVectorGetX(tempV), xsVectorGetZ(tempV), 0);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Deconstruct Unit");
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitOverrideAnimation(18, 0, true, false, -1, 0);
			//Interract
			if(TutorialMode == true){
				if(trCountUnitsInArea(""+1*trQuestVarGet("P"+p+"Unit"),0,"Shrine", 6) > 0){
					trQuestVarSet("P"+p+"FountainMsg", 2);
				}
				if(QuickStart != 0){
					trQuestVarSet("P"+p+"FountainMsg", 2);
				}
			}
			else{
				for(n = xGetDatabaseCount(dInterractables) ; > 0){
					xDatabaseNext(dInterractables);
					if(trCountUnitsInArea(""+xGetInt(dInterractables, xUnitID),p,""+GoatProto, 5) > 0){
						xUnitSelect(dInterractables, xUnitID);
						trUnitHighlight(1, true);
						if(xGetInt(dInterractables, xType) == 1){
							//Interracting with minigame statue
							//int statue = xGetInt(dInterractables, xSubtype);
							SquareHeight(xGetInt(dInterractables, xSquare1));
							SquareHeight(xGetInt(dInterractables, xSquare2));
						}
						if(xGetInt(dInterractables, xType) == 2){
							//Interracting with shrine
							if(xGetInt(dInterractables, xSubtype) == 0){
								xSetInt(dInterractables, xSubtype, 1);
								xUnitSelect(dInterractables, xUnitID);
								trQuestVarSetFromRand("temp", ShrineTimeMin, ShrineTimeMax);
								xSetInt(dInterractables, xSquare1, trTime()+1*trQuestVarGet("temp"));
								trUnitHighlight(1*trQuestVarGet("temp"), false);
								tempV = kbGetBlockPosition(""+1*xGetInt(dInterractables, xUnitID));
								temp = trGetNextUnitScenarioNameNumber();
								UnitCreate(0, "Dwarf", xsVectorGetX(tempV), xsVectorGetZ(tempV), 0);
								trUnitSelectClear();
								trUnitSelect(""+temp);
								trUnitChangeProtoUnit("Timeshift Out");
								xSetInt(dInterractables, xSquare2, temp);
								trUnitSelectClear();
								trUnitSelect(""+temp);
								trUnitSetAnimationPath("0,1,0,0,0");
								if(trCurrentPlayer() == p){
									playSound("shrine.wav");
								}
								ShrinesGot = ShrinesGot+1;
							}
						}
						if(xGetInt(dInterractables, xType) == 3){
							//Interracting with rune
							if(xGetInt(dInterractables, xSubtype) == 0){
								xSetInt(dInterractables, xSubtype, 1);
								xUnitSelect(dInterractables, xUnitID);
								trQuestVarSetFromRand("temp", ShrineTimeMin/2, ShrineTimeMax/2);
								xSetInt(dInterractables, xSquare1, trTime()+1*trQuestVarGet("temp"));
								trUnitHighlight(1*trQuestVarGet("temp"), false);
								tempV = kbGetBlockPosition(""+1*xGetInt(dInterractables, xUnitID));
								temp = trGetNextUnitScenarioNameNumber();
								UnitCreate(0, "Dwarf", xsVectorGetX(tempV), xsVectorGetZ(tempV), 0);
								trUnitSelectClear();
								trUnitSelect(""+temp);
								trUnitChangeProtoUnit("Spy Eye");
								trUnitSelectClear();
								trUnitSelect(""+temp);
								trMutateSelected(kbGetProtoUnitID("Monument"));
								xSetInt(dInterractables, xSquare2, temp);
								trUnitSelectClear();
								trUnitSelect(""+temp);
								trUnitSetAnimationPath("0,0,0,1,0");
								trUnitSelectClear();
								trUnitSelect(""+temp);
								trSetScale(0);
								trQuestVarModify("P"+p+"Runes", "+", 1);
								trQuestVarSetFromRand("temp",0,30);
								for(a = 1*trQuestVarGet("temp"); > 0){
									xDatabaseNext(dInterractables);
								}
								for(a = xGetDatabaseCount(dInterractables); > 0){
									//[THIS WILL ONLY GO TO FIRST UNIT]
									xDatabaseNext(dInterractables);
									if(xGetInt(dInterractables, xType) == 2){
										if(xGetInt(dInterractables, xSubtype) == 0){
											tempV = kbGetBlockPosition(""+xGetInt(dInterractables, xUnitID));
											break;
										}
									}
								}
								if(trCurrentPlayer() == p){
									trMinimapFlare(p, 10, tempV, true);
								}
								if(1*trQuestVarGet("P"+p+"Runes") == 1){
									ColouredIconChatToPlayer(p, "1,0,1", "icons\improvement thurisaz rune icon 64", "Runestones will flare an inactive shrine");
								}
							}
						}
						if(xGetInt(dInterractables, xType) == 4){
							xUnitSelect(dInterractables, xUnitID);
							trUnitChangeProtoUnit("Arkantos God Out");
							xFreeDatabaseBlock(dInterractables);
							PlayerChoice(p, "Choose your reward:", "Discover shrine activation requirement", 33, "Discover total number of shrines", 34, 10000);
						}
						if(xGetInt(dInterractables, xType) == 5){
							if(xGetInt(dInterractables, xSubtype) == 0){
								//camera
								tempV = kbGetBlockPosition(""+xGetInt(dInterractables, xUnitID));
								for(a = xGetDatabaseCount(dPoachers); > 0){
									xDatabaseNext(dPoachers);
									xUnitSelect(dPoachers, xUnitID);
									trUnitMoveToPoint(xsVectorGetX(tempV),0,xsVectorGetZ(tempV),-1,true);
								}
								xSetInt(dInterractables, xSubtype, 1);
								xSetInt(dInterractables, xSquare1, trTime()+150);
								xUnitSelect(dInterractables, xUnitID);
								trUnitSetAnimationPath("0,0,0,0,0");
								if(trCurrentPlayer() == p){
									playSound("attackwarning.wav");
									trMessageSetText("Poachers are converging on your position!", 6000);
								}
							}
						}
					}
				}
				if(xGetDatabaseCount(dRelics) > 0){
					for(n = xGetDatabaseCount(dRelics); > 0){
						xDatabaseNext(dRelics);
						if(trCountUnitsInArea(""+xGetInt(dRelics, xUnitID),p,""+GoatProto, 5) > 0){
							//Interracting with relic
							xUnitSelect(dRelics, xUnitID);
							trUnitChangeProtoUnit("Arkantos God Out");
							xUnitSelect(dRelics, xUnitID);
							trUnitSetAnimationPath("0,1,1,1,0,0,0");
							xUnitSelect(dRelics, xSubID);
							trUnitDestroy();
							xFreeDatabaseBlock(dRelics);
							SpawnRelic(1);
							xSetInt(dPlayerData, xRelics, xGetInt(dPlayerData, xRelics)+1);
							if(trCurrentPlayer() == p){
								playSound("relicselect.wav");
							}
						}
					}
				}
				if(xGetDatabaseCount(dShop) > 0){
					for(n = xGetDatabaseCount(dShop); > 0){
						xDatabaseNext(dShop);
						if(trCountUnitsInArea(""+xGetInt(dShop, xUnitID),p,""+GoatProto, 5) > 0){
							//Interracting with shop
							if(xGetInt(dPlayerData, xRelics) >= xGetInt(dShop, xCost)){
								xSetInt(dPlayerData, xRelics, xGetInt(dPlayerData, xRelics)-xGetInt(dShop, xCost));
								trTechGodPower(p, xGetString(dShop, xPowerName), 1);
								if(trCurrentPlayer() == p){
									playSound("tributereceived.wav");
									playSound("\cinematics\24_in\magic.mp3");
								}
							}
							else{
								if(trCurrentPlayer() == p){
									trMessageSetText("To purchase " + xGetString(dShop, xPower) + " - you need " + xGetInt(dShop, xCost) + " relics.", 6000);
									playSound("cantdothat.wav");
								}
							}
						}
					}
				}
			}
		}
		if(trPlayerResourceCount(p, "Food") > 0){
			trPlayerGrantResources(p, "Food", -100000);
		}
		//jump set anim to 13
	}
}

rule GoatJumpEnd
highFrequency
inactive
{
	if(Stage == 3){
		for(p=1 ; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			int anim = kbUnitGetAnimationActionType(kbGetBlockID(""+1*trQuestVarGet("P"+p+"Unit")+""));
			if(xGetInt(dPlayerData, xTarget) > 0){
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xTarget));
				if((trUnitPercentDamaged() > 0) || (trUnitDead())){
					xUnitSelect(dPlayerData, xTarget);
					trUnitConvert(p);
					trMutateSelected(kbGetProtoUnitID("Transport Ship Greek"));
					trSetSelectedScale(0,1,0);
					
					trUnitSelectByQV("P"+p+"Unit");
					trImmediateUnitGarrison(""+xGetInt(dPlayerData, xTarget));
					xUnitSelect(dPlayerData, xTarget);
					trUnitEjectContained();
					//trUnitChangeProtoUnit("Dwarf");
					
					xUnitSelect(dPlayerData, xTarget);
					trUnitDestroy();
					
					xSetInt(dPlayerData, xTarget, 0);
					
					trUnitSelectByQV("P"+p+"Unit");
					if(xGetBool(dPlayerData, xReadyToLeave) == false){
						trMutateSelected(kbGetProtoUnitID(""+GoatProto));
					}
					if(xGetBool(dPlayerData, xReadyToLeave) == true){
						trMutateSelected(kbGetProtoUnitID("Prisoner"));
					}
					trSetSelectedScale(0,1,0);
					
					//trUnitSelectByQV("P"+p+"Unit");
					//trSetUnitOrientation(trVectorQuestVarGet("V"+p+"dir"), vector(0,1,0), true);
					
					xSetInt(dPlayerData, xOldAnim, 2);
					
					xUnitSelect(dPlayerData, xSpyID);
					//trUnitOverrideAnimation(13, 0, false, false, -1, 0);
					trUnitOverrideAnimation(2, 0, true, true, -1, 0);
					
					trVectorQuestVarSet("P"+p+"Pos", kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
				}
				trUnitSelectClear();
				if(trTimeMS() > xGetInt(dPlayerData, xTimeout)){
					if(anim != 32){
						//end timeout jump
						xUnitSelect(dPlayerData, xTarget);
						trUnitConvert(p);
						trMutateSelected(kbGetProtoUnitID("Transport Ship Greek"));
						trSetSelectedScale(0,1,0);
						
						trUnitSelectByQV("P"+p+"Unit");
						trImmediateUnitGarrison(""+xGetInt(dPlayerData, xTarget));
						xUnitSelect(dPlayerData, xTarget);
						trUnitEjectContained();
						//trUnitChangeProtoUnit("Dwarf");
						
						xUnitSelect(dPlayerData, xTarget);
						trUnitDestroy();
						
						xSetInt(dPlayerData, xTarget, 0);
						
						trUnitSelectByQV("P"+p+"Unit");
						if(xGetBool(dPlayerData, xReadyToLeave) == false){
							trMutateSelected(kbGetProtoUnitID(""+GoatProto));
						}
						if(xGetBool(dPlayerData, xReadyToLeave) == true){
							trMutateSelected(kbGetProtoUnitID("Prisoner"));
						}
						trSetSelectedScale(0,1,0);
						
						//trUnitSelectByQV("P"+p+"Unit");
						//trSetUnitOrientation(trVectorQuestVarGet("V"+p+"dir"), vector(0,1,0), true);
						
						xSetInt(dPlayerData, xOldAnim, 2);
						
						xUnitSelect(dPlayerData, xSpyID);
						//trUnitOverrideAnimation(13, 0, false, false, -1, 0);
						trUnitOverrideAnimation(2, 0, true, true, -1, 0);
						
						trVectorQuestVarSet("P"+p+"Pos", kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
						if(distanceBetweenVectors(xGetVector(dPlayerData, xGoatTarget),kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit"))) > 225){
							debugLog("Vector differential bug, fixed");
							trUnitSelectByQV("P"+p+"Unit");
							trUnitChangeProtoUnit("Ragnorok SFX");
							trUnitSelectByQV("P"+p+"Unit");
							trUnitDestroy();
							trUnitSelectClear();
							trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
							trUnitChangeProtoUnit("Hero Death");
							CreateGoat(p, xsVectorGetX(xGetVector(dPlayerData, xGoatTarget)), xsVectorGetZ(xGetVector(dPlayerData, xGoatTarget)), 0);
						}
					}
				}
			}
			trUnitSelectClear();
		}
	}
}

rule GoatTutorialLoops
highFrequency
inactive
{
	if(TutorialMode){
		int temp = 0;
		for(p=1 ; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			trVectorQuestVarSet("P"+p+"Pos", kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
			if((playerIsPlaying(p) == false) && (xGetBool(dPlayerData, xPlayerActive) == true)){
				trUnitSelectByQV("P"+p+"Unit");
				trUnitChangeProtoUnit("Ragnorok SFX");
				trUnitSelectByQV("P"+p+"Unit");
				trUnitDestroy();
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
				trUnitChangeProtoUnit("Hero Death");
				xSetBool(dPlayerData, xPlayerActive, false);
				PlayersActive = PlayersActive-1;
				trPaintTerrain(5,((p*8)-2),40,((p*8+4)-2),CliffType,CliffSubType);
				trUnitSelectClear();
				for(a = xGetDatabaseCount(dTemp) ; > 0){
					xDatabaseNext(dTemp);
					if(xGetInt(dTemp, xExtra) == p){
						xUnitSelect(dTemp, xUnitID);
						trUnitDestroy();
						xFreeDatabaseBlock(dTemp);
					}
				}
			}
			//through wall
			if((trVectorQuestVarGetX("P"+p+"Pos") > 58) && (1*trQuestVarGet("P"+p+"DoneTutorial") == 0) && (1*trQuestVarGet("P"+p+"FountainMsg") == 0)){
				if(trCurrentPlayer() == p){
					startNPCDialog(9);
					trQuestVarSet("P"+p+"FountainMsg", 1);
					trCounterAddTime("cdtutoriala", -100, -200, "<color={PlayerColor("+p+")}>Press 'W' to interract.", -1);
				}
			}
			if((1*trQuestVarGet("P"+p+"FountainMsg") == 2) && (1*trQuestVarGet("P"+p+"DoneTutorial") == 0)){
				trUnitSelectByQV("P"+p+"Unit");
				trUnitChangeProtoUnit("Ragnorok SFX");
				trUnitSelectByQV("P"+p+"Unit");
				trUnitDestroy();
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
				trUnitChangeProtoUnit("Hero Death");
				trQuestVarSet("P"+p+"DoneTutorial", 1);
				trQuestVarModify("PlayersDoneTutorial", "+", 1);
				temp = 1*trQuestVarGet("PlayersDoneTutorial");
				trPaintTerrain(5,((p*8)-2),40,((p*8+4)-2),CliffType,CliffSubType);
				trUnitSelectClear();
				for(a = xGetDatabaseCount(dTemp) ; > 0){
					xDatabaseNext(dTemp);
					if(xGetInt(dTemp, xExtra) == p){
						xUnitSelect(dTemp, xUnitID);
						trUnitDestroy();
						xFreeDatabaseBlock(dTemp);
					}
				}
				trUnitSelectClear();
				trClearCounterDisplay();
				trSetCounterDisplay("<color={PlayerColor(" + GreenText() + ")}>Tutorial complete: " + temp + " / " + PlayersActive);
				if((temp == 1) && (PlayersActive > 1)){
					xsEnableRule("TutorialTimeout");
				}
				if(trCurrentPlayer() == p){
					playSound("ageadvance.wav");
					trCounterAbort("cdtutorial");
					trCounterAbort("cdtutoriala");
				}
			}
			trUnitSelectByQV("P"+p+"Unit");
			if((trUnitDead() == true) && (xGetBool(dPlayerData, xPlayerActive) == true) && (1*trQuestVarGet("P"+p+"DoneTutorial") == 0)){
				trUnitSelectByQV("P"+p+"Unit");
				trUnitChangeProtoUnit("Ragnorok SFX");
				trUnitSelectByQV("P"+p+"Unit");
				trUnitDestroy();
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
				trUnitChangeProtoUnit("Hero Death");
				CreateGoat(p, 14, p*16, 90);
			}
			if((trVectorQuestVarGetZ("P"+p+"Pos") > (p*16+8)) && (1*trQuestVarGet("P"+p+"DoneTutorial") == 0)){
				trUnitSelectByQV("P"+p+"Unit");
				trUnitTeleport(trVectorQuestVarGetX("P"+p+"Pos"),3,p*16);
			}
		}
	}
}

rule GoatTutorialDone
highFrequency
inactive
{
	if(PlayersActive == 1*trQuestVarGet("PlayersDoneTutorial")){
		xsDisableSelf();
		xsDisableRule("GoatTutorialLoops");
		xsEnableRule("BuildGoatArea");
		trClearCounterDisplay();
		trCounterAbort("cdtutorial");
		trCounterAbort("cdtutoriala");
		trCounterAbort("cdtutorialtimeout");
		trQuestVarSet("PlayersDoneTutorial", 0);
		trLetterBox(true);
		trUIFadeToColor(0,0,0,1,1,true);
		Stage = 3;
		characterDialog(ActName(Stage), " ", ActIcon(Stage));
		trSetFogAndBlackmap(true,true);
		trDelayedRuleActivation("ResetBlackmap");
		trFadeOutAllSounds(3);
		trFadeOutMusic(3);
		xResetDatabase(dTemp);
		TutorialMode = false;
	}
}
