rule TutorialTerrainRhino
highFrequency
inactive
{
	if (trTime() > cActivationTime + 1) {
		trCameraCut(vector(-65.460060,123.743729,-65.460060), vector(0.500000,-0.707107,0.500000), vector(0.500000,0.707107,0.500000), vector(0.707107,0.000000,-0.707107));
		xsDisableRule("DeerTutorialDone");
		TutorialMode = true;
		Stage = 2;
		CliffType = 2;
		CliffSubType = 2;
		//trLetterBox(false);
		clearMap("black", 5.0);
		trPaintTerrain(0,0,45,cNumberNonGaiaPlayers*8,CliffType,CliffSubType);
		xResetDatabase(dChests);
		int temp = 0;
		//trees
		for(t=0 ; < cNumberNonGaiaPlayers){
			for(x=0 ; < 46){
				if(iModulo(7,x) == 0){
					temp = trGetNextUnitScenarioNameNumber();
					UnitCreate(0, "Cinematic Block", x*2, t*16+8, 90);
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitChangeProtoUnit("Rock Sandstone Big");
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trSetScale(1.65);
				}
				else{
					temp = trGetNextUnitScenarioNameNumber();
					UnitCreate(0, "Cinematic Block", x*2, t*16+8, 90);
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitChangeProtoUnit("Savannah Tree");
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trSetScale(0.75);
				}
			}
		}
		trQuestVarSet("PlayersDoneTutorial", 0);
		for(p=1 ; < cNumberNonGaiaPlayers){
			trQuestVarSet("P"+p+"DoneTutorial", 0);
			trQuestVarSet("P"+p+"FountainMsg", 0);
			trPaintTerrain(5,((p*8)-2),40,((p*8+4)-2),0,15);
			//trPaintTerrain(7,p*8,7,p*8,0,73); //start sq
			PaintAtlantisArea(6,p*8-1,8,p*8+1,0,18);  //start sq
			trPaintTerrain(28,p*8+2,28,p*8-2,0,74); //end line
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(cNumberNonGaiaPlayers, "Cinematic Block", 28*2, p*16-4, 0);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Fence Wood");
			xAddDatabaseBlock(dTemp, true);
			xSetInt(dTemp, xUnitID, temp);
			xSetInt(dTemp, xExtra, p);
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(cNumberNonGaiaPlayers, "Cinematic Block", 28*2, p*16, 0);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Fence Wood");
			xAddDatabaseBlock(dTemp, true);
			xSetInt(dTemp, xUnitID, temp);
			xSetInt(dTemp, xExtra, p);
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(cNumberNonGaiaPlayers, "Cinematic Block", 28*2, p*16+4, 0);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Fence Wood");
			xAddDatabaseBlock(dTemp, true);
			xSetInt(dTemp, xUnitID, temp);
			xSetInt(dTemp, xExtra, p);
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(0, "Cinematic Block", 34*2, p*16, 0);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Fountain");
			xAddDatabaseBlock(dTemp, true);
			xSetInt(dTemp, xUnitID, temp);
			xSetInt(dTemp, xExtra, p);
			CreateRhino(p,14,16*p,90);
			xSetPointer(dPlayerData, xPlayerUnitID);
			xSetInt(dPlayerData, xPlayerUnitID, 1*trQuestVarGet("P"+p+"Unit"));
			modifyProtounitAbsolute(""+RhinoProto, p, 1, xGetFloat(dPlayerData, xRhinoWalk));
			if(trCurrentPlayer() == p){
				trCounterAddTime("cdtutorial", -100, -200, "<color={PlayerColor("+p+")}>Press 'Q' to start/stop charge.", -1);
			}
		}
		refreshPassability();
		xsEnableRule("Animations");
		xsEnableRule("Charge");
		xsDisableRule("Jump");
		xsDisableRule("VectorFirst");
		xsDisableRule("VectorSecond");
		xsEnableRule("RhinoTutorialDone");
		trDelayedRuleActivation("RhinoTutorialLoops");
		modifyProtounitAbsolute(""+RhinoProto, p, 1, xGetFloat(dPlayerData, xRhinoWalk));
		if(QuickStart == 0){
			startNPCDialog(6);
		}
		refreshPassability();
		uiZoomToProto(""+RhinoProto);
		uiLookAtProto(""+RhinoProto);
		playSound("\xpack\xcinematics\5_in\music.mp3");
		SetUI(5,1);
		xsDisableSelf();
	}
}

