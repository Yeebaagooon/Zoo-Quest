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
	}
}

rule ChickenWave1Go
inactive
highFrequency
{
	int temp = 0;
	if(ActPart == 2){
		int deploy = 15;
		while(deploy > 0){
			trQuestVarSetFromRand("temp", 1, xGetDatabaseCount(dShore));
			xSetPointer(dShore, 1*trQuestVarGet("temp"));
			tempV = xGetVector(dShore, xShoreLoc);
			xSetInt(dShore, xShoreDist, distanceBetweenVectors(xGetVector(dShore, xShoreLoc), MapCentre, true));
			if((xGetInt(dShore, xShoreDist) < 1800) && (xGetInt(dShore, xShoreDist) > 1600)){
				temp = trGetNextUnitScenarioNameNumber();
				UnitCreate(cNumberNonGaiaPlayers, "Hoplite", xsVectorGetX(tempV), xsVectorGetZ(tempV), 0);
				trUnitSelectClear();
				trUnitSelect(""+temp);
				deploy = deploy-1;
				xAddDatabaseBlock(dEnemies, true);
				xSetInt(dEnemies, xUnitID, temp);
				trUnitMoveToPoint(xsVectorGetX(MapCentre),1,xsVectorGetZ(MapCentre),-1,true);
			}
		}
		playSound("\cinematics\04_in\armyarrive.wav");
		xsDisableSelf();
	}
}
