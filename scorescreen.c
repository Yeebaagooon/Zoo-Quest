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
	playSoundCustom("\cinematics\9_in\music.mp3", "\cinematics\9_in\music.mp3");
	StageScore = 0;
	float Extras = 0;
	float ExtrasGot = 0;
	int temp = 0;
	//Current req is 40
	if(Stage == 1){
		//[CALCULATE THE PERCENT COMPLETE]
		if(1*trQuestVarGet("BerriesEaten") >= BerryTarget){
			//passing score
			StageScore = StageRequirement;
			//debugLog("Pass, score set to " + StageScore);
		}
		else{
			//failed main goal
			StageScore = StageRequirement*(trQuestVarGet("BerriesEaten")/BerryTarget);
			//debugLog("Fail, score set to " + StageScore);
		}
		//[CALCULATION PENALTIES]
		
		StageScore = StageScore - (PlayersDead*3);
		//[ADD ON BONUSES, ADD EXTRAS FOR WEIGHTING AND EXTRASGOT IF A PLAYER HAS IT]
		//[BERRIES,CHESTS,LOG JUMPS, MINIGAME FOUND, MINIGAME COMPLETE]
		Extras = Extras + (BerryTotal - BerryTarget);
		ExtrasGot = ExtrasGot + (trQuestVarGet("BerriesEaten") - BerryTarget);
		//debugLog("Extra berries = " + (trQuestVarGet("BerriesEaten") - BerryTarget) + " out of " + (BerryTotal - BerryTarget));
		Extras = Extras + ChestsTotal*2;
		ExtrasGot = ExtrasGot + ChestsFound*2;
		//debugLog("Chests = " + ChestsFound + " out of " + ChestsTotal);
		Extras = Extras + PlayersActive;
		for(a = 1 ; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, a);
			if(playerIsPlaying(a) == true){
				ExtrasGot = ExtrasGot + xGetInt(dPlayerData, xLogJumps);
				//debugLog("Log jumping player added " + xGetInt(dPlayerData, xLogJumps));
			}
		}
		Extras = Extras + 5;
		if(MinigameFound == true){
			ExtrasGot = ExtrasGot + 5;
		}
		if(MinigameWins > PlayersActive){
			MinigameWins = PlayersActive;
		}
		Extras = Extras + PlayersActive*2;
		ExtrasGot = ExtrasGot + MinigameWins*2;
		if(ExtrasGot > 0){
			float calc = ExtrasGot/Extras;
			StageScore = StageScore + (calc*(100-StageRequirement));
			//debugLog("ExtrasGot = " + ExtrasGot);
			//debugLog("Extras = " + Extras);
			//debugLog("Added to score = " + calc);
		}
		if((ExtrasGot >= Extras) && (Extras > 0)){
			StageScore = 100;
		}
		if(ExtrasGot > Extras){
			trChatSend(0, "ERROR MORE THAN 100 PERCENT COMPLETE");
		}
		
		//debugLog("SCORE = " + StageScore);
	}
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
		NewDestroyNumber = trGetNextUnitScenarioNameNumber()-1;
	}
}

rule CutToScore
highFrequency
inactive
{
	xsDisableSelf();
	//trLetterBox(false);
	trSetFogAndBlackmap(false, false);
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
		characterDialog(ActName(Stage) + " - Act Passed", ""+StageScore + " percent complete", ActIcon(Stage));
		xsEnableRule("PassAct1");
	}
	else if(StageScore < StageRequirement){
		characterDialog(ActName(Stage) + " - Act Failed", ""+StageScore + "/" + StageRequirement + " percent complete", ActIcon(Stage));
		xsEnableRule("LoseToScore");
	}
}

rule LoseToScore
highFrequency
inactive
{
	if (trTime() > cActivationTime + 3) {
		xsDisableSelf();
		xsEnableRule("EndGame");
		trLetterBox(false);
	}
}

rule EndGame
highFrequency
inactive
{
	if (trTime() > cActivationTime + 1) {
		trShowWinLose("You failed to progress", "xlose.wav");
		for(p=1 ; < cNumberNonGaiaPlayers){
			trSetPlayerDefeated(p);
		}
		xsDisableSelf();
		trEndGame();
	}
}

rule TempEndGame
highFrequency
inactive
{
	if (trTime() > cActivationTime + 1) {
		if(QuickStart == 0){
			trShowWinLose("Thats all so far...", "xwin.wav");
			for(p=1 ; < cNumberNonGaiaPlayers){
				trSetPlayerWon(p);
			}
			xsDisableSelf();
			trEndGame();
		}
		else{
			clearMap("black", 5);
			xsEnableRule("TutorialTerrainRhino");
			for(x=NewDestroyNumber ; < trGetNextUnitScenarioNameNumber()){
				trUnitSelectClear();
				trUnitSelect(""+x);
				trUnitDestroy();
			}
			xsDisableSelf();
		}
	}
}

rule PassAct1
highFrequency
inactive
{
	if (trTime() > cActivationTime + 3) {
		xsDisableSelf();
		trLetterBox(false);
		xsEnableRule("TempEndGame");
		xsEnableRule("ResetInts");
	}
}

rule ResetInts
highFrequency
inactive
{
	StageRequirement = 0;
	StageScore = 0;
	PlayersDead = 0;
	ChestsFound = 0;
	BerryTotal = 0;
	ChestsTotal = 0;
	BerryTarget = 0;
	PlayersMinigaming = 0;
	PlayersReadyToLeave = 0;
	MinigameWins = 0;
	InMinigame = false;
	MinigameFound = false;
	for(p=1 ; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		if(playerIsPlaying(p)){
			xSetBool(dPlayerData, xPlayerDead, false);
			xSetBool(dPlayerData, xReadyToLeave, false);
			xSetBool(dPlayerData, xStopDeath, false);
			xSetVector(dPlayerData, xVectorHold, vector(0,0,0));
			xSetInt(dPlayerData, xTeleportDue, 0);
		}
	}
	xResetDatabase(dTemp);
	xResetDatabase(dLogs);
	xsDisableSelf();
}
