rule BuildRhinoArea
highFrequency
inactive
{
	if (trTime() > cActivationTime + 1) {
		xResetDatabase(dChests);
		createMarsh();
		xsDisableSelf();
		//replaceTerrainAboveHeightMax("ForestFloorPine", "GrassB", 0.0);
		trLetterBox(false);
		trUIFadeToColor(0,0,0,100,800,false);
		uiZoomToProto(""+RhinoProto);
		uiLookAtProto(""+RhinoProto);
		trDelayedRuleActivation("ResetBlackmap");
		trDelayedRuleActivation("RhinoActLoops");
		//trDelayedRuleActivation("DeerMinigameDetect");
		//trDelayedRuleActivation("DeerLeave");
		//trDelayedRuleActivation("TEST");
		trDelayedRuleActivation("RhinoAllDead");
		//trDelayedRuleActivation("PoacherTimer");
		//trDelayedRuleActivation("DeerEndZoneSee");
		//xsEnableRule("DeerPoacherMovement");
		trSetCounterDisplay("<color={PlayerColor(2)}>Fencing destroyed: 0 / " + BerryTarget);
		ColouredIconChat("1,0.5,0", ActIcon(Stage), "<u>" + ActName(Stage) + "</u>");
		ColouredIconChat("0.0,0.8,0.2", "icons\icon building wooden fence 64", "Destroy enough fences.");
		trChatSend(0, "In each act you need to find and move to the extraction zone.");
		trChatSend(0, "It is a ring of ice terrain.");
		trChatSend(0, "When all players are dead or in the zone, the act ends.");
		trChatSend(0, "Make sure to explore, as higher act scores help you out later.");
		xsEnableRule("PlayMusic");
		SpawnRhinoPoacher(xsMax(PlayersActive,2));
		PlayersDead = 0;
		timediff = trTimeMS();
		timelast = trTimeMS();
	}
}

rule RhinoActLoops
highFrequency
inactive
{
	timediff = 0.001 * (trTimeMS() - timelast); // calculate timediff
	timelast = trTimeMS();
	int temp = 0;
	if(xGetDatabaseCount(dMissiles) > 0){
		DoMissile();
	}
	for(p=1 ; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		trUnitSelectByQV("P"+p+"Unit");
		trDamageUnit(1.5*timediff);
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
		if((xGetBool(dPlayerData, xStopDeath) == false) && (trPlayerUnitCountSpecific(p, ""+RhinoProto) == 0) && (trPlayerUnitCountSpecific(p, "Prisoner") == 0) && (xGetBool(dPlayerData, xPlayerActive) == true) && (xGetBool(dPlayerData, xPlayerDead) == false) && (InMinigame == false)){
			//PLAYER DEAD
			PlayersDead = PlayersDead+1;
			xSetBool(dPlayerData, xPlayerDead, true);
			PlayerColouredChat(p, trStringQuestVarGet("p"+p+"name") + " is dead!");
		}
	}
	if((PlayersActive == PlayersReadyToLeave+PlayersDead) && (PlayersDead != PlayersActive)){
		//xsEnableRule("RhinoExit");
	}
	if(xGetDatabaseCount(dChests) > 0){
		xDatabaseNext(dChests);
		int n = xGetInt(dChests, xUnitID);
		xUnitSelect(dChests,xUnitID);
		if(trCountUnitsInArea(""+n,0,"Great Box", 1) == 0){
			xFreeDatabaseBlock(dChests);
			debugLog("Chest removed" + n);
			debugLog(""+kbGetProtoUnitID(""+n));
			//			ChestsTotal = ChestsTotal-1;
			CreateChest(iModulo(252, trTimeMS()),iModulo(252, trTime()));
		}
		if (trUnitIsSelected()) {
			uiClearSelection();
			startNPCDialog(5);
		}
		trUnitSelectClear();
		for(pl=1 ; < cNumberNonGaiaPlayers){
			if(trCountUnitsInArea(""+n,pl,"All", 5) > 0){
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
				if(iModulo(2, trTimeMS()) == 0){
					PlayerChoice(pl, "Choose your reward:", "+2 hp", 12, "+not made", 12, 10000);
				}
				else{
					PlayerChoice(pl, "Choose your reward:", "+2 hp", 12, "not made", 12, 10000);
				}
			}
		}
		
	}
}

rule RhinoAllDead
inactive
minInterval 5
{
	if((Stage == 2) && (PlayersDead == PlayersActive)){
		trShowWinLose("All players are dead", "xlose.wav");
		for(p=1 ; < cNumberNonGaiaPlayers){
			trSetPlayerDefeated(p);
		}
		xsDisableSelf();
		trEndGame();
	}
}

rule RhinoPoacherMovement
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
