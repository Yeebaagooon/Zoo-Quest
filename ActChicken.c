void ChickenWave1(int unused = 0){
	ActPart = 2;
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
		//trDelayedRuleActivation("CrocAllDead");
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
			trUnforbidProtounit(p, "Armory");
			trUnforbidProtounit(p, "Tower");
			xSetPointer(dPlayerData, p);
			//xSetInt(dPlayerData, xCrocSize, 1);
			//xSetFloat(dPlayerData, xCrocNext, 5*xGetInt(dPlayerData, xCrocSize));
			trQuestVarSet("P"+p+"FountainMsg", 0);
			//limit
			modifyProtounitAbsolute("Tower", p, 10, 10);
			//build points = how many s to build
			modifyProtounitAbsolute("Tower", p, 4, 6);
			//limit
			modifyProtounitAbsolute("Armory", p, 10, 1);
			//build points = how many s to build
			modifyProtounitAbsolute("Armory", p, 4, 40);
		}
		//trQuestVarSet("NextPoacherSpawn", trTime()+220);
		//trQuestVarSet("NextFoodSpawn", trTime()+90);
		trRateConstruction(1);
		if(QuickStart == 5){
			trRateConstruction(10);
		}
		ActPart = 1;
		trCounterAddTime("ChickenInfo", 7, 0, "<color={PlayerColor(2)}>Attacks begin</color>", 40);
		xsEnableRule("ChickenWave1Go");
		modifyProtounitAbsolute("Toxotes", cNumberNonGaiaPlayers, 0, 10);
		modifyProtounitAbsolute("Toxotes", cNumberNonGaiaPlayers, 31, 5);
		modifyProtounitAbsolute("Huskarl", cNumberNonGaiaPlayers, 0, 20);
		modifyProtounitAbsolute("Huskarl", cNumberNonGaiaPlayers, 27, 10);
	}
}

rule ChickenWave1Go
inactive
highFrequency
{
	if(ActPart == 2){
		R5Wave(5*PlayersActive, "Hoplite", 1800, 1600);
		xsEnableRule("ChickenWave1A");
		playSound("\cinematics\04_in\armyarrive.wav");
		xsDisableSelf();
	}
}

rule ChickenWave1A
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(5*PlayersActive, "Hoplite", 1800, 1600);
		xsEnableRule("ChickenWave1B");
		xsDisableSelf();
	}
}

rule ChickenWave1B
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(5*PlayersActive, "Toxotes", 1900, 1700);
		xsEnableRule("ChickenWave1C");
		xsDisableSelf();
	}
}

rule ChickenWave1C
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(5*PlayersActive, "Toxotes", 1900, 1700);
		R5Wave(5*PlayersActive, "Hoplite", 1800, 1600);
		xsEnableRule("ChickenWave1D");
		xsDisableSelf();
	}
}

rule ChickenWave1D
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(8*PlayersActive, "Hoplite", 1900, 1600);
		xsEnableRule("ChickenWave1E");
		xsDisableSelf();
	}
}

rule ChickenWave1E
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(8*PlayersActive, "Toxotes", 1900, 1600);
		xsEnableRule("ChickenWave1F");
		xsDisableSelf();
		for(p = 1; < cNumberNonGaiaPlayers){
			trModifyProtounit(ChickenProto, p, 5, 1);
			ColouredChatToPlayer(p, "1,0.5,0", "<u>Relic hold capacity increased!</u>");
		}
		ChickenLevel = 2;
		playSound("ageadvance.wav");
	}
}

rule ChickenWave1F
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(5*PlayersActive, "Huskarl", 2000, 1700);
		xsEnableRule("ChickenWave1G");
		xsDisableSelf();
	}
}

rule ChickenWave1G
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(5*PlayersActive, "Toxotes", 1900, 1600);
		R5Wave(5*PlayersActive, "Huskarl", 2100, 1800);
		xsEnableRule("ChickenWave1H");
		xsDisableSelf();
	}
}

rule ChickenWave1H
inactive
highFrequency
{
	if (trTime() > cActivationTime + 30) {
		R5Wave(8*PlayersActive, "Huskarl", 2500, 2000);
		//xsEnableRule("ChickenWave1G");
		xsDisableSelf();
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
	}
}
