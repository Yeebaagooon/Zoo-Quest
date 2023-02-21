rule BuildGoatArea
highFrequency
inactive
{
	if (trTime() > cActivationTime + 1) {
		TutorialMode = false;
		createGoatArea();
		xsDisableSelf();
		//replaceTerrainAboveHeightMax("ForestFloorPine", "GrassB", 0.0);
		trLetterBox(false);
		trUIFadeToColor(0,0,0,100,800,false);
		uiZoomToProto(""+GoatProto);
		uiLookAtProto(""+GoatProto);
		trDelayedRuleActivation("ResetBlackmap");
		trDelayedRuleActivation("GoatMinigameDetect");
		trDelayedRuleActivation("TEST");
		trDelayedRuleActivation("GoatEndZoneSee");
		trDelayedRuleActivation("GoatAllDead");
		//trDelayedRuleActivation("PoacherTimer");
		xsEnableRule("GoatPoacherMovement");
		//trSetCounterDisplay("<color={PlayerColor(2)}>Fencing destroyed: "+FencesDone+"/8");
		ColouredIconChat("1,0.5,0", ActIcon(Stage), "<u>" + ActName(Stage) + "</u>");
		ColouredIconChat("0.0,0.8,0.2", "icons\icon building wooden fence 64", "Destroy enough fences.");
		ColouredChat("0.0,0.8,0.2", "Each long fence segment needs at least one break.");
		xsEnableRule("PlayMusic");
		//SpawnRhinoPoacher(xsMax(PlayersActive,3));
		//SpawnRhinoSuperPoacher(1);
		PlayersDead = 0;
		timediff = trTimeMS();
		timelast = trTimeMS();
		trDelayedRuleActivation("GoatActLoops");
		SpawnGoatPoacher(2);
		modifyProtounitAbsolute("Throwing Axeman", cNumberNonGaiaPlayers, 55, 4);
		for(p = 1 ; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			xSetInt(dPlayerData, xTimeout, trTimeMS()*2);
		}
	}
}

rule GoatEndZoneSee
inactive
highFrequency
{
	for(p=1 ; < cNumberNonGaiaPlayers){
		trUnitSelectByQV("P"+p+"Unit");
		if(trUnitDistanceToUnit(""+FlagUnitID) < 26){
			vector flagV = kbGetBlockPosition(""+FlagUnitID);
			for(x=1 ; < cNumberNonGaiaPlayers){
				trMinimapFlare(x,10,flagV,true);
			}
			UnitCreate(0, "Revealer", xsVectorGetX(flagV),xsVectorGetZ(flagV),0);
			trMessageSetText("The extraction zone has been found. Gather here when you are ready to end the act.", 8000);
			playSound("examinationbirth.wav");
			trUnitSelectClear();
			trUnitSelect(""+FlagUnitID);
			trUnitHighlight(10, true);
			trDelayedRuleActivation("GoatLeave");
			xsDisableSelf();
		}
	}
}

