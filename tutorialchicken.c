rule TutorialTerrainChicken
highFrequency
inactive
{
	if (trTime() > cActivationTime + 1) {
		trCameraCut(vector(-65.460060,123.743729,-65.460060), vector(0.500000,-0.707107,0.500000), vector(0.500000,0.707107,0.500000), vector(0.707107,0.000000,-0.707107));
		xsDisableRule("DeerTutorialDone");
		xsDisableRule("RhinoTutorialDone");
		xsDisableRule("GoatTutorialDone");
		xsDisableRule("CrocodileTutorialDone");
		xsDisableRule("Jump");
		xsDisableRule("JumpEnd");
		NewDestroyNumber = trGetNextUnitScenarioNameNumber()-1;
		TutorialMode = true;
		Stage = 5;
		CliffType = 2;
		CliffSubType = 13;
		//trLetterBox(false);
		clearMap("black", -5.0);
		trPaintTerrain(0,0,45,cNumberNonGaiaPlayers*8,CliffType,CliffSubType);
		xResetDatabase(dChests);
		int temp = 0;
		//trees
		for(t=0 ; < cNumberNonGaiaPlayers){
			for(x=0 ; < 40){
				if(iModulo(4,x) == 0){
					temp = trGetNextUnitScenarioNameNumber();
					UnitCreate(0, "Cinematic Block", x*2, t*16+8, 90);
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitChangeProtoUnit("Summoning Tree");
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trSetSelectedScale(0.8,0.4,0.8);
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitSetAnimationPath("0,1,1,1,1,1,0");
				}
				else{
					temp = trGetNextUnitScenarioNameNumber();
					trQuestVarSetFromRand("temph",0,360,true);
					UnitCreate(0, "Cinematic Block", x*2, t*16+8, 1*trQuestVarGet("temph"));
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitChangeProtoUnit("Spy Eye");
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trMutateSelected(kbGetProtoUnitID("Berry Bush"));
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trSetScale(2.5);
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitOverrideAnimation(2, 0, true, true, -1, 0);
				}
			}
		}
		trQuestVarSet("PlayersDoneTutorial", 0);
		for(p=1 ; < cNumberNonGaiaPlayers){
			//projectile speed
			modifyProtounitAbsolute("Wadjet Spit", p, 1, 10);
			trTechSetStatus(p, 108, 4);
			trPlayerKillAllGodPowers(p);
			trForbidProtounit(p, "Armory");
			trUnforbidProtounit(p, "Tower");
			//limit
			modifyProtounitAbsolute("Tower", p, 10, 1);
			//build points = how many s to build
			modifyProtounitAbsolute("Tower", p, 4, 4);
			trForbidProtounit(p, "House");
			trForbidProtounit(p, "Dock");
			trForbidProtounit(p, "Temple");
			trForbidProtounit(p, "Settlement Level 1");
			trForbidProtounit(p, "Wall Connector");
			trForbidProtounit(p, "Wall Short");
			trForbidProtounit(p, "Wall Medium");
			trForbidProtounit(p, "Wall Long");
			trQuestVarSet("P"+p+"DoneTutorial", 0);
			trQuestVarSet("P"+p+"FountainMsg", 0);
			trPaintTerrain(5,((p*8)-2),35,((p*8+4)-2),4,32);
			//trPaintTerrain(7,p*8,7,p*8,0,73); //start sq
			PaintAtlantisArea(6,p*8-1,8,p*8+1,12,1);  //start sq
			// cliff
			//main body
			trChangeTerrainHeight(4,p*8+3,35+2,p*8-2,2,false);
			
			PaintAtlantisArea(34-1, p*8-1, 34+1, p*8+1,12,1);
			/*	temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(0, "Cinematic Block", 34*2, p*16, 270);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Zebra");
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitHighlight(100, true);*/
			/*trUnitSelectClear();
			trUnitSelect(""+temp);
			trMutateSelected(kbGetProtoUnitID("Summoning Tree"));
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trSetScale(0.5);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitSetAnimationPath("0,1,0,0,0");*/
			xAddDatabaseBlock(dTemp, true);
			xSetInt(dTemp, xUnitID, temp);
			xSetInt(dTemp, xExtra, p);
			CreateChicken(p,14,16*p,90);
			xSetPointer(dPlayerData, p);
			xSetInt(dPlayerData, xPlayerUnitID, 1*trQuestVarGet("P"+p+"Unit"));
			if(trCurrentPlayer() == p){
				trCounterAddTime("cdtutorial", -100, -200, "<color={PlayerColor("+p+")}>Use 'Q' to build a tower at the cursor", -1);
			}
			trUnforbidProtounit(p, "Tower");
			trForbidProtounit(p, "Armory");
		}
		playSound("\cinematics\16_in\music.mp3");
		refreshPassability();
		xsEnableRule("Animations");
		//bored anim when swimming and maybe pivot height scale to 2
		xsEnableRule("FirstTower");
		//xsEnableRule("GoatJumpEnd");
		//xsEnableRule("ExtraJumpTech");
		//	xsEnableRule("Charge");
		//	xsDisableRule("VectorFirst");
		//	xsDisableRule("VectorSecond");
		//xsEnableRule("CrocTutorialDone");
		trDelayedRuleActivation("ChickenMechanicLoops");
		trDelayedRuleActivation("ChickenTutorialLoops");
		if(QuickStart == 0){
			startNPCDialog(14);
		}
		refreshPassability();
		uiZoomToProto(""+ChickenProto);
		uiLookAtProto(""+ChickenProto);
		xsDisableSelf();
		xsEnableRule("Testing");
	}
}

