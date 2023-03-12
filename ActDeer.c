rule BuildDeerArea
highFrequency
inactive
{
	if (trTime() > cActivationTime + 1) {
		//createForestArea();
		createDeepForestArea();
		xsDisableSelf();
		//replaceTerrainAboveHeightMax("ForestFloorPine", "GrassB", 0.0);
		replaceTerrainAboveHeightMax("GaiaCreepA", "GrassB", 0.0);
		replaceTerrainAboveHeightMax("CoralA", "GrassB", 0.0);
		trLetterBox(false);
		trUIFadeToColor(0,0,0,100,800,false);
		trCameraCut(vector(-36.525265,123.743729,-36.525265), vector(0.500000,-0.707107,0.500000), vector(0.500000,0.707107,0.500000), vector(0.707107,0.000000,-0.707107));
		uiZoomToProto(""+GazelleProto);
		uiLookAtProto(""+GazelleProto);
		trDelayedRuleActivation("ResetBlackmap");
		trDelayedRuleActivation("DeerActLoops");
		trDelayedRuleActivation("DeerMinigameDetect");
		trDelayedRuleActivation("DeerLeave");
		trDelayedRuleActivation("TEST");
		trDelayedRuleActivation("DeerAllDead");
		trDelayedRuleActivation("PoacherTimer");
		trDelayedRuleActivation("DeerEndZoneSee");
		xsEnableRule("DeerPoacherMovement");
		BerryTarget = 8+PlayersActive;
		if(BerryTarget >= xGetDatabaseCount(dBerryBush)){
			BerryTarget = xGetDatabaseCount(dBerryBush)-12+PlayersActive;
		}
		BerryTotal = xGetDatabaseCount(dBerryBush);
		trSetCounterDisplay("<color={PlayerColor(2)}>Berries Eaten: 0 / " + BerryTarget);
		ColouredIconChat("1,0.5,0", ActIcon(Stage), "<u>" + ActName(Stage) + "</u>");
		ColouredIconChat("0.0,0.8,0.2", "icons\world berry bush icon 64", "Eat at least the required number of berries");
		trChatSend(0, "In each act you need to find and move to the extraction zone.");
		trChatSend(0, "It is a ring of ice terrain.");
		trChatSend(0, "When all players are dead or in the zone, the act ends.");
		trChatSend(0, "Make sure to explore, as higher act scores help you out later.");
		playSound("\cinematics\19_out\music 2.mp3");
		xsEnableRule("PlayMusicDelay");
	}
}

rule PlayMusic
highFrequency
inactive
{
	trMusicPlay();
	trPlayNextMusicTrack();
	xsDisableSelf();
}

rule PlayMusicDelay
highFrequency
inactive
{
	if (trTime() > cActivationTime + 29) {
		trMusicPlay();
		trPlayNextMusicTrack();
		xsDisableSelf();
	}
}

void SpawnDeerPoachers(int unused = 0){
	unused = xsGetContextPlayer();
	xsSetContextPlayer(0);
	if(Stage == 1){
		trOverlayText("Poachers Spawned!", 5.0,-1,-1,600);
		SpawnDeerPoacher(xsMax(PlayersActive,2));
		playSound("\cinematics\04_in\armyarrive.wav");
	}
	xsSetContextPlayer(unused);
}

rule PoacherTimer
highFrequency
inactive
{
	if (trTime() > cActivationTime + 64) {
		if(InMinigame == false){
			if(Stage == 1){
				trCounterAddTime("poachtimer", 122, 0, "<color={PlayerColor(2)}>Poachers spawn", 32);
				trQuestVarSet("NextPoacherSpawn", trTime()+200);
				xsEnableRule("PoacherSpawnLoop");
				ColouredIconChat("1,0,0", "icons\archer n throwing axeman icon 64", "<u>Watch out for poachers!</u>");
				ColouredChat("0.9,0.3,0.3", "They can hide amongst the trees or actively scout for you.");
				ColouredChat("0.9,0.3,0.3", "You will be attacked on sight.");
				ColouredChat("0.9,0.3,0.3", "But can run or jump over the attacks.");
			}
			xsDisableSelf();
			xsEnableRule("ChestTimer");
		}
	}
}

