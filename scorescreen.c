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
	UnitCreate(1, "Osiris", 0,0,0);
	trLetterBox(true);
	trUIFadeToColor(0,0,0,1000,1,true);
	trFadeOutAllSounds(3);
	trSetLighting("default", 0);
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
		debugLog("Shrine Got = " + ShrinesGot);
		debugLog("Shrine Target = " + ShrineTarget);
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
		
		Extras = Extras+4;
		if(xGetDatabaseCount(dHelp) < 2){
			ExtrasGot = ExtrasGot+4;
		}
		
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
		
		for(p = 1 ; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetInt(dPlayerData, xCrocSize) > 6){
				Extras = Extras+2;
				ExtrasGot = ExtrasGot+2;
			}
		}
		if(StageScore < 0){
			StageScore = 2;
		}
		if(StageScore > 100){
			StageScore = 100;
		}
		if(ExtrasGot > Extras){
			debugLog("ERROR MORE THAN 100 PERCENT COMPLETE");
		}
		debugLog("Poachers total = " + PoachersTarget);
		debugLog("Poachers killed = " + PoachersDead);
		//debugLog("SCORE = " + StageScore);
	}
	if(AlwaysWin == true){
		if(StageScore < StageRequirement){
			trOverlayText("You only got " + StageScore, 5.0,50,50,600);
			StageScore = StageRequirement;
		}
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
	if(Stage == 5){
		trQuestVarSet("ScoreBonus1", 200);
		trQuestVarSet("ScoreBonus2", 200);
		trQuestVarSet("ScoreBonus3", 200);
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
		playSound("\Yeebaagooon\Zoo Quest\Credits.mp3");
		EndChats();
		xsDisableSelf();
		trEndGame();
	}
}

