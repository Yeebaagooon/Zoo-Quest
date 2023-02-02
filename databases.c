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

int dPoachers = 0;
int dMissiles = 0;
int xOwner = 0;
int xMissilePos = 0;
int xMissileDir = 0;
int xMissileCentre = 0;
int xMissilePrev = 0;

int dDots = 0;
int xPercent = 0;



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
	
	dPoachers = xInitDatabase("Poachers");
	xUnitID = xInitAddInt(dPoachers, "unit id");
	
	dMissiles = xInitDatabase("Missiles DB");
	xUnitID = xInitAddInt(dMissiles, "missile unit id", -1);
	xOwner = xInitAddInt(dMissiles, "missile owner", 0);
	xMissilePos = xInitAddVector(dMissiles, "position", vector(0,0,0));
	xMissileDir = xInitAddVector(dMissiles, "direction", vector(0,0,0));
	xMissileCentre = xInitAddVector(dMissiles, "centre", vector(0,0,0));
	xMissilePrev = xInitAddVector(dMissiles, "prev", vector(0,0,0));
	
	dDots = xInitDatabase("Dot DB");
	xUnitID = xInitAddInt(dDots, "unit id", 0);
	xPercent = xInitAddInt(dDots, "per", 0);
	
	MapCentre = xsVectorSet(252/2-1,0,252/2-1);
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

bool rayCollision(vector start = vector(0,0,0), vector dir = vector(1,0,0),
	float dist = 0, float width = 0) {
	if(xGetBool (dPlayerData, xPlayerActive)){
		vector pos = kbGetBlockPosition(""+xGetInt(dPlayerData,xPlayerUnitID),true);
		float current = distanceBetweenVectors(pos, start, false);
		if (current < dist) {
			vector hitbox = start + dir * current;
			if (distanceBetweenVectors(pos, hitbox, true) <= width) {
				//Next line allows jumping over missiles
				if(trPlayerUnitCountSpecific(xGetPointer(dPlayerData), ""+GazelleProto) == 1){
					return(true);
				}
			}
		}
	}
	return(false);
}

void DoMissile(){
	xDatabaseNext(dMissiles);
	vector pos = vector(0,0,0);
	vector dir = vector(0,0,0);
	vector prev = vector(0,0,0);
	prev = xGetVector(dMissiles, xMissilePrev); //when created this is the same as xMissilePos
	bool hit = false;
	int playerhit = 0;
	int boomID = 0;
	pos = kbGetBlockPosition(""+xGetInt(dMissiles, xUnitID));
	dir = xGetVector(dMissiles, xMissileDir); //Normalized direction when missile created and target locked
	xSetVector(dMissiles, xMissilePos, pos);
	xSetPointer(dPlayerData, xGetInt(dMissiles, xOwner));
	float dist = distanceBetweenVectors(pos, prev, false);
	for(x=1; < cNumberNonGaiaPlayers) {
		xDatabaseNext(dPlayerData);
		//2 is raw dist, 4 is squared
		if(rayCollision(prev,dir,dist+2,2)){
			hit = true;
			playerhit = xGetPointer(dPlayerData);
			break;
		}
	}
	if(hit){
		//hit effect
		xUnitSelect(dMissiles, xUnitID);
		trUnitDestroy();
		boomID = trGetNextUnitScenarioNameNumber();
		UnitCreate(0, "Cinematic Block", xsVectorGetX(pos), xsVectorGetZ(pos), 0);
		trUnitSelectClear();
		trUnitSelect(""+boomID);
		trUnitChangeProtoUnit("Blood Cinematic");
		playSound("leviathangrunt2.wav");
		trUnitSelectClear();
		xSetPointer(dPlayerData, playerhit);
		xUnitSelect(dPlayerData, xPlayerUnitID);
		trDamageUnit(1);
		//FREE DB LAST
		xFreeDatabaseBlock(dMissiles);
		//debugLog("Hits P " + playerhit);
	}
	else{
		xSetVector(dMissiles, xMissilePrev, pos);
		if((xsVectorGetX(pos) < 0) || (xsVectorGetX(pos) > 252) || (xsVectorGetZ(pos) < 0) || (xsVectorGetZ(pos) > 252)){
			//remove map outside
			xUnitSelect(dMissiles, xUnitID);
			trUnitDestroy();
			xFreeDatabaseBlock(dMissiles);
		}
	}
}

