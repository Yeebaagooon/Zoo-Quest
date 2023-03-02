rule TutorialTerrainCrocodile
highFrequency
inactive
{
	if (trTime() > cActivationTime + 1) {
		trCameraCut(vector(-65.460060,123.743729,-65.460060), vector(0.500000,-0.707107,0.500000), vector(0.500000,0.707107,0.500000), vector(0.707107,0.000000,-0.707107));
		xsDisableRule("DeerTutorialDone");
		xsDisableRule("RhinoTutorialDone");
		xsDisableRule("GoatTutorialDone");
		xsDisableRule("Jump");
		xsDisableRule("JumpEnd");
		NewDestroyNumber = trGetNextUnitScenarioNameNumber()-1;
		TutorialMode = true;
		Stage = 4;
		CliffType = 0;
		CliffSubType = 36;
		//trLetterBox(false);
		clearMap("black", -5.0);
		paintWaterKeepingMapPassable(1,3,vector(0.4588,0.6588,0.5098));
		trPaintTerrain(0,0,45,cNumberNonGaiaPlayers*8,CliffType,CliffSubType);
		xResetDatabase(dChests);
		int temp = 0;
		//trees
		for(t=0 ; < cNumberNonGaiaPlayers){
			for(x=0 ; < 46){
				if(iModulo(4,x) == 0){
					temp = trGetNextUnitScenarioNameNumber();
					UnitCreate(0, "Cinematic Block", x*2, t*16+8, 90);
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitChangeProtoUnit("Savannah Tree");
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trSetSelectedScale(1,0.9,1);
				}
				else{
					temp = trGetNextUnitScenarioNameNumber();
					trQuestVarSetFromRand("temph",0,360,true);
					UnitCreate(0, "Cinematic Block", x*2, t*16+8, 1*trQuestVarGet("temph"));
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitChangeProtoUnit("Spy Eye");
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trMutateSelected(kbGetProtoUnitID("Seaweed"));
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trSetScale(2.5);
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitOverrideAnimation(2, 0, true, true, -1, 0);
				}
			}
		}
		trQuestVarSet("PlayersDoneTutorial", 0);
		for(p=1 ; < cNumberNonGaiaPlayers){
			trForbidProtounit(p, "Farm");
			trForbidProtounit(p, "Ulsfark");
			trQuestVarSet("P"+p+"DoneTutorial", 0);
			trQuestVarSet("P"+p+"FountainMsg", 0);
			trPaintTerrain(5,((p*8)-2),40,((p*8+4)-2),4,29);
			//trPaintTerrain(7,p*8,7,p*8,0,73); //start sq
			PaintAtlantisArea(6,p*8-1,8,p*8+1,0,39);  //start sq
			// cliff
			//main body
			trChangeTerrainHeight(4,p*8+3,11,p*8-2,2,false);
			//trChangeTerrainHeight(12,p*8+3,17,p*8-2,-1,false);
			//first island
			trChangeTerrainHeight(18,p*8+3,27,p*8-2,2,false);
			
			PaintAtlantisArea(34-1, p*8-1, 34+1, p*8+1,0,39);
			trChangeTerrainHeight(34-1, p*8-1, 34+2, p*8+2,2,false);
			/*
			trChangeTerrainHeight(12,p*8+2,16,p*8-2,10,false);
			trPaintTerrain(11,p*8+2,16,p*8-2,CliffType,CliffSubType);
			trPaintTerrain(12,p*8+1,15,p*8-2,0,50);
			
			trChangeTerrainHeight(20,p*8+2,24,p*8-2,10,false);
			trPaintTerrain(19,p*8+2,24,p*8-2,CliffType,CliffSubType);
			trPaintTerrain(20,p*8+1,23,p*8-2,0,50);*/
			/*temp = trGetNextUnitScenarioNameNumber();
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
			xSetInt(dTemp, xExtra, p);*/
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(0, "Cinematic Block", 34*2, p*16, 270);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Zebra");
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitHighlight(100, true);
			/*trUnitSelectClear();
			trUnitSelect(""+temp);
			trMutateSelected(kbGetProtoUnitID("Summoning Tree"));
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trSetScale(0.5);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitSetAnimationPath("0,1,0,0,0");*/
			xAddDatabaseBlock(dTemp, true);
			xSetInt(dTemp, xUnitID, temp);
			xSetInt(dTemp, xExtra, p);
			CreateCroc(p,14,16*p,90);
			xSetPointer(dPlayerData, p);
			xSetInt(dPlayerData, xPlayerUnitID, 1*trQuestVarGet("P"+p+"Unit"));
			xSetInt(dPlayerData, xCrocSprintRechargeTimer, trTime());
			xSetInt(dPlayerData, xCrocSprintRechargeTime, xGetInt(dPlayerData, xCrocSprintRechargeTime)/4);
			if(trCurrentPlayer() == p){
				trCounterAddTime("cdtutorial", -100, -200, "<color={PlayerColor("+p+")}>Swim to the first island.", -1);
			}
		}
		
		refreshPassability();
		xsEnableRule("Animations");
		//bored anim when swimming and maybe pivot height scale to 2
		//xsEnableRule("GoatJump");
		//xsEnableRule("GoatJumpEnd");
		//xsEnableRule("ExtraJumpTech");
		//	xsEnableRule("Charge");
		//	xsDisableRule("VectorFirst");
		//	xsDisableRule("VectorSecond");
		xsEnableRule("CrocTutorialDone");
		trDelayedRuleActivation("CrocMechanicLoops");
		trDelayedRuleActivation("CrocTutorialLoops");
		if(QuickStart == 0){
			startNPCDialog(10);
		}
		refreshPassability();
		uiZoomToProto(""+CrocProto);
		uiLookAtProto(""+CrocProto);
		xsDisableSelf();
		xsEnableRule("Swimming");
	}
}

