int deployLocHeading(float posX = 0.0, float PosZ = 0.0, string unit = "", int p = 0, float heading = 0.0){
	int unitId = trGetNextUnitScenarioNameNumber();
	trArmyDispatch(""+p+",0",unit,1,posX,0,PosZ,heading,true);
	if(unitId != trGetNextUnitScenarioNameNumber()){
		return (unitId);
	} else {
		return (-1);
	}
}

int deployLoc(float posX = 0.0, float PosZ = 0.0, string unit = "", int p = 0){
	int unitId = trGetNextUnitScenarioNameNumber();
	trArmyDispatch(""+p+",0",unit,1,posX,0,PosZ,0,true);
	if(unitId != trGetNextUnitScenarioNameNumber()){
		return (unitId);
	} else {
		return (-1);
	}
}

void playSound(string soundName = ""){
	trSoundPlayPaused(""+soundName+"", "1", -1, "", "");
}

int deployLocRandomHeading(float posX = 0.0, float PosZ = 0.0, string unit = "", int p = 0){
	int unitId = trGetNextUnitScenarioNameNumber();
	trQuestVarSetFromRand("heading", 0, 359, true);
	trArmyDispatch(""+p+",0",unit,1,posX,0,PosZ,1*trQuestVarGet("heading"),true);
	if(unitId != trGetNextUnitScenarioNameNumber()){
		return (unitId);
	} else {
		return (-1);
	}
}