rule ChestTimer
highFrequency
inactive
{
	if (trTime() > cActivationTime + 54) {
		if(InMinigame == false){
			int x = xGetDatabaseCount(dChests);
			if((Stage == 1) && (x > 0)){
				ColouredIconChat("0,1,0", "icons\special e osiris box icon 64", "<u>Look out for chests!</u>");
				ColouredChat("0.3,0.9,0.3", "There are " + x + " unopened chests still to find.");
				ColouredChat("0.3,0.9,0.3", "Move near a chest to open it.");
				ColouredChat("0.3,0.9,0.3", "A stat bonus is granted for the player who does this.");
			}
			xsDisableSelf();
		}
	}
}

rule PoacherSpawnLoop
highFrequency
inactive
{
	if (trTime() > 1*trQuestVarGet("NextPoacherSpawn")) {
		if(Stage == 1){
			SpawnDeerPoacher(2);
			trQuestVarModify("NextPoacherSpawn", "+", 50);
		}
	}
	
}

rule TEST
highFrequency
inactive
{
	if (trTime() > cActivationTime + 3) {
		if(QuickStart != 0){
			trTechGodPower(1, "Vision", 111);
			trTechGodPower(1, "Sandstorm", 111);
			modifyProtounitAbsolute(""+GazelleProto, 1, 1, 20);
		}
		xsDisableSelf();
		trDelayedRuleActivation("ResetBlackmap");
	}
}

void ProcessBerries(int count = 1) {
	int temp = 0;
	vector pos = vector(0,0,0);
	vector posberry = vector(0,0,0);
	for (x=xsMin(count, xGetDatabaseCount(dBerryBush)); > 0) {
		xDatabaseNext(dBerryBush);
		xUnitSelect(dBerryBush, xUnitID);
		trUnitHighlight(10, false);
		posberry = xGetVector(dBerryBush, xUnitPos);
		for(p=1 ; < cNumberNonGaiaPlayers){
			pos = trVectorQuestVarGet("P"+p+"Pos");
			if(distanceBetweenVectors(posberry, pos, true) < 10){
				trUnitSelectClear();
				xUnitSelect(dBerryBush, xUnitID);
				trUnitChangeProtoUnit("Curse SFX");
				trQuestVarModify("BerriesEaten", "+", 1);
				temp = 1*trQuestVarGet("BerriesEaten");
				trClearCounterDisplay();
				if(temp < BerryTarget){
					trSetCounterDisplay("<color={PlayerColor(2)}>Berries Eaten: " + temp + " / " + BerryTarget);
				}
				else{
					trSetCounterDisplay("<color={PlayerColor(3)}>Berries Eaten: " + temp);
				}
				if(trCurrentPlayer() == p){
					playSoundCustom("colossuseat.wav", "\Yeebaagooon\Zoo Quest\Eat.mp3");
				}
				if(temp == BerryTarget){
					playSoundCustom("cinematics\10_in\clearedcity.wav", "\Yeebaagooon\Zoo Quest\Skillpoint.mp3");
					trMessageSetText("If all players make it to the extraction zone alive you will pass the act.", 10000);
				}
				//playSound("\Yeebaagooon\Zoo Quest\Eat.mp3");
				xFreeDatabaseBlock(dBerryBush);
				if(xGetDatabaseCount(dBerryBush) == 0){
					playSoundCustom("cinematics\10_in\clearedcity.wav", "\Yeebaagooon\Zoo Quest\Skillpoint.mp3");
					trOverlayText("All berries eaten!", 5.0,-1,-1,600);
				}
			}
		}
	}
}

void ProcessLogs(int count = 1) {
	int temp = 0;
	vector pos = vector(0,0,0);
	vector poslog = vector(0,0,0);
	for (x=xsMin(count, xGetDatabaseCount(dLogs)); > 0) {
		xDatabaseNext(dLogs);
		poslog = xGetVector(dLogs, xUnitPos);
		for(p=1 ; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetInt(dPlayerData, xLogJumps) == 0){
				pos = trVectorQuestVarGet("P"+p+"Pos");
				if(distanceBetweenVectors(poslog, pos, true) < 2){
					xSetInt(dPlayerData, xLogJumps, 1);
					ColouredIconChatToPlayer(p, "0,1,0.2", "world a rotting log shadow", "Perfect log jump!");
					if(trCurrentPlayer() == p){
						playSound("\cinematics\14_in\chimes.mp3");
					}
					break;
				}
			}
		}
	}
}

