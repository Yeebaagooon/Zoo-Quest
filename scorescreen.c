void CreateDot(int x = 0, int z = 0){
	int temp = trGetNextUnitScenarioNameNumber();
	UnitCreate(0, "Dwarf", x, z, 0);
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trUnitChangeProtoUnit("Rock Granite Small");
	trUnitSetVariation(temp, 1);
	xAddDatabaseBlock(dDots, true);
	xSetInt(dDots, xUnitID, temp);
	xSetInt(dDots, xPercent, z-20);
}

void SetPercentRequired(int pe = 0){
	int temp = trGetNextUnitScenarioNameNumber();
	UnitCreate(0, "Dwarf", 62, 20+pe, 0);
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trUnitChangeProtoUnit("Spy Eye");
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trMutateSelected(kbGetProtoUnitID("Outpost"));
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trSetSelectedScale(0,0,0);
	trQuestVarSet("PercentMark", temp);
}

rule ScoreScreenStart
highFrequency
inactive
{
	xsDisableSelf();
	trLetterBox(true);
	trUIFadeToColor(0,0,0,1000,1,true);
	trFadeOutAllSounds(3);
	trFadeOutMusic(3);
	xsEnableRule("DestroyStuff");
	characterDialog("Act I - Deer", "40 percent required to advance.", "icons\animal gazelle icon 64");
	StageScore = 100;
}

rule DestroyStuff
highFrequency
inactive
{
	if (trTime() > cActivationTime + 1) {
		xsDisableSelf();
		for(x=DontDestroyBelow ; < trGetNextUnitScenarioNameNumber()){
			trUnitSelectClear();
			trUnitSelect(""+x);
			trUnitDestroy();
		}
		clearMap("black", 5.0);
		refreshPassability();
		xsEnableRule("CutToScore");
	}
}

rule CutToScore
highFrequency
inactive
{
	xsDisableSelf();
	trLetterBox(false);
	trUIFadeToColor(0,0,0,1000,1,false);
	PaintAtlantisArea(30,10,32,61,5,4);
	trCameraCut(vector(171.726913,123.743729,70.647377), vector(-0.707094,-0.707106,0.004380), vector(-0.707094,0.707106,0.004380), vector(0.006194,0.000000,0.999981));
	for(z=1 ; < 51){
		CreateDot(63,20+z*2);
	}
	SetPercentRequired(StageRequirement);
	trQuestVarSet("ScoreCheck", 0);
	xsEnableRule("DoScore");
}

rule DoScore
highFrequency
inactive
{
	int TimerTile = trTimeMS();
	if(TimerTile > GlobalTimerMS){
		GlobalTimerMS = trTimeMS()+100;
		xDatabaseNext(dDots);
		trQuestVarModify("ScoreCheck", "+", 2);
		if(xGetInt(dDots, xPercent) <= StageScore){
			trUnitSelectClear();
			xUnitSelect(dDots, xUnitID);
			trUnitHighlight(10000, false);
		}
		if(1*trQuestVarGet("ScoreCheck") == StageRequirement){
			trUnitSelectByQV("PercentMark");
			trUnitChangeProtoUnit("Lightning Sparks");
			playSoundCustom("fanfare.wav", "\Yeebaagooon\Zoo Quest\Skillpoint.mp3");
		}
		if(1*trQuestVarGet("ScoreCheck") >= StageScore){
			xsDisableSelf();
			int temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(0, "Dwarf", 62, 20+StageScore, 0);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Tremor");
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(0, "Dwarf", 62, 20+StageScore, 0);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Flag");
			trUnitSetVariation(temp, 1);
		}
	}
}