int getTerrainType(string name = ""){
	if(name == "GrassA")return (0);
	if(name == "GrassB")return (0);
	if(name == "GrassDirt25")return (0);
	if(name == "GrassDirt50")return (0);
	if(name == "GrassDirt75")return (0);
	if(name == "CliffGreekB")return (0);
	if(name == "GreekRoad Burnt")return (0);
	if(name == "GreekRoad BurntB")return (0);
	if(name == "GaiaCreepA")return (0);
	if(name == "GaiaCreepASnow")return (0);
	if(name == "GaiaCreepASand")return (0);
	if(name == "GaiaCreepB")return (0);
	if(name == "GaiaCreepBorder")return (0);
	if(name == "GaiaCreepBorderSnow")return (0);
	if(name == "GaiaCreepBorderSand")return (0);
	if(name == "SavannahA")return (0);
	if(name == "SavannahB")return (0);
	if(name == "SavannahC")return (0);
	if(name == "SavannahD")return (0);
	if(name == "JungleA")return (0);
	if(name == "JungleB")return (0);
	if(name == "JungleDirt25")return (0);
	if(name == "JungleDirt50")return (0);
	if(name == "JungleDirt75")return (0);
	if(name == "CliffJungleB")return (0);
	if(name == "PlainA")return (0);
	if(name == "PlainB")return (0);
	if(name == "PlainDirt25")return (0);
	if(name == "PlainDirt50")return (0);
	if(name == "PlainDirt75")return (0);
	if(name == "CliffPlainB")return (0);
	if(name == "DirtA")return (0);
	if(name == "DirtB")return (0);
	if(name == "DirtC")return (0);
	if(name == "SandA")return (0);
	if(name == "SandB")return (0);
	if(name == "SandC")return (0);
	if(name == "SandD")return (0);
	if(name == "CliffEgyptianB")return (0);
	if(name == "SandDirt50")return (0);
	if(name == "SandDirt50b")return (0);
	if(name == "SnowA")return (0);
	if(name == "SnowB")return (0);
	if(name == "SnowGrass25")return (0);
	if(name == "SnowGrass50")return (0);
	if(name == "SnowGrass75")return (0);
	if(name == "SnowSand25")return (0);
	if(name == "SnowSand50")return (0);
	if(name == "SnowSand75")return (0);
	if(name == "CliffNorseB")return (0);
	if(name == "OlympusA")return (0);
	if(name == "OlympusB")return (0);
	if(name == "OlympusC")return (0);
	if(name == "OlympusTile")return (0);
	if(name == "TundraGrassA")return (0);
	if(name == "TundraGrassB")return (0);
	if(name == "TundraRockA")return (0);
	if(name == "TundraRockB")return (0);
	if(name == "MarshA")return (0);
	if(name == "MarshB")return (0);
	if(name == "MarshC")return (0);
	if(name == "MarshD")return (0);
	if(name == "MarshE")return (0);
	if(name == "MarshF")return (0);
	if(name == "EgyptianRoadA")return (0);
	if(name == "GreekRoadA")return (0);
	if(name == "NorseRoadA")return (0);
	if(name == "JungleRoadA")return (0);
	if(name == "PlainRoadA")return (0);
	if(name == "TundraRoadA")return (0);
	if(name == "CityTileA")return (0);
	if(name == "CityTileAtlantis")return (0);
	if(name == "CityTileAtlantisCoral")return (0);
	if(name == "CityTileWaterPool")return (0);
	if(name == "CityTileWaterEdgeA")return (0);
	if(name == "CityTileWaterEdgeB")return (0);
	if(name == "CityTileWaterEdgeEndA")return (0);
	if(name == "CityTileWaterEdgeEndB")return (0);
	if(name == "CityTileWaterEdgeEndC")return (0);
	if(name == "CityTileWaterEdgeEndD")return (0);
	if(name == "CityTileWaterCornerA")return (0);
	if(name == "CityTileWaterCornerB")return (0);
	if(name == "CityTileWaterCornerC")return (0);
	if(name == "CityTileWaterCornerD")return (0);
	if(name == "HadesBuildable1")return (0);
	if(name == "HadesBuildable2")return (0);
	if(name == "ForestFloorPalm")return (0);
	if(name == "ForestFloorPine")return (0);
	if(name == "ForestFloorPineSnow")return (0);
	if(name == "ForestFloorOak")return (0);
	if(name == "ForestFloorGaia")return (0);
	if(name == "ForestFloorSavannah")return (0);
	if(name == "ForestFloorDeadPine")return (0);
	if(name == "ForestFloorTundra")return (0);
	if(name == "ForestFloorMarsh")return (0);
	if(name == "ForestFloorJungle")return (0);
	if(name == "Water")return (1);
	if(name == "CliffA")return (2);
	if(name == "CliffGreekA")return (2);
	if(name == "CliffEgyptianA")return (2);
	if(name == "CliffNorseA")return (2);
	if(name == "CliffJungleA")return (2);
	if(name == "CliffPlainA")return (2);
	if(name == "Dam")return (2);
	if(name == "Hades3")return (2);
	if(name == "Hades5")return (2);
	if(name == "Hades6")return (2);
	if(name == "Hades7")return (2);
	if(name == "HadesCliff")return (2);
	if(name == "Hades4")return (2);
	if(name == "BlackRock")return (2);
	if(name == "UnderwaterRockA")return (3);
	if(name == "UnderwaterRockB")return (3);
	if(name == "UnderwaterRockC")return (3);
	if(name == "UnderwaterRockD")return (3);
	if(name == "UnderwaterRockE")return (3);
	if(name == "UnderwaterRockF")return (3);
	if(name == "UnderwaterIceA")return (3);
	if(name == "UnderwaterIceB")return (3);
	if(name == "UnderwaterIceC")return (3);
	if(name == "CoralA")return (3);
	if(name == "CoralB")return (3);
	if(name == "CoralC")return (3);
	if(name == "CoralC2")return (3);
	if(name == "CoralD")return (3);
	if(name == "CoralE")return (3);
	if(name == "CoralF")return (3);
	if(name == "ShorelineSandA")return (4);
	if(name == "ShorelineAegeanA")return (4);
	if(name == "ShorelineAegeanB")return (4);
	if(name == "ShorelineAegeanC")return (4);
	if(name == "ShorelineRedSeaA")return (4);
	if(name == "ShorelineRedSeaB")return (4);
	if(name == "ShorelineRedSeaC")return (4);
	if(name == "ShorelineNorwegianA")return (4);
	if(name == "ShorelineNorwegianB")return (4);
	if(name == "ShorelineNorwegianC")return (4);
	if(name == "ShorelineMediterraneanA")return (4);
	if(name == "ShorelineMediterraneanB")return (4);
	if(name == "ShorelineMediterraneanC")return (4);
	if(name == "ShorelineMediterraneanD")return (4);
	if(name == "ShorelineAtlanticA")return (4);
	if(name == "ShorelineAtlanticB")return (4);
	if(name == "ShorelineAtlanticC")return (4);
	if(name == "ShorelineTundraA")return (4);
	if(name == "ShorelineTundraB")return (4);
	if(name == "ShorelineTundraC")return (4);
	if(name == "ShorelineTundraD")return (4);
	if(name == "ShorelineJungleA")return (4);
	if(name == "ShorelineJungleB")return (4);
	if(name == "ShorelineJungleC")return (4);
	if(name == "ShorelinePlainA")return (4);
	if(name == "ShorelinePlainB")return (4);
	if(name == "ShorelinePlainC")return (4);
	if(name == "ShorelinePlainD")return (4);
	if(name == "RiverSandyA")return (4);
	if(name == "RiverSandyB")return (4);
	if(name == "RiverSandyC")return (4);
	if(name == "RiverSandyShallowA")return (4);
	if(name == "RiverGrassyA")return (4);
	if(name == "RiverGrassyB")return (4);
	if(name == "RiverGrassyC")return (4);
	if(name == "RiverIcyA")return (4);
	if(name == "RiverIcyB")return (4);
	if(name == "RiverIcyC")return (4);
	if(name == "RiverMarshA")return (4);
	if(name == "RiverMarshB")return (4);
	if(name == "RiverMarshC")return (4);
	if(name == "IceA")return (5);
	if(name == "IceB")return (5);
	if(name == "IceC")return (5);
	if(name == "MiningGround")return (5);
	if(name == "Black")return (5);
	if(name == "Hades1")return (5);
	if(name == "Hades2")return (5);
	if(name == "Hades4Passable")return (5);
	if(name == "Hades8")return (5);
	if(name == "Hades9")return (5);
}
int getTerrainSubType(string name = ""){
	if(name == "GrassA")return (0);
	if(name == "GrassB")return (1);
	if(name == "GrassDirt25")return (2);
	if(name == "GrassDirt50")return (3);
	if(name == "GrassDirt75")return (4);
	if(name == "CliffGreekB")return (5);
	if(name == "GreekRoad Burnt")return (6);
	if(name == "GreekRoad BurntB")return (7);
	if(name == "GaiaCreepA")return (8);
	if(name == "GaiaCreepASnow")return (9);
	if(name == "GaiaCreepASand")return (10);
	if(name == "GaiaCreepB")return (11);
	if(name == "GaiaCreepBorder")return (12);
	if(name == "GaiaCreepBorderSnow")return (13);
	if(name == "GaiaCreepBorderSand")return (14);
	if(name == "SavannahA")return (15);
	if(name == "SavannahB")return (16);
	if(name == "SavannahC")return (17);
	if(name == "SavannahD")return (18);
	if(name == "JungleA")return (19);
	if(name == "JungleB")return (20);
	if(name == "JungleDirt25")return (21);
	if(name == "JungleDirt50")return (22);
	if(name == "JungleDirt75")return (23);
	if(name == "CliffJungleB")return (24);
	if(name == "PlainA")return (25);
	if(name == "PlainB")return (26);
	if(name == "PlainDirt25")return (27);
	if(name == "PlainDirt50")return (28);
	if(name == "PlainDirt75")return (29);
	if(name == "CliffPlainB")return (30);
	if(name == "DirtA")return (31);
	if(name == "DirtB")return (32);
	if(name == "DirtC")return (33);
	if(name == "SandA")return (34);
	if(name == "SandB")return (35);
	if(name == "SandC")return (36);
	if(name == "SandD")return (37);
	if(name == "CliffEgyptianB")return (38);
	if(name == "SandDirt50")return (39);
	if(name == "SandDirt50b")return (40);
	if(name == "SnowA")return (41);
	if(name == "SnowB")return (42);
	if(name == "SnowGrass25")return (43);
	if(name == "SnowGrass50")return (44);
	if(name == "SnowGrass75")return (45);
	if(name == "SnowSand25")return (46);
	if(name == "SnowSand50")return (47);
	if(name == "SnowSand75")return (48);
	if(name == "CliffNorseB")return (49);
	if(name == "OlympusA")return (50);
	if(name == "OlympusB")return (51);
	if(name == "OlympusC")return (52);
	if(name == "OlympusTile")return (53);
	if(name == "TundraGrassA")return (54);
	if(name == "TundraGrassB")return (55);
	if(name == "TundraRockA")return (56);
	if(name == "TundraRockB")return (57);
	if(name == "MarshA")return (58);
	if(name == "MarshB")return (59);
	if(name == "MarshC")return (60);
	if(name == "MarshD")return (61);
	if(name == "MarshE")return (62);
	if(name == "MarshF")return (63);
	if(name == "EgyptianRoadA")return (64);
	if(name == "GreekRoadA")return (65);
	if(name == "NorseRoadA")return (66);
	if(name == "JungleRoadA")return (67);
	if(name == "PlainRoadA")return (68);
	if(name == "TundraRoadA")return (69);
	if(name == "CityTileA")return (70);
	if(name == "CityTileAtlantis")return (71);
	if(name == "CityTileAtlantisCoral")return (72);
	if(name == "CityTileWaterPool")return (73);
	if(name == "CityTileWaterEdgeA")return (74);
	if(name == "CityTileWaterEdgeB")return (75);
	if(name == "CityTileWaterEdgeEndA")return (76);
	if(name == "CityTileWaterEdgeEndB")return (77);
	if(name == "CityTileWaterEdgeEndC")return (78);
	if(name == "CityTileWaterEdgeEndD")return (79);
	if(name == "CityTileWaterCornerA")return (80);
	if(name == "CityTileWaterCornerB")return (81);
	if(name == "CityTileWaterCornerC")return (82);
	if(name == "CityTileWaterCornerD")return (83);
	if(name == "HadesBuildable1")return (84);
	if(name == "HadesBuildable2")return (85);
	if(name == "ForestFloorPalm")return (86);
	if(name == "ForestFloorPine")return (87);
	if(name == "ForestFloorPineSnow")return (88);
	if(name == "ForestFloorOak")return (89);
	if(name == "ForestFloorGaia")return (90);
	if(name == "ForestFloorSavannah")return (91);
	if(name == "ForestFloorDeadPine")return (92);
	if(name == "ForestFloorTundra")return (93);
	if(name == "ForestFloorMarsh")return (94);
	if(name == "ForestFloorJungle")return (95);
	if(name == "Water")return (0);
	if(name == "CliffA")return (0);
	if(name == "CliffGreekA")return (1);
	if(name == "CliffEgyptianA")return (2);
	if(name == "CliffNorseA")return (3);
	if(name == "CliffJungleA")return (4);
	if(name == "CliffPlainA")return (5);
	if(name == "Dam")return (6);
	if(name == "Hades3")return (7);
	if(name == "Hades5")return (8);
	if(name == "Hades6")return (9);
	if(name == "Hades7")return (10);
	if(name == "HadesCliff")return (11);
	if(name == "Hades4")return (12);
	if(name == "BlackRock")return (13);
	if(name == "UnderwaterRockA")return (0);
	if(name == "UnderwaterRockB")return (1);
	if(name == "UnderwaterRockC")return (2);
	if(name == "UnderwaterRockD")return (3);
	if(name == "UnderwaterRockE")return (4);
	if(name == "UnderwaterRockF")return (5);
	if(name == "UnderwaterIceA")return (6);
	if(name == "UnderwaterIceB")return (7);
	if(name == "UnderwaterIceC")return (8);
	if(name == "CoralA")return (9);
	if(name == "CoralB")return (10);
	if(name == "CoralC")return (11);
	if(name == "CoralC2")return (12);
	if(name == "CoralD")return (13);
	if(name == "CoralE")return (14);
	if(name == "CoralF")return (15);
	if(name == "ShorelineSandA")return (0);
	if(name == "ShorelineAegeanA")return (1);
	if(name == "ShorelineAegeanB")return (2);
	if(name == "ShorelineAegeanC")return (3);
	if(name == "ShorelineRedSeaA")return (4);
	if(name == "ShorelineRedSeaB")return (5);
	if(name == "ShorelineRedSeaC")return (6);
	if(name == "ShorelineNorwegianA")return (7);
	if(name == "ShorelineNorwegianB")return (8);
	if(name == "ShorelineNorwegianC")return (9);
	if(name == "ShorelineMediterraneanA")return (10);
	if(name == "ShorelineMediterraneanB")return (11);
	if(name == "ShorelineMediterraneanC")return (12);
	if(name == "ShorelineMediterraneanD")return (13);
	if(name == "ShorelineAtlanticA")return (14);
	if(name == "ShorelineAtlanticB")return (15);
	if(name == "ShorelineAtlanticC")return (16);
	if(name == "ShorelineTundraA")return (17);
	if(name == "ShorelineTundraB")return (18);
	if(name == "ShorelineTundraC")return (19);
	if(name == "ShorelineTundraD")return (20);
	if(name == "ShorelineJungleA")return (21);
	if(name == "ShorelineJungleB")return (22);
	if(name == "ShorelineJungleC")return (23);
	if(name == "ShorelinePlainA")return (24);
	if(name == "ShorelinePlainB")return (25);
	if(name == "ShorelinePlainC")return (26);
	if(name == "ShorelinePlainD")return (27);
	if(name == "RiverSandyA")return (28);
	if(name == "RiverSandyB")return (29);
	if(name == "RiverSandyC")return (30);
	if(name == "RiverSandyShallowA")return (31);
	if(name == "RiverGrassyA")return (32);
	if(name == "RiverGrassyB")return (33);
	if(name == "RiverGrassyC")return (34);
	if(name == "RiverIcyA")return (35);
	if(name == "RiverIcyB")return (36);
	if(name == "RiverIcyC")return (37);
	if(name == "RiverMarshA")return (38);
	if(name == "RiverMarshB")return (39);
	if(name == "RiverMarshC")return (40);
	if(name == "IceA")return (0);
	if(name == "IceB")return (1);
	if(name == "IceC")return (2);
	if(name == "MiningGround")return (3);
	if(name == "Black")return (4);
	if(name == "Hades1")return (5);
	if(name == "Hades2")return (6);
	if(name == "Hades4Passable")return (7);
	if(name == "Hades8")return (8);
	if(name == "Hades9")return (9);
}

