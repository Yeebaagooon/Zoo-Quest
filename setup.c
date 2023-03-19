rule EventSetHandler
active
highFrequency
//THESE ONLY WORK IF FIRES FUNCTION, SO USE VOID!
{
	for(p = 1; < cNumberNonGaiaPlayers){
		trEventSetHandler(p, "ChooseYes");
		trEventSetHandler(12+p, "ChooseNo");
	}
	trEventSetHandler(25, "CustomContent");
	trEventSetHandler(EVENT_REMOVE_CAM_TRACKS, "removeCamTracks");
	trEventSetHandler(27, "DeerMinigameGo");
	for(i=EVENT_BUILD_HOUSE; <= EVENT_BUILD_STOREHOUSE) {
		trEventSetHandler(i, "hotkeyAbility");
	}
	trEventSetHandler(EVENT_BUILD_AT_CURSOR, "buildAtCursor");
	trEventSetHandler(32, "SpawnDeerPoachers");
	trEventSetHandler(33, "TutForceEnd");
	trEventSetHandler(34, "RhinoMinigameGo");
	trEventSetHandler(35, "RhinoMGTimeout");
	trEventSetHandler(36, "GoatMinigameGo");
	trEventSetHandler(37, "GoatMGTimeout");
	trEventSetHandler(38, "CrocMinigameGo");
	trEventSetHandler(39, "CrocMGTimeout");
	trEventSetHandler(40, "ChickenWave1");
	trEventSetHandler(41, "ChickenWave1End");
	trEventSetHandler(42, "ChickenWave2");
	trEventSetHandler(43, "ChickenWave2End");
	trEventSetHandler(44, "ChickenWave3");
	trEventSetHandler(45, "ChickenWave3End");
	trEventSetHandler(46, "CineGo");
	xsDisableSelf();
}

rule Initialise
active
highFrequency
runImmediately
{
	characterDialog("Waiting for everyone to connect.", " ", "icons\special e son of osiris icon 64");
	trUIFadeToColor(0, 0, 0, 0, 10000, false);
	trFadeOutAllSounds(0.1);
	trFadeOutMusic(0.1);
	if(QuickStart == 0){
	}
	trBlockAllSounds(true);
	trArmyDispatch("0,0", "Cinematic Block", 1, 0, 0, 0, 0, false);
	for(p = 1; <= cNumberNonGaiaPlayers){
		deployLocHeading(0, p*2, "Victory Marker", p, 180);
	}
	trSetFogAndBlackmap(false, false);
	xsDisableSelf();
}

rule START
active
highFrequency
{
	trPlayerKillAllGodPowers(0);
	for(p = 1; <= cNumberNonGaiaPlayers){
		trSetCivAndCulture(p, 3, 1);
		trPlayerGrantResources(p, "Food", -10000.0);
		trPlayerGrantResources(p, "Wood", -10000.0);
		trPlayerGrantResources(p, "Gold", -10000.0);
		trPlayerGrantResources(p, "Favor", -10000.0);
		trPlayerKillAllGodPowers(p);
	}
	xsDisableRule("BasicVC1");
	xsDisableRule("BasicVC2");
	//start fade to black
	//trUIFadeToColor(1,0,0,0,0,true);
	//trShowImageDialog("icons\icon class harmless animal", MapName + " by Yeebaagooon");
	gadgetUnreal("ShowImageBox-BordersTop");
	gadgetUnreal("ShowImageBox-BordersBottom");
	gadgetUnreal("ShowImageBox-BordersLeft");
	gadgetUnreal("ShowImageBox-BordersRight");
	gadgetUnreal("ShowImageBox-BordersLeftTop");
	gadgetUnreal("ShowImageBox-BordersLeftBottom");
	gadgetUnreal("ShowImageBox-BordersRightBottom");
	gadgetUnreal("ShowImageBox-BordersRightTop");
	gadgetUnreal("ShowImageBox-CloseButton");
	pause(0);
	characterDialog("Initialising map", " ", "icons\special e son of osiris icon 64");
	xsEnableRule("load1");
	xsDisableSelf();
	//HOTKEYS
	//map("q", "game", "uiSetSpecialPower(220) uiSpecialPowerAtPointer");
	map("q", "game", "trackInsert(); trackAddWaypoint();trackPlay(-1,28);");
	map("w", "game", "trackInsert(); trackAddWaypoint();trackPlay(-1,29);");
	map("e", "game", "trackInsert(); trackAddWaypoint();trackPlay(-1,30);");
	map("r", "game", "uiSetSpecialPower(227) uiSpecialPowerAtPointer");
	%
	for(p=1; < cNumberNonGaiaPlayers) {
		code("trStringQuestVarSet(\"p"+p+"name\", \""+rmGetPlayerName(p)+"\");");
	}
	%
}

