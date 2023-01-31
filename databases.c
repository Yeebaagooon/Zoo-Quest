int spysearch = 0;
int spyreset = 0;
int spyProto = 0;
int spyUnit = 1;
int spyDest = 2;
int spyScale = 3;
int spyActive = 4;
int spyAnim = 5;



int dSpyRequests = 0;
int xSpyRequestProto = 0;
int xSpyRequestDest = 0;
int xSpyRequestScale = 0;
int xSpyRequestAnim = 0;
int xSpyRequestEvent = 0;

int dBerryBush = 0;
int dLogs = 0;
int xUnitID = 0;
int xUnitPos = 0;

int dTiles1 = 0;
int xTileX = 0;
int xTileZ = 0;
int xTileNumber = 0;
int xTileType = 0;
int xTileSubType = 0;
int dTiles2 = 0;

rule initialise_spy_database
active
highFrequency
{
	xsDisableSelf();
	xsSetContextPlayer(0);
	dSpyRequests = xInitDatabase("spyRequests", 32);
	xSpyRequestProto = xInitAddInt(dSpyRequests, "proto");
	xSpyRequestAnim = xInitAddInt(dSpyRequests, "anim");
	xSpyRequestScale = xInitAddVector(dSpyRequests, "scale");
	xSpyRequestDest = xInitAddVector(dSpyRequests, "dest");
	xSpyRequestEvent = xInitAddInt(dSpyRequests, "event");
	
	dBerryBush = xInitDatabase("Berries");
	xUnitID = xInitAddInt(dBerryBush, "unit id");
	xUnitPos = xInitAddVector(dBerryBush, "pos");
	
	dLogs = xInitDatabase("Logs");
	xUnitID = xInitAddInt(dLogs, "unit id");
	xUnitPos = xInitAddVector(dLogs, "pos");
	
	dTiles1 = xInitDatabase("Tileset");
	xTileX = xInitAddInt(dTiles1, "tx", 0);
	xTileZ = xInitAddInt(dTiles1, "tz", 0);
	xTileNumber = xInitAddInt(dTiles1, "number", 0);
	xTileType = xInitAddInt(dTiles1, "ttype", 0);
	xTileSubType = xInitAddInt(dTiles1, "tsubtype", 0);
	
	dTiles2 = xInitDatabase("Tileset two");
	xTileX = xInitAddInt(dTiles2, "tx", 0);
	xTileZ = xInitAddInt(dTiles2, "tz", 0);
	xTileNumber = xInitAddInt(dTiles2, "number", 0);
	xTileType = xInitAddInt(dTiles2, "ttype", 0);
	xTileSubType = xInitAddInt(dTiles2, "tsubtype", 0);
}

/*
Assumes that the target unit is already selected
*/
void spyEffect(int proto = 0, int anim = 0, vector dest = vector(0,0,0), vector scale = vector(1,1,1), int event = -1) {
	int newest = xAddDatabaseBlock(dSpyRequests);
	xSetInt(dSpyRequests, xSpyRequestProto, proto, newest);
	xSetInt(dSpyRequests, xSpyRequestAnim, anim, newest);
	xSetVector(dSpyRequests, xSpyRequestDest, dest, newest);
	xSetVector(dSpyRequests, xSpyRequestScale, scale, newest);
	xSetInt(dSpyRequests, xSpyRequestEvent, event, newest);
	trTechInvokeGodPower(0, "spy", vector(0,0,0), vector(0,0,0));
}
