//You have to move to be granted vision

rule TutorialTerrain
highFrequency
inactive
{
	//if (trTime() > cActivationTime + 1) {
	xsDisableSelf();
	//trLetterBox(false);
	clearMap("black", 5.0);
	trPaintTerrain(0,0,35,cNumberNonGaiaPlayers*8,2,4);
	int temp = 0;
	//trees
	for(t=0 ; < cNumberNonGaiaPlayers){
		for(x=0 ; < 36){
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(0, "Cinematic Block", x*2, t*16+8, 90);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trUnitChangeProtoUnit("Gaia Forest Tree");
			trUnitSelectClear();
			trUnitSelect(""+temp);
			trSetSelectedScale(2,0.3,1);
		}
	}
	for(p=1 ; < cNumberNonGaiaPlayers){
		trPaintTerrain(5,((p*8)-2),30,((p*8+4)-2),0,2);
		trPaintTerrain(7,p*8,7,p*8,0,73); //start sq
		trPaintTerrain(28,p*8+2,28,p*8-2,0,74); //end line
		//start log
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(0, "Cinematic Block", 20, p*16, 90);
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeProtoUnit("Rotting Log");
		trSetSelectedScale(2,3,2);
		//end log
		//start log
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(0, "Cinematic Block", 32, p*16, 90);
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeProtoUnit("Rotting Log");
		trSetSelectedScale(2,3,2);
		//end log
		//start log
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(0, "Cinematic Block", 46, p*16, 90);
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeProtoUnit("Rotting Log");
		trSetSelectedScale(2,3,2);
		//end log
		trPaintTerrain(10,p*8+2,10,p*8-2,2,4); //first log
		trPaintTerrain(16,p*8+2,16,p*8-2,2,4); //second log
		trPaintTerrain(23,p*8+2,23,p*8-2,2,4); //THIRD log
		trQuestVarSet("P"+p+"Unit", trGetNextUnitScenarioNameNumber());
		UnitCreate(p, ""+GazelleProto, 14, p*16, 90);
		trSetSelectedScale(0,1,0);
		UnitCreate(0, "Revealer to Player", 16, p*16, 90);
		trUnitSelectByQV("P"+p+"Unit");
		spyEffect(kbGetProtoUnitID("Gazelle"),0, xsVectorSet(dPlayerData,xSpyID,p), vector(1,1,1));
		trQuestVarSet("P"+p+"CanHaveVision", 1);
		trUnitSelectClear();
		trUnitSelectByQV("P"+p+"Unit");
		trUnitMoveToPoint(16,0,p*16+1, -1, false);
		xSetPointer(dPlayerData, xPlayerUnitID);
		xSetInt(dPlayerData, xPlayerUnitID, 1*trQuestVarGet("P"+p+"Unit"));
	}
	trPaintTerrain(0,0,0,0,2,4,true);
	xsEnableRule("Animations");
	xsEnableRule("Jump");
	xsEnableRule("JumpEnd");
	trDelayedRuleActivation("VectorSecond");
	if(QuickStart == 0){
		xsEnableRule("TutorialMsg1");
		startNPCDialog(2);
	}
}

rule ResetBlackmap
highFrequency
inactive
{
	xsDisableSelf();
	trPlayerResetBlackMapForAllPlayers();
}

rule TutorialVectorCheck
highFrequency
inactive
{
	int temp = 0;
	for(p=1 ; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
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
		}
		if((trVectorQuestVarGetX("P"+p+"Pos") > 58) && (1*trQuestVarGet("P"+p+"DoneTutorial") == 0)){
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
			trClearCounterDisplay();
			trSetCounterDisplay("<color={PlayerColor(" + GreenText() + ")}>Tutorial complete: " + temp + " / " + PlayersActive);
			if((temp == 1) && (PlayersActive > 1)){
				//timeout
			}
			if(trCurrentPlayer() == p){
				playSound("ageadvance.wav");
			}
		}
		if((trVectorQuestVarGetZ("P"+p+"Pos") > (p*16+8)) && (1*trQuestVarGet("P"+p+"DoneTutorial") == 0)){
			trUnitSelectByQV("P"+p+"Unit");
			trUnitTeleport(trVectorQuestVarGetX("P"+p+"Pos"),3,p*16);
		}
		if((trVectorQuestVarGetZ("P"+p+"Pos") < (p*16-8)) && (1*trQuestVarGet("P"+p+"DoneTutorial") == 0)){
			trUnitSelectByQV("P"+p+"Unit");
			trUnitTeleport(trVectorQuestVarGetX("P"+p+"Pos"),3,p*16);
		}
	}
}