void BuildYeebCol(int x = 0, int z = 0, int y = 0){
	FloatingUnit("Wall Connector", x, 3, z, 0,1,2,1);
	trUnitSelectByQV("QVRelic");
	trUnitSetAnimationPath("0,2,0,0,0,0");
	FloatingUnit("Wall Connector", x, 11, z, 0,1,2,1);
	trUnitSelectByQV("QVRelic");
	trUnitSetAnimationPath("0,2,0,0,0,0");
	FloatingUnit("Wall Connector", x, 19, z, 0,1,2,1);
	trUnitSelectByQV("QVRelic");
	trUnitSetAnimationPath("0,2,0,0,0,0");
	FloatingUnit("Wall Connector", x, 27, z, 0,1,2,1);
	trUnitSelectByQV("QVRelic");
	trUnitSetAnimationPath("0,2,0,0,0,0");
	FloatingUnit("Wall Connector", x, 3, z-2, 0,1,1,1);
	trUnitSelectByQV("QVRelic");
	trUnitSetAnimationPath("0,2,0,0,0,0");
	FloatingUnit("Wall Connector", x, 3, z+2, 0,1,1,1);
	trUnitSelectByQV("QVRelic");
	trUnitSetAnimationPath("0,2,0,0,0,0");
	FloatingUnit("Wall Connector", x+2, 3, z, 0,1,1,1);
	trUnitSelectByQV("QVRelic");
	trUnitSetAnimationPath("0,2,0,0,0,0");
	FloatingUnit("Wall Connector", x-2, 3, z, 0,1,1,1);
	trUnitSelectByQV("QVRelic");
	trUnitSetAnimationPath("0,2,0,0,0,0");
	FloatingUnit("Monument", x-2, 7, z, 270,1,1,1);
	FloatingUnit("Monument", x+2, 7, z, 90,1,1,1);
	FloatingUnit("Monument", x, 7, z+2, 0,1,1,1);
	FloatingUnit("Monument", x, 7, z-2, 180,1,1,1);
	FloatingUnit("Flag", x+2, 19, z, 90,1,-1,1);
	trUnitSelectByQV("QVRelic");
	trUnitSetAnimationPath("0,1,0,0,0,0");
	FloatingUnit("Flag", x-1.6, 19, z, 90,1,-1,1);
	trUnitSelectByQV("QVRelic");
	trUnitSetAnimationPath("0,1,0,0,0,0");
	FloatingUnit("Columns Fallen", x+2, 18.5, z, 90,0.5,0.5,0.5);
	trUnitSelectByQV("QVRelic");
	trUnitSetAnimationPath("0,0,0,0,0,0");
	FloatingUnit("Columns Fallen", x-2, 18.5, z, 270,0.5,0.5,0.5);
	trUnitSelectByQV("QVRelic");
	trUnitSetAnimationPath("0,0,0,0,0,0");
	//FloatingUnitAnimIdle("Plenty Vault", x, 3, z, 0,0.6,-1,0.6);
}

rule load1
inactive
highFrequency
{
	characterDialog("Loading map.", ""+MapVersion+"", "icons\special e son of osiris icon 64");
	xsEnableRule("load2");
	trBlockAllSounds(false);
	xsDisableSelf();
	while(cNumberNonGaiaPlayers>=trQuestVarGet("PlayerID")) {
		trQuestVarSet("PlayerID2", 0);
		while(cNumberNonGaiaPlayers>=trQuestVarGet("PlayerID2")) {
			trPlayerSetDiplomacy(trQuestVarGet("PlayerID"), trQuestVarGet("PlayerID2"), "Ally");
			trPlayerSetDiplomacy(trQuestVarGet("PlayerID2"), trQuestVarGet("PlayerID"), "Ally");
		trQuestVarSet("PlayerID2", trQuestVarGet("PlayerID2")+1);}
	trQuestVarSet("PlayerID", trQuestVarGet("PlayerID")+1);}
	
	for(p=1 ; < cNumberNonGaiaPlayers){
		trPlayerSetDiplomacy(0, p, "Enemy");
		trPlayerSetDiplomacy(cNumberNonGaiaPlayers, p, "Enemy");
		trPlayerSetDiplomacy(p, cNumberNonGaiaPlayers, "Enemy");
		trPlayerSetDiplomacy(p, 0, "Neutral");
	}
	trPlayerSetDiplomacy(0, cNumberNonGaiaPlayers, "Enemy");
	trTechSetStatus(0, 304, 4);
	PlayersActive = cNumberNonGaiaPlayers;
	PlayersActive = PlayersActive-1;
	aiSet("NoAI", cNumberNonGaiaPlayers);
}