rule Swimming
inactive
highFrequency
{
	vector temppos = vector(0,0,0);
	for(p=1 ; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		temppos = kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit"));
		float tempheight = (trGetWaterHeight(xsVectorGetX(temppos)/2, xsVectorGetZ(temppos)/2)-trGetTerrainHeight(xsVectorGetX(temppos)/2, xsVectorGetZ(temppos)/2));
		if(xGetBool(dPlayerData, xSwimming) == false){
			if(tempheight >= 1.25){
				xSetBool(dPlayerData, xSwimming, true);
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
				trUnitOverrideAnimation(3, 0, true, true, -1, 0);
				trUnitSelectByQV("P"+p+"Unit");
				trSetSelectedScale(0,2,0);
				modifyProtounitAbsolute(""+CrocProto, p, 1, xGetFloat(dPlayerData, xCrocWaterSpeed));
			}
		}
		else{
			if(tempheight < 1.25){
				xSetBool(dPlayerData, xSwimming, false);
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
				trUnitOverrideAnimation(15, 0, true, true, -1, 0);
				trUnitSelectByQV("P"+p+"Unit");
				trSetSelectedScale(0,1,0);
				modifyProtounitAbsolute(""+CrocProto, p, 1, xGetFloat(dPlayerData, xCrocLandSpeed));
				xSetInt(dPlayerData, xCrocBonusTimer, trTime()+xGetInt(dPlayerData, xCrocBonusTime));
			}
		}
		/*if(xGetBool(dPlayerData, xSwimming) == true){
			trUnitSelectByQV("P"+p+"Unit");
			trSetSelectedScale(0,1+tempheight/2,0);
		}*/
	}
}

