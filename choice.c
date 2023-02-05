int PlayerCycle = 1;
int ActionChoice = 0;
int ChoiceEffect = 0;
string YesChoiceUnitName = "Swordsman";
string NoChoiceUnitName = "Lancer";

rule AnswerConsequences
highFrequency
inactive
{
	//xsSetContextPlayer(0);
	//[REMEMBER THIS IS OPEN AND MAY NEED PLAYER SPECIFIC TAG]
	if(ActionChoice != 0){
		int p = ActionChoice;
		switch(ChoiceEffect)
		{
			case 0:
			{
				debugLog("NO CONSEQUENCE SET");
			}
			case 1:
			{
				trTechGodPower(p, "Vision", 1);
			}
			case 2:
			{
				trTechGodPower(p, "Serpents", 1);
			}
			case 3:
			{
				trQuestVarSet("SkipVotes", 1*trQuestVarGet("SkipVotes")+1);
				trClearCounterDisplay();
				trSetCounterDisplay("<color={PlayerColor(0)}>Votes to skip: " + 1*trQuestVarGet("SkipVotes"));
			}
			case 4:
			{
				xSetPointer(dPlayerData, p);
				xSetVector(dPlayerData, xVectorHold, kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
				xSetInt(dPlayerData, xTeleportDue, 1);
				trUnitSelectByQV("P"+p+"Unit");
				trUnitDestroy();
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
				trUnitChangeProtoUnit("Hero Death");
				trQuestVarSet("P"+p+"Unit", trGetNextUnitScenarioNameNumber());
				UnitCreate(p, ""+GazelleProto, 2*xsVectorGetX(StageVector)+7,2*xsVectorGetZ(StageVector)+10, 0);
				trUnitSelectByQV("P"+p+"Unit");
				trSetSelectedScale(0,1,0);
				trUnitSelectByQV("P"+p+"Unit");
				spyEffect(kbGetProtoUnitID("Gazelle"), 0, xsVectorSet(dPlayerData,xSpyID,p), vector(1,1,1));
				if(trCurrentPlayer() == p){
					uiZoomToProto(""+GazelleProto);
					uiLookAtProto(""+GazelleProto);
				}
			}
			case 5:
			{
				//Deer HP
				trModifyProtounit(""+GazelleProto, p, 0, 1);
				trModifyProtounit("Hero Greek Bellerophon", p, 0, 1);
				if(trCurrentPlayer() == p){
					playSound("researchcomplete.wav");
				}
			}
			case 6:
			{
				//Deer LOS
				trModifyProtounit(""+GazelleProto, p, 2, 4);
				trModifyProtounit("Hero Greek Bellerophon", p, 2, 4);
				if(trCurrentPlayer() == p){
					playSound("researchcomplete.wav");
				}
			}
			case 7:
			{
				//Deer speed
				trModifyProtounit(""+GazelleProto, p, 1, 0.5);
				trModifyProtounit("Hero Greek Bellerophon", p, 1, 0.5);
				if(trCurrentPlayer() == p){
					playSound("researchcomplete.wav");
				}
			}
			case 8:
			{
				//Deer minigame reward speed
				trModifyProtounit(""+GazelleProto, p, 1, 1);
				trModifyProtounit("Hero Greek Bellerophon", p, 1, 1);
				if(trCurrentPlayer() == p){
					playSound("researchcomplete.wav");
				}
			}
			case 9:
			{
				//Deer minigame reward LOS
				trModifyProtounit(""+GazelleProto, p, 2, 6);
				trModifyProtounit("Hero Greek Bellerophon", p, 2, 6);
				if(trCurrentPlayer() == p){
					playSound("researchcomplete.wav");
				}
			}
			case 10:
			{
				//Deer minigame reward hp
				trModifyProtounit(""+GazelleProto, p, 1, 2);
				trModifyProtounit("Hero Greek Bellerophon", p, 1, 2);
				if(trCurrentPlayer() == p){
					playSound("researchcomplete.wav");
				}
			}
			case 11:
			{
				//Deer minigame reward regen
				xSetPointer(dPlayerData, p);
				xSetInt(dPlayerData, xHPRegenTime, 30);
				xSetInt(dPlayerData, xHPRegen, xGetInt(dPlayerData, xHPRegen)+1);
				if(trCurrentPlayer() == p){
					playSound("researchcomplete.wav");
				}
			}
			case 12:
			{
				//Rhino HP
				trModifyProtounit(""+RhinoProto, p, 0, 2);
				trModifyProtounit(""+RhinoDrinkProto, p, 0, 2);
				if(trCurrentPlayer() == p){
					playSound("researchcomplete.wav");
				}
			}
		}
		trQuestVarSet("P"+ActionChoice+"YesAction", 0);
		trQuestVarSet("P"+ActionChoice+"NoAction", 0);
		trQuestVarSet("P"+ActionChoice+"ChoiceDialog", 0);
		ActionChoice = 0;
		//[Safety]
		unitTransform(""+YesChoiceUnitName + " Hero", "Cinematic Block");
		unitTransform(""+NoChoiceUnitName + " Hero", "Cinematic Block");
		if(trCurrentPlayer() == p){
			uiZoomToProto(""+GazelleProto);
			//uiLookAtProto(""+GazelleProto);
			uiLookAtUnit(1*trQuestVarGet("P"+p+"Unit"));
		}
		xsDisableSelf();
	}
}

//PlayerChoice(1, "Choose a god power again", "Vision", 1, "Serpents", 2);
//xsGetContextPlayer for problems

void PlayerChoice(int p = 0, string prompt = "Question", string answerone = "Answer 1", int effectone = 0, string answertwo = "Answer 2", int effecttwo = 0, int timeout = 10000){
	//xsDisableSelf();
	int temp = 0;
	//Check choice units alive
	//xsSetContextPlayer(-1);
	if(kbGetBlockID(""+1*trQuestVarGet("P"+p+"Yes")) == -1){
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(p, "Cinematic Block", p*3, 1, 0);
		trQuestVarSet("P"+p+"Yes", temp);
		debugLog("Choice selector dead");
	}
	if(kbGetBlockID(""+1*trQuestVarGet("P"+p+"No")) == -1){
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(p, "Cinematic Block", p*3, 1, 0);
		trQuestVarSet("P"+p+"No", temp);
		debugLog("Choice selector dead");
	}
	trUnitSelectByQV("P"+p+"No");
	trUnitChangeProtoUnit(""+NoChoiceUnitName);
	trUnitSelectByQV("P"+p+"No");
	trSetSelectedScale(0,0,0);
	trUnitSelectByQV("P"+p+"Yes");
	trUnitChangeProtoUnit(""+YesChoiceUnitName);
	trUnitSelectByQV("P"+p+"Yes");
	trSetSelectedScale(0,0,0);
	trQuestVarSet("P"+p+"YesAction", effectone);
	trQuestVarSet("P"+p+"NoAction", effecttwo);
	if(trCurrentPlayer() == p){
		trShowChoiceDialog(prompt, answerone, p, answertwo, p+12);
		//camera
	}
	trQuestVarSet("P"+p+"ChoiceDialog", 1);
	trQuestVarSet("P"+p+"ChoiceTimer", trTimeMS()+timeout);
	xsEnableRule("ChoiceTimeout" + p);
}

void ChooseYes(int p = 0){
	//xsSetContextPlayer(0);
	//xsDisableSelf();
	if(trCurrentPlayer() == p){
		trackInsert();
		trackAddWaypoint();
		trackPlay(10, EVENT_REMOVE_CAM_TRACKS);
		trUnitSelectClear();
		trBlockAllSounds();
		uiFindType(""+YesChoiceUnitName);
		uiTransformSelectedUnit(""+YesChoiceUnitName + " Hero");
		trUnblockAllSounds();
	}
}

void ChooseNo(int p = 0){
	//xsSetContextPlayer(0);
	p = p-12;
	//xsDisableSelf();
	if(trCurrentPlayer() == p){
		trackInsert();
		trackAddWaypoint();
		trackPlay(10,EVENT_REMOVE_CAM_TRACKS);
		trUnitSelectClear();
		trBlockAllSounds();
		uiFindType(""+NoChoiceUnitName);
		uiTransformSelectedUnit(""+NoChoiceUnitName + " Hero");
		trUnblockAllSounds();
	}
}

rule DetectAnswers
highFrequency
active
{
	//Process saving, one player each trigger loop detected
	PlayerCycle = PlayerCycle+1;
	if(PlayerCycle > cNumberNonGaiaPlayers){
		PlayerCycle = 1;
	}
	int p = PlayerCycle;
	//xsSetContextPlayer(-1);
	if(trPlayerUnitCountSpecific(p, ""+YesChoiceUnitName + " Hero") != 0){
		//trChatSend(0, "Yes registered");
		ChoiceEffect = 1*trQuestVarGet("P"+p+"YesAction");
		ActionChoice = p;
		xsEnableRule("AnswerConsequences");
		trUnitSelectByQV("P"+p+"No");
		trUnitChangeProtoUnit("Cinematic Block");
		trUnitSelectByQV("P"+p+"Yes");
		trUnitChangeProtoUnit("Cinematic Block");
	}
	if(trPlayerUnitCountSpecific(p, ""+NoChoiceUnitName + " Hero") != 0){
		//trChatSend(0, "No registered");
		ChoiceEffect = 1*trQuestVarGet("P"+p+"NoAction");
		ActionChoice = p;
		xsEnableRule("AnswerConsequences");
		trUnitSelectByQV("P"+p+"No");
		trUnitChangeProtoUnit("Cinematic Block");
		trUnitSelectByQV("P"+p+"Yes");
		trUnitChangeProtoUnit("Cinematic Block");
	}
}

rule SetupChoiceUnits
highFrequency
inactive
{
	xsDisableSelf();
	int temp = 0;
	for(p=1 ; < cNumberNonGaiaPlayers){
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(p, "Cinematic Block", p*3, 1, 0);
		trQuestVarSet("P"+p+"Yes", temp);
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(p, "Cinematic Block", p*3, 3, 0);
		trQuestVarSet("P"+p+"No", temp);
	}
	DontDestroyBelow = trGetNextUnitScenarioNameNumber();
	//trChatSend(0, "choice units set");
}

//[Zeno will be angry about this but couldn't get it in a function with the delay :(]
rule ChoiceTimeout1
highFrequency
inactive
{
	int p =1;
	if(trTimeMS() > 1*trQuestVarGet("P"+p+"ChoiceTimer")){
		if(1*trQuestVarGet("P"+p+"ChoiceDialog") == 1){
			if(trCurrentPlayer() == p){
				gadgetUnreal("ShowChoiceBox");
			}
			trQuestVarSet("P"+p+"ChoiceDialog", 0);
			trUnitSelectByQV("P"+p+"No");
			trUnitChangeProtoUnit("Cinematic Block");
			trUnitSelectByQV("P"+p+"Yes");
			trUnitChangeProtoUnit("Cinematic Block");
		}
		xsDisableSelf();
	}
}

rule ChoiceTimeout2
highFrequency
inactive
{
	int p =2;
	if(trTimeMS() > 1*trQuestVarGet("P"+p+"ChoiceTimer")){
		if(1*trQuestVarGet("P"+p+"ChoiceDialog") == 1){
			if(trCurrentPlayer() == p){
				gadgetUnreal("ShowChoiceBox");
			}
			trQuestVarSet("P"+p+"ChoiceDialog", 0);
			trUnitSelectByQV("P"+p+"No");
			trUnitChangeProtoUnit("Cinematic Block");
			trUnitSelectByQV("P"+p+"Yes");
			trUnitChangeProtoUnit("Cinematic Block");
		}
		xsDisableSelf();
	}
}

rule ChoiceTimeout3
highFrequency
inactive
{
	int p =3;
	if(trTimeMS() > 1*trQuestVarGet("P"+p+"ChoiceTimer")){
		if(1*trQuestVarGet("P"+p+"ChoiceDialog") == 1){
			if(trCurrentPlayer() == p){
				gadgetUnreal("ShowChoiceBox");
			}
			trQuestVarSet("P"+p+"ChoiceDialog", 0);
			trUnitSelectByQV("P"+p+"No");
			trUnitChangeProtoUnit("Cinematic Block");
			trUnitSelectByQV("P"+p+"Yes");
			trUnitChangeProtoUnit("Cinematic Block");
		}
		xsDisableSelf();
	}
}

rule ChoiceTimeout4
highFrequency
inactive
{
	int p =4;
	if(trTimeMS() > 1*trQuestVarGet("P"+p+"ChoiceTimer")){
		if(1*trQuestVarGet("P"+p+"ChoiceDialog") == 1){
			if(trCurrentPlayer() == p){
				gadgetUnreal("ShowChoiceBox");
			}
			trQuestVarSet("P"+p+"ChoiceDialog", 0);
			trUnitSelectByQV("P"+p+"No");
			trUnitChangeProtoUnit("Cinematic Block");
			trUnitSelectByQV("P"+p+"Yes");
			trUnitChangeProtoUnit("Cinematic Block");
		}
		xsDisableSelf();
	}
}

rule ChoiceTimeout5
highFrequency
inactive
{
	int p =5;
	if(trTimeMS() > 1*trQuestVarGet("P"+p+"ChoiceTimer")){
		if(1*trQuestVarGet("P"+p+"ChoiceDialog") == 1){
			if(trCurrentPlayer() == p){
				gadgetUnreal("ShowChoiceBox");
			}
			trQuestVarSet("P"+p+"ChoiceDialog", 0);
			trUnitSelectByQV("P"+p+"No");
			trUnitChangeProtoUnit("Cinematic Block");
			trUnitSelectByQV("P"+p+"Yes");
			trUnitChangeProtoUnit("Cinematic Block");
		}
		xsDisableSelf();
	}
}

rule ChoiceTimeout6
highFrequency
inactive
{
	int p =6;
	if(trTimeMS() > 1*trQuestVarGet("P"+p+"ChoiceTimer")){
		if(1*trQuestVarGet("P"+p+"ChoiceDialog") == 1){
			if(trCurrentPlayer() == p){
				gadgetUnreal("ShowChoiceBox");
			}
			trQuestVarSet("P"+p+"ChoiceDialog", 0);
			trUnitSelectByQV("P"+p+"No");
			trUnitChangeProtoUnit("Cinematic Block");
			trUnitSelectByQV("P"+p+"Yes");
			trUnitChangeProtoUnit("Cinematic Block");
		}
		xsDisableSelf();
	}
}

rule ChoiceTimeout7
highFrequency
inactive
{
	int p =7;
	if(trTimeMS() > 1*trQuestVarGet("P"+p+"ChoiceTimer")){
		if(1*trQuestVarGet("P"+p+"ChoiceDialog") == 1){
			if(trCurrentPlayer() == p){
				gadgetUnreal("ShowChoiceBox");
			}
			trQuestVarSet("P"+p+"ChoiceDialog", 0);
			trUnitSelectByQV("P"+p+"No");
			trUnitChangeProtoUnit("Cinematic Block");
			trUnitSelectByQV("P"+p+"Yes");
			trUnitChangeProtoUnit("Cinematic Block");
		}
		xsDisableSelf();
	}
}

rule ChoiceTimeout8
highFrequency
inactive
{
	int p =8;
	if(trTimeMS() > 1*trQuestVarGet("P"+p+"ChoiceTimer")){
		if(1*trQuestVarGet("P"+p+"ChoiceDialog") == 1){
			if(trCurrentPlayer() == p){
				gadgetUnreal("ShowChoiceBox");
			}
			trQuestVarSet("P"+p+"ChoiceDialog", 0);
			trUnitSelectByQV("P"+p+"No");
			trUnitChangeProtoUnit("Cinematic Block");
			trUnitSelectByQV("P"+p+"Yes");
			trUnitChangeProtoUnit("Cinematic Block");
		}
		xsDisableSelf();
	}
}

rule ChoiceTimeout9
highFrequency
inactive
{
	int p =9;
	if(trTimeMS() > 1*trQuestVarGet("P"+p+"ChoiceTimer")){
		if(1*trQuestVarGet("P"+p+"ChoiceDialog") == 1){
			if(trCurrentPlayer() == p){
				gadgetUnreal("ShowChoiceBox");
			}
			trQuestVarSet("P"+p+"ChoiceDialog", 0);
			trUnitSelectByQV("P"+p+"No");
			trUnitChangeProtoUnit("Cinematic Block");
			trUnitSelectByQV("P"+p+"Yes");
			trUnitChangeProtoUnit("Cinematic Block");
		}
		xsDisableSelf();
	}
}

rule ChoiceTimeout10
highFrequency
inactive
{
	int p =10;
	if(trTimeMS() > 1*trQuestVarGet("P"+p+"ChoiceTimer")){
		if(1*trQuestVarGet("P"+p+"ChoiceDialog") == 1){
			if(trCurrentPlayer() == p){
				gadgetUnreal("ShowChoiceBox");
			}
			trQuestVarSet("P"+p+"ChoiceDialog", 0);
			trUnitSelectByQV("P"+p+"No");
			trUnitChangeProtoUnit("Cinematic Block");
			trUnitSelectByQV("P"+p+"Yes");
			trUnitChangeProtoUnit("Cinematic Block");
		}
		xsDisableSelf();
	}
}

rule ChoiceTimeout11
highFrequency
inactive
{
	int p =11;
	if(trTimeMS() > 1*trQuestVarGet("P"+p+"ChoiceTimer")){
		if(1*trQuestVarGet("P"+p+"ChoiceDialog") == 1){
			if(trCurrentPlayer() == p){
				gadgetUnreal("ShowChoiceBox");
			}
			trQuestVarSet("P"+p+"ChoiceDialog", 0);
			trUnitSelectByQV("P"+p+"No");
			trUnitChangeProtoUnit("Cinematic Block");
			trUnitSelectByQV("P"+p+"Yes");
			trUnitChangeProtoUnit("Cinematic Block");
		}
		xsDisableSelf();
	}
}

rule ChoiceTimeout12
highFrequency
inactive
{
	int p =12;
	if(trTimeMS() > 1*trQuestVarGet("P"+p+"ChoiceTimer")){
		if(1*trQuestVarGet("P"+p+"ChoiceDialog") == 1){
			if(trCurrentPlayer() == p){
				gadgetUnreal("ShowChoiceBox");
			}
			trQuestVarSet("P"+p+"ChoiceDialog", 0);
			trUnitSelectByQV("P"+p+"No");
			trUnitChangeProtoUnit("Cinematic Block");
			trUnitSelectByQV("P"+p+"Yes");
			trUnitChangeProtoUnit("Cinematic Block");
		}
		xsDisableSelf();
	}
}
