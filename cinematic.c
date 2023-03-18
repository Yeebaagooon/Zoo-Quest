void CineGo(int unused = 0){
	xsEnableRule("RemoveCineTimers");
	xsEnableRule("Cine_START");
	xsDisableRule("SkipCine");
}

rule BuildCineScene
inactive
highFrequency
{
	int temp = 0;
	trRenderSky(true, "SkySunset");
	clearMap("black", 0);
	trPaintTerrain(100,59,104,63,2,11);
	trPaintTerrain(90,40,110,86,0,1);
	trPaintTerrain(102,40,110,86,0,0);
	PaintAtlantisArea(101,60,103,62,0,53);
	trQuestVarSet("Yeeb", trGetNextUnitScenarioNameNumber());
	UnitCreate(0, "Cinematic Block", 101*2+2, 60*2+2, 270);
	trQuestVarSet("YeebEgg", trGetNextUnitScenarioNameNumber());
	UnitCreate(0, "Cinematic Block", 101*2+2, 60*2+2, 292);
	trQuestVarSet("YeebSFX1", trGetNextUnitScenarioNameNumber());
	UnitCreate(0, "Cinematic Block", 101*2+2, 60*2+2, 315);
	trQuestVarSet("YeebSFX2", trGetNextUnitScenarioNameNumber());
	UnitCreate(0, "Cinematic Block", 101*2+2, 60*2+2, 315);
	trChangeTerrainHeight(101,60,104,63, 14);
	trUnitSelectByQV("Yeeb");
	trUnitChangeProtoUnit("Pharaoh of Osiris XP");
	trUnitSelectByQV("YeebEgg");
	trUnitChangeProtoUnit("Phoenix Egg");
	trUnitSelectByQV("YeebEgg");
	trSetScale(2.5);
	trUnitSelectByQV("YeebSFX1");
	trUnitChangeProtoUnit("Imperial Examination");
	
	PaintAtlantisArea(95,60,97,62,0,53);
	UnitCreate(0, "Chicken", 95*2+2, 60*2+2, 270);
	trChangeTerrainHeight(95,60,98,63, 3);
	PaintAtlantisArea(97,53,99,55,0,53);
	UnitCreate(0, "Rhinocerous", 97*2+2, 53*2+2, 270);
	trChangeTerrainHeight(97,53,100,56, 6);
	PaintAtlantisArea(97,67,99,69,0,53);
	UnitCreate(0, "Crocodile", 97*2+2, 67*2+2, 270);
	trChangeTerrainHeight(97,67,100,70, 6);
	
	PaintAtlantisArea(92,48,94,50,0,53);
	UnitCreate(0, "Goat", 92*2+2, 48*2+2, 270);
	trChangeTerrainHeight(92,48,95,51, 5);
	PaintAtlantisArea(92,72,94,74,0,53);
	UnitCreate(0, "Gazelle", 92*2+2, 72*2+2, 270);
	trChangeTerrainHeight(92,72,95,75, 5);
	
	modifyProtounitAbsolute("Chicken", 0, 1,0);
	modifyProtounitAbsolute("Goat", 0, 1,0);
	modifyProtounitAbsolute("Crocodile", 0, 1,0);
	modifyProtounitAbsolute("Rhinocerous", 0, 1,0);
	modifyProtounitAbsolute("Gazelle", 0, 1,0);
	
	replaceTerrainAtMinSteepness("GrassB", "CliffGreekA", 2);
	trCameraCut(vector(109.101425,39.023849,122.402161), vector(0.932531,-0.361055,0.005034), vector(0.361050,0.932545,0.001949), vector(0.005398,0.000000,-0.999985));
	paintTrees2("GrassA", "Pine");
	paintTrees2("GrassB", "Bush Short");
	int b = 0;
	for(a = 0; < 20){
		b = b+1;
		if(b > cNumberNonGaiaPlayers){
			b = 0;
		}
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(b, "Dwarf", 230, 70+a*5, 0);
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeProtoUnit("Hesperides Tree");
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trSetSelectedScale(1,1.4,1);
	}
	for(a = 0; < 20){
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(0, "Dwarf", 220, 70+a*5, 90);
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeProtoUnit("Tamarisk Tree");
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trSetSelectedScale(1.4,1,1.4);
	}
	temp = trGetNextUnitScenarioNameNumber();
	UnitCreate(0, "Dwarf", 240, 80, 90);
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trUnitChangeProtoUnit("Elephant");
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trSetSelectedScale(2,2,2);
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trUnitMoveToPoint(230,1,180,-1,false);
	trSetObscuredUnits(false);
	SkipRequired = PlayersActive-1;
	if(PlayersActive == 1){
		SkipRequired = PlayersActive;
	}
	trSetCounterDisplay("</color>Votes to skip: " + 1*trQuestVarGet("SkipVotes") +"/" + SkipRequired);
	trCounterAddTime("cdcine", 13, 0, "<color={PlayerColor("+ cNumberNonGaiaPlayers +")}>Cinematic begins", 46);
	for(p=1 ; < cNumberNonGaiaPlayers){
		PlayerChoice(p, "Skip Cinematic?", "Yes", 3, "No", -1, 12900);
	}
	xsEnableRule("SkipCine");
	xsDisableSelf();
}

