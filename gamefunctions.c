void ShootProjectile(vector dir = vector(0,0,0), vector startpos = vector(0,0,0), string protounit = "", string car = "", int anim = 0){
	int temp = 0;
	vector orient = xsVectorSet(xsVectorGetX(dir),0,xsVectorGetZ(dir));
	temp = trGetNextUnitScenarioNameNumber();
	UnitCreate(cNumberNonGaiaPlayers, "Dwarf", xsVectorGetX(startpos),xsVectorGetZ(startpos),0);
	if(IGUnit == true){
		IGUnit = false;
		trUnitSelectClear();
		trUnitSelect(""+IGName);
		trMutateSelected(kbGetProtoUnitID("Roc"));
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trImmediateUnitGarrison(""+IGName);
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeProtoUnit("Dwarf");
		trUnitSelectClear();
		trUnitSelect(""+IGName);
		trMutateSelected(kbGetProtoUnitID(unitcheck));
	}
	trUnitSelectClear();
	trUnitSelect(""+temp);
	trSetUnitOrientation(orient,vector(0,1,0),true);
	trSetScale(0);
	//THE CAR
	//dest = vectorSetAsTargetVector(startpos,dir,60.0);
	trUnitSelectClear();
	trUnitSelect(""+temp);
	int index = xAddDatabaseBlock(dIncomingMissiles, true);
	spyEffect(kbGetProtoUnitID("Trident Soldier"), 0, xsVectorSet(dIncomingMissiles, xMissileSpyID, index), vector(0,0,0));
	//THE SEAT, make 0,0,0
	xSetInt(dIncomingMissiles,xUnitID, temp);
	xSetVector(dIncomingMissiles, xMissilePos, startpos);
	xSetVector(dIncomingMissiles, xMissileDir, dir);
	xSetInt(dIncomingMissiles, xMissileProto, kbGetProtoUnitID(protounit));
	xSetInt(dIncomingMissiles, xMissileCarProto , kbGetProtoUnitID(car));
	xSetInt(dIncomingMissiles, xMissileAnim, anim);
}