rule CrocTutorialLoops
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
				//trPaintTerrain(5,((p*8)-2),40,((p*8+4)-2),getTerrainType("black"), getTerrainSubType("black"));
				trPaintWaterColor(vector(1,0,0), 0,((p*8)-2),40,((p*8+4)-2));
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
			if((trVectorQuestVarGetX("P"+p+"Pos") > 38) && (1*trQuestVarGet("P"+p+"DoneTutorial") == 0) && (1*trQuestVarGet("P"+p+"FountainMsg") == 0)){
				if(trCurrentPlayer() == p){
					startNPCDialog(11);
					trQuestVarSet("P"+p+"FountainMsg", 1);
					trCounterAbort("cdtutorial");
					trCounterAddTime("cdtutoriala", -100, -200, "<color={PlayerColor("+p+")}>Press 'Q' to sprint.", -1);
				}
			}
			if((trVectorQuestVarGetX("P"+p+"Pos") > 56) && (1*trQuestVarGet("P"+p+"DoneTutorial") == 0) && (1*trQuestVarGet("P"+p+"FountainMsg") == 1)){
				if(trCurrentPlayer() == p){
					startNPCDialog(12);
					trQuestVarSet("P"+p+"FountainMsg", 2);
					trCounterAbort("cdtutoriala");
					trCounterAddTime("cdtutoriala", -100, -200, "<color={PlayerColor("+p+")}>Press 'W' to eat", -1);
				}
			}
			if((1*trQuestVarGet("P"+p+"FountainMsg") == 3) && (1*trQuestVarGet("P"+p+"DoneTutorial") == 0)){
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
				trPaintWaterColor(vector(0,1,0), 0,((p*8)-2),40,((p*8+4)-2));
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
				CreateCroc(p, 14, p*16, 90);
			}
			if((trVectorQuestVarGetZ("P"+p+"Pos") > (p*16+8)) && (1*trQuestVarGet("P"+p+"DoneTutorial") == 0)){
				trUnitSelectByQV("P"+p+"Unit");
				trUnitTeleport(trVectorQuestVarGetX("P"+p+"Pos"),3,p*16);
			}
		}
	}
}

rule CrocTutorialDone
highFrequency
inactive
{
	if(PlayersActive == 1*trQuestVarGet("PlayersDoneTutorial")){
		xsDisableSelf();
		xsDisableRule("CrocTutorialLoops");
		xsEnableRule("BuildCrocArea");
		trClearCounterDisplay();
		trCounterAbort("cdtutorial");
		trCounterAbort("cdtutoriala");
		trCounterAbort("cdtutorialtimeout");
		trQuestVarSet("PlayersDoneTutorial", 0);
		trLetterBox(true);
		trUIFadeToColor(0,0,0,1,1,true);
		Stage = 4;
		characterDialog(ActName(Stage), " ", ActIcon(Stage));
		trSetFogAndBlackmap(true,true);
		trDelayedRuleActivation("ResetBlackmap");
		trFadeOutAllSounds(3);
		trFadeOutMusic(3);
		xResetDatabase(dTemp);
		TutorialMode = false;
		for(p=1 ; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			xSetInt(dPlayerData, xCrocSprintRechargeTime, xGetInt(dPlayerData, xCrocSprintRechargeTime)*4);
		}
	}
}

