rule Technologies
inactive
highFrequency
{
	for(p = 1; <= cNumberNonGaiaPlayers){
		trTechSetStatus(p, 1, 4);
		trTechSetStatus(p, 2, 4);
		trTechSetStatus(p, 116, 4);
		trTechSetStatus(p, 29, 4);
		trTechSetStatus(p, 353, 0);
		trTechSetStatus(p, 394, 0);
		trTechSetStatus(p, 510, 0);
		trTechSetStatus(p, 145, 0);
		trTechSetStatus(p, 144, 0);
		trTechSetStatus(p, 143, 0);
		trTechSetStatus(p, 379, 0);
		trTechSetStatus(p, 28, 4);
		trTechSetStatus(p, 30, 4);
		trTechSetStatus(p, 350, 4);
		trTechSetStatus(p, 27, 4);
		for(n=930; > 0) {
			trForbidProtounit(p,kbGetProtoUnitName(n));
		}
	}
	//      trUnforbidProtounit(p, "Outpost");
	//  trUnforbidProtounit(1*p, "Oracle Hero");
	xsDisableSelf();
}

void modifyBuildableProto(string proto = "", int p = 0) {
	trModifyProtounit(proto, p, 55, 4);
	modifyProtounitAbsolute(proto, p, 2, 0);
	for(i=16; <= 19) {
		trModifyProtounit(proto, p, i, 9999999999999999999.0);
		trModifyProtounit(proto, p, i, -9999999999999999999.0);
		trModifyProtounit(proto, p, i, 0.0);
	}
}

