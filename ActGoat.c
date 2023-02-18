rule BuildGoatArea
highFrequency
inactive
{
	if (trTime() > cActivationTime + 1) {
		TutorialMode = false;
		createGoatArea();
		xsDisableSelf();
		//replaceTerrainAboveHeightMax("ForestFloorPine", "GrassB", 0.0);
		trLetterBox(false);
		trUIFadeToColor(0,0,0,100,800,false);
		uiZoomToProto(""+GoatProto);
		uiLookAtProto(""+GoatProto);
		trDelayedRuleActivation("ResetBlackmap");
		//	trDelayedRuleActivation("RhinoMinigameDetect");
		trDelayedRuleActivation("TEST");
		trDelayedRuleActivation("GoatEndZoneSee");
		//trDelayedRuleActivation("RhinoAllDead");
		//trDelayedRuleActivation("PoacherTimer");
		//xsEnableRule("RhinoPoacherMovement");
		//trSetCounterDisplay("<color={PlayerColor(2)}>Fencing destroyed: "+FencesDone+"/8");
		ColouredIconChat("1,0.5,0", ActIcon(Stage), "<u>" + ActName(Stage) + "</u>");
		ColouredIconChat("0.0,0.8,0.2", "icons\icon building wooden fence 64", "Destroy enough fences.");
		ColouredChat("0.0,0.8,0.2", "Each long fence segment needs at least one break.");
		xsEnableRule("PlayMusic");
		//SpawnRhinoPoacher(xsMax(PlayersActive,3));
		//SpawnRhinoSuperPoacher(1);
		PlayersDead = 0;
		timediff = trTimeMS();
		timelast = trTimeMS();
		//trDelayedRuleActivation("RhinoActLoops");
	}
}

rule GoatEndZoneSee
inactive
highFrequency
{
	for(p=1 ; < cNumberNonGaiaPlayers){
		trUnitSelectByQV("P"+p+"Unit");
		if(trUnitDistanceToUnit(""+FlagUnitID) < 26){
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
