/*

Rhino MG - Move to things?
Poachers, two lvels?
Projectile link to ground

EXTRAS
Kill up to 5 extra poachers
Kill an uber poacher
One player survive with full hp
All players complete 2 full charges
Kill first couple of poachers
*/


rule BuildRhinoArea
highFrequency
inactive
{
	if (trTime() > cActivationTime + 1) {
		TutorialMode = false;
		createMarsh();
		xsDisableSelf();
		//replaceTerrainAboveHeightMax("ForestFloorPine", "GrassB", 0.0);
		trLetterBox(false);
		trUIFadeToColor(0,0,0,100,800,false);
		uiZoomToProto(""+RhinoProto);
		uiLookAtProto(""+RhinoProto);
		trDelayedRuleActivation("ResetBlackmap");
		trDelayedRuleActivation("RhinoMinigameDetect");
		trDelayedRuleActivation("TEST");
		trDelayedRuleActivation("RhinoAllDead");
		//trDelayedRuleActivation("PoacherTimer");
		xsEnableRule("RhinoPoacherMovement");
		trSetCounterDisplay("<color={PlayerColor(2)}>Fencing destroyed: "+FencesDone+"/8");
		ColouredIconChat("1,0.5,0", ActIcon(Stage), "<u>" + ActName(Stage) + "</u>");
		ColouredIconChat("0.0,0.8,0.2", "icons\icon building wooden fence 64", "Destroy enough fences.");
		ColouredChat("0.0,0.8,0.2", "Each long fence segment needs at least one break.");
		xsEnableRule("PlayMusic");
		SpawnRhinoPoacher(xsMax(PlayersActive,3));
		//SpawnRhinoSuperPoacher(1);
		PlayersDead = 0;
		timediff = trTimeMS();
		timelast = trTimeMS();
		for(p = 1; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			xSetFloat(dPlayerData, xRhinoChargeTime, xGetInt(dPlayerData, xRhinoChargeTimeMax));
		}
		trDelayedRuleActivation("RhinoActLoops");
	}
}

void ProcessRhinoFence(int count = 5){
	for (x=xsMin(count, xGetDatabaseCount(dFences)); > 0) {
		xDatabaseNext(dFences);
		xUnitSelect(dFences, xUnitID);
		if(trUnitDead() == true){
			if(1*trQuestVarGet("Segment"+xGetInt(dFences, xSegment)+"Broken") == 0){
				trQuestVarModify("Segment"+xGetInt(dFences, xSegment)+"Broken", "+", 1);
				FencesDone = FencesDone+1;
			}
			xFreeDatabaseBlock(dFences);
		}
	}
	//trClearCounterDisplay();
	if(FencesDone < 8){
		trSetCounterDisplay("<color={PlayerColor(2)}>Fencing destroyed: "+FencesDone+"/8");
	}
	else{
		trSetCounterDisplay("<color={PlayerColor(3)}>Fencing destroyed: "+FencesDone+"/8");
		playSoundCustom("xnew_objective.wav", "\Yeebaagooon\Zoo Quest\Skillpoint.mp3");
		xsEnableRule("RhinoPartTwo");
	}
}

void PoacherKillTrack(int count = 5){
	for (x=xsMin(count, xGetDatabaseCount(dPoachers)); > 0) {
		xDatabaseNext(dPoachers);
		xUnitSelect(dPoachers, xUnitID);
		if(trUnitDead() == true){
			PoachersDead = PoachersDead+1;
			xFreeDatabaseBlock(dPoachers);
		}
	}
	//trClearCounterDisplay();
	if(ActPart == 2){
		if(PoachersDead < PoachersTarget){
			trSetCounterDisplay("<color={PlayerColor(2)}>Poachers killed: "+PoachersDead+"/" + PoachersTarget);
		}
		else{
			playSoundCustom("xnew_objective.wav", "\Yeebaagooon\Zoo Quest\Skillpoint.mp3");
			SpawnRhinoPoacher(5);
			trMessageSetText("You must now find the extraction zone. Take care, advanced poachers are coming!", 10000);
			//xsEnableRule("RhinoPartTwo");
			ActPart = 3;
			//	SpawnRhinoSuperPoacher(1);
		}
	}
	if(ActPart == 3){
		trSetCounterDisplay("<color={PlayerColor(3)}>Poachers killed: "+PoachersDead);
	}
}

