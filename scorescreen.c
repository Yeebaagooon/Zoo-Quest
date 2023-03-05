void CreateDot(int x = 0, int z = 0, bool bonus = false){
	int temp = trGetNextUnitScenarioNameNumber();
	UnitCreate(0, "Dwarf", x, z, 0);
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trUnitChangeProtoUnit("Rock Granite Small");
	trUnitSetVariation(temp, 1);
	xAddDatabaseBlock(dDots, true);
	xSetInt(dDots, xUnitID, temp);
	xSetInt(dDots, xPercent, z-20);
	if(bonus == true){
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(0, "Dwarf", x, z, 0);
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeProtoUnit("Spy Eye");
		trUnitSelectClear();
		trQuestVarModify("Bonus", "+", 1);
		trQuestVarSet("Bonus"+1*trQuestVarGet("Bonus")+"", temp);
		trUnitSelect(""+temp);
		if(1*trQuestVarGet("Bonus") == 2){
			trMutateSelected(kbGetProtoUnitID("Acid Pool"));
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitSetAnimationPath("0,1,1,0,0,0,0");
		}
		if(1*trQuestVarGet("Bonus") == 3){
			trMutateSelected(kbGetProtoUnitID("Hero Birth"));
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitSetAnimationPath("0,1,0,0,0,0,0");
		}
		if(1*trQuestVarGet("Bonus") == 1){
			trMutateSelected(kbGetProtoUnitID("Poison SFX"));
		}
	}
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
	float calc = 0;
	int temp = 0;
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
			calc = ExtrasGot/Extras;
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
	if(Stage == 2){
		//[CALCULATE THE PERCENT COMPLETE]
		if(PoachersDead >= PoachersTarget){
			//passing score
			StageScore = StageRequirement;
			//debugLog("Pass, score set to " + StageScore);
		}
		else{
			//failed main goal
			trQuestVarSet("temp", PoachersDead);
			StageScore = StageRequirement*(trQuestVarGet("temp")/PoachersTarget);
			//debugLog("Fail, score set to " + StageScore);
		}
		//[CALCULATION PENALTIES]
		
		StageScore = StageScore - (PlayersDead*4);
		//[ADD ON BONUSES, ADD EXTRAS FOR WEIGHTING AND EXTRASGOT IF A PLAYER HAS IT]
		//[CHESTS, UP TO 5 EXTRA POACHER DEATHS,]
		Extras = Extras + ChestsTotal*2;
		ExtrasGot = ExtrasGot + ChestsFound*2;
		//debugLog("Chests = " + ChestsFound + " out of " + ChestsTotal);
		
		Extras = Extras + 5;
		for(a=1 ; <= 5){
			if(PoachersDead >= PoachersTarget+a){
				ExtrasGot = ExtrasGot+1;
			}
		}
		Extras = Extras + 2;
		if(MinigameFound == true){
			ExtrasGot = ExtrasGot + 2;
		}
		Extras = Extras + 5;
		if(MinigameWins > 0){
			ExtrasGot = ExtrasGot + 5;
		}
		Extras = Extras +4;
		if(1*trQuestVarGet("RhinoSurvival") > 4){
			ExtrasGot = ExtrasGot+4;
		}
		else{
			ExtrasGot = ExtrasGot + 1*trQuestVarGet("RhinoSurvival");
		}
		Extras = Extras+2;
		ExtrasGot = ExtrasGot + 1*trQuestVarGet("RhinoBonuses");
		/*Extras = Extras + PlayersActive;
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
		}*/
		//Extras = Extras + PlayersActive*2;
		//ExtrasGot = ExtrasGot + MinigameWins*2;
		if(ExtrasGot > 0){
			calc = ExtrasGot/Extras;
			StageScore = StageScore + (calc*(100-StageRequirement));
			debugLog("ExtrasGot = " + ExtrasGot);
			debugLog("Extras = " + Extras);
			debugLog("Added to score = " + (calc*(100-StageRequirement)));
		}
		if((ExtrasGot >= Extras) && (Extras > 0)){
			StageScore = 100;
		}
		if(ExtrasGot > Extras){
			trChatSend(0, "ERROR MORE THAN 100 PERCENT COMPLETE");
		}
		
		//debugLog("SCORE = " + StageScore);
	}
	if(Stage == 3){
		//COPY FROM STAGE 2 BECAUSE THIS HAS SHRINE WEIGHTING AND IS MESSY
		//[CALCULATE THE PERCENT COMPLETE]
		//int ShrineTarget = ShrinesMax-2;
		debugLog("Shrines max = " + ShrinesMax);
		if(ShrinesGot >= ShrineTarget){
			//passing score
			StageScore = StageRequirement;
			debugLog("Pass, score set to " + StageScore);
			ExtrasGot = ExtrasGot + (ShrinesGot - ShrineTarget)*3;
		}
		else{
			//failed main goal
			trQuestVarSet("temp", ShrinesGot);
			StageScore = StageRequirement*(trQuestVarGet("temp")/ShrinesMax);
			debugLog("Fail, score set to " + StageScore);
		}
		//[CALCULATION PENALTIES]
		Extras = Extras + (ShrinesMax - ShrineTarget)*3;
		StageScore = StageScore - (PlayersDead*6);
		//[ADD ON BONUSES, ADD EXTRAS FOR WEIGHTING AND EXTRASGOT IF A PLAYER HAS IT]
		//[CHESTS, UP TO 5 EXTRA POACHER DEATHS,]
		Extras = Extras + ChestsTotal*2;
		ExtrasGot = ExtrasGot + ChestsFound*2;
		debugLog("Chests = " + ChestsFound + " out of " + ChestsTotal);
		
		Extras = Extras + 2;
		if(MinigameFound == true){
			ExtrasGot = ExtrasGot + 2;
		}
		Extras = Extras + (PlayersActive*5);
		if(MinigameWins > 0){
			ExtrasGot = ExtrasGot + MinigameWins*5;
		}
		
		if(ExtrasGot > 0){
			calc = ExtrasGot/Extras;
			StageScore = StageScore + (calc*(100-StageRequirement));
			debugLog("ExtrasGot = " + ExtrasGot);
			debugLog("Extras = " + Extras);
			debugLog("Added to score = " + (calc*(100-StageRequirement)));
		}
		if((ExtrasGot >= Extras) && (Extras > 0)){
			StageScore = 100;
		}
		if(ExtrasGot > Extras){
			trChatSend(0, "ERROR MORE THAN 100 PERCENT COMPLETE");
		}
		//debugLog("SCORE = " + StageScore);
	}
	if(Stage == 4){
		//[CALCULATE THE PERCENT COMPLETE]
		if(CrocProgress >= CrocTarget){
			//passing score
			StageScore = StageRequirement;
			debugLog("Pass, score set to " + StageScore);
		}
		else{
			//failed main goal
			trQuestVarSet("temp", CrocProgress);
			StageScore = StageRequirement*(trQuestVarGet("temp")/CrocTarget);
			StageScore = StageScore-6;
			debugLog("Fail, score set to " + StageScore);
		}
		//[CALCULATION PENALTIES]
		
		StageScore = StageScore - (PlayersDead*6);
		//[ADD ON BONUSES, ADD EXTRAS FOR WEIGHTING AND EXTRASGOT IF A PLAYER HAS IT]
		//[CHESTS, UP TO 5 EXTRA POACHER DEATHS,]
		Extras = Extras + ChestsTotal*2;
		ExtrasGot = ExtrasGot + ChestsFound*2;
		//debugLog("Chests = " + ChestsFound + " out of " + ChestsTotal);
		
		Extras = Extras+3;
		if(MinigameFound == true){
			ExtrasGot = ExtrasGot + 3;
		}
		Extras = Extras + (PlayersActive*3);
		if(MinigameWins > 0){
			ExtrasGot = ExtrasGot + (MinigameWins*3);
		}
		
		//Extras = Extras + PlayersActive*2;
		//ExtrasGot = ExtrasGot + MinigameWins*2;
		if(ExtrasGot > 0){
			calc = ExtrasGot/Extras;
			StageScore = StageScore + (calc*(100-StageRequirement));
			debugLog("ExtrasGot = " + ExtrasGot);
			debugLog("Extras = " + Extras);
			debugLog("Added to score = " + (calc*(100-StageRequirement)));
		}
		Extras = Extras+10;
		if(PoachersDead*2 > PoachersTarget){
			ExtrasGot = ExtrasGot+10;
		}
		/*if((ExtrasGot >= Extras) && (Extras > 0)){
			StageScore = 100;
		}*/
		//This make score 100 even if player fails
		if(StageScore < 0){
			StageScore = 2;
		}
		if(StageScore > 100){
			StageScore = 100;
		}
		if(ExtrasGot > Extras){
			trChatSend(0, "ERROR MORE THAN 100 PERCENT COMPLETE");
		}
		debugLog("Poachers total = " + PoachersTarget);
		debugLog("Poachers killed = " + PoachersDead);
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
	trQuestVarSet("Bonus", 0);
	trQuestVarSet("Bonus1", 0);
	trQuestVarSet("Bonus2", 0);
	trQuestVarSet("Bonus3", 0);
	if(Stage == 1){
		trQuestVarSet("ScoreBonus1", 60);
		trQuestVarSet("ScoreBonus2", 80);
		trQuestVarSet("ScoreBonus3", 100);
	}
	if(Stage == 2){
		trQuestVarSet("ScoreBonus1", 60);
		trQuestVarSet("ScoreBonus2", 80);
		trQuestVarSet("ScoreBonus3", 100);
	}
	if(Stage == 3){
		trQuestVarSet("ScoreBonus1", 70);
		trQuestVarSet("ScoreBonus2", 86);
		trQuestVarSet("ScoreBonus3", 100);
	}
	if(Stage == 4){
		trQuestVarSet("ScoreBonus1", 80);
		trQuestVarSet("ScoreBonus2", 90);
		trQuestVarSet("ScoreBonus3", 100);
	}
	for(z=1 ; < 51){
		if((z == 1*trQuestVarGet("ScoreBonus1")/2) || (z == 1*trQuestVarGet("ScoreBonus2")/2) || (z == 1*trQuestVarGet("ScoreBonus3")/2)){
			CreateDot(63,20+z*2, true);
		}
		else{
			CreateDot(63,20+z*2, false);
		}
	}
	SetPercentRequired(StageRequirement);
	trQuestVarSet("ScoreCheck", 0);
	xsEnableRule("DoScore");
}

rule DoScore
highFrequency
inactive
{
	//[SCORE OVERRIDE FOR TESTING]
	//StageScore = 100;
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
		xsEnableRule("PassAct");
	}
	else{
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
			//xsEnableRule("TutorialTerrainRhino");
			//[SORT THE ABOVE OUT - AS A CUT TO RHINO FOR DEER, MAYBE JUST FIRE THE EVENT]
			for(x=NewDestroyNumber ; < trGetNextUnitScenarioNameNumber()){
				trUnitSelectClear();
				trUnitSelect(""+x);
				trUnitDestroy();
			}
			xsDisableSelf();
		}
	}
}

