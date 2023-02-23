rule TutorialTerrainCrocodile
highFrequency
inactive
{
	if (trTime() > cActivationTime + 1) {
		trCameraCut(vector(-65.460060,123.743729,-65.460060), vector(0.500000,-0.707107,0.500000), vector(0.500000,0.707107,0.500000), vector(0.707107,0.000000,-0.707107));
		xsDisableRule("DeerTutorialDone");
		xsDisableRule("RhinoTutorialDone");
		xsDisableRule("GoatTutorialDone");
		xsDisableRule("Jump");
		xsDisableRule("JumpEnd");
		NewDestroyNumber = trGetNextUnitScenarioNameNumber()-1;
		TutorialMode = true;
		Stage = 4;
		CliffType = 3;
		CliffSubType = 2;
		//trLetterBox(false);
		clearMap("black", -5.0);
		paintWaterKeepingMapPassable(1,3,vector(1,1,1));
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
					trUnitChangeProtoUnit("Rock River Icy");
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trSetScale(1.65);
				}
				else{
					temp = trGetNextUnitScenarioNameNumber();
					UnitCreate(0, "Cinematic Block", x*2, t*16+8, 90);
					trUnitSelectClear();
					trUnitSelect(""+temp);
					trUnitChangeProtoUnit("Pine Snow");
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
			trPaintTerrain(5,((p*8)-2),40,((p*8+4)-2),0,50);
			//trPaintTerrain(7,p*8,7,p*8,0,73); //start sq
			PaintAtlantisArea(6,p*8-1,8,p*8+1,0,53);  //start sq
			trPaintTerrain(28,p*8+2,28,p*8-2,0,74); //end line
			// cliff
			//main body
			trChangeTerrainHeight(4,p*8+3,11,p*8-2,2,false);
			trChangeTerrainHeight(14,p*8+3,17,p*8-2,8,false);
			for(a=1 ; < 15){
				trChangeTerrainHeight(17+a-1,p*8+3,17+a,p*8-2,2-a*0.5,false);
			}
			/*
			trChangeTerrainHeight(12,p*8+2,16,p*8-2,10,false);
			trPaintTerrain(11,p*8+2,16,p*8-2,CliffType,CliffSubType);
			trPaintTerrain(12,p*8+1,15,p*8-2,0,50);
			
			trChangeTerrainHeight(20,p*8+2,24,p*8-2,10,false);
			trPaintTerrain(19,p*8+2,24,p*8-2,CliffType,CliffSubType);
			trPaintTerrain(20,p*8+1,23,p*8-2,0,50);*/
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(cNumberNonGaiaPlayers, "Cinematic Block", 28*2, p*16-4, 0);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Fence Stone");
			xAddDatabaseBlock(dTemp, true);
			xSetInt(dTemp, xUnitID, temp);
			xSetInt(dTemp, xExtra, p);
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(cNumberNonGaiaPlayers, "Cinematic Block", 28*2, p*16, 0);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Fence Stone");
			xAddDatabaseBlock(dTemp, true);
			xSetInt(dTemp, xUnitID, temp);
			xSetInt(dTemp, xExtra, p);
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(cNumberNonGaiaPlayers, "Cinematic Block", 28*2, p*16+4, 180);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Fence Stone");
			xAddDatabaseBlock(dTemp, true);
			xSetInt(dTemp, xUnitID, temp);
			xSetInt(dTemp, xExtra, p);
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(0, "Cinematic Block", 34*2, p*16, 270);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Shrine");
			//trUnitSelectClear();
			//trUnitSelect(""+temp);
			//trMutateSelected(kbGetProtoUnitID("Shrine"));
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitSetAnimationPath("2,0,0,0,0");
			xAddDatabaseBlock(dTemp, true);
			xSetInt(dTemp, xUnitID, temp);
			xSetInt(dTemp, xExtra, p);
			CreateCroc(p,14,16*p,90);
			xSetPointer(dPlayerData, xPlayerUnitID);
			xSetInt(dPlayerData, xPlayerUnitID, 1*trQuestVarGet("P"+p+"Unit"));
			xSetInt(dPlayerData, xTarget, 0);
			xSetInt(dPlayerData, xTimeout, trTimeMS()*2);
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
		//xsEnableRule("GoatTutorialDone");
		//trDelayedRuleActivation("GoatTutorialLoops");
		if(QuickStart == 0){
			startNPCDialog(8);
		}
		refreshPassability();
		uiZoomToProto(""+CrocProto);
		uiLookAtProto(""+CrocProto);
		xsDisableSelf();
		xsEnableRule("Swimming");
	}
}

rule TestLoop
inactive
highFrequency
{
	
	//debugLog(""+(trGetWaterHeight(xsVectorGetX(test)/2, xsVectorGetZ(test)/2)-trGetTerrainHeight(xsVectorGetX(test)/2, xsVectorGetZ(test)/2)));
	//>1.25 = underwater
}

rule Swimming
inactive
highFrequency
{
	vector temppos = vector(0,0,0);
	for(p=1 ; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		temppos = kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit"));
		float tempheight = (trGetWaterHeight(xsVectorGetX(temppos)/2, xsVectorGetZ(temppos)/2)-trGetTerrainHeight(xsVectorGetX(temppos)/2, xsVectorGetZ(temppos)/2));
		if(xGetBool(dPlayerData, xSwimming) == false){
			if(tempheight >= 1.25){
				xSetBool(dPlayerData, xSwimming, true);
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
				trUnitOverrideAnimation(3, 0, true, true, -1, 0);
				trUnitSelectByQV("P"+p+"Unit");
				trSetSelectedScale(0,2,0);
			}
		}
		else{
			if(tempheight < 1.25){
				xSetBool(dPlayerData, xSwimming, false);
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
				trUnitOverrideAnimation(15, 0, true, true, -1, 0);
				trUnitSelectByQV("P"+p+"Unit");
				trSetSelectedScale(0,1,0);
			}
		}
		/*if(xGetBool(dPlayerData, xSwimming) == true){
			trUnitSelectByQV("P"+p+"Unit");
			trSetSelectedScale(0,1+tempheight/2,0);
		}*/
	}
}