rule Charge
highFrequency
inactive
{
	int anim = 0;
	int temp = 0;
	float height = 0;
	for(p=1 ; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		if(trPlayerResourceCount(p, "Gold") > 0){
			trPlayerGrantResources(p, "Gold", -100000);
			if((xGetBool(dPlayerData, xReadyToLeave) == false) && (trPlayerUnitCountSpecific(p, ""+RhinoProto) == 1)){
				if(xGetFloat(dPlayerData, xRhinoChargeTime) > 0){
					ToggleCharge(p);
					//ColouredIconChatToPlayer(p, "1,1,0", "icons\icon object stat hit point", "Stamina = " + 1*xGetFloat(dPlayerData, xRhinoChargeTime));
				}
				else{
					ColouredIconChatToPlayer(p, "1,0,0", "icons\icon object stat hit point", "Not enough stamina to charge!");
					if(trCurrentPlayer() == p){
						playSound("cantdothat.wav");
					}
				}
			}
		}
		if(trPlayerResourceCount(p, "Wood") > 0){
			trPlayerGrantResources(p, "Wood", -100000);
			if(TutorialMode == false){
				height = xsVectorGetY(kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
				if(height > 0.31){
					ColouredIconChatToPlayer(p, "1,0.2,0.2", "icons\editor edit water", "Height needs to be less than 0!<color=0,1,1> " + height);
					if(trCurrentPlayer() == p){
						playSound("cantdothat.wav");
					}
				}
				else{
					trUnitSelectByQV("P"+p+"Unit");
					trMutateSelected(kbGetProtoUnitID(""+RhinoDrinkProto));
					trQuestVarSet("P"+p+"Drink", trTimeMS()+1000*xGetFloat(dPlayerData, xRhinoDrinkTime));
					if(trCurrentPlayer() == p){
						trCounterAddTime("rhinodrinker" +p, 1*xGetFloat(dPlayerData, xRhinoDrinkTime),0,"<color={PlayerColor("+BlueText()+")}>Drinking", -1);
						playSound("shipdeathsplash.wav");
						playSound("geyserbirth.wav");
					}
				}
			}
			else if(TutorialMode == true){
				//tutorial W (68)
				height = xsVectorGetX(kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
				if((height < 70) && (height > 66)){
					//yes
					trQuestVarSet("P"+p+"FountainMsg", 2);
					if(trCurrentPlayer() == p){
						trCounterAddTime("rhinodrinker" +p, 2,0,"<color={PlayerColor("+BlueText()+")}>Drinking", -1);
						playSound("shipdeathsplash.wav");
						playSound("geyserbirth.wav");
					}
				}
				else{
					//no
					ColouredIconChatToPlayer(p, "1,0.2,0.2", "icons\editor edit water", "Not close enough to fountain!");
					if(trCurrentPlayer() == p){
						playSound("cantdothat.wav");
					}
				}
			}
		}
		if(trPlayerResourceCount(p, "Food") > 0){
			trPlayerGrantResources(p, "Food", -100000);
		}
		if(xGetBool(dPlayerData, xCharge) == true){
			//Charge effects
			if(iModulo(10, trTimeMS()) == 0){
				temp = trGetNextUnitScenarioNameNumber();
				UnitCreate(0, "Dwarf",xsVectorGetX(kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit"))),xsVectorGetZ(kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit"))),0);
				trUnitSelectClear();
				trUnitSelect(""+temp);
				trUnitChangeProtoUnit("Dust Medium");
				trUnitSelectByQV("P"+p+"Unit");
				trDamageUnitsInArea(cNumberNonGaiaPlayers, "Fence Wood", 6, 50);
				trDamageUnitsInArea(cNumberNonGaiaPlayers, "Slinger", 2, 50);
				trDamageUnitsInArea(cNumberNonGaiaPlayers, "Chu Ko Nu", 2, 50);
			}
			if(xGetFloat(dPlayerData, xRhinoChargeTime) < 0){
				ToggleCharge(p);
				ColouredIconChatToPlayer(p, "1,0,0", "icons\icon object stat hit point", "Out of stamina!");
				trQuestVarModify("P"+p+"StaminaWarn", "+", 1);
				if(1*trQuestVarGet("P"+p+"StaminaWarn") < 3){
					ColouredIconChatToPlayer(p, "1,1,0", "icons\editor river", "Use 'W' when near water to drink and replenish stamina.");
				}
				if(trCurrentPlayer() == p){
					playSound("cantdothat.wav");
				}
			}
		}
		if((trTimeMS() > 1*trQuestVarGet("P"+p+"Drink")) && (trPlayerUnitCountSpecific(p, ""+RhinoDrinkProto) == 1)){
			trUnitSelectByQV("P"+p+"Unit");
			trMutateSelected(kbGetProtoUnitID(""+RhinoProto));
			xSetFloat(dPlayerData, xRhinoChargeTime, xGetInt(dPlayerData, xRhinoChargeTimeMax));
			if(trCurrentPlayer() == p){
				playSound("geyserhit2.wav");
			}
		}
	}
}

