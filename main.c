rmSetStatusText("",0.01);
int MapSize = 252;
rmSetMapSize(252, 252);
rmSetSeaLevel(0);
rmSetSeaType("greek river");
rmTerrainInitialize("GrassB",5);
rmSetLightingSet("Default");
rmSetGaiaCiv(cCivIsis);

/*
int id = 0;
int skin = 2;
int r = 0;
//skin = rmRandInt(1,1);
// 0==eggy, 1==greek, 2==norse, 3==atlantean
for(i = 0; < 700){
	id = rmCreateArea("terrainmix"+i);
	if(skin == 0){
		rmSetGaiaCiv(cCivIsis);
		r = rmRandInt(0,8);
		if(r == 0)rmSetAreaTerrainType(id,"SandB");
		if(r == 1)rmSetAreaTerrainType(id,"CoralD");
		if(r == 2)rmSetAreaTerrainType(id,"SavannahA");
		if(r == 3)rmSetAreaTerrainType(id,"SavannahD");
		if(r == 4)rmSetAreaTerrainType(id,"DirtA");
		if(r == 5)rmSetAreaTerrainType(id,"EgyptianRoadA");
		if(r == 6)rmSetAreaTerrainType(id,"ForestFloorPalm");
		if(r == 7)rmSetAreaTerrainType(id,"SandD");
		if(r == 8)rmSetAreaTerrainType(id,"ForestFloorSavannah");
		rmSetAreaBaseHeight(id,rmRandFloat(1,5));
		rmSetAreaCoherence(id,0.5);
		rmSetAreaHeightBlend(id,1.45);
		rmSetAreaSize(id,0.001,0.01);
		rmSetAreaSmoothDistance(id,rmRandInt(0,10));
		rmBuildArea(id);
	}
	if(skin == 1){
		rmSetGaiaCiv(cCivZeus);
		r = rmRandInt(0,8);
		if(r == 0)rmSetAreaTerrainType(id,"CliffGreekB");
		if(r == 1)rmSetAreaTerrainType(id,"RiverGrassyC");
		if(r == 2)rmSetAreaTerrainType(id,"MarshF");
		if(r == 3)rmSetAreaTerrainType(id,"JungleA");
		if(r == 4)rmSetAreaTerrainType(id,"GrassDirt25");
		if(r == 5)rmSetAreaTerrainType(id,"GrassDirt50");
		if(r == 6)rmSetAreaTerrainType(id,"ForestFloorOak");
		if(r == 7)rmSetAreaTerrainType(id,"GrassA");
		if(r == 8)rmSetAreaTerrainType(id,"ForestFloorPine");
		rmSetAreaBaseHeight(id,rmRandFloat(1,5));
		rmSetAreaCoherence(id,0.5);
		rmSetAreaHeightBlend(id,1.45);
		rmSetAreaSize(id,0.001,0.01);
		rmSetAreaSmoothDistance(id,rmRandInt(0,10));
		rmBuildArea(id);
	}
	if(skin == 2){
		rmSetGaiaCiv(cCivThor);
		r = rmRandInt(0,8);
		if(r == 0)rmSetAreaTerrainType(id,"IceA"); //5,0
		if(r == 1)rmSetAreaTerrainType(id,"SnowB"); //0,42
		if(r == 2)rmSetAreaTerrainType(id,"ShorelineAtlanticB"); //4,15
		if(r == 3)rmSetAreaTerrainType(id,"OlympusA"); //0,50
		if(r == 4)rmSetAreaTerrainType(id,"TundraGrassA"); //0,54
		if(r == 5)rmSetAreaTerrainType(id,"TundraRockB"); //0,57
		if(r == 6)rmSetAreaTerrainType(id,"OlympusB"); //0,51
		if(r == 7)rmSetAreaTerrainType(id,"ForestFloorTundra"); //0,93
		if(r == 8)rmSetAreaTerrainType(id,"ForestFloorPineSnow"); //0,88
		rmSetAreaBaseHeight(id,rmRandFloat(1,5));
		rmSetAreaCoherence(id,0.5);
		rmSetAreaHeightBlend(id,1.45);
		rmSetAreaSize(id,0.001,0.01);
		rmSetAreaSmoothDistance(id,rmRandInt(0,10));
		rmBuildArea(id);
	}
	if(skin == 3){
		rmSetGaiaCiv(cCivOuranos);
		r = rmRandInt(0,8);
		if(r == 0)rmSetAreaTerrainType(id,"MarshA"); //0-58
		if(r == 1)rmSetAreaTerrainType(id,"MarshC"); //0-60
		if(r == 2)rmSetAreaTerrainType(id,"GaiaCreepA"); //0-8
		if(r == 3)rmSetAreaTerrainType(id,"GaiaCreepB"); //0-1
		if(r == 4)rmSetAreaTerrainType(id,"GrassB"); //0,54
		if(r == 5)rmSetAreaTerrainType(id,"RiverGrassyC");
		if(r == 6)rmSetAreaTerrainType(id,"RiverMarshC"); //4-40
		if(r == 7)rmSetAreaTerrainType(id,"ForestFloorGaia"); //0-90
		if(r == 8)rmSetAreaTerrainType(id,"ForestFloorMarsh"); //0-94
		rmSetAreaBaseHeight(id,rmRandFloat(1,5));
		rmSetAreaCoherence(id,0.5);
		rmSetAreaHeightBlend(id,1.45);
		rmSetAreaSize(id,0.001,0.01);
		rmSetAreaSmoothDistance(id,rmRandInt(0,10));
		rmBuildArea(id);
	}
}
*/