rule FirstTower
inactive
highFrequency
{
	int temp = 0;
	for(p = 1; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		if((trPlayerUnitCountSpecific(p, "Tower") != 0) && (1*trQuestVarGet("P"+p+"FountainMsg") == 0)){
			trQuestVarSet("P"+p+"FountainMsg", 1);
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(cNumberNonGaiaPlayers, "Cinematic Block", 34*2, p*16, 270);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Hoplite");
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitMoveToPoint(2,2,p*16,-1,true);
			xAddDatabaseBlock(dEnemies, true);
			xSetInt(dEnemies, xUnitID, temp);
			if(trCurrentPlayer() == p){
				startNPCDialog(15);
				trCounterAbort("cdtutorial");
				trCounterAddTime("cdtutorial", -100, -200, "<color={PlayerColor("+p+")}>Use 'W' to craft a relic at the cursor", -1);
			}
			trUnforbidProtounit(p, "Armory");
		}
	}
}

rule Testing
inactive
highFrequency
{
	if(xGetDatabaseCount(dMissiles) > 0){
		DoMissileStage5();
	}
}

void ProcessFreeRelics(int count = 0){
	for (x=xsMin(count, xGetDatabaseCount(dFreeRelics)); > 0) {
		xDatabaseNext(dFreeRelics);
		xUnitSelect(dFreeRelics, xUnitID);
		if (trUnitGetIsContained("Unit")) {
			for(p=1; < cNumberNonGaiaPlayers) {
				if (trUnitIsOwnedBy(p)) {
					trMutateSelected(relicProto(xGetInt(dFreeRelics, xRelicType)));
					trSetSelectedScale(0,0,-1);
					trUnitSetAnimationPath("1,0,1,1,0,0,0");
					if (trCurrentPlayer() == p) {
						ColouredChatToPlayer(p, "1,0.5,0", relicName(xGetInt(dFreeRelics, xUnitID)));
						trSoundPlayFN("researchcomplete.wav","1",-1,"","");
					}
					FunctionRelic(true, p);
					trUnitSelectClear();
					xUnitSelect(dFreeRelics, xSFXID);
					trUnitChangeProtoUnit("Rocket");
					xAddDatabaseBlock(dHeldRelics, true);
					xSetInt(dHeldRelics, xUnitID, 1*xGetInt(dFreeRelics, xUnitID));
					xSetInt(dHeldRelics, xRelicType, 1*xGetInt(dFreeRelics, xRelicType));
					xSetFloat(dHeldRelics, xRelicStat, xGetFloat(dFreeRelics, xRelicStat));
					xFreeDatabaseBlock(dFreeRelics);
					break;
				}
			}
		} else if (trUnitIsSelected()) {
			uiClearSelection();
			uiMessageBox(relicName(xGetInt(dFreeRelics, xUnitID)));
		}
	}
}

