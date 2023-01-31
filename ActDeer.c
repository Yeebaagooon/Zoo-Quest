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
	//Check terrain for extraction
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
	trPaintTerrain(xsVectorGetX(StageVector)+6,xsVectorGetZ(StageVector)+3,xsVectorGetX(StageVector)+25,xsVectorGetZ(StageVector)+7,0,73);
	trPaintTerrain(xsVectorGetX(StageVector),xsVectorGetZ(StageVector)+3,xsVectorGetX(StageVector),xsVectorGetZ(StageVector)+7,2,13);
	PaintAtlantisArea(xsVectorGetX(StageVector)+26,xsVectorGetZ(StageVector)+4,xsVectorGetX(StageVector)+28,xsVectorGetZ(StageVector)+6,0,71);
	for(z=1 ; < 8){
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(0, "Cinematic Block", 2*xsVectorGetX(StageVector)+(8*z),2*xsVectorGetZ(StageVector)+11,0);
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
	if(PlayersMinigaming > 0){
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
	}
	else if(PlayersMinigaming == 0){
		//end MG
		trUnitSelectByQV("MinigameStartSFX");
		trUnitDestroy();
		trUnitSelectByQV("MinigameStartID");
		trUnitDestroy();
		trDelayedRuleActivation("DeerMinigameEnd");
		trMessageSetText("Nobody was on the white tiles. Minigame cancelled.", 5000);
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
				trQuestVarSet("P"+p+"Unit", trGetNextUnitScenarioNameNumber());
				UnitCreate(p, ""+GazelleProto, xsVectorGetX(temp), xsVectorGetZ(temp), 0);
				trUnitSelectByQV("P"+p+"Unit");
				trSetSelectedScale(0,1,0);
				trUnitSelectByQV("P"+p+"Unit");
				spyEffect(kbGetProtoUnitID("Gazelle"), 0, xsVectorSet(dPlayerData,xSpyID,p), vector(1,1,1));
				xSetBool(dPlayerData, xStopDeath, false);
				xSetInt(dPlayerData, xTeleportDue, 0);
			}
		}
		uiZoomToProto(""+GazelleProto);
		uiLookAtProto(""+GazelleProto);
		unitTransform("Tartarian Gate Flame", "Flowers");
		unitTransform("Revealer", "Rocket");
		xsDisableSelf();
	}
}
