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
			actnamed = "Act II - Unknown";
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
			animaliconact = "Act II - Not yet made";
		}
	}
	return(animaliconact);
}

void SpawnDeerPoacher(int num = 0){
	int temp = 0;
	for(n=num ; > 0){
		temp = trGetNextUnitScenarioNameNumber();
		trQuestVarSetFromRand("x",0,252);
		trQuestVarSetFromRand("z",0,252);
		UnitCreate(cNumberNonGaiaPlayers, "Throwing Axeman", 1*trQuestVarGet("x"), 1*trQuestVarGet("z"), 0);
		xAddDatabaseBlock(dPoachers, true);
		xSetInt(dPoachers, xUnitID, temp);
		xSetInt(dPoachers, xMoveTime, 0);
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
