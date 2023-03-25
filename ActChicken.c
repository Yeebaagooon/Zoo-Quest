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

void ChickenWave3(int unused = 0){
	ActPart = 6;
}

void ChickenWave3End(int unused = 0){
	ActPart = 7;
}

rule BuildChickenArea
highFrequency
inactive
{
	if (trTime() > cActivationTime + 1) {
		TutorialMode = false;
		createChickenArea();
		xsDisableSelf();
		trUIFadeToColor(0,0,0,100,800,false);
		if(PlayCine == true){
			xsEnableRule("C_Cine_000");
		}
		else{
			xsEnableRule("ChickenLanding");
		}
		uiZoomToProto(""+ChickenProto);
		uiLookAtProto(""+ChickenProto);
		//replaceTerrainAboveHeightMax("ForestFloorPine", "GrassB", 0.0);
		xsEnableRule("PlayMusic");
	}
}

rule ChickenLanding
highFrequency
inactive
{
	if (trTime() > cActivationTime + 3) {
		trLetterBox(false);
		uiZoomToProto(""+ChickenProto);
		uiLookAtProto(""+ChickenProto);
		trDelayedRuleActivation("ResetBlackmap");
		trDelayedRuleActivation("TEST");
		trDelayedRuleActivation("ChickenAllDead");
		ColouredIconChat("1,0.5,0", ActIcon(Stage), "<u>" + ActName(Stage) + "</u>");
		ColouredChat("0.0,0.8,0.2", "Chickens are tasty and made out of food.");
		ColouredChat("0.0,0.8,0.2", "The hordes are coming - defend yourselves!");
		trQuestVarSet("Time", trTime());
		PlayersDead = 0;
		timediff = trTimeMS();
		timelast = trTimeMS();
		trDelayedRuleActivation("ChickenActLoops");
		for(p = 1 ; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			xSetInt(dPlayerData, xS5E, 1);
			trUnforbidProtounit(p, "Armory");
			trUnforbidProtounit(p, "Tower");
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
		trRateConstruction(1);
		if(QuickStart == 5){
			trRateConstruction(10);
		}
		ActPart = 1;
		trCounterAddTime("ChickenInfo", 65-(QuickStart*9), 0, "<color={PlayerColor(2)}>Attacks begin</color>", 40);
		xsEnableRule("ChickenWave1Go");
		//trModifyProtounit(ChickenProto, 1, 5, 4);
		//xsEnableRule("ChickenWave2Finish");
		modifyProtounitAbsolute("Toxotes", cNumberNonGaiaPlayers, 0, 50);
		modifyProtounitAbsolute("Militia", cNumberNonGaiaPlayers, 0, 50);
		modifyProtounitAbsolute("Toxotes", cNumberNonGaiaPlayers, 31, 5);
		modifyProtounitAbsolute("Spearman", cNumberNonGaiaPlayers, 0, 100);
		modifyProtounitAbsolute("Spearman", cNumberNonGaiaPlayers, 27, 10);
		modifyProtounitAbsolute("Spearman", cNumberNonGaiaPlayers, 34, 0);
		modifyProtounitAbsolute("Spearman", cNumberNonGaiaPlayers, 39, 0);
		modifyProtounitAbsolute("Militia", cNumberNonGaiaPlayers, 34, 0);
		modifyProtounitAbsolute("Militia", cNumberNonGaiaPlayers, 39, 0);
		modifyProtounitAbsolute("Slinger", cNumberNonGaiaPlayers, 0, 50);
		modifyProtounitAbsolute("Slinger", cNumberNonGaiaPlayers, 11, 18);
		modifyProtounitAbsolute("Slinger", cNumberNonGaiaPlayers, 2, 20);
		modifyProtounitAbsolute("Slinger", cNumberNonGaiaPlayers, 31, 10);
		modifyProtounitAbsolute("Peltast", cNumberNonGaiaPlayers, 0, 1000);
		modifyProtounitAbsolute("Peltast", cNumberNonGaiaPlayers, 11, 20);
		modifyProtounitAbsolute("Peltast", cNumberNonGaiaPlayers, 2, 250);
		modifyProtounitAbsolute("Peltast", cNumberNonGaiaPlayers, 31, 20);
		modifyProtounitAbsolute("Bella", cNumberNonGaiaPlayers, 0, 150);
		modifyProtounitAbsolute("Bella", cNumberNonGaiaPlayers, 27, 10);
		modifyProtounitAbsolute("Bella", cNumberNonGaiaPlayers, 28, 0);
		modifyProtounitAbsolute("Bella", cNumberNonGaiaPlayers, 29, 0);
		trModifyProtounit("Bella", cNumberNonGaiaPlayers, 1, -1);
		trModifyProtounit("Militia", cNumberNonGaiaPlayers, 1, -1);
		trModifyProtounit("Spearman", cNumberNonGaiaPlayers, 1, -1);
		for(q = 33; < 55){
			modifyProtounitAbsolute("Bella", cNumberNonGaiaPlayers, q, 0);
			modifyProtounitAbsolute("Monkey King", cNumberNonGaiaPlayers, q, 0);
		}
		modifyProtounitAbsolute("Monkey King", cNumberNonGaiaPlayers, 0, 200);
		modifyProtounitAbsolute("Monkey King", cNumberNonGaiaPlayers, 27, 30);
		modifyProtounitAbsolute("Monkey King", cNumberNonGaiaPlayers, 28, 10);
		modifyProtounitAbsolute("Monkey King", cNumberNonGaiaPlayers, 29, 10);
		modifyProtounitAbsolute("Bogsveigir", cNumberNonGaiaPlayers, 0, 100);
		modifyProtounitAbsolute("Bogsveigir", cNumberNonGaiaPlayers, 31, 25);
		
		modifyProtounitAbsolute("Toxotes", cNumberNonGaiaPlayers, 2, 50);
		modifyProtounitAbsolute("Militia", cNumberNonGaiaPlayers, 2, 50);
		modifyProtounitAbsolute("Spearman", cNumberNonGaiaPlayers, 2, 50);
		modifyProtounitAbsolute("Slinger", cNumberNonGaiaPlayers, 2, 50);
		modifyProtounitAbsolute("Peltast", cNumberNonGaiaPlayers, 2, 50);
		modifyProtounitAbsolute("Bella", cNumberNonGaiaPlayers, 2, 50);
		modifyProtounitAbsolute("Monkey King", cNumberNonGaiaPlayers, 2, 50);
		modifyProtounitAbsolute("Bogsveigir", cNumberNonGaiaPlayers, 2, 50);
		
		modifyProtounitAbsolute("Satyr", cNumberNonGaiaPlayers, 0, 2000);
		modifyProtounitAbsolute("Satyr", cNumberNonGaiaPlayers, 11, 20);
		modifyProtounitAbsolute("Satyr", cNumberNonGaiaPlayers, 2, 400);
		modifyProtounitAbsolute("Satyr", cNumberNonGaiaPlayers, 31, 40);
		modifyProtounitAbsolute("Satyr", cNumberNonGaiaPlayers, 13, 1);
		
		modifyProtounitAbsolute("White Tiger", cNumberNonGaiaPlayers, 0, 300);
		modifyProtounitAbsolute("White Tiger", cNumberNonGaiaPlayers, 27, 60);
		
		modifyProtounitAbsolute("Scarab", cNumberNonGaiaPlayers, 0, 400);
		modifyProtounitAbsolute("Scarab", cNumberNonGaiaPlayers, 27, 110);
		
		modifyProtounitAbsolute("Manticore", cNumberNonGaiaPlayers, 0, 200);
		modifyProtounitAbsolute("Manticore", cNumberNonGaiaPlayers, 11, 26);
		modifyProtounitAbsolute("Manticore", cNumberNonGaiaPlayers, 2, 400);
		modifyProtounitAbsolute("Manticore", cNumberNonGaiaPlayers, 31, 80);
		modifyProtounitAbsolute("Manticore", cNumberNonGaiaPlayers, 13, 1);
		
		modifyProtounitAbsolute("Fenris Wolf", cNumberNonGaiaPlayers, 0, 500);
		modifyProtounitAbsolute("Fenris Wolf", cNumberNonGaiaPlayers, 27, 160);
		
		modifyProtounitAbsolute("Militia", cNumberNonGaiaPlayers, 24, 0);
		modifyProtounitAbsolute("Militia", cNumberNonGaiaPlayers, 25, 0);
		modifyProtounitAbsolute("Militia", cNumberNonGaiaPlayers, 26, 0);
		modifyProtounitAbsolute("Titan Prometheus", cNumberNonGaiaPlayers, 24, 0);
		modifyProtounitAbsolute("Titan Prometheus", cNumberNonGaiaPlayers, 25, 0);
		modifyProtounitAbsolute("Titan Prometheus", cNumberNonGaiaPlayers, 26, 0);
		
		if(Difficulty > 1){
			modifyProtounitAbsolute("Manticore", cNumberNonGaiaPlayers, 0, 300);
			modifyProtounitAbsolute("White Tiger", cNumberNonGaiaPlayers, 0, 400);
			modifyProtounitAbsolute("Scarab", cNumberNonGaiaPlayers, 0, 500);
		}
		
		trTechSetStatus(cNumberNonGaiaPlayers, 500, 4);
		modifyProtounitAbsolute("Titan Prometheus", cNumberNonGaiaPlayers, 9, 0);
		
		if(QuickStart == 0){
			gadgetUnreal("GodPowers");
		}
		trSetCounterDisplay("You will be able to hold more relics as the act progresses");
		for(x = 1; <= cNumberNonGaiaPlayers){
			trModifyProtounit("Dwarf", x, 8, 10);
		}
		AllowChicken = 0;
		xsDisableSelf();
	}
}

rule ChickenWave1Go
inactive
highFrequency
{
	if(ActPart == 2){
		R5Wave(2*(PlayersActive-PlayersDead), "Militia", 3000, 2000);
		xsEnableRule("ChickenWave1A");
		//xsEnableRule("ChickenWave1Finish");
		playSound("\cinematics\04_in\armyarrive.wav");
		trCounterAddTime("ChickenInfo", 200, 0, "<color={PlayerColor(2)}>Ring 1 super poacher</color>", 41);
		trClearCounterDisplay();
		xsDisableSelf();
	}
}

rule ChickenWave1A
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(2*(PlayersActive-PlayersDead), "Toxotes", 1900, 1700);
		xsEnableRule("ChickenWave1C");
		xsDisableSelf();
	}
}