void grantGodPowerNoRechargeNextPosition(int p = 0, string power = "", int count = 0) {
for(tempPowerTech = -1; > 1){}
for(tempPosition = -1; > 1){}
	if(power=="Animal Magnetism")tempPowerTech=227;
	if(power=="Audrey")tempPowerTech=407;
	if(power=="Barrage")tempPowerTech=546;
	if(power=="Blessing of Zeus")tempPowerTech=351;
	if(power=="Bolt")tempPowerTech=221;
	if(power=="Bronze")tempPowerTech=175;
	if(power=="Bronze XP05")tempPowerTech=457;
	if(power=="Call to Arms")tempPowerTech=547;
	if(power=="Cease Fire")tempPowerTech=147;
	if(power=="Cease Fire Nomad")tempPowerTech=376;
	if(power=="Change Caladria")tempPowerTech=464;
	if(power=="Change Chimera")tempPowerTech=463;
	if(power=="Change Cyclops")tempPowerTech=462;
	if(power=="Change Hydra")tempPowerTech=467;
	if(power=="Change Manticore")tempPowerTech=465;
	if(power=="Change Nemean")tempPowerTech=466;
	if(power=="Chaos")tempPowerTech=409;
	if(power=="Chicken Storm")tempPowerTech=388;
	if(power=="Citadel")tempPowerTech=232;
	if(power=="Create Gold")tempPowerTech=84;
	if(power=="Curse")tempPowerTech=229;
	if(power=="Earth Dragon")tempPowerTech=557;
	if(power=="Earthquake")tempPowerTech=239;
	if(power=="Eclipse")tempPowerTech=214;
	if(power=="Examination")tempPowerTech=550;
	if(power=="Flaming Weapons")tempPowerTech=223;
	if(power=="Flood")tempPowerTech=555;
	if(power=="Flood Weak")tempPowerTech=556;
	if(power=="Forest Fire")tempPowerTech=248;
	if(power=="Forest Fire SPC")tempPowerTech=594;
	if(power=="Frost")tempPowerTech=57;
	if(power=="Gaia Forest")tempPowerTech=418;
	if(power=="Gaia Forest SPC")tempPowerTech=505;
	if(power=="Geyser")tempPowerTech=552;
	if(power=="Goatunheim")tempPowerTech=391;
	if(power=="Great Hunt")tempPowerTech=146;
	if(power=="Healing Spring")tempPowerTech=228;
	if(power=="Heroize")tempPowerTech=439;
	if(power=="Hesperides")tempPowerTech=436;
	if(power=="Implode")tempPowerTech=442;
	if(power=="Inferno")tempPowerTech=558;
	if(power=="Journey")tempPowerTech=548;
	if(power=="Lightning Storm")tempPowerTech=42;
	if(power=="Locust Swarm")tempPowerTech=43;
	if(power=="Meteor")tempPowerTech=61;
	if(power=="Nidhogg")tempPowerTech=235;
	if(power=="Pestilence")tempPowerTech=249;
	if(power=="Plenty")tempPowerTech=236;
	if(power=="Prosperity")tempPowerTech=211;
	if(power=="Ragnorok")tempPowerTech=234;
	if(power=="Rain")tempPowerTech=156;
	if(power=="Recreation")tempPowerTech=543;
	if(power=="Restoration")tempPowerTech=134;
	if(power=="Reverse Time")tempPowerTech=406;
	if(power=="Reverse Wonder")tempPowerTech=434;
	if(power=="Sandstorm")tempPowerTech=231;
	if(power=="Seed of Gaia")tempPowerTech=485;
	if(power=="Sentinel")tempPowerTech=230;
	if(power=="Serpents")tempPowerTech=226;
	if(power=="Skeleton Power")tempPowerTech=129;
	if(power=="Snow Storm")tempPowerTech=172;
	if(power=="Son of Osiris")tempPowerTech=237;
	if(power=="SPCLightning Storm")tempPowerTech=468;
	if(power=="SPCMeteor")tempPowerTech=334;
	if(power=="Spiders")tempPowerTech=438;
	if(power=="Spy")tempPowerTech=222;
	if(power=="Tartarian Gate")tempPowerTech=419;
	if(power=="Timber Harvest")tempPowerTech=545;
	if(power=="TitanGate")tempPowerTech=444;
	if(power=="Tornado")tempPowerTech=44;
	if(power=="Tornado XP05")tempPowerTech=458;
	if(power=="Traitors")tempPowerTech=408;
	if(power=="Traitors SPC")tempPowerTech=491;
	if(power=="Tremor")tempPowerTech=414;
	if(power=="Tsunami")tempPowerTech=598;
	if(power=="Undermine")tempPowerTech=152;
	if(power=="Underworld Passage")tempPowerTech=133;
	if(power=="Uproot")tempPowerTech=553;
	if(power=="Uproot SPC")tempPowerTech=554;
	if(power=="Vision")tempPowerTech=220;
	if(power=="Volcano")tempPowerTech=410;
	if(power=="Vortex")tempPowerTech=431;
	if(power=="Walking Berry Bushes")tempPowerTech=389;
	if(power=="Walking Woods")tempPowerTech=233;
	if(power=="Water Damage")tempPowerTech=615;
	if(power=="Well of Urd")tempPowerTech=366;
	if(power=="Year of the Goat")tempPowerTech=544;
	if(tempPowerTech>=0){
		if(trGetGPData(p, 0, 0) == tempPowerTech)tempPosition=0;
		if(trGetGPData(p, 0, 1) == tempPowerTech)tempPosition=1;
		if(trGetGPData(p, 0, 2) == tempPowerTech)tempPosition=2;
		if(trGetGPData(p, 0, 3) == tempPowerTech)tempPosition=3;
		if(trGetGPData(p, 0, 4) == tempPowerTech)tempPosition=4;
		if(tempPosition>=0){
			trSetGPData(p, 5, tempPosition, 0 - trGetGPData(p, 5, tempPosition));
			trSetGPData(p, 1, tempPosition, count);
			trSetGPData(p, 2, tempPosition, 0 - trGetGPData(p, 2, tempPosition));
		} else {
			if((trGetGPData(p, 1, 0) > 0 || trGetGPData(p, 2, 0) > 0) == false){
				tempPosition=0;
			} else if((trGetGPData(p, 1, 1) > 0 || trGetGPData(p, 2, 1) > 0) == false){
				tempPosition=1;
			} else if((trGetGPData(p, 1, 2) > 0 || trGetGPData(p, 2, 2) > 0) == false){
				tempPosition=2;
			} else {
				tempPosition=3;
			}
			trTechGodPowerAtPosition(p, power, 0, tempPosition + 1);
			trSetGPData(p, 5, tempPosition, 0 - trGetGPData(p, 5, tempPosition));
			trSetGPData(p, 1, tempPosition, count - trGetGPData(p, 1, tempPosition) + trGetGPData(p, 2, tempPosition));
			trSetGPData(p, 2, tempPosition, 0 - trGetGPData(p, 2, tempPosition));
		}
	}
}

void GPSetRechargeTime(int p = 0, string power ="", int time = 1000) {
for(tempPowerTech = -1; > 1){}
for(tempPosition = -1; > 1){}
	if(power=="Animal Magnetism")tempPowerTech=227;
	if(power=="Audrey")tempPowerTech=407;
	if(power=="Barrage")tempPowerTech=546;
	if(power=="Blessing of Zeus")tempPowerTech=351;
	if(power=="Bolt")tempPowerTech=221;
	if(power=="Bronze")tempPowerTech=175;
	if(power=="Bronze XP05")tempPowerTech=457;
	if(power=="Call to Arms")tempPowerTech=547;
	if(power=="Cease Fire")tempPowerTech=147;
	if(power=="Cease Fire Nomad")tempPowerTech=376;
	if(power=="Change Caladria")tempPowerTech=464;
	if(power=="Change Chimera")tempPowerTech=463;
	if(power=="Change Cyclops")tempPowerTech=462;
	if(power=="Change Hydra")tempPowerTech=467;
	if(power=="Change Manticore")tempPowerTech=465;
	if(power=="Change Nemean")tempPowerTech=466;
	if(power=="Chaos")tempPowerTech=409;
	if(power=="Chicken Storm")tempPowerTech=388;
	if(power=="Citadel")tempPowerTech=232;
	if(power=="Create Gold")tempPowerTech=84;
	if(power=="Curse")tempPowerTech=229;
	if(power=="Earth Dragon")tempPowerTech=557;
	if(power=="Earthquake")tempPowerTech=239;
	if(power=="Eclipse")tempPowerTech=214;
	if(power=="Examination")tempPowerTech=550;
	if(power=="Flaming Weapons")tempPowerTech=223;
	if(power=="Flood")tempPowerTech=555;
	if(power=="Flood Weak")tempPowerTech=556;
	if(power=="Forest Fire")tempPowerTech=248;
	if(power=="Forest Fire SPC")tempPowerTech=594;
	if(power=="Frost")tempPowerTech=57;
	if(power=="Gaia Forest")tempPowerTech=418;
	if(power=="Gaia Forest SPC")tempPowerTech=505;
	if(power=="Geyser")tempPowerTech=552;
	if(power=="Goatunheim")tempPowerTech=391;
	if(power=="Great Hunt")tempPowerTech=146;
	if(power=="Healing Spring")tempPowerTech=228;
	if(power=="Heroize")tempPowerTech=439;
	if(power=="Hesperides")tempPowerTech=436;
	if(power=="Implode")tempPowerTech=442;
	if(power=="Inferno")tempPowerTech=558;
	if(power=="Journey")tempPowerTech=548;
	if(power=="Lightning Storm")tempPowerTech=42;
	if(power=="Locust Swarm")tempPowerTech=43;
	if(power=="Meteor")tempPowerTech=61;
	if(power=="Nidhogg")tempPowerTech=235;
	if(power=="Pestilence")tempPowerTech=249;
	if(power=="Plenty")tempPowerTech=236;
	if(power=="Prosperity")tempPowerTech=211;
	if(power=="Ragnorok")tempPowerTech=234;
	if(power=="Rain")tempPowerTech=156;
	if(power=="Recreation")tempPowerTech=543;
	if(power=="Restoration")tempPowerTech=134;
	if(power=="Reverse Time")tempPowerTech=406;
	if(power=="Reverse Wonder")tempPowerTech=434;
	if(power=="Sandstorm")tempPowerTech=231;
	if(power=="Seed of Gaia")tempPowerTech=485;
	if(power=="Sentinel")tempPowerTech=230;
	if(power=="Serpents")tempPowerTech=226;
	if(power=="Skeleton Power")tempPowerTech=129;
	if(power=="Snow Storm")tempPowerTech=172;
	if(power=="Son of Osiris")tempPowerTech=237;
	if(power=="SPCLightning Storm")tempPowerTech=468;
	if(power=="SPCMeteor")tempPowerTech=334;
	if(power=="Spiders")tempPowerTech=438;
	if(power=="Spy")tempPowerTech=222;
	if(power=="Tartarian Gate")tempPowerTech=419;
	if(power=="Timber Harvest")tempPowerTech=545;
	if(power=="TitanGate")tempPowerTech=444;
	if(power=="Tornado")tempPowerTech=44;
	if(power=="Tornado XP05")tempPowerTech=458;
	if(power=="Traitors")tempPowerTech=408;
	if(power=="Traitors SPC")tempPowerTech=491;
	if(power=="Tremor")tempPowerTech=414;
	if(power=="Tsunami")tempPowerTech=598;
	if(power=="Undermine")tempPowerTech=152;
	if(power=="Underworld Passage")tempPowerTech=133;
	if(power=="Uproot")tempPowerTech=553;
	if(power=="Uproot SPC")tempPowerTech=554;
	if(power=="Vision")tempPowerTech=220;
	if(power=="Volcano")tempPowerTech=410;
	if(power=="Vortex")tempPowerTech=431;
	if(power=="Walking Berry Bushes")tempPowerTech=389;
	if(power=="Walking Woods")tempPowerTech=233;
	if(power=="Water Damage")tempPowerTech=615;
	if(power=="Well of Urd")tempPowerTech=366;
	if(power=="Year of the Goat")tempPowerTech=544;
	if(tempPowerTech>=0){
		if(trGetGPData(p, 0, 0) == tempPowerTech)tempPosition=0;
		if(trGetGPData(p, 0, 1) == tempPowerTech)tempPosition=1;
		if(trGetGPData(p, 0, 2) == tempPowerTech)tempPosition=2;
		if(trGetGPData(p, 0, 3) == tempPowerTech)tempPosition=3;
		if(trGetGPData(p, 0, 4) == tempPowerTech)tempPosition=4;
		if(tempPosition>=0){
			if(false){
				trSetGPData(p, 5, tempPosition, time);
			} else {
				trSetGPData(p, 5, tempPosition, time - trGetGPData(p, 5, tempPosition));
			}
		}
	}
}


