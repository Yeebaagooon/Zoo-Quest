void ShootProjectile(vector dir = vector(0,0,0), vector startpos = vector(0,0,0), string protounit = "", string car = "", int anim = 0, int dmg = 1, int time = 10000, int ownerof = 0){
	int temp = 0;
	if(ownerof == 0){
		ownerof = cNumberNonGaiaPlayers;
	}
	vector orient = xsVectorSet(xsVectorGetX(dir),0,xsVectorGetZ(dir));
	temp = trGetNextUnitScenarioNameNumber();
	UnitCreate(ownerof, "Dwarf", xsVectorGetX(startpos),xsVectorGetZ(startpos),0);
	if(IGUnit == true){
		IGUnit = false;
		if(unitcheck != "Tower"){
			trUnitSelectClear();
			trUnitSelect(""+IGName);
			trMutateSelected(kbGetProtoUnitID("Roc"));
		}
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trImmediateUnitGarrison(""+IGName);
		trUnitSelectClear();
		trUnitSelect(""+temp);
		trUnitChangeProtoUnit("Dwarf");
		trUnitSelectClear();
		if(unitcheck != "Tower"){
			trUnitSelect(""+IGName);
			trMutateSelected(kbGetProtoUnitID(unitcheck));
		}
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
	xSetInt(dIncomingMissiles, xOwner, ownerof);
	xSetVector(dIncomingMissiles, xMissilePos, startpos);
	xSetVector(dIncomingMissiles, xMissileDir, dir);
	xSetInt(dIncomingMissiles, xMissileProto, kbGetProtoUnitID(protounit));
	xSetInt(dIncomingMissiles, xMissileCarProto , kbGetProtoUnitID(car));
	xSetInt(dIncomingMissiles, xMissileAnim, anim);
	xSetInt(dIncomingMissiles, xIMissileDmg, dmg);
	xSetInt(dIncomingMissiles, xIMissileTime, time);
	if(protounit == "Meteorite"){
		xAddDatabaseBlock(dBurner, true);
		xSetInt(dBurner, xUnitID, temp);
	}
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
	trStringQuestVarSet("Question13", "Deer antlers will grow back");
	trStringQuestVarSet("Question14", "Deer eyes are on the front of the head");
	trStringQuestVarSet("Question15", "Deer can be white");
	trStringQuestVarSet("Question16", "Reindeer can be found in Antarctica");
	trQuestVarSet("MaxQNumber", 20);
	trStringQuestVarSet("Question17", "The word rhinoceros is a combination of two Greek words, 'rhino' and 'ceros'");
	trStringQuestVarSet("Question18", "Rhino horns are made of bone");
	trStringQuestVarSet("Question19", "Deer antlers are made of bone");
	trStringQuestVarSet("Question20", "A group of Rhinos is called a herd");
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
		case 5:
		{
			actnamed = "Act V - Chicken";
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
		case 5:
		{
			animaliconact = "icons\animal chicken icon 64";
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
		case 3:
		{
			thename = GoatProto;
		}
		case 4:
		{
			thename = CrocProto;
		}
		case 5:
		{
			thename = ChickenProto;
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
				if((distanceBetweenVectors(spawn, kbGetBlockPosition(""+xGetInt(dPlayerData, xPlayerUnitID)),true) < 1000) && (xGetBool(dPlayerData, xPlayerActive) == true)){
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
		if (trUnitIsSelected() == false) {
			uiFindType(CurrentProto());
		}
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
		if(trPlayerUnitCountSpecific(xGetPointer(dPlayerData), "Petsuchos") > 0){
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
		if(trPlayerUnitCountSpecific(xGetPointer(dPlayerData), ""+ChickenProto) > 0){
			switch(ability)
			{
				case EVENT_BUILD_HOUSE:
				{
					uiSetProtoCursor("Tower", true);
				}
				case EVENT_BUILD_GRANARY:
				{
					uiSetProtoCursor("Armory", true);
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
	xSetPointer(dPlayerData, p);
	trQuestVarSet("P"+p+"Unit", trGetNextUnitScenarioNameNumber());
	UnitCreate(p, ""+GazelleProto, x, z, heading);
	trUnitSelectByQV("P"+p+"Unit");
	trSetSelectedScale(0,1,0);
	trUnitSelectByQV("P"+p+"Unit");
	spyEffect(kbGetProtoUnitID("Gazelle"), 0, xsVectorSet(dPlayerData,xSpyID,p), vector(1,1,1));
	xSetInt(dPlayerData, xPlayerUnitID, 1*trQuestVarGet("P"+p+"Unit"));
	xSetBool(dPlayerData, xStopDeath, false);
}

void CreateRhino(int p = 1, int x = 1, int z = 1, int heading = 0){
	xSetPointer(dPlayerData, p);
	trQuestVarSet("P"+p+"Unit", trGetNextUnitScenarioNameNumber());
	UnitCreate(p, ""+RhinoProto, x, z, heading);
	trUnitSelectByQV("P"+p+"Unit");
	trSetSelectedScale(0,1,0);
	trUnitSelectByQV("P"+p+"Unit");
	spyEffect(kbGetProtoUnitID("Rhinocerous"), 0, xsVectorSet(dPlayerData,xSpyID,p), vector(1,1,1));
	//spyEffect(kbGetProtoUnitID("Cinematic Block"), 0, xsVectorSet(dPlayerData,xSecondSpy,p), vector(1,1,1));
	xSetInt(dPlayerData, xPlayerUnitID, 1*trQuestVarGet("P"+p+"Unit"));
	xSetBool(dPlayerData, xStopDeath, false);
}

void CreateGoat(int p = 1, int x = 1, int z = 1, int heading = 0){
	xSetPointer(dPlayerData, p);
	trQuestVarSet("P"+p+"Unit", trGetNextUnitScenarioNameNumber());
	UnitCreate(p, ""+GoatProto, x, z, heading);
	trUnitSelectByQV("P"+p+"Unit");
	trSetSelectedScale(0,0.3,0);
	trUnitSelectByQV("P"+p+"Unit");
	spyEffect(kbGetProtoUnitID("Goat"), 0, xsVectorSet(dPlayerData,xSpyID,p), vector(1,1,1));
	//spyEffect(kbGetProtoUnitID("Cinematic Block"), 0, xsVectorSet(dPlayerData,xSecondSpy,p), vector(1,1,1));
	xSetInt(dPlayerData, xPlayerUnitID, 1*trQuestVarGet("P"+p+"Unit"));
	xSetBool(dPlayerData, xStopDeath, false);
}

void CreateCroc(int p = 1, int x = 1, int z = 1, int heading = 0){
	xSetPointer(dPlayerData, p);
	trQuestVarSet("P"+p+"Unit", trGetNextUnitScenarioNameNumber());
	UnitCreate(p, ""+CrocProto, x, z, heading);
	trUnitSelectByQV("P"+p+"Unit");
	trSetSelectedScale(0,1,0);
	trUnitSelectByQV("P"+p+"Unit");
	spyEffect(kbGetProtoUnitID("Crocodile"), 0, xsVectorSet(dPlayerData,xSpyID,p), vector(1,1,1));
	//spyEffect(kbGetProtoUnitID("Cinematic Block"), 0, xsVectorSet(dPlayerData,xSecondSpy,p), vector(1,1,1));
	xSetInt(dPlayerData, xPlayerUnitID, 1*trQuestVarGet("P"+p+"Unit"));
	xSetBool(dPlayerData, xStopDeath, false);
	trUnitSelectClear();
	xUnitSelect(dPlayerData, xSpyID);
	float scale = 0.25*xGetInt(dPlayerData, xCrocSize)+0.75;
	trSetScale(scale);
}

void CreateChicken(int p = 1, int x = 1, int z = 1, int heading = 0){
	if(AllowChicken == 1){
		xSetPointer(dPlayerData, p);
		trQuestVarSet("P"+p+"Unit", trGetNextUnitScenarioNameNumber());
		UnitCreate(p, ""+ChickenProto, x, z, heading);
		trUnitSelectByQV("P"+p+"Unit");
		//[SUPER FUCKING STRANGE RELIC SHRINK]
		trSetSelectedScale(0.000001,0.000001,0.000001);
		trUnitSelectByQV("P"+p+"Unit");
		spyEffect(kbGetProtoUnitID("Chicken"), 0, xsVectorSet(dPlayerData,xSpyID,p), vector(2,2,2));
		//spyEffect(kbGetProtoUnitID("Cinematic Block"), 0, xsVectorSet(dPlayerData,xSecondSpy,p), vector(1,1,1));
		xSetInt(dPlayerData, xPlayerUnitID, 1*trQuestVarGet("P"+p+"Unit"));
		xSetBool(dPlayerData, xStopDeath, false);
		
		xAddDatabaseBlock(dEnemyCollision, true);
		xSetInt(dEnemyCollision, xUnitID, 1*trQuestVarGet("P"+p+"Unit"));
	}
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

void SpawnShop(string powertechname = "", string powerdispname = "", int costofpower = 1){
	int temp = 0;
	int firstunit = 0;
	int num = 1;
	while(num > 0){
		trQuestVarSetFromRand("x", 0, 126);
		trQuestVarSetFromRand("z", 0, 126);
		firstunit = trGetNextUnitScenarioNameNumber();
		trQuestVarSetFromRand("temph",0,360,true);
		UnitCreate(0, "Cinematic Block", 2*trQuestVarGet("x"),2*trQuestVarGet("z"), 1*trQuestVarGet("temph"));
		if((trGetTerrainType(1*trQuestVarGet("x"), 1*trQuestVarGet("z")) != getTerrainType("IceA")) && (trGetTerrainSubType(1*trQuestVarGet("x"), 1*trQuestVarGet("z")) != getTerrainSubType("IceA"))){
			if(trCountUnitsInArea(""+firstunit, 0, "Obelisk", 20) == 0){
				temp = trGetNextUnitScenarioNameNumber();
				UnitCreate(0, "Cinematic Block", 2*trQuestVarGet("x"),2*trQuestVarGet("z"), 1*trQuestVarGet("temph"));
				trUnitSelectClear();
				trUnitSelect(""+firstunit);
				trUnitChangeProtoUnit("Obelisk");
				trUnitSelectClear();
				trUnitSelect(""+firstunit);
				trUnitSetAnimationPath("2,0,0,0,0,0");
				trUnitSelectClear();
				trUnitSelect(""+temp);
				trUnitChangeProtoUnit("Spy Eye");
				trUnitSelectClear();
				trUnitSelect(""+temp);
				trMutateSelected(kbGetProtoUnitID("Guardian XP"));
				trUnitSelectClear();
				trUnitSelect(""+temp);
				trSetScale(0);
				xAddDatabaseBlock(dShop, true);
				xSetInt(dShop, xUnitID, firstunit);
				xSetString(dShop, xPower, powerdispname);
				xSetString(dShop, xPowerName, powertechname);
				xSetInt(dShop, xDecorationID, temp);
				xSetInt(dShop, xCost, costofpower);
				num = 0;
			}
		}
	}
}

void CrocGrow(int p = 0){
	xSetPointer(dPlayerData, p);
	xSetInt(dPlayerData, xCrocSize, xGetInt(dPlayerData, xCrocSize)+1);
	CrocProgress = CrocProgress+1;
	xSetFloat(dPlayerData, xCrocFood, xGetFloat(dPlayerData, xCrocFood)-xGetFloat(dPlayerData, xCrocNext));
	//4+2*xGetInt(dPlayerData, xCrocSize)
	xSetFloat(dPlayerData, xCrocNext, 4+2*xGetInt(dPlayerData, xCrocSize));
	if(Difficulty == 3){
		xSetFloat(dPlayerData, xCrocNext, xGetFloat(dPlayerData, xCrocNext)+1);
	}
	if(xGetFloat(dPlayerData, xCrocFood) < 0){
		xSetFloat(dPlayerData, xCrocFood, 0);
	}
	trUnitSelectClear();
	xUnitSelect(dPlayerData, xSpyID);
	float scale = 0.25*xGetInt(dPlayerData, xCrocSize)+0.75;
	trSetScale(scale);
	//debugLog("Scale: " + scale);
	if(trCurrentPlayer() == p){
		playSound("ageadvance.wav");
	}
	trModifyProtounit(""+CrocProto, p, 0, 2);
	trModifyProtounit(""+CrocProto, p, 2, 2);
	trModifyProtounit(""+CrocProto, p, 29, 2);
	trModifyProtounit("Petsuchos", p, 0, 2);
	trModifyProtounit("Petsuchos", p, 2, 2);
	trModifyProtounit("Petsuchos", p, 29, 2);
	xSetFloat(dPlayerData, xCrocLandSpeed, xGetFloat(dPlayerData, xCrocLandSpeed)+0.2);
	xSetFloat(dPlayerData, xCrocWaterSpeed, xGetFloat(dPlayerData, xCrocWaterSpeed)+0.35);
	trUnitSelectByQV("P"+p+"Unit");
	trDamageUnit(-1);
	if(iModulo(4, xGetInt(dPlayerData, xCrocSize)-1) == 0){
		//debugLog("Factor 4");
		trModifyProtounit(""+CrocProto, p, 0, 5);
		trModifyProtounit("Petsuchos", p, 0, 5);
		trModifyProtounit(""+CrocProto, p, 29, 6);
		xSetInt(dPlayerData, xCrocSprintDuration, xGetInt(dPlayerData, xCrocSprintDuration)+1000);
		xSetInt(dPlayerData, xCrocSprintRechargeTime, xGetInt(dPlayerData, xCrocSprintRechargeTime)-1);
		trDamageUnit(-1);
	}
	if(xGetInt(dPlayerData, xCrocSize) == 3){
		ColouredIconChatToPlayer(p, "0,0,0.7", "icons\animal crocodile icon 64", "You can now use 'W' to sink Kebenits!");
	}
	if(xGetInt(dPlayerData, xCrocSize) == 5){
		ColouredIconChatToPlayer(p, "0,0,0.7", "icons\animal crocodile icon 64", "You can now use 'W' to eat Chu Ko Nus!");
	}
	if(xGetInt(dPlayerData, xCrocSize) == 7){
		ColouredIconChatToPlayer(p, "0,0,0.7", "icons\animal crocodile icon 64", "Goal achieved!");
		ColouredChatToPlayer(p, "0,0,0.7", "You can still grow further");
		ColouredChatToPlayer(p, "0,0,0.7", "But you may attract even more deadly poachers...");
		if(trCurrentPlayer() == p){
			playSoundCustom("cinematics\10_in\clearedcity.wav", "\Yeebaagooon\Zoo Quest\Skillpoint.mp3");
		}
	}
	if(xGetInt(dPlayerData, xCrocSize) == 8){
		ColouredIconChatToPlayer(p, "0,0,0.7", "icons\animal crocodile icon 64", "You can now use 'W' to eat Peltasts!");
		ColouredChatToPlayer(p, "0,0,0.7", "They do a lot of damage so you may want to avoid them.");
	}
	if(xGetInt(dPlayerData, xCrocSize) == 9){
		ColouredIconChatToPlayer(p, "0,0,0.7", "icons\animal crocodile icon 64", "You can now use 'W' to eat Sentinels!");
	}
	if(xGetInt(dPlayerData, xCrocSize) == 10){
		ColouredIconChatToPlayer(p, "1,0,0", "icons\animal crocodile icon 64", "You have become an infamous man eater!");
		ColouredIconChatToPlayer(p, "1,0,0", "icons\animal crocodile icon 64", "The world's top poachers are coming for you.");
		trQuestVarSet("AllowS4Uber", 1);
	}
	trSetCivilizationNameOverride(p, "Level " + xGetInt(dPlayerData, xCrocSize));
}


rule DebugRevive
highFrequency
active
{
	if(trCheckGPActive("Rain", 1)){
		//[revive debug]
		for(p = 1; < cNumberNonGaiaPlayers){
			xSetPointer(dPlayerData, p);
			if(xGetBool(dPlayerData, xPlayerActive) == true){
				if(xGetBool(dPlayerData, xPlayerDead) == true){
					xSetBool(dPlayerData, xPlayerDead, false);
					PlayersDead = PlayersDead-1;
					trUnitSelectByQV("P"+p+"Unit");
					trUnitDestroy();
					xUnitSelect(dPlayerData, xSpyID);
					trUnitDestroy();
					UnitCreateV(0, "Revealer To Player", xGetVector(dPlayerData, xDeathVector));
					if(Stage == 1){
						CreateGazelle(p, xsVectorGetX(xGetVector(dPlayerData, xDeathVector)), xsVectorGetZ(xGetVector(dPlayerData, xDeathVector)), 0);
					}
					if(Stage == 2){
						CreateRhino(p, xsVectorGetX(xGetVector(dPlayerData, xDeathVector)), xsVectorGetZ(xGetVector(dPlayerData, xDeathVector)), 0);
					}
					if(Stage == 3){
						CreateGoat(p, xsVectorGetX(xGetVector(dPlayerData, xDeathVector)), xsVectorGetZ(xGetVector(dPlayerData, xDeathVector)), 0);
					}
					if(Stage == 4){
						CreateCroc(p, xsVectorGetX(xGetVector(dPlayerData, xDeathVector)), xsVectorGetZ(xGetVector(dPlayerData, xDeathVector)), 0);
					}
					if(Stage == 5){
						CreateChicken(p, xsVectorGetX(xGetVector(dPlayerData, xDeathVector)), xsVectorGetZ(xGetVector(dPlayerData, xDeathVector)), 0);
					}
					trUnitSelectByQV("P"+p+"Unit");
					trSetScale(1);
					uiZoomToProto(CurrentProto());
					uiLookAtProto(CurrentProto());
				}
			}
		}
		xsDisableSelf();
		xsEnableRule("DebugTimer");
		playSound("herorevived.wav");
		trOverlayText("DEBUG: Players revived!", 3.0,-1,-1,600);
	}
}

rule DebugTimer
highFrequency
inactive
{
	if (trTime() > cActivationTime + 1) {
		for(p = 1; < cNumberNonGaiaPlayers){
		}
		xsDisableSelf();
		xsEnableRule("DebugRevive");
		debugLog("PlayersActive = " + PlayersActive);
		debugLog("PlayersDead = " + PlayersDead);
	}
}

void DoRelicSFX(int id = 0, int type = 0){
	trUnitSelectClear();
	trUnitSelect(""+id);
	if(type == RELIC_ATTACK){
		trUnitChangeProtoUnit("Spy Eye");
		trUnitSelectClear();
		trUnitSelect(""+id);
		trMutateSelected(kbGetProtoUnitID("Theris"));
		trUnitSelectClear();
		trUnitSelect(""+id);
		trSetScale(0);
	}
	if(type == RELIC_HP){
		trUnitChangeProtoUnit("Spy Eye");
		trUnitSelectClear();
		trUnitSelect(""+id);
		trMutateSelected(kbGetProtoUnitID("Tower Mirror"));
		trUnitSelectClear();
		trUnitSelect(""+id);
		trSetScale(0);
	}
	if(type == RELIC_PROJ_SPEED){
		trUnitChangeProtoUnit("Spy Eye");
		trUnitSelectClear();
		trUnitSelect(""+id);
		trMutateSelected(kbGetProtoUnitID("Volcano"));
		trUnitSelectClear();
		trUnitSelect(""+id);
		trSetScale(0.8);
	}
	if(type == RELIC_CHICKEN_SPEED){
		trUnitChangeProtoUnit("Spy Eye");
		trUnitSelectClear();
		trUnitSelect(""+id);
		trMutateSelected(kbGetProtoUnitID("Pegasus"));
		trUnitSelectClear();
		trUnitSelect(""+id);
		trSetScale(0.5);
		trUnitSelectClear();
		trUnitSelect(""+id);
		trSetSelectedHeight(1.0);
	}
	if(type == RELIC_RANGE){
		trUnitChangeProtoUnit("Spy Eye");
		trUnitSelectClear();
		trUnitSelect(""+id);
		trMutateSelected(kbGetProtoUnitID("Guardian XP"));
		trUnitSelectClear();
		trUnitSelect(""+id);
		trSetScale(0);
	}
	if(type == RELIC_TOWER){
		trUnitChangeProtoUnit("Spy Eye");
		trUnitSelectClear();
		trUnitSelect(""+id);
		trMutateSelected(kbGetProtoUnitID("undermine ground decal corner"));
		trUnitSelectClear();
		trUnitSelect(""+id);
		trSetScale(0.8);
	}
	if(type == RELIC_CHICKEN_HP){
		trUnitChangeProtoUnit("Spy Eye");
		trUnitSelectClear();
		trUnitSelect(""+id);
		trMutateSelected(kbGetProtoUnitID("Chicken Exploding"));
		trUnitSelectClear();
		trUnitSelect(""+id);
		trSetScale(2);
	}
	if(type == RELIC_CHICKEN_HEAL){
		trUnitChangeProtoUnit("Spy Eye");
		trUnitSelectClear();
		trUnitSelect(""+id);
		trMutateSelected(kbGetProtoUnitID("Healing SFX"));
	}
	if(type == RELIC_TOWER_HEAL){
		trUnitChangeProtoUnit("Spy Eye");
		trUnitSelectClear();
		trUnitSelect(""+id);
		trMutateSelected(kbGetProtoUnitID("Poison SFX"));
		trUnitSelectClear();
		trUnitSelect(""+id);
		trSetScale(0.2);
	}
}

void ForceRelic(int id = 0, int type = 0, float stat = 0){
	xAddDatabaseBlock(dFreeRelics, true);
	xSetInt(dFreeRelics, xUnitID, id);
	xSetInt(dFreeRelics, xRelicType, type);
	xSetFloat(dFreeRelics, xRelicStat, stat);
	//?pointer
	xUnitSelect(dFreeRelics, xUnitID);
	trUnitChangeProtoUnit("Titan Atlantean");
	xUnitSelect(dFreeRelics, xUnitID);
	trUnitChangeProtoUnit("Relic");
	yFindLatestReverse("SFXUnit", "Titan Gate Dead", 0);
	DoRelicSFX(1*trQuestVarGet("SFXUnit"), type);
	xSetInt(dFreeRelics, xSFXID, 1*trQuestVarGet("SFXUnit"));
}

void NewRelic(int id = 0, int max = 0, int forcelevel = 0){
	int type = 0;
	float stat = 0;
	float level = 0;
	if(max == 0){
		max = RELIC_NUMBER;
	}
	if(forcelevel == 0){
		trQuestVarSetFromRand("temp", 1, ChickenLevel);
		level = 1*trQuestVarGet("temp");
	}
	else{
		level = forcelevel;
	}
	trQuestVarSetFromRand("type", 1, max);
	type = 1*trQuestVarGet("type");
	if(type == RELIC_ATTACK){
		trQuestVarSetFromRand("temp", 1, 3, true);
		if(level == 2){
			trQuestVarSetFromRand("temp", 4, 6, true);
		}
		if(level == 3){
			trQuestVarSetFromRand("temp", 7, 9, true);
		}
		if(level == 4){
			trQuestVarSetFromRand("temp", 10, 15, true);
		}
		if(level == 5){
			trQuestVarSetFromRand("temp", 16, 20, true);
		}
		if(level == 6){
			trQuestVarSetFromRand("temp", 21, 25, true);
		}
		if(level == 7){
			trQuestVarSetFromRand("temp", 26, 40, true);
		}
		
	}
	if(type == RELIC_HP){
		trQuestVarSetFromRand("temp", 3, 10, true);
		if(level == 2){
			trQuestVarSetFromRand("temp", 11, 20, true);
		}
		if(level == 3){
			trQuestVarSetFromRand("temp", 21, 30, true);
		}
		if(level == 4){
			trQuestVarSetFromRand("temp", 31, 50, true);
		}
		if(level == 5){
			trQuestVarSetFromRand("temp", 51, 65, true);
		}
		if(level == 6){
			trQuestVarSetFromRand("temp", 66, 80, true);
		}
		if(level == 7){
			trQuestVarSetFromRand("temp", 81, 100, true);
		}
		
		trQuestVarModify("temp", "*", 10);
	}
	if(type == RELIC_PROJ_SPEED){
		trQuestVarSet("temp", level);
		trQuestVarModify("temp", "*", 25);
	}
	if(type == RELIC_CHICKEN_SPEED){
		trQuestVarSet("temp", level);
	}
	if(type == RELIC_RANGE){
		trQuestVarSetFromRand("temp", 1, 2, true);
		if(level == 2){
			trQuestVarSetFromRand("temp", 3, 4, true);
		}
		if(level == 3){
			trQuestVarSetFromRand("temp", 5, 6, true);
		}
		if(level == 4){
			trQuestVarSetFromRand("temp", 7, 8, true);
		}
		if(level == 5){
			trQuestVarSetFromRand("temp", 9, 10, true);
		}
		if(level == 6){
			trQuestVarSetFromRand("temp", 11, 12, true);
		}
		if(level == 7){
			trQuestVarSetFromRand("temp", 13, 15, true);
		}
	}
	if(type == RELIC_TOWER){
		trQuestVarSetFromRand("temp", 1, 2, true);
		if(level == 2){
			trQuestVarSetFromRand("temp", 3, 5, true);
		}
		if(level == 3){
			trQuestVarSetFromRand("temp", 6, 8, true);
		}
		if(level == 4){
			trQuestVarSetFromRand("temp", 9, 14, true);
		}
		if(level == 5){
			trQuestVarSetFromRand("temp", 15, 17, true);
		}
		if(level == 6){
			trQuestVarSetFromRand("temp", 18, 20, true);
		}
		if(level == 7){
			trQuestVarSetFromRand("temp", 21, 25, true);
		}
	}
	if(type == RELIC_CHICKEN_HP){
		trQuestVarSetFromRand("temp", 1, 7, true);
		if(level == 2){
			trQuestVarSetFromRand("temp", 8, 11, true);
		}
		if(level == 3){
			trQuestVarSetFromRand("temp", 12, 15, true);
		}
		if(level == 4){
			trQuestVarSetFromRand("temp", 20, 30, true);
		}
		if(level == 5){
			trQuestVarSetFromRand("temp", 31, 41, true);
		}
		if(level == 6){
			trQuestVarSetFromRand("temp", 42, 50, true);
		}
		if(level == 7){
			trQuestVarSetFromRand("temp", 51, 66, true);
		}
		trQuestVarModify("temp", "*", 15);
	}
	if(type == RELIC_CHICKEN_HEAL){
		trQuestVarSetFromRand("temp", 1, 2, true);
		if(level == 2){
			trQuestVarSetFromRand("temp", 3, 4, true);
		}
		if(level == 3){
			trQuestVarSetFromRand("temp", 5, 7, true);
		}
		if(level == 4){
			trQuestVarSetFromRand("temp", 8, 10, true);
		}
		if(level == 5){
			trQuestVarSetFromRand("temp", 11, 12, true);
		}
		if(level == 6){
			trQuestVarSetFromRand("temp", 13, 15, true);
		}
		if(level == 7){
			trQuestVarSetFromRand("temp", 16, 20, true);
		}
	}
	if(type == RELIC_TOWER_HEAL){
		trQuestVarSetFromRand("temp", 1, 2, true);
		if(level == 2){
			trQuestVarSetFromRand("temp", 3, 4, true);
		}
		if(level == 3){
			trQuestVarSetFromRand("temp", 5, 7, true);
		}
		if(level == 4){
			trQuestVarSetFromRand("temp", 8, 10, true);
		}
		if(level == 5){
			trQuestVarSetFromRand("temp", 11, 13, true);
		}
		if(level == 6){
			trQuestVarSetFromRand("temp", 14, 18, true);
		}
		if(level == 7){
			trQuestVarSetFromRand("temp", 20, 30, true);
		}
	}
	stat = trQuestVarGet("temp");
	if(Difficulty >= 2){
		stat = stat*0.75;
	}
	xAddDatabaseBlock(dFreeRelics, true);
	xSetInt(dFreeRelics, xUnitID, id);
	xSetInt(dFreeRelics, xRelicType, type);
	xSetFloat(dFreeRelics, xRelicStat, stat);
	//?pointer
	xUnitSelect(dFreeRelics, xUnitID);
	trUnitChangeProtoUnit("Titan Atlantean");
	xUnitSelect(dFreeRelics, xUnitID);
	trUnitChangeProtoUnit("Relic");
	xUnitSelect(dFreeRelics, xUnitID);
	trSetScale(0.25*level+0.75);
	yFindLatestReverse("SFXUnit", "Titan Gate Dead", 0);
	DoRelicSFX(1*trQuestVarGet("SFXUnit"), type);
	xSetInt(dFreeRelics, xSFXID, 1*trQuestVarGet("SFXUnit"));
	xSetInt(dFreeRelics, xRelicLevel, level);
}

void FunctionRelic(bool apply = false, int p = 0){
	xSetPointer(dPlayerData, p);
	if(apply == true){
		if(xGetInt(dFreeRelics, xRelicType) == RELIC_ATTACK){
			trModifyProtounit("Tower", p, 31, 1*xGetFloat(dFreeRelics, xRelicStat));
			xSetInt(dPlayerData, xTowerDamage, xGetInt(dPlayerData, xTowerDamage)+1*xGetFloat(dFreeRelics, xRelicStat));
		}
		if(xGetInt(dFreeRelics, xRelicType) == RELIC_HP){
			trModifyProtounit("Tower", p, 0, 1*xGetFloat(dFreeRelics, xRelicStat));
		}
		if(xGetInt(dFreeRelics, xRelicType) == RELIC_PROJ_SPEED){
			xSetInt(dPlayerData, xLandmineDamage, xGetInt(dPlayerData, xLandmineDamage)+1*xGetFloat(dFreeRelics, xRelicStat));
		}
		if(xGetInt(dFreeRelics, xRelicType) == RELIC_CHICKEN_SPEED){
			trModifyProtounit(ChickenProto, p, 1, xGetFloat(dFreeRelics, xRelicStat));
		}
		if(xGetInt(dFreeRelics, xRelicType) == RELIC_RANGE){
			trModifyProtounit("Tower", p, 11, 1*xGetFloat(dFreeRelics, xRelicStat));
			trModifyProtounit("Tower", p, 2, 1*xGetFloat(dFreeRelics, xRelicStat));
		}
		if(xGetInt(dFreeRelics, xRelicType) == RELIC_TOWER){
			trModifyProtounit("Tower", p, 10, 1*xGetFloat(dFreeRelics, xRelicStat)+1);
		}
		if(xGetInt(dFreeRelics, xRelicType) == RELIC_CHICKEN_HP){
			trModifyProtounit(ChickenProto, p, 0, 1*xGetFloat(dFreeRelics, xRelicStat));
		}
		if(xGetInt(dFreeRelics, xRelicType) == RELIC_CHICKEN_HEAL){
			trQuestVarModify("P"+p+"ChickenRegen", "+", 1*xGetFloat(dFreeRelics, xRelicStat));
		}
		if(xGetInt(dFreeRelics, xRelicType) == RELIC_TOWER_HEAL){
			trQuestVarModify("P"+p+"TowerRegen", "+", 1*xGetFloat(dFreeRelics, xRelicStat));
		}
	}
	if(apply == false){
		//HELD RELICS FOR HERE
		if(xGetInt(dHeldRelics, xRelicType) == RELIC_ATTACK){
			trModifyProtounit("Tower", p, 31, -1*xGetFloat(dHeldRelics, xRelicStat));
			xSetInt(dPlayerData, xTowerDamage, xGetInt(dPlayerData, xTowerDamage)-1*xGetFloat(dHeldRelics, xRelicStat));
		}
		if(xGetInt(dHeldRelics, xRelicType) == RELIC_HP){
			trModifyProtounit("Tower", p, 0, (0-1*xGetFloat(dHeldRelics, xRelicStat)));
		}
		if(xGetInt(dHeldRelics, xRelicType) == RELIC_PROJ_SPEED){
			xSetInt(dPlayerData, xLandmineDamage, xGetInt(dPlayerData, xLandmineDamage)-1*xGetFloat(dHeldRelics, xRelicStat));
		}
		if(xGetInt(dHeldRelics, xRelicType) == RELIC_CHICKEN_SPEED){
			trModifyProtounit(ChickenProto, p, 1, (0-xGetFloat(dHeldRelics, xRelicStat)));
		}
		if(xGetInt(dHeldRelics, xRelicType) == RELIC_RANGE){
			trModifyProtounit("Tower", p, 11, -1*xGetFloat(dHeldRelics, xRelicStat));
			trModifyProtounit("Tower", p, 2, -1*xGetFloat(dHeldRelics, xRelicStat));
		}
		if(xGetInt(dHeldRelics, xRelicType) == RELIC_TOWER){
			trModifyProtounit("Tower", p, 10, -1*xGetFloat(dHeldRelics, xRelicStat)-1);
		}
		if(xGetInt(dHeldRelics, xRelicType) == RELIC_CHICKEN_HP){
			trModifyProtounit(ChickenProto, p, 0, -1*xGetFloat(dHeldRelics, xRelicStat));
		}
		if(xGetInt(dHeldRelics, xRelicType) == RELIC_CHICKEN_HEAL){
			trQuestVarModify("P"+p+"ChickenRegen", "-", 1*xGetFloat(dHeldRelics, xRelicStat));
		}
		if(xGetInt(dHeldRelics, xRelicType) == RELIC_TOWER_HEAL){
			trQuestVarModify("P"+p+"TowerRegen", "-", 1*xGetFloat(dHeldRelics, xRelicStat));
		}
		
	}
}

void R5Wave(int deploy = 1, string proto = "", int distancemmax = 1800, int distancemin = 1600){
	vector tempV = vector(0,0,0);
	int temp = 0;
	while(deploy > 0){
		trQuestVarSetFromRand("temp", 1, xGetDatabaseCount(dShore));
		xSetPointer(dShore, 1*trQuestVarGet("temp"));
		tempV = xGetVector(dShore, xShoreLoc);
		xSetInt(dShore, xShoreDist, distanceBetweenVectors(xGetVector(dShore, xShoreLoc), MapCentre, true));
		if((xGetInt(dShore, xShoreDist) < distancemmax) && (xGetInt(dShore, xShoreDist) > distancemin)){
			temp = trGetNextUnitScenarioNameNumber();
			UnitCreate(cNumberNonGaiaPlayers, proto, xsVectorGetX(tempV), xsVectorGetZ(tempV), 0);
			trUnitSelectClear();
			trUnitSelect(""+temp);
			deploy = deploy-1;
			xAddDatabaseBlock(dEnemies, true);
			xSetInt(dEnemies, xUnitID, temp);
			trUnitMoveToPoint(xsVectorGetX(MapCentre),1,xsVectorGetZ(MapCentre),-1,true);
		}
	}
}

void R5Chest(int deploy = 1, int distancemmax = 1800, int distancemin = 1600){
	vector tempV = vector(0,0,0);
	int temp = 0;
	while(deploy > 0){
		trQuestVarSetFromRand("temp", 1, xGetDatabaseCount(dShore));
		xSetPointer(dShore, 1*trQuestVarGet("temp"));
		tempV = xGetVector(dShore, xShoreLoc);
		xSetInt(dShore, xShoreDist, distanceBetweenVectors(xGetVector(dShore, xShoreLoc), MapCentre, true));
		if((xGetInt(dShore, xShoreDist) < distancemmax) && (xGetInt(dShore, xShoreDist) > distancemin)){
			CreateChest(xsVectorGetX(tempV)/2, xsVectorGetZ(tempV)/2, -1);
			deploy = deploy-1;
		}
	}
}