rule ChickenWave1C
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(2*(PlayersActive-PlayersDead), "Toxotes", 1900, 1700);
		R5Wave(3*(PlayersActive-PlayersDead), "Militia", 1800, 1600);
		xsEnableRule("ChickenWave1E");
		xsDisableSelf();
	}
}


rule ChickenWave1E
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(3*(PlayersActive-PlayersDead), "Toxotes", 1900, 1600);
		if(Difficulty == 3){
			R5Wave(2*(PlayersActive-PlayersDead), "Slinger", 1900, 1600);
		}
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
		R5Wave(2*(PlayersActive-PlayersDead), "Spearman", 2000, 1700);
		xsEnableRule("ChickenWave1G");
		xsDisableSelf();
	}
}

rule ChickenWave1G
inactive
highFrequency
{
	if (trTime() > cActivationTime + 40) {
		R5Wave(2*(PlayersActive-PlayersDead), "Slinger", 2800, 1600);
		R5Wave(3*(PlayersActive-PlayersDead), "Spearman", 2100, 1800);
		trClearCounterDisplay();
		xsDisableSelf();
		xsEnableRule("ChickenWave1Super");
	}
}

rule ChickenWave1Super
inactive
highFrequency
{
	if (ActPart == 3) {
		trQuestVarSet("SuperPoacher", trGetNextUnitScenarioNameNumber());
		R5Wave(1, "Peltast", 3500, 2500);
		R5Wave(2*(PlayersActive-PlayersDead), "Spearman", 3000, 2000);
		modifyProtounitAbsolute("Wadjet Spit", cNumberNonGaiaPlayers, 1, 10);
		xsDisableSelf();
		playSound("\cinematics\04_in\armyarrive.wav");
		xsEnableRule("ChickenWave1Finish");
		xsEnableRule("PeltastWalk");
	}
}

