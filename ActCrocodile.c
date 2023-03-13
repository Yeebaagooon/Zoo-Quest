void AskQuestion(int p = 0){
	xSetPointer(dPlayerData, p);
	trQuestVarSetFromRand("temp", 1, 1*trQuestVarGet("MaxQNumber"));
	PlayerChoice(p, trStringQuestVarGet("Question"+1*trQuestVarGet("temp")), "True", 44, "False", 45, 20000);
	if(iModulo(2, 1*trQuestVarGet("temp")) == 0){
		xSetInt(dPlayerData, xQuestionAnswer, 0);
	}
	else{
		xSetInt(dPlayerData, xQuestionAnswer, 1);
	}
}

rule BuildCrocArea
highFrequency
inactive
{
	if (trTime() > cActivationTime + 1) {
		TutorialMode = false;
		createCrocArea();
		xsDisableSelf();
		//replaceTerrainAboveHeightMax("ForestFloorPine", "GrassB", 0.0);
		trLetterBox(false);
		trUIFadeToColor(0,0,0,100,800,false);
		uiZoomToProto(""+CrocProto);
		uiLookAtProto(""+CrocProto);
		trDelayedRuleActivation("ResetBlackmap");
		trDelayedRuleActivation("CrocMinigameDetect");
		trDelayedRuleActivation("TEST");
		trDelayedRuleActivation("CrocEndZoneSee");
		trDelayedRuleActivation("CrocAllDead");
		trDelayedRuleActivation("CrocPoacherTimer");
		xsEnableRule("CrocPoacherMovement");
		//trDelayedRuleActivation("GoatBonus");
		//trSetCounterDisplay("<color={PlayerColor(2)}>Fencing destroyed: "+FencesDone+"/8");
		ColouredIconChat("1,0.5,0", ActIcon(Stage), "<u>" + ActName(Stage) + "</u>");
		//ColouredIconChat("0.0,0.8,0.2", "icons\building norse shrine icon 64", "Interract with shrines using W.");
		ColouredChat("0.0,0.8,0.2", "Use 'W' to kill and eat zebras to grow.");
		ColouredChat("0.0,0.8,0.2", "As always watch out for poachers.");
		ColouredChat("0.0,0.8,0.2", "Grow at least one player to level 7.");
		xsEnableRule("PlayMusic");
		PlayersDead = 0;
		timediff = trTimeMS();
		timelast = trTimeMS();
		trDelayedRuleActivation("CrocActLoops");
		for(p = 1 ; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			xSetInt(dPlayerData, xCrocSize, 1);
			xSetFloat(dPlayerData, xCrocNext, 5*xGetInt(dPlayerData, xCrocSize));
			trQuestVarSet("P"+p+"FountainMsg", 0);
		}
		trQuestVarSet("NextPoacherSpawn", trTime()+220);
		trQuestVarSet("NextFoodSpawn", trTime()+90);
		SpawnEdible(cNumberNonGaiaPlayers*2);
		trRateConstruction(20);
		SpawnCrocPoacher1(xsMax(4, cNumberNonGaiaPlayers+2));
		SpawnCrocPoacher2(xsMax(3, cNumberNonGaiaPlayers));
		modifyProtounitAbsolute("Chu Ko Nu", cNumberNonGaiaPlayers, 0, 5);
		modifyProtounitAbsolute("Chu Ko Nu", cNumberNonGaiaPlayers, 12, 3);
		modifyProtounitAbsolute("Chu Ko Nu", cNumberNonGaiaPlayers, 26, 0);
		modifyProtounitAbsolute("Chu Ko Nu", cNumberNonGaiaPlayers, 31, 1);
		ActPart = 1;
		//SpawnCrocPoacher4(1);
		CrocTarget = 5*PlayersActive;
		SpawnRelic(PlayersActive);
	}
}

