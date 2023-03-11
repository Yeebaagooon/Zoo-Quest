void ChickenWave1(int unused = 0){
	ActPart = 2;
}

void ChickenWave1End(int unused = 0){
	ActPart = 3;
}

void ChickenWave2(int unused = 0){
	ActPart = 4;
}

void ChickenWave2End(int unused = 0){
	ActPart = 5;
}

rule BuildChickenArea
highFrequency
inactive
{
	if (trTime() > cActivationTime + 1) {
		TutorialMode = false;
		createChickenArea();
		xsDisableSelf();
		//replaceTerrainAboveHeightMax("ForestFloorPine", "GrassB", 0.0);
		trLetterBox(false);
		trUIFadeToColor(0,0,0,100,800,false);
		uiZoomToProto(""+ChickenProto);
		uiLookAtProto(""+ChickenProto);
		trDelayedRuleActivation("ResetBlackmap");
		//trDelayedRuleActivation("CrocMinigameDetect");
		trDelayedRuleActivation("TEST");
		//trDelayedRuleActivation("CrocEndZoneSee");
		trDelayedRuleActivation("ChickenAllDead");
		//trDelayedRuleActivation("CrocPoacherTimer");
		//xsEnableRule("CrocPoacherMovement");
		//trSetCounterDisplay("<color={PlayerColor(2)}>Fencing destroyed: "+FencesDone+"/8");
		ColouredIconChat("1,0.5,0", ActIcon(Stage), "<u>" + ActName(Stage) + "</u>");
		//ColouredIconChat("0.0,0.8,0.2", "icons\building norse shrine icon 64", "Interract with shrines using W.");
		ColouredChat("0.0,0.8,0.2", "Chickens are tasty and made out of food.");
		ColouredChat("0.0,0.8,0.2", "This probably needs a short cinematic.");
		xsEnableRule("PlayMusic");
		trQuestVarSet("Time", trTime());
		PlayersDead = 0;
		timediff = trTimeMS();
		timelast = trTimeMS();
		trDelayedRuleActivation("ChickenActLoops");
		for(p = 1 ; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			xSetInt(dPlayerData, xS5E, 5);
			trUnforbidProtounit(p, "Armory");
			trUnforbidProtounit(p, "Tower");
			xSetPointer(dPlayerData, p);
			//xSetInt(dPlayerData, xCrocSize, 1);
			//xSetFloat(dPlayerData, xCrocNext, 5*xGetInt(dPlayerData, xCrocSize));
			trQuestVarSet("P"+p+"FountainMsg", 0);
			//limit
			modifyProtounitAbsolute("Tower", p, 10, xGetInt(dPlayerData, xTowerLimit));
			//build points = how many s to build
			modifyProtounitAbsolute("Tower", p, 4, 6);
			//limit
			modifyProtounitAbsolute("Armory", p, 10, 1);
			//build points = how many s to build
			modifyProtounitAbsolute("Armory", p, 4, 40);
			trTechGodPower(p, "Animal Magnetism", 1);
			trPlayerSetDiplomacy(p, 0, "Neutral");
		}
		//trQuestVarSet("NextPoacherSpawn", trTime()+220);
		//trQuestVarSet("NextFoodSpawn", trTime()+90);
		trRateConstruction(1);
		if(QuickStart == 5){
			trRateConstruction(10);
		}
		ActPart = 1;
		trCounterAddTime("ChickenInfo", 65-(QuickStart*9), 0, "<color={PlayerColor(2)}>Attacks begin</color>", 40);
		xsEnableRule("ChickenWave1Go");
		modifyProtounitAbsolute("Toxotes", cNumberNonGaiaPlayers, 0, 50);
		modifyProtounitAbsolute("Militia", cNumberNonGaiaPlayers, 0, 50);
		modifyProtounitAbsolute("Toxotes", cNumberNonGaiaPlayers, 31, 5);
		modifyProtounitAbsolute("Spearman", cNumberNonGaiaPlayers, 0, 100);
		modifyProtounitAbsolute("Spearman", cNumberNonGaiaPlayers, 27, 10);
		modifyProtounitAbsolute("Spearman", cNumberNonGaiaPlayers, 34, 0);
		modifyProtounitAbsolute("Spearman", cNumberNonGaiaPlayers, 39, 0);
		modifyProtounitAbsolute("Militia", cNumberNonGaiaPlayers, 34, 0);
		modifyProtounitAbsolute("Militia", cNumberNonGaiaPlayers, 39, 0);
		modifyProtounitAbsolute("Slinger", cNumberNonGaiaPlayers, 0, 5);
		modifyProtounitAbsolute("Slinger", cNumberNonGaiaPlayers, 11, 18);
		modifyProtounitAbsolute("Slinger", cNumberNonGaiaPlayers, 2, 20);
		modifyProtounitAbsolute("Slinger", cNumberNonGaiaPlayers, 31, 10);
		modifyProtounitAbsolute("Peltast", cNumberNonGaiaPlayers, 0, 1000);
		modifyProtounitAbsolute("Peltast", cNumberNonGaiaPlayers, 11, 20);
		modifyProtounitAbsolute("Peltast", cNumberNonGaiaPlayers, 2, 250);
		modifyProtounitAbsolute("Peltast", cNumberNonGaiaPlayers, 31, 20);
		modifyProtounitAbsolute("Bella", cNumberNonGaiaPlayers, 0, 300);
		modifyProtounitAbsolute("Bella", cNumberNonGaiaPlayers, 27, 10);
		modifyProtounitAbsolute("Bella", cNumberNonGaiaPlayers, 28, 0);
		modifyProtounitAbsolute("Bella", cNumberNonGaiaPlayers, 29, 0);
		for(q = 33; < 55){
			modifyProtounitAbsolute("Bella", cNumberNonGaiaPlayers, q, 0);
			modifyProtounitAbsolute("Monkey King", cNumberNonGaiaPlayers, q, 0);
		}
		modifyProtounitAbsolute("Monkey King", cNumberNonGaiaPlayers, 0, 400);
		modifyProtounitAbsolute("Monkey King", cNumberNonGaiaPlayers, 27, 70);
		modifyProtounitAbsolute("Monkey King", cNumberNonGaiaPlayers, 28, 10);
		modifyProtounitAbsolute("Monkey King", cNumberNonGaiaPlayers, 29, 10);
		modifyProtounitAbsolute("Bogsveigir", cNumberNonGaiaPlayers, 0, 350);
		modifyProtounitAbsolute("Bogsveigir", cNumberNonGaiaPlayers, 31, 25);
		
		
		if(QuickStart == 0){
			gadgetUnreal("GodPowers");
		}
		trSetCounterDisplay("You will be able to hold more relics as the act progresses");
	}
}