rule PeltastWalk
inactive
highFrequency
{
	if (trTime() > cActivationTime + 40) {
		trModifyProtounit("Peltast", cNumberNonGaiaPlayers, 55, 4);
		trUnitSelectByQV("SuperPoacher");
		trUnitMoveToPoint(128,0,128,-1,true);
		xsDisableSelf();
	}
}

rule ChickenWave1Finish
inactive
highFrequency
{
	if(trPlayerUnitCountSpecific(cNumberNonGaiaPlayers, "Peltast") == 0){
		ActPart = 3;
		trPlayerKillAllUnits(cNumberNonGaiaPlayers);
		R5Chest((cNumberNonGaiaPlayers-Difficulty), 9800, 3600);
		modifyProtounitAbsolute("Wadjet Spit", cNumberNonGaiaPlayers, 1, 6);
		vector tileForStart = MapCentre*0.5;
		int StartTileX = xsVectorGetX(tileForStart);
		int StartTileZ = xsVectorGetZ(tileForStart);
		int currentId = 0;
		playSound("xwin.wav");
		trOverlayText("Ring 1 cleared!", 5.0,-1,-1,600);
		AllowChicken = 1;
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
		AllowChicken = 0;
		trCounterAddTime("ChickenInfo", 65-(QuickStart*9), 0, "<color={PlayerColor(2)}>Ring 2 attacks begin</color>", 42);
		xsEnableRule("ChickenWave2Go");
		ChickenLevel = 3;
		for(p = 1; < cNumberNonGaiaPlayers){
			trModifyProtounit(ChickenProto, p, 24, 0.25);
			trModifyProtounit(ChickenProto, p, 25, 0.25);
			trModifyProtounit(ChickenProto, p, 26, 0.25);
			trModifyProtounit(ChickenProto, p, 5, 1);
			xSetPointer(dPlayerData, p);
		}
		ColouredChat("1,0.5,0", "<u>Relic hold capacity increased!</u>");
		/*replaceCircle(StartTileX,StartTileZ,32, "BlackRock", "TundraRoadA");
		replaceCircle(StartTileX,StartTileZ,130,"IceC","CliffGreekA");
		refreshPassability();
		replaceCircle(StartTileX,StartTileZ,130,"CliffGreekA","IceC");
		replaceCircleOutline(StartTileX,StartTileZ,52, "TundraRoadC", "BlackRock");
		trVectorQuestVarSet("dir", xsVectorSet(11, 0, 0));
		trVectorQuestVarSet("CentreMap", xsVectorSet(StartTileX*2, 0, StartTileZ*2));*/
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
			trVectorQuestVarSet("dir", rotationMatrix(trVectorQuestVarGet("dir"), baseCos, baseSin));
		}
		paintCircleOutline(StartTileX,StartTileZ,32, "TundraRoadA");
		paintCircleOutline(StartTileX,StartTileZ,52, "BlackRock");
		refreshPassability();
		xsDisableSelf();
	}
}