void refreshPassability(){
	trPaintTerrain(0, 0, 0, 0, trGetTerrainType(0, 0), trGetTerrainSubType(0, 0), true);
}

void characterDialog(string character = "", string message = "", string portrait = ""){
	trSoundPlayFN("","1",-1,""+character+":"+message,portrait);
}

void modifyProtounitAbsolute(string protounit = "", int p = 0, int field = 0, float value = 0.0){
	if(field == 6){
		trModifyProtounit(protounit, p, field, -9999999999999999999.0);
		trModifyProtounit(protounit, p, field, value);
	} else if(field == 5 || field == 7 || field == 10 || field == 13){
		trModifyProtounit(protounit, p, field, 2147483648.0);
		trModifyProtounit(protounit, p, field, 2147483648.0);
		trModifyProtounit(protounit, p, field, value);
	} else {
		trModifyProtounit(protounit, p, field, 9999999999999999999.0);
		trModifyProtounit(protounit, p, field, -9999999999999999999.0);
		trModifyProtounit(protounit, p, field, value);
	}
}

void paintShopSquare(int posX = 0, int PosZ = 0, string terrain = ""){
	int terrainType = getTerrainType(terrain);
	int terrainSubType = getTerrainSubType(terrain);
	trPaintTerrain(posX+1, PosZ+1, posX+1, PosZ+1, 0, 80, false);
	trPaintTerrain(posX+1, PosZ, posX+1, PosZ, 0, 74, false);
	trPaintTerrain(posX+1, PosZ-1, posX+1, PosZ-1, 0, 81, false);
	trPaintTerrain(posX, PosZ-1, posX, PosZ-1, 0, 75, false);
	trPaintTerrain(posX-1, PosZ-1, posX-1, PosZ-1, 0, 82, false);
	trPaintTerrain(posX-1, PosZ, posX-1, PosZ, 0, 74, false);
	trPaintTerrain(posX-1, PosZ+1, posX-1, PosZ+1, 0, 83, false);
	trPaintTerrain(posX, PosZ+1, posX, PosZ+1, 0, 75, false);
	trPaintTerrain(posX, PosZ, posX, PosZ, terrainType, terrainSubType, false);
}

/*
void setupProto(string displayname = "", string protounitname = "",
	int goldCost = 0, int incomeChange = 0, string desc = "", int bounty = 0,
	int attacker = 0) {
	int id = trQuestVarGet("BlueprintCount");
	trStringQuestVarSet("proto"+id+"displayname", displayname);
	trStringQuestVarSet("proto"+id+"protounitname", protounitname);
	trQuestVarSet("proto"+id+"goldCost", goldCost);
	trQuestVarSet("proto"+id+"incomeChange", incomeChange);
	trStringQuestVarSet("proto"+id+"desc", desc);
	trQuestVarSet("proto"+id+"bounty", bounty);
	trQuestVarSet("proto"+id+"attacker", attacker);
	
	trQuestVarSet("blueprint"+1*trQuestVarGet("blueprintCount"), id);
	trQuestVarSet("blueprintCount", 1 + trQuestVarGet("blueprintCount"));
}
*/

void CounterShow(int xx = 0){
	string colourString = "<color={PlayerColor("+xx+")}>";
	string incomeString = "Income: "+1*trQuestVarGet("P"+xx+"Income")+" | Lives: "+1*trQuestVarGet("P"+xx+"Lives");
	string LivesString = ""+1*trQuestVarGet("P"+xx+"Lives")+" | "+1*trQuestVarGet("P"+xx+"Lives");
	string iconString = "<icon=(16)(icons/icon resource wood)>";
	trSetCounterDisplay(colourString+incomeString);
}

void ColouredTimer(int c = 0, string text = "", int time = 0, string name = "countdown", int eventID = -1){
	string colourString = "<color={PlayerColor("+c+")}>";
	trCounterAddTime(name, time, 0, colourString + text, eventID);
}

void ColouredIconTimer(int c = 0, string icon ="", string text = "", int time = 0,
	string name = "countdown", int eventID = -1){
	string colourString = "<color={PlayerColor("+c+")}>";
	string iconString = "<icon=(20)("+icon+")>";
	trCounterAddTime(name, time, 0, colourString + iconString + text, eventID);
}

void OverlayTextPlayerColor(int p = 0){
	if(p == 0)trOverlayTextColour(153, 102, 0);
	if(p == 1)trOverlayTextColour(50, 50, 255);
	if(p == 2)trOverlayTextColour(255, 50, 50);
	if(p == 3)trOverlayTextColour(0, 150, 0);
	if(p == 4)trOverlayTextColour(50, 235, 255);
	if(p == 5)trOverlayTextColour(223, 52, 238);
	if(p == 6)trOverlayTextColour(255, 255, 0);
	if(p == 7)trOverlayTextColour(255, 102, 0);
	if(p == 8)trOverlayTextColour(128, 0, 64);
	if(p == 9)trOverlayTextColour(50, 255, 50);
	if(p == 10)trOverlayTextColour(179, 251, 186);
	if(p == 11)trOverlayTextColour(80, 80, 80);
	if(p == 12)trOverlayTextColour(255, 0, 102);
}

void UnitCreate(int xplayerx = 0, string protounitname = "", int xx = 0, int zz = 0, int xheadingx = 0){
	trQuestVarSet("CreatingU", trGetNextUnitScenarioNameNumber());
	trArmyDispatch(""+xplayerx+",0", "Dwarf", 1, xx, 0, zz, xheadingx, true);
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("CreatingU"));
	trMutateSelected(kbGetProtoUnitID(""+protounitname+""));
}

void FloatingUnit(string protounitname="", int xx = 0, int yy = 0, int zz = 0, int xheadingx = 0,
	float scalex = 1, float scaley = 1, float scalez = 1){
	//trArmyDispatch("0,0", "Revealer", 1, xx, yy, zz, xheadingx, true);
	trQuestVarSet("BuildID", trQuestVarGet("BuildID") + 1);
	trQuestVarSet("QVHero"+(1*trQuestVarGet("BuildID"))+"", trGetNextUnitScenarioNameNumber());
	trQuestVarSet("QVHero", trGetNextUnitScenarioNameNumber());
	trArmyDispatch("0,0", "Dwarf", 1, xx, yy, zz, xheadingx, true);
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVHero"));
	trUnitChangeProtoUnit("Amanra");
	trQuestVarSet("QVRelic"+(1*trQuestVarGet("BuildID"))+"", trGetNextUnitScenarioNameNumber());
	trQuestVarSet("QVRelic", trGetNextUnitScenarioNameNumber());
	trArmyDispatch("0,0", "Relic", 1, xx, yy, zz, trQuestVarGet("Heading"+(1*trQuestVarGet("Build"))+""), true);
	trQuestVarCopy("QVHero", "QVHero"+(1*trQuestVarGet("BuildID"))+"");
	trVectorQuestVarSet("V1", kbGetBlockPosition("0"));
	trVectorQuestVarSet("V1", xsVectorSet(trVectorQuestVarGetX("V1") + xx,
			yy,trVectorQuestVarGetZ("V1") + zz));
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVRelic"));
	trImmediateUnitGarrison(""+(1*trQuestVarGet("QVHero"))+"");
	trMutateSelected(kbGetProtoUnitID(""+protounitname+""));
	trUnitSelectClear();
	//unitTransform("Relic",""+protounitname+"");
	trUnitSelect(""+1*trQuestVarGet("QVHero"), true);
	trMutateSelected(kbGetProtoUnitID("Wadjet Spit"));
	trQuestVarSet("Build", trQuestVarGet("Build") - 1);
	trUnitTeleport(trVectorQuestVarGetX("V1"),trVectorQuestVarGetY("V1"),trVectorQuestVarGetZ("V1"));
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVRelic"), true);
	trSetSelectedScale(scalex, scaley, scalez);
	trUnitSetAnimationPath("1,0,0,0,0");
}

