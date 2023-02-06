rule ysearch
inactive
highFrequency
{
	int id = 0;
	int unittype = 0;
	int temp = 0;
	int closest = 0;
	int closestid = 0;
	vector scale = vector(0,0,0);
	vector dest = vector(0,0,0);
	vector dist = vector(0,0,0);
	vector closevector = vector(0,0,0);
	vector target = vector(0,0,0);
	for(i = spysearch; < trGetNextUnitScenarioNameNumber()) {
		id = kbGetBlockID(""+i, true);
		unittype = kbGetUnitBaseTypeID(id);
		switch(unittype)
		{
			case kbGetProtoUnitID("Spy Eye"):
			{
				if (xGetDatabaseCount(dSpyRequests) > 0) {
					scale = xGetVector(dSpyRequests, xSpyRequestScale);
					dest = xGetVector(dSpyRequests, xSpyRequestDest);
					trUnitSelectClear();
					trUnitSelectByID(id);
					trMutateSelected(xGetInt(dSpyRequests, xSpyRequestProto));
					trSetSelectedScale(xsVectorGetX(scale),xsVectorGetY(scale),xsVectorGetZ(scale));
					trUnitOverrideAnimation(xGetInt(dSpyRequests, xSpyRequestAnim),0,true,false,-1);
					trEventFire(xGetInt(dSpyRequests, xSpyRequestEvent));
					if (aiPlanSetUserVariableInt(1*xsVectorGetX(dest),1*xsVectorGetY(dest),1*xsVectorGetZ(dest),i) == false) {
						debugLog("spy error N/A: " + 1*xsVectorGetX(dest) + "," + 1*xsVectorGetY(dest) + "," + 1*xsVectorGetZ(dest));
					}
					xFreeDatabaseBlock(dSpyRequests);
					spyreset = 0;
				} else {
					debugLog("Spy Buffer is empty");
				}
				break;
			}
			case kbGetProtoUnitID("House"):
			{
				// [DEBUG] trPlayerGrantResources(kbUnitGetOwner(id), "Gold", 1);
				trUnitSelectClear();
				trUnitSelectByID(id);
				trUnitDestroy();
				break;
			}
			case kbGetProtoUnitID("Granary"):
			{
				trPlayerGrantResources(kbUnitGetOwner(id), "Wood", 1);
				trUnitSelectClear();
				trUnitSelectByID(id);
				trUnitDestroy();
				break;
			}
			case kbGetProtoUnitID("Fence Wood"):
			{
				//Stage 2 destroy fences underwater (-1.5)
				if(xsVectorGetY(kbGetBlockPosition(""+trGetUnitScenarioNameNumber(id))) < -1.6){
					trUnitSelectClear();
					trUnitSelectByID(id);
					trUnitChangeProtoUnit("Cinematic Block");
				}
			}
			case kbGetProtoUnitID("Axe"):
			{
				//axe
				vector axevector = vector(0,0,0);
				axevector = kbGetBlockPosition(""+i);
				trUnitSelectClear();
				trUnitSelectByID(id);
				trUnitDestroy();
				dist = vector(0,0,0);
				closevector = vector(0,0,0);
				target = vector(0,0,0);
				closest = 10000;
				closestid = 0;
				//cycle through all throwing axemen to find the closest
				for(a=0 ; < xGetDatabaseCount(dPoachers)){
					xDatabaseNext(dPoachers);
					dist = kbGetBlockPosition(""+xGetInt(dPoachers, xUnitID));
					if(distanceBetweenVectors(dist, axevector, true) < closest){
						closest = distanceBetweenVectors(dist, axevector, true);
						closestid = xGetInt(dPoachers, xUnitID);
					}
				}
				closevector = kbGetBlockPosition(""+closestid);
				xsSetContextPlayer(cNumberNonGaiaPlayers);
				dest = kbGetBlockPosition(""+trGetUnitScenarioNameNumber(kbUnitGetTargetUnitID(kbGetBlockID(""+closestid))));
				xsSetContextPlayer(0);
				dist = xsVectorNormalize(dest-closevector);
				temp = trGetNextUnitScenarioNameNumber();
				UnitCreate(cNumberNonGaiaPlayers, "Lampades Bolt",xsVectorGetX(closevector),xsVectorGetZ(closevector),0);
				dist = vectorSetAsTargetVector(closevector,dist,60.0);
				trUnitSelectClear();
				trUnitSelect(""+temp);
				trUnitMoveToPoint(xsVectorGetX(dist),0,xsVectorGetZ(dist),-1,false);
				xAddDatabaseBlock(dMissiles, true);
				xSetInt(dMissiles, xUnitID, temp);
				xSetInt(dMissiles, xOwner, cNumberNonGaiaPlayers);
				xSetVector(dMissiles, xMissilePos, closevector);
				xSetVector(dMissiles, xMissilePrev, closevector);
				xSetVector(dMissiles, xMissileDir, xsVectorNormalize(dist));
				xAddDatabaseBlock(dDestroyMe, true);
				xSetInt(dDestroyMe, xUnitID, temp);
				xSetInt(dDestroyMe, xDestroyTime, trTimeMS()+10000);
			}
			case kbGetProtoUnitID("Sling Stone"):
			{
				//axe
				vector slingvector = vector(0,0,0);
				slingvector = kbGetBlockPosition(""+i);
				trUnitSelectClear();
				trUnitSelectByID(id);
				trUnitDestroy();
				dist = vector(0,0,0);
				closevector = vector(0,0,0);
				target = vector(0,0,0);
				closest = 10000;
				closestid = 0;
				//cycle through all poachers to find the closest
				for(a=0 ; < xGetDatabaseCount(dPoachers)){
					xDatabaseNext(dPoachers);
					dist = kbGetBlockPosition(""+xGetInt(dPoachers, xUnitID));
					if(distanceBetweenVectors(dist, slingvector, true) < closest){
						closest = distanceBetweenVectors(dist, slingvector, true);
						closestid = xGetInt(dPoachers, xUnitID);
					}
				}
				closevector = kbGetBlockPosition(""+closestid);
				xsSetContextPlayer(cNumberNonGaiaPlayers);
				dest = kbGetBlockPosition(""+trGetUnitScenarioNameNumber(kbUnitGetTargetUnitID(kbGetBlockID(""+closestid))));
				xsSetContextPlayer(0);
				dist = xsVectorNormalize(dest-closevector);
				temp = trGetNextUnitScenarioNameNumber();
				UnitCreate(cNumberNonGaiaPlayers, "Javelin Flaming", xsVectorGetX(closevector),xsVectorGetZ(closevector),0);
				dist = vectorSetAsTargetVector(closevector,dist,60.0);
				trUnitSelectClear();
				trUnitSelect(""+temp);
				trUnitMoveToPoint(xsVectorGetX(dist),0,xsVectorGetZ(dist),-1,false);
				xAddDatabaseBlock(dMissiles, true);
				xSetInt(dMissiles, xUnitID, temp);
				xSetInt(dMissiles, xOwner, cNumberNonGaiaPlayers);
				xSetVector(dMissiles, xMissilePos, closevector);
				xSetVector(dMissiles, xMissilePrev, closevector);
				xSetVector(dMissiles, xMissileDir, xsVectorNormalize(dist));
				xAddDatabaseBlock(dDestroyMe, true);
				xSetInt(dDestroyMe, xUnitID, temp);
				xSetInt(dDestroyMe, xDestroyTime, trTimeMS()+10000);
			}
			case kbGetProtoUnitID("Hero Birth"):
			{
				debugLog("spysearch: " + i);
			}
		}
	}
	if (xGetDatabaseCount(dSpyRequests) > 0) {
		spyreset = spyreset + 1;
		if (spyreset >= 10) {
			debugLog("Spy reset. Failed requests: " + xGetDatabaseCount(dSpyRequests));
			xClearDatabase(dSpyRequests);
			spyreset = 0;
		}
	}
	spysearch = trGetNextUnitScenarioNameNumber();
}