rule CrocMechanicLoops
highFrequency
inactive
{
	int anim = 0;
	for(p=1 ; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		if(trPlayerResourceCount(p, "Gold") > 0){
			trPlayerGrantResources(p, "Gold", -100000);
			//sprint
			if(xGetBool(dPlayerData, xReadyToLeave) == false){
				if(trTime() >= xGetInt(dPlayerData, xCrocSprintRechargeTimer)){
					if(xGetBool(dPlayerData, xSwimming) == false){
						if(trTime() < xGetInt(dPlayerData, xCrocBonusTimer)){
							//fast water bonus
							modifyProtounitAbsolute(""+CrocProto, p, 1, xGetFloat(dPlayerData, xCrocLandSpeed)*xGetFloat(dPlayerData, xCrocSprintSpeed)*1.25);
						}
						else{
							modifyProtounitAbsolute(""+CrocProto, p, 1, xGetFloat(dPlayerData, xCrocLandSpeed)*xGetFloat(dPlayerData, xCrocSprintSpeed));
						}
						trUnitSelectClear();
						trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
						trUnitOverrideAnimation(13, 0, true, true, -1, 0);
					}
					else{
						modifyProtounitAbsolute(""+CrocProto, p, 1, xGetFloat(dPlayerData, xCrocWaterSpeed)*xGetFloat(dPlayerData, xCrocSprintSpeed));
					}
					xSetInt(dPlayerData, xCrocSprintRechargeTimer, trTime()+xGetInt(dPlayerData, xCrocSprintRechargeTime)+(xGetInt(dPlayerData, xCrocSprintDuration)/1000));
					xSetInt(dPlayerData, xCrocSprintEndTime, trTimeMS()+xGetInt(dPlayerData, xCrocSprintDuration));
					xSetInt(dPlayerData, xCrocSprintState, 1);
					//debugLog("Sprint recharges at " + xGetInt(dPlayerData, xCrocSprintRechargeTimer) + " seconds");
					//debugLog("Sprint ends at " + xGetInt(dPlayerData, xCrocSprintEndTime) + " Mseconds");
					if(trCurrentPlayer() == p){
						trCounterAddTime("sprinttooltip"+p, xGetInt(dPlayerData, xCrocSprintDuration)/1000, 0, "Sprint active", -1);
					}
				}
				else{
					debugLog("Sprint not ready, wait " + (xGetInt(dPlayerData, xCrocSprintRechargeTimer)-trTime()) + " seconds!");
					if(trCurrentPlayer() == p){
						playSound("cantdothat.wav");
					}
				}
			}
		}
		if(trPlayerResourceCount(p, "Wood") > 0){
			trPlayerGrantResources(p, "Wood", -100000);
			//EAT
			if(TutorialMode == true){
				playSound("crocsnap.wav");
				if(trCountUnitsInArea(""+1*trQuestVarGet("P"+p+"Unit"),0, "Zebra", 5) == 1){
					trQuestVarSet("P"+p+"FountainMsg", 3);
				}
				if(QuickStart != 0){
					trQuestVarSet("P"+p+"FountainMsg", 3);
				}
			}
			else{
				for(n = xGetDatabaseCount(dEdibles) ; > 0){
					xDatabaseNext(dEdibles);
					if(trCountUnitsInArea(""+xGetInt(dEdibles, xUnitID),p,""+CrocProto, 5) > 0){
						xUnitSelect(dEdibles, xUnitID);
						trUnitHighlight(1, true);
						if(xGetInt(dEdibles, xType) == 1){
							//Interracting with zebra
							if(xGetInt(dEdibles, xSubtype) == 0){
								xUnitSelect(dEdibles, xUnitID);
								trDamageUnit(1000);
								xFreeDatabaseBlock(dEdibles);
								Zebras = Zebras-1;
								if(trCurrentPlayer() == p){
									playSound("crocsnap.wav");
								}
								trQuestVarModify("P"+p+"FountainMsg", "+", 1);
								if(1*trQuestVarGet("P"+p+"FountainMsg") == 1){
									if(trCurrentPlayer() == p){
										trMessageSetText("Now you'll need to eat the deceased Zebra in order to grow. Right click the dead Zebra.", 7500);
									}
								}
							}
						}
						if(xGetInt(dEdibles, xType) == 2){
							if(xGetInt(dPlayerData, xCrocSize) > 4 ){
								//Interracting with chokonu
								if(xGetInt(dEdibles, xSubtype) == 0){
									xUnitSelect(dEdibles, xUnitID);
									trDamageUnit(1000);
									xFreeDatabaseBlock(dEdibles);
									xUnitSelect(dPoachers, xUnitID);
									xFreeDatabaseBlock(dPoachers);
									xSetFloat(dPlayerData, xCrocFood, xGetFloat(dPlayerData, xCrocFood)+2);
									if(trCurrentPlayer() == p){
										playSound("crocsnap.wav");
										playSound("spidermaledeath" + iModulo(6, (trTime())+1) + ".wav");
									}
								}
							}
						}
						if(xGetInt(dEdibles, xType) == 3){
							if(xGetInt(dPlayerData, xCrocSize) > 2 ){
								//Interracting with kebenit
								if(xGetInt(dEdibles, xSubtype) == 0){
									xUnitSelect(dEdibles, xUnitID);
									trDamageUnit(1000);
									xFreeDatabaseBlock(dEdibles);
									xUnitSelect(dPoachers, xUnitID);
									xFreeDatabaseBlock(dPoachers);
									if(trCurrentPlayer() == p){
										playSound("crocsnap.wav");
									}
								}
							}
						}
						if(xGetInt(dEdibles, xType) == 4){
							if(xGetInt(dPlayerData, xCrocSize) > 9 ){
								//Interracting with sentinel
								if(xGetInt(dEdibles, xSubtype) == 0){
									xUnitSelect(dEdibles, xUnitID);
									trDamageUnit(1000);
									xFreeDatabaseBlock(dEdibles);
									xUnitSelect(dPoachers, xUnitID);
									xFreeDatabaseBlock(dPoachers);
									if(trCurrentPlayer() == p){
										playSound("crocsnap.wav");
									}
								}
							}
						}
						if(xGetInt(dEdibles, xType) == 5){
							if(xGetInt(dPlayerData, xCrocSize) > 7 ){
								//Interracting with peltast
								if(xGetInt(dEdibles, xSubtype) == 0){
									xUnitSelect(dEdibles, xUnitID);
									trDamageUnit(1000);
									xFreeDatabaseBlock(dEdibles);
									xUnitSelect(dPoachers, xUnitID);
									xFreeDatabaseBlock(dPoachers);
									xSetFloat(dPlayerData, xCrocFood, xGetFloat(dPlayerData, xCrocFood)+3);
									if(trCurrentPlayer() == p){
										playSound("crocsnap.wav");
										playSound("spidermaledeath" + iModulo(6, (trTime())+1) + ".wav");
									}
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
		if(trTimeMS() > xGetInt(dPlayerData, xCrocSprintEndTime)){
			//if(xGetInt(dPlayerData, xCrocSprintEndTime) != 0){
			//debugLog("Time end" + xGetInt(dPlayerData, xCrocSprintEndTime));
			if(xGetInt(dPlayerData, xCrocSprintState) == 1){
				if(xGetBool(dPlayerData, xSwimming) == false){
					modifyProtounitAbsolute(""+CrocProto, p, 1, xGetFloat(dPlayerData, xCrocLandSpeed));
					trUnitSelectClear();
					trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
					trUnitOverrideAnimation(15, 0, true, true, -1, 0);
				}
				else{
					modifyProtounitAbsolute(""+CrocProto, p, 1, xGetFloat(dPlayerData, xCrocWaterSpeed));
				}
				xSetInt(dPlayerData, xCrocSprintState, 0);
				if(trCurrentPlayer() == p){
					trCounterAddTime("sprinttooltip"+p, xGetInt(dPlayerData, xCrocSprintRechargeTimer)-trTime(), 0, "Sprint recharging", -1);
				}
				//debugLog("Sprint off");
				if(trCurrentPlayer() == p){
					playSound("godpowerfailed.wav");
				}
			}
			//}
		}
		anim = kbUnitGetAnimationActionType(kbGetBlockID(""+1*trQuestVarGet("P"+p+"Unit")+""));
		if(anim == 5){
			xSetFloat(dPlayerData, xCrocFood, xGetFloat(dPlayerData, xCrocFood)+0.01);
			//about 1000 for level 2
		}
	}
}