rule ChickenWave1Go
inactive
highFrequency
{
	if(ActPart == 2){
		R5Wave(2*(PlayersActive-PlayersDead), "Militia", 3000, 2000);
		xsEnableRule("ChickenWave1A");
		playSound("\cinematics\04_in\armyarrive.wav");
		trCounterAddTime("ChickenInfo", 320, 0, "<color={PlayerColor(2)}>Ring 1 super poacher</color>", 41);
		trClearCounterDisplay();
		xsDisableSelf();
	}
}

rule ChickenWave1A
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(3*(PlayersActive-PlayersDead), "Militia", 1800, 1600);
		xsEnableRule("ChickenWave1B");
		xsDisableSelf();
	}
}

rule ChickenWave1B
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(3*(PlayersActive-PlayersDead), "Toxotes", 1900, 1700);
		xsEnableRule("ChickenWave1C");
		xsDisableSelf();
	}
}

rule ChickenWave1C
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(4*(PlayersActive-PlayersDead), "Toxotes", 1900, 1700);
		R5Wave(4*(PlayersActive-PlayersDead), "Militia", 1800, 1600);
		xsEnableRule("ChickenWave1D");
		xsDisableSelf();
	}
}

rule ChickenWave1D
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(6*(PlayersActive-PlayersDead), "Militia", 1900, 1600);
		R5Wave(1*(PlayersActive-PlayersDead), "Slinger", 2800, 2400);
		xsEnableRule("ChickenWave1E");
		xsDisableSelf();
	}
}

