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
			for(x=0 ; < 46){
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
			trPaintTerrain(5,((p*8)-2),40,((p*8+4)-2),4,32);
			//trPaintTerrain(7,p*8,7,p*8,0,73); //start sq
			PaintAtlantisArea(6,p*8-1,8,p*8+1,12,1);  //start sq
			// cliff
			//main body
			trChangeTerrainHeight(4,p*8+3,39+2,p*8-2,2,false);
			
			PaintAtlantisArea(34-1, p*8-1, 34+1, p*8+1,0,39);
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(0, "Cinematic Block", 34*2, p*16, 270);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Zebra");
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitHighlight(100, true);
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
			playSound("\cinematics\16_in\music.mp3");
			if(trCurrentPlayer() == p){
				trCounterAddTime("cdtutorial", -100, -200, "<color={PlayerColor("+p+")}>Swim to the first island.", -1);
			}
		}
		
		refreshPassability();
		xsEnableRule("Animations");
		//bored anim when swimming and maybe pivot height scale to 2
		//xsEnableRule("GoatJump");
		//xsEnableRule("GoatJumpEnd");
		//xsEnableRule("ExtraJumpTech");
		//	xsEnableRule("Charge");
		//	xsDisableRule("VectorFirst");
		//	xsDisableRule("VectorSecond");
		//xsEnableRule("CrocTutorialDone");
		//trDelayedRuleActivation("CrocMechanicLoops");
		//trDelayedRuleActivation("CrocTutorialLoops");
		if(QuickStart == 0){
			startNPCDialog(10);
		}
		refreshPassability();
		uiZoomToProto(""+ChickenProto);
		uiLookAtProto(""+ChickenProto);
		xsDisableSelf();
	}
}
