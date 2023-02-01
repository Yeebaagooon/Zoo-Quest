rule ysearch
inactive
highFrequency
{
	int id = 0;
	int unittype = 0;
	int temp = 0;
	vector scale = vector(0,0,0);
	vector dest = vector(0,0,0);
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
				trUnitSelectClear();
				trUnitSelectByID(id);
				trUnitDestroy();
				break;
			}
			case kbGetProtoUnitID("Axe"):
			{
				//axe
				vector axevector = vector(0,0,0);
				axevector = kbGetBlockPosition(""+i);
				trUnitSelectClear();
				trUnitSelectByID(id);
				trUnitDestroy();
				vector dist = vector(0,0,0);
				vector closevector = vector(0,0,0);
				vector target = vector(0,0,0);
				int closest = 10000;
				int closestid = 0;
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