rule DeerTutorialDone
highFrequency
inactive
{
	if(PlayersActive == 1*trQuestVarGet("PlayersDoneTutorial")){
		xsDisableSelf();
		xsDisableRule("TutorialVectorCheck");
		xsEnableRule("BuildDeerArea");
		trClearCounterDisplay();
		trQuestVarSet("PlayersDoneTutorial", 0);
		trLetterBox(true);
		trUIFadeToColor(0,0,0,1,1,true);
		characterDialog("Act I - Deer", " ", "icons\animal gazelle icon 64");
		trSetFogAndBlackmap(true,true);
		trDelayedRuleActivation("ResetBlackmap");
		/*
		trShowImageDialog("icons\icon class harmless animal", "Entering Bullshit Forest");
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
		*/
	}
}

rule TutorialMsg1
highFrequency
inactive
{
	if (trTime() > cActivationTime + 5) {
		startNPCDialog(3);
		trDelayedRuleActivation("TutorialVectorCheck");
		trDelayedRuleActivation("DeerTutorialDone");
		xsDisableSelf();
		/*
		gadgetReal("ShowImageBox-BordersTop");
		gadgetReal("ShowImageBox-BordersBottom");
		gadgetReal("ShowImageBox-BordersLeft");
		gadgetReal("ShowImageBox-BordersRight");
		gadgetReal("ShowImageBox-BordersLeftTop");
		gadgetReal("ShowImageBox-BordersLeftBottom");
		gadgetReal("ShowImageBox-BordersRightBottom");
		gadgetReal("ShowImageBox-BordersRightTop");
		gadgetReal("ShowImageBox-CloseButton");
		gadgetUnreal("ShowImageBox");
		*/
	}
}

rule Animations
highFrequency
inactive
{
	int anim = 0;
	for(p=1 ; < cNumberNonGaiaPlayers){
		anim = 0;
		anim = kbUnitGetAnimationActionType(kbGetBlockID(""+1*trQuestVarGet("P"+p+"Unit")+""));
		xSetPointer(dPlayerData, p);
		/*if(p == 1){
			trChatSend(0, ""+anim);
		}*/
		if((xGetInt(dPlayerData, xOldAnim) == anim) || (xGetInt(dPlayerData, xOldAnim) == -10)){
			continue;
			//Stop if no anim change
		}
		xSetInt(dPlayerData, xOldAnim, anim);
		if((anim == 10) || (anim == 11)){
			trUnitSelectClear();
			trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
			trUnitOverrideAnimation(15, 0, true, true, -1, 0);
		}
		if(anim == 9){
			trUnitSelectClear();
			trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
			trUnitOverrideAnimation(2, 0, true, true, -1, 0);
		}
		//jump set anim to 13
	}
}

rule Jump
highFrequency
inactive
{
	int anim = 0;
	for(p=1 ; < cNumberNonGaiaPlayers){
		if(trPlayerResourceCount(p, "Gold") > 0){
			xSetPointer(dPlayerData, p);
			trPlayerGrantResources(p, "Gold", -100000);
			trUnitSelectClear();
			trUnitSelectByQV("P"+p+"Unit");
			trMutateSelected(kbGetProtoUnitID("Hero Greek Bellerophon"));
			//trUnitChangeProtoUnit("Hero Greek Bellerophon");
			trSetSelectedScale(0,1,0);
			xSetInt(dPlayerData, xOldAnim, -10);
			trUnitSelectClear();
			trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
			trUnitOverrideAnimation(13, 0, true, false, -1, 0);
			xSetInt(dPlayerData, xTarget, trGetNextUnitScenarioNameNumber());
			//Greta heading 0 to player heading
			UnitCreate(cNumberNonGaiaPlayers, "Female", trVectorQuestVarGetX("V"+p+"Second"), trVectorQuestVarGetZ("V"+p+"Second"), 0);
			xUnitSelect(dPlayerData, xTarget);
			trSetSelectedScale(1,0,1);
			trSetUnitOrientation(trVectorQuestVarGet("V"+p+"dir"), vector(0,1,0), true);
			trUnitSelectClear();
			trUnitSelectByQV("P"+p+"Unit");
			trUnitDoWorkOnUnit(""+xGetInt(dPlayerData, xTarget),-1);
			xAddDatabaseBlock(dDestroyMe, true);
			xSetInt(dDestroyMe, xDestroyName, xGetInt(dPlayerData, xTarget));
			xSetInt(dDestroyMe, xDestroyTime, trTimeMS()+2300);
		}
		//jump set anim to 13
	}
	for (x= xGetDatabaseCount(dDestroyMe); > 0) {
		xDatabaseNext(dDestroyMe);
		if(trTimeMS() > xGetInt(dDestroyMe, xDestroyTime)){
			xUnitSelect(dDestroyMe, xDestroyName);
			trDamageUnit(100);
			//trUnitDestroy();
			//trChatSend(0, "<color=1,0,0>"+xGetInt(dDestroyMe, xDestroyName));
			xFreeDatabaseBlock(dDestroyMe);
		}
	}
}

