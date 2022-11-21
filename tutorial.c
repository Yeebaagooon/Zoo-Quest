string GazelleProto = "Hero Greek Jason";

rule TutorialTerrain
highFrequency
inactive
{
	//if (trTime() > cActivationTime + 1) {
	xsDisableSelf();
	//trLetterBox(false);
	trPaintTerrain(0,0,35,cNumberNonGaiaPlayers*8,2,4);
	int temp = 0;
	for(p=1 ; < cNumberNonGaiaPlayers){
		//	trPlayerSetDiplomacy(0, p, "Enemy");
		//	trPlayerSetDiplomacy(cNumberNonGaiaPlayers, p, "Enemy");
		//	trPlayerSetDiplomacy(p, cNumberNonGaiaPlayers, "Enemy");
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
		UnitCreate(0, "Revealer to Player", 14, p*16, 90);
		spyEffect(1*trQuestVarGet("P"+p+"Unit"), kbGetProtoUnitID("Gazelle"), xsVectorSet(dPlayerData,xSpyID,p), vector(1,1,1));
		//spyEffect(1*trQuestVarGet("P"+p+"Unit"), kbGetProtoUnitID("Gazelle"), vector(1,1,1), vector(1,1,1));
		trTechGodPower(p, "Vision", 1);
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

rule TutorialMsg1
highFrequency
inactive
{
	if (trTime() > cActivationTime + 5) {
		startNPCDialog(3);
		xsDisableSelf();
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
			break;
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
		if(trPlayerGetPopulation(p) > 100){
			xSetPointer(dPlayerData, p);
			unitTransform("Vision Revealer", "Rocket");
			unitTransform("Vision SFX", "Rocket");
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
			trUnitSelectClear();
			trUnitSelect(""+xGetInt(dPlayerData, xTarget));
			trSetSelectedScale(1,0,1);
			trUnitSelectClear();
			trUnitSelectByQV("P"+p+"Unit");
			trUnitDoWorkOnUnit(""+xGetInt(dPlayerData, xTarget),-1);
		}
		//jump set anim to 13
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
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xTarget));
				trMutateSelected(kbGetProtoUnitID("Transport Ship Greek"));
				trUnitSelect(""+xGetInt(dPlayerData, xTarget));
				trUnitConvert(p);
				trUnitSelect(""+xGetInt(dPlayerData, xTarget));
				trSetSelectedScale(0,0,0);
				trUnitSelectByQV("P"+p+"Unit");
				trImmediateUnitGarrison(""+xGetInt(dPlayerData, xTarget));
				trUnitSelectByQV("P"+p+"Unit");
				trUnitChangeProtoUnit(""+GazelleProto);
				trUnitSelect(""+xGetInt(dPlayerData, xTarget));
				trUnitChangeProtoUnit("Rocket");
				xSetInt(dPlayerData, xTarget, 0);
				trUnitSelectClear();
				trUnitSelectByQV("P"+p+"Unit");
				trMutateSelected(kbGetProtoUnitID(""+GazelleProto));
				xSetInt(dPlayerData, xOldAnim, 2);
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
				//trUnitOverrideAnimation(13, 0, false, false, -1, 0);
				trUnitOverrideAnimation(2, 0, true, true, -1, 0);
				trTechGodPower(p, "Vision", 1);
				trVectorQuestVarSet("P"+p+"Pos", kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
				if(1*trQuestVarGet("P"+p+"FirstJump") == 0){
					trQuestVarSet("P"+p+"FirstJump", 1);
					if(trCurrentPlayer() == p){
						//startNPCDialog(4);
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
			trVectorQuestVarSet("V"+p+"Second", xsVectorSet(trVectorQuestVarGetX("V"+p+"Second") * 10,trVectorQuestVarGetY("V"+p+"Second") * 1,trVectorQuestVarGetZ("V"+p+"Second") * 10));
			trVectorQuestVarSet("V"+p+"Second", trVectorQuestVarGet("V"+p+"Second") + trVectorQuestVarGet("P"+p+"Pos"));
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

/*
Vector shozzle
trVectorQuestVarSet("V2", kbGetBlockPosition("0"));
trVectorQuestVarSet("V2", trVectorQuestVarGet("V2") - trVectorQuestVarGet("V1"));

trVectorQuestVarSet("V2", xsVectorNormalize(trVectorQuestVarGet("V2")));
trVectorQuestVarSet("V2", xsVectorSet(trVectorQuestVarGetX("V2") * 9,trVectorQuestVarGetY("V2") * 0,trVectorQuestVarGetZ("V2") * 9));

trVectorQuestVarSet("V2", trVectorQuestVarGet("V2") + trVectorQuestVarGet("V1"));

trArmyDispatch("1,10", "Ajax", 1, trVectorQuestVarGetX("V2"), trVectorQuestVarGetY("V2"), trVectorQuestVarGetZ("V2"), 0, true);
*/