void FloatingUnitAnim(string protounitname="", int xx = 0, int yy = 0, int zz = 0, int xheadingx = 0,
	float scalex = 1, float scaley = 1, float scalez = 1, string anim="0,0,0,0,0"){
	trArmyDispatch("0,0", "Revealer", 1, xx, yy, zz, xheadingx, true);
	trQuestVarSet("BuildID", trQuestVarGet("BuildID") + 1);
	trQuestVarSet("QVHero"+(1*trQuestVarGet("BuildID"))+"", trGetNextUnitScenarioNameNumber());
	trQuestVarSet("QVHero", trGetNextUnitScenarioNameNumber());
	trArmyDispatch("0,0", "Dwarf", 1, xx, yy, zz, xheadingx, true);
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVHero"));
	trUnitChangeProtoUnit("Amanra");
	trQuestVarSet("QVRelic"+(1*trQuestVarGet("BuildID"))+"", trGetNextUnitScenarioNameNumber());
	trQuestVarSet("QVRelic", trGetNextUnitScenarioNameNumber());
	trArmyDispatch("0,0", "Relic", 1, xx, yy, zz, trQuestVarGet("Heading"+(1*trQuestVarGet("Build"))+""), true);
	trQuestVarCopy("QVHero", "QVHero"+(1*trQuestVarGet("BuildID"))+"");
	trVectorQuestVarSet("V1", kbGetBlockPosition("0"));
	trVectorQuestVarSet("V1", xsVectorSet(trVectorQuestVarGetX("V1") + xx,
			yy,trVectorQuestVarGetZ("V1") + zz));
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVRelic"));
	trImmediateUnitGarrison(""+(1*trQuestVarGet("QVHero"))+"");
	trMutateSelected(kbGetProtoUnitID(""+protounitname+""));
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVHero"), true);
	trMutateSelected(kbGetProtoUnitID("Wadjet Spit"));
	trQuestVarSet("Build", trQuestVarGet("Build") - 1);
	trUnitTeleport(trVectorQuestVarGetX("V1"),trVectorQuestVarGetY("V1"),trVectorQuestVarGetZ("V1"));
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVRelic"), true);
	trSetSelectedScale(scalex, scaley, scalez);
	trUnitSetAnimationPath(""+anim+"");
}

void FloatingUnitAnimNoLOS(string protounitname="", int xx = 0, int yy = 0, int zz = 0, int xheadingx = 0,
	float scalex = 1, float scaley = 1, float scalez = 1, string anim="0,0,0,0,0"){
	trQuestVarSet("BuildID", trQuestVarGet("BuildID") + 1);
	trQuestVarSet("QVHero"+(1*trQuestVarGet("BuildID"))+"", trGetNextUnitScenarioNameNumber());
	trQuestVarSet("QVHero", trGetNextUnitScenarioNameNumber());
	trArmyDispatch("0,0", "Flying Medic", 1, xx, yy, zz, xheadingx, true);
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVHero"));
	trUnitChangeProtoUnit("Amanra");
	trQuestVarSet("QVRelic"+(1*trQuestVarGet("BuildID"))+"", trGetNextUnitScenarioNameNumber());
	trQuestVarSet("QVRelic", trGetNextUnitScenarioNameNumber());
	trArmyDispatch("0,0", "Relic", 1, xx, yy, zz, trQuestVarGet("Heading"+(1*trQuestVarGet("Build"))+""), true);
	trQuestVarCopy("QVHero", "QVHero"+(1*trQuestVarGet("BuildID"))+"");
	trVectorQuestVarSet("V1", kbGetBlockPosition("0"));
	trVectorQuestVarSet("V1", xsVectorSet(trVectorQuestVarGetX("V1") + xx,
			yy,trVectorQuestVarGetZ("V1") + zz));
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVRelic"));
	trImmediateUnitGarrison(""+(1*trQuestVarGet("QVHero"))+"");
	trMutateSelected(kbGetProtoUnitID(""+protounitname+""));
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVHero"), true);
	trMutateSelected(kbGetProtoUnitID("Wadjet Spit"));
	trQuestVarSet("Build", trQuestVarGet("Build") - 1);
	trUnitTeleport(trVectorQuestVarGetX("V1"),trVectorQuestVarGetY("V1"),trVectorQuestVarGetZ("V1"));
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVRelic"), true);
	trSetSelectedScale(scalex, scaley, scalez);
	trUnitSetAnimationPath(""+anim+"");
}

void FloatingUnitAnimCiv(string protounitname="", int xx = 0, int yy = 0, int zz = 0, int xheadingx = 0,
	float scalex = 1, float scaley = 1, float scalez = 1, string anim="0,0,0,0,0"){
	trArmyDispatch("0,0", "Revealer", 1, xx, yy, zz, xheadingx, true);
	trQuestVarSet("BuildID", trQuestVarGet("BuildID") + 1);
	trQuestVarSet("QVHero"+(1*trQuestVarGet("BuildID"))+"", trGetNextUnitScenarioNameNumber());
	trQuestVarSet("QVHero", trGetNextUnitScenarioNameNumber());
	trArmyDispatch("0,0", "Revealer", 1, xx, yy, zz, xheadingx, true);
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVHero"));
	trUnitChangeProtoUnit("Amanra");
	trQuestVarSet("QVRelic"+(1*trQuestVarGet("BuildID"))+"", trGetNextUnitScenarioNameNumber());
	trQuestVarSet("QVRelic", trGetNextUnitScenarioNameNumber());
	trArmyDispatch("0,0", "Relic", 1, xx, yy, zz, trQuestVarGet("Heading"+(1*trQuestVarGet("Build"))+""), true);
	trQuestVarCopy("QVHero", "QVHero"+(1*trQuestVarGet("BuildID"))+"");
	trVectorQuestVarSet("V1", kbGetBlockPosition("0"));
	trVectorQuestVarSet("V1", xsVectorSet(trVectorQuestVarGetX("V1") + xx,
			trVectorQuestVarGetY("V1") + yy,trVectorQuestVarGetZ("V1") + zz));
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVRelic"));
	trImmediateUnitGarrison(""+(1*trQuestVarGet("QVHero"))+"");
	trMutateSelected(kbGetProtoUnitID(""+protounitname+""));
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVHero"), true);
	trMutateSelected(kbGetProtoUnitID("Wadjet Spit"));
	trQuestVarSet("Build", trQuestVarGet("Build") - 1);
	trUnitTeleport(trVectorQuestVarGetX("V1"),trVectorQuestVarGetY("V1"),trVectorQuestVarGetZ("V1"));
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVRelic"), true);
	trSetSelectedScale(scalex, scaley, scalez);
}

void FloatingUnitAnim4(string protounitname="", int xx = 0, int yy = 0, int zz = 0, int xheadingx = 0,
	float scalex = 1, float scaley = 1, float scalez = 1, string anim="0,0,0,0,0", int p = 0){
	trArmyDispatch(""+p+",0", "Revealer", 1, xx, yy, zz, xheadingx, true);
	trQuestVarSet("BuildID", trQuestVarGet("BuildID") + 1);
	trQuestVarSet("QVHero"+(1*trQuestVarGet("BuildID"))+"", trGetNextUnitScenarioNameNumber());
	trQuestVarSet("QVHero", trGetNextUnitScenarioNameNumber());
	trArmyDispatch(""+p+",0", "Flying Medic", 1, xx, yy, zz, xheadingx, true);
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVHero"));
	trUnitChangeProtoUnit("Amanra");
	trQuestVarSet("QVRelic"+(1*trQuestVarGet("BuildID"))+"", trGetNextUnitScenarioNameNumber());
	trQuestVarSet("QVRelic", trGetNextUnitScenarioNameNumber());
	trArmyDispatch(""+p+",0", "Relic", 1, xx, yy, zz, trQuestVarGet("Heading"+(1*trQuestVarGet("Build"))+""), true);
	trQuestVarCopy("QVHero", "QVHero"+(1*trQuestVarGet("BuildID"))+"");
	trVectorQuestVarSet("V1", kbGetBlockPosition("0"));
	trVectorQuestVarSet("V1", xsVectorSet(trVectorQuestVarGetX("V1") + xx,
			yy,trVectorQuestVarGetZ("V1") + zz));
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVRelic"));
	trImmediateUnitGarrison(""+(1*trQuestVarGet("QVHero"))+"");
	trMutateSelected(kbGetProtoUnitID(""+protounitname+""));
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVHero"), true);
	trMutateSelected(kbGetProtoUnitID("Wadjet Spit"));
	trQuestVarSet("Build", trQuestVarGet("Build") - 1);
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVRelic"), true);
	trSetSelectedScale(scalex, scaley, scalez);
	trUnitSetAnimationPath(""+anim+"");
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVHero"), true);
	trUnitTeleport(trVectorQuestVarGetX("V1"),yy,trVectorQuestVarGetZ("V1"));
}