rule JumpEnd
highFrequency
inactive
{
	for(p=1 ; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		if(xGetInt(dPlayerData, xTarget) > 0){
			trUnitSelectClear();
			trUnitSelect(""+xGetInt(dPlayerData, xTarget));
			if(trUnitPercentDamaged() > 0){
				xUnitSelect(dPlayerData, xTarget);
				trUnitConvert(p);
				trMutateSelected(kbGetProtoUnitID("Transport Ship Greek"));
				trSetSelectedScale(0,1,0);
				
				trUnitSelectByQV("P"+p+"Unit");
				trImmediateUnitGarrison(""+xGetInt(dPlayerData, xTarget));
				trUnitChangeProtoUnit("Dwarf");
				
				xUnitSelect(dPlayerData, xTarget);
				trUnitDestroy();
				
				xSetInt(dPlayerData, xTarget, 0);
				
				trUnitSelectByQV("P"+p+"Unit");
				trMutateSelected(kbGetProtoUnitID(""+GazelleProto));
				trSetSelectedScale(0,1,0);
				
				trUnitSelectByQV("P"+p+"Unit");
				trSetUnitOrientation(trVectorQuestVarGet("V"+p+"dir"), vector(0,1,0), true);
				
				xSetInt(dPlayerData, xOldAnim, 2);
				
				xUnitSelect(dPlayerData, xSpyID);
				//trUnitOverrideAnimation(13, 0, false, false, -1, 0);
				trUnitOverrideAnimation(2, 0, true, true, -1, 0);
				trQuestVarSet("P"+p+"CanHaveVision", 1);
				trVectorQuestVarSet("P"+p+"Pos", kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
				if(1*trQuestVarGet("P"+p+"FirstJump") == 0){
					trQuestVarSet("P"+p+"FirstJump", 1);
					if(trCurrentPlayer() == p){
						startNPCDialog(4);
					}
				}
			}
		}
		trUnitSelectClear();
	}
}

rule VectorFirst
highFrequency
inactive
{
	for(p=1 ; < cNumberNonGaiaPlayers){
		trVectorQuestVarSet("V"+p+"Third", kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
		if(trVectorQuestVarGet("V"+p+"Third") != trVectorQuestVarGet("P"+p+"Pos")){
			trVectorQuestVarSet("V"+p+"Second", kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
			trVectorQuestVarSet("V"+p+"Second", trVectorQuestVarGet("V"+p+"Second") - trVectorQuestVarGet("P"+p+"Pos"));
			trVectorQuestVarSet("V"+p+"Second", xsVectorNormalize(trVectorQuestVarGet("V"+p+"Second")));
			trVectorQuestVarSet("V"+p+"dir", trVectorQuestVarGet("V"+p+"Second"));
			trVectorQuestVarSet("V"+p+"Second", xsVectorSet(trVectorQuestVarGetX("V"+p+"Second") * 10,trVectorQuestVarGetY("V"+p+"Second") * 1,trVectorQuestVarGetZ("V"+p+"Second") * 10));
			trVectorQuestVarSet("V"+p+"Second", trVectorQuestVarGet("V"+p+"Second") + trVectorQuestVarGet("P"+p+"Pos"));
			if(1*trQuestVarGet("P"+p+"CanHaveVision") == 1){
				trQuestVarSet("P"+p+"CanHaveVision", 0);
			}
		}
	}
	xsDisableSelf();
	trDelayedRuleActivation("VectorSecond");
}

rule VectorSecond
highFrequency
inactive
{
	for(p=1 ; < cNumberNonGaiaPlayers){
		trVectorQuestVarSet("P"+p+"Pos", kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
	}
	xsDisableSelf();
	trDelayedRuleActivation("VectorFirst");
}