rule ChickenWave2Go
inactive
highFrequency
{
	if(ActPart == 4){
		R5Wave(1*(PlayersActive-PlayersDead), "Bella", 3900, 3600);
		xsEnableRule("ChickenWave2B");
		playSound("\cinematics\04_in\armyarrive.wav");
		trCounterAddTime("ChickenInfo", 240, 0, "<color={PlayerColor(2)}>Ring 2 super poacher</color>", 43);
		trClearCounterDisplay();
		xsDisableSelf();
	}
}

rule ChickenWave2B
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(1*(PlayersActive-PlayersDead), "Bogsveigir", 4300, 3900);
		xsEnableRule("ChickenWave2C");
		xsDisableSelf();
	}
}


rule ChickenWave2C
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
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
		R5Wave(1*(PlayersActive-PlayersDead), "Bogsveigir", 7500, 6000);
		xsEnableRule("ChickenWave2G");
		xsDisableSelf();
		for(p = 1; < cNumberNonGaiaPlayers){
			trModifyProtounit(ChickenProto, p, 5, 1);
			ColouredChatToPlayer(p, "1,0.5,0", "<u>Relic hold capacity increased!</u>");
		}
		ChickenLevel = 4;
		playSound("ageadvance.wav");
	}
}

rule ChickenWave2G
inactive
highFrequency
{
	if (trTime() > cActivationTime + 45) {
		R5Wave(1*(PlayersActive-PlayersDead), "Bogsveigir", 8500, 7000);
		R5Wave(1*(PlayersActive-PlayersDead), "Monkey King", 8700, 7200);
		xsEnableRule("ChickenWave2I");
		trClearCounterDisplay();
		xsDisableSelf();
	}
}