rule load2
inactive
highFrequency
{
	characterDialog("Loading map..", ""+MapVersion+"", "icons\special e son of osiris icon 64");
	xsEnableRule("load3");
	xsEnableRule("Stats");
	xsEnableRule("SetupChoiceUnits");
	xsDisableSelf();
}

rule load3
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 1){
		characterDialog("Loading map...", ""+MapVersion+"", "icons\special e son of osiris icon 64");
		for(p = 1; <= cNumberNonGaiaPlayers){
			trPlayerGrantResources(p, "Food", -10000.0);
			trPlayerGrantResources(p, "Wood", -10000.0);
			trPlayerGrantResources(p, "Gold", -10000.0);
			trPlayerGrantResources(p, "Favor", -10000.0);
			trPlayerKillAllGodPowers(p);
			//this does custom content
			trSoundPlayFN("\Yeebaagooon\Zoo Quest\test sound.mp3", "1", 25, "","");
		}
		xsEnableRule("load4");
		xsDisableSelf();
	}
}

rule load4
inactive
highFrequency
{
	if((trTime()-cActivationTime) >= 1){
		//fade out when loaded
		trUnblockAllSounds();
		trLetterBox(false);
		trUIFadeToColor(0,0,0,1000,1,false);
		trOverlayTextColour(255, 125, 0);
		gadgetUnreal("ShowImageBox");
		trOverlayText(MapName, 8.0, 594, 28, 1000);
		trSetUnitIdleProcessing(true);
		xsDisableSelf();
		Difficulty = 1*trGetWorldDifficulty();
		gadgetReal("ShowImageBox-BordersTop");
		gadgetReal("ShowImageBox-BordersBottom");
		gadgetReal("ShowImageBox-BordersLeft");
		gadgetReal("ShowImageBox-BordersRight");
		gadgetReal("ShowImageBox-BordersLeftTop");
		gadgetReal("ShowImageBox-BordersLeftBottom");
		gadgetReal("ShowImageBox-BordersRightBottom");
		gadgetReal("ShowImageBox-BordersRightTop");
		gadgetReal("ShowImageBox-CloseButton");
		//startNPCDialog(1);
		if(QuickStart == 8){
			for(a = 1 ; < 10){
				for(b = 1 ; < 10){
					BuildYeebCol(10+a*15,10+b*15);
				}
			}
			for(x = 0 ; < 40){
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
			for(x = 0 ; < 14){
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
			trCameraCut(vector(94.802574,19.802563,186.212006), vector(-0.035675,-0.082735,-0.995933), vector(-0.002962,0.996572,-0.082682), vector(-0.999359,-0.000000,0.035798));
			trCameraCut(vector(94.537735,9.362560,111.773857), vector(-0.035724,0.064126,-0.997302), vector(0.002295,0.997942,0.064085), vector(-0.999359,-0.000000,0.035798));
		}
		if(QuickStart == 7){
			xsEnableRule("ChickenWave3Finish");
		}
		if(QuickStart == 6){
			xsEnableRule("BuildCineScene");
		}
		if(QuickStart == 5){
			xsEnableRule("TutorialTerrainChicken");
		}
		if(QuickStart == 4){
			xsEnableRule("TutorialTerrainCrocodile");
		}
		if(QuickStart == 3){
			xsEnableRule("TutorialTerrainGoat");
		}
		if(QuickStart == 2){
			xsEnableRule("TutorialTerrainRhino");
		}
		if(QuickStart == 1){
			xsEnableRule("BuildDeerArea");
			xsEnableRule("Animations");
			xsEnableRule("Jump");
			xsEnableRule("JumpEnd");
			trDelayedRuleActivation("VectorSecond");
		}
		if(QuickStart == 0){
			xsEnableRule("TutorialTerrain");
		}
		xsEnableRule("CustomContentChat");
		xsEnableRule("ysearch");
		xsEnableRule("DestroyConstant");
		xsEnableRule("Animations");
		trDelayedRuleActivation("Help_Chat");
		for(p = 1; < cNumberNonGaiaPlayers){
			trSetCivilizationNameOverride(p, "Yeebaagooon");
		}
		trSetCivilizationNameOverride(cNumberNonGaiaPlayers, "Poachers");
	}
}

void CustomContent(int p = 0){
	//xsSetContextPlayer(0);
	xsDisableSelf();
	trQuestVarSet("CustomContent", 1);
}



rule CustomContentChat
inactive
highFrequency
{
	if(1*trQuestVarGet("CustomContent") == 1){
		playSound("\Yeebaagooon\Zoo Quest\Skillpoint.mp3");
		ColouredIconChat("1,0.5,0", "icons\special e son of osiris icon 64","Custom Content enabled!");
	}
	xsDisableSelf();
}