rule RhinoPartTwo
highFrequency
inactive
{
	if (trTime() > cActivationTime + 4) {
		PoachersTarget = xsMax(PlayersActive*2,5);
		trSetCounterDisplay("<color={PlayerColor(2)}>Poachers killed: "+PoachersDead+"/" + PoachersTarget);
		ActPart = 2;
		trOverlayText("Poachers Spawning...", 5.0,-1,-1,600);
		SpawnRhinoPoacher(2);
		playSound("\cinematics\04_in\armyarrive.wav");
		xsDisableSelf();
		trQuestVarSet("NextPoacherSpawn", trTime()+30);
		xsEnableRule("RhinoPoacherSpawnLoop");
		paintCircle(xsVectorGetX(EndPoint),xsVectorGetZ(EndPoint),8,LeaveTerrain);
		trUnitSelectClear();
		trUnitSelect(""+FlagUnitID);
		trMutateSelected(kbGetProtoUnitID("Flag"));
		trUnitSelectClear();
		trUnitSelect(""+FlagUnitID);
		trUnitSetAnimationPath("0,0,0,0,0,0");
		trUnitSelectClear();
		trUnitSelect(""+FlagSFXID);
		trMutateSelected(kbGetProtoUnitID("Osiris Box Glow"));
		trUnitSelectClear();
		trUnitSelect(""+FlagSFXID);
		trUnitSetAnimationPath("0,0,1,0,0,0");
		trDelayedRuleActivation("RhinoEndZoneSee");
		trDelayedRuleActivation("RhinoLeave");
	}
}

rule RhinoPoacherSpawnLoop
highFrequency
inactive
{
	if (trTime() > 1*trQuestVarGet("NextPoacherSpawn")) {
		if(Stage == 2){
			if(xGetDatabaseCount(dPoachers) < PoachersTarget){
				trQuestVarSetFromRand("temp", 20, 50);
				if(1*trQuestVarGet("temp") < 35){
					SpawnRhinoPoacher(2);
				}
				else{
					SpawnRhinoPoacher(3);
				}
			}
			else{
				trQuestVarSetFromRand("temp", 10, 30);
			}
			trQuestVarModify("NextPoacherSpawn", "+", 1*trQuestVarGet("temp"));
		}
	}
}