rule ChickenWave2I
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(2*(PlayersActive-PlayersDead), "Bogsveigir", 9900, 7000);
		xsEnableRule("ChickenWave2Super");
		xsDisableSelf();
	}
}

rule ChickenWave2Super
inactive
highFrequency
{
	if (ActPart == 5) {
		trQuestVarSet("SuperPoacher", trGetNextUnitScenarioNameNumber());
		R5Wave(1, "Satyr", 9900, 8000);
		R5Wave(1*(PlayersActive-PlayersDead), "Monkey King", 9800, 8000);
		modifyProtounitAbsolute("Wadjet Spit", cNumberNonGaiaPlayers, 1, 12);
		xsDisableSelf();
		playSound("\cinematics\04_in\armyarrive.wav");
		xsEnableRule("ChickenWave2Finish");
		xsEnableRule("SatyrWalk");
	}
}

rule SatyrWalk
inactive
highFrequency
{
	if (trTime() > cActivationTime + 40) {
		trModifyProtounit("Satyr", cNumberNonGaiaPlayers, 55, 4);
		trUnitSelectByQV("SuperPoacher");
		trUnitMoveToPoint(128,0,128,-1,true);
		xsDisableSelf();
	}
}

rule ChickenWave2Finish
inactive
highFrequency
{
	if(trPlayerUnitCountSpecific(cNumberNonGaiaPlayers, "Satyr") == 0){
		AllowChicken = 1;
		trPlayerKillAllUnits(cNumberNonGaiaPlayers);
		R5Chest((cNumberNonGaiaPlayers-Difficulty), 20000, 9800);
		modifyProtounitAbsolute("Wadjet Spit", cNumberNonGaiaPlayers, 1, 6);
		vector tileForStart = MapCentre*0.5;
		int StartTileX = xsVectorGetX(tileForStart);
		int StartTileZ = xsVectorGetZ(tileForStart);
		int currentId = 0;
		playSound("xwin.wav");
		trOverlayText("Ring 2 cleared!", 5.0,-1,-1,600);
		ChickenLevel = 5;
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
		AllowChicken = 0;
		ColouredChat("1,0.5,0", "<u>Relic hold capacity increased!</u>");
		paintCircleOutline(StartTileX,StartTileZ,52, "UnderwaterRockC");
		refreshPassability();
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
				NewRelic(currentId, RELIC_NUMBER, 5);
			}
			//spyEffect(1*trQuestVarGet("P"+p+"Unit"), kbGetProtoUnitID("Gazelle"), vector(1,1,1), vector(1,1,1));
			trVectorQuestVarSet("dir", rotationMatrix(trVectorQuestVarGet("dir"), baseCos, baseSin));
			trUnitSelectClear();
		}
		trCounterAddTime("ChickenInfo", 90-(QuickStart*15), 0, "<color={PlayerColor(2)}>Final ring attacks begin</color>", 44);
		xsEnableRule("ChickenWave3Go");
		xsDisableSelf();
	}
}

rule ChickenWave3Go
inactive
highFrequency
{
	if(ActPart == 6){
		R5Wave(1*(PlayersActive-PlayersDead), "White Tiger", 12000, 10000);
		//R5Wave(1, "Manticore", 12000, 10000);
		xsEnableRule("ChickenWave3A");
		playSound("\cinematics\04_in\armyarrive.wav");
		trClearCounterDisplay();
		trCounterAddTime("ChickenInfo", 260, 0, "<color={PlayerColor(2)}>Ultra poacher</color>", 45);
		xsDisableSelf();
	}
}

rule ChickenWave3A
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(1*(PlayersActive-PlayersDead), "Scarab", 12000, 10000);
		//R5Wave(1, "Titan Prometheus", 12000, 10000);
		xsEnableRule("ChickenWave3C");
		xsDisableSelf();
	}
}

rule ChickenWave3C
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(1*(PlayersActive-PlayersDead), "Scarab", 14000, 10000);
		R5Wave(2*(PlayersActive-PlayersDead), "White Tiger", 15000, 10000);
		xsEnableRule("ChickenWave3D");
		xsDisableSelf();
	}
}

rule ChickenWave3D
inactive
highFrequency
{
	if (trTime() > cActivationTime + 35) {
		R5Wave(2*(PlayersActive-PlayersDead), "Scarab", 16000, 10000);
		R5Wave(1*(PlayersActive-PlayersDead), "Manticore", 16000, 10000);
		xsEnableRule("ChickenWave3E");
		xsDisableSelf();
	}
}