rule PassAct
highFrequency
inactive
{
	if (trTime() > cActivationTime + 3) {
		xsDisableSelf();
		xsEnableRule("CheckBonuses");
	}
}

rule StopBonusCheck
highFrequency
inactive
{
	//FROM HERE WE START A NEW STAGE
	xsEnableRule("ResetInts");
	characterDialog(" ", " ", "");
	Stage = Stage+1;
	xsDisableSelf();
	if(Stage == 2){
		xsEnableRule("TutorialTerrainRhino");
	}
	if(Stage == 3){
		xsEnableRule("TutorialTerrainGoat");
	}
	if(Stage == 4){
		xsEnableRule("TutorialTerrainCrocodile");
	}
	if(Stage == 5){
		xsEnableRule("TempEndGame");
	}
	trLetterBox(false);
	trFadeOutAllSounds(3);
	trFadeOutMusic(3);
}


rule CheckBonuses
highFrequency
inactive
{
	if(StageScore >= 1*trQuestVarGet("ScoreBonus1")){
		trUnitSelectByQV("Bonus1");
		trUnitChangeProtoUnit("Ragnorok SFX");
		int temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(0, "Dwarf", 62, 20+1*trQuestVarGet("ScoreBonus1"), 0);
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeProtoUnit("Kronny Birth");
		xsEnableRule("CheckBonuses2");
		playSound("plentybirth.wav");
		if(Stage == 1){
			characterDialog("Bonus unlocked!", "+4 hitpoints next stage", ActIcon(Stage));
			for(p = 1 ; < cNumberNonGaiaPlayers){
				trModifyProtounit(""+RhinoProto, p, 0, 4);
				trModifyProtounit(""+RhinoDrinkProto, p, 0, 4);
			}
		}
		if(Stage == 2){
			characterDialog("Bonus unlocked!", "+4 hitpoints next stage", ActIcon(Stage));
			for(p = 1 ; < cNumberNonGaiaPlayers){
				trModifyProtounit(""+GoatProto, p, 0, 4);
			}
		}
		if(Stage == 3){
			characterDialog("Bonus unlocked!", "+4 LOS next stage", ActIcon(Stage));
			for(p = 1 ; < cNumberNonGaiaPlayers){
				trModifyProtounit(""+CrocProto, p, 2, 4);
			}
		}
	}
	else{
		xsEnableRule("StopBonusCheck");
	}
	xsDisableSelf();
}

