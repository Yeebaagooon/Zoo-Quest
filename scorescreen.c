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
	characterDialog(ActName(Stage) + " - " + StageRequirement + " percent required to advance", "", ActIcon(Stage));
	StageScore = 41;
	//Current req is 40
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
		GlobalTimerMS = trTimeMS()+70;
		trQuestVarModify("ScoreCheck", "+", 1);
		if (iModulo(2, 1*trQuestVarGet("ScoreCheck")) == 0) { //if is divisble by 2
			xDatabaseNext(dDots);
			if(xGetInt(dDots, xPercent) <= StageScore){
				trUnitSelectClear();
				xUnitSelect(dDots, xUnitID);
				trUnitHighlight(10000, false);
			}
			if((1*trQuestVarGet("ScoreCheck") == StageRequirement) && (StageScore >= StageRequirement)){
				trUnitSelectByQV("PercentMark");
				trUnitChangeProtoUnit("Implode Sphere Effect");
				trUnitSelectByQV("PercentMark");
				trDamageUnitPercent(100);
				playSoundCustom("fanfare.wav", "\Yeebaagooon\Zoo Quest\Skillpoint.mp3");
			}
			if(1*trQuestVarGet("ScoreCheck") >= StageScore){
				xsDisableSelf();
				trDelayedRuleActivation("DoScoreEnd");
				int temp = trGetNextUnitScenarioNameNumber();
				UnitCreate(0, "Dwarf", 62, 20+StageScore, 0);
				trUnitSelectClear();
				trUnitSelect(""+temp);
				trUnitChangeProtoUnit("Tremor");
				temp = trGetNextUnitScenarioNameNumber();
				if(StageScore >= StageRequirement){
					UnitCreate(GreenText(), "Dwarf", 62, 20+StageScore, 0);
				}
				if(StageScore < StageRequirement){
					UnitCreate(RedText(), "Dwarf", 62, 20+StageScore, 0);
				}
				trUnitSelectClear();
				trUnitSelect(""+temp);
				trUnitChangeProtoUnit("Flag");
				trUnitSelectClear();
				trUnitSelect(""+temp);
				trUnitSetAnimationPath("0,1,0,0,0,0");
			}
		}
		characterDialog(ActName(Stage) + " - " + StageRequirement + " percent required to advance", ""+1*trQuestVarGet("ScoreCheck") + " percent complete", ActIcon(Stage));
	}
}

rule DoScoreEnd
inactive
highFrequency
{
	xsDisableSelf();
	if(StageScore >= StageRequirement){
		characterDialog(ActName(Stage) + " - Stage Passed", ""+StageScore + " percent complete", ActIcon(Stage));
	}
	else if(StageScore < StageRequirement){
		characterDialog(ActName(Stage) + " - Stage Failed", ""+StageScore + "/" + StageRequirement + " percent complete", ActIcon(Stage));
	}
}
