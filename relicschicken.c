const int RELIC_NUMBER = 6;

const int RELIC_ATTACK = 1;
const int RELIC_HP = 2;
const int RELIC_PROJ_SPEED = 3;
const int RELIC_CHICKEN_SPEED = 4;
const int RELIC_RANGE = 5;
const int RELIC_TOWER = 6;


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
			msg = "+ " + 1*stat + " Attack";
		}
		case RELIC_HP:
		{
			msg = "+ " + 1*stat + " Tower HP";
		}
		case RELIC_PROJ_SPEED:
		{
			msg = "+ " + stat + " projectile speed";
		}
		case RELIC_CHICKEN_SPEED:
		{
			msg = "+ " + stat + " chicken speed";
		}
		case RELIC_RANGE:
		{
			msg = "+ " + 1*stat + " tower range";
		}
		case RELIC_TOWER:
		{
			msg = "+ " + 1*stat + " tower limit";
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
			proto = kbGetProtoUnitID("Phoenix From Egg");
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
	}
	return(proto);
}