rule CheckBonuses2
highFrequency
inactive
{
	if (trTime() > cActivationTime + 3) {
		if(StageScore >= 1*trQuestVarGet("ScoreBonus2")){
			trUnitSelectByQV("Bonus2");
			trUnitChangeProtoUnit("Ragnorok SFX");
			int temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(0, "Dwarf", 62, 20+1*trQuestVarGet("ScoreBonus2"), 0);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Kronny Birth");
			xsEnableRule("CheckBonuses3");
			playSound("plentybirth.wav");
			if(Stage == 1){
				characterDialog("Bonus unlocked!", "+1 base speed next stage", ActIcon(Stage));
			}
			if(Stage == 2){
				characterDialog("Bonus unlocked!", "+1hp regen every 30s next stage", ActIcon(Stage));
			}
			for(p = 1 ; < cNumberNonGaiaPlayers){
				xSetPointer(dPlayerData, p);
				xSetInt(dPlayerData, xHPRegenTime, 30);
				xSetInt(dPlayerData, xHPRegen, xGetInt(dPlayerData, xHPRegen)+1);
			}
			if(Stage == 3){
				characterDialog("Bonus unlocked!", "+0.5 sprint speed multiplier next stage", ActIcon(Stage));
				for(p = 1 ; < cNumberNonGaiaPlayers){
					xSetPointer(dPlayerData, p);
					xSetFloat(dPlayerData, xCrocSprintSpeed, xGetFloat(dPlayerData, xCrocSprintSpeed)+0.5);
				}
			}
		}
		else{
			xsEnableRule("StopBonusCheck");
		}
		xsDisableSelf();
	}
}