rule DeerActLoops
highFrequency
inactive
{
	if(Stage == 1){
		timediff = 0.001 * (trTimeMS() - timelast); // calculate timediff
		timelast = trTimeMS();
		int temp = 0;
		int TimerTile = 0;
		ProcessBerries(5);
		ProcessLogs(7);
		if(xGetDatabaseCount(dMissiles) > 0){
			DoMissile();
		}
		for(p=1 ; < cNumberNonGaiaPlayers){
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
			if((xGetBool(dPlayerData, xStopDeath) == false) && (trPlayerUnitCountSpecific(p, ""+GazelleProto) == 0) && (trPlayerUnitCountSpecific(p, "Hero Greek Bellerophon") == 0) && (trPlayerUnitCountSpecific(p, "Prisoner") == 0) && (xGetBool(dPlayerData, xPlayerActive) == true) && (xGetBool(dPlayerData, xPlayerDead) == false) && (InMinigame == false)){
				//PLAYER DEAD
				PlayersDead = PlayersDead+1;
				xSetBool(dPlayerData, xPlayerDead, true);
				PlayerColouredChat(p, trStringQuestVarGet("p"+p+"name") + " is dead!");
				PlayerColouredChatToSelf(p, "You'll be able to join the next act if your team pass this one.");
				trPlayerKillAllGodPowers(p);
				xSetVector(dPlayerData, xDeathVector, kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
				trTechGodPower(1, "Rain", 1);
				if(iModulo(2, trTime()) == 0){
					playSound("\dialog\fr\skul062.mp3");
				}
				else{
					playSound("\xpack\xdialog\fr\xkri075.mp3");
				}
			}
			xSetVector(dPlayerData, xConstantPos, kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
			if(xGetInt(dPlayerData, xHPRegen) > 0){
				if(trTime() > xGetInt(dPlayerData, xHPRegenNext)){
					trUnitSelectByQV("P"+p+"Unit");
					trDamageUnit(-1*xGetInt(dPlayerData, xHPRegen));
					xSetInt(dPlayerData, xHPRegenNext, trTime()+xGetInt(dPlayerData, xHPRegenTime));
				}
			}
			if(InMinigame == true){
				//MINIGAME
				for(b = 0; <xGetDatabaseCount(dPoachers)){
					xDatabaseNext(dPoachers);
					xUnitSelect(dPoachers, xUnitID);
					trUnitChangeProtoUnit("Cinematic Block");
				}
				if(xGetBool(dPlayerData, xStopDeath) == true){
					if(trPlayerUnitCountSpecific(p, ""+GazelleProto) == 1){
						trVectorQuestVarSet("P"+p+"PosMG", kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
						if((trGetTerrainType(trVectorQuestVarGetX("P"+p+"PosMG")/2,trVectorQuestVarGetZ("P"+p+"PosMG")/2) == 2) && (trGetTerrainSubType(trVectorQuestVarGetX("P"+p+"PosMG")/2,trVectorQuestVarGetZ("P"+p+"PosMG")/2) == 10)){
							trUnitSelectByQV("P"+p+"Unit");
							trUnitChangeProtoUnit("Ragnorok SFX");
							trUnitSelectByQV("P"+p+"Unit");
							trUnitDestroy();
							trUnitSelectClear();
							trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
							trUnitChangeProtoUnit("Hero Death");
							UnitCreate(0, "Tartarian Gate Flame", trVectorQuestVarGetX("P"+p+"PosMG"),trVectorQuestVarGetZ("P"+p+"PosMG"), 90);
							if(xGetInt(dPlayerData, xTeleportDue) == 0){
								xSetVector(dPlayerData, xVectorHold, trVectorQuestVarGet("P"+p+"PosMG"));
							}
							PlayersMinigaming = PlayersMinigaming-1;
							if(trCurrentPlayer() == p){
								playSound("xlose.wav");
								trOverlayText("Minigame Failed!", 3.0,-1,-1,600);
							}
						}
						trVectorQuestVarSet("P"+p+"PosMG", trVectorQuestVarGet("P"+p+"PosMG")/2);
						if((trVectorQuestVarGetZ("P"+p+"PosMG") < xsVectorGetZ(StageVector)+1) || (trVectorQuestVarGetZ("P"+p+"PosMG") > xsVectorGetZ(StageVector)+11) || (trVectorQuestVarGetX("P"+p+"PosMG") < xsVectorGetX(StageVector))){
							xSetBool(dPlayerData, xStopDeath, false);
							PlayersMinigaming = PlayersMinigaming-1;
							if(trCurrentPlayer() == p){
								playSound("xlose.wav");
								trMessageSetText("You have gone out of bounds and been returned to normal play.", 5000);
							}
						}
						if(trVectorQuestVarGetX("P"+p+"PosMG") > xsVectorGetX(StageVector)+26){
							xSetBool(dPlayerData, xStopDeath, false);
							PlayersMinigaming = PlayersMinigaming-1;
							MinigameWins = MinigameWins+1;
							if(trCurrentPlayer() == p){
								playSound("xwin.wav");
								playSound("\cinematics\15_in\gong.wav");
								trMessageSetText("You have won the minigame!", 4000);
							}
							trQuestVarSetFromRand("temp",1,2,true);
							if(1*trQuestVarGet("temp") == 1){
								PlayerChoice(p, "Choose your reward:", "+1 speed", 8, "+2 hp", 10, 10000);
							}
							else{
								PlayerChoice(p, "Choose your reward:", "+6 LOS", 9, "+1hp regen every 30s", 11, 10000);
							}
						}
					}
				}
			}
		}
		if(InMinigame == true){
			TimerTile = trTimeMS();
			if(TimerTile > GlobalTimerMS){
				GlobalTimerMS = trTimeMS()+250;
				trQuestVarModify("LavaTile", "+", 1);
				trQuestVarModify("LavaTile2", "+", 1);
				trQuestVarModify("LavaTile3", "+", 1);
				if(1*trQuestVarGet("LavaTile") >= xGetDatabaseCount(dTiles1)){
					trQuestVarSet("LavaTile", 0);
				}
				if(1*trQuestVarGet("LavaTile2") >= xGetDatabaseCount(dTiles2)){
					trQuestVarSet("LavaTile2", 0);
				}
				if(1*trQuestVarGet("LavaTile3") >= xGetDatabaseCount(dTiles2)){
					trQuestVarSet("LavaTile3", 0);
				}
				for(a=0 ; < xGetDatabaseCount(dTiles1)){
					xDatabaseNext(dTiles1);
					trPaintTerrain(xGetInt(dTiles1, xTileX),xGetInt(dTiles1, xTileZ),xGetInt(dTiles1, xTileX),xGetInt(dTiles1, xTileZ),xGetInt(dTiles1, xTileType),xGetInt(dTiles1, xTileSubType));
					if(a == 1*trQuestVarGet("LavaTile")){
						trPaintTerrain(xGetInt(dTiles1, xTileX),xGetInt(dTiles1, xTileZ),xGetInt(dTiles1, xTileX),xGetInt(dTiles1, xTileZ),2,10);
					}
				}
				for(b=0 ; < xGetDatabaseCount(dTiles2)){
					xDatabaseNext(dTiles2);
					trPaintTerrain(xGetInt(dTiles2, xTileX),xGetInt(dTiles2, xTileZ),xGetInt(dTiles2, xTileX),xGetInt(dTiles2, xTileZ),xGetInt(dTiles2, xTileType),xGetInt(dTiles2, xTileSubType));
					if(b == 1*trQuestVarGet("LavaTile2")){
						trPaintTerrain(xGetInt(dTiles2, xTileX),xGetInt(dTiles2, xTileZ),xGetInt(dTiles2, xTileX),xGetInt(dTiles2, xTileZ),2,10);
					}
					if(b == 1*trQuestVarGet("LavaTile3")){
						trPaintTerrain(xGetInt(dTiles2, xTileX),xGetInt(dTiles2, xTileZ),xGetInt(dTiles2, xTileX),xGetInt(dTiles2, xTileZ),2,10);
					}
				}
			}
		}
		//Check terrain for extraction is done in seperate trigger
		if((PlayersActive == PlayersReadyToLeave+PlayersDead) && (PlayersDead != PlayersActive)){
			xsEnableRule("DeerExit");
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
						PlayerChoice(pl, "Choose your reward:", "+1 hp", 5, "+4 LOS", 6, 10000);
					}
					else{
						PlayerChoice(pl, "Choose your reward:", "+1 hp", 5, "+0.5 Speed", 7, 10000);
					}
				}
			}
			
		}
	}
}