void FloatingUnitAnim5(string protounitname="", int xx = 0, int yy = 0, int zz = 0, int xheadingx = 0,
	float scalex = 1, float scaley = 1, float scalez = 1, string anim="0,0,0,0,0", int p = 0){
	trArmyDispatch(""+p+",0", "Revealer", 1, xx, yy, zz, xheadingx, true);
	trQuestVarSet("BuildID", trQuestVarGet("BuildID") + 1);
	trQuestVarSet("QVHero"+(1*trQuestVarGet("BuildID"))+"", trGetNextUnitScenarioNameNumber());
	trQuestVarSet("QVHero", trGetNextUnitScenarioNameNumber());
	trArmyDispatch(""+p+",0", "Flying Medic", 1, xx, yy, zz, xheadingx, true);
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVHero"));
	trUnitChangeProtoUnit("Amanra");
	trQuestVarSet("QVRelic"+(1*trQuestVarGet("BuildID"))+"", trGetNextUnitScenarioNameNumber());
	trQuestVarSet("QVRelic", trGetNextUnitScenarioNameNumber());
	trArmyDispatch(""+p+",0", "Relic", 1, xx, yy, zz, trQuestVarGet("Heading"+(1*trQuestVarGet("Build"))+""), true);
	trQuestVarCopy("QVHero", "QVHero"+(1*trQuestVarGet("BuildID"))+"");
	trVectorQuestVarSet("V1", xsVectorSet(xx, yy, zz));
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVRelic"));
	trImmediateUnitGarrison(""+(1*trQuestVarGet("QVHero"))+"");
	trMutateSelected(kbGetProtoUnitID(""+protounitname+""));
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVHero"), true);
	trMutateSelected(kbGetProtoUnitID("Wadjet Spit"));
	trQuestVarSet("Build", trQuestVarGet("Build") - 1);
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVRelic"), true);
	trSetSelectedScale(scalex, scaley, scalez);
	trUnitSetAnimationPath(""+anim+"");
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVHero"), true);
	trUnitTeleport(trVectorQuestVarGetX("V1"),trVectorQuestVarGetY("V1"),trVectorQuestVarGetZ("V1"));
}

void FloatingUnitAnim2(string protounitname="", int xx = 0, int yy = 0, int zz = 0, int xheadingx = 0,
	float scalex = 1, float scaley = 1, float scalez = 1, string anim="0,0,0,0,0"){
	trArmyDispatch("0,0", "Revealer", 1, xx, yy, zz, xheadingx, true);
	trQuestVarSet("BuildID", trQuestVarGet("BuildID") + 1);
	trQuestVarSet("QVHero"+(1*trQuestVarGet("BuildID"))+"", trGetNextUnitScenarioNameNumber());
	trQuestVarSet("QVHero", trGetNextUnitScenarioNameNumber());
	trArmyDispatch("0,0", "Flying Medic", 1, 50, yy, 50, xheadingx, true);
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVHero"));
	trUnitChangeProtoUnit("Amanra");
	trQuestVarSet("QVRelic"+(1*trQuestVarGet("BuildID"))+"", trGetNextUnitScenarioNameNumber());
	trQuestVarSet("QVRelic", trGetNextUnitScenarioNameNumber());
	trArmyDispatch("0,0", "Relic", 1, 50, yy, 50, trQuestVarGet("Heading"+(1*trQuestVarGet("Build"))+""), true);
	trQuestVarCopy("QVHero", "QVHero"+(1*trQuestVarGet("BuildID"))+"");
	trVectorQuestVarSet("V1", kbGetBlockPosition("0"));
	trVectorQuestVarSet("V1", xsVectorSet(trVectorQuestVarGetX("V1") + xx,
			trVectorQuestVarGetY("V1") + yy,trVectorQuestVarGetZ("V1") + zz));
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVRelic"));
	trImmediateUnitGarrison(""+(1*trQuestVarGet("QVHero"))+"");
	trMutateSelected(kbGetProtoUnitID(""+protounitname+""));
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVHero"), true);
	trMutateSelected(kbGetProtoUnitID("Wadjet Spit"));
	trQuestVarSet("Build", trQuestVarGet("Build") - 1);
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVRelic"), true);
	trSetSelectedScale(scalex, scaley, scalez);
	trUnitSetAnimationPath(""+anim+"");
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVHero"), true);
	trUnitTeleport(trVectorQuestVarGetX("V1"),trVectorQuestVarGetY("V1"),trVectorQuestVarGetZ("V1"));
}

void FloatingUnitAnimIdle(string protounitname="", int xx = 0, int yy = 0, int zz = 0, int xheadingx = 0,
	float scalex = 1, float scaley = 1, float scalez = 1, string anim="0,0,0,0,0", int animtype = 2){
	trArmyDispatch("0,0", "Revealer", 1, xx, yy, zz, xheadingx, true);
	trQuestVarSet("BuildID", trQuestVarGet("BuildID") + 1);
	trQuestVarSet("QVHero"+(1*trQuestVarGet("BuildID"))+"", trGetNextUnitScenarioNameNumber());
	trQuestVarSet("QVHero", trGetNextUnitScenarioNameNumber());
	trArmyDispatch("0,0", "Flying Medic", 1, xx, yy, zz, xheadingx, true);
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVHero"));
	trUnitChangeProtoUnit("Amanra");
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVHero"));
	trUnitOverrideAnimation(animtype, 0, true, true, -1, 0);
	trQuestVarSet("QVRelic"+(1*trQuestVarGet("BuildID"))+"", trGetNextUnitScenarioNameNumber());
	trQuestVarSet("QVRelic", trGetNextUnitScenarioNameNumber());
	trArmyDispatch("0,0", "Ajax", 1, xx, yy, zz, trQuestVarGet("Heading"+(1*trQuestVarGet("Build"))+""), true);
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVRelic"));
	trUnitOverrideAnimation(animtype, 0, true, true, -1, 0);
	trMutateSelected(kbGetProtoUnitID("Relic"));
	trQuestVarCopy("QVHero", "QVHero"+(1*trQuestVarGet("BuildID"))+"");
	trVectorQuestVarSet("V1", kbGetBlockPosition("0"));
	trVectorQuestVarSet("V1", xsVectorSet(trVectorQuestVarGetX("V1") + xx,
			yy,trVectorQuestVarGetZ("V1") + zz));
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVRelic"));
	trImmediateUnitGarrison(""+(1*trQuestVarGet("QVHero"))+"");
	trMutateSelected(kbGetProtoUnitID(""+protounitname+""));
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVHero"), true);
	trMutateSelected(kbGetProtoUnitID("Wadjet Spit"));
	trQuestVarSet("Build", trQuestVarGet("Build") - 1);
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVRelic"), true);
	trSetSelectedScale(scalex, scaley, scalez);
	trUnitSetAnimationPath(""+anim+"");
	trUnitSelectClear();
	trUnitSelect(""+1*trQuestVarGet("QVHero"), true);
	trUnitTeleport(trVectorQuestVarGetX("V1"),trVectorQuestVarGetY("V1"),trVectorQuestVarGetZ("V1"));
}

/*
void trQuestVarModify(string qv = "", string operation = "", float value = 0){
	trQuestVarSet(""+qv+"", trQuestVarGet(""+qv+"") "+operation+" "+value+");
}
*/

void paintTreesSlow(string terrain = "", string tree = "", int xmin = 0, int zmin = 0, int xmax = 0, int zmax = 0){
	int terrainType = getTerrainType(terrain);
	int terrainSubType = getTerrainSubType(terrain);
	trPaintTerrain(xmin, zmin, xmax, zmax, terrainType, terrainSubType, false);
	for (x=xmax; >= xmin) {
		for (z=zmax; >= zmin) {
			trQuestVarSetFromRand("heading", 0, 359, true);
			trArmyDispatch("0,0", "Victory Marker", 1, x*2, 5.00, z*2, 1*trQuestVarGet("Heading"), false);
		}
	}
	trUnitSelectClear();
	trUnitSelect("0");
	trUnitChangeInArea(0, 0, "Victory Marker", tree, 999.0);
}

void trQuestVarModify(string QV = "", string Operator = "", int number = 0){
	if(Operator == "+"){
		trQuestVarSet(QV, 1*trQuestVarGet(QV) + number);
	}
	else if(Operator == "-"){
		trQuestVarSet(QV, 1*trQuestVarGet(QV) - number);
	}
	else if(Operator == "*"){
		trQuestVarSet(QV, 1*trQuestVarGet(QV) * number);
	}
	else if(Operator == "/"){
		trQuestVarSet(QV, 1*trQuestVarGet(QV) / number);
	}
}
void trPaintTerrainCircle(int posX = 0, int PosZ = 0, int irad = 0, int type = 0, int subtype = 0){
for(tempType = -1; > 1){}
for(tempSubType = -1; > 1){}
for(tempMinX = 0; > 1){}
for(tempMinZ = 0; > 1){}
for(tempMaxX = 0; > 1){}
for(tempMaxZ = 0; > 1){}
for(tempX = 0; > 1){}
for(tempZ = 0; > 1){}
for(tempRadiusCheck = 0; > 1){}
for(tempOldContextPlayer = 0; > 1){}
	tempMinX = xsMax(0.0 - posX, -1*irad );
	tempMinZ = xsMax(0.0 - PosZ, -1*irad );
	tempOldContextPlayer = xsGetContextPlayer();
	xsSetContextPlayer(0);
	tempMaxX = xsMin(kbGetMapXSize() / 2 - posX - 1, irad );
	tempMaxZ = xsMin(kbGetMapZSize() / 2 - PosZ - 1, irad );
	xsSetContextPlayer(tempOldContextPlayer);
	tempRadiusCheck = irad  * irad  + irad ;
	for(tempZ = tempMaxZ; >= tempMinZ){
		for(tempX = tempMaxX; >= tempMinX){
			if(tempRadiusCheck > (tempX*tempX + tempZ*tempZ)){
				trPaintTerrain(tempX + posX, tempZ + PosZ, tempX + posX, tempZ + PosZ, type, subtype, false);
			}
		}
	}
}