rule RhinoActLoops
highFrequency
inactive
{
	if(Stage == 2){
		timediff = 0.001 * (trTimeMS() - timelast); // calculate timediff
		timelast = trTimeMS();
		int temp = 0;
		if(xGetDatabaseCount(dMissiles) > 0){
			DoMissile();
		}
		if(FencesDone < 8){
			ProcessRhinoFence(10);
		}
		else{
			if(ActPart < 2){
				trSetCounterDisplay("<color={PlayerColor(3)}>Fencing destroyed: "+FencesDone+"/8");
			}
			else{
				PoacherKillTrack(5);
			}
		}
		for(p=1 ; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(trPlayerUnitCountSpecific(p, ""+RhinoProto) == 1){
				trUnitSelectByQV("P"+p+"Unit");
				trDamageUnit(1.5*timediff);
			}
			if(xGetBool(dPlayerData, xCharge) == true){
				//Charge effects
				xSetFloat(dPlayerData, xRhinoChargeTime, xGetFloat(dPlayerData, xRhinoChargeTime)-timediff);
			}
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
			if((xGetBool(dPlayerData, xStopDeath) == false) && (trPlayerUnitCountSpecific(p, ""+RhinoProto) == 0) && (trPlayerUnitCountSpecific(p, "Prisoner") == 0) && (trPlayerUnitCountSpecific(p, ""+RhinoDrinkProto) == 0) && (xGetBool(dPlayerData, xPlayerActive) == true) && (xGetBool(dPlayerData, xPlayerDead) == false) && (InMinigame == false)){
				//PLAYER DEAD
				PlayersDead = PlayersDead+1;
				xSetBool(dPlayerData, xPlayerDead, true);
				PlayerColouredChat(p, trStringQuestVarGet("p"+p+"name") + " is dead!");
			}
			if(xGetInt(dPlayerData, xHPRegen) > 0){
				if(trTime() > xGetInt(dPlayerData, xHPRegenNext)){
					trUnitSelectByQV("P"+p+"Unit");
					trDamageUnit(-1*xGetInt(dPlayerData, xHPRegen));
					xSetInt(dPlayerData, xHPRegenNext, trTime()+xGetInt(dPlayerData, xHPRegenTime));
				}
			}
			if(trCurrentPlayer() == p){
				trCounterAbort("stamina"+p);
				trCounterAddTime("stamina"+p, -100, -200, "<color={PlayerColor("+p+")}>Stamina: " + 1*xGetFloat(dPlayerData, xRhinoChargeTime), -1);
			}
		}
		if((PlayersActive == PlayersReadyToLeave+PlayersDead) && (PlayersDead != PlayersActive)){
			xsEnableRule("RhinoExit");
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
				if(trCountUnitsInArea(""+n,pl,""+RhinoProto, 5) > 0){
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
					trQuestVarSetFromRand("temp", 1, 2);
					trQuestVarSetFromRand("temp2", 1, 3);
					if(1*trQuestVarGet("temp") == 1){
						if(1*trQuestVarGet("temp2") == 1){
							PlayerChoice(pl, "Choose your reward:", "+2 hp", 12, "+1.5 charge speed", 14, 10000);
						}
						if(1*trQuestVarGet("temp2") == 2){
							PlayerChoice(pl, "Choose your reward:", "+2 hp", 12, "+2 max stamina", 15, 10000);
						}
						if(1*trQuestVarGet("temp2") == 3){
							PlayerChoice(pl, "Choose your reward:", "+2 hp", 12, "-1s drink time", 16, 10000);
						}
					}
					if(1*trQuestVarGet("temp") == 2){
						if(1*trQuestVarGet("temp2") == 1){
							PlayerChoice(pl, "Choose your reward:", "+0.5 base speed", 13, "+1.5 charge speed", 14, 10000);
						}
						if(1*trQuestVarGet("temp2") == 2){
							PlayerChoice(pl, "Choose your reward:", "+0.5 base speed", 13, "+2 max stamina", 15, 10000);
						}
						if(1*trQuestVarGet("temp2") == 3){
							PlayerChoice(pl, "Choose your reward:", "+0.5 base speed", 13, "-1s drink time", 16, 10000);
						}
					}
					
					
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
	int superpoacher = 0;
	int target = 0;
	int temp = 0;
	vector dest = vector(0,0,0);
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

rule RhinoEndZoneSee
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
			xsDisableSelf();
		}
	}
}

rule RhinoLeave
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
			trMutateSelected(kbGetProtoUnitID(""+RhinoProto));
			PlayerColouredChatToSelf(p, "You have left the extraction zone");
			STOP = 1;
		}
	}
	if((xGetBool(dPlayerData, xReadyToLeave) == false) && (STOP == 0)){
		if((trGetTerrainType(1*xsVectorGetX(tempV)/2,1*xsVectorGetZ(tempV)/2) == getTerrainType(LeaveTerrain)) && (trGetTerrainSubType(1*xsVectorGetX(tempV)/2,1*xsVectorGetZ(tempV)/2) == getTerrainSubType(LeaveTerrain))){
			xSetBool(dPlayerData, xReadyToLeave, true);
			xSetBool(dPlayerData, xStopDeath, true);
			PlayersReadyToLeave = PlayersReadyToLeave+1;
			trUnitSelectByQV("P"+p+"Unit");
			trMutateSelected(kbGetProtoUnitID("Prisoner"));
			PlayerColouredChat(p, trStringQuestVarGet("p"+p+"name") + " is ready to leave");
			if(trQuestVarGet("P"+p+"LeaveMsg") == 0){
				trQuestVarSet("P"+p+"LeaveMsg", 1);
				ColouredChatToPlayer(p, "1,1,0", "You cannot charge or drink in the extraction zone.");
				ColouredChatToPlayer(p, "1,1,0", "You also cannot die or be attacked.");
			}
		}
	}
}