rule GoatActLoops
highFrequency
inactive
{
	if(Stage == 3){
		timediff = 0.001 * (trTimeMS() - timelast); // calculate timediff
		timelast = trTimeMS();
		tempV = vector(0,0,0);
		int temp = 0;
		if(xGetDatabaseCount(dMissiles) > 0){
			DoMissile();
		}
		if(InMinigame == true){
			if(trTime() > 1*trQuestVarGet("MGTime")){
				trQuestVarModify("MGTime", "+", 5);
				//refreshPassability();
				//sq6?
			}
		}
		for(p = 1; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(InMinigame == true){
				if(xGetBool(dPlayerData, xStopDeath) == true){
					if(trPlayerUnitCountSpecific(p, ""+GoatProto) == 1){
						tempV = kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit"));
						if((trGetTerrainType(1*xsVectorGetX(tempV)/2,1*xsVectorGetZ(tempV)/2) == 5) && (trGetTerrainSubType(1*xsVectorGetX(tempV)/2,1*xsVectorGetZ(tempV)/2) == 7)){
							trUnitSelectByQV("P"+p+"Unit");
							trUnitChangeProtoUnit("Ragnorok SFX");
							trUnitSelectByQV("P"+p+"Unit");
							trUnitDestroy();
							trUnitSelectClear();
							trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
							trUnitChangeProtoUnit("Hero Death");
							UnitCreate(0, "Tartarian Gate Flame", trVectorQuestVarGetX("P"+p+"PosMG"),trVectorQuestVarGetZ("P"+p+"PosMG"), 90);
							PlayersMinigaming = PlayersMinigaming-1;
							trChatSend(0, "Players MG" + PlayersMinigaming);
							if(trCurrentPlayer() == p){
								playSound("xlose.wav");
								trOverlayText("Minigame Failed!", 3.0,-1,-1,600);
							}
							break;
						}
					}
				}
				if(SquaresDown > 5){
					if(xGetBool(dPlayerData, xStopDeath) == true){
						MinigameWins = MinigameWins+1;
						if(trCurrentPlayer() == p){
							playSound("xwin.wav");
							playSound("\cinematics\15_in\gong.wav");
							trMessageSetText("You have won the minigame!", 4000);
						}
						trQuestVarSetFromRand("temp",1,2,true);
						if(1*trQuestVarGet("temp") == 1){
							PlayerChoice(p, "Choose your reward:", "+5 hp", 19, "+5 max stamina", 20, 10000);
						}
						else{
							PlayerChoice(p, "Choose your reward:", "+20 percent charge speed", 18, "+1hp regen every 20s", 17, 10000);
						}
						PlayersMinigaming = PlayersMinigaming-1;
						trChatSend(0, "Players MG" + PlayersMinigaming);
						xSetBool(dPlayerData, xStopDeath, false);
					}
				}
			}
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
			if((xGetBool(dPlayerData, xStopDeath) == false) && (trPlayerUnitCountSpecific(p, ""+GoatProto) == 0) && (trPlayerUnitCountSpecific(p, "Prisoner") == 0) && (trPlayerUnitCountSpecific(p, "Anubite") == 0) && (xGetBool(dPlayerData, xPlayerActive) == true) && (xGetBool(dPlayerData, xPlayerDead) == false) && (InMinigame == false)){
				//PLAYER DEAD
				PlayersDead = PlayersDead+1;
				xSetBool(dPlayerData, xPlayerDead, true);
				PlayerColouredChat(p, trStringQuestVarGet("p"+p+"name") + " is dead!");
			}
		}
		if((PlayersActive == PlayersReadyToLeave+PlayersDead) && (PlayersDead != PlayersActive)){
			xsEnableRule("GoatExit");
		}
		
	}
	
}

rule GoatPoacherMovement
inactive
highFrequency
{
	int superpoacher = 0;
	int target = 0;
	int temp = 0;
	vector dest = vector(0,0,0);
	if(xGetDatabaseCount(dPoachers) > 0){
		xDatabaseNext(dPoachers);
		if(xGetInt(dPoachers, xMoveTime) < trTime()){
			trQuestVarSetFromRand("x",0,252);
			trQuestVarSetFromRand("y",30,80);
			trQuestVarSetFromRand("z",0,252);
			xSetInt(dPoachers, xMoveTime, trTime()+1*trQuestVarGet("y"));
			xUnitSelect(dPoachers, xUnitID);
			trUnitMoveToPoint(1*trQuestVarGet("x"),5,1*trQuestVarGet("z"),-1,true);
		}
	}
}


