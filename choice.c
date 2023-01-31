int PlayerCycle = 1;
int ActionChoice = 0;
int ChoiceEffect = 0;
string YesChoiceUnitName = "Swordsman";
string NoChoiceUnitName = "Lancer";

rule AnswerConsequences
highFrequency
inactive
{
	xsSetContextPlayer(0);
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
		}
		trQuestVarSet("P"+ActionChoice+"YesAction", 0);
		trQuestVarSet("P"+ActionChoice+"NoAction", 0);
		ActionChoice = 0;
		//[Safety]
		unitTransform(""+YesChoiceUnitName + " Hero", "Cinematic Block");
		unitTransform(""+NoChoiceUnitName + " Hero", "Cinematic Block");
		xsDisableSelf();
	}
}

//PlayerChoice(1, "Choose a god power again", "Vision", 1, "Serpents", 2);
//xsGetContextPlayer for problems

void PlayerChoice(int p = 0, string prompt = "Question", string answerone = "Answer 1", int effectone = 0, string answertwo = "Answer 2", int effecttwo = 0){
	xsDisableSelf();
	int temp = 0;
	//Check choice units alive
	xsSetContextPlayer(-1);
	if(kbUnitGetProtoUnitID(1*trQuestVarGet("P"+p+"Yes")) == -1){
		temp = trGetNextUnitScenarioNameNumber();
		UnitCreate(p, "Cinematic Block", p*3, 1, 0);
		trQuestVarSet("P"+p+"Yes", temp);
		debugLog("Choice selector dead");
	}
	if(kbUnitGetProtoUnitID(1*trQuestVarGet("P"+p+"No")) == -1){
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
}

void ChooseYes(int p = 0){
	//xsSetContextPlayer(0);
	xsDisableSelf();
	if(trCurrentPlayer() == p){
		trackInsert();
		trackAddWaypoint();
		trackPlay(10, EVENT_REMOVE_CAM_TRACKS);
		trUnitSelectClear();
		uiFindType(""+YesChoiceUnitName);
		uiTransformSelectedUnit(""+YesChoiceUnitName + " Hero");
	}
}

void ChooseNo(int p = 0){
	//xsSetContextPlayer(0);
	p = p-12;
	xsDisableSelf();
	if(trCurrentPlayer() == p){
		trackInsert();
		trackAddWaypoint();
		trackPlay(10,EVENT_REMOVE_CAM_TRACKS);
		trUnitSelectClear();
		uiFindType(""+NoChoiceUnitName);
		uiTransformSelectedUnit(""+NoChoiceUnitName + " Hero");
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
	trChatSend(0, "choice units set");
}

//[TIMEOUT]
//gadgetUnreal("ShowChoiceBox");
//trIsGadgetVisible("ShowChoiceBox")
