const int RELIC_NUMBER = 9;

const int RELIC_ATTACK = 1;
const int RELIC_HP = 2;
const int RELIC_PROJ_SPEED = 3;
const int RELIC_CHICKEN_SPEED = 4;
const int RELIC_RANGE = 5;
const int RELIC_TOWER = 6;
const int RELIC_CHICKEN_HP = 7;
const int RELIC_CHICKEN_HEAL = 8;
const int RELIC_TOWER_HEAL = 9;

//cone proj, armoury, allow cliff

string relicName(int relicid = 0) {
	string msg = "WTF That's not a relic!";
	int relic = 0;
	float stat = 0;
	for(a = xGetDatabaseCount(dFreeRelics); > 0){
		xDatabaseNext(dFreeRelics);
		if(xGetInt(dFreeRelics, xUnitID) == relicid){
			relic = xGetInt(dFreeRelics, xRelicType);
			stat = xGetFloat(dFreeRelics, xRelicStat);
			continue;
		}
	}
	for(a = xGetDatabaseCount(dHeldRelics); > 0){
		xDatabaseNext(dHeldRelics);
		if(xGetInt(dHeldRelics, xUnitID) == relicid){
			relic = xGetInt(dHeldRelics, xRelicType);
			stat = xGetFloat(dHeldRelics, xRelicStat);
			continue;
		}
	}
	switch(relic)
	{
		case RELIC_ATTACK:
		{
			msg = "+ " + 1*stat + " attack";
		}
		case RELIC_HP:
		{
			msg = "+ " + 1*stat + " tower HP";
		}
		case RELIC_PROJ_SPEED:
		{
			msg = "+ " + 1*stat + " landmine damage";
		}
		case RELIC_CHICKEN_SPEED:
		{
			msg = "+ " + 1*stat + " chicken speed";
		}
		case RELIC_RANGE:
		{
			msg = "+ " + 1*stat + " tower range";
		}
		case RELIC_TOWER:
		{
			msg = "+ " + 1*stat + " tower limit";
		}
		case RELIC_CHICKEN_HP:
		{
			msg = "+ " + 1*stat + " chicken HP";
		}
		case RELIC_CHICKEN_HEAL:
		{
			msg = "+ " + 1*stat + " chicken heal per second";
		}
		case RELIC_TOWER_HEAL:
		{
			msg = "+ " + 1*stat + " tower heal per second";
		}
	}
	return(msg);
}

int relicProto(int relic = 0) {
	int proto = kbGetProtoUnitID("Hoplite");
	switch(relic)
	{
		case RELIC_ATTACK:
		{
			proto = kbGetProtoUnitID("Ballista");
		}
		case RELIC_HP:
		{
			proto = kbGetProtoUnitID("Wall Connector");
		}
		case RELIC_PROJ_SPEED:
		{
			proto = kbGetProtoUnitID("Fire Giant");
		}
		case RELIC_CHICKEN_SPEED:
		{
			proto = kbGetProtoUnitID("Pegasus");
		}
		case RELIC_RANGE:
		{
			proto = kbGetProtoUnitID("Crossbowman");
		}
		case RELIC_TOWER:
		{
			proto = kbGetProtoUnitID("Tower");
		}
		case RELIC_CHICKEN_HP:
		{
			proto = kbGetProtoUnitID("Chicken Exploding");
		}
		case RELIC_CHICKEN_HEAL:
		{
			proto = kbGetProtoUnitID("Valkyrie");
		}
		case RELIC_TOWER_HEAL:
		{
			proto = kbGetProtoUnitID("Physician");
		}
	}
	return(proto);
}