rule SkipCine
inactive
highFrequency
{
	if(1*trQuestVarGet("SkipVotes") >= SkipRequired){
		xsEnableRule("RemoveCineTimers");
		xsDisableSelf();
		xsDisableRule("Cine_START");
		xsEnableRule("CineStartSkip");
		SkipRequired = 47;
		trSetObscuredUnits(true);
	}
}

rule RemoveCineTimers
inactive
highFrequency
{
	trCounterAbort("cdcine");
	trClearCounterDisplay();
	xsDisableSelf();
	xsDisableRule("SkipCine");
}

rule Cine_START
inactive
highFrequency
{
	xsEnableRule("RemoveCineTimers");
	trLetterBox(true);
	trSetFogAndBlackmap(false,false);
	trRenderSky(true, "SkyBlue");
	trSetObscuredUnits(false);
	createCinematicMap();
	replaceTerrainAboveHeightMax("GaiaCreepA", "GrassB", 0.0);
	replaceTerrainAboveHeightMax("CoralA", "GrassB", 0.0);
	createCameraTrack(5000);
	trCameraCut(vector(-4.191484,31.823811,-23.344259), vector(0.512498,-0.420865,0.748477), vector(0.237777,0.907123,0.347260), vector(0.825111,-0.000000,-0.564971));
	addCameraTrackWaypoint();
	trCameraCut(vector(-23.063557,31.823811,-1.844474), vector(0.808599,-0.420865,0.411146), vector(0.375154,0.907123,0.190752), vector(0.453241,-0.000001,-0.891388));
	addCameraTrackWaypoint();
	trCameraCut(vector(-29.122383,31.823811,19.313332), vector(0.903661,-0.420865,0.079180), vector(0.419259,0.907123,0.036735), vector(0.087286,-0.000001,-0.996183));
	addCameraTrackWaypoint();
	playCameraTrack();
	characterDialog("Yeebaagooon", "In Zoo Quest, you will play as various animals over five acts.", "icons\special e son of osiris icon 64");
	xsDisableSelf();
	xsEnableRule("Cine_002");
	trFadeOutAllSounds(3);
	trFadeOutMusic(3);
	playSound("\music\interface\gank sneakin'.mp3");
}

rule Cine_002
inactive
highFrequency
{
	if (trTime() > cActivationTime + 5) {
		createCameraTrack(12000);
		trCameraCut(vector(-29.122383,31.823811,19.313332), vector(0.903661,-0.420865,0.079180), vector(0.419259,0.907123,0.036735), vector(0.087286,-0.000001,-0.996183));
		addCameraTrackWaypoint();
		trCameraCut(vector(8.596761,49.823807,6.115839), vector(0.864105,-0.359189,0.352569), vector(0.332572,0.933265,0.135694), vector(0.377780,-0.000001,-0.925895));
		addCameraTrackWaypoint();
		trCameraCut(vector(137.518402,63.803802,23.713142), vector(0.347379,-0.359189,0.866205), vector(0.133698,0.933265,0.333379), vector(0.928145,-0.000001,-0.372219));
		addCameraTrackWaypoint();
		trCameraCut(vector(191.856720,63.803802,148.407471), vector(0.300016,-0.591888,0.748104), vector(0.220313,0.806020,0.549357), vector(0.928145,-0.000001,-0.372219));
		addCameraTrackWaypoint();
		playCameraTrack();
		characterDialog("Yeebaagooon", "In each act, there will be specific objectives relating to your animal.", "icons\special e son of osiris icon 64");
		xsDisableSelf();
		xsEnableRule("Cine_025");
		xsEnableRule("Cine_003");
	}
}

