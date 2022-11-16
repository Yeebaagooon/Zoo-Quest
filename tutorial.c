string GazelleProto = "Hero Greek Jason";

rule TutorialTerrain
highFrequency
inactive
{
	//if (trTime() > cActivationTime + 1) {
	xsDisableSelf();
	//trLetterBox(false);
	trPaintTerrain(0,0,35,cNumberNonGaiaPlayers*8,2,4);
	for(p=1 ; < cNumberNonGaiaPlayers){
		//	trPlayerSetDiplomacy(0, p, "Enemy");
		//	trPlayerSetDiplomacy(cNumberNonGaiaPlayers, p, "Enemy");
		//	trPlayerSetDiplomacy(p, cNumberNonGaiaPlayers, "Enemy");
		trPaintTerrain(5,((p*8)-2),30,((p*8+4)-2),0,2);
		trPaintTerrain(7,p*8,7,p*8,0,73); //start sq
		trPaintTerrain(28,p*8+2,28,p*8-2,0,74); //end line
		trPaintTerrain(0,0,0,0,2,4,true);
		trQuestVarSet("P"+p+"Unit", trGetNextUnitScenarioNameNumber());
		UnitCreate(p, ""+GazelleProto, 14, p*16, 90);
		trSetSelectedScale(0,1,0);
		UnitCreate(0, "Revealer to Player", 14, p*16, 90);
		spyEffect(1*trQuestVarGet("P"+p+"Unit"), kbGetProtoUnitID("Gazelle"), xsVectorSet(dPlayerData,xSpyID,p), vector(1,1,1));
		//spyEffect(1*trQuestVarGet("P"+p+"Unit"), kbGetProtoUnitID("Gazelle"), vector(1,1,1), vector(1,1,1));
		trTechGodPower(p, "Vision", 1);
	}
	xsEnableRule("Animations");
	xsEnableRule("Jump");
	xsEnableRule("JumpEnd");
	//}
}

rule Animations
highFrequency
inactive
{
	int anim = 0;
	for(p=1 ; < cNumberNonGaiaPlayers){
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
			UnitCreate(cNumberNonGaiaPlayers, "Female", 14, 16, 0);
			trUnitSelectClear();
			trUnitSelect(""+xGetInt(dPlayerData, xTarget));
			trSetSelectedScale(0,0,0);
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
			}
		}
		trUnitSelectClear();
	}
}