rule ChickenWave1E
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(6*(PlayersActive-PlayersDead), "Toxotes", 1900, 1600);
		xsEnableRule("ChickenWave1F");
		xsDisableSelf();
		for(p = 1; < cNumberNonGaiaPlayers){
			trModifyProtounit(ChickenProto, p, 5, 1);
			ColouredChatToPlayer(p, "1,0.5,0", "<u>Relic hold capacity increased!</u>");
		}
		ChickenLevel = 2;
		playSound("ageadvance.wav");
		trClearCounterDisplay();
		trSetCounterDisplay("Use 'R' to convert unwanted relics to landmines");
	}
}

rule ChickenWave1F
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(5*(PlayersActive-PlayersDead), "Spearman", 2000, 1700);
		xsEnableRule("ChickenWave1G");
		xsDisableSelf();
	}
}

rule ChickenWave1G
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(5*(PlayersActive-PlayersDead), "Slinger", 2800, 1600);
		R5Wave(5*(PlayersActive-PlayersDead), "Spearman", 2100, 1800);
		xsEnableRule("ChickenWave1H");
		trClearCounterDisplay();
		xsDisableSelf();
	}
}

rule ChickenWave1H
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(8*(PlayersActive-PlayersDead), "Spearman", 2500, 2000);
		xsEnableRule("ChickenWave1I");
		xsDisableSelf();
	}
}

rule ChickenWave1I
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(8*(PlayersActive-PlayersDead), "Slinger", 3500, 2000);
		xsEnableRule("ChickenWave1Super");
		xsDisableSelf();
	}
}

rule ChickenWave1Super
inactive
highFrequency
{
	if (ActPart == 3) {
		R5Wave(1, "Peltast", 3500, 2500);
		R5Wave(5*(PlayersActive-PlayersDead), "Spearman", 3000, 2000);
		modifyProtounitAbsolute("Wadjet Spit", cNumberNonGaiaPlayers, 1, 10);
		xsDisableSelf();
		playSound("\cinematics\04_in\armyarrive.wav");
		xsEnableRule("ChickenWave1Finish");
	}
}

rule ChickenWave1Finish
inactive
highFrequency
{
	if(trPlayerUnitCountSpecific(cNumberNonGaiaPlayers, "Peltast") == 0){
		modifyProtounitAbsolute("Wadjet Spit", cNumberNonGaiaPlayers, 1, 6);
		vector tileForStart = MapCentre*0.5;
		int StartTileX = xsVectorGetX(tileForStart);
		int StartTileZ = xsVectorGetZ(tileForStart);
		int currentId = 0;
		playSound("xwin.wav");
		trOverlayText("Ring 1 cleared!", 5.0,-1,-1,600);
		ChickenLevel = 3;
		for(p = 1; < cNumberNonGaiaPlayers){
			trModifyProtounit(ChickenProto, p, 24, 0.25);
			trModifyProtounit(ChickenProto, p, 25, 0.25);
			trModifyProtounit(ChickenProto, p, 26, 0.25);
			trModifyProtounit(ChickenProto, p, 5, 1);
			xSetPointer(dPlayerData, p);
			if((xGetBool(dPlayerData, xPlayerDead) == true) && (xGetBool(dPlayerData, xPlayerActive) == true)){
				CreateChicken(p, StartTileX*2, StartTileZ*2, 0);
				xSetBool(dPlayerData, xPlayerDead, false);
				PlayersDead = PlayersDead-1;
				trTechGodPower(p, "Animal Magnetism", 1);
			}
		}
		ColouredChat("1,0.5,0", "<u>Relic hold capacity increased!</u>");
		replaceCircle(StartTileX,StartTileZ,32, "BlackRock", "TundraRoadA");
		replaceCircle(StartTileX,StartTileZ,130,"IceC","CliffGreekA");
		refreshPassability();
		replaceCircle(StartTileX,StartTileZ,130,"CliffGreekA","IceC");
		
		
		
		trVectorQuestVarSet("dir", xsVectorSet(11, 0, 0));
		trVectorQuestVarSet("CentreMap", xsVectorSet(StartTileX*2, 0, StartTileZ*2));
		//SPAWN PLAYERS
		float baseCos = xsCos(6.283185 / (cNumberNonGaiaPlayers-1));
		float baseSin = xsSin(6.283185 / (cNumberNonGaiaPlayers-1));
		int heading = 90;
		for(p=1; < cNumberNonGaiaPlayers) {
			xSetPointer(dPlayerData, p);
			trVectorQuestVarSet("base", trVectorQuestVarGet("CentreMap") + trVectorQuestVarGet("dir"));
			heading = heading-(360/(cNumberNonGaiaPlayers-1));
			if(heading > 360){
				heading = heading-360;
			}
			if(heading < 0){
				heading = heading+360;
			}
			if(xGetBool(dPlayerData, xPlayerActive) == true){
				currentId = trGetNextUnitScenarioNameNumber();
				UnitCreate(0, "Relic", trVectorQuestVarGetX("base"), trVectorQuestVarGetZ("base"), heading);
				NewRelic(currentId, RELIC_NUMBER, 3);
			}
			//spyEffect(1*trQuestVarGet("P"+p+"Unit"), kbGetProtoUnitID("Gazelle"), vector(1,1,1), vector(1,1,1));
			trVectorQuestVarSet("dir", rotationMatrix(trVectorQuestVarGet("dir"), baseCos, baseSin));
			trUnitSelectClear();
		}
		trCounterAddTime("ChickenInfo", 65-(QuickStart*9), 0, "<color={PlayerColor(2)}>Ring 2 attacks begin</color>", 42);
		xsEnableRule("ChickenWave2Go");
		xsDisableSelf();
		
	}
}