rule Cine_0025
inactive
highFrequency
{
	if (trTime() > cActivationTime + 3) {
		//Objectives display here
		xsDisableSelf();
	}
}

rule Cine_003
inactive
highFrequency
{
	if (trTime() > cActivationTime + 5) {
		characterDialog("Yeebaagooon", "When you explore the map, you will find an ice zone with a flag, like this one.", "icons\special e son of osiris icon 64");
		xsDisableSelf();
		xsEnableRule("Cine_004");
	}
}

rule Cine_004
inactive
highFrequency
{
	if (trTime() > cActivationTime + 5) {
		characterDialog("Yeebaagooon", "This is the extraction zone.", "icons\special e son of osiris icon 64");
		xsDisableSelf();
		xsEnableRule("Cine_005");
	}
}

rule Cine_005
inactive
highFrequency
{
	if (trTime() > cActivationTime + 3) {
		characterDialog("Yeebaagooon", "When all surviving players are here, the act will end.", "icons\special e son of osiris icon 64");
		xsDisableSelf();
		xsEnableRule("Cine_006");
	}
}

rule Cine_006
inactive
highFrequency
{
	if (trTime() > cActivationTime + 4) {
		characterDialog("Yeebaagooon", "Depending on your performance, you then advance to the next act.", "icons\special e son of osiris icon 64");
		xsEnableRule("Cine_007");
		xsDisableSelf();
	}
}

rule Cine_007
inactive
highFrequency
{
	if (trTime() > cActivationTime + 5) {
		characterDialog("Yeebaagooon", "You may also find some secrets when you are exploring.", "icons\special e son of osiris icon 64");
		xsDisableSelf();
		createCameraTrack(12000);
		trCameraCut(vector(199.871262,13.335322,178.271561), vector(-0.932545,-0.354518,0.068379), vector(-0.353569,0.935049,0.025925), vector(0.073129,0.000001,0.997322));
		addCameraTrackWaypoint();
		trCameraCut(vector(194.912292,13.335322,165.898911), vector(-0.721632,-0.354518,0.594612), vector(-0.273603,0.935049,0.225443), vector(0.635915,0.000000,0.771759));
		addCameraTrackWaypoint();
		trCameraCut(vector(182.261459,13.335322,158.322586), vector(-0.183567,-0.354518,0.916853), vector(-0.069599,0.935049,0.347619), vector(0.980540,0.000000,0.196319));
		addCameraTrackWaypoint();
		trCameraCut(vector(178.096512,13.335322,170.524948), vector(0.158200,-0.679734,0.716195), vector(0.146612,0.733459,0.663734), vector(0.976462,-0.000000,-0.215690));
		addCameraTrackWaypoint();
		playCameraTrack();
		xsEnableRule("Cine_008");
	}
}

rule Cine_008
inactive
highFrequency
{
	if (trTime() > cActivationTime + 4) {
		characterDialog("Yeebaagooon", "Such as these chests.", "icons\special e son of osiris icon 64");
		xsEnableRule("Cine_009");
		xsDisableSelf();
	}
}

rule Cine_009
inactive
highFrequency
{
	if (trTime() > cActivationTime + 3) {
		characterDialog("Yeebaagooon", "They will grant you a stat bonus when you walk up to them.", "icons\special e son of osiris icon 64");
		xsEnableRule("Cine_010");
		xsDisableSelf();
	}
}

rule Cine_010
inactive
highFrequency
{
	if (trTime() > cActivationTime + 4) {
		characterDialog("Yeebaagooon", "There are also minigames in each act.", "icons\special e son of osiris icon 64");
		xsEnableRule("Cine_011");
		createCameraTrack(12000);
		trCameraCut(vector(45.501041,68.355316,11.553124), vector(0.220021,-0.713443,0.665275), vector(0.224017,0.700714,0.677360), vector(0.949425,0.000001,-0.313995));
		addCameraTrackWaypoint();
		trCameraCut(vector(99.999657,68.355316,19.155584), vector(-0.393685,-0.713443,0.579665), vector(-0.400838,0.700714,0.590194), vector(0.827249,0.000001,0.561836));
		addCameraTrackWaypoint();
		playCameraTrack();
		xsDisableSelf();
	}
}

rule Cine_011
inactive
highFrequency
{
	if (trTime() > cActivationTime + 3) {
		characterDialog("Yeebaagooon", "You cannot die in a minigame.", "icons\special e son of osiris icon 64");
		xsDisableSelf();
		xsEnableRule("Cine_012");
	}
}