rule ChickenWave3E
inactive
highFrequency
{
	if (trTime() > cActivationTime + 35) {
		R5Wave(2*(PlayersActive-PlayersDead), "Fenris Wolf", 16000, 10000);
		xsEnableRule("ChickenWave3F");
		xsDisableSelf();
		for(p = 1; < cNumberNonGaiaPlayers){
			trModifyProtounit(ChickenProto, p, 5, 1);
			ColouredChatToPlayer(p, "1,0.5,0", "<u>Relic hold capacity increased!</u>");
		}
		ChickenLevel = 6;
		playSound("ageadvance.wav");
	}
}

rule ChickenWave3F
inactive
highFrequency
{
	if (trTime() > cActivationTime + 45) {
		R5Wave(1*(PlayersActive-PlayersDead), "Manticore", 16000, 6600);
		xsEnableRule("ChickenWave3H");
		xsDisableSelf();
	}
}


rule ChickenWave3H
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(3*(PlayersActive-PlayersDead), "Fenris Wolf", 16000, 7000);
		xsEnableRule("ChickenWave3Super");
		xsDisableSelf();
	}
}

rule ChickenWave3Super
inactive
highFrequency
{
	if (ActPart == 7) {
		R5Wave(1, "Titan Prometheus", 14000, 10000);
		R5Wave(2*(PlayersActive-PlayersDead), "White Tiger", 12000, 10000);
		modifyProtounitAbsolute("Wadjet Spit", cNumberNonGaiaPlayers, 1, 12);
		modifyProtounitAbsolute("Titan Prometheus", cNumberNonGaiaPlayers, 0, 8000+(3000*Difficulty));
		xsDisableSelf();
		playSound("\cinematics\04_in\armyarrive.wav");
		trSetLighting("Night", 6);
		xsEnableRule("ChickenWave3Finish");
	}
}