rule ChickenWave2Go
inactive
highFrequency
{
	if(ActPart == 4){
		R5Wave(2*(PlayersActive-PlayersDead), "Bella", 3900, 3600);
		xsEnableRule("ChickenWave2A");
		playSound("\cinematics\04_in\armyarrive.wav");
		trCounterAddTime("ChickenInfo", 330, 0, "<color={PlayerColor(2)}>Ring 2 super poacher</color>", 43);
		trClearCounterDisplay();
		xsDisableSelf();
	}
}

rule ChickenWave2A
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(2*(PlayersActive-PlayersDead), "Bella", 4000, 3600);
		xsEnableRule("ChickenWave2B");
		xsDisableSelf();
	}
}

rule ChickenWave2B
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(3*(PlayersActive-PlayersDead), "Bogsveigir", 4300, 3900);
		xsEnableRule("ChickenWave2C");
		xsDisableSelf();
	}
}

rule ChickenWave2C
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(3*(PlayersActive-PlayersDead), "Bogsveigir", 5000, 4400);
		R5Wave(2*(PlayersActive-PlayersDead), "Bella", 4400, 3600);
		xsEnableRule("ChickenWave2D");
		xsDisableSelf();
	}
}

rule ChickenWave2D
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(3*(PlayersActive-PlayersDead), "Bella", 6000, 5000);
		R5Wave(1*(PlayersActive-PlayersDead), "Monkey King", 7000, 6000);
		xsEnableRule("ChickenWave2E");
		xsDisableSelf();
	}
}

rule ChickenWave2E
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(6*(PlayersActive-PlayersDead), "Bogsveigir", 7500, 6000);
		xsEnableRule("ChickenWave2F");
		xsDisableSelf();
		for(p = 1; < cNumberNonGaiaPlayers){
			trModifyProtounit(ChickenProto, p, 5, 1);
			ColouredChatToPlayer(p, "1,0.5,0", "<u>Relic hold capacity increased!</u>");
		}
		ChickenLevel = 4;
		playSound("ageadvance.wav");
	}
}

rule ChickenWave2F
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(5*(PlayersActive-PlayersDead), "Monkey King", 8000, 6600);
		xsEnableRule("ChickenWave2G");
		xsDisableSelf();
	}
}

rule ChickenWave2G
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(5*(PlayersActive-PlayersDead), "Bogsveigir", 8500, 7000);
		R5Wave(8*(PlayersActive-PlayersDead), "Monkey King", 8700, 7200);
		xsEnableRule("ChickenWave2H");
		trClearCounterDisplay();
		xsDisableSelf();
	}
}

rule ChickenWave2H
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(12*(PlayersActive-PlayersDead), "Bella", 9000, 7000);
		xsEnableRule("ChickenWave2I");
		xsDisableSelf();
	}
}

rule ChickenWave2I
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(12*(PlayersActive-PlayersDead), "Bogsveigir", 9900, 7000);
		xsEnableRule("ChickenWave2Super");
		xsDisableSelf();
	}
}

