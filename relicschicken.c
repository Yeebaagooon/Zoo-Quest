const int RELIC_NUMBER = 1;

const int RELIC_ATTACK = 1;

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
	}
	return(msg);
}

int relicProto(int relic = 0) {
	int proto = kbGetProtoUnitID("Hoplite");
	switch(relic)
	{
		case RELIC_ATTACK:
		{
			proto = kbGetProtoUnitID("Thor Hammer Head");
		}
	}
	return(proto);
}