rule Stats
inactive
highFrequency
{
	trModifyProtounit("Dwarf", 0, 55, 4);
	trModifyProtounit("Kronny Birth", 0, 8, 0.3);
	trModifyProtounit("Palm", 0, 0, 9999999999999999999.0);
	modifyProtounitAbsolute("Throwing Axeman", cNumberNonGaiaPlayers, 2, 36);
	modifyProtounitAbsolute("Throwing Axeman", cNumberNonGaiaPlayers, 0, 100);
	modifyProtounitAbsolute("Throwing Axeman", cNumberNonGaiaPlayers, 30, 1);
	modifyProtounitAbsolute("Throwing Axeman", cNumberNonGaiaPlayers, 11, 25);
	modifyProtounitAbsolute("Slinger", cNumberNonGaiaPlayers, 2, 28);
	modifyProtounitAbsolute("Slinger", cNumberNonGaiaPlayers, 0, 20);
	modifyProtounitAbsolute("Slinger", cNumberNonGaiaPlayers, 30, 2);
	modifyProtounitAbsolute("Slinger", cNumberNonGaiaPlayers, 11, 20);
	modifyProtounitAbsolute("Chu Ko Nu", cNumberNonGaiaPlayers, 2, 34);
	modifyProtounitAbsolute("Chu Ko Nu", cNumberNonGaiaPlayers, 0, 50);
	modifyProtounitAbsolute("Chu Ko Nu", cNumberNonGaiaPlayers, 11, 24);
	modifyProtounitAbsolute("Chu Ko Nu", cNumberNonGaiaPlayers, 30, 2);
	modifyProtounitAbsolute("Lampades Bolt", cNumberNonGaiaPlayers, 1, 5);
	modifyProtounitAbsolute("Lampades Bolt", cNumberNonGaiaPlayers, 8, 10);
	modifyProtounitAbsolute("Javelin Flaming", cNumberNonGaiaPlayers, 1, 6);
	modifyProtounitAbsolute("Javelin Flaming", cNumberNonGaiaPlayers, 8, 10);
	modifyProtounitAbsolute("Maceman", 0, 1, 14);
	modifyProtounitAbsolute("Villager Egyptian", cNumberNonGaiaPlayers, 0, 10000);
	modifyProtounitAbsolute("Kebenit", cNumberNonGaiaPlayers, 0, 10);
	modifyProtounitAbsolute("Kebenit", cNumberNonGaiaPlayers, 31, 1);
	modifyProtounitAbsolute("Kebenit", cNumberNonGaiaPlayers, 13, 1);
	modifyProtounitAbsolute("Kebenit", cNumberNonGaiaPlayers, 26, 0);
	modifyProtounitAbsolute("Kebenit", cNumberNonGaiaPlayers, 2, 20);
	modifyProtounitAbsolute("Kebenit", cNumberNonGaiaPlayers, 11, 14);
	modifyProtounitAbsolute("Titan Atlantean", 0, 2, 0);
	modifyProtounitAbsolute("Titan Gate Dead", 0, 2, 0);
	modifyProtounitAbsolute("Shrine", 0, 2, 0);
	modifyProtounitAbsolute("Monument", 0, 2, 0);
	modifyProtounitAbsolute("Runestone", 0, 2, 0);
	modifyProtounitAbsolute("Frost Drift", 0, 2, 0);
	modifyProtounitAbsolute("Torch", 0, 2, 0);
	modifyProtounitAbsolute("Flag", 0, 2, 2);
	modifyProtounitAbsolute("Spy Eye", 0, 2, 2);
	modifyProtounitAbsolute("Zebra", 0, 1, 0);
	modifyProtounitAbsolute("Zebra", 0, 0, 1);
	modifyProtounitAbsolute("Cinematic Block", 0, 2, 2);
	modifyProtounitAbsolute("Sentinel Main", cNumberNonGaiaPlayers, 0, 30);
	modifyProtounitAbsolute("Sentinel Main", cNumberNonGaiaPlayers, 31, 2);
	modifyProtounitAbsolute("Sentinel Main", cNumberNonGaiaPlayers, 26, 0);
	modifyProtounitAbsolute("Peltast", cNumberNonGaiaPlayers, 0, 30);
	modifyProtounitAbsolute("Peltast", cNumberNonGaiaPlayers, 31, 5);
	modifyProtounitAbsolute("Peltast", cNumberNonGaiaPlayers, 26, 0);
	modifyProtounitAbsolute("Peltast", cNumberNonGaiaPlayers, 2, 30);
	modifyProtounitAbsolute("Peltast", cNumberNonGaiaPlayers, 11, 24);
	for(p = 1; <= cNumberNonGaiaPlayers){
		modifyProtounitAbsolute("Rocket", p, 1, 5);
		modifyProtounitAbsolute("Rocket", p, 8, 10);
		modifyProtounitAbsolute("Wadjet Spit", p, 1, 9);
		modifyProtounitAbsolute("Wadjet Spit", p, 8, 10);
		modifyProtounitAbsolute("Maceman", p, 1, 14);
		trModifyProtounit("Dwarf", p, 55, 4);
		trModifyProtounit("Animal Attractor", p, 55, 4);
		trModifyProtounit("Hero Greek Bellerophon", p, 55, 4);
		//trQuestVarSet("P"+p+"FlagBaseWarnF", 15);
		//modifyProtounitAbsolute("Gate", p, 0, 1000);
		modifyProtounitAbsolute(""+GazelleProto, p, 0, 2);
		modifyProtounitAbsolute(""+GazelleProto, p, 2, 22);
		modifyProtounitAbsolute("Hero Greek Bellerophon", p, 0, 2);
		modifyProtounitAbsolute(""+RhinoProto, p, 0, 10);
		modifyProtounitAbsolute(""+RhinoProto, p, 9, 30);
		modifyProtounitAbsolute(""+RhinoDrinkProto, p, 0, 10);
		modifyProtounitAbsolute(""+RhinoDrinkProto, p, 1, 0);
		modifyProtounitAbsolute(""+RhinoDrinkProto, p, 2, 10);
		modifyProtounitAbsolute(""+RhinoDrinkProto, p, 14, 0);
		modifyProtounitAbsolute(""+RhinoDrinkProto, p, 15, 0);
		modifyProtounitAbsolute(""+RhinoProto, p, 1, xGetFloat(dPlayerData, xRhinoWalk));
		modifyProtounitAbsolute(""+RhinoProto, p, 2, 22);
		modifyProtounitAbsolute(""+GoatProto, p, 0, 6);
		modifyProtounitAbsolute(""+CrocProto, p, 0, 5);
		modifyProtounitAbsolute(""+CrocProto, p, 1, xGetFloat(dPlayerData, xCrocLandSpeed));
		modifyProtounitAbsolute(""+CrocProto, p, 2, 10);
		modifyProtounitAbsolute(""+CrocProto, p, 22, 10000);
		modifyProtounitAbsolute("Petsuchos", p, 0, 5);
		modifyProtounitAbsolute("Petsuchos", p, 1, xGetFloat(dPlayerData, xCrocLandSpeed));
		modifyProtounitAbsolute("Petsuchos", p, 2, 10);
		modifyProtounitAbsolute("Petsuchos", p, 22, 10000);
		for(a = 24; <= 29){
			modifyProtounitAbsolute(""+GazelleProto, p, a, 0);
			modifyProtounitAbsolute(""+RhinoProto, p, a, 0);
			modifyProtounitAbsolute(""+GoatProto, p, a, 0);
			modifyProtounitAbsolute(""+CrocProto, p, a, 0);
			modifyProtounitAbsolute("Hero Greek Bellerophon", p, a, 0);
		}
		modifyProtounitAbsolute(""+RhinoProto, p, 27, 15);
		modifyProtounitAbsolute(""+CrocProto, p, 11, 2);
		modifyProtounitAbsolute(""+CrocProto, p, 12, 2);
		modifyProtounitAbsolute(""+CrocProto, p, 13, 0);
		modifyProtounitAbsolute(""+CrocProto, p, 29, 5);
		modifyBuildableProto("House", p);
		modifyBuildableProto("Granary", p);
		modifyBuildableProto("Storehouse", p);
		modifyProtounitAbsolute("House", p, 16, -1);
		modifyProtounitAbsolute("Granary", p, 17, -1);
		modifyProtounitAbsolute("Storehouse", p, 18, -1);
		trModifyProtounit(""+YesChoiceUnitName, p, 55, 4);
		trModifyProtounit(""+YesChoiceUnitName, p, 1, -10);
		trModifyProtounit(""+YesChoiceUnitName, p, 2, 9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName, p, 2, -9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName, p, 2, 0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 2, 9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 2, -9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 2, 0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 6, -100);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 16, 9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 17, 9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 18, 9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 19, 9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 16, -9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 17, -9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 18, -9999999999999999999.0);
		trModifyProtounit(""+YesChoiceUnitName + " Hero", p, 19, -9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName, p, 55, 4);
		trModifyProtounit(""+NoChoiceUnitName, p, 1, -10);
		trModifyProtounit(""+NoChoiceUnitName, p, 2, 9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName, p, 2, -9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName, p, 2, 0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 2, 9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 2, -9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 2, 0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 6, -100);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 16, 9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 17, 9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 18, 9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 19, 9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 16, -9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 17, -9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 18, -9999999999999999999.0);
		trModifyProtounit(""+NoChoiceUnitName + " Hero", p, 19, -9999999999999999999.0);
		trModifyProtounit(""+CrocProto, p, 55, 3);
		trModifyProtounit("Petsuchos", p, 55, 3);
		trModifyProtounit("Huskarl", 0, 55, 4);
		trModifyProtounit("Trident Soldier", 0, 55, 4);
		trModifyProtounit("Dwarf", 0, 55, 4);
		trModifyProtounit("Huskarl", cNumberNonGaiaPlayers, 55, 4);
		trModifyProtounit("Trident Soldier", cNumberNonGaiaPlayers, 55, 4);
		trModifyProtounit("Dwarf", cNumberNonGaiaPlayers, 55, 4);
		trModifyProtounit("Invisible Target", 0, 55, 4);
		trModifyProtounit("Invisible Target", cNumberNonGaiaPlayers, 55, 4);
		trModifyProtounit("Maceman", 0, 55, 4);
		trModifyProtounit("Maceman", cNumberNonGaiaPlayers, 55, 4);
	}
	xsDisableSelf();
}

/*
The field ids are as follows:
Hitpoints=0
Speed=1
LOS=2
Train Points=3
Build Points=4
Max Contained=5
Population Count=6
Pop Cap Addition=7
Lifespan=8
Recharge Time=9
Build Limit=10
Range=11
Minimum Range=12
Num Projectiles=13
Healing Rate=14
Healing Range=15
Cost Gold=16
Cost Wood=17
Cost Food=18
Cost Favor=19
Carry Capacity Gold=20
Carry Capacity Wood=21
Carry Capacity Food=22
Carry Capacity Favor=23
Armor Hack=24
Armor Pierce=25
Armor Crush=26
Hand Attack Hack=27
Hand Attack Pierce=28
Hand Attack Crush=29
Ranged Attack Hack=30
Ranged Attack Pierce=31
Ranged Attack Crush=32
Movetype = 55
Delta of 0: Movement Type None.
Delta of 1: Movement Type Land.
Delta of 2: Movement Type Water.
Delta of 3: Movement Type Amphibious.
Delta of 4: Movement Type Air.
*/