rule ChickenWave2Super
inactive
highFrequency
{
	if (ActPart == 5) {
		R5Wave(1, "Satyr", 3500, 2500);
		R5Wave(8*(PlayersActive-PlayersDead), "Monkey King", 9800, 8000);
		modifyProtounitAbsolute("Wadjet Spit", cNumberNonGaiaPlayers, 1, 10);
		xsDisableSelf();
		playSound("\cinematics\04_in\armyarrive.wav");
		xsEnableRule("ChickenWave2Finish");
	}
}


rule ChickenActLoops
highFrequency
inactive
{
	if(Stage == 5){
		timediff = 0.001 * (trTimeMS() - timelast); // calculate timediff
		timelast = trTimeMS();
		if(trTime() > 1*trQuestVarGet("Time")){
			trQuestVarModify("Time", "+", 1);
			for(p = 1; < cNumberNonGaiaPlayers){
				if(1*trQuestVarGet("P"+p+"ChickenRegen") > 0){
					trUnitSelectByQV("P"+p+"Unit");
					trDamageUnit(-1*trQuestVarGet("P"+p+"ChickenRegen"));
				}
				if(1*trQuestVarGet("P"+p+"TowerRegen") > 0){
					trUnitSelectByQV("P"+p+"Unit");
					trDamageUnitsInArea(p, "Tower", 500, -1*trQuestVarGet("P"+p+"TowerRegen"));
				}
			}
		}
		for(p = 1; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if((xGetBool(dPlayerData, xStopDeath) == false) && (trPlayerUnitCountSpecific(p, ""+ChickenProto) == 0) && (trPlayerUnitCountSpecific(p, "Prisoner") == 0) && (xGetBool(dPlayerData, xPlayerActive) == true) && (xGetBool(dPlayerData, xPlayerDead) == false) && (InMinigame == false)){
				//PLAYER DEAD
				PlayersDead = PlayersDead+1;
				xSetBool(dPlayerData, xPlayerDead, true);
				PlayerColouredChat(p, trStringQuestVarGet("p"+p+"name") + " is dead!");
				xSetVector(dPlayerData, xDeathVector, kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
				trPlayerKillAllGodPowers(p);
				trPlayerKillAllBuildings(p);
				trPlayerKillAllUnits(p);
				gadgetReal("GodPowers");
				trTechGodPower(1, "Rain", 1);
				if(iModulo(2, trTime()) == 0){
					playSound("\dialog\es\skul062.mp3");
				}
				else{
					playSound("\xpack\xdialog\es\xkri075.mp3");
				}
			}
			if((trTime() > 1*trQuestVarGet("P"+p+"ERecharge")) && (xGetInt(dPlayerData, xS5E) == 0)){
				trQuestVarSet("P"+p+"ERecharge", trTime()+xGetInt(dPlayerData, xS5ERecharge));
				xSetInt(dPlayerData, xS5E, -1);
			}
			if((trTime() >= 1*trQuestVarGet("P"+p+"ERecharge")) && (xGetInt(dPlayerData, xS5E) < 0)){
				xSetInt(dPlayerData, xS5E, 5);
			}
			
			if(xGetInt(dPlayerData, xS5E) > 0){
				if(trCurrentPlayer() == p){
					trCounterAbort("cdtutorial");
					trCounterAddTime("cdtutorial", -100, -200, "</color>E - All towers fire at cursor | " + xGetInt(dPlayerData, xS5E), -1);
				}
			}
			else if((1*trQuestVarGet("P"+p+"ERecharge") > trTime()) && (xGetInt(dPlayerData, xS5E) == -1)){
				if(trCurrentPlayer() == p){
					trCounterAbort("cdtutorial");
					trCounterAddTime("cdtutorial", xGetInt(dPlayerData, xS5ERecharge), 0, "</color>E recharging", -1);
				}
				xSetInt(dPlayerData, xS5E, -2);
				//E recharge
			}
		}
	}
}

rule ChickenAllDead
inactive
minInterval 5
{
	if((Stage == 5) && (PlayersDead == PlayersActive)){
		trShowWinLose("All players are dead", "xlose.wav");
		for(p=1 ; < cNumberNonGaiaPlayers){
			trSetPlayerDefeated(p);
		}
		xsDisableSelf();
		trEndGame();
	}
}
