// [DEER OBJECTIVES]
/*
Compulsory:
-Eat target berry (Target)
-Jump over log (1/cNum)
-Reach extraction point alive (cNum)

Extra:
-Complete MG (cNum)
100 = All berries, all jumps, all alive
Required = 40
*/

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
		uiZoomToProto(""+GazelleProto);
		uiLookAtProto(""+GazelleProto);
		trDelayedRuleActivation("ResetBlackmap");
		trDelayedRuleActivation("DeerActLoops");
		trDelayedRuleActivation("DeerMinigameDetect");
		trDelayedRuleActivation("Testing");
		trDelayedRuleActivation("DeerLeave");
		BerryTarget = 8+PlayersActive;
		if(BerryTarget >= xGetDatabaseCount(dBerryBush)){
			BerryTarget = xGetDatabaseCount(dBerryBush)-12+PlayersActive;
		}
	}
}

rule Testing
highFrequency
inactive
{
	if (trTime() > cActivationTime + 1) {
		xsDisableSelf();
		xsSetContextPlayer(0);
		PlayerChoice(1, "Participate in minigame?", "Yes", 4, "No", 0);
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
					playSoundCustom("farming3.wav", "\Yeebaagooon\Zoo Quest\Eat.mp3");
				}
				if(temp == BerryTarget){
					playSoundCustom("cinematics\10_in\clearedcity.wav", "\Yeebaagooon\Zoo Quest\Skillpoint.mp3");
				}
				//playSound("\Yeebaagooon\Zoo Quest\Eat.mp3");
				xFreeDatabaseBlock(dBerryBush);
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
			pos = trVectorQuestVarGet("P"+p+"Pos");
			if(distanceBetweenVectors(poslog, pos, true) < 2){
				trChatSend(0, "Log jump!");
				break;
			}
		}
	}
}

rule DeerActLoops
highFrequency
inactive
{
	int temp = 0;
	int TimerTile = 0;
	ProcessBerries(5);
	ProcessLogs(7);
	for(p=1 ; < cNumberNonGaiaPlayers){
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
		xSetVector(dPlayerData, xConstantPos, kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
		if(InMinigame == true){
			//MINIGAME
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
						xSetVector(dPlayerData, xVectorHold, trVectorQuestVarGet("P"+p+"PosMG"));
						PlayersMinigaming = PlayersMinigaming-1;
						if(trCurrentPlayer() == p){
							playSound("xlose.wav");
							trOverlayText("Fail!", 3.0,-1,-1,600);
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
							trMessageSetText("You have won!", 4000);
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
	//Check terrain for extraction
	if(PlayersReadyToLeave == PlayersActive){
		xsEnableRule("DeerExit");
	}
}

rule DeerMinigameDetect
highFrequency
inactive
{
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
			for(x=1 ; < cNumberNonGaiaPlayers){
				if(x != p){
					PlayerChoice(x, "Participate in minigame?", "Yes", 4, "No", 0);
				}
			}
			xsDisableSelf();
		}
	}
}

void DeerMinigameGo(int temp = 0){
	xsSetContextPlayer(0);
	InMinigame = true;
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
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(0, "Dwarf", 2*xsVectorGetX(StageVector)+(8*z),2*xsVectorGetZ(StageVector)+8,0);
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeProtoUnit("Revealer");
	}
	for(p=1 ; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		trVectorQuestVarSet("P"+p+"PosMG", kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
		trVectorQuestVarSet("P"+p+"PosMG", trVectorQuestVarGet("P"+p+"PosMG")/2);
		if((trVectorQuestVarGetX("P"+p+"PosMG") > xsVectorGetX(StageVector)-2) && (trVectorQuestVarGetX("P"+p+"PosMG") < xsVectorGetX(StageVector)+6) && (trVectorQuestVarGetZ("P"+p+"PosMG") > xsVectorGetZ(StageVector)-4) && (trVectorQuestVarGetZ("P"+p+"PosMG") < xsVectorGetZ(StageVector)+8)){
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
		trDelayedRuleActivation("DeerMinigameEnd");
		trMessageSetText("Nobody was on the white tiles. Minigame cancelled.", 5000);
		InMinigame = false;
	}
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
			if(xGetInt(dPlayerData, xTeleportDue) == 1){
				temp = xGetVector(dPlayerData, xVectorHold);
				trUnitSelectByQV("P"+p+"Unit");
				trUnitChangeProtoUnit("Ragnorok SFX");
				trUnitSelectByQV("P"+p+"Unit");
				trUnitDestroy();
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
				trUnitChangeProtoUnit("Hero Death");
				CreateGazelle(p, xsVectorGetX(temp), xsVectorGetZ(temp), 0);
				xSetBool(dPlayerData, xStopDeath, false);
				xSetInt(dPlayerData, xTeleportDue, 0);
			}
			else if(xGetInt(dPlayerData, xTeleportDue) == 0){
				if(trPlayerUnitCountSpecific(p, ""+GazelleProto) == 0){
					temp = xGetVector(dPlayerData, xVectorHold);
					trUnitSelectByQV("P"+p+"Unit");
					trUnitChangeProtoUnit("Ragnorok SFX");
					trUnitSelectByQV("P"+p+"Unit");
					trUnitDestroy();
					trUnitSelectClear();
					trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
					trUnitChangeProtoUnit("Hero Death");
					CreateGazelle(p, xsVectorGetX(temp), xsVectorGetZ(temp), 0);
				}
			}
		}
		uiZoomToProto(""+GazelleProto);
		uiLookAtProto(""+GazelleProto);
		unitTransform("Tartarian Gate Flame", "Flowers");
		unitTransform("Revealer", "Rocket");
		xsDisableSelf();
		InMinigame = false;
	}
}

rule DeerLeave
inactive
highFrequency
{
	int ABORT = 0;
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
			PlayersReadyToLeave = PlayersReadyToLeave-1;
			PlayerColouredChatToSelf(p, "You have left the extraction zone");
			ABORT = 1;
		}
	}
	if((xGetBool(dPlayerData, xReadyToLeave) == false) && (ABORT == 0)){
		if((trGetTerrainType(1*xsVectorGetX(tempV)/2,1*xsVectorGetZ(tempV)/2) == getTerrainType(LeaveTerrain)) && (trGetTerrainSubType(1*xsVectorGetX(tempV)/2,1*xsVectorGetZ(tempV)/2) == getTerrainSubType(LeaveTerrain))){
			xSetBool(dPlayerData, xReadyToLeave, true);
			PlayersReadyToLeave = PlayersReadyToLeave+1;
			PlayerColouredChat(p, trStringQuestVarGet("p"+p+"name") + " is ready to leave");
		}
	}
}

rule DeerExit
inactive
highFrequency
{
	xsDisableSelf();
	xsDisableRule("DeerActLoops");
	xsDisableRule("DeerMinigameDetect");
	xsDisableRule("DeerMinigameEnd");
	trChatSend(0, "END R1");
}