rule RhinoExit
inactive
highFrequency
{
	trCounterAbort("poachtimer");
	xsDisableRule("Charge");
	xsDisableRule("RhinoPartTwo");
	xsDisableRule("RhinoPoacherSpawnLoop");
	xsDisableRule("RhinoActLoops");
	xsDisableRule("RhinoAllDead");
	xsDisableRule("RhinoPoacherMovement");
	xsDisableRule("RhinoEndZoneSee");
	xsDisableRule("RhinoLeave");
	xsDisableRule("RhinoTutorialLoops");
	xsDisableRule("RhinoMinigameDetect");
	xsDisableRule("MGGORhino");
	for(p=1 ; < cNumberNonGaiaPlayers){
		trUnitSelectByQV("P"+p+"Unit");
		trUnitChangeProtoUnit("Ragnorok SFX");
		trUnitSelectByQV("P"+p+"Unit");
		trUnitDestroy();
		trUnitSelectClear();
		trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
		trUnitChangeProtoUnit("Hero Death");
		trCounterAbort("stamina"+p);
	}
	trClearCounterDisplay();
	xsEnableRule("ScoreScreenStart");
	xsDisableSelf();
}

rule RhinoMinigameDetect
highFrequency
inactive
{
	xsSetContextPlayer(0);
	vector pos = vector(0,0,0);
	vector minigame = kbGetBlockPosition(""+1*trQuestVarGet("MinigameStartID"));
	for(p=1 ; < cNumberNonGaiaPlayers){
		pos = kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit"));
		if(distanceBetweenVectors(minigame, pos, true) < 10){
			trUnitSelectByQV("MinigameStartSFX");
			trUnitChangeProtoUnit("Olympus Temple SFX");
			trUnitSelectByQV("MinigameStartID");
			trUnitChangeProtoUnit("Forest Fire SFX");
			PaintAtlantisArea(xsVectorGetX(StageVector)-2,xsVectorGetZ(StageVector)-2,xsVectorGetX(StageVector)+2,xsVectorGetZ(StageVector)+2,0,53);
			refreshPassability();
			trMessageSetText("Minigame found! Remain in the white square if you wish to play.", 10000);
			trCounterAddTime("CDMG", 12, 0, "<color={PlayerColor("+p+")}>Minigame Starts", 34);
			MinigameFound = true;
			for(x=1 ; < cNumberNonGaiaPlayers){
				if(x != p){
					PlayerChoice(x, "Participate in minigame?", "Yes", 4, "No", 0, 11900);
				}
			}
			for(b = 0; <xGetDatabaseCount(dPoachers)){
				xDatabaseNext(dPoachers);
				xUnitSelect(dPoachers, xUnitID);
				trUnitChangeProtoUnit("Cinematic Block");
			}
			xsDisableSelf();
		}
	}
}

void RhinoMinigameGo(int temp = 0){
	xsEnableRule("MGGORhino");
}

rule MGGORhino
inactive
highFrequency
{
	InMinigame = true;
	int temp = trGetNextUnitScenarioNameNumber();
	trPaintTerrain(xsVectorGetX(StageVector)-2,xsVectorGetZ(StageVector)-2,xsVectorGetX(StageVector)+2,xsVectorGetZ(StageVector)+2,0,73);
	refreshPassability();
	//trDelayedRuleActivation("DeerMinigameEnd");
	trMessageSetText("Rules.", 8000);
	CreateMinigameFlag(2*xsVectorGetX(StageVector)+2,2*xsVectorGetZ(StageVector)+2);
	for(p=1 ; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		trVectorQuestVarSet("P"+p+"PosMG", kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
		trVectorQuestVarSet("P"+p+"PosMG", trVectorQuestVarGet("P"+p+"PosMG")/2);
		if((trVectorQuestVarGetX("P"+p+"PosMG") > xsVectorGetX(StageVector)-2) && (trVectorQuestVarGetX("P"+p+"PosMG") < xsVectorGetX(StageVector)+2) && (trVectorQuestVarGetZ("P"+p+"PosMG") > xsVectorGetZ(StageVector)-2) && (trVectorQuestVarGetZ("P"+p+"PosMG") < xsVectorGetZ(StageVector)+2)){
			xSetBool(dPlayerData, xStopDeath, true);
			PlayerColouredChat(p, trStringQuestVarGet("p"+p+"name") + " is playing");
			PlayersMinigaming = PlayersMinigaming+1;
		}
	}
	if(PlayersMinigaming == 0){
		//end MG
		trUnitSelectByQV("MinigameStartSFX");
		trUnitDestroy();
		trUnitSelectByQV("MinigameStartID");
		trUnitDestroy();
		trMessageSetText("Nobody was on the white tiles. Minigame cancelled.", 5000);
		InMinigame = false;
	}
	xsDisableSelf();
}
