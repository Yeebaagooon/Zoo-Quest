//Map size

int getMapSize(){
	return (252);
}

int getMapSizeSquared(){
	return (getMapSize() * getMapSize());
}


//Weighted random numbers

// DONE_DEFINE_CONSTANTS

float startSunRed = 255.0;
float startSunGreen = 255.0;
float startSunBlue = 255.0;
float startAmbientRed = 115.0;
float startAmbientGreen = 115.0;
float startAmbientBlue = 115.0;
float startSunInclination = 38.0;
float startSunRotation = 280.0;

vector tempCameraPos = vector(0.0, 0.0, 0.0);
vector tempCameraMx = vector(0.0, 0.0, 0.0);
vector tempCameraMy = vector(0.0, 0.0, 0.0);
vector tempCameraMz = vector(0.0, 0.0, 0.0);
float tempH = 0.0;
float tempT = 0.0;
float tempSinH = 0.0;
float tempCosH = 0.0;
float tempSinT = 0.0;
float tempCosT = 0.0;
float tempPosX = 0.0;
float tempPosY = 0.0;
float tempPosZ = 0.0;
int tempI = -1;
float tempF = 0.0;
int cameraTrackTime = 0;
bool cameraFirstWaypoint = false;
string tempS = "";
string tempS2 = "";
vector tempV = vector(0.0, 0.0, 0.0);
vector tempV2 = vector(0.0, 0.0, 0.0);
vector tempV3 = vector(0.0, 0.0, 0.0);

int qvToInt(string name = ""){
	return (1*(0.4999999 + trQuestVarGet(name)));
}
int randomInt(int low = 0, int high = 0){
	trQuestVarSetFromRand("r", low, high, true);
	return (qvToInt("r"));
}
float randomFloat(float low = 0.0, float high = 0.0){
	trQuestVarSetFromRand("r", low, high, false);
	return (trQuestVarGet("r"));
}


float toMetres(float fraction = 0.0){
	return (fraction * getMapSize());
}
float toTiles(float fraction = 0.0){
	return (fraction * (getMapSize() / 2));
}
float interpolate(float from = 0.0, float to = 0.0, float fraction = 0.0){
	return ((1.0 - fraction) * from + fraction * to);
}
float interpolateRange(float from0 = 0.0, float to0 = 0.0, float from1 = 0.0, float to1 = 0.0, float pos0 = 0.0){
	float range0 = to0 - from0;
	float pos0Proportion = (pos0 - from0) / range0;
	return (interpolate(from1, to1, pos0Proportion));
}
vector interpolateVector(vector from = vector(0.0, 0.0, 0.0), vector to = vector(0.0, 0.0, 0.0), float fraction = 0.0){
	return (xsVectorSet(interpolate(xsVectorGetX(from), xsVectorGetX(to), fraction),
			interpolate(xsVectorGetY(from), xsVectorGetY(to), fraction),
			interpolate(xsVectorGetZ(from), xsVectorGetZ(to), fraction)));
}

float clamp(float minValue = 0.0, float maxValue = 0.0, float value = 0.0){
	return (xsMin(maxValue, xsMax(minValue, value)));
}

int modInt(int value = 0, int ceiling = 1){
	return (value - (value / ceiling) * ceiling);
}
float modFloat(float value = 0.0, float ceiling = 1.0){
	return (value - (1.0*(1*(value / ceiling))) * ceiling);
}

int absInt(int value = 0){
	if(value < 0){
		return (0 - value);
	} else {
		return (value);
	}
}
float circleX(float centre = 0.0, int i = 0, int total = 0, float radius = 0.0, float disp = 0){
	return(centre + radius * xsSin((6.283185 * i) / total + (45.0 - disp) * 0.017453));
}
float circleZ(float centre = 0.0, int i = 0, int total = 0, float radius = 0.0, float disp = 0){
	return(centre + radius * xsCos((6.283185 * i) / total + (45.0 - disp) * 0.017453));
}
void cameraLookAt(vector dest = vector(0.0, 0.0, 0.0), float distance = 0.0, float heading = 0.0,
	float tilt = 0.0, float verticalOffset = 0.0){
	tempH = PI * heading / 180.0;
	tempT = PI * tilt / 180.0;
	tempSinH = xsSin(tempH);
	tempCosH = xsCos(tempH);
	tempSinT = xsSin(tempT);
	tempCosT = xsCos(tempT);
	tempPosX = 0.0+xsVectorGetX(dest)-tempCosH*tempCosT*distance;
	tempPosY = tempSinT*distance+(xsVectorGetY(dest) + verticalOffset);
	tempPosZ = 0.0+xsVectorGetZ(dest)-tempSinH*tempCosT*distance;
	tempCameraPos = xsVectorSet(tempPosX, tempPosY, tempPosZ);
	tempCameraMx = xsVectorSet(tempCosH*tempCosT, 0.0-tempSinT, tempSinH*tempCosT);
	tempCameraMy = xsVectorSet(tempCosH*tempSinT, tempCosT, tempSinH*tempSinT);
	tempCameraMz = xsVectorSet(tempSinH, 0, 0.0-tempCosH);
	trCameraCut(tempCameraPos, tempCameraMx, tempCameraMy, tempCameraMz);
}
void createCameraTrack(int timeMS = 0){
	cameraFirstWaypoint = true;
	cameraTrackTime = timeMS;
	trackInsert();
	trackPlay(cameraTrackTime, -1);
}
void addCameraTrackWaypoint(){
	if(cameraFirstWaypoint){
		cameraFirstWaypoint = false;
	} else {
		trackAddWaypoint();
	}
	trackEditWaypoint();
}
void playCameraTrack(int eventId = -1){
	trackPlay(cameraTrackTime, eventId);
}
bool unitSelected(int unitName = 0, bool backwards = false){
	if(unitName < 0)return (false);
	trUnitSelectClear();
	trUnitSelect(""+unitName, backwards);
	return (trUnitIsSelected());
}