rule DestroyConstant
highFrequency
inactive
{
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

rule CrocQuizQuestions
highFrequency
inactive
{
	//ODD QUESTIONS ANSWER TRUE
	//EVEN QUESTIONS ANSWER FALSE
	trStringQuestVarSet("Question1" ,"There are multiple crocodile species");
	trStringQuestVarSet("Question2", "Crocodiles cannot hear");
	trStringQuestVarSet("Question3", "Crocodiles lay eggs");
	trStringQuestVarSet("Question4", "The crocodile has a horizontal pupil");
	trStringQuestVarSet("Question5", "Alligators and crocodiles are different species");
	trStringQuestVarSet("Question6", "Crocodile feet are webbed");
	trStringQuestVarSet("Question7", "Generally, crocodiles are larger than alligators");
	trStringQuestVarSet("Question8", "Crocodiles enjoy cold weather");
	trStringQuestVarSet("Question9", "Crocodiles can grow beyond 6 metres in length");
	trStringQuestVarSet("Question10", "Steve Irwin was killed by a crocodile");
	trStringQuestVarSet("Question11", "Crocodiles eat humans");
	trStringQuestVarSet("Question12", "Crocodiles cannot grow new teeth");
	trQuestVarSet("MaxQNumber", 12);
	xsDisableSelf();
}

string ActName(int num = 0){
	string actnamed = "Error";
	switch(num)
	{
		case 1:
		{
			actnamed = "Act I - Deer";
		}
		case 2:
		{
			actnamed = "Act II - Rhino";
		}
		case 3:
		{
			actnamed = "Act III - Goat";
		}
		case 4:
		{
			actnamed = "Act IV - Crocodile";
		}
	}
	return(actnamed);
}

string ActIcon(int num = 0){
	string animaliconact = "Error";
	switch(num)
	{
		case 1:
		{
			animaliconact = "icons\animal gazelle icon 64";
		}
		case 2:
		{
			animaliconact = "icons\animal rhino icon 64";
		}
		case 3:
		{
			animaliconact = "icons\animal goat icon 64";
		}
		case 4:
		{
			animaliconact = "icons\animal crocodile icon 64";
		}
	}
	return(animaliconact);
}

//unused
string CurrentProto(int num = 0){
	string thename = "Error";
	switch(num)
	{
		case 1:
		{
			thename = GazelleProto;
		}
		case 2:
		{
			thename = RhinoProto;
		}
	}
	return(thename);
}

void CreateMinigameFlag(int x = 0, int z = 0){
	int tempnum = trGetNextUnitScenarioNameNumber();
	UnitCreate(0, "Dwarf", x,z,0);
	trUnitSelectClear();
	trUnitSelect(""+tempnum);
	trUnitChangeProtoUnit("Spy Eye");
	trUnitSelectClear();
	trUnitSelect(""+tempnum);
	trMutateSelected(kbGetProtoUnitID("Flag"));
	trUnitSelectClear();
	trUnitSelect(""+tempnum);
	trUnitSetAnimationPath("0,0,0,0,0,0");
	trUnitSelectClear();
	trUnitSelect(""+tempnum);
	trSetSelectedScale(2,2,2);
	trQuestVarSet("MinigameStartSFX", tempnum);
	tempnum = trGetNextUnitScenarioNameNumber();
	UnitCreate(0, "Dwarf", x,z,0);
	trUnitSelectClear();
	trUnitSelect(""+tempnum);
	trUnitChangeProtoUnit("Spy Eye");
	trUnitSelectClear();
	trUnitSelect(""+tempnum);
	trMutateSelected(kbGetProtoUnitID("Pyramid Osiris Xpack"));
	trUnitSelectClear();
	trUnitSelect(""+tempnum);
	trSetSelectedScale(100,0,0);
	trUnitSelectClear();
	trUnitSelect(""+tempnum);
	trUnitOverrideAnimation(6, 0, false, true, -1);
	trUnitSelectClear();
	trUnitSelect(""+tempnum);
	trUnitSetAnimationPath("0,0,1,0,0,0");
	trQuestVarSet("MinigameStartID", tempnum);
}

void SpawnDeerPoacher(int num = 0){
	int temp = 0;
	vector spawn = vector(0,0,0);
	vector EP = EndPoint*2;
	int allow = 0;
	if(InMinigame == false){
		while(num > 0){
			temp = trGetNextUnitScenarioNameNumber();
			trQuestVarSetFromRand("x",0,252);
			trQuestVarSetFromRand("z",0,252);
			spawn=xsVectorSet(1*trQuestVarGet("x"),5, 1*trQuestVarGet("z"));
			while((distanceBetweenVectors(spawn, EP, true) < 2000)){
				trQuestVarSetFromRand("x",0,252);
				trQuestVarSetFromRand("z",0,252);
				spawn=xsVectorSet(1*trQuestVarGet("x"),5, 1*trQuestVarGet("z"));
				continue;
			}
			for(p = 1; < cNumberNonGaiaPlayers){
				xSetPointer(dPlayerData, p);
				if((distanceBetweenVectors(spawn, kbGetBlockPosition(""+xGetInt(dPlayerData, xPlayerUnitID)),true) < 600) && (xGetBool(dPlayerData, xPlayerActive) == true)){
					allow = 1;
				}
			}
			if(allow == 0){
				UnitCreate(cNumberNonGaiaPlayers, "Throwing Axeman", 1*trQuestVarGet("x"), 1*trQuestVarGet("z"), 0);
				xAddDatabaseBlock(dPoachers, true);
				xSetInt(dPoachers, xUnitID, temp);
				xSetInt(dPoachers, xMoveTime, 0);
				num = num-1;
			}
			else if(allow == 1){
				allow = 0;
			}
		}
	}
}

void SpawnRhinoPoacher(int num = 0){
	int temp = 0;
	vector spawn = vector(0,0,0);
	vector EP = EndPoint*2;
	int allow = 0;
	if(InMinigame == false){
		while(num > 0){
			temp = trGetNextUnitScenarioNameNumber();
			trQuestVarSetFromRand("x",0,252);
			trQuestVarSetFromRand("z",0,252);
			spawn=xsVectorSet(1*trQuestVarGet("x"),5, 1*trQuestVarGet("z"));
			while((distanceBetweenVectors(spawn, EP, true) < 2000)){
				trQuestVarSetFromRand("x",0,252);
				trQuestVarSetFromRand("z",0,252);
				spawn=xsVectorSet(1*trQuestVarGet("x"),5, 1*trQuestVarGet("z"));
				continue;
			}
			for(p = 1; < cNumberNonGaiaPlayers){
				xSetPointer(dPlayerData, p);
				if((distanceBetweenVectors(spawn, kbGetBlockPosition(""+xGetInt(dPlayerData, xPlayerUnitID)),true) < 900) && (xGetBool(dPlayerData, xPlayerActive) == true)){
					allow = 1;
				}
			}
			if(allow == 0){
				UnitCreate(cNumberNonGaiaPlayers, "Slinger", 1*trQuestVarGet("x"), 1*trQuestVarGet("z"), 0);
				xAddDatabaseBlock(dPoachers, true);
				xSetInt(dPoachers, xUnitID, temp);
				xSetInt(dPoachers, xMoveTime, 0);
				num = num-1;
			}
			else if(allow == 1){
				allow = 0;
			}
		}
	}
}

void SpawnGoatPoacher(int num = 0){
	int temp = 0;
	vector spawn = vector(0,0,0);
	vector EP = EndPoint*2;
	int allow = 0;
	if(InMinigame == false){
		while(num > 0){
			temp = trGetNextUnitScenarioNameNumber();
			trQuestVarSetFromRand("x",0,252);
			trQuestVarSetFromRand("z",0,252);
			spawn=xsVectorSet(1*trQuestVarGet("x"),5, 1*trQuestVarGet("z"));
			while((distanceBetweenVectors(spawn, EP, true) < 2000)){
				trQuestVarSetFromRand("x",0,252);
				trQuestVarSetFromRand("z",0,252);
				spawn=xsVectorSet(1*trQuestVarGet("x"),5, 1*trQuestVarGet("z"));
				continue;
			}
			for(p = 1; < cNumberNonGaiaPlayers){
				xSetPointer(dPlayerData, p);
				if((distanceBetweenVectors(spawn, kbGetBlockPosition(""+xGetInt(dPlayerData, xPlayerUnitID)),true) < 1200) && (xGetBool(dPlayerData, xPlayerActive) == true)){
					allow = 1;
				}
			}
			if(allow == 0){
				UnitCreate(cNumberNonGaiaPlayers, "Throwing Axeman", 1*trQuestVarGet("x"), 1*trQuestVarGet("z"), 0);
				xAddDatabaseBlock(dPoachers, true);
				xSetInt(dPoachers, xUnitID, temp);
				xSetInt(dPoachers, xMoveTime, 0);
				num = num-1;
				trUnitSelectClear();
				trUnitSelect(""+temp);
				trSetScale(0);
				trUnitSelectClear();
				trUnitSelect(""+temp);
				spyEffect(kbGetProtoUnitID("Snowman"), 0, vector(0,0,0), vector(2,2,2));
			}
			else if(allow == 1){
				allow = 0;
			}
		}
	}
}

void SpawnRhinoSuperPoacher(int num = 0){
	int temp = 0;
	vector spawn = vector(0,0,0);
	vector EP = EndPoint*2;
	int allow = 0;
	if(InMinigame == false){
		while(num > 0){
			temp = trGetNextUnitScenarioNameNumber();
			trQuestVarSetFromRand("x",0,252);
			trQuestVarSetFromRand("z",0,252);
			spawn=xsVectorSet(1*trQuestVarGet("x"),5, 1*trQuestVarGet("z"));
			while((distanceBetweenVectors(spawn, EP, true) < 1000)){
				trQuestVarSetFromRand("x",0,252);
				trQuestVarSetFromRand("z",0,252);
				spawn=xsVectorSet(1*trQuestVarGet("x"),5, 1*trQuestVarGet("z"));
				continue;
			}
			for(p = 1; < cNumberNonGaiaPlayers){
				xSetPointer(dPlayerData, p);
				if((distanceBetweenVectors(spawn, kbGetBlockPosition(""+xGetInt(dPlayerData, xPlayerUnitID)),true) < 1000) && (xGetBool(dPlayerData, xPlayerActive) == true)){
					allow = 1;
				}
			}
			if(allow == 0){
				UnitCreate(cNumberNonGaiaPlayers, "Chu Ko Nu", 1*trQuestVarGet("x"), 1*trQuestVarGet("z"), 0);
				xAddDatabaseBlock(dPoachers, true);
				xSetInt(dPoachers, xUnitID, temp);
				xSetInt(dPoachers, xMoveTime, 0);
				num = num-1;
				if(num == 0){
					playSound("\cinematics\04_in\armyarrive.wav");
				}
			}
			else if(allow == 1){
				allow = 0;
			}
		}
	}
}

void hotkeyAbility(int ability = 0) {
	xsSetContextPlayer(0);
	int old = xGetPointer(dPlayerData);
	xSetPointer(dPlayerData, trCurrentPlayer());
	if (xGetBool(dPlayerData, xPlayerActive)) {
		trackInsert();
		trackAddWaypoint();
		trackPlay(1,EVENT_BUILD_AT_CURSOR);
		trBlockAllSounds(false);
		xUnitSelectByID(dPlayerData, xPlayerUnitID);
		//if (trUnitIsSelected() == false) {
		//	uiFindType(""+GazelleProto);
		//}
		if(trPlayerUnitCountSpecific(xGetPointer(dPlayerData), ""+GazelleProto) > 0){
			switch(ability)
			{
				case EVENT_BUILD_HOUSE:
				{
					uiSetProtoCursor("House", true);
				}
				case EVENT_BUILD_GRANARY:
				{
					uiSetProtoCursor("Granary", true);
				}
				case EVENT_BUILD_STOREHOUSE:
				{
					uiSetProtoCursor("Storehouse", true);
				}
			}
		}
		if(trPlayerUnitCountSpecific(xGetPointer(dPlayerData), ""+RhinoProto) > 0){
			switch(ability)
			{
				case EVENT_BUILD_HOUSE:
				{
					uiSetProtoCursor("House", true);
				}
				case EVENT_BUILD_GRANARY:
				{
					uiSetProtoCursor("Granary", true);
				}
				case EVENT_BUILD_STOREHOUSE:
				{
					uiSetProtoCursor("Storehouse", true);
				}
			}
		}
		if(trPlayerUnitCountSpecific(xGetPointer(dPlayerData), ""+GoatProto) > 0){
			switch(ability)
			{
				case EVENT_BUILD_HOUSE:
				{
					uiSetProtoCursor("House", true);
				}
				case EVENT_BUILD_GRANARY:
				{
					uiSetProtoCursor("Granary", true);
				}
				case EVENT_BUILD_STOREHOUSE:
				{
					uiSetProtoCursor("Storehouse", true);
				}
			}
		}
		if(trPlayerUnitCountSpecific(xGetPointer(dPlayerData), ""+CrocProto) > 0){
			switch(ability)
			{
				case EVENT_BUILD_HOUSE:
				{
					uiSetProtoCursor("House", true);
				}
				case EVENT_BUILD_GRANARY:
				{
					uiSetProtoCursor("Granary", true);
				}
				case EVENT_BUILD_STOREHOUSE:
				{
					uiSetProtoCursor("Storehouse", true);
				}
			}
		}
	}
	xSetPointer(dPlayerData, old);
}

void buildAtCursor(int eventID = -1) {
	uiBuildAtPointer();
	uiClearCursor();
	trackInsert();
	trackAddWaypoint();
	trackPlay(1,EVENT_REMOVE_CAM_TRACKS);
}

int BlueText(int a = 3){
	if(cNumberNonGaiaPlayers > 3){
		a = 4;
	}
	else{
		a = 1;
	}
	return(a);
}

int GreenText(int a = 3){
	if(cNumberNonGaiaPlayers > 2){
		a = 3;
	}
	else{
		a = 0;
	}
	return(a);
}

int RedText(int a = 2){
	if(cNumberNonGaiaPlayers > 1){
		a = 2;
	}
	else{
		a = 0;
	}
	return(a);
}


void CreateGazelle(int p = 1, int x = 1, int z = 1, int heading = 0){
	trQuestVarSet("P"+p+"Unit", trGetNextUnitScenarioNameNumber());
	UnitCreate(p, ""+GazelleProto, x, z, heading);
	trUnitSelectByQV("P"+p+"Unit");
	trSetSelectedScale(0,1,0);
	trUnitSelectByQV("P"+p+"Unit");
	spyEffect(kbGetProtoUnitID("Gazelle"), 0, xsVectorSet(dPlayerData,xSpyID,p), vector(1,1,1));
	xSetPointer(dPlayerData, p);
	xSetInt(dPlayerData, xPlayerUnitID, 1*trQuestVarGet("P"+p+"Unit"));
	xSetBool(dPlayerData, xStopDeath, false);
	/*
	vector test = kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit"));
	test = test + HeadingToVector(heading);
	test = test + HeadingToVector(heading);
	UnitCreate(p, "Dwarf", xsVectorGetX(test),xsVectorGetZ(test), 0);
	*/
}

void CreateRhino(int p = 1, int x = 1, int z = 1, int heading = 0){
	trQuestVarSet("P"+p+"Unit", trGetNextUnitScenarioNameNumber());
	UnitCreate(p, ""+RhinoProto, x, z, heading);
	trUnitSelectByQV("P"+p+"Unit");
	trSetSelectedScale(0,1,0);
	trUnitSelectByQV("P"+p+"Unit");
	spyEffect(kbGetProtoUnitID("Rhinocerous"), 0, xsVectorSet(dPlayerData,xSpyID,p), vector(1,1,1));
	//spyEffect(kbGetProtoUnitID("Cinematic Block"), 0, xsVectorSet(dPlayerData,xSecondSpy,p), vector(1,1,1));
	xSetPointer(dPlayerData, p);
	xSetInt(dPlayerData, xPlayerUnitID, 1*trQuestVarGet("P"+p+"Unit"));
	xSetBool(dPlayerData, xStopDeath, false);
	/*
	vector test = kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit"));
	test = test + HeadingToVector(heading);
	test = test + HeadingToVector(heading);
	UnitCreate(p, "Dwarf", xsVectorGetX(test),xsVectorGetZ(test), 0);
	*/
}

void CreateGoat(int p = 1, int x = 1, int z = 1, int heading = 0){
	trQuestVarSet("P"+p+"Unit", trGetNextUnitScenarioNameNumber());
	UnitCreate(p, ""+GoatProto, x, z, heading);
	trUnitSelectByQV("P"+p+"Unit");
	trSetSelectedScale(0,0.3,0);
	trUnitSelectByQV("P"+p+"Unit");
	spyEffect(kbGetProtoUnitID("Goat"), 0, xsVectorSet(dPlayerData,xSpyID,p), vector(1,1,1));
	//spyEffect(kbGetProtoUnitID("Cinematic Block"), 0, xsVectorSet(dPlayerData,xSecondSpy,p), vector(1,1,1));
	xSetPointer(dPlayerData, p);
	xSetInt(dPlayerData, xPlayerUnitID, 1*trQuestVarGet("P"+p+"Unit"));
	xSetBool(dPlayerData, xStopDeath, false);
	/*
	vector test = kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit"));
	test = test + HeadingToVector(heading);
	test = test + HeadingToVector(heading);
	UnitCreate(p, "Dwarf", xsVectorGetX(test),xsVectorGetZ(test), 0);
	*/
}

void CreateCroc(int p = 1, int x = 1, int z = 1, int heading = 0){
	trQuestVarSet("P"+p+"Unit", trGetNextUnitScenarioNameNumber());
	UnitCreate(p, ""+CrocProto, x, z, heading);
	trUnitSelectByQV("P"+p+"Unit");
	trSetSelectedScale(0,1,0);
	trUnitSelectByQV("P"+p+"Unit");
	spyEffect(kbGetProtoUnitID("Crocodile"), 0, xsVectorSet(dPlayerData,xSpyID,p), vector(1,1,1));
	//spyEffect(kbGetProtoUnitID("Cinematic Block"), 0, xsVectorSet(dPlayerData,xSecondSpy,p), vector(1,1,1));
	xSetPointer(dPlayerData, p);
	xSetInt(dPlayerData, xPlayerUnitID, 1*trQuestVarGet("P"+p+"Unit"));
	xSetBool(dPlayerData, xStopDeath, false);
	trUnitSelectClear();
	xUnitSelect(dPlayerData, xSpyID);
	float scale = 0.25*xGetInt(dPlayerData, xCrocSize)+0.75;
	trSetScale(scale);
	/*
	vector test = kbGetBlockPosition(""+1*trQuestVarGet("P"+p+"Unit"));
	test = test + HeadingToVector(heading);
	test = test + HeadingToVector(heading);
	UnitCreate(p, "Dwarf", xsVectorGetX(test),xsVectorGetZ(test), 0);
	*/
}

void CreateChest(int x = 1, int z = 1, int heading = -1){
	if(heading == -1){
		trQuestVarSetFromRand("temph",0,360,true);
		heading = 1*trQuestVarGet("temph");
	}
	int ChestQuery = 0;
	trQuestVarSet("temp",trGetNextUnitScenarioNameNumber());
	UnitCreate(0, "Dwarf", x*2, z*2, heading);
	trUnitSelectByQV("temp");
	trUnitChangeProtoUnit("Titan Atlantean");
	trUnitSelectByQV("temp");
	trUnitChangeProtoUnit("Great Box");
	trUnitSelectByQV("temp");
	trSetSelectedScale(0.6,0.6,0.6);
	trUnitSelectByQV("temp");
	trUnitHighlight(10000, false);
	yFindLatestReverse("temp2", "Titan Gate Dead", 0);
	trUnitSelectByQV("temp2");
	trUnitChangeProtoUnit("Dwarf");
	trUnitSelectByQV("temp2");
	trUnitChangeProtoUnit("Cinematic Block");
	xAddDatabaseBlock(dChests, true);
	xSetInt(dChests, xUnitID, 1*trQuestVarGet("temp"));
	xSetInt(dChests, xUnlockUnitID, 1*trQuestVarGet("temp2"));
	ChestsTotal = ChestsTotal+1;
}

void AddTileMGDeer(int x = 0, int z = 0){
	int count = xGetDatabaseCount(dTiles1);
	xAddDatabaseBlock(dTiles1, true);
	xSetInt(dTiles1, xTileX, x);
	xSetInt(dTiles1, xTileZ, z);
	xSetInt(dTiles1, xTileNumber, count+1);
	xSetInt(dTiles1, xTileType, trGetTerrainType(x,z));
	xSetInt(dTiles1, xTileSubType,trGetTerrainSubType(x,z));
}

void AddTileMGDeer2(int x = 0, int z = 0){
	int count = xGetDatabaseCount(dTiles2);
	xAddDatabaseBlock(dTiles2, true);
	xSetInt(dTiles2, xTileX, x);
	xSetInt(dTiles2, xTileZ, z);
	xSetInt(dTiles2, xTileNumber, count+1);
	xSetInt(dTiles2, xTileType, trGetTerrainType(x,z));
	xSetInt(dTiles2, xTileSubType,trGetTerrainSubType(x,z));
}

void ToggleCharge(int p = 0){
	xSetPointer(dPlayerData, p);
	if(xGetBool(dPlayerData, xCharge) == false){
		xSetBool(dPlayerData, xCharge, true);
		modifyProtounitAbsolute(""+RhinoProto, p, 1, xGetFloat(dPlayerData, xRhinoRun));
		if(trCurrentPlayer() == p){
			playSound("rumble.wav");
		}
	}
	else if(xGetBool(dPlayerData, xCharge) == true){
		xSetBool(dPlayerData, xCharge, false);
		modifyProtounitAbsolute(""+RhinoProto, p, 1, xGetFloat(dPlayerData, xRhinoWalk));
		//end
	}
}

void CrocGrow(int p = 0){
	xSetPointer(dPlayerData, p);
	xSetInt(dPlayerData, xCrocSize, xGetInt(dPlayerData, xCrocSize)+1);
	xSetFloat(dPlayerData, xCrocFood, 0);
	//5+2*xGetInt(dPlayerData, xCrocSize)
	xSetFloat(dPlayerData, xCrocNext, 1);
	trUnitSelectClear();
	xUnitSelect(dPlayerData, xSpyID);
	float scale = 0.25*xGetInt(dPlayerData, xCrocSize)+0.75;
	trSetScale(scale);
	debugLog("Scale: " + scale);
	if(trCurrentPlayer() == p){
		playSound("ageadvance.wav");
	}
	trModifyProtounit(""+CrocProto, p, 0, 2);
	trModifyProtounit(""+CrocProto, p, 2, 2);
	trModifyProtounit(""+CrocProto, p, 29, 2);
	xSetFloat(dPlayerData, xCrocLandSpeed, xGetFloat(dPlayerData, xCrocLandSpeed)+0.2);
	xSetFloat(dPlayerData, xCrocWaterSpeed, xGetFloat(dPlayerData, xCrocWaterSpeed)+0.35);
	trUnitSelectByQV("P"+p+"Unit");
	trDamageUnit(-1);
	if(iModulo(4, xGetInt(dPlayerData, xCrocSize)-1) == 0){
		//debugLog("Factor 4");
		trModifyProtounit(""+CrocProto, p, 0, 5);
		trModifyProtounit(""+CrocProto, p, 29, 6);
		xSetInt(dPlayerData, xCrocSprintDuration, xGetInt(dPlayerData, xCrocSprintDuration)+1000);
		xSetInt(dPlayerData, xCrocSprintRechargeTime, xGetInt(dPlayerData, xCrocSprintRechargeTime)-1);
		trDamageUnit(-1);
		if(xGetInt(dPlayerData, xCrocSize) == 5){
			ColouredIconChatToPlayer(p, "0,0,0.7", "icons\animal crocodile icon", "You can now use 'W' to eat Chu Ko Nus!");
		}
	}
}