rule DeerMinigameDetect
highFrequency
inactive
{
	//xsSetContextPlayer(0);
	vector pos = vector(0,0,0);
	vector minigame = kbGetBlockPosition(""+1*trQuestVarGet("MinigameStartID"));
	for(p=1 ; < cNumberNonGaiaPlayers){
		pos = trVectorQuestVarGet("P"+p+"Pos");
		if(distanceBetweenVectors(minigame, pos, true) < 10){
			trUnitSelectByQV("MinigameStartSFX");
			trUnitChangeProtoUnit("Olympus Temple SFX");
			trUnitSelectByQV("MinigameStartID");
			trUnitChangeProtoUnit("Forest Fire SFX");
			PaintAtlantisArea(xsVectorGetX(StageVector)+1,xsVectorGetZ(StageVector)+3,xsVectorGetX(StageVector)+5,xsVectorGetZ(StageVector)+7,0,53);
			refreshPassability();
			trMessageSetText("Minigame found! Remain in the white square if you wish to play.", 10000);
			trCounterAddTime("CDMG", 12, 0, "<color={PlayerColor("+p+")}>Minigame Starts", 27);
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
			xsDisableSelf();
		}
	}
}

void DeerMinigameGo(int eventfireID = 0){
	xsEnableRule("MGGODeer");
}