rule CrocPoacherTimer
highFrequency
inactive
{
	if (trTime() > 1*trQuestVarGet("NextPoacherSpawn")) {
		if(InMinigame == false){
			if(Stage == 4){
				SpawnEdible(cNumberNonGaiaPlayers+1);
				trQuestVarSet("NextPoacherSpawn", trTime()+40+iModulo(90, trTimeMS()));
				SpawnCrocPoacher1(xsMin(4, cNumberNonGaiaPlayers+2));
				if(CrocProgress < 2*PlayersActive){
					SpawnCrocPoacher2(xsMax(3, cNumberNonGaiaPlayers));
				}
				if(CrocProgress >= 2*PlayersActive){
					SpawnCrocPoacher3(1);
					SpawnEdible(1);
				}
				if(CrocProgress >= 3*PlayersActive){
					SpawnCrocPoacher4(iModulo(2, trTime())+1);
					trOverlayText("Super Poachers Spawning...", 5.0,-1,-1,600);
					playSound("\cinematics\04_in\armyarrive.wav");
				}
				if(CrocProgress >= 4*PlayersActive){
					SpawnCrocPoacher4(xsMax(1,PlayersActive-2));
				}
				if(CrocProgress >= 5*PlayersActive){
					SpawnCrocPoacher4(xsMax(1,PlayersActive-2));
					SpawnCrocPoacher3(1);
				}
				if(1*trQuestVarGet("AllowS4Uber") > 0){
					trOverlayText("Uber Poacher Spawning... run!", 5.0,-1,-1,600);
					playSound("\cinematics\04_in\armyarrive.wav");
					UberCrocPoacher(1);
					trQuestVarModify("NextPoacherSpawn", "-", 30);
				}
				if(1*trQuestVarGet("FirstBuffer") == 0){
					trQuestVarModify("NextPoacherSpawn", "+", 40);
					trQuestVarSet("FirstBuffer", 1);
					SpawnEdible(2);
				}
			}
		}
	}
}

rule CrocFoodTimer
highFrequency
inactive
{
	if (trTime() > 1*trQuestVarGet("NextFoodSpawn")) {
		if(Stage == 4){
			trQuestVarSet("NextFoodSpawn", trTime()+30+iModulo(120, trTimeMS()));
			if(Zebras < PlayersActive*2){
				SpawnEdible(xsMax(4, CrocProgress));
			}
		}
	}
}