void trPaintTerrainCircleOutline(int posX = 0, int PosZ = 0, int irad = 0, int type = 0, int subtype = 0){
for(tempType = -1; > 1){}
for(tempSubType = -1; > 1){}
for(tempMinX = 0; > 1){}
for(tempMinZ = 0; > 1){}
for(tempMaxX = 0; > 1){}
for(tempMaxZ = 0; > 1){}
for(tempX = 0; > 1){}
for(tempZ = 0; > 1){}
for(tempRadiusCheck = 0; > 1){}
for(tempOldContextPlayer = 0; > 1){}
	tempMinX = xsMax(0.0 - posX, -1*irad );
	tempMinZ = xsMax(0.0 - PosZ, -1*irad );
	tempOldContextPlayer = xsGetContextPlayer();
	xsSetContextPlayer(0);
	tempMaxX = xsMin(kbGetMapXSize() / 2 - posX - 1, irad );
	tempMaxZ = xsMin(kbGetMapZSize() / 2 - PosZ - 1, irad );
	xsSetContextPlayer(tempOldContextPlayer);
	tempRadiusCheck = irad  * irad  + irad ;
	for(tempZ = tempMaxZ; >= tempMinZ){
		for(tempX = tempMaxX; >= tempMinX){
			if(tempRadiusCheck <= (tempX*tempX + tempZ*tempZ)){
				trPaintTerrain(tempX + posX, tempZ + PosZ, tempX + posX, tempZ + PosZ, type, subtype, false);
			}
		}
	}
}

//MAP SIZE
void replaceCircle(int posX = 0, int PosZ = 0, int radius = 0, string oldTerrain = "", string newTerrain = ""){
	int oldTerrainType = getTerrainType(oldTerrain);
	int oldTerrainSubType = getTerrainSubType(oldTerrain);
	int newTerrainType = getTerrainType(newTerrain);
	int newTerrainSubType = getTerrainSubType(newTerrain);
	int tempMinX = xsMax(0.0 - posX, 0.0 - radius);
	int tempMinZ = xsMax(0.0 - PosZ, 0.0 - radius);
	int tempMaxX = xsMin(200 - posX, radius);
	int tempMaxZ = xsMin(200 - PosZ, radius);
	int tempRadiusCheck = radius * radius + radius;
	for(tempZ = tempMaxZ; >= tempMinZ){
		for(tempX = tempMaxX; >= tempMinX){
			if(tempRadiusCheck >= (tempX*tempX + tempZ*tempZ)){
				int terrainType = trGetTerrainType(tempX + posX, tempZ + PosZ);
				int terrainSubType = trGetTerrainSubType(tempX + posX, tempZ + PosZ);
				if(terrainType == oldTerrainType && terrainSubType == oldTerrainSubType){
					trPaintTerrain(tempX + posX, tempZ + PosZ, tempX + posX, tempZ + PosZ, newTerrainType, newTerrainSubType, false);
				}
			}
		}
	}
}

void trPaintElevationCircle(int PosX = 0, int PosZ = 0, int Rad = 0, int Height = 0){
for(tempMinX = 0; > 1){}
for(tempMinZ = 0; > 1){}
for(tempMaxX = 0; > 1){}
for(tempMaxZ = 0; > 1){}
for(tempRadiusCheck = 0; > 1){}
for(tempLocX = 0; > 1){}
for(tempLocZ = 0; > 1){}
for(tempOldContextPlayer = 0; > 1){}
	tempMinX = xsMax(0.0 - PosX, -1*Rad);
	tempMinZ = xsMax(0.0 - PosZ, -1*Rad);
	tempOldContextPlayer = xsGetContextPlayer();
	xsSetContextPlayer(0);
	tempMaxX = xsMin(kbGetMapXSize() / 2 - PosX, Rad);
	tempMaxZ = xsMin(kbGetMapZSize() / 2 - PosZ, Rad);
	xsSetContextPlayer(tempOldContextPlayer);
	tempRadiusCheck = Rad * Rad + Rad;
	if(false){
		for(tempZ = tempMaxZ; >= tempMinZ){
			for(tempX = tempMaxX; >= tempMinX){
				if(tempRadiusCheck > (tempX*tempX + tempZ*tempZ)){
					tempLocX = tempX + PosX;
					tempLocZ = tempZ + PosZ;
					trChangeTerrainHeight(tempLocX, tempLocZ, tempLocX, tempLocZ, trGetTerrainHeight(tempLocX, tempLocZ) + Height, false);
				}
			}
		}
	} else {
		for(tempZ = tempMaxZ; >= tempMinZ){
			for(tempX = tempMaxX; >= tempMinX){
				if(tempRadiusCheck >= (tempX*tempX + tempZ*tempZ)){
					tempLocX = tempX + PosX;
					tempLocZ = tempZ + PosZ;
					trChangeTerrainHeight(tempLocX, tempLocZ, tempLocX, tempLocZ, Height, false);
				}
			}
		}
	}
}

void CTFPaintBase(float PosX = 0, float PosZ = 0){
	trPaintTerrainCircle(PosX/2+7,PosZ/2+8,10,2,13);
	trPaintElevationCircle(PosX/2+7,PosZ/2+7,11,5);
}

void CTFBuildBase(int p = 1, float PosX = 0, float PosZ = 0){
	trQuestVarSet("Base", trGetNextUnitScenarioNameNumber());
	
	trVectorQuestVarSet("P"+p+"Base", xsVectorSet(PosX+15, 5, PosZ+15));
	//	refreshPassability();
	trArmyDispatch(""+p+",0", "Victory Marker", 1, PosX+14, 0, PosZ+15, 0, false);
	trArmyDispatch(""+p+",0", "Victory Marker", 1, PosX, 0, PosZ+10, 0, false);
	trArmyDispatch(""+p+",0", "Victory Marker", 1, PosX, 0, PosZ+15, 90, false);
	trArmyDispatch(""+p+",0", "Victory Marker", 1, PosX, 0, PosZ+20, 0, false);
	
	trArmyDispatch(""+p+",0", "Victory Marker", 1, PosX+4, 0, PosZ+24, 135, false);
	trArmyDispatch(""+p+",0", "Victory Marker", 1, PosX+8, 0, PosZ+28, 0, false);
	
	trArmyDispatch(""+p+",0", "Victory Marker", 1, PosX+13, 0, PosZ+28, 180, false);
	trArmyDispatch(""+p+",0", "Victory Marker", 1, PosX+18, 0, PosZ+28, 0, false);
	
	trArmyDispatch(""+p+",0", "Victory Marker", 1, PosX+22, 0, PosZ+24, 225, false);
	trArmyDispatch(""+p+",0", "Victory Marker", 1, PosX+26, 0, PosZ+20, 0, false);
	
	
	trArmyDispatch(""+p+",0", "Victory Marker", 1, PosX+26, 0, PosZ+15, 270, false);
	trArmyDispatch(""+p+",0", "Victory Marker", 1, PosX+26, 0, PosZ+10, 0, false);
	
	trArmyDispatch(""+p+",0", "Victory Marker", 1, PosX+22, 0, PosZ+6, 315, false);
	//thjis
	trArmyDispatch(""+p+",0", "Victory Marker", 1, PosX+18, 0, PosZ+2, 0, false);
	
	trArmyDispatch(""+p+",0", "Victory Marker", 1, PosX+12, 0, PosZ+2, 180, false);
	trArmyDispatch(""+p+",0", "Victory Marker", 1, PosX+8, 0, PosZ+2, 0, false);
	
	trArmyDispatch(""+p+",0", "Victory Marker", 1, PosX+4, 0, PosZ+6, 45, false);
	
	//mirror
	trArmyDispatch(""+p+",0", "Victory Marker", 1, PosX+11, 0, PosZ+14, 0, false);
	trArmyDispatch(""+p+",0", "Victory Marker", 1, PosX+11, 0, PosZ+16, 0, false);
	trArmyDispatch(""+p+",0", "Victory Marker", 1, PosX+13, 0, PosZ+14, 0, false);
	trArmyDispatch(""+p+",0", "Victory Marker", 1, PosX+13, 0, PosZ+16, 0, false);
	
	yAddToDatabase("BaseBlocks", "Base");
	trQuestVarModify("Base", "+", 1);
	trUnitSelectClear();
	trUnitSelectByQV("Base", false);
	trUnitChangeProtoUnit("Atlantis Wall Connector");
	trVectorQuestVarSet("P"+p+"FlagSlot8", kbGetBlockPosition(""+1*trQuestVarGet("Base")+""));
	trUnitSelectClear();
	trQuestVarModify("Base", "+", 1);
	trUnitSelectByQV("Base", false);
	trUnitChangeProtoUnit("Atlantis Wall Long");
	trUnitSelectClear();
	trQuestVarModify("Base", "+", 1);
	trUnitSelectByQV("Base", false);
	trUnitChangeProtoUnit("Atlantis Wall Connector");
	trVectorQuestVarSet("P"+p+"FlagSlot7", kbGetBlockPosition(""+1*trQuestVarGet("Base")+""));
	trUnitSelectClear();
	trQuestVarModify("Base", "+", 1);
	trUnitSelectByQV("Base", false);
	trUnitChangeProtoUnit("Gate");
	yAddToDatabase("Gates", "Base");
	trUnitSelectClear();
	trQuestVarModify("Base", "+", 1);
	trUnitSelectByQV("Base", false);
	trUnitChangeProtoUnit("Atlantis Wall Connector");
	trVectorQuestVarSet("P"+p+"FlagSlot6", kbGetBlockPosition(""+1*trQuestVarGet("Base")+""));
	trUnitSelectClear();
	trQuestVarModify("Base", "+", 1);
	trUnitSelectByQV("Base", false);
	trUnitChangeProtoUnit("Atlantis Wall Long");
	trUnitSelectClear();
	trQuestVarModify("Base", "+", 1);
	trUnitSelectByQV("Base", false);
	trUnitChangeProtoUnit("Atlantis Wall Connector");
	trVectorQuestVarSet("P"+p+"FlagSlot5", kbGetBlockPosition(""+1*trQuestVarGet("Base")+""));
	trUnitSelectClear();
	trQuestVarModify("Base", "+", 1);
	trUnitSelectByQV("Base", false);
	trUnitChangeProtoUnit("Gate");
	yAddToDatabase("Gates", "Base");
	trUnitSelectClear();
	trQuestVarModify("Base", "+", 1);
	trUnitSelectByQV("Base", false);
	trUnitChangeProtoUnit("Atlantis Wall Connector");
	trVectorQuestVarSet("P"+p+"FlagSlot4", kbGetBlockPosition(""+1*trQuestVarGet("Base")+""));
	trUnitSelectClear();
	trQuestVarModify("Base", "+", 1);
	trUnitSelectByQV("Base", false);
	trUnitChangeProtoUnit("Atlantis Wall Long");
	trUnitSelectClear();
	trQuestVarModify("Base", "+", 1);
	trUnitSelectByQV("Base", false);
	trUnitChangeProtoUnit("Atlantis Wall Connector");
	trVectorQuestVarSet("P"+p+"FlagSlot3", kbGetBlockPosition(""+1*trQuestVarGet("Base")+""));
	trUnitSelectClear();
	trQuestVarModify("Base", "+", 1);
	trUnitSelectByQV("Base", false);
	trUnitChangeProtoUnit("Gate");
	yAddToDatabase("Gates", "Base");
	trUnitSelectClear();
	trQuestVarModify("Base", "+", 1);
	trUnitSelectByQV("Base", false);
	trUnitChangeProtoUnit("Atlantis Wall Connector");
	trVectorQuestVarSet("P"+p+"FlagSlot2", kbGetBlockPosition(""+1*trQuestVarGet("Base")+""));
	trUnitSelectClear();
	trQuestVarModify("Base", "+", 1);
	trUnitSelectByQV("Base", false);
	trUnitChangeProtoUnit("Atlantis Wall Long");
	trUnitSelectClear();
	trQuestVarModify("Base", "+", 1);
	trUnitSelectByQV("Base", false);
	trUnitChangeProtoUnit("Atlantis Wall Connector");
	trVectorQuestVarSet("P"+p+"FlagSlot1", kbGetBlockPosition(""+1*trQuestVarGet("Base")+""));
	trUnitSelectClear();
	trQuestVarModify("Base", "+", 1);
	trUnitSelectByQV("Base", false);
	trUnitChangeProtoUnit("Gate");
	yAddToDatabase("Gates", "Base");
	trUnitSelectClear();
	trQuestVarModify("Base", "+", 1);
	trUnitSelectByQV("Base", false);
	trUnitChangeProtoUnit("Tower Mirror");
	trUnitSelectClear();
	trQuestVarModify("Base", "+", 1);
	trUnitSelectByQV("Base", false);
	trUnitChangeProtoUnit("Tower Mirror");
	trUnitSelectClear();
	trQuestVarModify("Base", "+", 1);
	trUnitSelectByQV("Base", false);
	trUnitChangeProtoUnit("Tower Mirror");
	trUnitSelectClear();
	trQuestVarModify("Base", "+", 1);
	trUnitSelectByQV("Base", false);
	trUnitChangeProtoUnit("Tower Mirror");
	//This bit sets the victory marker of unitID p to the middle of the player base
	trUnitSelectClear();
	trUnitSelectByID(p);
	trUnitTeleport(trVectorQuestVarGetX("P"+p+"Base"),
		trVectorQuestVarGetY("P"+p+"Base"),trVectorQuestVarGetZ("P"+p+"Base"));
	trUnitChangeProtoUnit("Storage Pit");
	
}