void ProcessHeldRelics(int count = 1) {
	int dropper = 0;
	for (x=xsMin(count, xGetDatabaseCount(dHeldRelics)); > 0) {
		xDatabaseNext(dHeldRelics);
		xUnitSelect(dHeldRelics, xUnitID);
		//If relic is dropped
		for(p=1; < cNumberNonGaiaPlayers) {
			if (trUnitIsOwnedBy(p)) {
				//WHO DROPPED THE RELIC
				//trChatSend(0, "Held by p"+p+"");
				dropper = p;
			}
		}
		if (trUnitGetIsContained("Unit") == false) {
			FunctionRelic(false, dropper);
			ColouredChatToPlayer(dropper, "1,0.2,0", relicName(xGetInt(dFreeRelics, xUnitID)) + " dropped");
			trUnitChangeProtoUnit("Relic");
			xUnitSelect(dHeldRelics, xUnitID);
			xAddDatabaseBlock(dFreeRelics, true);
			xUnitSelect(dHeldRelics, xUnitID);
			trUnitChangeProtoUnit("Titan Atlantean");
			yFindLatestReverse("SFXUnit", "Titan Gate Dead", 0);
			DoRelicSFX(1*trQuestVarGet("SFXUnit"), xGetInt(dHeldRelics, xRelicType));
			xUnitSelect(dHeldRelics, xUnitID);
			trUnitChangeProtoUnit("Relic");
			xSetInt(dFreeRelics, xUnitID, 1*xGetInt(dHeldRelics, xUnitID));
			xSetInt(dFreeRelics, xRelicType, 1*xGetInt(dHeldRelics, xRelicType));
			xSetFloat(dFreeRelics, xRelicStat, xGetFloat(dHeldRelics, xRelicStat));
			xSetInt(dFreeRelics, xSFXID, 1*trQuestVarGet("SFXUnit"));
			xFreeDatabaseBlock(dHeldRelics);
			break;
		}
	}
}

rule ChickenMechanicLoops
highFrequency
inactive
{
	ProcessFreeRelics(1);
	ProcessHeldRelics(1);
	for(p = 1; < cNumberNonGaiaPlayers){
		if(trPlayerUnitCountSpecific(p, "Armory") > 0){
			yFindLatestReverse("ArmoryP"+p, "Armory", p);
			trUnitSelectByQV("ArmoryP"+p);
			trUnitChangeProtoUnit("Relic");
			trUnitSelectByQV("ArmoryP"+p);
			trUnitConvert(0);
			if(TutorialMode == true){
				ForceRelic(1*trQuestVarGet("ArmoryP"+p),1,1);
			}
			//add to db held relics as will be owned by 0
		}
	}
	
}

rule ChickenTutorialLoops
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
				trPaintTerrain(5,((p*8)-2),40,((p*8+4)-2),getTerrainType("black"), getTerrainSubType("black"));
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
			if((1*trQuestVarGet("P"+p+"FountainMsg") == 3) && (1*trQuestVarGet("P"+p+"DoneTutorial") == 0)){
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
				trPaintWaterColor(vector(0,1,0), 0,((p*8)-2),40,((p*8+4)-2));
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
				CreateChicken(p, 14, p*16, 90);
			}
			if((trPlayerUnitCountSpecific(p, ChickenProto) == 0) && (1*trQuestVarGet("P"+p+"DoneTutorial") == 0)){
				trUnitSelectByQV("P"+p+"Unit");
				trUnitChangeProtoUnit("Ragnorok SFX");
				trUnitSelectByQV("P"+p+"Unit");
				trUnitDestroy();
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
				trUnitChangeProtoUnit("Hero Death");
				CreateChicken(p, 14, p*16, 90);
			}
		}
	}
}