rule PassAct
highFrequency
inactive
{
	if (trTime() > cActivationTime + 3) {
		xsDisableSelf();
		xsEnableRule("CheckBonuses");
		if(Stage == 1){
			Score1 = StageScore;
		}
		if(Stage == 2){
			Score2 = StageScore;
		}
		if(Stage == 3){
			Score3 = StageScore;
		}
		if(Stage == 4){
			Score4 = StageScore;
		}
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
		xsEnableRule("TutorialTerrainChicken");
	}
	trLetterBox(false);
	for(p = 1; < cNumberNonGaiaPlayers){
		trSetCivilizationNameOverride(p, ActName(Stage));
	}
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
		if(Stage == 4){
			characterDialog("Bonus unlocked!", "+4 tower count next stage", ActIcon(Stage));
			for(p = 1 ; < cNumberNonGaiaPlayers){
				xSetPointer(dPlayerData, p);
				xSetInt(dPlayerData, xTowerLimit, xGetInt(dPlayerData, xTowerLimit)+4);
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
			if(Stage == 4){
				characterDialog("Bonus unlocked!", "+1 starting relic slot next stage", ActIcon(Stage));
				for(p = 1 ; < cNumberNonGaiaPlayers){
					trModifyProtounit(ChickenProto, p, 5, 1);
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
			//[DO THESE]
			if(Stage == 1){
				characterDialog("Bonus unlocked!", "Super charge and hp regen next act", ActIcon(Stage));
				trQuestVarSet("SuperBonus", 2);
			}
			if(Stage == 2){
				characterDialog("Bonus unlocked!", "No starting poachers next act", ActIcon(Stage));
				trQuestVarSet("SuperBonus", 3);
			}
			if(Stage == 3){
				characterDialog("Bonus unlocked!", "Super sprint and start at level 2 next act", ActIcon(Stage));
				trQuestVarSet("SuperBonus", 4);
			}
			if(Stage == 4){
				characterDialog("Bonus unlocked!", "Better relics supplied at act start", ActIcon(Stage));
				trQuestVarSet("SuperBonus", 5);
			}
			playSound("plentybirth.wav");
			playSound("bronzebirth.wav");
			playSound("restorationbirth.wav");
			trUIFadeToColor(255,255,0,100,500,true);
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
			xSetBool(dPlayerData,xPWantsMG, true);
		}
	}
	xResetDatabase(dTemp);
	xResetDatabase(dLogs);
	xResetDatabase(dDots);
	xResetDatabase(dChests);
	xResetDatabase(dMissiles);
	xResetDatabase(dPoachers);
	xResetDatabase(dInterractables);
	for(x=NewDestroyNumber ; < trGetNextUnitScenarioNameNumber()){
		trUnitSelectClear();
		trUnitSelect(""+x);
		trUnitDestroy();
	}
	xsDisableSelf();
}

rule EndGameLand
highFrequency
inactive
{
	if (trTime() > cActivationTime + 5) {
		xsDisableSelf();
		xsEnableRule("GameEnd");
		trLetterBox(true);
		trUIFadeToColor(255,255,255,500,1000,false);
		playSound("\Yeebaagooon\Zoo Quest\Credits.mp3");
	}
}

rule GameEnd
highFrequency
inactive
{
	for(x=DontDestroyBelow ; < trGetNextUnitScenarioNameNumber()){
		trUnitSelectClear();
		trUnitSelect(""+x);
		trUnitDestroy();
	}
	xsDisableRule("Animations");
	Stage = 6;
	trFadeOutAllSounds(3);
	trSetLighting("default", 0);
	trFadeOutMusic(3);
	clearMap("black", 5.0);
	refreshPassability();
	PaintAtlantisArea(30,10,32,61,5,4);
	PaintAtlantisArea(30,7,32,9,0,90);
	PaintAtlantisArea(33,10,35,61,5,4);
	PaintAtlantisArea(33,7,35,9,0,15);
	PaintAtlantisArea(36,10,38,61,5,4);
	PaintAtlantisArea(36,7,38,9,2,3);
	PaintAtlantisArea(39,10,41,61,5,4);
	PaintAtlantisArea(39,7,41,9,0,37);
	PaintAtlantisArea(42,10,44,61,5,4);
	PaintAtlantisArea(42,7,44,9,3,2);
	PaintAtlantisArea(45,10,47,61,5,4);
	PaintAtlantisArea(45,7,47,9,60,0);
	trCameraCut(vector(78.466331,32.151772,-47.824001), vector(0.019572,-0.281540,0.959350), vector(0.005743,0.959549,0.281482), vector(0.999792,0.000000,-0.020397));
	modifyProtounitAbsolute("Chicken", 0, 1,0);
	modifyProtounitAbsolute("Goat", 0, 1,0);
	modifyProtounitAbsolute("Crocodile", 0, 1,0);
	modifyProtounitAbsolute("Rhinocerous", 0, 1,0);
	modifyProtounitAbsolute("Gazelle", 0, 1,0);
	UnitCreate(0, "Gazelle" ,62, 16, 180);
	UnitCreate(0, "Rhinocerous" ,68, 16, 180);
	UnitCreate(0, "Goat", 74, 16, 180);
	UnitCreate(0, "Crocodile" ,80, 16, 180);
	UnitCreate(0, "Chicken" , 86, 16, 180);
	UnitCreate(0, "Pharaoh of Osiris XP" ,92, 16, 180);
	for(z=1 ; < 51){
		CreateDot(93,20+z*2, false);
	}
	TotalScore = (Score1+Score2+Score3+Score4+100)/5;
	trPaintTerrain(31,11,31,10+(Score1/2),0,1);
	trPaintTerrain(34,11,34,10+(Score2/2),0,1);
	trPaintTerrain(37,11,37,10+(Score3/2),0,1);
	trPaintTerrain(40,11,40,10+(Score4/2),0,1);
	trPaintTerrain(43,11,43,10+(100/2),0,1);
	trQuestVarSet("ScoreCheck", 0);
	xsDisableSelf();
	xsEnableRule("ScoreFDelay");
	trSetFogAndBlackmap(false,false);
}

rule ScoreFDelay
highFrequency
inactive
{
	if (trTime() > cActivationTime + 2) {
		xsDisableSelf();
		xsEnableRule("DoScoreFinal");
		trSetFogAndBlackmap(false,false);
	}
}

rule DoScoreFinal
highFrequency
inactive
{
	int TimerTile = trTimeMS();
	if(TimerTile > GlobalTimerMS){
		GlobalTimerMS = trTimeMS()+70;
		trQuestVarModify("ScoreCheck", "+", 1);
		if (iModulo(2, 1*trQuestVarGet("ScoreCheck")) == 0) { //if is divisble by 2
			xDatabaseNext(dDots);
			if(xGetInt(dDots, xPercent) <= TotalScore){
				trUnitSelectClear();
				xUnitSelect(dDots, xUnitID);
				trUnitHighlight(10000, false);
			}
			if(1*trQuestVarGet("ScoreCheck") >= TotalScore){
				xsDisableSelf();
				if(TotalScore >= 90){
					trDelayedRuleActivation("FinalScore100");
				}
				else{
					trDelayedRuleActivation("FinalScoreDone");
				}
				int temp = trGetNextUnitScenarioNameNumber();
				UnitCreate(0, "Dwarf", 93, 20+TotalScore, 90);
				trUnitSelectClear();
				trUnitSelect(""+temp);
				trUnitChangeProtoUnit("Heavenlight");
				temp = trGetNextUnitScenarioNameNumber();
				UnitCreate(GreenText(), "Dwarf", 93, 20+TotalScore, 90);
				trUnitSelectClear();
				trUnitSelect(""+temp);
				trUnitChangeProtoUnit("Flag");
				trUnitSelectClear();
				trUnitSelect(""+temp);
				trUnitSetAnimationPath("0,1,0,0,0,0");
				playSoundCustom("fanfare.wav", "\Yeebaagooon\Zoo Quest\Skillpoint.mp3");
			}
		}
		characterDialog("Zoo Quest - "+1*trQuestVarGet("ScoreCheck") + " percent complete", "", "icons/special e son of osiris icon 64");
	}
}

void TextDifficulty(){
	string difficult = "error";
	if(Difficulty == 0){
		trOverlayTextColour(0, 255, 0);
		trOverlayText("Easy difficulty", 8.0, 584, 180, 1000);
	}
	if(Difficulty == 1){
		trOverlayTextColour(255, 255, 0);
		trOverlayText("Moderate difficulty", 8.0, 550, 180, 1000);
	}
	if(Difficulty == 2){
		trOverlayTextColour(255, 125, 0);
		trOverlayText("Hard difficulty", 8.0, 584, 180, 1000);
	}
	if(Difficulty == 3){
		trOverlayTextColour(255, 0, 0);
		trOverlayText("Titan difficulty", 8.0, 582, 180, 1000);
	}
}


rule FinalScoreDone
highFrequency
inactive
{
	if (trTime() > cActivationTime + 2) {
		trLetterBox(false);
		xsDisableSelf();
		xsEnableRule("YouWin");
		TextDifficulty();
		createCameraTrack(1000);
		trCameraCut(vector(78.466331,32.151772,-47.824001), vector(0.019572,-0.281540,0.959350), vector(0.005743,0.959549,0.281482), vector(0.999792,-0.000000,-0.020397));
		addCameraTrackWaypoint();
		trCameraCut(vector(75.384941,18.111774,-48.841358), vector(0.020254,-0.118123,0.992792), vector(0.002410,0.992999,0.118098), vector(0.999792,-0.000000,-0.020397));
		addCameraTrackWaypoint();
		playCameraTrack();
		if(Difficulty == 0){
			PaintAtlantisArea(28,64,49,69,0,71);
		}
		if(Difficulty == 1){
			PaintAtlantisArea(28,64,49,69,0,86);
		}
		if(Difficulty == 2){
			PaintAtlantisArea(28,64,49,69,2,12);
		}
		if(Difficulty == 3){
			PaintAtlantisArea(28,64,49,69,2,10);
		}
		trChangeTerrainHeight(30,65,48,65,7,false);
		trChangeTerrainHeight(30,66,48,66,10,false);
		trChangeTerrainHeight(30,67,48,67,13,false);
		trChangeTerrainHeight(30,68,48,68,16,false);
		trChangeTerrainHeight(30,69,48,69,19,false);
		trChangeTerrainHeight(30,70,48,70,22,false);
	}
}

rule FinalScore100
highFrequency
inactive
{
	for(x=DontDestroyBelow ; < trGetNextUnitScenarioNameNumber()){
		trUnitSelectClear();
		trUnitSelect(""+x);
		trUnitDestroy();
	}
	clearMap("black", 5.0);
	for(a = 4 ; < 8){
		for(b = 1 ; < 10){
			BuildYeebCol(10+a*15,10+b*15);
		}
	}
	for(x = 10 ; < 30){
		for(z = 0 ; < 40){
			int temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(0, "Dwarf", x*4, z*4, 0);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Spy Eye");
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trMutateSelected(kbGetProtoUnitID("Wall Connector"));
			trUnitSetAnimationPath("0,1,0,0,0,0,0");
			trSetSelectedScale(2,0.01,2);
		}
	}
	for(x = 4 ; < 10){
		int temp2 = trGetNextUnitScenarioNameNumber();
		UnitCreate(1, "Underworld Passage SPC", 12+x*10, 12, 0);
		trUnitSelectClear();
		trUnitSelect(""+temp2);
		trSetSelectedUpVector(0,2,0);
		trSetSelectedScale(2,1,1);
		trUnitSelectClear();
		trUnitSelect(""+temp2);
		trUnitSetAnimationPath("2,0,0,0,0,0,0");
	}
	int temp3 = trGetNextUnitScenarioNameNumber();
	UnitCreate(1, "Pharaoh of Osiris XP", 92,20, 0);
	trUnitSelectClear();
	trUnitSelect(""+temp3);
	trUnitSetAnimationPath("0,1,0,1,0,0");
	trUnitOverrideAnimation(33, 0, true, true, -1, 0);
	trUnitSelectClear();
	createCameraTrack(7500);
	trCameraCut(vector(94.802574,19.802563,186.212006), vector(-0.035675,-0.082735,-0.995933), vector(-0.002962,0.996572,-0.082682), vector(-0.999359,-0.000000,0.035798));
	addCameraTrackWaypoint();
	trCameraCut(vector(94.537735,9.362560,111.773857), vector(-0.035724,0.064126,-0.997302), vector(0.002295,0.997942,0.064085), vector(-0.999359,-0.000000,0.035798));
	addCameraTrackWaypoint();
	playCameraTrack();
	xsDisableSelf();
	xsEnableRule("YouWinDelay");
	trSetObscuredUnits(false);
	trUIFadeToColor(255,255,255,500,1000,false);
}

rule YouWinDelay
highFrequency
inactive
{
	if (trTime() > cActivationTime + 6) {
		xsDisableSelf();
		trLetterBox(false);
		xsEnableRule("YouWin");
		TextDifficulty();
	}
}

rule YouWin
highFrequency
inactive
{
	if (trTime() > cActivationTime + 1) {
		trShowWinLose("Zoo Quest "+1*trQuestVarGet("ScoreCheck") + " percent complete ", "xwin.wav");
		for(p=1 ; < cNumberNonGaiaPlayers){
			trSetPlayerWon(p);
		}
		xsDisableSelf();
		trEndGame();
		xsDisableSelf();
		EndChats();
	}
}
