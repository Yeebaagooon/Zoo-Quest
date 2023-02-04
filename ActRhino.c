rule BuildRhinoArea
highFrequency
inactive
{
	if (trTime() > cActivationTime + 1) {
		//createForestArea();
		createStartTown();
		xsDisableSelf();
		//replaceTerrainAboveHeightMax("ForestFloorPine", "GrassB", 0.0);
		trLetterBox(false);
		trUIFadeToColor(0,0,0,100,800,false);
		uiZoomToProto(""+RhinoProto);
		uiLookAtProto(""+RhinoProto);
		trDelayedRuleActivation("ResetBlackmap");
		trDelayedRuleActivation("RhinoActLoops");
		/*trDelayedRuleActivation("DeerMinigameDetect");
		trDelayedRuleActivation("DeerLeave");
		trDelayedRuleActivation("TEST");
		trDelayedRuleActivation("DeerAllDead");
		trDelayedRuleActivation("PoacherTimer");
		trDelayedRuleActivation("DeerEndZoneSee");
		xsEnableRule("DeerPoacherMovement");*/
		trSetCounterDisplay("<color={PlayerColor(2)}>Fencing destroyed: 0 / " + BerryTarget);
		ColouredIconChat("1,0.5,0", ActIcon(Stage), "<u>" + ActName(Stage) + "</u>");
		ColouredIconChat("0.0,0.8,0.2", "icons\world berry bush icon 64", "Eat at least the required number of berries");
		trChatSend(0, "In each act you need to find and move to the extraction zone.");
		trChatSend(0, "It is a ring of ice terrain.");
		trChatSend(0, "When all players are dead or in the zone, the act ends.");
		trChatSend(0, "Make sure to explore, as higher act scores help you out later.");
		xsEnableRule("PlayMusic");
	}
}