void setupUnitShop(int slot = 0, string displayname = "", string protoname = "",
	string description = "", int cost = 0, int limit = 0) {
	trStringQuestVarSet("unit"+slot+"displayname", displayname);
	trStringQuestVarSet("unit"+slot+"protoname", protoname);
	trStringQuestVarSet("unit"+slot+"description", description);
	trQuestVarSet("unit"+slot+"cost", cost);
	trQuestVarSet("unit"+slot+"limit", limit);
}

void setupPowerShop(int slot = 0, string displayname = "", string powername = "",
	string protoname = "", string description = "", int cost = 0, int idneeded = 0) {
	trStringQuestVarSet("power"+slot+"displayname", displayname);
	trStringQuestVarSet("power"+slot+"powername", powername);
	trStringQuestVarSet("power"+slot+"protoname", protoname);
	trStringQuestVarSet("power"+slot+"description", description);
	trQuestVarSet("power"+slot+"cost", cost);
	trQuestVarSet("power"+slot+"id", idneeded);
}

void playSoundCustom(string BasesoundName = "", string CustomsoundName = ""){
	if(1*trQuestVarGet("CustomContent") == 0){
		trSoundPlayPaused(""+BasesoundName+"", "1", -1, "", "");
	}
	else {
		trSoundPlayPaused(""+CustomsoundName+"", "1", -1, "", "");
	}
}

void ColouredIconChat(string colour = "1,1,1", string icon = "", string chats = ""){
	trChatSend(0, "<color="+colour+"><icon=(20)("+icon+")> "+chats+"</color>");
}

void PlayerColouredChat(int p = 0, string chats = ""){
	trChatSend(0, "<color={PlayerColor("+p+")}> "+chats+"</color>");
}

void PlayerColouredChatToSelf(int p = 0, string chats = ""){
	trChatSendToPlayer(0, p, "<color={PlayerColor("+p+")}> "+chats+"</color>");
}

void ColouredIconChatToPlayer(int p = 1, string colour = "1,1,1", string icon = "", string chats = ""){
	trChatSendToPlayer(0, p, "<color=" + colour + "><icon=(20)(" + icon + ")> " + chats + "</color>");
}

void PwnPlayer(int p = 0, int v = 0){
	trSetPlayerDefeated(p);
	OverlayTextPlayerColor(p);
	trOverlayText(trStringQuestVarGet("p"+p+"name") + "'s flag has been captured!", 5.0, 350, 350, 800);
	playSound("Yeebaagooon\Capture The Flag\Warp.mp3");
	playSound("timeshift.wav");
	trCameraShake(5, 0.1);
	trPlayerKillAllBuildings(p);
	trPlayerKillAllUnits(p);
	trUnitSelectClear();
	trUnitSelect("+p+");
	trUnitChangeProtoUnit("Cinematic Block");
	trPlayerGrantResources(v, "Food", 1*trPlayerResourceCount(p, "Food"));
	trPlayerGrantResources(v, "Wood", 1*trPlayerResourceCount(p, "Wood"));
	trPlayerGrantResources(v, "Gold", 1*trPlayerResourceCount(p, "Gold"));
	ColouredIconChatToPlayer(v, "{PlayerColor("+p+")}", "icons\icon resource food",
		""+1*trPlayerResourceCount(p, "Food")+"");
	ColouredIconChatToPlayer(v, "{PlayerColor("+p+")}", "icons\icon resource wood",
		""+1*trPlayerResourceCount(p, "Wood")+"");
	ColouredIconChatToPlayer(v, "{PlayerColor("+p+")}", "icons\icon resource gold",
		""+1*trPlayerResourceCount(p, "Gold")+"");
	trPlayerGrantResources(p, "Food", -10000.0);
	trPlayerGrantResources(p, "Wood", -10000.0);
	trPlayerGrantResources(p, "Gold", -10000.0);
	trPlayerGrantResources(p, "Favor", -10000.0);
	trQuestVarModify("P"+v+"FlagsGot", "+", 1);
	if(1*trQuestVarGet("P"+v+"FlagsGot") < 9){
		//flag go on base
		//0 = heading
		//Seems to be off for 3 of them
		/*
		trQuestVarSet("QVGateFlag", trGetNextUnitScenarioNameNumber()-10);
		trUnitSelectClear();
		trUnitSelect(""+1*trQuestVarGet("P"+p+"FlagSlot"+1*trQuestVarGet("P"+v+"FlagsGot")+""));
		trUnitChangeProtoUnit("Titan Atlantean");
		trUnitSelectClear();
		yFindLatestAll("QVGateFlag", "Titan Gate Dead");
		trUnitSelectClear();
		trUnitSelect(""+1*trQuestVarGet("QVGateFlag"));
		trUnitChangeProtoUnit("Ajax");
		trUnitSelectClear();
		trUnitSelect(""+1*trQuestVarGet("P"+p+"FlagSlot"+1*trQuestVarGet("P"+v+"FlagsGot")+""));
		trUnitChangeProtoUnit("Atlantis Wall Connector");
		trUnitSelectClear();
		trUnitSelect(""+1*trQuestVarGet("QVGateFlag"));
		trUnitChangeProtoUnit("Flag");
		trUnitSetAnimationPath("0,0,0,0,0");
		*/
		FloatingUnitAnim4("Flag",
			1*trVectorQuestVarGetX("P"+v+"FlagSlot"+1*trQuestVarGet("P"+v+"FlagsGot")),
			1*trVectorQuestVarGetY("P"+v+"FlagSlot"+1*trQuestVarGet("P"+v+"FlagsGot")),
			1*trVectorQuestVarGetZ("P"+v+"FlagSlot"+1*trQuestVarGet("P"+v+"FlagsGot")),
			0, 1, 1, 1, "0,0,0,0,0", p);
	}
}



void PaintAtlantisArea (int x0 = 0, int z0 = 0, int x1 = 0, int z1 = 0, int fill1 = 0, int fill2 = 0){
	//bottom corner
	trPaintTerrain(x0, z1, x0, z1, 0, 83, false);
	trPaintTerrain(x1, z1, x1, z1, 0, 80, false);
	//top corner
	trPaintTerrain(x0, z0, x0, z0, 0, 82, false);
	trPaintTerrain(x1, z0, x1, z0, 0, 81, false);
	//bottom and top row
	trPaintTerrain(x1-1, z1, x0+1, z1, 0, 75, false);
	trPaintTerrain(x1-1, z0, x0+1, z0, 0, 75, false);
	//left and right row
	trPaintTerrain(x1, z1-1, x1, z0+1, 0, 74, false);
	trPaintTerrain(x0, z1-1, x0, z0+1, 0, 74, false);
	//fill
	trPaintTerrain(x1-1, z1-1, x0+1, z0+1, fill1, fill2, false);
}