rule GoatMinigameDetect
highFrequency
inactive
{
	//xsSetContextPlayer(0);
	vector pos = vector(0,0,0);
	vector minigame = kbGetBlockPosition(""+1*trQuestVarGet("MinigameStartID"));
	for(p=1 ; < cNumberNonGaiaPlayers){
		pos = kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit"));
		if(distanceBetweenVectors(minigame, pos, true) < 10){
			trUnitSelectByQV("MinigameStartSFX");
			trUnitChangeProtoUnit("Olympus Temple SFX");
			trUnitSelectByQV("MinigameStartID");
			trUnitChangeProtoUnit("Forest Fire SFX");
			PaintAtlantisArea(xsVectorGetX(StageVector)-2,xsVectorGetZ(StageVector)-2,xsVectorGetX(StageVector)+2,xsVectorGetZ(StageVector)+2,0,53);
			trChangeTerrainHeight(xsVectorGetX(StageVector)-2,xsVectorGetZ(StageVector)-2,xsVectorGetX(StageVector)+3,xsVectorGetZ(StageVector)+3,10,false);
			refreshPassability();
			trMessageSetText("Minigame found! Remain in the white square if you wish to play.", 10000);
			trCounterAddTime("CDMG", 12-(QuickStart*5), 0, "<color={PlayerColor("+p+")}>Minigame Starts", 36);
			MinigameFound = true;
			for(x=1 ; < cNumberNonGaiaPlayers){
				if(x != p){
					PlayerChoice(x, "Participate in minigame?", "Yes", 4, "No", 0, 11900);
				}
			}
			for(b = 0; <xGetDatabaseCount(dPoachers)){
				xDatabaseNext(dPoachers);
				xUnitSelect(dPoachers, xUnitID);
				trUnitChangeProtoUnit("Cinematic Block");
			}
			trMusicStop();
			playSound("\cinematics\22_in\music 2.mp3");
			xsDisableSelf();
		}
	}
}

void GoatMinigameGo(int temp = 0){
	xsEnableRule("MGGOGoat");
}

void GoatStatueMake(int x = 0, int z = 0){
	int temp = trGetNextUnitScenarioNameNumber();
	UnitCreate(0, "Dwarf", x*2+4, z*2+4, 180);
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trUnitChangeProtoUnit("Spy Eye");
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trMutateSelected(kbGetProtoUnitID("Columns"));
	xAddDatabaseBlock(dInterractables, true);
	xSetInt(dInterractables, xUnitID, temp);
	xSetInt(dInterractables, xType, 1);
	xSetInt(dInterractables, xSubtype, xGetDatabaseCount(dInterractables));
	trQuestVarSetFromRand("temp", 1, xGetDatabaseCount(dTemp), true);
	xSetPointer(dTemp, 1*trQuestVarGet("temp"));
	//trChatSend(0, "<color=1,1,0>Col " + xGetDatabaseCount(dInterractables));
	//trChatSend(0, "<color=0,1,0>Sq1 " + xGetInt(dTemp, xUnitID));
	xSetInt(dInterractables, xSquare1, xGetInt(dTemp, xUnitID));
	trQuestVarSetFromRand("temp", 1, 9, true);
	xSetInt(dInterractables, xSquare2, 1*trQuestVarGet("temp"));
	//trChatSend(0, "<color=0,0.5,0>Sq2 " + 1*trQuestVarGet("temp"));
	trUnitSelectClear();
	xFreeDatabaseBlock(dTemp);
}