rule CrocActLoops
highFrequency
inactive
{
	if(Stage == 4){
		timediff = 0.001 * (trTimeMS() - timelast); // calculate timediff
		timelast = trTimeMS();
		tempV = vector(0,0,0);
		int temp = 0;
		if(xGetDatabaseCount(dMissiles) > 0){
			DoMissile();
		}
		if(xGetDatabaseCount(dBurner) > 0){
			for(a = xGetDatabaseCount(dBurner); > 0){
				xDatabaseNext(dBurner);
				if(trCountUnitsInArea(""+xGetInt(dBurner, xUnitID),0, "Palm", 2) > 0){
					trUnitSelectClear();
					xUnitSelect(dBurner, xUnitID);
					trUnitChangeProtoUnit("Palm");
					tempV = kbGetBlockPosition(""+xGetInt(dBurner, xUnitID));
					temp = trGetNextUnitScenarioNameNumber();
					UnitCreateV(0, "Dwarf", tempV);
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitChangeProtoUnit("Meteor Impact Ground");
					temp = trGetNextUnitScenarioNameNumber();
					UnitCreateV(0, "Dwarf", tempV);
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitChangeProtoUnit("Underworld Smoke");
					playSound("meteorbighit.wav");
					playSound("forestfirebirth.wav");
					xAddDatabaseBlock(dDestroyMe, true);
					xSetInt(dDestroyMe, xDestroyName, temp);
					xSetInt(dDestroyMe, xDestroyTime, trTimeMS()+6000);
					trUnitSelectClear();
					xUnitSelect(dBurner, xUnitID);
					trTechInvokeGodPower(0, "Forest Fire", vector(0,0,0), vector(0,0,0));
					xFreeDatabaseBlock(dBurner);
				}
			}
		}
		for(a = xGetDatabaseCount(dPoachers); > 0){
			xDatabaseNext(dPoachers);
			xUnitSelect(dPoachers, xUnitID);
			if(trUnitAlive() == false){
				xFreeDatabaseBlock(dPoachers);
				PoachersDead = PoachersDead+1;
			}
		}
		if(ActPart == 1){
			if(CrocProgress >= 7){
				ActPart = 2;
			}
		}
		for(p = 1; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if((playerIsPlaying(p) == false) && (xGetBool(dPlayerData, xPlayerActive) == true) && (xGetBool(dPlayerData, xPlayerDead) == false)){
				trUnitSelectByQV("P"+p+"Unit");
				trUnitChangeProtoUnit("Ragnorok SFX");
				trUnitSelectByQV("P"+p+"Unit");
				trUnitDestroy();
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
				trUnitChangeProtoUnit("Hero Death");
				xSetBool(dPlayerData, xPlayerActive, false);
				PlayersActive = PlayersActive-1;
			}
			if(trCurrentPlayer() == p){
				if(xGetInt(dPlayerData, xCrocSize) < 7){
					trSetCounterDisplay("Level: " + xGetInt(dPlayerData, xCrocSize) + "/7");
				}
				else{
					trSetCounterDisplay("Level: " + xGetInt(dPlayerData, xCrocSize));
				}
				trCounterAbort("CrocC"+p);
				trCounterAbort("CrocR"+p);
				trCounterAddTime("CrocC"+p, -100, -10, "Food: " + 1*xGetFloat(dPlayerData, xCrocFood) + " | Next: " + 1*xGetFloat(dPlayerData, xCrocNext), -1);
				if((xGetInt(dPlayerData, xRelics) == 1) && (xGetString(dPlayerData, xCrocProto) == CrocProto)){
					trCounterAddTime("CrocR"+p, -100, -10, "Gold: " + 1*xGetInt(dPlayerData, xRelics) + "/2", -1);
				}
				if((xGetInt(dPlayerData, xRelics) > 1) && (xGetString(dPlayerData, xCrocProto) == CrocProto)){
					trCounterAddTime("CrocR"+p, -100, -10, "Press E for temporary ranged attack", -1);
				}
			}
			if((xGetBool(dPlayerData, xStopDeath) == false) && (trPlayerUnitCountSpecific(p, ""+CrocProto) == 0) && (trPlayerUnitCountSpecific(p, "Prisoner") == 0) && (trPlayerGetPopulation(p) == 0) && (xGetBool(dPlayerData, xPlayerActive) == true) && (xGetBool(dPlayerData, xPlayerDead) == false) && (InMinigame == false)){
				//PLAYER DEAD
				PlayersDead = PlayersDead+1;
				xSetBool(dPlayerData, xPlayerDead, true);
				PlayerColouredChat(p, trStringQuestVarGet("p"+p+"name") + " is dead!");
				PlayerColouredChatToSelf(p, "You'll be able to join the next act if your team pass this one.");
				trPlayerKillAllGodPowers(p);
				xSetVector(dPlayerData, xDeathVector, kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
				trTechGodPower(1, "Rain", 1);
				if(iModulo(2, trTime()) == 0){
					playSound("\dialog\ko\skul062.mp3");
				}
				else{
					playSound("\xpack\xdialog\ko\xkri075.mp3");
				}
			}
			if(xGetInt(dPlayerData, xHPRegen) > 0){
				if(trTime() > xGetInt(dPlayerData, xHPRegenNext)){
					trUnitSelectByQV("P"+p+"Unit");
					trDamageUnit(-1*xGetInt(dPlayerData, xHPRegen));
					xSetInt(dPlayerData, xHPRegenNext, trTime()+xGetInt(dPlayerData, xHPRegenTime));
				}
			}
			if(xGetFloat(dPlayerData, xCrocFood) >= xGetFloat(dPlayerData, xCrocNext)){
				CrocGrow(p);
			}
			if(InMinigame == true){
				if(xGetInt(dPlayerData, xAnswer) > -1){
					if(xGetInt(dPlayerData, xQuestionAnswer) == 1){
						if(xGetInt(dPlayerData, xAnswer) == 1){
							ColouredChatToPlayer(p, "0,1,0", "Correct!");
							xSetInt(dPlayerData, xQuestionsCorrect, xGetInt(dPlayerData, xQuestionsCorrect)+1);
							if(trCurrentPlayer() == p){
								playSoundCustom("favordump.wav", "\Yeebaagooon\Zoo Quest\Gem.mp3");
							}
						}
						else{
							ColouredChatToPlayer(p, "1,0,0", "Wrong!");
							if(trCurrentPlayer() == p){
								playSoundCustom("cantdothat.wav", "cantdothat.wav");
							}
						}
					}
					else{
						if(xGetInt(dPlayerData, xAnswer) == 0){
							ColouredChatToPlayer(p, "0,1,0", "Correct!");
							if(trCurrentPlayer() == p){
								playSoundCustom("favordump.wav", "\Yeebaagooon\Zoo Quest\Gem.mp3");
							}
							xSetInt(dPlayerData, xQuestionsCorrect, xGetInt(dPlayerData, xQuestionsCorrect)+1);
						}
						else{
							ColouredChatToPlayer(p, "1,0,0", "Wrong!");
							if(trCurrentPlayer() == p){
								playSoundCustom("cantdothat.wav", "cantdothat.wav");
							}
						}
					}
					
					xSetInt(dPlayerData, xAnswer, -1);
					xSetInt(dPlayerData, xQuestionAnswer, -1);
					xSetInt(dPlayerData, xQuestions, xGetInt(dPlayerData, xQuestions)-1);
					if(xGetInt(dPlayerData, xQuestions) > 0){
						AskQuestion(p);
						debugLog("Q asked to P" + p);
						debugLog("Qs remaining P"+p+": " + xGetInt(dPlayerData, xQuestions));
					}
					else{
						xSetInt(dPlayerData, xAnswer, -1);
						if(xGetInt(dPlayerData, xQuestionsCorrect) > 2){
							if(trCurrentPlayer() == p){
								playSound("xwin.wav");
							}
							MinigameWins = MinigameWins+1;
							if(iModulo(2, trTime()) == 0){
								PlayerChoice(p, "Choose your reward:", "Instant grow", 35, "+2 hp regen every 20s", 46, 10000);
							}
							else{
								PlayerChoice(p, "Choose your reward:", "+2s sprint time", 47, "-4s sprint cooldown", 48, 10000);
							}
							
						}
						else{
							if(trCurrentPlayer() == p){
								playSound("xlose.wav");
								trOverlayText("Minigame Failed!", 3.0,-1,-1,600);
							}
						}
						PlayersMinigaming = PlayersMinigaming-1;
					}
				}
			}
			//save
			if((xGetInt(dPlayerData, xQuestions) > 0) && (1*trQuestVarGet("P"+p+"ChoiceDialog") == 0)){
				AskQuestion(p);
				debugLog("Saved P" + p);
			}
		}
		if((PlayersActive == PlayersReadyToLeave+PlayersDead) && (PlayersDead != PlayersActive)){
			xsEnableRule("CrocExit");
		}
		if(xGetDatabaseCount(dChests) > 0){
			xDatabaseNext(dChests);
			int n = xGetInt(dChests, xUnitID);
			xUnitSelect(dChests,xUnitID);
			if(trCountUnitsInArea(""+n,0,"Great Box", 1) == 0){
				xFreeDatabaseBlock(dChests);
				debugLog("Chest removed" + n);
				debugLog(""+kbGetProtoUnitID(""+n));
				ChestsTotal = ChestsTotal-1;
				//CreateChest(iModulo(252, trTimeMS()),iModulo(252, trTime()));
			}
			if (trUnitIsSelected()) {
				uiClearSelection();
				startNPCDialog(5);
			}
			trUnitSelectClear();
			for(pl=1 ; < cNumberNonGaiaPlayers){
				if(trCountUnitsInArea(""+n,pl,xGetString(dPlayerData, xCrocProto), 5) > 0){
					xUnitSelect(dChests,xUnitID);
					trUnitSetAnimation("SE_Great_Box_Opening",false,-1);
					xUnitSelect(dChests,xUnitID);
					trUnitHighlight(3, false);
					trUnitSelectClear();
					xUnitSelect(dChests, xUnlockUnitID);
					trUnitChangeProtoUnit("Spy Eye");
					trUnitSelectClear();
					xUnitSelect(dChests, xUnlockUnitID);
					trMutateSelected(kbGetProtoUnitID("Pyramid Osiris Xpack"));
					trUnitSelectClear();
					xUnitSelect(dChests, xUnlockUnitID);
					trSetSelectedScale(100,0,0);
					trUnitSelectClear();
					xUnitSelect(dChests, xUnlockUnitID);
					trUnitOverrideAnimation(6, 0, false, true, -1);
					trUnitSelectClear();
					xUnitSelect(dChests, xUnlockUnitID);
					trUnitSetAnimationPath("0,1,0,0,0,0");
					xAddDatabaseBlock(dDestroyMe, true);
					xSetInt(dDestroyMe, xDestroyName, xGetInt(dChests, xUnlockUnitID));
					xSetInt(dDestroyMe, xDestroyTime, trTimeMS()+3000);
					ChestsFound = ChestsFound+1;
					xFreeDatabaseBlock(dChests);
					trQuestVarSetFromRand("temp", 1, 3);
					trQuestVarSetFromRand("temp2", 1, 3);
					if(1*trQuestVarGet("temp") == 1){
						if(1*trQuestVarGet("temp2") == 1){
							PlayerChoice(pl, "Choose your reward:", "+5 hp", 36, "+4 LOS", 37, 10000);
						}
						if(1*trQuestVarGet("temp2") == 2){
							PlayerChoice(pl, "Choose your reward:", "+5 hp", 36, "+1s sprint time", 40, 10000);
						}
						if(1*trQuestVarGet("temp2") == 3){
							PlayerChoice(pl, "Choose your reward:", "Instant grow", 35, "+1hp regen every 20s", 43, 10000);
						}
					}
					if(1*trQuestVarGet("temp") == 2){
						if(1*trQuestVarGet("temp2") == 1){
							PlayerChoice(pl, "Choose your reward:", "+4 LOS", 37, "+0.4 land speed", 38, 10000);
						}
						if(1*trQuestVarGet("temp2") == 2){
							PlayerChoice(pl, "Choose your reward:", "+4 LOS", 37, "+0.6 swim speed", 39, 10000);
						}
						if(1*trQuestVarGet("temp2") == 3){
							PlayerChoice(pl, "Choose your reward:", "+0.3 sprint speed multiplier", 42, "-2s sprint cd", 41, 10000);
						}
					}
					if(1*trQuestVarGet("temp") == 3){
						if(1*trQuestVarGet("temp2") == 1){
							PlayerChoice(pl, "Choose your reward:", "+1s sprint time", 40, "-2s sprint cd", 41, 10000);
						}
						if(1*trQuestVarGet("temp2") == 2){
							PlayerChoice(pl, "Choose your reward:", "Instant grow", 35, "+0.3 sprint speed multiplier", 42, 10000);
						}
						if(1*trQuestVarGet("temp2") == 3){
							PlayerChoice(pl, "Choose your reward:", "+0.4 land speed", 38, "+0.6 swim speed", 39, 10000);
						}
					}
					
					
				}
			}
		}
		if(Zebras <= PlayersActive/2){
			SpawnEdible(cNumberNonGaiaPlayers);
			SpawnCrocPoacher1(2);
			SpawnCrocPoacher2(1);
		}
		
	}
	
}

rule CrocLeave
inactive
highFrequency
{
	int STOP = 0;
	trQuestVarModify("PlayerCycle", "+", 1);
	if(1*trQuestVarGet("PlayerCycle") > cNumberNonGaiaPlayers){
		trQuestVarSet("PlayerCycle", 1);
	}
	int p = 1*trQuestVarGet("PlayerCycle");
	xSetPointer(dPlayerData, p);
	tempV = kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit"));
	if(xGetBool(dPlayerData, xReadyToLeave) == true){
		if((trGetTerrainType(1*xsVectorGetX(tempV)/2,1*xsVectorGetZ(tempV)/2) != getTerrainType(LeaveTerrain)) || (trGetTerrainSubType(1*xsVectorGetX(tempV)/2,1*xsVectorGetZ(tempV)/2) != getTerrainSubType(LeaveTerrain))){
			xSetBool(dPlayerData, xReadyToLeave, false);
			xSetBool(dPlayerData, xStopDeath, false);
			PlayersReadyToLeave = PlayersReadyToLeave-1;
			trUnitSelectByQV("P"+p+"Unit");
			trMutateSelected(kbGetProtoUnitID(""+CrocProto));
			PlayerColouredChatToSelf(p, "You have left the extraction zone");
			STOP = 1;
		}
	}
	if((xGetBool(dPlayerData, xReadyToLeave) == false) && (STOP == 0) && (xGetBool(dPlayerData, xPlayerDead) == false)){
		if((trGetTerrainType(1*xsVectorGetX(tempV)/2,1*xsVectorGetZ(tempV)/2) == getTerrainType(LeaveTerrain)) && (trGetTerrainSubType(1*xsVectorGetX(tempV)/2,1*xsVectorGetZ(tempV)/2) == getTerrainSubType(LeaveTerrain))){
			xSetBool(dPlayerData, xReadyToLeave, true);
			xSetBool(dPlayerData, xStopDeath, true);
			PlayersReadyToLeave = PlayersReadyToLeave+1;
			trUnitSelectByQV("P"+p+"Unit");
			trMutateSelected(kbGetProtoUnitID("Prisoner"));
			PlayerColouredChat(p, trStringQuestVarGet("p"+p+"name") + " is ready to leave");
			if(trQuestVarGet("P"+p+"LeaveMsg") == 0){
				trQuestVarSet("P"+p+"LeaveMsg", 1);
				ColouredChatToPlayer(p, "1,1,0", "You cannot use abilities in the extraction zone.");
				ColouredChatToPlayer(p, "1,1,0", "You also cannot die or be attacked.");
			}
		}
	}
}

rule CrocPoacherMovement
inactive
highFrequency
{
	if(xGetDatabaseCount(dPoachers) > 0){
		xDatabaseNext(dPoachers);
		if(xGetInt(dPoachers, xMoveTime) < trTime()){
			trQuestVarSetFromRand("x",0,252);
			trQuestVarSetFromRand("y",30,80);
			trQuestVarSetFromRand("z",0,252);
			xSetInt(dPoachers, xMoveTime, trTime()+1*trQuestVarGet("y"));
			xUnitSelect(dPoachers, xUnitID);
			trUnitMoveToPoint(1*trQuestVarGet("x"),5,1*trQuestVarGet("z"),-1,true);
		}
	}
}

rule CrocEndZoneSee
inactive
highFrequency
{
	for(p=1 ; < cNumberNonGaiaPlayers){
		trUnitSelectByQV("P"+p+"Unit");
		if(trUnitDistanceToUnit(""+FlagUnitID) < 23){
			vector flagV = kbGetBlockPosition(""+FlagUnitID);
			for(x=1 ; < cNumberNonGaiaPlayers){
				trMinimapFlare(x,10,flagV,true);
			}
			UnitCreate(0, "Revealer", xsVectorGetX(flagV),xsVectorGetZ(flagV),0);
			trMessageSetText("The extraction zone has been found. Gather here when you are ready to end the act.", 8000);
			playSound("examinationbirth.wav");
			trUnitSelectClear();
			trUnitSelect(""+FlagUnitID);
			trUnitHighlight(10, true);
			trDelayedRuleActivation("CrocLeave");
			xsDisableSelf();
		}
	}
}

rule CrocAllDead
inactive
minInterval 5
{
	if((Stage == 4) && (PlayersDead == PlayersActive)){
		trShowWinLose("All players are dead", "xlose.wav");
		for(p=1 ; < cNumberNonGaiaPlayers){
			trSetPlayerDefeated(p);
		}
		xsDisableSelf();
		trEndGame();
	}
}

rule CrocMinigameDetect
highFrequency
inactive
{
	//xsSetContextPlayer(0);
	vector pos = vector(0,0,0);
	vector minigame = kbGetBlockPosition(""+1*trQuestVarGet("MinigameStartID"));
	for(p=1 ; < cNumberNonGaiaPlayers){
		pos = kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit"));
		if(distanceBetweenVectors(minigame, pos, true) < 10){
			trUnitSelectByQV("MinigameStartSFX");
			trUnitChangeInArea(0,0,"Palm", "Rocket", 10);
			trUnitSelectByQV("MinigameStartSFX");
			trUnitChangeProtoUnit("Olympus Temple SFX");
			trUnitSelectByQV("MinigameStartID");
			trUnitChangeProtoUnit("Forest Fire SFX");
			PaintAtlantisArea(xsVectorGetX(StageVector)-2,xsVectorGetZ(StageVector)-2,xsVectorGetX(StageVector)+2,xsVectorGetZ(StageVector)+2,0,53);
			refreshPassability();
			trMessageSetText("Minigame found! Remain in the white square if you wish to play.", 10000);
			trCounterAddTime("CDMG", 12-(QuickStart*2), 0, "<color={PlayerColor("+p+")}>Minigame Starts", 38);
			MinigameFound = true;
			for(x=1 ; < cNumberNonGaiaPlayers){
				xSetPointer(dPlayerData, x);
				if(x != p){
					if(xGetBool(dPlayerData, xPlayerDead) == false){
						PlayerChoice(x, "Participate in minigame?", "Yes", 4, "No", 0, 11900);
					}
				}
			}
			for(b = xGetDatabaseCount(dPoachers); > 0){
				xDatabaseNext(dPoachers);
				xUnitSelect(dPoachers, xUnitID);
				trUnitChangeProtoUnit("Cinematic Block");
			}
			for(c = xGetDatabaseCount(dMissiles); > 0){
				xDatabaseNext(dMissiles);
				xUnitSelect(dMissiles, xUnitID);
				trUnitDestroy();
				xFreeDatabaseBlock(dMissiles);
			}
			trMusicStop();
			playSound("\cinematics\22_in\music 2.mp3");
			xsEnableRule("CrocQuizQuestions");
			xsDisableSelf();
		}
	}
}

void CrocMinigameGo(int temp = 0){
	xsEnableRule("MGGOCroc");
}

rule MGGOCroc
inactive
highFrequency
{
	InMinigame = true;
	int temp = trGetNextUnitScenarioNameNumber();
	int StartX = xsVectorGetX(StageVector);
	int StartZ = xsVectorGetZ(StageVector);
	temp = trGetNextUnitScenarioNameNumber();
	for(p=1 ; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		if(xGetBool(dPlayerData, xPlayerActive)){
			trVectorQuestVarSet("P"+p+"PosMG", kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
			trVectorQuestVarSet("P"+p+"PosMG", trVectorQuestVarGet("P"+p+"PosMG")/2);
			if((trVectorQuestVarGetX("P"+p+"PosMG") > xsVectorGetX(StageVector)-2) && (trVectorQuestVarGetX("P"+p+"PosMG") < xsVectorGetX(StageVector)+2) && (trVectorQuestVarGetZ("P"+p+"PosMG") > xsVectorGetZ(StageVector)-2) && (trVectorQuestVarGetZ("P"+p+"PosMG") < xsVectorGetZ(StageVector)+2)){
				PlayerColouredChat(p, trStringQuestVarGet("p"+p+"name") + " is playing");
				PlayersMinigaming = PlayersMinigaming+1;
				xSetBool(dPlayerData, xStopDeath, true);
				xSetInt(dPlayerData, xQuestions, 4);
				AskQuestion(p);
				if(xGetInt(dPlayerData, xTeleportDue) == 0){
					xSetVector(dPlayerData, xVectorHold, kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
				}
			}
		}
	}
	refreshPassability();
	if(PlayersMinigaming == 0){
		//end MG
		trUnitSelectByQV("MinigameStartSFX");
		trUnitDestroy();
		trUnitSelectByQV("MinigameStartID");
		trUnitDestroy();
		trMessageSetText("Nobody was on the white tiles. Minigame cancelled.", 5000);
		for(b = xGetDatabaseCount(dPoachers); > 0){
			xDatabaseNext(dPoachers);
			xUnitSelect(dPoachers, xUnitID);
			trUnitChangeProtoUnit(xGetString(dPoachers, xPoacherType));
		}
		InMinigame = false;
		xsEnableRule("PlayMusic");
		trPaintTerrain(xsVectorGetX(StageVector)-1,xsVectorGetZ(StageVector)-1,xsVectorGetX(StageVector)+1,xsVectorGetZ(StageVector)+1,0,51);
		refreshPassability();
		for(p=1 ; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if((trPlayerUnitCountSpecific(p, ""+CrocProto) == 0) && (xGetBool(dPlayerData, xPlayerDead) == false)){
				CreateCroc(p, xsVectorGetX(StageVector), xsVectorGetZ(StageVector), 0);
			}
		}
	}
	else{
		trMessageSetText("This minigame is a quiz, get 3/4 questions right to win!", 8000);
		trCounterAddTime("cdCrocminigame", 90,0,"<color={PlayerColor(2)}>Minigame time remaining", 39);
		playSoundCustom("\xpack\xcinematics\6_a\music.mp3", "\Yeebaagooon\Zoo Quest\Minigame4.mp3");
		xsEnableRule("CrocMinigameEnd");
	}
	xsDisableSelf();
}

void CrocMGTimeout(int eventID = 0){
	PlayersMinigaming = 0;
}

rule CrocMinigameEnd
inactive
highFrequency
{
	if(PlayersMinigaming <= 0){
		vector temp = vector(0,0,0);
		trPaintTerrain(xsVectorGetX(StageVector)-1,xsVectorGetZ(StageVector)-1,xsVectorGetX(StageVector)+1,xsVectorGetZ(StageVector)+1,0,51);
		refreshPassability();
		//for some reason the player data db is destroyed in this minigame - fixed, playerdeath bool
		for(p=1 ; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if((xGetInt(dPlayerData, xTeleportDue) == 1) && (xGetBool(dPlayerData, xPlayerActive) == true)){
				temp = xGetVector(dPlayerData, xVectorHold);
				trQuestVarSet("P"+p+"IG", trGetNextUnitScenarioNameNumber());
				UnitCreateV(p, "Roc", temp, 0);
				trUnitSelectByQV("P"+p+"Unit");
				trImmediateUnitGarrison(""+1*trQuestVarGet("P"+p+"IG"));
				trUnitSelectByQV("P"+p+"IG");
				trUnitChangeProtoUnit("Cinematic Block");
				xSetBool(dPlayerData, xStopDeath, false);
				xSetInt(dPlayerData, xTeleportDue, 0);
			}
			else if((xGetInt(dPlayerData, xTeleportDue) == 0) && (xGetBool(dPlayerData, xPlayerActive) == true)){
				if(trPlayerUnitCountSpecific(p, ""+CrocProto) == 0){
					trQuestVarSet("P"+p+"IG", trGetNextUnitScenarioNameNumber());
					UnitCreateV(p, "Roc", temp, 0);
					trUnitSelectByQV("P"+p+"Unit");
					trImmediateUnitGarrison(""+1*trQuestVarGet("P"+p+"IG"));
					trUnitSelectByQV("P"+p+"IG");
					trUnitChangeProtoUnit("Cinematic Block");
				}
			}
			if(trPlayerUnitCountSpecific(p, ""+CrocProto) == 0){
				CreateCroc(p, trVectorQuestVarGetX("P"+p+"PosMG")*2, trVectorQuestVarGetZ("P"+p+"PosMG")*2, 0);
			}
			xSetBool(dPlayerData, xStopDeath, false);
		}
		uiZoomToProto(""+CrocProto);
		uiLookAtProto(""+CrocProto);
		for(b = xGetDatabaseCount(dPoachers); > 0){
			xDatabaseNext(dPoachers);
			xUnitSelect(dPoachers, xUnitID);
			trUnitChangeProtoUnit(xGetString(dPoachers, xPoacherType));
			if(xGetString(dPoachers, xPoacherType) == "Kebenit"){
				xUnitSelect(dPoachers, xUnitID);
				trSetScale(0.6);
			}
		}
		trUnitSelectByQV("MinigameStartSFX");
		trUnitChangeProtoUnit("Olympus Temple SFX");
		trUnitSelectByQV("MinigameStartID");
		trUnitChangeProtoUnit("Forest Fire SFX");
		xsDisableSelf();
		InMinigame = false;
		PlayersMinigaming = 0;
		trCounterAbort("cdCrocminigame");
		trFadeOutAllSounds(3);
		trFadeOutMusic(3);
		xsEnableRule("PlayMusic");
	}
}

rule CrocExit
inactive
highFrequency
{
	trCounterAbort("poachtimer");
	xsDisableRule("CrocActLoops");
	xsDisableRule("CrocAllDead");
	xsDisableRule("CrocPoacherMovement");
	xsDisableRule("CrocEndZoneSee");
	xsDisableRule("CrocLeave");
	xsDisableRule("CrocTutorialLoops");
	xsDisableRule("CrocMinigameDetect");
	xsDisableRule("CrocBonus");
	xsDisableRule("MGGOCroc");
	xsDisableRule("CrocPoacherTimer");
	xsDisableRule("CrocMechanicLoops");
	xsDisableRule("CrocFoodTimer");
	xsDisableRule("CrocMinigameEnd");
	for(p=1 ; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		trUnitSelectByQV("P"+p+"Unit");
		trUnitChangeProtoUnit("Ragnorok SFX");
		trUnitSelectByQV("P"+p+"Unit");
		trUnitDestroy();
		trUnitSelectClear();
		trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
		trUnitChangeProtoUnit("Hero Death");
		trCounterAbort("sprinttooltip"+p);
		trCounterAbort("CrocC"+p);
		trCounterAbort("CrocR"+p);
	}
	trClearCounterDisplay();
	xResetDatabase(dBurner);
	xsEnableRule("ScoreScreenStart");
	xsDisableSelf();
}