rule CheckBonuses3
highFrequency
inactive
{
	if (trTime() > cActivationTime + 3) {
		if(StageScore >= 100){
			trUnitSelectByQV("Bonus3");
			trUnitChangeProtoUnit("Ragnorok SFX");
			int temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(0, "Dwarf", 62, 20+1*trQuestVarGet("ScoreBonus3"), 0);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Kronny Birth");
			xsEnableRule("BonusDelay");
			if(Stage == 1){
				characterDialog("Bonus unlocked!", "deer max bonus", ActIcon(Stage));
			}
			if(Stage == 2){
				characterDialog("Bonus unlocked!", "rhino max bonus", ActIcon(Stage));
			}
			if(Stage == 3){
				characterDialog("Bonus unlocked!", "goat max bonus", ActIcon(Stage));
			}
			playSound("plentybirth.wav");
		}
		else{
			xsEnableRule("StopBonusCheck");
		}
		xsDisableSelf();
	}
}

rule BonusDelay
highFrequency
inactive
{
	if (trTime() > cActivationTime + 4) {
		xsEnableRule("StopBonusCheck");
		xsDisableSelf();
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
	ActPart = 0;
	PoachersDead = 0;
	PoachersTarget = 0;
	for(p=1 ; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		if(playerIsPlaying(p)){
			xSetBool(dPlayerData, xPlayerDead, false);
			xSetBool(dPlayerData, xReadyToLeave, false);
			xSetBool(dPlayerData, xStopDeath, false);
			xSetVector(dPlayerData, xVectorHold, vector(0,0,0));
			xSetInt(dPlayerData, xTeleportDue, 0);
			xSetInt(dPlayerData, xRelics, 0);
		}
	}
	xResetDatabase(dTemp);
	xResetDatabase(dLogs);
	xResetDatabase(dDots);
	for(x=NewDestroyNumber ; < trGetNextUnitScenarioNameNumber()){
		trUnitSelectClear();
		trUnitSelect(""+x);
		trUnitDestroy();
	}
	xsDisableSelf();
}