rule MGGODeer
highFrequency
inactive
{
	InMinigame = true;
	int temp = trGetNextUnitScenarioNameNumber();
	trPaintTerrain(xsVectorGetX(StageVector)+6,xsVectorGetZ(StageVector)+3,xsVectorGetX(StageVector)+25,xsVectorGetZ(StageVector)+7,0,73);
	trPaintTerrain(xsVectorGetX(StageVector),xsVectorGetZ(StageVector)+3,xsVectorGetX(StageVector),xsVectorGetZ(StageVector)+7,2,13);
	PaintAtlantisArea(xsVectorGetX(StageVector)+26,xsVectorGetZ(StageVector)+4,xsVectorGetX(StageVector)+28,xsVectorGetZ(StageVector)+6,0,71);
	refreshPassability();
	//trPaintTerrain(xsVectorGetX(StageVector)+6,xsVectorGetZ(StageVector)+3,xsVectorGetX(StageVector)+25,xsVectorGetZ(StageVector)+7,0,73);
	trPaintTerrain(xsVectorGetX(StageVector)+6,xsVectorGetZ(StageVector)+7,xsVectorGetX(StageVector)+9,xsVectorGetZ(StageVector)+7,2,10);
	trPaintTerrain(xsVectorGetX(StageVector)+6,xsVectorGetZ(StageVector)+3,xsVectorGetX(StageVector)+6,xsVectorGetZ(StageVector)+5,2,10);
	trPaintTerrain(xsVectorGetX(StageVector)+8,xsVectorGetZ(StageVector)+5,xsVectorGetX(StageVector)+9,xsVectorGetZ(StageVector)+7,2,10);
	trPaintTerrain(xsVectorGetX(StageVector)+6,xsVectorGetZ(StageVector)+3,xsVectorGetX(StageVector)+9,xsVectorGetZ(StageVector)+3,2,10);
	trPaintTerrain(xsVectorGetX(StageVector)+10,xsVectorGetZ(StageVector)+3,xsVectorGetX(StageVector)+12,xsVectorGetZ(StageVector)+7,2,10);
	trPaintTerrain(xsVectorGetX(StageVector)+25,xsVectorGetZ(StageVector)+3,xsVectorGetX(StageVector)+25,xsVectorGetZ(StageVector)+7,2,10);
	trDelayedRuleActivation("DeerMinigameEnd");
	trMessageSetText("The floor is lava! Reach the end safely. If you jump outside the arena you are disqualified.", 8000);
	AddTileMGDeer(xsVectorGetX(StageVector)+17,xsVectorGetZ(StageVector)+3);
	AddTileMGDeer(xsVectorGetX(StageVector)+17,xsVectorGetZ(StageVector)+4);
	AddTileMGDeer(xsVectorGetX(StageVector)+17,xsVectorGetZ(StageVector)+5);
	AddTileMGDeer(xsVectorGetX(StageVector)+17,xsVectorGetZ(StageVector)+6);
	AddTileMGDeer(xsVectorGetX(StageVector)+17,xsVectorGetZ(StageVector)+7);
	AddTileMGDeer(xsVectorGetX(StageVector)+18,xsVectorGetZ(StageVector)+7);
	AddTileMGDeer(xsVectorGetX(StageVector)+19,xsVectorGetZ(StageVector)+7);
	AddTileMGDeer(xsVectorGetX(StageVector)+19,xsVectorGetZ(StageVector)+6);
	AddTileMGDeer(xsVectorGetX(StageVector)+19,xsVectorGetZ(StageVector)+5);
	AddTileMGDeer(xsVectorGetX(StageVector)+19,xsVectorGetZ(StageVector)+4);
	AddTileMGDeer(xsVectorGetX(StageVector)+19,xsVectorGetZ(StageVector)+3);
	AddTileMGDeer(xsVectorGetX(StageVector)+18,xsVectorGetZ(StageVector)+3);
	trQuestVarSet("LavaTile", 1);
	AddTileMGDeer2(xsVectorGetX(StageVector)+21,xsVectorGetZ(StageVector)+3);
	AddTileMGDeer2(xsVectorGetX(StageVector)+21,xsVectorGetZ(StageVector)+4);
	AddTileMGDeer2(xsVectorGetX(StageVector)+21,xsVectorGetZ(StageVector)+5);
	AddTileMGDeer2(xsVectorGetX(StageVector)+21,xsVectorGetZ(StageVector)+6);
	AddTileMGDeer2(xsVectorGetX(StageVector)+21,xsVectorGetZ(StageVector)+7);
	AddTileMGDeer2(xsVectorGetX(StageVector)+22,xsVectorGetZ(StageVector)+7);
	AddTileMGDeer2(xsVectorGetX(StageVector)+23,xsVectorGetZ(StageVector)+7);
	AddTileMGDeer2(xsVectorGetX(StageVector)+24,xsVectorGetZ(StageVector)+7);
	AddTileMGDeer2(xsVectorGetX(StageVector)+24,xsVectorGetZ(StageVector)+6);
	AddTileMGDeer2(xsVectorGetX(StageVector)+24,xsVectorGetZ(StageVector)+5);
	AddTileMGDeer2(xsVectorGetX(StageVector)+24,xsVectorGetZ(StageVector)+4);
	AddTileMGDeer2(xsVectorGetX(StageVector)+24,xsVectorGetZ(StageVector)+3);
	AddTileMGDeer2(xsVectorGetX(StageVector)+23,xsVectorGetZ(StageVector)+3);
	AddTileMGDeer2(xsVectorGetX(StageVector)+22,xsVectorGetZ(StageVector)+3);
	trQuestVarSet("LavaTile2", 1);
	trQuestVarSet("LavaTile3", 8);
	for(z=1 ; < 8){
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(0, "Dwarf", 2*xsVectorGetX(StageVector)+(8*z),2*xsVectorGetZ(StageVector)+12,0);
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeProtoUnit("Revealer");
		xAddDatabaseBlock(dTemp, true);
		xSetInt(dTemp, xUnitID, temp);
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(0, "Dwarf", 2*xsVectorGetX(StageVector)+(8*z),2*xsVectorGetZ(StageVector)+8,0);
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeProtoUnit("Revealer");
		xAddDatabaseBlock(dTemp, true);
		xSetInt(dTemp, xUnitID, temp);
	}
	CreateMinigameFlag(2*xsVectorGetX(StageVector)+55,2*xsVectorGetZ(StageVector)+11);
	for(p=1 ; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		if(xGetBool(dPlayerData, xPlayerActive)){
			trVectorQuestVarSet("P"+p+"PosMG", kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
			trVectorQuestVarSet("P"+p+"PosMG", trVectorQuestVarGet("P"+p+"PosMG")/2);
			if((trVectorQuestVarGetX("P"+p+"PosMG") > xsVectorGetX(StageVector)-2) && (trVectorQuestVarGetX("P"+p+"PosMG") < xsVectorGetX(StageVector)+6) && (trVectorQuestVarGetZ("P"+p+"PosMG") > xsVectorGetZ(StageVector)-4) && (trVectorQuestVarGetZ("P"+p+"PosMG") < xsVectorGetZ(StageVector)+8)){
				xSetBool(dPlayerData, xStopDeath, true);
				PlayerColouredChat(p, trStringQuestVarGet("p"+p+"name") + " is playing");
				PlayersMinigaming = PlayersMinigaming+1;
			}
		}
	}
	if(PlayersMinigaming == 0){
		//end MG
		trUnitSelectByQV("MinigameStartSFX");
		trUnitDestroy();
		trUnitSelectByQV("MinigameStartID");
		trUnitDestroy();
		trMessageSetText("Nobody was on the white tiles. Minigame cancelled.", 5000);
		xsEnableRule("PlayMusic");
		InMinigame = false;
	}
	if(PlayersMinigaming > 0){
		playSoundCustom("\cinematics\31_out\music.mp3", "\Yeebaagooon\Zoo Quest\Minigame1.mp3");
	}
	xsDisableSelf();
}

rule DeerMinigameEnd
inactive
highFrequency
{
	if(PlayersMinigaming == 0){
		vector temp = vector(0,0,0);
		trPaintTerrain(xsVectorGetX(StageVector)-1,xsVectorGetZ(StageVector)-1,xsVectorGetX(StageVector)+31,xsVectorGetZ(StageVector)+11,0,0);
		refreshPassability();
		for(p=1 ; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if((xGetInt(dPlayerData, xTeleportDue) == 1) && (xGetBool(dPlayerData, xPlayerActive) == true)){
				debugLog("Path 1 - P" + p);
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
				debugLog("Path 2 - P" + p);
				if(trPlayerUnitCountSpecific(p, ""+GazelleProto) == 0){
					temp = xGetVector(dPlayerData, xVectorHold);
					trQuestVarSet("P"+p+"IG", trGetNextUnitScenarioNameNumber());
					UnitCreateV(p, "Roc", temp, 0);
					trUnitSelectByQV("P"+p+"Unit");
					trImmediateUnitGarrison(""+1*trQuestVarGet("P"+p+"IG"));
					trUnitSelectByQV("P"+p+"IG");
					trUnitChangeProtoUnit("Cinematic Block");
					CreateGazelle(p, xsVectorGetX(temp), xsVectorGetZ(temp), 0);
				}
			}
			if((trPlayerUnitCountSpecific(p, GazelleProto) == 0) && (xGetBool(dPlayerData, xPlayerDead) == false) && (trPlayerUnitCountSpecific(p, "Hero Greek Bellerophon") == 0)){
				debugLog("Path 3 - P" + p);
				CreateGazelle(p, trVectorQuestVarGetX("P"+p+"PosMG"),trVectorQuestVarGetZ("P"+p+"PosMG"));
			}
		}
		uiZoomToProto(""+GazelleProto);
		uiLookAtProto(""+GazelleProto);
		unitTransform("Tartarian Gate Flame", "Flowers");
		for(c = xGetDatabaseCount(dTemp) ; > 0){
			xDatabaseNext(dTemp);
			xUnitSelect(dTemp, xUnitID);
			trUnitDestroy();
			xFreeDatabaseBlock(dTemp);
		}
		for(b = xGetDatabaseCount(dPoachers); > 0){
			xDatabaseNext(dPoachers);
			xUnitSelect(dPoachers, xUnitID);
			trUnitChangeProtoUnit("Throwing Axeman");
		}
		trUnitSelectByQV("MinigameStartSFX");
		trUnitChangeProtoUnit("Olympus Temple SFX");
		trUnitSelectByQV("MinigameStartID");
		trUnitChangeProtoUnit("Forest Fire SFX");
		xsDisableSelf();
		InMinigame = false;
		trFadeOutAllSounds(3);
		trFadeOutMusic(3);
		xsEnableRule("PlayMusic");
	}
}

rule DeerLeave
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
	tempV = xGetVector(dPlayerData, xConstantPos);
	if(xGetBool(dPlayerData, xReadyToLeave) == true){
		if((trGetTerrainType(1*xsVectorGetX(tempV)/2,1*xsVectorGetZ(tempV)/2) != getTerrainType(LeaveTerrain)) || (trGetTerrainSubType(1*xsVectorGetX(tempV)/2,1*xsVectorGetZ(tempV)/2) != getTerrainSubType(LeaveTerrain))){
			xSetBool(dPlayerData, xReadyToLeave, false);
			xSetBool(dPlayerData, xStopDeath, false);
			PlayersReadyToLeave = PlayersReadyToLeave-1;
			trUnitSelectByQV("P"+p+"Unit");
			trMutateSelected(kbGetProtoUnitID("Hero Greek Jason"));
			PlayerColouredChatToSelf(p, "You have left the extraction zone");
			STOP = 1;
		}
	}
	if((xGetBool(dPlayerData, xReadyToLeave) == false) && (STOP == 0)  && (xGetBool(dPlayerData, xPlayerDead) == false)){
		if((trGetTerrainType(1*xsVectorGetX(tempV)/2,1*xsVectorGetZ(tempV)/2) == getTerrainType(LeaveTerrain)) && (trGetTerrainSubType(1*xsVectorGetX(tempV)/2,1*xsVectorGetZ(tempV)/2) == getTerrainSubType(LeaveTerrain))){
			xSetBool(dPlayerData, xReadyToLeave, true);
			xSetBool(dPlayerData, xStopDeath, true);
			PlayersReadyToLeave = PlayersReadyToLeave+1;
			trUnitSelectByQV("P"+p+"Unit");
			trMutateSelected(kbGetProtoUnitID("Prisoner"));
			PlayerColouredChat(p, trStringQuestVarGet("p"+p+"name") + " is ready to leave");
			if(trQuestVarGet("P"+p+"LeaveMsg") == 0){
				trQuestVarSet("P"+p+"LeaveMsg", 1);
				ColouredChatToPlayer(p, "1,1,0", "You cannot jump in the extraction zone.");
				ColouredChatToPlayer(p, "1,1,0", "You also cannot die or be attacked.");
			}
		}
	}
}

