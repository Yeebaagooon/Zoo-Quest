rule ysearch
inactive
highFrequency
{
	int id = 0;
	int unittype = 0;
	int temp = 0;
	int closest = 0;
	int closestid = 0;
	float baseCos = 0;
	float baseSin = 0;
	int index = 0;
	vector scale = vector(0,0,0);
	vector dest = vector(0,0,0);
	vector dir = vector(0,0,0);
	vector closevector = vector(0,0,0);
	vector target = vector(0,0,0);
	vector slingvector = vector(0,0,0);
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
				if(Stage == 3){
					xSetPointer(dPlayerData, kbUnitGetOwner(id));
					xSetVector(dPlayerData, xGoatTarget, kbGetBlockPosition(""+trGetUnitScenarioNameNumber(id)));
					xSetFloat(dPlayerData, xGoatJumpDist, distanceBetweenVectors(xGetVector(dPlayerData, xGoatTarget),kbGetBlockPosition(""+1*trQuestVarGet("P"+kbUnitGetOwner(id)+"Unit")),true));
					if(xGetFloat(dPlayerData, xGoatJumpDist) >= 225){
						//try a fix
						dir = xGetVector(dPlayerData, xGoatTarget)-kbGetBlockPosition(""+1*trQuestVarGet("P"+kbUnitGetOwner(id)+"Unit"));
						dir = xsVectorNormalize(dir);
						vector tempV = kbGetBlockPosition(""+1*trQuestVarGet("P"+kbUnitGetOwner(id)+"Unit"));
						target = tempV+(dir*15);
						xSetVector(dPlayerData, xGoatTarget, target);
						xSetFloat(dPlayerData, xGoatJumpDist, distanceBetweenVectors(xGetVector(dPlayerData, xGoatTarget),kbGetBlockPosition(""+1*trQuestVarGet("P"+kbUnitGetOwner(id)+"Unit")),true));
					}
				}
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
			case kbGetProtoUnitID("Storehouse"):
			{
				trPlayerGrantResources(kbUnitGetOwner(id), "Food", 1);
				if(Stage == 5){
					xSetPointer(dPlayerData, kbUnitGetOwner(id));
					xSetVector(dPlayerData, xSpecialVector, kbGetBlockPosition(""+trGetUnitScenarioNameNumber(id)));
				}
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
				dir = vector(0,0,0);
				closevector = vector(0,0,0);
				target = vector(0,0,0);
				closest = 10000;
				closestid = 0;
				//cycle through all throwing axemen to find the closest
				for(a=xGetDatabaseCount(dPoachers) ; > 0){
					xDatabaseNext(dPoachers);
					dir = kbGetBlockPosition(""+xGetInt(dPoachers, xUnitID));
					xUnitSelect(dPoachers, xUnitID);
					if(trUnitDead() == false){
						if(distanceBetweenVectors(dir, axevector, true) < closest){
							closest = distanceBetweenVectors(dir, axevector, true);
							closestid = xGetInt(dPoachers, xUnitID);
						}
					}
				}
				closevector = kbGetBlockPosition(""+closestid);
				xsSetContextPlayer(cNumberNonGaiaPlayers);
				dest = kbGetBlockPosition(""+trGetUnitScenarioNameNumber(kbUnitGetTargetUnitID(kbGetBlockID(""+closestid))));
				xsSetContextPlayer(0);
				dir = xsVectorNormalize(dest-closevector);
				if(Stage != 3){
					ShootProjectile(dir, closevector, "Lampades Bolt", "Rocket");
				}
				if(Stage == 3){
					//rotate to L, for loop shoot
					baseCos = 0.965926; //cos15
					baseSin = 0.258819; //sin15
					//calculator for sin and cos(angle) required
					//so for 15 degrees and 5 projs our angles are 30,15,0,-15-,-30, so set to cos/sin -30 then loop for +15
					dir = rotationMatrix(dir, 0.965926, -0.258819); //dir, -30cos, -30sin
					for(a = 1; < 4){
						ShootProjectile(dir, closevector, "Lampades Bolt", "Wadjet Spit", 0, 1, 8000);
						dir = rotationMatrix(dir, baseCos, baseSin);
					}
				}
			}
			case kbGetProtoUnitID("Sling Stone"):
			{
				//axe
				slingvector = kbGetBlockPosition(""+i);
				trUnitSelectClear();
				trUnitSelectByID(id);
				trUnitDestroy();
				dir = vector(0,0,0);
				closevector = vector(0,0,0);
				target = vector(0,0,0);
				closest = 10000;
				closestid = 0;
				//cycle through all poachers to find the closest
				if(Stage != 5){
					for(a=xGetDatabaseCount(dPoachers) ; > 0){
						xDatabaseNext(dPoachers);
						dir = kbGetBlockPosition(""+xGetInt(dPoachers, xUnitID));
						xUnitSelect(dPoachers, xUnitID);
						if(trUnitDead() == false){
							if(distanceBetweenVectors(dir, slingvector, true) < closest){
								closest = distanceBetweenVectors(dir, slingvector, true);
								closestid = xGetInt(dPoachers, xUnitID);
							}
						}
					}
				}
				else{
					for(a=xGetDatabaseCount(dEnemies) ; > 0){
						xDatabaseNext(dEnemies);
						dir = kbGetBlockPosition(""+xGetInt(dEnemies, xUnitID));
						xUnitSelect(dEnemies, xUnitID);
						if(trUnitDead() == false){
							if(distanceBetweenVectors(dir, slingvector, true) < closest){
								closest = distanceBetweenVectors(dir, slingvector, true);
								closestid = xGetInt(dEnemies, xUnitID);
							}
						}
					}
				}
				closevector = kbGetBlockPosition(""+closestid);
				xsSetContextPlayer(cNumberNonGaiaPlayers);
				dest = kbGetBlockPosition(""+trGetUnitScenarioNameNumber(kbUnitGetTargetUnitID(kbGetBlockID(""+closestid))));
				xsSetContextPlayer(0);
				dir = xsVectorNormalize(dest-closevector);
				if(Stage != 5){
					ShootProjectile(dir, closevector, "Lampades Bolt", "Rocket");
				}
				else{
					if(Stage == 5){
						ShootProjectile(dir, closevector, "Ball of Fire", "Wadjet Spit", 0, 10, 8000);
					}
				}
			}
			case kbGetProtoUnitID("Arrow"):
			{
				if(Stage != 5){
					slingvector = kbGetBlockPosition(""+i);
					trUnitSelectClear();
					trUnitSelectByID(id);
					trUnitDestroy();
					dir = vector(0,0,0);
					closevector = vector(0,0,0);
					target = vector(0,0,0);
					closest = 10000;
					closestid = 0;
					//cycle through all poachers to find the closest
					for(a=xGetDatabaseCount(dPoachers) ; > 0){
						xDatabaseNext(dPoachers);
						dir = kbGetBlockPosition(""+xGetInt(dPoachers, xUnitID));
						xUnitSelect(dPoachers, xUnitID);
						if(trUnitDead() == false){
							if(distanceBetweenVectors(dir, slingvector, true) < closest){
								closest = distanceBetweenVectors(dir, slingvector, true);
								closestid = xGetInt(dPoachers, xUnitID);
							}
						}
					}
					closevector = kbGetBlockPosition(""+closestid);
					xsSetContextPlayer(cNumberNonGaiaPlayers);
					dest = kbGetBlockPosition(""+trGetUnitScenarioNameNumber(kbUnitGetTargetUnitID(kbGetBlockID(""+closestid))));
					xsSetContextPlayer(0);
					dir = xsVectorNormalize(dest-closevector);
					//rotate to L, for loop shoot
					baseCos = 0.996195; //cos5
					baseSin = 0.087156; //sin5
					//calculator for sin and cos(angle) required
					//so for 15 degrees and 5 projs our angles are 30,15,0,-15-,-30, so set to cos/sin -30 then loop for +15
					dir = rotationMatrix(dir, 0.965926, -0.258819); //dir, -15cos, -15sin
					for(a = 1; < 6){
						for(b = xGetDatabaseCount(dPoachers); > 0){
							xDatabaseNext(dPoachers);
							if(xGetInt(dPoachers, xUnitID) == closestid){
								unitcheck = xGetString(dPoachers, xPoacherType);
								continue;
							}
						}
						if(unitcheck == "Sentinel Main"){
							IGUnit = true;
							IGName = closestid;
						}
						ShootProjectile(dir, closevector, "Lampades Bolt", "Wadjet Spit", 0, 2, 7000);
						dir = rotationMatrix(dir, baseCos, baseSin);
					}
				}
				if(Stage == 5){
					slingvector = kbGetBlockPosition(""+i);
					trUnitSelectClear();
					trUnitSelectByID(id);
					trUnitDestroy();
					dir = vector(0,0,0);
					closevector = vector(0,0,0);
					target = vector(0,0,0);
					closest = 10000;
					closestid = 0;
					//cycle through all poachers to find the closest
					for(a=xGetDatabaseCount(dTowers) ; > 0 ){
						xDatabaseNext(dTowers);
						dir = kbGetBlockPosition(""+xGetInt(dTowers, xUnitID));
						xUnitSelect(dTowers, xUnitID);
						if(trUnitDead() == false){
							if(xGetBool(dTowers, xConstructed) == true){
								if(distanceBetweenVectors(dir, slingvector, true) < closest){
									closest = distanceBetweenVectors(dir, slingvector, true);
									closestid = xGetInt(dTowers, xUnitID);
									index = xGetPointer(dTowers);
								}
							}
						}
					}
					closevector = kbGetBlockPosition(""+closestid);
					xsSetContextPlayer(xGetInt(dTowers, xOwner, index));
					dest = kbGetBlockPosition(""+trGetUnitScenarioNameNumber(kbUnitGetTargetUnitID(kbGetBlockID(""+closestid))));
					xsSetContextPlayer(0);
					dir = xsVectorNormalize(dest-closevector);
					IGUnit = true;
					IGName = closestid;
					unitcheck = "Tower";
					xSetPointer(dPlayerData, xGetInt(dTowers, xOwner));
					trBlockAllAmbientSounds();
					trBlockAllSounds();
					ShootProjectile(dir, closevector, "Lampades Bolt", "Wadjet Spit", 0, xGetInt(dPlayerData, xTowerDamage), 5000, 1*xGetInt(dTowers, xOwner));
					trDelayedRuleActivation("UnblockSound");
				}
			}
			case kbGetProtoUnitID("Spear Flaming"):
			{
				slingvector = kbGetBlockPosition(""+i);
				trUnitSelectClear();
				trUnitSelectByID(id);
				trUnitDestroy();
				dir = vector(0,0,0);
				closevector = vector(0,0,0);
				target = vector(0,0,0);
				closest = 10000;
				closestid = 0;
				//cycle through all poachers to find the closest
				if(Stage != 5){
					for(a=xGetDatabaseCount(dPoachers) ; > 0){
						xDatabaseNext(dPoachers);
						dir = kbGetBlockPosition(""+xGetInt(dPoachers, xUnitID));
						xUnitSelect(dPoachers, xUnitID);
						if(trUnitDead() == false){
							if(distanceBetweenVectors(dir, slingvector, true) < closest){
								closest = distanceBetweenVectors(dir, slingvector, true);
								closestid = xGetInt(dPoachers, xUnitID);
							}
						}
					}
				}
				else{
					for(a=xGetDatabaseCount(dEnemies) ; > 0){
						xDatabaseNext(dEnemies);
						dir = kbGetBlockPosition(""+xGetInt(dEnemies, xUnitID));
						xUnitSelect(dEnemies, xUnitID);
						if(trUnitDead() == false){
							if(distanceBetweenVectors(dir, slingvector, true) < closest){
								closest = distanceBetweenVectors(dir, slingvector, true);
								closestid = xGetInt(dEnemies, xUnitID);
							}
						}
					}
				}
				closevector = kbGetBlockPosition(""+closestid);
				xsSetContextPlayer(cNumberNonGaiaPlayers);
				dest = kbGetBlockPosition(""+trGetUnitScenarioNameNumber(kbUnitGetTargetUnitID(kbGetBlockID(""+closestid))));
				xsSetContextPlayer(0);
				dir = xsVectorNormalize(dest-closevector);
				if(Stage == 4){
					//rotate to L, for loop shoot
					baseCos = 0.965926; //cos15
					baseSin = 0.258819; //sin15
					//calculator for sin and cos(angle) required
					//so for 15 degrees and 5 projs our angles are 30,15,0,-15-,-30, so set to cos/sin -30 then loop for +15
					dir = rotationMatrix(dir, 0.866025, -0.5); //dir, -30cos, -30sin
					for(a = 1; < 6){
						ShootProjectile(dir, closevector, "Ball of Fire", "Maceman", 0, 5, 4000);
						dir = rotationMatrix(dir, baseCos, baseSin);
					}
				}
				if(Stage == 5){
					//rotate to L, for loop shoot
					baseCos = 0.965926; //cos15
					baseSin = 0.258819; //sin15
					//calculator for sin and cos(angle) required
					//so for 15 degrees and 5 projs our angles are 30,15,0,-15-,-30, so set to cos/sin -30 then loop for +15
					dir = rotationMatrix(dir, 0.866025, -0.5); //dir, -30cos, -30sin
					for(a = 1; < 6){
						ShootProjectile(dir, closevector, "Ball of Fire", "Wadjet Spit", 0, 20, 6000);
						dir = rotationMatrix(dir, baseCos, baseSin);
					}
				}
			}
			case kbGetProtoUnitID("Arrow Flaming"):
			{
				slingvector = kbGetBlockPosition(""+i);
				trUnitSelectClear();
				trUnitSelectByID(id);
				trUnitDestroy();
				dir = vector(0,0,0);
				closevector = vector(0,0,0);
				target = vector(0,0,0);
				closest = 10000;
				closestid = 0;
				//cycle through all poachers to find the closest
				if(Stage != 5){
					for(a=xGetDatabaseCount(dPoachers) ; > 0){
						xDatabaseNext(dPoachers);
						dir = kbGetBlockPosition(""+xGetInt(dPoachers, xUnitID));
						xUnitSelect(dPoachers, xUnitID);
						if(trUnitDead() == false){
							if(distanceBetweenVectors(dir, slingvector, true) < closest){
								closest = distanceBetweenVectors(dir, slingvector, true);
								closestid = xGetInt(dPoachers, xUnitID);
							}
						}
					}
				}
				else{
					for(a=xGetDatabaseCount(dEnemies) ; > 0){
						xDatabaseNext(dEnemies);
						dir = kbGetBlockPosition(""+xGetInt(dEnemies, xUnitID));
						xUnitSelect(dEnemies, xUnitID);
						if(trUnitDead() == false){
							if(distanceBetweenVectors(dir, slingvector, true) < closest){
								closest = distanceBetweenVectors(dir, slingvector, true);
								closestid = xGetInt(dEnemies, xUnitID);
							}
						}
					}
				}
				closevector = kbGetBlockPosition(""+closestid);
				xsSetContextPlayer(cNumberNonGaiaPlayers);
				dest = kbGetBlockPosition(""+trGetUnitScenarioNameNumber(kbUnitGetTargetUnitID(kbGetBlockID(""+closestid))));
				xsSetContextPlayer(0);
				dir = xsVectorNormalize(dest-closevector);
				if(Stage == 2){
					//rotate to L, for loop shoot
					baseCos = 0.965926; //cos15
					baseSin = 0.258819; //sin15
					//calculator for sin and cos(angle) required
					//so for 15 degrees and 5 projs our angles are 30,15,0,-15-,-30, so set to cos/sin -30 then loop for +15
					dir = rotationMatrix(dir, 0.866025, -0.5); //dir, -30cos, -30sin
					for(a = 1; < 6){
						ShootProjectile(dir, closevector, "Lampades Bolt", "Wadjet Spit");
						dir = rotationMatrix(dir, baseCos, baseSin);
					}
				}
				if(Stage == 4){
					for(a = xGetDatabaseCount(dPoachers); > 0){
						xDatabaseNext(dPoachers);
						if(xGetInt(dPoachers, xUnitID) == closestid){
							unitcheck = xGetString(dPoachers, xPoacherType);
							continue;
						}
					}
					if(unitcheck == "Kebenit"){
						IGUnit = true;
						IGName = closestid;
					}
					ShootProjectile(dir, closevector, "Lampades Bolt", "Wadjet Spit");
				}
				if(Stage == 5){
					ShootProjectile(dir, closevector, "Ball of Fire", "Wadjet Spit", 0, 5, 8000);
				}
			}
			case kbGetProtoUnitID("Tower"):
			{
				trUnitSelectClear();
				trUnitSelectByID(id);
				trSetSelectedScale(1,0.3,1);
				trUnitSelectClear();
				dest = kbGetBlockPosition(""+i);
				if(TutorialMode == true){
					int owner = kbUnitGetOwner(id);
					owner = owner*16;
					if((xsVectorGetZ(dest) > owner+8 ) || (xsVectorGetZ(dest) < owner-8 )){
						trUnitSelectByID(id);
						trUnitDestroy();
						owner = owner/16;
						if(trCurrentPlayer() == owner){
							playSound("cantdothat.wav");
						}
						ColouredChatToPlayer(owner, "1,0,0", "Build in your own section!");
					}
				}
				xAddDatabaseBlock(dTowers, true);
				xSetInt(dTowers, xUnitID, i);
				xSetInt(dTowers, xOwner, kbUnitGetOwner(id));
				xSetBool(dTowers, xConstructed, false);
				xAddDatabaseBlock(dEnemyCollision, true);
				xSetInt(dEnemyCollision, xUnitID, i);
			}
			case kbGetProtoUnitID("Animal Attractor"):
			{
				trTechGodPower(kbUnitGetOwner(id), "Animal Magnetism", 1);
				dest = kbGetBlockPosition(""+i);
				scale = kbGetBlockPosition(""+1*trQuestVarGet("P"+kbUnitGetOwner(id)+"Unit"));
				if(distanceBetweenVectors(dest,scale) < 144){
					for(a = xGetDatabaseCount(dFreeRelics); > 0){
						xDatabaseNext(dFreeRelics);
						dir = kbGetBlockPosition(""+xGetInt(dFreeRelics, xUnitID));
						if(distanceBetweenVectors(dest,dir) < 36){
							xUnitSelect(dFreeRelics, xUnitID);
							trUnitChangeProtoUnit("Dwarf");
							xUnitSelect(dFreeRelics, xUnitID);
							trUnitChangeProtoUnit("UI Range Indicator Norse SFX");
							xUnitSelect(dFreeRelics, xSFXID);
							trUnitChangeProtoUnit("Osiris SFX");
							xAddDatabaseBlock(dMines, true);
							xSetInt(dMines, xUnitID, xGetInt(dFreeRelics, xUnitID));
							xSetInt(dMines, xOwner, kbUnitGetOwner(id));
							xSetInt(dMines, xMineSFX, xGetInt(dFreeRelics, xSFXID));
							xFreeDatabaseBlock(dFreeRelics);
						}
					}
				}
				else{
					if(trCurrentPlayer() == kbUnitGetOwner(id)){
						playSound("cantdothat.wav");
						ColouredChatToPlayer(kbUnitGetOwner(id), "1,0,0", "You can't convert mines from this far away.");
					}
				}
				trUnitSelectClear();
				trUnitSelectByID(id);
				trUnitDestroy();
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
	if(xGetDatabaseCount(dIncomingMissiles) > 0){
		//[IF REMOVE, DB COUNT GOES DOWN SO DO IT LIKE THIS]
		for(a = xGetDatabaseCount(dIncomingMissiles) ; > 0){
			xDatabaseNext(dIncomingMissiles);
			//if missile has spy eye, shoot it and cast spy on it too
			if(xGetInt(dIncomingMissiles, xMissileSpyID) > -1){
				if(xGetInt(dIncomingMissiles, xMissileSpyOfSpyID) > -1){
					//passenger here
					xUnitSelect(dIncomingMissiles, xMissileSpyID);
					trUnitChangeProtoUnit("Victory Marker");
					xUnitSelect(dIncomingMissiles, xMissileSpyID);
					trSetScale(2);
					xUnitSelect(dIncomingMissiles, xMissileSpyOfSpyID);
					trSetScale(0);
					xFreeDatabaseBlock(dIncomingMissiles);
				}
				else if(xGetBool(dIncomingMissiles, SpyDone) == false){
					dest = vectorSetAsTargetVector(xGetVector(dIncomingMissiles, xMissilePos), xGetVector(dIncomingMissiles, xMissileDir), 60.0);
					xUnitSelect(dIncomingMissiles, xUnitID);
					trMutateSelected(xGetInt(dIncomingMissiles, xMissileCarProto));
					xSetBool(dIncomingMissiles, SpyDone, true);
					//The car is the rocket
					trUnitSelectClear();
					xUnitSelect(dIncomingMissiles, xUnitID);
					trUnitMoveToPoint(xsVectorGetX(dest),0,xsVectorGetZ(dest),-1,false);
					xAddDatabaseBlock(dMissiles, true);
					xSetInt(dMissiles, xUnitID, xGetInt(dIncomingMissiles, xUnitID));
					xSetInt(dMissiles, xOwner, xGetInt(dIncomingMissiles, xOwner));
					xSetVector(dMissiles, xMissilePos, xGetVector(dIncomingMissiles, xMissilePos));
					xSetVector(dMissiles, xMissilePrev, xGetVector(dIncomingMissiles, xMissilePos));
					xSetVector(dMissiles, xMissileDir, xGetVector(dIncomingMissiles, xMissileDir));
					xSetInt(dMissiles, xMissileDmg, xGetInt(dIncomingMissiles, xIMissileDmg));
					xAddDatabaseBlock(dDestroyMe, true);
					xSetInt(dDestroyMe, xUnitID, xGetInt(dIncomingMissiles, xUnitID));
					xSetInt(dDestroyMe, xDestroyTime, trTimeMS()+xGetInt(dIncomingMissiles, xIMissileTime));
					xUnitSelect(dIncomingMissiles, xMissileSpyID);
					trUnitChangeProtoUnit("Huskarl");
					xUnitSelect(dIncomingMissiles, xMissileSpyID);
					trUnitConvert(cNumberNonGaiaPlayers);
					xUnitSelect(dIncomingMissiles, xMissileSpyID);
					trSetScale(0);
					xUnitSelect(dIncomingMissiles, xMissileSpyID);
					spyEffect(xGetInt(dIncomingMissiles, xMissileProto), xGetInt(dIncomingMissiles, xMissileAnim), xsVectorSet(dIncomingMissiles, xMissileSpyOfSpyID, xGetPointer(dIncomingMissiles)), vector(1,1,1));
				}
				
			}
		}
	}
}

rule UnblockSound
inactive
highFrequency
{
	trUnBlockAllAmbientSounds();
	trUnblockAllSounds();
	xsDisableSelf();
}