rule ChickenWave3Finish
inactive
highFrequency
{
	if(trPlayerUnitCountSpecific(cNumberNonGaiaPlayers, "Titan Prometheus") == 0){
		trFadeOutAllSounds(3);
		playSound("xwin.wav");
		trSetLighting("default", 3);
		trUIFadeToColor(255,255,255,1500,3000,true);
		xsEnableRule("EndGameLand");
		trFadeOutMusic(3);
		trPlayerKillAllUnits(cNumberNonGaiaPlayers);
		for(a = xGetDatabaseCount(dMissiles); > 0){
			xDatabaseNext(dMissiles);
			xUnitSelect(dMissiles, xUnitID);
			trUnitDestroy();
			xFreeDatabaseBlock(dMissiles);
		}
		xClearDatabase(dMissiles);
		xResetDatabase(dMissiles);
		for(p = 1; < cNumberNonGaiaPlayers){
			trPlayerKillAllGodPowers(p);
			trUnitSelectClear();
			trUnitSelectByQV("P"+p+"Unit");
			trDamageUnit(-1000);
		}
		xsDisableSelf();
		xsDisableRule("BuildChickenArea");
		xsDisableRule("ChickenLanding");
		xsDisableRule("ChickenWave1Go");
		xsDisableRule("ChickenWave1A");
		xsDisableRule("ChickenWave1B");
		xsDisableRule("ChickenWave1C");
		xsDisableRule("ChickenWave1D");
		xsDisableRule("ChickenWave1E");
		xsDisableRule("ChickenWave1F");
		xsDisableRule("ChickenWave1G");
		xsDisableRule("ChickenWave1H");
		xsDisableRule("ChickenWave1I");
		xsDisableRule("ChickenWave1Super");
		xsDisableRule("ChickenWave1Finish");
		xsDisableRule("ChickenWave2Go");
		xsDisableRule("ChickenWave2A");
		xsDisableRule("ChickenWave2B");
		xsDisableRule("ChickenWave2C");
		xsDisableRule("ChickenWave2D");
		xsDisableRule("ChickenWave2E");
		xsDisableRule("ChickenWave2F");
		xsDisableRule("ChickenWave2G");
		xsDisableRule("ChickenWave2H");
		xsDisableRule("ChickenWave2I");
		xsDisableRule("ChickenWave2Super");
		xsDisableRule("ChickenWave2Finish");
		xsDisableRule("ChickenWave3Go");
		xsDisableRule("ChickenWave3A");
		xsDisableRule("ChickenWave3B");
		xsDisableRule("ChickenWave3C");
		xsDisableRule("ChickenWave3D");
		xsDisableRule("ChickenWave3E");
		xsDisableRule("ChickenWave3F");
		xsDisableRule("ChickenWave3G");
		xsDisableRule("ChickenWave3H");
		xsDisableRule("ChickenWave3I");
		xsDisableRule("ChickenWave3Super");
		xsDisableRule("ChickenWave3Finish");
		xsDisableRule("ChickenActLoops");
		xsDisableRule("ChickenAllDead");
		xsDisableRule("TutorialTerrainChicken");
		xsDisableRule("FirstTower");
		xsDisableRule("MissileCheckS5");
		xsDisableRule("ChickenMechanicLoops");
		xsDisableRule("ChickenTutorialLoops");
		xsDisableRule("ChickenTutorialDone");
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
				PlayerColouredChat(p, "They will respawn once the super poacher is dead!");
				xSetVector(dPlayerData, xDeathVector, kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
				trPlayerKillAllGodPowers(p);
				trPlayerKillAllBuildings(p);
				trPlayerKillAllUnits(p);
				if(iModulo(2, trTime()) == 0){
					playSound("\dialog\es\skul062.mp3");
				}
				else{
					playSound("\xpack\xdialog\es\xkri075.mp3");
				}
			}
			if(xGetInt(dPlayerData, xHPRegen) > 0){
				if(trTime() > xGetInt(dPlayerData, xHPRegenNext)){
					trUnitSelectByQV("P"+p+"Unit");
					trDamageUnit(-1*xGetInt(dPlayerData, xHPRegen));
					xSetInt(dPlayerData, xHPRegenNext, trTime()+xGetInt(dPlayerData, xHPRegenTime));
				}
			}
			if((trTime() > 1*trQuestVarGet("P"+p+"ERecharge")) && (xGetInt(dPlayerData, xS5E) == 0)){
				trQuestVarSet("P"+p+"ERecharge", trTime()+xGetInt(dPlayerData, xS5ERecharge));
				xSetInt(dPlayerData, xS5E, -1);
			}
			if((trTime() >= 1*trQuestVarGet("P"+p+"ERecharge")) && (xGetInt(dPlayerData, xS5E) < 0)){
				xSetInt(dPlayerData, xS5E, 1);
			}
			
			if(xGetInt(dPlayerData, xS5E) > 0){
				if(trCurrentPlayer() == p){
					trCounterAbort("cdtutorial");
					trCounterAddTime("cdtutorial", -100, -200, "</color>E - All towers doubleshot", -1);
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
				if(trCountUnitsInArea(""+n,pl,ChickenProto, 5) > 0){
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
					trQuestVarSetFromRand("temp2", 1, 3);
					if(ActPart < 6){
						if(1*trQuestVarGet("temp2") == 1){
							PlayerChoice(pl, "Choose your reward:", "+200 chicken hp", 57, "+4 tower limit", 59, 10000);
						}
						if(1*trQuestVarGet("temp2") == 2){
							PlayerChoice(pl, "Choose your reward:", "+1 chicken speed", 58, "+4 tower attack", 60, 10000);
						}
						if(1*trQuestVarGet("temp2") == 3){
							PlayerChoice(pl, "Choose your reward:", "+1 landmine explosion range", 61, "+20hp regen every 20s", 62, 10000);
						}
					}
					else{
						//more rewards higher
						if(1*trQuestVarGet("temp2") == 1){
							PlayerChoice(pl, "Choose your reward:", "+400 chicken hp", 57, "+8 tower limit", 59, 10000);
						}
						if(1*trQuestVarGet("temp2") == 2){
							PlayerChoice(pl, "Choose your reward:", "+2 chicken speed", 58, "+8 tower attack", 60, 10000);
						}
						if(1*trQuestVarGet("temp2") == 3){
							PlayerChoice(pl, "Choose your reward:", "+2 landmine explosion range", 61, "+60hp regen every 20s", 62, 10000);
						}
					}
				}
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
		EndChats();
		trEndGame();
		playSound("\Yeebaagooon\Zoo Quest\Credits.mp3");
	}
}
