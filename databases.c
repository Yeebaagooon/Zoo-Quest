int dDestroyMe = 0;
int xDestroyName = 0;
int xDestroyTime = 0;

int spysearch = 0;
int spyreset = 0;
int spyProto = 0;
int spyUnit = 1;
int spyDest = 2;
int spyScale = 3;
int spyActive = 4;
int spyAnim = 5;

/*DB HELP
dPlayerData = xInitDatabase("playerData");
xDrillPower = xInitAddInt(dPlayerData, "drillpower", 10);
xHullHP = xInitAddInt(dPlayerData, "hullhp", 1000);
xsEnableRule("fill_database");


rule fill_database
inactive
highFrequency

for(p=1; < cNumberNonGaiaPlayers) {
	xAddDatabaseBlock(dPlayerData);
}
//This sets up basic stats for all players
xSetPointer(dPlayerData, 1);
xSetInt(dPlayerData, xDrillPower, 10);
//Sets the drill power for that player (1)
xsDisableSelf();

xSetPointer(dPlayerData, 1);
xGetInt(dPlayerData, xDrillPower)
//Retrieves the drill power for that player (1)

*/




rule initialise_spy_database
active
highFrequency
{
	xsDisableSelf();
	xsSetContextPlayer(0);
	modularCounterInit("spyFind", 63);
	modularCounterInit("spyFound", 63);
	spyProto = zNewArray(mInt,64,"spyProto");
	spyUnit = zNewArray(mInt,64,"spyUnit");
	spyDest = zNewArray(mVector,64,"spyDest");
	spyScale = zNewArray(mVector,64,"spyScale");
	spyActive = zNewArray(mBool,64,"spyActive");
	spyAnim = zNewArray(mInt,64,"spyAnim");
}

void spyEffect(int unit = 0, int proto = 0, vector dest = vector(0,0,0), vector scale = vector(1,1,1), int anim = 0) {
	if (peekModularCounterNext("spyFind") != trQuestVarGet("spyFound")) {
		trUnitSelectClear();
		trUnitSelect(""+unit, true);
		if (trUnitAlive()) {
			int x = modularCounterNext("spyFind");
			aiPlanSetUserVariableInt(ARRAYS,spyProto,x,proto);
			aiPlanSetUserVariableInt(ARRAYS,spyUnit,x,unit);
			aiPlanSetUserVariableBool(ARRAYS,spyActive,x,true);
			aiPlanSetUserVariableVector(ARRAYS,spyDest,x,dest);
			aiPlanSetUserVariableVector(ARRAYS,spyScale,x,scale);
			aiPlanSetUserVariableInt(ARRAYS,spyAnim,x,anim);
			trBlockAllSounds();
			trTechInvokeGodPower(0, "spy", vector(0,0,0), vector(0,0,0));
			trUnblockAllSounds();
		}
	} else {
		debugLog("Spy buffer overflow");
	}
}

rule spy_find
active
highFrequency
{
	int x = 0;
	int id = 0;
	vector scale = vector(0,0,0);
	vector dest = vector(0,0,0);
	while(spysearch < trGetNextUnitScenarioNameNumber()) {
		id = kbGetBlockID(""+spysearch, true);
		if (kbGetUnitBaseTypeID(id) == kbGetProtoUnitID("Spy Eye")) {
			x = modularCounterNext("spyfound");
			if (aiPlanGetUserVariableBool(ARRAYS,spyActive,x)) {
				spyreset = 0;
				aiPlanSetUserVariableBool(ARRAYS,spyActive,x,false);
				trUnitSelectClear();
				trUnitSelect(""+aiPlanGetUserVariableInt(ARRAYS,spyUnit,x),true);
				dest = aiPlanGetUserVariableVector(ARRAYS,spyDest,x);
				if (trUnitAlive() == false) {
					if (aiPlanSetUserVariableInt(1*xsVectorGetX(dest),1*xsVectorGetY(dest),1*xsVectorGetZ(dest),-1) == false) {
						debugLog("spy error dead: " + 1*xsVectorGetX(dest) + "," + 1*xsVectorGetY(dest) + "," + 1*xsVectorGetZ(dest));
					}
				} else {
					trUnitSelectClear();
					trUnitSelectByID(id);
					trMutateSelected(aiPlanGetUserVariableInt(ARRAYS,spyProto,x));
					scale = aiPlanGetUserVariableVector(ARRAYS,spyScale,x);
					trSetSelectedScale(xsVectorGetX(scale),xsVectorGetY(scale),xsVectorGetZ(scale));
					trUnitSelectClear();
					trUnitSelectByID(id);
					int anim = aiPlanGetUserVariableInt(ARRAYS,spyAnim,x);
					if(anim != 0){
						trUnitOverrideAnimation(anim, 0, false, false, -1, 0);
					}
					if (aiPlanSetUserVariableInt(1*xsVectorGetX(dest),1*xsVectorGetY(dest),1*xsVectorGetZ(dest),spysearch) == false) {
						/*trUnitSelectClear();
						xAddDatabaseBlock(dDestroyMe, true);
						xSetInt(dDestroyMe, xDestroyName, id);
						xSetInt(dDestroyMe, xDestroyTime, trTimeMS()+5000);
						debugLog("Added to destroy DB");*/
					}
				}
			}
		}
		spysearch = 1 + spysearch;
	}
	if (trQuestVarGet("spyfind") != trQuestVarGet("spyfound")) {
		spyreset = 1 + spyreset;
		if (spyreset >= 5) {
			while (trQuestVarGet("spyfind") != trQuestVarGet("spyfound")) {
				x = modularCounterNext("spyFound");
				if (aiPlanGetUserVariableBool(ARRAYS,spyActive,x)) {
					aiPlanSetUserVariableBool(ARRAYS,spyActive,x,false);
					aiPlanSetUserVariableInt(xsVectorGetX(dest),xsVectorGetY(dest),xsVectorGetZ(dest),-1);
				}
			}
			debugLog("resetting spyfound");
		}
	} else {
		spyreset = 0;
	}
}