void modifyProtounitAbsoluteAllHumanPlayers(string protounit = "", int field = 0, float value = 0.0){
	for(p = 1; <= cNumberNonGaiaPlayers){
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
}
int getOwner(int unitName = -1){
	return (kbUnitGetOwner(kbGetBlockID(""+(1*unitName), true)));
}
vector getPosition(int unitName = -1){
	return (kbGetBlockPosition(""+(1*unitName), true));
}

int unitPercentDamaged(int unitName = 0){
	trUnitSelectClear();
	trUnitSelect(""+unitName, true);
	return (trUnitPercentDamaged());
}
bool unitDead(int unitName = 0, bool backwards = true){
	if(unitName < 0)return (false);
	trUnitSelectClear();
	trUnitSelect(""+unitName, backwards);
	return (trUnitDead());
}
bool unitGarrisonedIn(int unitName = 0, string container = "", bool backwards = true){
	if(unitName < 0)return (false);
	trUnitSelectClear();
	trUnitSelect(""+unitName, backwards);
	return (trUnitGetIsContained(container));
}

bool unitNearby(int from = -1, float distance = 0.0, int to = -1){
	if(from < 0 || to < 0)return (false);
	float distanceSquared = distance * distance;
	vector fromV = kbGetBlockPosition(""+from, true);
	vector toV = kbGetBlockPosition(""+to, true);
	float diffX = xsVectorGetX(toV) - xsVectorGetX(fromV);
	float diffZ = xsVectorGetZ(toV) - xsVectorGetZ(fromV);
	if((diffX * diffX + diffZ * diffZ) <= distanceSquared)return (true);
	return (false);
}
bool isContained(int unitName = 0, string containType = ""){
	if(unitName < 0)return (false);
	trUnitSelectClear();
	trUnitSelect(""+unitName, true);
	return (trUnitGetIsContained(containType));
}
vector vectorMultiply(vector v = vector(0,0,0), float amount = 0.0){
	return (xsVectorSet(xsVectorGetX(v)*amount,xsVectorGetY(v)*amount,xsVectorGetZ(v)*amount));
}
void sunVector(vector sun = vector(0,0,0)){
	sunColor(xsVectorGetX(sun),xsVectorGetY(sun),xsVectorGetZ(sun));
}
void ambientVector(vector ambient = vector(0,0,0)){
	ambientColor(xsVectorGetX(ambient),xsVectorGetY(ambient),xsVectorGetZ(ambient));
}
float clampColor(float value = 0.0){
	return (clamp(0.0, 255.0, value));
}
vector randomHue(){
	int hueType = randomInt(0, 2);
	float first = randomFloat(0.0, 255.0);
	float second = 255.0 - first;
	if(hueType == 0)return (xsVectorSet(first, second, 0.0));
	if(hueType == 1)return (xsVectorSet(0.0, first, second));
	if(hueType == 2)return (xsVectorSet(first, 0.0, second));
}
void look(string unitToLookAt = ""){
	trBlockAllSounds(true);
	uiFindType(unitToLookAt);
	uiClearSelection();
	trUnblockAllSounds();
}
string displayFloat(float value = 0.0){
	string valueAsString = ""+value;
	for(i = 0; < 6){
		if(xsSubString(valueAsString, 1, xsStringLength(valueAsString) - 1) != "0"){
			return (valueAsString);
		} else {
			valueAsString = xsSubString(valueAsString, xsStringLength(valueAsString) - 1, 0);
		}
	}
	return (xsSubString(valueAsString, xsStringLength(valueAsString) - 1, 0));
}

string displayTime(int seconds = 0){
	if(seconds < 60){
		return (""+seconds);
	}
	int secondsPart = modInt(seconds, 60);
	string displaySeconds = "" + secondsPart;
	if(secondsPart < 10){
		displaySeconds = "0" + displaySeconds;
	}
	return ("" + (seconds / 60) + ":" + displaySeconds);
}
void setSelectedUnitHeadingDegress(float heading = 0.0){
	float headingRadians = PI * heading / 180.0;
	trSetUnitOrientation(xsVectorSet(xsCos(headingRadians), 0.0, xsSin(headingRadians)), xsVectorSet(0.0, 1.0, 0.0), true);
}
// ### RANDOM WITHOUT REPLACEMENT
int array0 = 0;
int array1 = 0;
int array2 = 0;
int array3 = 0;
int array4 = 0;
int array5 = 0;
int array6 = 0;
int array7 = 0;
int array8 = 0;
int array9 = 0;
int array10 = 0;
int array11 = 0;
int array12 = 0;
int array13 = 0;
int array14 = 0;
int array15 = 0;
int array16 = 0;
int array17 = 0;
int array18 = 0;
int array19 = 0;
int array20 = 0;
int array21 = 0;
int array22 = 0;
int array23 = 0;
int array24 = 0;
int array25 = 0;
int array26 = 0;
int array27 = 0;
int array28 = 0;
int array29 = 0;
int array30 = 0;
int array31 = 0;
int array32 = 0;
int array33 = 0;
int array34 = 0;
int array35 = 0;
int array36 = 0;
int array37 = 0;
int array38 = 0;
int array39 = 0;
int array40 = 0;
int array41 = 0;
int array42 = 0;
int array43 = 0;
int array44 = 0;
int array45 = 0;
int array46 = 0;
int array47 = 0;
int array48 = 0;
int array49 = 0;
int array50 = 0;
int array51 = 0;
int array52 = 0;
int array53 = 0;
int array54 = 0;
int array55 = 0;
int array56 = 0;
int array57 = 0;
int array58 = 0;
int array59 = 0;
int array60 = 0;
int array61 = 0;
int array62 = 0;
int array63 = 0;
int array64 = 0;
int array65 = 0;
int array66 = 0;
int array67 = 0;
int array68 = 0;
int array69 = 0;
int array70 = 0;
int array71 = 0;
int array72 = 0;
int array73 = 0;
int array74 = 0;
int array75 = 0;
int array76 = 0;
int array77 = 0;
int array78 = 0;
int array79 = 0;
int array80 = 0;
int array81 = 0;
int array82 = 0;
int array83 = 0;
int array84 = 0;
int array85 = 0;
int array86 = 0;
int array87 = 0;
int array88 = 0;
int array89 = 0;
int array90 = 0;
int array91 = 0;
int array92 = 0;
int array93 = 0;
int array94 = 0;
int array95 = 0;
int array96 = 0;
int array97 = 0;
int array98 = 0;
int array99 = 0;
int array100 = 0;
int array101 = 0;
int array102 = 0;
int array103 = 0;
int array104 = 0;
int array105 = 0;
int array106 = 0;
int array107 = 0;
int array108 = 0;
int array109 = 0;
int array110 = 0;
int array111 = 0;
int array112 = 0;
int array113 = 0;
int array114 = 0;
int array115 = 0;
int array116 = 0;
int arraySize = 0;
int randomArrayGet(int index = 0){
	if(index == 0)return (array0);
	if(index == 1)return (array1);
	if(index == 2)return (array2);
	if(index == 3)return (array3);
	if(index == 4)return (array4);
	if(index == 5)return (array5);
	if(index == 6)return (array6);
	if(index == 7)return (array7);
	if(index == 8)return (array8);
	if(index == 9)return (array9);
	if(index == 10)return (array10);
	if(index == 11)return (array11);
	if(index == 12)return (array12);
	if(index == 13)return (array13);
	if(index == 14)return (array14);
	if(index == 15)return (array15);
	if(index == 16)return (array16);
	if(index == 17)return (array17);
	if(index == 18)return (array18);
	if(index == 19)return (array19);
	if(index == 20)return (array20);
	if(index == 21)return (array21);
	if(index == 22)return (array22);
	if(index == 23)return (array23);
	if(index == 24)return (array24);
	if(index == 25)return (array25);
	if(index == 26)return (array26);
	if(index == 27)return (array27);
	if(index == 28)return (array28);
	if(index == 29)return (array29);
	if(index == 30)return (array30);
	if(index == 31)return (array31);
	if(index == 32)return (array32);
	if(index == 33)return (array33);
	if(index == 34)return (array34);
	if(index == 35)return (array35);
	if(index == 36)return (array36);
	if(index == 37)return (array37);
	if(index == 38)return (array38);
	if(index == 39)return (array39);
	if(index == 40)return (array40);
	if(index == 41)return (array41);
	if(index == 42)return (array42);
	if(index == 43)return (array43);
	if(index == 44)return (array44);
	if(index == 45)return (array45);
	if(index == 46)return (array46);
	if(index == 47)return (array47);
	if(index == 48)return (array48);
	if(index == 49)return (array49);
	if(index == 50)return (array50);
	if(index == 51)return (array51);
	if(index == 52)return (array52);
	if(index == 53)return (array53);
	if(index == 54)return (array54);
	if(index == 55)return (array55);
	if(index == 56)return (array56);
	if(index == 57)return (array57);
	if(index == 58)return (array58);
	if(index == 59)return (array59);
	if(index == 60)return (array60);
	if(index == 61)return (array61);
	if(index == 62)return (array62);
	if(index == 63)return (array63);
	if(index == 64)return (array64);
	if(index == 65)return (array65);
	if(index == 66)return (array66);
	if(index == 67)return (array67);
	if(index == 68)return (array68);
	if(index == 69)return (array69);
	if(index == 70)return (array70);
	if(index == 71)return (array71);
	if(index == 72)return (array72);
	if(index == 73)return (array73);
	if(index == 74)return (array74);
	if(index == 75)return (array75);
	if(index == 76)return (array76);
	if(index == 77)return (array77);
	if(index == 78)return (array78);
	if(index == 79)return (array79);
	if(index == 80)return (array80);
	if(index == 81)return (array81);
	if(index == 82)return (array82);
	if(index == 83)return (array83);
	if(index == 84)return (array84);
	if(index == 85)return (array85);
	if(index == 86)return (array86);
	if(index == 87)return (array87);
	if(index == 88)return (array88);
	if(index == 89)return (array89);
	if(index == 90)return (array90);
	if(index == 91)return (array91);
	if(index == 92)return (array92);
	if(index == 93)return (array93);
	if(index == 94)return (array94);
	if(index == 95)return (array95);
	if(index == 96)return (array96);
	if(index == 97)return (array97);
	if(index == 98)return (array98);
	if(index == 99)return (array99);
	if(index == 100)return (array100);
	if(index == 101)return (array101);
	if(index == 102)return (array102);
	if(index == 103)return (array103);
	if(index == 104)return (array104);
	if(index == 105)return (array105);
	if(index == 106)return (array106);
	if(index == 107)return (array107);
	if(index == 108)return (array108);
	if(index == 109)return (array109);
	if(index == 110)return (array110);
	if(index == 111)return (array111);
	if(index == 112)return (array112);
	if(index == 113)return (array113);
	if(index == 114)return (array114);
	if(index == 115)return (array115);
	if(index == 116)return (array116);
}
void randomArraySet(int index = 0, int value = 0){
	if(index == 0)array0 = value;
	if(index == 1)array1 = value;
	if(index == 2)array2 = value;
	if(index == 3)array3 = value;
	if(index == 4)array4 = value;
	if(index == 5)array5 = value;
	if(index == 6)array6 = value;
	if(index == 7)array7 = value;
	if(index == 8)array8 = value;
	if(index == 9)array9 = value;
	if(index == 10)array10 = value;
	if(index == 11)array11 = value;
	if(index == 12)array12 = value;
	if(index == 13)array13 = value;
	if(index == 14)array14 = value;
	if(index == 15)array15 = value;
	if(index == 16)array16 = value;
	if(index == 17)array17 = value;
	if(index == 18)array18 = value;
	if(index == 19)array19 = value;
	if(index == 20)array20 = value;
	if(index == 21)array21 = value;
	if(index == 22)array22 = value;
	if(index == 23)array23 = value;
	if(index == 24)array24 = value;
	if(index == 25)array25 = value;
	if(index == 26)array26 = value;
	if(index == 27)array27 = value;
	if(index == 28)array28 = value;
	if(index == 29)array29 = value;
	if(index == 30)array30 = value;
	if(index == 31)array31 = value;
	if(index == 32)array32 = value;
	if(index == 33)array33 = value;
	if(index == 34)array34 = value;
	if(index == 35)array35 = value;
	if(index == 36)array36 = value;
	if(index == 37)array37 = value;
	if(index == 38)array38 = value;
	if(index == 39)array39 = value;
	if(index == 40)array40 = value;
	if(index == 41)array41 = value;
	if(index == 42)array42 = value;
	if(index == 43)array43 = value;
	if(index == 44)array44 = value;
	if(index == 45)array45 = value;
	if(index == 46)array46 = value;
	if(index == 47)array47 = value;
	if(index == 48)array48 = value;
	if(index == 49)array49 = value;
	if(index == 50)array50 = value;
	if(index == 51)array51 = value;
	if(index == 52)array52 = value;
	if(index == 53)array53 = value;
	if(index == 54)array54 = value;
	if(index == 55)array55 = value;
	if(index == 56)array56 = value;
	if(index == 57)array57 = value;
	if(index == 58)array58 = value;
	if(index == 59)array59 = value;
	if(index == 60)array60 = value;
	if(index == 61)array61 = value;
	if(index == 62)array62 = value;
	if(index == 63)array63 = value;
	if(index == 64)array64 = value;
	if(index == 65)array65 = value;
	if(index == 66)array66 = value;
	if(index == 67)array67 = value;
	if(index == 68)array68 = value;
	if(index == 69)array69 = value;
	if(index == 70)array70 = value;
	if(index == 71)array71 = value;
	if(index == 72)array72 = value;
	if(index == 73)array73 = value;
	if(index == 74)array74 = value;
	if(index == 75)array75 = value;
	if(index == 76)array76 = value;
	if(index == 77)array77 = value;
	if(index == 78)array78 = value;
	if(index == 79)array79 = value;
	if(index == 80)array80 = value;
	if(index == 81)array81 = value;
	if(index == 82)array82 = value;
	if(index == 83)array83 = value;
	if(index == 84)array84 = value;
	if(index == 85)array85 = value;
	if(index == 86)array86 = value;
	if(index == 87)array87 = value;
	if(index == 88)array88 = value;
	if(index == 89)array89 = value;
	if(index == 90)array90 = value;
	if(index == 91)array91 = value;
	if(index == 92)array92 = value;
	if(index == 93)array93 = value;
	if(index == 94)array94 = value;
	if(index == 95)array95 = value;
	if(index == 96)array96 = value;
	if(index == 97)array97 = value;
	if(index == 98)array98 = value;
	if(index == 99)array99 = value;
	if(index == 100)array100 = value;
	if(index == 101)array101 = value;
	if(index == 102)array102 = value;
	if(index == 103)array103 = value;
	if(index == 104)array104 = value;
	if(index == 105)array105 = value;
	if(index == 106)array106 = value;
	if(index == 107)array107 = value;
	if(index == 108)array108 = value;
	if(index == 109)array109 = value;
	if(index == 110)array110 = value;
	if(index == 111)array111 = value;
	if(index == 112)array112 = value;
	if(index == 113)array113 = value;
	if(index == 114)array114 = value;
	if(index == 115)array115 = value;
	if(index == 116)array116 = value;
}



void randomArrayInitialise(int count = 0){
	for(i = 0; < count){
		randomArraySet(i, i);
	}
	arraySize = count;
}

int randomArrayNext(){
	int nextIndex = randomInt(0, arraySize - 1);
	int nextValue = randomArrayGet(nextIndex);
	randomArraySet(nextIndex, randomArrayGet(arraySize - 1));
	arraySize = arraySize - 1;
	return (nextValue);
}
// ### TERRAIN


vector randomCircleLoc(float centreX = 0.0, float centreZ = 0.0, float radius = 0.0){
	bool terminate = false;
	float posX = -1;
	float posZ = -1;
	float radiusCheck = radius * radius + radius;
	while(terminate == false){
		posX = randomFloat(0.0-radius, radius);
		posZ = randomFloat(0.0-radius, radius);
		if(posX*posX + posZ*posZ <= radiusCheck){
			terminate = true;
		}
	}
	return (xsVectorSet(posX + centreX, 0, posZ + centreZ));
}
vector randomOutsideCircleLoc(float centreX = 0.0, float centreZ = 0.0, float radius = 0.0){
	bool terminate = false;
	float posX = -1;
	float posZ = -1;
	float radiusCheck = radius * radius + radius;
	while(terminate == false){
		posX = randomFloat(0.0, getMapSize() / 2);
		posZ = randomFloat(0.0, getMapSize() / 2);
		float distX = centreX - posX;
		float distZ = centreZ - posZ;
		if(distX*distX + distZ*distZ > radiusCheck){
			terminate = true;
		}
	}
	return (xsVectorSet(posX, 0, posZ));
}
void paintCircle(int posX = 0, int posZ = 0, int radius = 0, string terrain = ""){
	int terrainType = getTerrainType(terrain);
	int terrainSubType = getTerrainSubType(terrain);
	int tempMinX = xsMax(0.0 - posX, 0.0 - radius);
	int tempMinZ = xsMax(0.0 - posZ, 0.0 - radius);
	int tempMaxX = xsMin(getMapSize() / 2 - posX, radius);
	int tempMaxZ = xsMin(getMapSize() / 2 - posZ, radius);
	int tempRadiusCheck = radius * radius + radius;
	for(tempZ = tempMaxZ; >= tempMinZ){
		for(tempX = tempMaxX; >= tempMinX){
			if(tempRadiusCheck >= (tempX*tempX + tempZ*tempZ)){
				trPaintTerrain(tempX + posX, tempZ + posZ, tempX + posX, tempZ + posZ, terrainType, terrainSubType, false);
			}
		}
	}
}
void replaceCircleAllBut(int posX = 0, int posZ = 0, int radius = 0, string oldTerrain = "", string newTerrain = ""){
	int oldTerrainType = getTerrainType(oldTerrain);
	int oldTerrainSubType = getTerrainSubType(oldTerrain);
	int newTerrainType = getTerrainType(newTerrain);
	int newTerrainSubType = getTerrainSubType(newTerrain);
	int tempMinX = xsMax(0.0 - posX, 0.0 - radius);
	int tempMinZ = xsMax(0.0 - posZ, 0.0 - radius);
	int tempMaxX = xsMin(getMapSize() / 2 - posX, radius);
	int tempMaxZ = xsMin(getMapSize() / 2 - posZ, radius);
	int tempRadiusCheck = radius * radius + radius;
	for(tempZ = tempMaxZ; >= tempMinZ){
		for(tempX = tempMaxX; >= tempMinX){
			if(tempRadiusCheck >= (tempX*tempX + tempZ*tempZ)){
				int terrainType = trGetTerrainType(tempX + posX, tempZ + posZ);
				int terrainSubType = trGetTerrainSubType(tempX + posX, tempZ + posZ);
				if(terrainType != oldTerrainType || terrainSubType != oldTerrainSubType){
					trPaintTerrain(tempX + posX, tempZ + posZ, tempX + posX, tempZ + posZ, newTerrainType, newTerrainSubType, false);
				}
			}
		}
	}
}
void paintCircleHeight(int posX = 0, int posZ = 0, int radius = 0, string terrain = "", float h = 0){
	int terrainType = getTerrainType(terrain);
	int terrainSubType = getTerrainSubType(terrain);
	int tempMinX = xsMax(0.0 - posX, 0.0 - radius);
	int tempMinZ = xsMax(0.0 - posZ, 0.0 - radius);
	int tempMaxX = xsMin(getMapSize() / 2 - posX, radius);
	int tempMaxZ = xsMin(getMapSize() / 2 - posZ, radius);
	int tempRadiusCheck = radius * radius + radius;
	for(tempZ = tempMaxZ; >= tempMinZ){
		for(tempX = tempMaxX; >= tempMinX){
			if(tempRadiusCheck >= (tempX*tempX + tempZ*tempZ)){
				trPaintTerrain(tempX + posX, tempZ + posZ, tempX + posX, tempZ + posZ, terrainType, terrainSubType, false);
				trChangeTerrainHeight(tempX + posX, tempZ + posZ, tempX + posX + 1, tempZ + posZ + 1, h, false);
			}
		}
	}
}
void paintCircleHeightLowerOnly(int posX = 0, int posZ = 0, int radius = 0, string terrain = "", float h = 0){
	int terrainType = getTerrainType(terrain);
	int terrainSubType = getTerrainSubType(terrain);
	int tempMinX = xsMax(0.0 - posX, 0.0 - radius);
	int tempMinZ = xsMax(0.0 - posZ, 0.0 - radius);
	int tempMaxX = xsMin(getMapSize() / 2 - posX, radius);
	int tempMaxZ = xsMin(getMapSize() / 2 - posZ, radius);
	int tempRadiusCheck = radius * radius + radius;
	for(tempZ = tempMaxZ; >= tempMinZ){
		for(tempX = tempMaxX; >= tempMinX){
			if(tempRadiusCheck >= (tempX*tempX + tempZ*tempZ)){
				trPaintTerrain(tempX + posX, tempZ + posZ, tempX + posX, tempZ + posZ, terrainType, terrainSubType, false);
				if(trGetTerrainHeight(tempX + posX, tempZ + posZ) > h){
					trChangeTerrainHeight(tempX + posX, tempZ + posZ, tempX + posX + 1, tempZ + posZ + 1, h, false);
				}
			}
		}
	}
}
void paintCircleHeightRaiseOnly(int posX = 0, int posZ = 0, int radius = 0, string terrain = "", float h = 0){
	int terrainType = getTerrainType(terrain);
	int terrainSubType = getTerrainSubType(terrain);
	int tempMinX = xsMax(0.0 - posX, 0.0 - radius);
	int tempMinZ = xsMax(0.0 - posZ, 0.0 - radius);
	int tempMaxX = xsMin(getMapSize() / 2 - posX, radius);
	int tempMaxZ = xsMin(getMapSize() / 2 - posZ, radius);
	int tempRadiusCheck = radius * radius + radius;
	for(tempZ = tempMaxZ; >= tempMinZ){
		for(tempX = tempMaxX; >= tempMinX){
			if(tempRadiusCheck >= (tempX*tempX + tempZ*tempZ)){
				trPaintTerrain(tempX + posX, tempZ + posZ, tempX + posX, tempZ + posZ, terrainType, terrainSubType, false);
				if(trGetTerrainHeight(tempX + posX, tempZ + posZ) < h){
					trChangeTerrainHeight(tempX + posX, tempZ + posZ, tempX + posX + 1, tempZ + posZ + 1, h, false);
				}
			}
		}
	}
}
void paintCircleRemovingWater(int posX = 0, int posZ = 0, int radius = 0, string terrain = ""){
	int terrainType = getTerrainType(terrain);
	int terrainSubType = getTerrainSubType(terrain);
	int tempMinX = xsMax(0.0 - posX, 0.0 - radius);
	int tempMinZ = xsMax(0.0 - posZ, 0.0 - radius);
	int tempMaxX = xsMin(getMapSize() / 2 - posX, radius);
	int tempMaxZ = xsMin(getMapSize() / 2 - posZ, radius);
	int tempRadiusCheck = radius * radius + radius;
	for(tempZ = tempMaxZ; >= tempMinZ){
		for(tempX = tempMaxX; >= tempMinX){
			if(tempRadiusCheck >= (tempX*tempX + tempZ*tempZ)){
				trPaintTerrain(tempX + posX, tempZ + posZ, tempX + posX, tempZ + posZ, terrainType, terrainSubType, false);
				int height = xsMax(trGetTerrainHeight(tempX + posX, tempZ + posZ), trGetWaterHeight(tempX + posX, tempZ + posZ));
				trChangeTerrainHeight(tempX + posX, tempZ + posZ, tempX + posX + 1, tempZ + posZ + 1, 15.0, false);
				trChangeTerrainHeight(tempX + posX, tempZ + posZ, tempX + posX + 1, tempZ + posZ + 1, height, false);
			}
		}
	}
}
void paintCircleHeight2(int posX = 0, int posZ = 0, int radius = 0, string terrain = "", float h = 0){
	int terrainType = getTerrainType(terrain);
	int terrainSubType = getTerrainSubType(terrain);
	int tempMinX = xsMax(0.0 - posX, 0.0 - radius);
	int tempMinZ = xsMax(0.0 - posZ, 0.0 - radius);
	int tempMaxX = xsMin(getMapSize() / 2 - posX, radius);
	int tempMaxZ = xsMin(getMapSize() / 2 - posZ, radius);
	int tempRadiusCheck = radius * radius + radius;
	for(tempZ = tempMaxZ; >= tempMinZ){
		for(tempX = tempMaxX; >= tempMinX){
			if(tempRadiusCheck >= (tempX*tempX + tempZ*tempZ)){
				trPaintTerrain(tempX + posX, tempZ + posZ, tempX + posX, tempZ + posZ, terrainType, terrainSubType, false);
			}
		}
	}
	tempRadiusCheck = (radius - 1) * (radius - 1) + (radius - 1);
	for(tempZ = tempMaxZ; >= tempMinZ){
		for(tempX = tempMaxX; >= tempMinX){
			if(tempRadiusCheck >= (tempX*tempX + tempZ*tempZ)){
				trChangeTerrainHeight(tempX + posX, tempZ + posZ, tempX + posX + 1, tempZ + posZ + 1, h, false);
			}
		}
	}
}
void changeCircleHeight(int posX = 0, int posZ = 0, int radius = 0, float h = 0){
	int tempMinX = xsMax(0.0 - posX, 0.0 - radius);
	int tempMinZ = xsMax(0.0 - posZ, 0.0 - radius);
	int tempMaxX = xsMin(getMapSize() / 2 - posX, radius);
	int tempMaxZ = xsMin(getMapSize() / 2 - posZ, radius);
	int tempRadiusCheck = radius * radius + radius;
	for(tempZ = tempMaxZ; >= tempMinZ){
		for(tempX = tempMaxX; >= tempMinX){
			if(tempRadiusCheck >= (tempX*tempX + tempZ*tempZ)){
				trChangeTerrainHeight(tempX + posX, tempZ + posZ, tempX + posX + 1, tempZ + posZ + 1, h, false);
			}
		}
	}
}
void changeTerrainHeight(int amount = 0){
	for(z = 0; <= getMapSize() / 2) {
		for(x = 0; <= getMapSize() / 2) {
			float height = trGetTerrainHeight(x, z);
			trChangeTerrainHeight(x, z, x, z, height + amount, false);
		}
	}
}

void paintMap(string terrain = ""){
	trPaintTerrain(0, 0, getMapSize() / 2 - 1, getMapSize() / 2 - 1, getTerrainType(terrain), getTerrainSubType(terrain), false);
}
void smooth(int amount = 0){
	subModeEnter("Simulation", "Editor");
	for(i = 0; < amount){
		terrainFilter();
	}
	subModeLeave("Simulation", "Editor");
	modeEnter("Pregame");
	modeEnter("Simulation");
}
void changeGlobalHeight(float height = 0){
	subModeEnter("Simulation", "Editor");
	terrainAdjustGlobalHeight(height);
	subModeLeave("Simulation", "Editor");
	modeEnter("Pregame");
	modeEnter("Simulation");
}
void replaceTerrainBelowHeightMin(string oldTerrain = "", string newTerrain = "", float height = 0.0){
	int oldTerrainType = getTerrainType(oldTerrain);
	int oldTerrainSubType = getTerrainSubType(oldTerrain);
	int newTerrainType = getTerrainType(newTerrain);
	int newTerrainSubType = getTerrainSubType(newTerrain);
	int maxX = getMapSize() / 2;
	int maxZ = getMapSize() / 2;
	for(z = 0; < maxZ) {
		for(x = 0; < maxX) {
			int terrainType = trGetTerrainType(x, z);
			int terrainSubType = trGetTerrainSubType(x, z);
			float height0 = trGetTerrainHeight(x, z);
			float height1 = trGetTerrainHeight(x + 1, z);
			float height2 = trGetTerrainHeight(x, z + 1);
			float height3 = trGetTerrainHeight(x + 1, z + 1);
			float minHeight = xsMin(xsMin(height0, height1), xsMin(height2, height3));
			if(terrainType == oldTerrainType && terrainSubType == oldTerrainSubType && minHeight <= height){
				trPaintTerrain(x, z, x, z, newTerrainType, newTerrainSubType, false);
			}
		}
	}
}
void replaceTerrainBelowHeightMax(string oldTerrain = "", string newTerrain = "", float height = 0.0){
	int oldTerrainType = getTerrainType(oldTerrain);
	int oldTerrainSubType = getTerrainSubType(oldTerrain);
	int newTerrainType = getTerrainType(newTerrain);
	int newTerrainSubType = getTerrainSubType(newTerrain);
	int maxX = getMapSize() / 2;
	int maxZ = getMapSize() / 2;
	for(z = 0; < maxZ) {
		for(x = 0; < maxX) {
			int terrainType = trGetTerrainType(x, z);
			int terrainSubType = trGetTerrainSubType(x, z);
			float height0 = trGetTerrainHeight(x, z);
			float height1 = trGetTerrainHeight(x + 1, z);
			float height2 = trGetTerrainHeight(x, z + 1);
			float height3 = trGetTerrainHeight(x + 1, z + 1);
			float maxHeight = xsMax(xsMax(height0, height1), xsMax(height2, height3));
			if(terrainType == oldTerrainType && terrainSubType == oldTerrainSubType && maxHeight <= height){
				trPaintTerrain(x, z, x, z, newTerrainType, newTerrainSubType, false);
			}
		}
	}
}
void replaceTerrainAboveHeightMin(string oldTerrain = "", string newTerrain = "", float height = 0.0){
	int oldTerrainType = getTerrainType(oldTerrain);
	int oldTerrainSubType = getTerrainSubType(oldTerrain);
	int newTerrainType = getTerrainType(newTerrain);
	int newTerrainSubType = getTerrainSubType(newTerrain);
	int maxX = getMapSize() / 2;
	int maxZ = getMapSize() / 2;
	for(z = 0; < maxZ) {
		for(x = 0; < maxX) {
			int terrainType = trGetTerrainType(x, z);
			int terrainSubType = trGetTerrainSubType(x, z);
			float height0 = trGetTerrainHeight(x, z);
			float height1 = trGetTerrainHeight(x + 1, z);
			float height2 = trGetTerrainHeight(x, z + 1);
			float height3 = trGetTerrainHeight(x + 1, z + 1);
			float minHeight = xsMin(xsMin(height0, height1), xsMin(height2, height3));
			if(terrainType == oldTerrainType && terrainSubType == oldTerrainSubType && minHeight >= height){
				trPaintTerrain(x, z, x, z, newTerrainType, newTerrainSubType, false);
			}
		}
	}
}
void replaceTerrainAboveHeightMax(string oldTerrain = "", string newTerrain = "", float height = 0.0){
	int oldTerrainType = getTerrainType(oldTerrain);
	int oldTerrainSubType = getTerrainSubType(oldTerrain);
	int newTerrainType = getTerrainType(newTerrain);
	int newTerrainSubType = getTerrainSubType(newTerrain);
	int maxX = getMapSize() / 2;
	int maxZ = getMapSize() / 2;
	for(z = 0; < maxZ) {
		for(x = 0; < maxX) {
			int terrainType = trGetTerrainType(x, z);
			int terrainSubType = trGetTerrainSubType(x, z);
			float height0 = trGetTerrainHeight(x, z);
			float height1 = trGetTerrainHeight(x + 1, z);
			float height2 = trGetTerrainHeight(x, z + 1);
			float height3 = trGetTerrainHeight(x + 1, z + 1);
			float maxHeight = xsMax(xsMax(height0, height1), xsMax(height2, height3));
			if(terrainType == oldTerrainType && terrainSubType == oldTerrainSubType && maxHeight >= height){
				trPaintTerrain(x, z, x, z, newTerrainType, newTerrainSubType, false);
			}
		}
	}
}
void replaceTerrainAtMaxSteepness(string oldTerrain = "", string newTerrain = "", float difference = 0.0){
	int oldTerrainType = getTerrainType(oldTerrain);
	int oldTerrainSubType = getTerrainSubType(oldTerrain);
	int newTerrainType = getTerrainType(newTerrain);
	int newTerrainSubType = getTerrainSubType(newTerrain);
	int maxX = getMapSize() / 2;
	int maxZ = getMapSize() / 2;
	for(z = 0; < maxZ) {
		for(x = 0; < maxX) {
			int terrainType = trGetTerrainType(x, z);
			int terrainSubType = trGetTerrainSubType(x, z);
			float height0 = trGetTerrainHeight(x, z);
			float height1 = trGetTerrainHeight(x + 1, z);
			float height2 = trGetTerrainHeight(x, z + 1);
			float height3 = trGetTerrainHeight(x + 1, z + 1);
			float minHeight = xsMin(xsMin(height0, height1), xsMin(height2, height3));
			float maxHeight = xsMax(xsMax(height0, height1), xsMax(height2, height3));
			if(terrainType == oldTerrainType && terrainSubType == oldTerrainSubType && (maxHeight - minHeight <= difference)){
				trPaintTerrain(x, z, x, z, newTerrainType, newTerrainSubType, false);
			}
		}
	}
}
void replaceTerrainAtMinSteepness(string oldTerrain = "", string newTerrain = "", float difference = 0.0){
	int oldTerrainType = getTerrainType(oldTerrain);
	int oldTerrainSubType = getTerrainSubType(oldTerrain);
	int newTerrainType = getTerrainType(newTerrain);
	int newTerrainSubType = getTerrainSubType(newTerrain);
	int maxX = getMapSize() / 2;
	int maxZ = getMapSize() / 2;
	for(z = 0; < maxZ) {
		for(x = 0; < maxX) {
			int terrainType = trGetTerrainType(x, z);
			int terrainSubType = trGetTerrainSubType(x, z);
			float height0 = trGetTerrainHeight(x, z);
			float height1 = trGetTerrainHeight(x + 1, z);
			float height2 = trGetTerrainHeight(x, z + 1);
			float height3 = trGetTerrainHeight(x + 1, z + 1);
			float minHeight = xsMin(xsMin(height0, height1), xsMin(height2, height3));
			float maxHeight = xsMax(xsMax(height0, height1), xsMax(height2, height3));
			if(terrainType == oldTerrainType && terrainSubType == oldTerrainSubType && (maxHeight - minHeight >= difference)){
				trPaintTerrain(x, z, x, z, newTerrainType, newTerrainSubType, false);
			}
		}
	}
}
bool unitOnTerrain(int unitName = 0, string terrain = ""){
	if(unitName < 0)return (false);
	vector unitPosV = kbGetBlockPosition(""+unitName, true);
	int unitPosX = xsVectorGetX(unitPosV) / 2.0;
	int unitPosZ = xsVectorGetZ(unitPosV) / 2.0;
	int terrainType = getTerrainType(terrain);
	int terrainSubType = getTerrainSubType(terrain);
	int foundTerrainType = trGetTerrainType(unitPosX, unitPosZ);
	int foundTerrainSubType = trGetTerrainSubType(unitPosX, unitPosZ);
	if(foundTerrainType == terrainType && foundTerrainSubType == terrainSubType)return (true);
	return (false);
}

float heightAboveTerrain(vector posV = vector(0.0, 0.0, 0.0)){
	float tilesFloatX = xsVectorGetX(posV) / 2.0;
	float tilesFloatZ = xsVectorGetZ(posV) / 2.0;
	float tilesModX = modFloat(tilesFloatX, 1.0);
	float tilesModZ = modFloat(tilesFloatZ, 1.0);
	int minHeightX = xsFloor(tilesFloatX);
	int minHeightZ = xsFloor(tilesFloatZ);
	int maxHeightX = xsCeil(tilesFloatX);
	int maxHeightZ = xsCeil(tilesFloatZ);
	float terrainHeightMinMin = trGetTerrainHeight(minHeightX, minHeightZ);
	float terrainHeightMaxMin = trGetTerrainHeight(maxHeightX, minHeightZ);
	float terrainHeightMinMax = trGetTerrainHeight(minHeightX, maxHeightZ);
	float terrainHeightMaxMax = trGetTerrainHeight(maxHeightX, maxHeightZ);
	float heightMinZ = interpolate(terrainHeightMinMin, terrainHeightMaxMin, tilesModX);
	float heightMaxZ = interpolate(terrainHeightMinMax, terrainHeightMaxMax, tilesModX);
	return (xsVectorGetY(posV) - interpolate(heightMinZ, heightMaxZ, tilesModZ));
}

void setTerrainHeightForTerrain(string oldTerrain = "", float h = 0.0){
	int oldTerrainType = getTerrainType(oldTerrain);
	int oldTerrainSubType = getTerrainSubType(oldTerrain);
	int maxX = getMapSize() / 2;
	int maxZ = getMapSize() / 2;
	for(z = 0; < maxZ) {
		for(x = 0; < maxX) {
			int terrainType = trGetTerrainType(x, z);
			int terrainSubType = trGetTerrainSubType(x, z);
			if(terrainType == oldTerrainType && terrainSubType == oldTerrainSubType){
				trChangeTerrainHeight(x, z, x + 1, z + 1, h, false);
			}
		}
	}
}


vector getRandomTileMatchingTerrain(string terrain = "", int border = 0){
	int terrainType = getTerrainType(terrain);
	int terrainSubType = getTerrainSubType(terrain);
	int maxX = getMapSize() / 2 - border;
	int maxZ = getMapSize() / 2 - border;
	int matchCount = 0;
	int foundTerrainType = 0;
	int foundTerrainSubType =0;
	for(z = border; < maxZ) {
		for(x = border; < maxX) {
			foundTerrainType = trGetTerrainType(x, z);
			foundTerrainSubType = trGetTerrainSubType(x, z);
			if(foundTerrainType == terrainType && foundTerrainSubType == terrainSubType){
				matchCount = matchCount + 1;
			}
		}
	}
	int choice = randomInt(0, matchCount - 1);
	matchCount = 0;
	for(z = border; < maxZ) {
		for(x = border; < maxX) {
			foundTerrainType = trGetTerrainType(x, z);
			foundTerrainSubType = trGetTerrainSubType(x, z);
			if(foundTerrainType == terrainType && foundTerrainSubType == terrainSubType){
				if(matchCount == choice)return (xsVectorSet(x, 0, z));
				matchCount = matchCount + 1;
			}
		}
	}
	return (vector(-1.0, -1.0, -1.0));
}
vector calculateUpVectorAtTile(int posX = 0, int posZ = 0){
	float heightX0Z0 = trGetTerrainHeight(posX, posZ);
	float heightX1Z0 = trGetTerrainHeight(posX + 1, posZ);
	float heightX0Z1 = trGetTerrainHeight(posX, posZ + 1);
	float heightX1Z1 = trGetTerrainHeight(posX + 1, posZ + 1);
	float vectorX = heightX1Z0 + heightX1Z1 - heightX0Z0 - heightX0Z1;
	float vectorZ = heightX0Z1 + heightX1Z1 - heightX0Z0 - heightX1Z0;
	return (xsVectorSet(vectorX,0,vectorZ));
}
// ### UNIT

int deployLocUsingCineBlock(float posX = 0.0, float posZ = 0.0, string unit = "", int p = 0){
	int cineBlockId = deployLoc(posX, posZ, "Cinematic Block", p);
	trUnitSelectClear();
	if(cineBlockId == -1)return (cineBlockId);
	trUnitSelect(""+cineBlockId, true);
	trUnitChangeProtoUnit(unit);
	return (cineBlockId);
}
void deployCluster(float posX = 0.0, float posZ = 0.0, string unit = "", int p = 0, int count = 0,
	float radius = 0.0, bool forceOnMap = false){
	for(i = 0; < count){
		vector loc = randomCircleLoc(posX, posZ, radius);
		float finalPosX = xsVectorGetX(loc);
		float finalPosZ = xsVectorGetZ(loc);
		if(forceOnMap){
			finalPosX = clamp(0.0, toMetres(1.0), finalPosX);
			finalPosZ = clamp(0.0, toMetres(1.0), finalPosZ);
		}
		deployLoc(finalPosX, finalPosZ, unit, p);
	}
}

void dC(float pX = 0.0, float pZ = 0.0, string u = "", int p = 0, int c = 0, float r = 0.0, int c2 = 0,
	float r2 = 0.0, bool forceOnMap = false){
	for(i = 0; < c2){
		vector loc = randomCircleLoc(pX, pZ, r2);
		float finalPosX = xsVectorGetX(loc);
		float finalPosZ = xsVectorGetZ(loc);
		deployCluster(finalPosX, finalPosZ, u, p, c, r, forceOnMap);
	}
}



void dM(string u = "", int p = 0, int c = 0, float r = 0.0, int c2 = 0){
	for(i = 0; < c2){
		deployCluster(randomFloat(0.0, toMetres(1.0)), randomFloat(0.0, toMetres(1.0)), u, p, c, r);
	}
}


void paintTrees(string terrain = "", string tree = ""){
	int terrainType = getTerrainType(terrain);
	int terrainSubType = getTerrainSubType(terrain);
	int k = 0;
	for(i = 0; < getMapSize() / 2) {
		for(j = 0; < getMapSize() / 2) {
			if(k == 0 && trGetTerrainType(i, j) == terrainType && trGetTerrainSubType(i, j) == terrainSubType){
				deployLoc(i * 2  + 1, j * 2 + 1, "Victory Marker", 0);
			}
			k = 1 - k;
		}
		//k = 1 - k;
	}
	trUnitSelectClear();
	trUnitSelect("0");
	trUnitChangeInArea(0, 0, "Victory Marker", tree, 999.0);
}


void paintUnit(string terrain = "", string unit = "", int p = 0, float c = 0.1){
	int terrainType = getTerrainType(terrain);
	int terrainSubType = getTerrainSubType(terrain);
	for(i = 0; < getMapSize() / 2) {
		for(j = 0; < getMapSize() / 2) {
			if(trGetTerrainType(i, j) == terrainType && trGetTerrainSubType(i, j) == terrainSubType && randomFloat(0.0, 1.0) <= c){
				deployLoc(i * 2 + 1, j * 2 + 1, unit, p);
			}
		}
	}
}

void clearMap(string terrain = "", float height = 0.0){
	trChangeTerrainHeight(0, 0, getMapSize() / 2, getMapSize() / 2, 15, false);
	trChangeTerrainHeight(0, 0, getMapSize() / 2, getMapSize() / 2, height, false);
	trPaintTerrain(0, 0, getMapSize() / 2 - 1, getMapSize() / 2 - 1, 0,0, false);
	refreshPassability();
	trPaintTerrain(0, 0, getMapSize() / 2 - 1, getMapSize() / 2 - 1, getTerrainType(terrain), getTerrainSubType(terrain), false);
	trRenderSnow(0.0);
	trSetCloudData(1.5, 0.6, 0.6, 2, 0, 1);
}

float randomFloatWeighted(float min = 0.0, float max = 1.0, int weight = 1){
	float value = max;
	/*
	ERROR
	for(i = 0; < weight){
		value = rmRandFloat(min, value);
	}*/
	return (value);
}

void paintWaterKeepingMapPassable(float waterHeight = 0.0, float depth = 1.0, vector waterColour = vector(1.0, 1.0, 1.0)){
	int oldTerrainType = trGetTerrainType(0, 0);
	int oldTerrainSubType = trGetTerrainSubType(0, 0);
	trCoverTerrainWithWater(waterHeight, 1.0,"Aegean Sea");
	trPaintWaterColor(waterColour,0,0,toTiles(1.0)+1,toTiles(1.0)+1);
	trChangeTerrainHeight(0, 0, (getMapSize() / 2), (getMapSize() / 2), waterHeight - depth, false);
	trPaintTerrain(0, 0, (getMapSize() / 2) - 1, (getMapSize() / 2) - 1, oldTerrainType, oldTerrainSubType, false);
	//waterMap = true;
}

void createStartTown(){
	
	string baseTerrain = "ShorelineJungleA";
	int mapId = 0;
	clearMap("ShorelineJungleA", 0.0);
	paintWaterKeepingMapPassable(0.0, 5.0, vector(0.2, 0.6, 0.8));
	int sideChosen = randomInt(0, 3);
	for(i = 0; < 100) {
		if(sideChosen == 0)tempV = xsVectorSet(randomFloat(0, toTiles(1.0)), 0.0, randomFloat(toTiles(0.25), toTiles(1.0)));
		if(sideChosen == 1)tempV = xsVectorSet(randomFloat(toTiles(0.25), toTiles(1.0)), 0.0, randomFloat(0, toTiles(1.0)));
		if(sideChosen == 2)tempV = xsVectorSet(randomFloat(0, toTiles(1.0)), 0.0, randomFloat(0, toTiles(0.75)));
		if(sideChosen == 3)tempV = xsVectorSet(randomFloat(0, toTiles(0.75)), 0.0, randomFloat(0, toTiles(1.0)));
		for(j = 0; < 5) {
			tempV2 = randomCircleLoc(xsVectorGetX(tempV), xsVectorGetZ(tempV), 10.0);
			paintCircleHeight(xsVectorGetX(tempV2), xsVectorGetZ(tempV2), toTiles(0.04),
				"GrassDirt50", randomFloatWeighted(1.0, 2.0, 2));
		}
	}
	for(i = 0; < 30) {
		if(sideChosen == 0)tempV = xsVectorSet(randomFloat(0, toTiles(1.0)), 0.0, randomFloat(toTiles(0.6), toTiles(1.0)));
		if(sideChosen == 1)tempV = xsVectorSet(randomFloat(toTiles(0.6), toTiles(1.0)), 0.0, randomFloat(0, toTiles(1.0)));
		if(sideChosen == 2)tempV = xsVectorSet(randomFloat(0, toTiles(1.0)), 0.0, randomFloat(0, toTiles(0.4)));
		if(sideChosen == 3)tempV = xsVectorSet(randomFloat(0, toTiles(0.4)), 0.0, randomFloat(0, toTiles(1.0)));
		for(j = 0; < 20) {
			tempV2 = randomCircleLoc(xsVectorGetX(tempV), xsVectorGetZ(tempV), 10.0);
			paintCircleHeight(xsVectorGetX(tempV2), xsVectorGetZ(tempV2), toTiles(0.04),
				"GrassB", randomFloatWeighted(2.0, 5.0, 2));
		}
	}
	for(i = 0; < 10) {
		if(sideChosen == 0)tempV = xsVectorSet(randomFloat(0, toTiles(1.0)), 0.0, randomFloat(toTiles(0.8), toTiles(1.0)));
		if(sideChosen == 1)tempV = xsVectorSet(randomFloat(toTiles(0.8), toTiles(1.0)), 0.0, randomFloat(0, toTiles(1.0)));
		if(sideChosen == 2)tempV = xsVectorSet(randomFloat(0, toTiles(1.0)), 0.0, randomFloat(0, toTiles(0.2)));
		if(sideChosen == 3)tempV = xsVectorSet(randomFloat(0, toTiles(0.2)), 0.0, randomFloat(0, toTiles(1.0)));
		for(j = 0; < 20) {
			tempV2 = randomCircleLoc(xsVectorGetX(tempV), xsVectorGetZ(tempV), 15.0);
			paintCircleHeight(xsVectorGetX(tempV2), xsVectorGetZ(tempV2), toTiles(0.04),
				"ForestFloorOak", randomFloatWeighted(4.0, 8.0, 2));
		}
	}
	smooth(10);
	replaceTerrainBelowHeightMax("ShorelineJungleA", "CoralC", -1.0);
	replaceTerrainBelowHeightMax("CoralC", "Black", -2.0);
	refreshPassability();
	
	paintTrees("ForestFloorOak", "Oak Tree");
	paintUnit("GrassDirt50", "Market", 0, 0.001);
	paintUnit("GrassDirt50", "Academy", 0, 0.001);
	paintUnit("GrassDirt50", "Temple", 0, 0.001);
	paintUnit("GrassDirt50", "Armory", 0, 0.001);
	paintUnit("GrassDirt50", "House", 0, 0.01);
	paintUnit("GrassDirt50", "Oak Tree", 0, 0.01);
	paintUnit("GrassDirt50", "Fence Stone", 0, 0.004);
	paintUnit("GrassDirt50", "Grass", 0, 0.01);
	paintUnit("GrassDirt50", "Seagull", 0, 0.001);
	paintUnit("GrassDirt50", "Hoplite", 0, 0.005);
	paintUnit("GrassDirt50", "Toxotes", 0, 0.005);
	paintUnit("GrassDirt50", "Hippikon", 0, 0.005);
	paintUnit("GrassB", "Storehouse", 0, 0.01);
	paintUnit("GrassB", "Wood Pile 1", 0, 0.001);
	paintUnit("GrassB", "Wood Pile 2", 0, 0.001);
	paintUnit("GrassB", "Wood Pile 3", 0, 0.001);
	paintUnit("GrassB", "Villager Greek", 0, 0.01);
	paintUnit("GrassB", "Oak Stump", 0, 0.1);
	paintUnit("GrassB", "Oak Tree", 0, 0.1);
	paintUnit("CoralC", "Dock", 0, 0.02);
	paintUnit("Black", "Fish - Herring", 0, 0.01);
	paintUnit("Black", "Fishing Ship Greek", 0, 0.004);
	
	int setna = trGetNextUnitScenarioNameNumber();
	if(sideChosen==0)deployCluster(randomFloat(toMetres(0.2), toMetres(0.8)), toMetres(0.5),
		"Setna", 0, 1, 10.0, true);
	if(sideChosen==1)deployCluster(toMetres(0.5), randomFloat(toMetres(0.2), toMetres(0.8)),
		"Setna", 0, 1, 10.0, true);
	if(sideChosen==2)deployCluster(randomFloat(toMetres(0.2), toMetres(0.8)), toMetres(0.5),
		"Setna", 0, 1, 10.0, true);
	if(sideChosen==3)deployCluster(toMetres(0.5), randomFloat(toMetres(0.2), toMetres(0.8)),
		"Setna", 0, 1, 10.0, true);
	int bird = trGetNextUnitScenarioNameNumber();
	if(sideChosen==0)deployCluster(toMetres(0.5), toMetres(0.05), "Oar Footprint", cNumberNonGaiaPlayers, 1, 10.0, true);
	if(sideChosen==1)deployCluster(toMetres(0.05), toMetres(0.5), "Oar Footprint", cNumberNonGaiaPlayers, 1, 10.0, true);
	if(sideChosen==2)deployCluster(toMetres(0.5), toMetres(0.95), "Oar Footprint", cNumberNonGaiaPlayers, 1, 10.0, true);
	if(sideChosen==3)deployCluster(toMetres(0.95), toMetres(0.5), "Oar Footprint", cNumberNonGaiaPlayers, 1, 10.0, true);
	trUnitSelectClear();
	trUnitSelect(""+bird, true);
	trUnitChangeProtoUnit("Victory Marker");
	for(p = 1; <= cNumberNonGaiaPlayers) {
		if(sideChosen==0)deployCluster(toMetres(0.5), toMetres(0.05), "Transport Ship Greek", p, 1, 10.0, true);
		if(sideChosen==1)deployCluster(toMetres(0.05), toMetres(0.5), "Transport Ship Greek", p, 1, 10.0, true);
		if(sideChosen==2)deployCluster(toMetres(0.5), toMetres(0.95), "Transport Ship Greek", p, 1, 10.0, true);
		if(sideChosen==3)deployCluster(toMetres(0.95), toMetres(0.5), "Transport Ship Greek", p, 1, 10.0, true);
	}
	
}

void createSafeArea(){
	string baseTerrain = "CliffEgyptianB";
	trSetCivAndCulture(0, 0, 0);
	clearMap("Black", -5.0);
	int centrePosX = randomInt(toTiles(0.4), toTiles(0.6));
	int centrePosZ = randomInt(toTiles(0.4), toTiles(0.6));
	for(i = 0; < 10) {
		tempV = randomCircleLoc(centrePosX, centrePosZ, 30.0); //dont know what this does
		for(j = 0; < 20) { //number of circles to make
			tempV2 = randomCircleLoc(xsVectorGetX(tempV), xsVectorGetZ(tempV), 40.0); //also available area
			paintCircleHeight(xsVectorGetX(tempV2), xsVectorGetZ(tempV2), toTiles(0.02), "CliffEgyptianB", 30.0); //to tiles is radius and does internal area
		}
	}
	
	/*
	randomCircleLoc picks random circle at the location of the first two values and radius the thrid
	and returns as a vector
	then the second bit does it again
	the idea is to do big groups and then smaller groups
	the idea is to make it "clump"
	So if you want some cliff in some random areas you pick the the locations (Outer loop) and then pick areas near the original location to actually paint (The inner loop)
	This is so you don;t get just circles everywhere but instead those circles are distorted by painting in random areas nearby causing it to distort
	and if you want further distortions you can then do a third loop inside to distort event further
	*even
	I would do whatever the cohence algorithm in AOM does since I think that does excellent areas but I not got a clue how it does it to repl
	*/
	smooth(20);
	replaceTerrainBelowHeightMin("CliffEgyptianB", "CliffEgyptianA", 12.0);
	replaceTerrainAboveHeightMax("SandC", "CliffNorseA", 8.0);
	replaceTerrainAboveHeightMax("SandD", "SandC", 14.0);
	refreshPassability();
	
	paintUnit("Black", "Pine", 0, 0.002);
	paintUnit("Black", "Oak Tree", 0, 0.01);
	replaceTerrainAboveHeightMin("Black", "SandC", -999.0);
	refreshPassability();
	int templeSafeArea = trGetNextUnitScenarioNameNumber();
	deployCluster(2.0*centrePosX, 2.0*centrePosZ, "Temple Underworld", 0, 1, 20.0, true);
	paintUnit("OlympusTile", "Ruins", 0, 0.01);
	paintUnit("OlympusTile", "Columns", 0, 0.01);
	paintUnit("OlympusTile", "Fallen Columns", 0, 0.01);
}

void createUluru(){
	string baseTerrain = "CliffEgyptianB";
	trSetCivAndCulture(0, 0, 0);
	clearMap("Black", -5.0);
	int centrePosX = randomInt(toTiles(0.45), toTiles(0.55));
	int centrePosZ = randomInt(toTiles(0.45), toTiles(0.55));
	for(i = 0; < 10) {
		tempV = randomCircleLoc(centrePosX, centrePosZ, 20.0); //dont know what this does
		for(j = 0; < 10) { //number of circles to make
			tempV2 = randomCircleLoc(xsVectorGetX(tempV), xsVectorGetZ(tempV), 30.0); //also available area
			paintCircleHeight(xsVectorGetX(tempV2), xsVectorGetZ(tempV2), toTiles(0.08), "CliffEgyptianB", 20.0); //to tiles is radius and does internal area
		}
	}
	
	/*
	randomCircleLoc picks random circle at the location of the first two values and radius the thrid
	and returns as a vector
	then the second bit does it again
	the idea is to do big groups and then smaller groups
	the idea is to make it "clump"
	So if you want some cliff in some random areas you pick the the locations (Outer loop) and then pick areas near the original location to actually paint (The inner loop)
	This is so you don;t get just circles everywhere but instead those circles are distorted by painting in random areas nearby causing it to distort
	and if you want further distortions you can then do a third loop inside to distort event further
	*even
	I would do whatever the cohence algorithm in AOM does since I think that does excellent areas but I not got a clue how it does it to repl
	*/
	smooth(20);
	replaceTerrainBelowHeightMin("CliffEgyptianB", "CliffEgyptianA", 12.0);
	replaceTerrainAboveHeightMax("SandC", "CliffNorseA", 8.0);
	replaceTerrainAboveHeightMax("SandD", "SandC", 14.0);
	refreshPassability();
	
	paintUnit("Black", "Pine", 0, 0.002);
	paintUnit("Black", "Oak Tree", 0, 0.01);
	replaceTerrainAboveHeightMin("Black", "SandC", -999.0);
	refreshPassability();
	int templeSafeArea = trGetNextUnitScenarioNameNumber();
	deployCluster(2.0*centrePosX, 2.0*centrePosZ, "Temple Underworld", 0, 1, 20.0, true);
	paintUnit("OlympusTile", "Ruins", 0, 0.01);
	paintUnit("OlympusTile", "Columns", 0, 0.01);
	paintUnit("OlympusTile", "Fallen Columns", 0, 0.01);
}

void BuildSandMaze(){
	clearMap("SandC", 2.0);
	for(i = 0; < 100){
		tempV = xsVectorSet(toTiles(randomFloat(0.2, 0.8)), 0.0, toTiles(randomFloat(0.2, 0.8)));
		tempF = randomInt(0, 2) * 10 - 5;
		for(j = 0; < 4) {
			tempV2 = randomCircleLoc(xsVectorGetX(tempV), xsVectorGetZ(tempV), 10.0);
			changeCircleHeight(xsVectorGetX(tempV2), xsVectorGetZ(tempV2), toTiles(0.05), tempF);
		}
	}
	smooth(3);
	replaceTerrainAtMaxSteepness("SandC", "CliffEgyptianA", 0.8);
	trChangeTerrainHeight(0, 0, toTiles(1.0), toTiles(1.0), 0, false);
	setTerrainHeightForTerrain("CliffEgyptianA", 5.0);
	smooth(2);
	setTerrainHeightForTerrain("SandC", 0.0);
	replaceTerrainAboveHeightMin("CliffEgyptianA", "ForestfloorPalm", 4.0);
	replaceTerrainBelowHeightMax("CliffEgyptianA", "SandC", 0.0);
	smooth(1);
	paintTrees("ForestfloorPalm", "Palm");
	refreshPassability();
}

void createForestArea(){
	string baseTerrain = "GrassA";
	int mapId = 2;
	int centrePosX = 0;
	int centrePosZ= 0;
	clearMap("ForestFloorOak", 5.0);
	for(i = 0; < 30) {
		centrePosX = randomInt(toTiles(0), toTiles(1.0));
		centrePosZ = randomInt(toTiles(0), toTiles(1.0));
		for(j = 0; < 3) {
			tempV = randomCircleLoc(centrePosX, centrePosZ, 20.0);
			for(k = 0; < 10) {
				tempV2 = randomCircleLoc(xsVectorGetX(tempV), xsVectorGetZ(tempV), 10.0);
				paintCircleHeight(xsVectorGetX(tempV2), xsVectorGetZ(tempV2), toTiles(randomFloat(0.0, 0.03)), "GrassA", 3.0);
			}
		}
	}
	for(i = 0; < 8) {
		centrePosX = randomInt(toTiles(0), toTiles(1.0));
		centrePosZ = randomInt(toTiles(0), toTiles(1.0));
		for(j = 0; < 3) {
			tempV = randomCircleLoc(centrePosX, centrePosZ, 20.0);
			for(k = 0; < 4) {
				tempV2 = randomCircleLoc(xsVectorGetX(tempV), xsVectorGetZ(tempV), 10.0);
				int floatCircleSize = toTiles(randomFloat(0.0, 0.04));
				changeCircleHeight(xsVectorGetX(tempV2), xsVectorGetZ(tempV2), floatCircleSize, 15.0);
				replaceCircle(xsVectorGetX(tempV2), xsVectorGetZ(tempV2), floatCircleSize, "ForestFloorOak", "ForestFloorPine");
				replaceCircle(xsVectorGetX(tempV2), xsVectorGetZ(tempV2), floatCircleSize, "GrassA", "SnowGrass75");
			}
		}
	}
	replaceTerrainAtMinSteepness("GrassA", "CliffGreekA", 2.0);
	for(i = 0; < 30) {
		tempV = xsVectorSet(toTiles(randomFloat(0.0, 1.0)), 0.0, toTiles(randomFloat(0.0, 1.0)));
		for(j = 0; < 10) {
			tempV2 = randomCircleLoc(xsVectorGetX(tempV), xsVectorGetZ(tempV), 10.0);
			replaceCircle(xsVectorGetX(tempV2), xsVectorGetZ(tempV2), toTiles(0.02), "GrassA", "GrassDirt25");
		}
	}
	for(i = 0; < 30) {
		tempV = xsVectorSet(toTiles(randomFloat(0.0, 1.0)), 0.0, toTiles(randomFloat(0.0, 1.0)));
		for(j = 0; < 10) {
			tempV2 = randomCircleLoc(xsVectorGetX(tempV), xsVectorGetZ(tempV), 10.0);
			replaceCircle(xsVectorGetX(tempV2), xsVectorGetZ(tempV2), toTiles(0.01), "GrassA", "GrassDirt50");
		}
	}
	smooth(3);
	refreshPassability();
	paintTrees("ForestFloorOak", "Oak Autumn");
	paintTrees("ForestFloorPine", "Pine");
	paintUnit("GrassA", "Flowers", 0, 0.025);
	paintUnit("GrassDirt25", "Grass", 0, 0.025);
	paintUnit("GrassDirt50", "Bush", 0, 0.025);
}
void createDeepForestArea(){
	DestroyNumber = trGetNextUnitScenarioNameNumber();
	for(n = DontDestroyBelow ; < DestroyNumber){
		trUnitSelectClear();
		trUnitSelect(""+n);
		trUnitDestroy();
	}
	//trSetFogAndBlackmap(true,true);
	//[MAP]
	string baseTerrain = "GaiaCreepA";
	int ABORT = 0;
	int centrePosX = 0;
	int centrePosZ= 0;
	clearMap("ForestFloorPine", 5.0);
	for(i = 0; < 10) {
		centrePosX = randomInt(toTiles(0), toTiles(1.0));
		centrePosZ = randomInt(toTiles(0), toTiles(1.0));
		for(j = 0; < 10) {
			tempV = randomCircleLoc(centrePosX, centrePosZ, 20.0);
			for(k = 0; < 10) {
				tempV2 = randomCircleLoc(xsVectorGetX(tempV), xsVectorGetZ(tempV), 40.0);
				paintCircleHeight(xsVectorGetX(tempV2), xsVectorGetZ(tempV2), toTiles(randomFloat(0.0, 0.03)), "GaiaCreepA", 5.0);
			}
		}
	}
	vector tileForEnd = getRandomTileMatchingTerrain("GaiaCreepA", 10);
	int EndTileX = xsVectorGetX(tileForEnd);
	int EndTileZ = xsVectorGetZ(tileForEnd);
	float EndHeight = trGetTerrainHeight(EndTileX, EndTileZ);
	
	float EndMetreX = EndTileX*2+1;
	float EndMetreZ = EndTileZ*2+1;
	
	vector tileForStart = getRandomTileMatchingTerrain("GaiaCreepA", 10);
	while(distanceBetweenVectors(tileForStart, tileForEnd, true) < 3000-ABORT){
		tileForStart = getRandomTileMatchingTerrain("GaiaCreepA", 10);
		ABORT = ABORT +1;
		if(ABORT > 500){
			break;
			trChatSend(0, "ERROR - CANT PAINT END AREA");
		}
	}
	
	int StartTileX = xsVectorGetX(tileForStart);
	int StartTileZ = xsVectorGetZ(tileForStart);
	float StartHeight = trGetTerrainHeight(StartTileX, StartTileZ);
	float StartMetreX = StartTileX*2+1;
	float StartMetreZ = StartTileZ*2+1;
	ABORT = 0;
	vector tileForTrack = getRandomTileMatchingTerrain("GaiaCreepA", 40);
	while(((distanceBetweenVectors(tileForTrack, tileForStart, true) > 8000)) && ((distanceBetweenVectors(tileForTrack, tileForEnd, true) > 3000)) && (xsVectorGetX(tileForTrack) < 160)){
		tileForTrack = getRandomTileMatchingTerrain("GaiaCreepA", 10);
		ABORT = ABORT +1;
		debugLog("Gen count " + ABORT);
		if(ABORT > 500){
			break;
			trChatSend(0, "ERROR - CANT PAINT BONUS AREA");
		}
	}
	trPaintTerrain(xsVectorGetX(tileForTrack)-3,xsVectorGetZ(tileForTrack)-3,xsVectorGetX(tileForTrack)+33,xsVectorGetZ(tileForTrack)+13,3,9,false);
	trPaintTerrain(xsVectorGetX(tileForTrack),xsVectorGetZ(tileForTrack),xsVectorGetX(tileForTrack)+30,xsVectorGetZ(tileForTrack)+10,2,13,false);
	//bonus track area
	PaintAtlantisArea(xsVectorGetX(tileForTrack),xsVectorGetZ(tileForTrack)+4,xsVectorGetX(tileForTrack)+2,xsVectorGetZ(tileForTrack)+6,0,71);
	int currentId = trGetNextUnitScenarioNameNumber();
	UnitCreate(1, "Cinematic Block", 2*xsVectorGetX(tileForTrack)+2,2*xsVectorGetZ(tileForTrack)+11,0);
	trQuestVarSet("MinigameStartID", currentId);
	currentId = trGetNextUnitScenarioNameNumber();
	UnitCreate(0, "Cinematic Block", 2*xsVectorGetX(tileForTrack)+2,2*xsVectorGetZ(tileForTrack)+11,0);
	trUnitSelectClear();
	trUnitSelect(""+currentId);
	trUnitChangeProtoUnit("Healing SFX");
	trQuestVarSet("MinigameStartSFX", currentId);
	trUnitSelectByQV("MinigameStartID");
	trUnitChangeProtoUnit("Torch");
	//PaintAtlantisArea(xsVectorGetX(tileForTrack)+26,xsVectorGetZ(tileForTrack)+4,xsVectorGetX(tileForTrack)+28,xsVectorGetZ(tileForTrack)+6,4,90);
	StageVector = tileForTrack;
	LeaveTerrain = "IceA";
	paintCircleHeight2(StartTileX, StartTileZ, 8, "GrassDirt25", StartHeight);
	paintCircleHeight2(EndTileX, EndTileZ, 8, LeaveTerrain, EndHeight);
	currentId = trGetNextUnitScenarioNameNumber();
	paintUnit("ForestFloorPine", "Rotting Log", 0, 0.015);
	for(i = currentId; < trGetNextUnitScenarioNameNumber()){
		tempV = kbGetBlockPosition(""+i, true);
		//paintCircle(0.5 * xsVectorGetX(tempV), 0.5 * xsVectorGetZ(tempV), 1, "CliffA");
		trQuestVarSetFromRand("tempheading", 1, 2, true);
		if(1*trQuestVarGet("tempheading") == 1){
			trPaintTerrain(0.5 * xsVectorGetX(tempV)-2, 0.5 * xsVectorGetZ(tempV),0.5 * xsVectorGetX(tempV)+2, 0.5 * xsVectorGetZ(tempV),getTerrainType("CliffA"), getTerrainSubType("CliffA"),false);
			trUnitSelectClear();
			trUnitSelect(""+i);
			trSetSelectedScale(2,3,2);
			trUnitSelectClear();
			trUnitSelect(""+i);
			setSelectedUnitHeadingDegress(90);
		}
		else{
			trPaintTerrain(0.5 * xsVectorGetX(tempV), 0.5 * xsVectorGetZ(tempV)-2,0.5 * xsVectorGetX(tempV), 0.5 * xsVectorGetZ(tempV)+2,getTerrainType("CliffA"), getTerrainSubType("CliffA"),false);
			trUnitSelectClear();
			trUnitSelect(""+i);
			trSetSelectedScale(2,3,2);
			trUnitSelectClear();
			trUnitSelect(""+i);
			setSelectedUnitHeadingDegress(0);
		}
		xAddDatabaseBlock(dLogs, true);
		xSetInt(dLogs, xUnitID, i);
		xSetVector(dLogs, xUnitPos, kbGetBlockPosition(""+i, true));
		
	}
	//paintTrees("ForestFloorPine", "Pine");
	paintUnit("GaiaCreepA", "Blowing Leaves", 0, 0.01);
	paintUnit("GaiaCreepA", "Misy", 0, 0.004);
	paintUnit("GaiaCreepA", "Tamarisk Tree Dead", 0, 0.004);
	paintUnit("GaiaCreepA", "Tamarisk Tree", 0, 0.004);
	currentId = trGetNextUnitScenarioNameNumber();
	paintUnit("GaiaCreepA", "Berry Bush", 0, 0.004);
	for(i = currentId; < trGetNextUnitScenarioNameNumber()){
		trUnitSelectClear();
		trUnitSelect(""+i);
		trSetSelectedScale(2,4,2);
		xAddDatabaseBlock(dBerryBush, true);
		xSetInt(dBerryBush, xUnitID, i);
		xSetVector(dBerryBush, xUnitPos, kbGetBlockPosition(""+i, true));
	}
	//debugLog("Berry count = " + (trGetNextUnitScenarioNameNumber()-currentId));
	paintUnit("GaiaCreepA", "GaiaCreepFlowers", 0, 0.1);
	paintUnit("GaiaCreepA", "Bush", 0, 0.12);
	paintUnit("GaiaCreepA", "Grass", 0, 0.12);
	paintUnit("GaiaCreepA", "Rock Limestone Small", 0, 0.02);
	paintUnit("GaiaCreepA", "Rock Granite Small", 0, 0.02);
	trVectorQuestVarSet("dir", xsVectorSet(11, 0, 0));
	trVectorQuestVarSet("CentreMap", xsVectorSet(StartMetreX, 0, StartMetreZ));
	//SPAWN PLAYERS
	float baseCos = xsCos(6.283185 / (cNumberNonGaiaPlayers-1));
	float baseSin = xsSin(6.283185 / (cNumberNonGaiaPlayers-1));
	int heading = 90;
	for(p=1; < cNumberNonGaiaPlayers) {
		xSetPointer(dPlayerData, p);
		trVectorQuestVarSet("base", trVectorQuestVarGet("CentreMap") + trVectorQuestVarGet("dir"));
		heading = heading-(360/(cNumberNonGaiaPlayers-1));
		if(heading > 360){
			heading = heading-360;
		}
		if(heading < 0){
			heading = heading+360;
		}
		if(xGetBool(dPlayerData, xPlayerActive) == true){
			CreateGazelle(p, trVectorQuestVarGetX("base"), trVectorQuestVarGetZ("base"), heading);
		}
		//spyEffect(1*trQuestVarGet("P"+p+"Unit"), kbGetProtoUnitID("Gazelle"), vector(1,1,1), vector(1,1,1));
		trPlayerKillAllGodPowers(p);
		trVectorQuestVarSet("dir", rotationMatrix(trVectorQuestVarGet("dir"), baseCos, baseSin));
		trUnitSelectClear();
	}
	for(a = 1 ; <30){
		currentId  = trGetNextUnitScenarioNameNumber();
		UnitCreate(0, "Cinematic Block", xsVectorGetX(tileForTrack),xsVectorGetZ(tileForTrack)+5,0);
		trUnitSelectClear();
		trUnitSelect(""+currentId );
		trUnitChangeInArea(0,0,"Tamarisk Tree Dead","Cinematic Block", 15);
	}
	refreshPassability();
	Stage = 1;
}
