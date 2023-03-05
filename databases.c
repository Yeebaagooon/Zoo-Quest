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
int xPoacherType = 0;
int xMoveTime = 0;
int dMissiles = 0;
int xOwner = 0;
int xMissilePos = 0;
int xMissileDir = 0;
int xMissileCentre = 0;
int xMissilePrev = 0;
int xMissileDmg = 0;
int xMissileTime = 0;

int dDots = 0;
int xPercent = 0;

int dChests = 0;
int xKeyType = 0;
int xUnlockUnitID = 0;

int dKeys = 0;
int xKeySFXID = 0;

int dTemp = 0;
int xExtra = 0;

int dFences = 0;
int xSegment = 0;

int dIncomingMissiles = 0;
int xMissileDest = 0;
int xMissileSpyID = 0;
int xMissileSpyOfSpyID = 0;
int xMissileProto = 0;
int xMissileCarProto = 0;
int xMissileAnim = 0;
int SpyDone = 0;
int xIMissileDmg = 0;
int xIMissileTime = 0;

int dInterractables = 0;
int xType = 0;
int xSubtype = 0;
int xSquare1 = 0;
int xSquare2 = 0;

int dEdibles = 0;
int xTime1 = 0;
int xTime2 = 0;

int dShore = 0;
int xShoreLoc = 0;

int dDirtA = 0;
int xDirtLoc = 0;

int dRiver = 0;
int xRiverLoc = 0;

int dHelp = 0;
int xSubID = 0;

int dRelics = 0;