rule Cine_012
inactive
highFrequency
{
	if (trTime() > cActivationTime + 2) {
		characterDialog("Yeebaagooon", "Complete them for bonus points.", "icons\special e son of osiris icon 64");
		xsDisableSelf();
		xsEnableRule("Cine_013");
	}
}

rule Cine_013
inactive
highFrequency
{
	if (trTime() > cActivationTime + 3) {
		characterDialog("Yeebaagooon", "A final cautionary note - watch out for poachers.", "icons\special e son of osiris icon 64");
		createCameraTrack(3800);
		trCameraCut(vector(44.548786,68.355316,86.877846), vector(0.095280,-0.713443,0.694206), vector(0.097010,0.700714,0.706816), vector(0.990712,0.000000,-0.135975));
		addCameraTrackWaypoint();
		trCameraCut(vector(46.055031,37.558235,109.633667), vector(0.113962,-0.545501,0.830326), vector(0.074174,0.838110,0.540435), vector(0.990712,0.000000,-0.135975));
		addCameraTrackWaypoint();
		trCameraCut(vector(48.570820,11.835312,137.803925), vector(0.125484,-0.385176,0.914272), vector(0.052374,0.922843,0.381599), vector(0.990712,0.000000,-0.135975));
		addCameraTrackWaypoint();
		playCameraTrack();
		xsDisableSelf();
		xsEnableRule("Cine_014");
	}
}

rule Cine_014
inactive
highFrequency
{
	if (trTime() > cActivationTime + 4) {
		characterDialog("Yeebaagooon", "If you're ever unsure what to do - type 'HELP'.", "icons\special e son of osiris icon 64");
		xsDisableSelf();
		xsEnableRule("Cine_END");
		int temp = trGetNextUnitScenarioNameNumber()-1;
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeInArea(0,0,"Great Box","Cinematic Block", 600);
	}
}

rule Cine_END
inactive
highFrequency
{
	if (trTime() > cActivationTime + 4) {
		xsDisableSelf();
		xsDisableRule("TutorialLoops");
		xsEnableRule("BuildDeerArea");
		trUIFadeToColor(0,0,0,1,1,true);
		Stage = 1;
		characterDialog(ActName(Stage), " ", ActIcon(Stage));
		trSetFogAndBlackmap(true,true);
		trSetObscuredUnits(true);
		trDelayedRuleActivation("ResetBlackmap");
		trFadeOutAllSounds(3);
		trFadeOutMusic(3);
	}
}


//===========================================
//=============chicken cine==================
//===========================================


rule C_Cine_000
inactive
highFrequency
{
	if (trTime() > cActivationTime + 1) {
		characterDialog("Chicken Gameplay", "Build towers to defend yourselves against the hordes.", "icons\animal chicken icon 64");
		xsDisableSelf();
		xsEnableRule("C_Cine_001");
	}
}

rule C_Cine_001
inactive
highFrequency
{
	if (trTime() > cActivationTime + 4) {
		xSetPointer(dPlayerData, 1);
		characterDialog("Chicken Gameplay", "You can only build " + xGetInt(dPlayerData, xTowerLimit) + ", this may increase later.", "icons\animal chicken icon 64");
		xsDisableSelf();
		xsEnableRule("C_Cine_002");
	}
}

rule C_Cine_002
inactive
highFrequency
{
	if (trTime() > cActivationTime + 4) {
		characterDialog("Chicken Gameplay", "Relics give stat bonuses, you can only hold one at the start.", "icons\animal chicken icon 64");
		xsDisableSelf();
		xsEnableRule("C_Cine_003");
	}
}

rule C_Cine_003
inactive
highFrequency
{
	if (trTime() > cActivationTime + 4) {
		characterDialog("Chicken Powers", "Unwanted relics can be turned into landmines with 'R'", "icons\animal chicken icon 64");
		xsDisableSelf();
		xsEnableRule("C_Cine_004");
	}
}

rule C_Cine_004
inactive
highFrequency
{
	if (trTime() > cActivationTime + 4) {
		characterDialog("Chicken Powers", "Use 'E' to temporarily allow towers to fire two arrows", "icons\animal chicken icon 64");
		xsDisableSelf();
		xsEnableRule("C_Cine_005");
	}
}

rule C_Cine_005
inactive
highFrequency
{
	if (trTime() > cActivationTime + 4) {
		characterDialog("Chicken Powers", "E will recharge after use.", "icons\animal chicken icon 64");
		xsDisableSelf();
		xsEnableRule("ChickenLanding");
	}
}
