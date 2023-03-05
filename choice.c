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
		string stringtemp = "";
		int p = ActionChoice;
		int temp = 0;
		vector dir = vector(0,0,0);
		int closest = 100000;
		xSetPointer(dPlayerData, p);
		switch(ChoiceEffect)
		{
			case 0:
			{
				debugLog("NO CONSEQUENCE SET");
			}
			case 1:
			{
				trTechGodPower(p, "Vision", 1);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 2:
			{
				trTechGodPower(p, "Restoration", 1);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
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
				trChatSendToPlayer(0, p, "Debug TP you should be player " + xGetPointer(dPlayerData));
				if(Stage == 1){
					trQuestVarSet("P"+p+"IG", trGetNextUnitScenarioNameNumber());
					UnitCreate(p, "Roc", 2*xsVectorGetX(StageVector)+7,2*xsVectorGetZ(StageVector)+10, 0);
					trUnitSelectByQV("P"+p+"Unit");
					trImmediateUnitGarrison(""+1*trQuestVarGet("P"+p+"IG"));
					trUnitSelectByQV("P"+p+"IG");
					trUnitChangeProtoUnit("Cinematic Block");
					if(trCurrentPlayer() == p){
						uiZoomToProto(""+GazelleProto);
						uiLookAtProto(""+GazelleProto);
					}
				}
				if(Stage == 2){
					trQuestVarSet("P"+p+"IG", trGetNextUnitScenarioNameNumber());
					UnitCreate(p, "Roc", 2*xsVectorGetX(StageVector)+2,2*xsVectorGetZ(StageVector)+2, 0);
					trUnitSelectByQV("P"+p+"Unit");
					trImmediateUnitGarrison(""+1*trQuestVarGet("P"+p+"IG"));
					trUnitSelectByQV("P"+p+"IG");
					trUnitChangeProtoUnit("Cinematic Block");
					if(trCurrentPlayer() == p){
						uiZoomToProto(""+RhinoProto);
						uiLookAtProto(""+RhinoProto);
					}
				}
				if(Stage == 3){
					trQuestVarSet("P"+p+"IG", trGetNextUnitScenarioNameNumber());
					UnitCreate(p, "Roc", 2*xsVectorGetX(StageVector)+2,2*xsVectorGetZ(StageVector)+2, 0);
					trUnitSelectByQV("P"+p+"Unit");
					trImmediateUnitGarrison(""+1*trQuestVarGet("P"+p+"IG"));
					trUnitSelectByQV("P"+p+"IG");
					trUnitChangeProtoUnit("Cinematic Block");
					if(trCurrentPlayer() == p){
						uiZoomToProto(""+GoatProto);
						uiLookAtProto(""+GoatProto);
					}
				}
				if(Stage == 4){
					trQuestVarSet("P"+p+"IG", trGetNextUnitScenarioNameNumber());
					UnitCreate(p, "Roc", 2*xsVectorGetX(StageVector)+2,2*xsVectorGetZ(StageVector)+2, 0);
					trUnitSelectByQV("P"+p+"Unit");
					trImmediateUnitGarrison(""+1*trQuestVarGet("P"+p+"IG"));
					trUnitSelectByQV("P"+p+"IG");
					trUnitChangeProtoUnit("Cinematic Block");
					if(trCurrentPlayer() == p){
						uiZoomToProto(""+CrocProto);
						uiLookAtProto(""+CrocProto);
					}
				}
			}
			case 5:
			{
				//Deer HP
				trModifyProtounit(""+GazelleProto, p, 0, 1);
				trModifyProtounit("Hero Greek Bellerophon", p, 0, 1);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 6:
			{
				//Deer LOS
				trModifyProtounit(""+GazelleProto, p, 2, 4);
				trModifyProtounit("Hero Greek Bellerophon", p, 2, 4);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 7:
			{
				//Deer speed
				trModifyProtounit(""+GazelleProto, p, 1, 0.5);
				trModifyProtounit("Hero Greek Bellerophon", p, 1, 0.5);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 8:
			{
				//Deer minigame reward speed
				trModifyProtounit(""+GazelleProto, p, 1, 1);
				trModifyProtounit("Hero Greek Bellerophon", p, 1, 1);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 9:
			{
				//Deer minigame reward LOS
				trModifyProtounit(""+GazelleProto, p, 2, 6);
				trModifyProtounit("Hero Greek Bellerophon", p, 2, 6);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 10:
			{
				//Deer minigame reward hp
				trModifyProtounit(""+GazelleProto, p, 0, 2);
				trModifyProtounit("Hero Greek Bellerophon", p, 0, 2);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 11:
			{
				//Deer minigame reward regen
				xSetInt(dPlayerData, xHPRegenTime, 30);
				xSetInt(dPlayerData, xHPRegen, xGetInt(dPlayerData, xHPRegen)+1);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 12:
			{
				//Rhino HP
				trModifyProtounit(""+RhinoProto, p, 0, 2);
				trModifyProtounit(""+RhinoDrinkProto, p, 0, 2);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 13:
			{
				//Rhino base Speed
				xSetFloat(dPlayerData, xRhinoWalk, (xGetFloat(dPlayerData, xRhinoWalk)+0.5));
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 14:
			{
				//Rhino charge Speed
				xSetFloat(dPlayerData, xRhinoRun, (xGetFloat(dPlayerData, xRhinoRun)+1.5));
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 15:
			{
				//Rhino charge time
				xSetInt(dPlayerData, xRhinoChargeTimeMax, (xGetInt(dPlayerData, xRhinoChargeTimeMax)+2));
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 16:
			{
				//Rhino drink time
				xSetFloat(dPlayerData, xRhinoDrinkTime, (xGetFloat(dPlayerData, xRhinoDrinkTime)-1));
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 17:
			{
				//Rhino minigame reward regen
				xSetInt(dPlayerData, xHPRegenTime, 20);
				xSetInt(dPlayerData, xHPRegen, xGetInt(dPlayerData, xHPRegen)+1);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 18:
			{
				//Rhino minigame charge Speed
				xSetFloat(dPlayerData, xRhinoRun, (xGetFloat(dPlayerData, xRhinoRun)*1.2));
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 19:
			{
				//Rhino HP
				trModifyProtounit(""+RhinoProto, p, 0, 5);
				trModifyProtounit(""+RhinoDrinkProto, p, 0, 5);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 20:
			{
				//Rhino MG charge time
				xSetInt(dPlayerData, xRhinoChargeTimeMax, (xGetInt(dPlayerData, xRhinoChargeTimeMax)+5));
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 21:
			{
				//Goat +2 HP
				trModifyProtounit(""+GoatProto, p, 0, 2);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 22:
			{
				//Goat +0.5 speed
				trModifyProtounit(""+GoatProto, p, 1, 0.5);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 23:
			{
				//Goat +4 LOS
				trModifyProtounit(""+GoatProto, p, 2, 4);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 24:
			{
				//Goat regen +1/30
				xSetInt(dPlayerData, xHPRegenTime, 30);
				xSetInt(dPlayerData, xHPRegen, xGetInt(dPlayerData, xHPRegen)+1);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 25:
			{
				//Goat +3 HP
				trModifyProtounit(""+GoatProto, p, 0, 3);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 26:
			{
				//Goat +0.75 speed
				trModifyProtounit(""+GoatProto, p, 1, 0.75);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 27:
			{
				//Goat remove snowman
				if(xGetDatabaseCount(dPoachers) > 0){
					xDatabaseNext(dPoachers);
					xUnitSelect(dPoachers, xUnitID);
					trUnitChangeProtoUnit("Timeshift In");
					xUnitSelect(dPoachers, xUnitID);
					trUnitSetAnimationPath("0,1,1,0,0,0");
				}
				xFreeDatabaseBlock(dPoachers);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 28:
			{
				//Goat +10s shrine min
				ShrineTimeMin = ShrineTimeMin+10;
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 29:
			{
				//Goat +20s shrine max
				ShrineTimeMax = ShrineTimeMax+20;
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 30:
			{
				//Goat +60s all shrines
				for(x = xGetDatabaseCount(dInterractables); > 0){
					xDatabaseNext(dInterractables);
					if(xGetInt(dInterractables, xType) == 2){
						if(xGetInt(dInterractables, xSubtype) == 1){
							xSetInt(dInterractables, xSquare1, xGetInt(dInterractables, xSquare1)+60);
						}
					}
				}
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 31:
			{
				//Goat +6 HP
				trModifyProtounit(""+GoatProto, p, 0, 6);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 32:
			{
				//Goat +1.5 speed
				trModifyProtounit(""+GoatProto, p, 1, 1.5);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 33:
			{
				//Goat target
				stringtemp = " has discovered the number of active shrines required to progress is ";
				trMessageSetText(trStringQuestVarGet("p"+p+"name") + stringtemp + ShrineTarget + ".", 10000);
				playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
			}
			case 34:
			{
				//Goat target
				stringtemp = " has discovered this act has a total of ";
				trMessageSetText(trStringQuestVarGet("p"+p+"name") + stringtemp + ShrinesMax + " shrines.", 10000);
				playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
			}
			case 35:
			{
				//Croc grow
				CrocGrow(p);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 36:
			{
				//Croc +5 HP
				trModifyProtounit(""+CrocProto, p, 0, 5);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 37:
			{
				//Croc +4 LOS
				trModifyProtounit(""+CrocProto, p, 2, 4);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 38:
			{
				//Croc +0.4 land speed
				xSetFloat(dPlayerData, xCrocLandSpeed, xGetFloat(dPlayerData, xCrocLandSpeed)+0.4);
				modifyProtounitAbsolute(""+CrocProto, p, 1, xGetFloat(dPlayerData, xCrocLandSpeed));
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 39:
			{
				//Croc +0.6 swim speed
				xSetFloat(dPlayerData, xCrocWaterSpeed, xGetFloat(dPlayerData, xCrocWaterSpeed)+0.6);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 40:
			{
				//Croc +1s sprint time
				xSetInt(dPlayerData, xCrocSprintDuration, xGetInt(dPlayerData, xCrocSprintDuration)+1000);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 41:
			{
				//Croc -2s sprint cd
				xSetInt(dPlayerData, xCrocSprintRechargeTime, xGetInt(dPlayerData, xCrocSprintRechargeTime)-2);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 42:
			{
				//Croc 0.3 sprint speed multiplier
				xSetFloat(dPlayerData, xCrocSprintSpeed, xGetFloat(dPlayerData, xCrocSprintSpeed)+0.3);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 43:
			{
				//Croc regen +1/20
				xSetInt(dPlayerData, xHPRegenTime, 20);
				xSetInt(dPlayerData, xHPRegen, xGetInt(dPlayerData, xHPRegen)+1);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 44:
			{
				//MG true
				xSetPointer(dPlayerData, p);
				xSetInt(dPlayerData, xAnswer, 1);
			}
			case 45:
			{
				//MG false
				xSetPointer(dPlayerData, p);
				xSetInt(dPlayerData, xAnswer, 0);
			}
			case 46:
			{
				//Croc regen +2/20
				xSetInt(dPlayerData, xHPRegenTime, 20);
				xSetInt(dPlayerData, xHPRegen, xGetInt(dPlayerData, xHPRegen)+2);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 47:
			{
				//Croc +2s sprint time
				xSetInt(dPlayerData, xCrocSprintDuration, xGetInt(dPlayerData, xCrocSprintDuration)+2000);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 48:
			{
				//Croc -4s sprint cd
				xSetInt(dPlayerData, xCrocSprintRechargeTime, xGetInt(dPlayerData, xCrocSprintRechargeTime)-4);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 49:
			{
				//flare nearest zebra
				temp = 0;
				for(a=xGetDatabaseCount(dEdibles) ; > 0){
					xDatabaseNext(dEdibles);
					if(xGetInt(dEdibles, xType) == 1){
						dir = kbGetBlockPosition(""+xGetInt(dEdibles, xUnitID));
						if(distanceBetweenVectors(dir, kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")), true) < closest){
							closest = distanceBetweenVectors(dir, kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")), true);
							temp = xGetInt(dEdibles, xUnitID);
						}
					}
				}
				dir = kbGetBlockPosition(""+temp);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
					trMinimapFlare(p,10,dir,true);
				}
			}
			case 50:
			{
				//spawn 2 zebra
				SpawnEdible(2);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 51:
			{
				//spawn zebra
				temp = trGetNextUnitScenarioNameNumber();
				UnitCreateV(0, "Zebra", kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
				xAddDatabaseBlock(dEdibles, true);
				xSetInt(dEdibles, xUnitID, temp);
				xSetInt(dEdibles, xType, 1);
				xSetInt(dEdibles, xSubtype, 0);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 52:
			{
				//4 food
				xSetFloat(dPlayerData, xCrocFood, xGetFloat(dPlayerData, xCrocFood)+4);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 53:
			{
				//flare nearest shrine
				temp = 0;
				for(a=xGetDatabaseCount(dInterractables) ; > 0){
					xDatabaseNext(dInterractables);
					if(xGetInt(dInterractables, xType) == 2){
						if(xGetInt(dInterractables, xSubtype) == 0){
							dir = kbGetBlockPosition(""+xGetInt(dInterractables, xUnitID));
							if(distanceBetweenVectors(dir, kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")), true) < closest){
								closest = distanceBetweenVectors(dir, kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")), true);
								temp = xGetInt(dInterractables, xUnitID);
							}
						}
					}
				}
				dir = kbGetBlockPosition(""+temp);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
					trMinimapFlare(p,10,dir,true);
				}
			}
			case 54:
			{
				//flare nearest relic
				temp = 0;
				for(a=xGetDatabaseCount(dRelics) ; > 0){
					xDatabaseNext(dRelics);
					dir = kbGetBlockPosition(""+xGetInt(dRelics, xUnitID));
					if(distanceBetweenVectors(dir, kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")), true) < closest){
						closest = distanceBetweenVectors(dir, kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")), true);
						temp = xGetInt(dRelics, xUnitID);
					}
				}
				dir = kbGetBlockPosition(""+temp);
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
					trMinimapFlare(p,10,dir,true);
				}
			}
			case 55:
			{
				//Goat +10s shrine max
				ShrineTimeMax = ShrineTimeMax+10;
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
				}
			}
			case 56:
			{
				//Goat +15s all shrines
				for(x = xGetDatabaseCount(dInterractables); > 0){
					xDatabaseNext(dInterractables);
					if(xGetInt(dInterractables, xType) == 2){
						if(xGetInt(dInterractables, xSubtype) == 1){
							xSetInt(dInterractables, xSquare1, xGetInt(dInterractables, xSquare1)+15);
						}
					}
				}
				if(trCurrentPlayer() == p){
					playSoundCustom("researchcomplete.wav", "\Yeebaagooon\Zoo Quest\SelectBonus.mp3");
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
			if(Stage == 1){
				uiZoomToProto(""+GazelleProto);
			}
			if(Stage == 2){
				uiZoomToProto(""+RhinoProto);
			}
			if(Stage == 3){
				uiZoomToProto(""+GoatProto);
			}
			if(Stage == 4){
				uiZoomToProto(xGetString(dPlayerData, xCrocProto));
			}
		}
		
		xsDisableSelf();
	}
}

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