/*rule DeerAllDead
inactive
minInterval 5
{
	if((Stage == 1) && (PlayersDead == PlayersActive)){
		trShowWinLose("All players are dead", "xlose.wav");
		for(p=1 ; < cNumberNonGaiaPlayers){
			trSetPlayerDefeated(p);
		}
		xsDisableSelf();
		trEndGame();
	}
}*/

rule DeerPoacherMovement
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

rule DeerEndZoneSee
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

rule DeerExit
inactive
highFrequency
{
	trCounterAbort("poachtimer");
	xsDisableRule("DeerActLoops");
	xsDisableRule("DeerMinigameDetect");
	xsDisableRule("DeerMinigameEnd");
	xsDisableRule("DeerLeave");
	xsDisableRule("DeerAllDead");
	xsDisableRule("DeerPoacherMovement");
	xsDisableRule("PoacherSpawnLoop");
	xsDisableRule("PoacherTimer");
	xsDisableRule("DeerEndZoneSee");
	xsDisableRule("ChestTimer");
	xsDisableRule("PlayMusic");
	xsDisableRule("PlayMusicDelay");
	xsDisableRule("MGGODeer");
	for(p=1 ; < cNumberNonGaiaPlayers){
		trUnitSelectByQV("P"+p+"Unit");
		trUnitChangeProtoUnit("Ragnorok SFX");
		trUnitSelectByQV("P"+p+"Unit");
		trUnitDestroy();
		trUnitSelectClear();
		trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
		trUnitChangeProtoUnit("Hero Death");
	}
	trClearCounterDisplay();
	xsEnableRule("ScoreScreenStart");
	xsDisableSelf();
}
