rule TutorialTerrainGoat
highFrequency
inactive
{
	if (trTime() > cActivationTime + 1) {
		trCameraCut(vector(-65.460060,123.743729,-65.460060), vector(0.500000,-0.707107,0.500000), vector(0.500000,0.707107,0.500000), vector(0.707107,0.000000,-0.707107));
		xsDisableRule("DeerTutorialDone");
		xsDisableRule("RhinoTutorialDone");
		TutorialMode = true;
		Stage = 3;
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
			CreateGoat(p,14,16*p,90);
			xSetPointer(dPlayerData, xPlayerUnitID);
			xSetInt(dPlayerData, xPlayerUnitID, 1*trQuestVarGet("P"+p+"Unit"));
			xSetInt(dPlayerData, xTarget, 0);
			if(trCurrentPlayer() == p){
				trCounterAddTime("cdtutorial", -100, -200, "<color={PlayerColor("+p+")}>Press 'Q' to jump to the cursor.", -1);
			}
		}
		trChangeTerrainHeight(10,0,12,30,10,false);
		refreshPassability();
		xsEnableRule("Animations");
		xsEnableRule("GoatJump");
		xsEnableRule("GoatJumpEnd");
		//	xsEnableRule("Charge");
		//	xsDisableRule("Jump");
		//	xsDisableRule("VectorFirst");
		//	xsDisableRule("VectorSecond");
		//	xsEnableRule("GoatTutorialDone");
		//	trDelayedRuleActivation("GoatTutorialLoops");
		//	if(QuickStart == 0){
		//		startNPCDialog(6);
		//	}
		refreshPassability();
		uiZoomToProto(""+GoatProto);
		uiLookAtProto(""+GoatProto);
		xsDisableSelf();
	}
}

rule GoatJump
highFrequency
inactive
{
	int anim = 0;
	for(p=1 ; < cNumberNonGaiaPlayers){
		if(trPlayerResourceCount(p, "Gold") > 0){
			xSetPointer(dPlayerData, p);
			trPlayerGrantResources(p, "Gold", -100000);
			if(xGetBool(dPlayerData, xReadyToLeave) == false){
				trUnitSelectClear();
				trUnitSelectByQV("P"+p+"Unit");
				trMutateSelected(kbGetProtoUnitID("Anubite"));
				//trUnitChangeProtoUnit("Hero Greek Bellerophon");
				trSetSelectedScale(0,6,0);
				xSetInt(dPlayerData, xOldAnim, -10);
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
				trUnitOverrideAnimation(24, 0, true, false, -1, 0);
				xSetInt(dPlayerData, xTarget, trGetNextUnitScenarioNameNumber());
				//Greta heading 0 to player heading
				UnitCreate(cNumberNonGaiaPlayers, "Female", xsVectorGetX(xGetVector(dPlayerData,xGoatTarget)), xsVectorGetZ(xGetVector(dPlayerData,xGoatTarget)), 0);
				xUnitSelect(dPlayerData, xTarget);
				trSetSelectedScale(0.1,0.1,0.1);
				//trSetUnitOrientation(trVectorQuestVarGet("V"+p+"dir"), vector(0,1,0), true);
				trUnitSelectClear();
				trUnitSelectByQV("P"+p+"Unit");
				trUnitDoWorkOnUnit(""+xGetInt(dPlayerData, xTarget),-1);
				xAddDatabaseBlock(dDestroyMe, true);
				xSetInt(dDestroyMe, xDestroyName, xGetInt(dPlayerData, xTarget));
				xSetInt(dDestroyMe, xDestroyTime, trTimeMS()+4800);
			}
		}
		if(trPlayerResourceCount(p, "Wood") > 0){
			trPlayerGrantResources(p, "Wood", -100000);
		}
		if(trPlayerResourceCount(p, "Food") > 0){
			trPlayerGrantResources(p, "Food", -100000);
		}
		//jump set anim to 13
	}
	for (x= xGetDatabaseCount(dDestroyMe); > 0) {
		xDatabaseNext(dDestroyMe);
		if(trTimeMS() > xGetInt(dDestroyMe, xDestroyTime)){
			xUnitSelect(dDestroyMe, xDestroyName);
			trUnitDestroy();
			//trUnitDestroy();
			//trChatSend(0, "<color=1,0,0>"+xGetInt(dDestroyMe, xDestroyName));
			xFreeDatabaseBlock(dDestroyMe);
		}
	}
}

rule GoatJumpEnd
highFrequency
inactive
{
	for(p=1 ; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		if(xGetInt(dPlayerData, xTarget) > 0){
			trUnitSelectClear();
			trUnitSelect(""+xGetInt(dPlayerData, xTarget));
			if((trUnitPercentDamaged() > 0) || (trUnitDead())){
				xUnitSelect(dPlayerData, xTarget);
				trUnitConvert(p);
				trMutateSelected(kbGetProtoUnitID("Transport Ship Greek"));
				trSetSelectedScale(0,1,0);
				
				trUnitSelectByQV("P"+p+"Unit");
				trImmediateUnitGarrison(""+xGetInt(dPlayerData, xTarget));
				xUnitSelect(dPlayerData, xTarget);
				trUnitEjectContained();
				//trUnitChangeProtoUnit("Dwarf");
				
				xUnitSelect(dPlayerData, xTarget);
				trUnitDestroy();
				
				xSetInt(dPlayerData, xTarget, 0);
				
				trUnitSelectByQV("P"+p+"Unit");
				if(xGetBool(dPlayerData, xReadyToLeave) == false){
					trMutateSelected(kbGetProtoUnitID(""+GoatProto));
				}
				if(xGetBool(dPlayerData, xReadyToLeave) == true){
					trMutateSelected(kbGetProtoUnitID("Prisoner"));
				}
				trSetSelectedScale(0,1,0);
				
				//trUnitSelectByQV("P"+p+"Unit");
				//trSetUnitOrientation(trVectorQuestVarGet("V"+p+"dir"), vector(0,1,0), true);
				
				xSetInt(dPlayerData, xOldAnim, 2);
				
				xUnitSelect(dPlayerData, xSpyID);
				//trUnitOverrideAnimation(13, 0, false, false, -1, 0);
				trUnitOverrideAnimation(2, 0, true, true, -1, 0);
				
				trVectorQuestVarSet("P"+p+"Pos", kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
			}
		}
		trUnitSelectClear();
	}
}
