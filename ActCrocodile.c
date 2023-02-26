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
		//trDelayedRuleActivation("GoatMinigameDetect");
		trDelayedRuleActivation("TEST");
		trDelayedRuleActivation("CrocEndZoneSee");
		trDelayedRuleActivation("CrocAllDead");
		//trDelayedRuleActivation("GoatPoacherTimer");
		xsEnableRule("CrocPoacherMovement");
		//trDelayedRuleActivation("GoatBonus");
		//trSetCounterDisplay("<color={PlayerColor(2)}>Fencing destroyed: "+FencesDone+"/8");
		ColouredIconChat("1,0.5,0", ActIcon(Stage), "<u>" + ActName(Stage) + "</u>");
		//ColouredIconChat("0.0,0.8,0.2", "icons\building norse shrine icon 64", "Interract with shrines using W.");
		ColouredChat("0.0,0.8,0.2", "Use 'W' to kill and eat zebras to grow.");
		ColouredChat("0.0,0.8,0.2", "As always watch out for poachers.");
		xsEnableRule("PlayMusic");
		//SpawnRhinoPoacher(xsMax(PlayersActive,3));
		//SpawnRhinoSuperPoacher(1);
		PlayersDead = 0;
		timediff = trTimeMS();
		timelast = trTimeMS();
		trDelayedRuleActivation("CrocActLoops");
		//SpawnGoatPoacher(2);
		modifyProtounitAbsolute("Throwing Axeman", cNumberNonGaiaPlayers, 55, 1);
		for(p = 1 ; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			xSetInt(dPlayerData, xCrocSize, 1);
			xSetFloat(dPlayerData, xCrocNext, 5*xGetInt(dPlayerData, xCrocSize));
			trQuestVarSet("P"+p+"FountainMsg", 0);
		}
		trQuestVarSet("NextPoacherSpawn", trTime()+220);
		SpawnEdible(cNumberNonGaiaPlayers*2);
		trRateConstruction(20);
		SpawnCrocPoacher1(2);
		SpawnCrocPoacher2(1);
		modifyProtounitAbsolute("Chu Ko Nu", cNumberNonGaiaPlayers, 0, 5);
		modifyProtounitAbsolute("Chu Ko Nu", cNumberNonGaiaPlayers, 12, 3);
		modifyProtounitAbsolute("Chu Ko Nu", cNumberNonGaiaPlayers, 26, 0);
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
		for(p = 1; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
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
			}
			if(trCurrentPlayer() == p){
				trSetCounterDisplay("Food: " + 1*xGetFloat(dPlayerData, xCrocFood) + " | Next: " + 1*xGetFloat(dPlayerData, xCrocNext));
			}
			if((xGetBool(dPlayerData, xStopDeath) == false) && (trPlayerUnitCountSpecific(p, ""+CrocProto) == 0) && (trPlayerUnitCountSpecific(p, "Prisoner") == 0) && (trPlayerGetPopulation(p) == 0) && (trPlayerUnitCountSpecific(p, "Anubite") == 0) && (xGetBool(dPlayerData, xPlayerActive) == true) && (xGetBool(dPlayerData, xPlayerDead) == false) && (InMinigame == false)){
				//PLAYER DEAD
				PlayersDead = PlayersDead+1;
				xSetBool(dPlayerData, xPlayerDead, true);
				PlayerColouredChat(p, trStringQuestVarGet("p"+p+"name") + " is dead!");
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
				if(trCountUnitsInArea(""+n,pl,""+CrocProto, 5) > 0){
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
		if(xGetDatabaseCount(dEdibles) < 2){
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
	}
	trClearCounterDisplay();
	xsEnableRule("ScoreScreenStart");
	xsDisableSelf();
}
