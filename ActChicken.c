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
		PlayersDead = 0;
		timediff = trTimeMS();
		timelast = trTimeMS();
		//trDelayedRuleActivation("ChickenActLoops");
		for(p = 1 ; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			//xSetInt(dPlayerData, xCrocSize, 1);
			//xSetFloat(dPlayerData, xCrocNext, 5*xGetInt(dPlayerData, xCrocSize));
			trQuestVarSet("P"+p+"FountainMsg", 0);
			//limit
			modifyProtounitAbsolute("Tower", p, 10, 10);
			//build points = how many s to build
			modifyProtounitAbsolute("Tower", p, 4, 10);
			//limit
			modifyProtounitAbsolute("Armory", p, 10, 1);
			//build points = how many s to build
			modifyProtounitAbsolute("Armory", p, 4, 60);
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
		xsDisableSelf();
	}
}