int dShop = 0;
int xPower = 0;
int xPowerName = 0;
int xDecorationID = 0;
int xCost = 0;

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
	xMoveTime = xInitAddInt(dPoachers, "time", 0);
	xPoacherType = xInitAddString(dPoachers, "protoid", "Throwing Axeman");
	
	dMissiles = xInitDatabase("Missiles DB");
	xUnitID = xInitAddInt(dMissiles, "missile unit id", -1);
	xOwner = xInitAddInt(dMissiles, "missile owner", 0);
	xMissilePos = xInitAddVector(dMissiles, "position", vector(0,0,0));
	xMissileDir = xInitAddVector(dMissiles, "direction", vector(0,0,0));
	xMissilePrev = xInitAddVector(dMissiles, "prev", vector(0,0,0));
	xMissileDmg = xInitAddInt(dMissiles, "dmg", 1);
	xMissileTime = xInitAddInt(dMissiles, "time", 10000);
	
	dIncomingMissiles = xInitDatabase("Incoming DB");
	xUnitID = xInitAddInt(dIncomingMissiles, "missile unit id", -1);
	xOwner = xInitAddInt(dIncomingMissiles, "missile owner", cNumberNonGaiaPlayers);
	xMissilePos = xInitAddVector(dIncomingMissiles, "position", vector(0,0,0));
	xMissileDir = xInitAddVector(dIncomingMissiles, "direction", vector(0,0,0));
	xMissileSpyID = xInitAddInt(dIncomingMissiles, "spy name", -1);
	xMissileSpyOfSpyID = xInitAddInt(dIncomingMissiles, "spy of spy", -1);
	xMissileProto = xInitAddInt(dIncomingMissiles, "proto id", -1);
	xMissileCarProto = xInitAddInt(dIncomingMissiles, "car id", -1);
	xMissileAnim = xInitAddInt(dIncomingMissiles, "anim", 0);
	SpyDone = xInitAddBool(dIncomingMissiles, "spy done", false);
	xIMissileDmg = xInitAddInt(dIncomingMissiles, "dmg", 1);
	xIMissileTime = xInitAddInt(dIncomingMissiles, "time", 10000);
	
	dDots = xInitDatabase("Dot DB");
	xUnitID = xInitAddInt(dDots, "unit id", 0);
	xPercent = xInitAddInt(dDots, "per", 0);
	
	dChests = xInitDatabase("chest DB");
	xUnitID = xInitAddInt(dChests, "unit id", 0);
	xKeyType = xInitAddInt(dChests, "key type", 0);
	xUnlockUnitID = xInitAddInt(dChests, "unlock unit id", 0);
	
	dKeys = xInitDatabase("key DB");
	xUnitID = xInitAddInt(dKeys, "unit id", 0);
	xKeyType = xInitAddInt(dKeys, "key type", 0);
	xKeySFXID = xInitAddInt(dKeys, "sfx id", 0);
	
	dTemp = xInitDatabase("tempdb");
	xUnitID = xInitAddInt(dTemp, "id", 0);
	xExtra = xInitAddInt(dTemp, "extra param", 0);
	
	dFences = xInitDatabase("fencedb");
	xUnitID = xInitAddInt(dFences, "id", -1);
	xSegment = xInitAddInt(dFences, "segment", 0);
	
	MapCentre = xsVectorSet(252/2-1,0,252/2-1);
	
	dInterractables = xInitDatabase("interractables");
	xUnitID = xInitAddInt(dInterractables, "desc", 0);
	xType = xInitAddInt(dInterractables, "desc", 0);
	xSubtype = xInitAddInt(dInterractables, "desc", 0);
	xSquare1 = xInitAddInt(dInterractables, "sq1", 0);
	xSquare2 = xInitAddInt(dInterractables, "sq2", 0);
	
	dEdibles = xInitDatabase("edibles");
	xUnitID = xInitAddInt(dEdibles, "id", 0);
	xType = xInitAddInt(dEdibles, "desc", 0);
	xSubtype = xInitAddInt(dEdibles, "desc", 0);
	xTime1 = xInitAddInt(dEdibles, "desc", 0);
	xTime2 = xInitAddInt(dEdibles, "desc", 0);
	
	dShore = xInitDatabase("dShore");
	xShoreLoc = xInitAddVector(dShore, "loc", vector(0,0,0));
	
	dDirtA = xInitDatabase("dirta");
	xDirtLoc = xInitAddVector(dDirtA, "loc", vector(0,0,0));
	
	dRiver = xInitDatabase("river");
	xRiverLoc = xInitAddVector(dRiver, "loc", vector(0,0,0));
	
	dHelp = xInitDatabase("Helpers DB");
	xUnitID = xInitAddInt(dHelp, "unit id", -1);
	xSubID = xInitAddInt(dHelp, "sub type", -1);
	
	dRelics = xInitDatabase("Relics DB");
	xUnitID = xInitAddInt(dRelics, "unit id", -1);
	xSubID = xInitAddInt(dRelics, "sub type", -1);
	
	dShop = xInitDatabase("Shop");
	xUnitID = xInitAddInt(dShop, "shop", 0);
	xPower = xInitAddString(dShop, "shop", "power");
	xPowerName = xInitAddString(dShop, "shop", "power");
	xDecorationID = xInitAddInt(dShop, "shop", 0);
	xCost = xInitAddInt(dShop, "shop", 0);
	
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
			if(xGetBool(dPlayerData, xStopDeath) == false){
				if (distanceBetweenVectors(pos, hitbox, true) <= width) {
					if(trPlayerUnitCountSpecific(xGetPointer(dPlayerData), ""+GazelleProto) == 1){
						return(true);
					}
					if((trPlayerUnitCountSpecific(xGetPointer(dPlayerData), ""+RhinoProto) == 1) || (trPlayerUnitCountSpecific(xGetPointer(dPlayerData), ""+RhinoDrinkProto) == 1)){
						return(true);
					}
					if(trPlayerUnitCountSpecific(xGetPointer(dPlayerData), ""+GoatProto) == 1){
						return(true);
					}
					if(trPlayerUnitCountSpecific(xGetPointer(dPlayerData), ""+CrocProto) == 1){
						return(true);
					}
					if(trPlayerUnitCountSpecific(xGetPointer(dPlayerData), "Petsuchos") == 1){
						return(true);
					}
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
		if(Stage == 1){
			if(rayCollision(prev,dir,dist+2,2)){
				hit = true;
				playerhit = xGetPointer(dPlayerData);
				break;
			}
		}
		if(Stage == 2){
			if(rayCollision(prev,dir,dist+2,4)){
				hit = true;
				playerhit = xGetPointer(dPlayerData);
				break;
			}
		}
		if(Stage == 3){
			if(rayCollision(prev,dir,dist+2,2)){
				hit = true;
				playerhit = xGetPointer(dPlayerData);
				break;
			}
		}
		if(Stage == 4){
			if(rayCollision(prev,dir,dist+2,4)){
				hit = true;
				playerhit = xGetPointer(dPlayerData);
				break;
			}
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
		if(Stage == 1){
			trUnitChangeProtoUnit("Blood Cinematic");
			if(trCurrentPlayer() == playerhit){
				playSound("leviathangrunt2.wav");
			}
			trUnitSelectClear();
			xSetPointer(dPlayerData, playerhit);
			xUnitSelect(dPlayerData, xPlayerUnitID);
			trDamageUnit(1);
		}
		if(Stage == 2){
			trUnitChangeProtoUnit("Blood Cinematic");
			if(trCurrentPlayer() == playerhit){
				playSound("rhinogrunt" + (1*iModulo(2,trTime())+1) + ".wav");
			}
			trUnitSelectClear();
			xSetPointer(dPlayerData, playerhit);
			xUnitSelect(dPlayerData, xPlayerUnitID);
			trDamageUnit(2);
		}
		if(Stage == 3){
			trUnitChangeProtoUnit("Blood Cinematic");
			if(trCurrentPlayer() == playerhit){
				playSound("goatselect.wav");
			}
			trUnitSelectClear();
			xSetPointer(dPlayerData, playerhit);
			xUnitSelect(dPlayerData, xPlayerUnitID);
			trDamageUnit(1);
		}
		if(Stage == 4){
			trUnitChangeProtoUnit("Blood Cinematic");
			if(trCurrentPlayer() == playerhit){
				playSound("crocodilegrunt" + (1*iModulo(2,trTime())+1) + ".wav");
			}
			trUnitSelectClear();
			xSetPointer(dPlayerData, playerhit);
			xUnitSelect(dPlayerData, xPlayerUnitID);
			trDamageUnit(xGetInt(dMissiles, xMissileDmg));
		}
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

