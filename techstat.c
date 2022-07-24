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
		for(n=930; >0) {
			trForbidProtounit(p,kbGetProtoUnitName(n));
		}
	}
	//      trUnforbidProtounit(p, "Outpost");
	//  trUnforbidProtounit(1*p, "Oracle Hero");
	xsDisableSelf();
}

rule Stats
inactive
highFrequency
{
	trModifyProtounit("Dwarf", 0, 55, 4);
	for(p = 1; <= cNumberNonGaiaPlayers){
		trModifyProtounit("Dwarf", p, 55, 4);
		//trQuestVarSet("P"+p+"FlagBaseWarnF", 15);
		//modifyProtounitAbsolute("Gate", p, 0, 1000);
		modifyProtounitAbsolute("Atlantis Wall Long", p, 0, 10000000);
		modifyProtounitAbsolute("Atlantis Wall Connector", p, 0, 10000000);
		modifyProtounitAbsolute("Tower Mirror", p, 0, 10000000);
		modifyProtounitAbsolute("Storage Pit", p, 0, 10000000);
		trUnforbidProtounit(p, "Outpost");
		modifyProtounitAbsolute("Outpost", p, 16, 0);
		modifyProtounitAbsolute("Outpost", p, 17, 100);
		modifyProtounitAbsolute("Mercenary", p, 8, 1);
		modifyProtounitAbsolute("Farm", p, 16, 0);
		modifyProtounitAbsolute("Farm", p, 17, 100);
		modifyProtounitAbsolute("Farm", p, 18, 0);
		modifyProtounitAbsolute("Tower", p, 16, 0);
		modifyProtounitAbsolute("Tower", p, 17, 250);
		modifyProtounitAbsolute("Tower", p, 18, 0);
		modifyProtounitAbsolute("Tower", p, 10, 5);
		modifyProtounitAbsolute("Ape of Set", p, 16, 50);
		modifyProtounitAbsolute("Ape of Set", p, 17, 0);
		modifyProtounitAbsolute("Ape of Set", p, 18, 0);
		modifyProtounitAbsolute("Ape of Set", p, 19, 0);
		modifyProtounitAbsolute("Ape of Set", p, 6, 0);
		modifyProtounitAbsolute("Ape of Set", p, 3, 1);
		modifyProtounitAbsolute("Market", p, 16, 0);
		modifyProtounitAbsolute("Market", p, 17, 400);
		modifyProtounitAbsolute("Market", p, 18, 0);
		modifyProtounitAbsolute("Market", p, 10, 1);
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
*/