rule RhinoTutorialDone
highFrequency
inactive
{
	if((PlayersActive == 1*trQuestVarGet("PlayersDoneTutorial")) && (PlayersActive > 0)){
		xsDisableSelf();
		xsDisableRule("RhinoTutorialLoops");
		xsEnableRule("BuildRhinoArea");
		trClearCounterDisplay();
		trCounterAbort("cdtutorial");
		trCounterAbort("cdtutoriala");
		trCounterAbort("cdtutorialtimeout");
		trQuestVarSet("PlayersDoneTutorial", 0);
		trLetterBox(true);
		trUIFadeToColor(0,0,0,1,1,true);
		Stage = 2;
		characterDialog(ActName(Stage), " ", ActIcon(Stage));
		trSetFogAndBlackmap(true,true);
		trDelayedRuleActivation("ResetBlackmap");
		trFadeOutAllSounds(3);
		trFadeOutMusic(3);
		xResetDatabase(dTemp);
		TutorialMode = false;
	}
}

rule RhinoTutorialLoops
highFrequency
inactive
{
	if(TutorialMode){
		int temp = 0;
		for(p=1 ; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			trVectorQuestVarSet("P"+p+"Pos", kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
			if((playerIsPlaying(p) == false) && (xGetBool(dPlayerData, xPlayerActive) == true)){
				trUnitSelectByQV("P"+p+"Unit");
				trUnitChangeProtoUnit("Ragnorok SFX");
				trUnitSelectByQV("P"+p+"Unit");
				trUnitDestroy();
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
				trUnitChangeProtoUnit("Hero Death");
				xSetBool(dPlayerData, xPlayerActive, false);
				PlayersActive = PlayersActive-1;
				trPaintTerrain(5,((p*8)-2),40,((p*8+4)-2),CliffType,CliffSubType);
				trUnitSelectClear();
				for(a = xGetDatabaseCount(dTemp) ; > 0){
					xDatabaseNext(dTemp);
					if(xGetInt(dTemp, xExtra) == p){
						xUnitSelect(dTemp, xUnitID);
						trUnitDestroy();
						xFreeDatabaseBlock(dTemp);
					}
				}
			}
			//through wall
			if((trVectorQuestVarGetX("P"+p+"Pos") > 58) && (1*trQuestVarGet("P"+p+"DoneTutorial") == 0) && (1*trQuestVarGet("P"+p+"FountainMsg") == 0)){
				if(trCurrentPlayer() == p){
					startNPCDialog(7);
					trQuestVarSet("P"+p+"FountainMsg", 1);
					trCounterAddTime("cdtutoriala", -100, -200, "<color={PlayerColor("+p+")}>Press 'W' to drink.", -1);
				}
			}
			if((1*trQuestVarGet("P"+p+"FountainMsg") == 2) && (1*trQuestVarGet("P"+p+"DoneTutorial") == 0)){
				trUnitSelectByQV("P"+p+"Unit");
				trUnitChangeProtoUnit("Ragnorok SFX");
				trUnitSelectByQV("P"+p+"Unit");
				trUnitDestroy();
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
				trUnitChangeProtoUnit("Hero Death");
				trQuestVarSet("P"+p+"DoneTutorial", 1);
				trQuestVarModify("PlayersDoneTutorial", "+", 1);
				temp = 1*trQuestVarGet("PlayersDoneTutorial");
				trPaintTerrain(5,((p*8)-2),40,((p*8+4)-2),CliffType,CliffSubType);
				trUnitSelectClear();
				for(a = xGetDatabaseCount(dTemp) ; > 0){
					xDatabaseNext(dTemp);
					if(xGetInt(dTemp, xExtra) == p){
						xUnitSelect(dTemp, xUnitID);
						trUnitDestroy();
						xFreeDatabaseBlock(dTemp);
					}
				}
				trUnitSelectClear();
				trClearCounterDisplay();
				trSetCounterDisplay("<color={PlayerColor(" + GreenText() + ")}>Tutorial complete: " + temp + " / " + PlayersActive);
				if((temp == 1) && (PlayersActive > 1)){
					xsEnableRule("TutorialTimeout");
				}
				if(trCurrentPlayer() == p){
					playSound("ageadvance.wav");
					trCounterAbort("cdtutorial");
					trCounterAbort("cdtutoriala");
				}
			}
			trUnitSelectByQV("P"+p+"Unit");
			if((trUnitDead() == true) && (xGetBool(dPlayerData, xPlayerActive) == true) && (1*trQuestVarGet("P"+p+"DoneTutorial") == 0)){
				trUnitSelectByQV("P"+p+"Unit");
				trUnitChangeProtoUnit("Ragnorok SFX");
				trUnitSelectByQV("P"+p+"Unit");
				trUnitDestroy();
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
				trUnitChangeProtoUnit("Hero Death");
				CreateRhino(p, 14, p*16, 90);
			}
		}
	}
}
