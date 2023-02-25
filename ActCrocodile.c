rule BuildCrocArea
highFrequency
inactive
{
	if (trTime() > cActivationTime + 1) {
		TutorialMode = false;
		createCrocArea();
		xsDisableSelf();
		//replaceTerrainAboveHeightMax("ForestFloorPine", "GrassB", 0.0);
		trLetterBox(false);
		trUIFadeToColor(0,0,0,100,800,false);
		uiZoomToProto(""+CrocProto);
		uiLookAtProto(""+CrocProto);
		trDelayedRuleActivation("ResetBlackmap");
		//trDelayedRuleActivation("GoatMinigameDetect");
		trDelayedRuleActivation("TEST");
		//trDelayedRuleActivation("GoatEndZoneSee");
		//trDelayedRuleActivation("GoatAllDead");
		//trDelayedRuleActivation("GoatPoacherTimer");
		//xsEnableRule("GoatPoacherMovement");
		//trDelayedRuleActivation("GoatBonus");
		//trSetCounterDisplay("<color={PlayerColor(2)}>Fencing destroyed: "+FencesDone+"/8");
		ColouredIconChat("1,0.5,0", ActIcon(Stage), "<u>" + ActName(Stage) + "</u>");
		ColouredIconChat("0.0,0.8,0.2", "icons\building norse shrine icon 64", "Interract with shrines using W.");
		ColouredChat("0.0,0.8,0.2", "Eat flashing animals to grow in size.");
		ColouredChat("0.0,0.8,0.2", "Only flashing animals can be eaten!");
		xsEnableRule("PlayMusic");
		//SpawnRhinoPoacher(xsMax(PlayersActive,3));
		//SpawnRhinoSuperPoacher(1);
		PlayersDead = 0;
		timediff = trTimeMS();
		timelast = trTimeMS();
		//trDelayedRuleActivation("GoatActLoops");
		//SpawnGoatPoacher(2);
		modifyProtounitAbsolute("Throwing Axeman", cNumberNonGaiaPlayers, 55, 1);
		for(p = 1 ; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			//xSetInt(dPlayerData, xTimeout, trTimeMS()*2);
		}
		trQuestVarSet("NextPoacherSpawn", trTime()+220);
	}
}