rule MGGOGoat
inactive
highFrequency
{
	InMinigame = true;
	int temp = trGetNextUnitScenarioNameNumber();
	int StartX = xsVectorGetX(StageVector);
	int StartZ = xsVectorGetZ(StageVector);
	
	
	//1,2,3
	//4,5,6
	//7,8,9
	
	//SQUARE 1st clicks
	for(p = 1; < 10){
		xAddDatabaseBlock(dTemp, true);
		xSetInt(dTemp, xUnitID, p);
	}
	
	//SQUARE 1
	trPaintTerrain(StartX-10,StartZ+4,StartX-4,StartZ+10,2,3);
	PaintAtlantisArea(StartX-9,StartZ+5,StartX-5,StartZ+9,0,53);
	trChangeTerrainHeight(StartX-9,StartZ+5,StartX-4,StartZ+10,15,false);
	GoatStatueMake(StartX-9,StartZ+5);
	
	//SQUARE 2
	trPaintTerrain(StartX-3,StartZ+4,StartX+3,StartZ+10,2,3);
	PaintAtlantisArea(StartX-2,StartZ+5,StartX+2,StartZ+9,0,53);
	trChangeTerrainHeight(StartX-2,StartZ+5,StartX+3,StartZ+10,15,false);
	GoatStatueMake(StartX-2,StartZ+5);
	
	//SQUARE 3
	trPaintTerrain(StartX+4,StartZ+4,StartX+10,StartZ+10,2,3);
	PaintAtlantisArea(StartX+5,StartZ+5,StartX+9,StartZ+9,0,53);
	trChangeTerrainHeight(StartX+5,StartZ+5,StartX+10,StartZ+10,15,false);
	GoatStatueMake(StartX+5,StartZ+5);
	
	//SQUARE 4
	trPaintTerrain(StartX-10,StartZ-3,StartX-4,StartZ+3,2,3);
	PaintAtlantisArea(StartX-9,StartZ-2,StartX-5,StartZ+2,0,53);
	trChangeTerrainHeight(StartX-9,StartZ-2,StartX-4,StartZ+3,15,false);
	GoatStatueMake(StartX-9,StartZ-2);
	
	//SQUARE 5
	trPaintTerrain(StartX-3,StartZ-3,StartX+3,StartZ+3,2,3);
	PaintAtlantisArea(StartX-2,StartZ-2,StartX+2,StartZ+2,0,53);
	trChangeTerrainHeight(StartX-2,StartZ-2,StartX+3,StartZ+3,15,false);
	GoatStatueMake(StartX-2,StartZ-2);
	
	//SQUARE 6
	trPaintTerrain(StartX+4,StartZ-3,StartX+10,StartZ+3,2,3);
	PaintAtlantisArea(StartX+5,StartZ-2,StartX+9,StartZ+2,0,53);
	trChangeTerrainHeight(StartX+5,StartZ-2,StartX+10,StartZ+3,15,false);
	GoatStatueMake(StartX+5,StartZ-2);
	
	//SQUARE 7
	trPaintTerrain(StartX-10,StartZ-10,StartX-4,StartZ-4,2,3);
	PaintAtlantisArea(StartX-9,StartZ-9,StartX-5,StartZ-5,0,53);
	trChangeTerrainHeight(StartX-9,StartZ-9,StartX-4,StartZ-4,15,false);
	GoatStatueMake(StartX-9,StartZ-9);
	
	//SQUARE 8
	trPaintTerrain(StartX-3,StartZ-10,StartX+3,StartZ-4,2,3);
	PaintAtlantisArea(StartX-2,StartZ-9,StartX+2,StartZ-5,0,53);
	trChangeTerrainHeight(StartX-2,StartZ-9,StartX+3,StartZ-4,15,false);
	GoatStatueMake(StartX-2,StartZ-9);
	
	//SQUARE 9
	trPaintTerrain(StartX+4,StartZ-10,StartX+10,StartZ-4,2,3);
	PaintAtlantisArea(StartX+5,StartZ-9,StartX+9,StartZ-5,0,53);
	trChangeTerrainHeight(StartX+5,StartZ-9,StartX+10,StartZ-4,15,false);
	GoatStatueMake(StartX+5,StartZ-9);
	
	temp = trGetNextUnitScenarioNameNumber();
	
	trUnitSelectByQV("MinigameStartSFX");
	trUnitChangeInArea(0,0,"Pine Snow", "Rocket", 30);
	trUnitChangeInArea(0,0,"Rock River Icy", "Rocket", 30);
	for(p=1 ; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		if(xGetBool(dPlayerData, xPlayerActive)){
			trVectorQuestVarSet("P"+p+"PosMG", kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
			trVectorQuestVarSet("P"+p+"PosMG", trVectorQuestVarGet("P"+p+"PosMG")/2);
			if((trVectorQuestVarGetX("P"+p+"PosMG") > xsVectorGetX(StageVector)-2) && (trVectorQuestVarGetX("P"+p+"PosMG") < xsVectorGetX(StageVector)+2) && (trVectorQuestVarGetZ("P"+p+"PosMG") > xsVectorGetZ(StageVector)-2) && (trVectorQuestVarGetZ("P"+p+"PosMG") < xsVectorGetZ(StageVector)+2)){
				PlayerColouredChat(p, trStringQuestVarGet("p"+p+"name") + " is playing");
				PlayersMinigaming = PlayersMinigaming+1;
				xSetBool(dPlayerData, xStopDeath, true);
				if(xGetInt(dPlayerData, xTeleportDue) == 0){
					xSetVector(dPlayerData, xVectorHold, kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit")));
				}
			}
		}
		//-spawn guys
	}
	refreshPassability();
	if(PlayersMinigaming == 0){
		//end MG
		trUnitSelectByQV("MinigameStartSFX");
		trUnitDestroy();
		trUnitSelectByQV("MinigameStartID");
		trUnitDestroy();
		trMessageSetText("Nobody was on the white tiles. Minigame cancelled.", 5000);
		for(c = xGetDatabaseCount(dTemp) ; > 0){
			xDatabaseNext(dTemp);
			xUnitSelect(dTemp, xUnitID);
			trUnitDestroy();
			xFreeDatabaseBlock(dTemp);
		}
		for(b = 0; <xGetDatabaseCount(dPoachers)){
			xDatabaseNext(dPoachers);
			xUnitSelect(dPoachers, xUnitID);
			trUnitChangeProtoUnit("Throwing Axeman");
		}
		InMinigame = false;
		xsEnableRule("PlayMusic");
		trChangeTerrainHeight(xsVectorGetX(StageVector)-10,xsVectorGetZ(StageVector)-10,xsVectorGetX(StageVector)+10,xsVectorGetZ(StageVector)+10,9,false);
		trPaintTerrain(xsVectorGetX(StageVector)-10,xsVectorGetZ(StageVector)-10,xsVectorGetX(StageVector)+10,xsVectorGetZ(StageVector)+10,0,51);
		refreshPassability();
		for(p=1 ; < cNumberNonGaiaPlayers){
			if(trPlayerUnitCountSpecific(p, ""+GoatProto) == 0){
				CreateGoat(p, xsVectorGetX(StageVector), xsVectorGetZ(StageVector), 0);
				debugLog("Path 3");
				
			}
		}
	}
	else{
		trMessageSetText("Sink 6 tiles into lava while remaining alive yourself!", 8000);
		trCounterAddTime("cdgoatminigame", 120,0,"<color={PlayerColor(0)}>Minigame time remaining", 37);
		playSoundCustom("\xpack\xcinematics\7_in\music.mp3", "\Yeebaagooon\Zoo Quest\Minigame3.mp3");
		trQuestVarSet("MGTime", trTime()+5);
		xsEnableRule("GoatMinigameEnd");
	}
	xsDisableSelf();
}

void GoatMGTimeout(int eventID = 0){
	PlayersMinigaming = 0;
}

/*rule GoatDebug
active
highFrequency
{
	if(trChatHistoryContains("Reset", 1)){
		trChatHistoryClear();
		refreshPassability();
	}
}*/

rule GoatMinigameEnd
inactive
highFrequency
{
	if(PlayersMinigaming <= 0){
		vector temp = vector(0,0,0);
		trChangeTerrainHeight(xsVectorGetX(StageVector)-10,xsVectorGetZ(StageVector)-10,xsVectorGetX(StageVector)+10,xsVectorGetZ(StageVector)+10,9,false);
		trPaintTerrain(xsVectorGetX(StageVector)-10,xsVectorGetZ(StageVector)-10,xsVectorGetX(StageVector)+10,xsVectorGetZ(StageVector)+10,0,51);
		refreshPassability();
		debugLog("Cols left:" + xGetDatabaseCount(dInterractables));
		for(n = xGetDatabaseCount(dInterractables) ; > 0){
			xDatabaseNext(dInterractables);
			if(xGetInt(dInterractables, xType) == 1){
				xUnitSelect(dInterractables, xUnitID);
				trUnitChangeProtoUnit("Hero Birth");
				xFreeDatabaseBlock(dInterractables);
			}
			//debugLog("cols " + xGetDatabaseCount(dInterractables));
		}
		for(p=1 ; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if((xGetInt(dPlayerData, xTeleportDue) == 1) && (xGetBool(dPlayerData, xPlayerActive) == true)){
				temp = xGetVector(dPlayerData, xVectorHold);
				debugLog("Path 1");
				trUnitSelectByQV("P"+p+"Unit");
				trUnitChangeProtoUnit("Ragnorok SFX");
				trUnitSelectByQV("P"+p+"Unit");
				trUnitDestroy();
				trUnitSelectClear();
				trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
				trUnitChangeProtoUnit("Hero Death");
				CreateGoat(p, xsVectorGetX(temp), xsVectorGetZ(temp), 0);
				xSetBool(dPlayerData, xStopDeath, false);
				xSetInt(dPlayerData, xTeleportDue, 0);
			}
			else if((xGetInt(dPlayerData, xTeleportDue) == 0) && (xGetBool(dPlayerData, xPlayerActive) == true)){
				if(trPlayerUnitCountSpecific(p, ""+GoatProto) == 0){
					debugLog("Path 2");
					temp = xGetVector(dPlayerData, xVectorHold);
					trUnitSelectByQV("P"+p+"Unit");
					trUnitChangeProtoUnit("Ragnorok SFX");
					trUnitSelectByQV("P"+p+"Unit");
					trUnitDestroy();
					trUnitSelectClear();
					trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
					trUnitChangeProtoUnit("Hero Death");
					CreateGoat(p, xsVectorGetX(temp), xsVectorGetZ(temp), 0);
				}
			}
			if(trPlayerUnitCountSpecific(p, ""+GoatProto) == 0){
				CreateGoat(p, trVectorQuestVarGetX("P"+p+"PosMG")*2, trVectorQuestVarGetZ("P"+p+"PosMG")*2, 0);
				debugLog("Path 3");
				//fail is /2
			}
		}
		uiZoomToProto(""+GoatProto);
		uiLookAtProto(""+GoatProto);
		unitTransform("Tartarian Gate Flame", "Flowers");
		for(c = xGetDatabaseCount(dTemp) ; > 0){
			xDatabaseNext(dTemp);
			xUnitSelect(dTemp, xUnitID);
			trUnitDestroy();
			xFreeDatabaseBlock(dTemp);
		}
		for(b = 0; <xGetDatabaseCount(dPoachers)){
			xDatabaseNext(dPoachers);
			xUnitSelect(dPoachers, xUnitID);
			trUnitChangeProtoUnit("Throwing Axeman");
		}
		trUnitSelectByQV("MinigameStartSFX");
		trUnitChangeProtoUnit("Olympus Temple SFX");
		trUnitSelectByQV("MinigameStartID");
		trUnitChangeProtoUnit("Forest Fire SFX");
		xsDisableSelf();
		InMinigame = false;
		PlayersMinigaming = 0;
		trCounterAbort("cdgoatminigame");
		trFadeOutAllSounds(3);
		trFadeOutMusic(3);
		xsEnableRule("PlayMusic");
	}
}

rule GoatLeave
inactive
highFrequency
{
	int STOP = 0;
	trQuestVarModify("PlayerCycle", "+", 1);
	if(1*trQuestVarGet("PlayerCycle") > cNumberNonGaiaPlayers){
		trQuestVarSet("PlayerCycle", 1);
	}
	int p = 1*trQuestVarGet("PlayerCycle");
	xSetPointer(dPlayerData, p);
	tempV = kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit"));
	if(xGetBool(dPlayerData, xReadyToLeave) == true){
		if((trGetTerrainType(1*xsVectorGetX(tempV)/2,1*xsVectorGetZ(tempV)/2) != getTerrainType(LeaveTerrain)) || (trGetTerrainSubType(1*xsVectorGetX(tempV)/2,1*xsVectorGetZ(tempV)/2) != getTerrainSubType(LeaveTerrain))){
			xSetBool(dPlayerData, xReadyToLeave, false);
			xSetBool(dPlayerData, xStopDeath, false);
			PlayersReadyToLeave = PlayersReadyToLeave-1;
			trUnitSelectByQV("P"+p+"Unit");
			trMutateSelected(kbGetProtoUnitID(""+GoatProto));
			PlayerColouredChatToSelf(p, "You have left the extraction zone");
			STOP = 1;
		}
	}
	if((xGetBool(dPlayerData, xReadyToLeave) == false) && (STOP == 0)){
		if((trGetTerrainType(1*xsVectorGetX(tempV)/2,1*xsVectorGetZ(tempV)/2) == getTerrainType(LeaveTerrain)) && (trGetTerrainSubType(1*xsVectorGetX(tempV)/2,1*xsVectorGetZ(tempV)/2) == getTerrainSubType(LeaveTerrain))){
			xSetBool(dPlayerData, xReadyToLeave, true);
			xSetBool(dPlayerData, xStopDeath, true);
			PlayersReadyToLeave = PlayersReadyToLeave+1;
			trUnitSelectByQV("P"+p+"Unit");
			trMutateSelected(kbGetProtoUnitID("Prisoner"));
			PlayerColouredChat(p, trStringQuestVarGet("p"+p+"name") + " is ready to leave");
			if(trQuestVarGet("P"+p+"LeaveMsg") == 0){
				trQuestVarSet("P"+p+"LeaveMsg", 1);
				ColouredChatToPlayer(p, "1,1,0", "You cannot jump or interract in the extraction zone.");
				ColouredChatToPlayer(p, "1,1,0", "You also cannot die or be attacked.");
			}
		}
	}
}

rule GoatAllDead
inactive
minInterval 5
{
	if((Stage == 3) && (PlayersDead == PlayersActive)){
		trShowWinLose("All players are dead", "xlose.wav");
		for(p=1 ; < cNumberNonGaiaPlayers){
			trSetPlayerDefeated(p);
		}
		xsDisableSelf();
		trEndGame();
	}
}

rule GoatExit
inactive
highFrequency
{
	trCounterAbort("poachtimer");
	xsDisableRule("GoatActLoops");
	xsDisableRule("GoatAllDead");
	xsDisableRule("GoatPoacherMovement");
	xsDisableRule("GoatEndZoneSee");
	xsDisableRule("GoatLeave");
	xsDisableRule("GoatTutorialLoops");
	xsDisableRule("GoatMinigameDetect");
	xsDisableRule("MGGOGoat");
	for(p=1 ; < cNumberNonGaiaPlayers){
		trUnitSelectByQV("P"+p+"Unit");
		trUnitChangeProtoUnit("Ragnorok SFX");
		trUnitSelectByQV("P"+p+"Unit");
		trUnitDestroy();
		trUnitSelectClear();
		trUnitSelect(""+xGetInt(dPlayerData, xSpyID));
		trUnitChangeProtoUnit("Hero Death");
		trCounterAbort("stamina"+p);
	}
	trClearCounterDisplay();
	xsEnableRule("ScoreScreenStart");
	xsDisableSelf();
}
