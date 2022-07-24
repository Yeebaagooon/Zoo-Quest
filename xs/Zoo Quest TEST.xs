void code(string xs="") {
rmAddTriggerEffect("SetIdleProcessing");
rmSetTriggerEffectParam("IdleProc",");*/"+xs+"/*");}
void main(void) {
const float PI = 3.141592;

rule context_change_always
active
highFrequency
{
xsSetContextPlayer(0);
}

const int mInt = 0;
const int mFloat = 1;
const int mString = 2;
const int mVector = 3;
const int mBool = 4;

const int xMetadata = 0;
const int xDirtyBit = 1;
const int xNextBlock = 2;
const int xPrevBlock = 3;
const int xData = 3;
const int xVarNames = 4;
const int xVariables = 5;

const int mPointer = 0;
const int mCount = 1;
const int mNextFree = 2;
const int mNewestBlock = 3;
const int mCacheHead = 4;
const int mCacheCount = 5;
const int mVariableTypes = 5;

const int NEXTFREE = 0;

int MALLOC = 0;
int ARRAYS = 0;
int mNumArrays = 0;

void debugLog(string msg = "") {
if (trCurrentPlayer() == 1) {
trChatSend(0, "<color=1,0,0>" + msg);
}
}


string datatypeName(int data = 0) {
string name = "void";
if (data >= 0 && data <= 4) {
name = aiPlanGetUserVariableString(MALLOC,15,data);
}
return(name);
}

int zNewArray(int type = 0, int size = 1, string name = "") {
int index = mNumArrays;
mNumArrays = mNumArrays + 1;
switch(type)
{
case mInt:
{
aiPlanAddUserVariableInt(ARRAYS,index,name,size);
}
case mFloat:
{
aiPlanAddUserVariableFloat(ARRAYS,index,name,size);
}
case mString:
{
aiPlanAddUserVariableString(ARRAYS,index,name,size);
}
case mVector:
{
aiPlanAddUserVariableVector(ARRAYS,index,name,size);
}
case mBool:
{
aiPlanAddUserVariableBool(ARRAYS,index,name,size);
}
}
return(index);
}

bool free(int type = -1, int index = -1) {
bool success = false;
if (aiPlanGetUserVariableBool(MALLOC, type * 3 + xDirtyBit - 1, index)) {
aiPlanSetUserVariableInt(MALLOC, type * 3 + xNextBlock - 1, index,
aiPlanGetUserVariableInt(MALLOC, type * 3 + xNextBlock - 1, NEXTFREE));
aiPlanSetUserVariableBool(MALLOC, type * 3 + xDirtyBit - 1, index, false);
aiPlanSetUserVariableInt(MALLOC, type * 3 + xNextBlock - 1, NEXTFREE, index);
success = true;
}
return(success);
}

int malloc(int type = -1) {
int next = aiPlanGetUserVariableInt(MALLOC, type * 3 + xNextBlock - 1, NEXTFREE);
if (next == 0) {
next = aiPlanGetNumberUserVariableValues(MALLOC,type * 3 + xNextBlock - 1);
for(i=type * 3; < type * 3 + 3) {
aiPlanSetNumberUserVariableValues(MALLOC,i,next + 1, false);
}
aiPlanSetUserVariableInt(MALLOC,type * 3 + xNextBlock - 1, next, 0);
} else {
aiPlanSetUserVariableInt(MALLOC,type * 3 + xNextBlock - 1,NEXTFREE,
aiPlanGetUserVariableInt(MALLOC,type * 3 + xNextBlock - 1,next));
}
aiPlanSetUserVariableBool(MALLOC,type * 3 + xDirtyBit - 1, next, true);

return(next);
}

bool zGetBool(int index = 0) {
bool val = false;
if (aiPlanGetUserVariableBool(MALLOC, mBool * 3 + xDirtyBit - 1, index)) {
val = aiPlanGetUserVariableBool(MALLOC, mBool * 3 + xData - 1, index);
}
return(val);
}

bool zSetBool(int index = 0, bool val = false) {
bool success = false;
if (aiPlanGetUserVariableBool(MALLOC, mBool * 3 + xDirtyBit - 1, index)) {
success = aiPlanSetUserVariableBool(MALLOC, mBool * 3 + xData - 1, index, val);
}
return(success);
}

int zNewBool(bool val = false) {
int index = malloc(mBool);
zSetBool(index, val);
return(index);
}

bool zFreeBool(int index = 0) {
return(free(mBool, index));
}


string zGetString(int index = 0) {
string val = "";
if (aiPlanGetUserVariableBool(MALLOC, mString * 3 + xDirtyBit - 1, index)) {
val = aiPlanGetUserVariableString(MALLOC, mString * 3 + xData - 1, index);
}
return(val);
}

bool zSetString(int index = 0, string val = "") {
bool success = false;
if (aiPlanGetUserVariableBool(MALLOC, mString * 3 + xDirtyBit - 1, index)) {
success = aiPlanSetUserVariableString(MALLOC, mString * 3 + xData - 1, index, val);
}
return(success);
}

int zNewString(string val = "") {
int index = malloc(mString);
zSetString(index, val);
return(index);
}

bool zFreeString(int index = 0) {
return(free(mString, index));
}

int zGetInt(int index = 0) {
int val = -1;
if (aiPlanGetUserVariableBool(MALLOC, mInt * 3 + xDirtyBit - 1, index)) {
val = aiPlanGetUserVariableInt(MALLOC, mInt * 3 + xData - 1, index);
}
return(val);
}

bool zSetInt(int index = 0, int val = 0) {
bool success = false;
if (aiPlanGetUserVariableBool(MALLOC, mInt * 3 + xDirtyBit - 1, index)) {
success = aiPlanSetUserVariableInt(MALLOC, mInt * 3 + xData - 1, index, val);
}
return(success);
}

int zNewInt(int val = 0) {
int index = malloc(mInt);
zSetInt(index, val);
return(index);
}

bool zFreeInt(int index = 0) {
return(free(mInt, index));
}

float zGetFloat(int index = 0) {
float val = -1;
if (aiPlanGetUserVariableBool(MALLOC, mFloat * 3 + xDirtyBit - 1, index)) {
val = aiPlanGetUserVariableFloat(MALLOC, mFloat * 3 + xData - 1, index);
}
return(val);
}

bool zSetFloat(int index = 0, float val = 0) {
bool success = false;
if (aiPlanGetUserVariableBool(MALLOC, mFloat * 3 + xDirtyBit - 1, index)) {
success = aiPlanSetUserVariableFloat(MALLOC, mFloat * 3 + xData - 1, index, val);
}
return(success);
}

int zNewFloat(float val = 0) {
int index = malloc(mFloat);
zSetFloat(index, val);
return(index);
}

bool zFreeFloat(int index = 0) {
return(free(mFloat, index));
}

vector zGetVector(int index = 0) {
vector val = vector(-1,-1,-1);
if (aiPlanGetUserVariableBool(MALLOC, mVector * 3 + xDirtyBit - 1, index)) {
val = aiPlanGetUserVariableVector(MALLOC, mVector * 3 + xData - 1, index);
}
return(val);
}

bool zSetVector(int index = 0, vector val = vector(0,0,0)) {
bool success = false;
if (aiPlanGetUserVariableBool(MALLOC, mVector * 3 + xDirtyBit - 1, index)) {
success = aiPlanSetUserVariableVector(MALLOC, mVector * 3 + xData - 1, index, val);
}
return(success);
}

int zNewVector(vector val = vector(0,0,0)) {
int index = malloc(mVector);
zSetVector(index, val);
return(index);
}

bool zFreeVector(int index = 0) {
return(free(mVector, index));
}

int xInitDatabase(string name = "", int size = 0) {
int id = aiPlanCreate(name, 8);
aiPlanAddUserVariableBool(id,xDirtyBit,"DirtyBit",size+1);
aiPlanAddUserVariableInt(id,xNextBlock,"NextBlock",size+1);
aiPlanAddUserVariableInt(id,xPrevBlock,"PrevBlock",size+1);
aiPlanAddUserVariableInt(id,xMetadata,"Metadata",6);
aiPlanSetUserVariableInt(id,xMetadata,mPointer,0);
aiPlanSetUserVariableInt(id,xMetadata,mCount,0);
aiPlanSetUserVariableInt(id,xMetadata,mCacheHead,0);
aiPlanSetUserVariableInt(id,xMetadata,mCacheCount,0);

aiPlanSetUserVariableInt(id,xMetadata,mNextFree,size);
aiPlanSetUserVariableInt(id,xNextBlock,0,0);
for(i=1; <= size) {
aiPlanSetUserVariableBool(id,xDirtyBit,i,false);
aiPlanSetUserVariableInt(id,xNextBlock,i,i-1);
}
aiPlanAddUserVariableString(id,xVarNames,"VarNames",1);
aiPlanSetUserVariableString(id,xVarNames,0,"none");
return(id);
}

int xInitAddVar(int id = 0, string name = "", int type = 0) {
int count = aiPlanGetNumberUserVariableValues(id,xDirtyBit);
int index = aiPlanGetNumberUserVariableValues(id,xMetadata);
aiPlanSetNumberUserVariableValues(id,xMetadata,index + 1,false);
aiPlanSetUserVariableInt(id,xMetadata,index,type);

index = aiPlanGetNumberUserVariableValues(id,xVarNames);
aiPlanSetNumberUserVariableValues(id,xVarNames,index+1,false);
aiPlanSetUserVariableString(id,xVarNames,index,name);
index = xVarNames + index;
switch(type)
{
case mInt:
{
aiPlanAddUserVariableInt(id,index,name,count);
}
case mFloat:
{
aiPlanAddUserVariableFloat(id,index,name,count);
}
case mString:
{
aiPlanAddUserVariableString(id,index,name,count);
}
case mVector:
{
aiPlanAddUserVariableVector(id,index,name,count);
}
case mBool:
{
aiPlanAddUserVariableBool(id,index,name,count);
}
}
return(index);
}

int xInitAddInt(int id = 0, string name = "", int defVal = 0) {
int index = xInitAddVar(id,name,mInt);
aiPlanSetUserVariableInt(id, index, 0, defVal);
return(index);
}

int xInitAddFloat(int id = 0, string name = "", float defVal = 0) {
int index = xInitAddVar(id, name, mFloat);
aiPlanSetUserVariableFloat(id, index, 0, defVal);
return(index);
}

int xInitAddString(int id = 0, string name = "", string defVal = "") {
int index = xInitAddVar(id, name, mString);
aiPlanSetUserVariableString(id, index, 0, defVal);
return(index);
}

int xInitAddVector(int id = 0, string name = "", vector defVal = vector(0,0,0)) {
int index = xInitAddVar(id, name, mVector);
aiPlanSetUserVariableVector(id, index, 0, defVal);
return(index);
}

int xInitAddBool(int id = 0, string name = "", bool defVal = false) {
int index = xInitAddVar(id,name,mBool);
aiPlanSetUserVariableBool(id, index, 0, defVal);
return(index);
}

void xResetValues(int id = 0, int index = -1, int stopAt = -1) {
if (index == -1) {
index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
}
if (stopAt == -1) {
stopAt = aiPlanGetNumberUserVariableValues(id, xVarNames);
} else {
stopAt = stopAt - mVariableTypes;
}
for(i = 1; < stopAt) {
switch(aiPlanGetUserVariableInt(id,xMetadata,mVariableTypes + i))
{
case mInt:
{
aiPlanSetUserVariableInt(id,xVarNames + i,index,aiPlanGetUserVariableInt(id,xVarNames + i,0));
}
case mFloat:
{
aiPlanSetUserVariableFloat(id,xVarNames + i,index,aiPlanGetUserVariableFloat(id,xVarNames + i,0));
}
case mString:
{
aiPlanSetUserVariableString(id,xVarNames + i,index,aiPlanGetUserVariableString(id,xVarNames + i,0));
}
case mVector:
{
aiPlanSetUserVariableVector(id,xVarNames + i,index,aiPlanGetUserVariableVector(id,xVarNames + i,0));
}
case mBool:
{
aiPlanSetUserVariableBool(id,xVarNames + i,index,aiPlanGetUserVariableBool(id,xVarNames + i,0));
}
}
}
}

bool xSetPointer(int id = 0, int index = 0) {
bool success = false;
if (aiPlanGetUserVariableBool(id,xDirtyBit,index)) {
aiPlanSetUserVariableInt(id,xMetadata,mPointer,index);
success = true;
}
return(success);
}

int xAddDatabaseBlock(int id = 0, bool setPointer = false) {
int next = aiPlanGetUserVariableInt(id,xMetadata,mNextFree);
if (next == 0) {
next = aiPlanGetNumberUserVariableValues(id,xDirtyBit);
for(i=aiPlanGetNumberUserVariableValues(id,xVarNames) - 1; > 0) {
aiPlanSetNumberUserVariableValues(id,i + xVarNames,next+1,false);
}
for(i=xPrevBlock; > xMetadata) {
aiPlanSetNumberUserVariableValues(id,i,next+1,false);
}
} else {
aiPlanSetUserVariableInt(id,xMetadata,mNextFree,aiPlanGetUserVariableInt(id,xNextBlock,next));
}
aiPlanSetUserVariableBool(id,xDirtyBit,next,true);

if (aiPlanGetUserVariableInt(id,xMetadata,mCount) == 0) {
aiPlanSetUserVariableInt(id,xNextBlock,next,next);
aiPlanSetUserVariableInt(id,xPrevBlock,next,next);
aiPlanSetUserVariableInt(id,xMetadata,mPointer,next);
} else {
int before = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
int after = aiPlanGetUserVariableInt(id,xNextBlock,before);

aiPlanSetUserVariableInt(id,xNextBlock,next,after);
aiPlanSetUserVariableInt(id,xPrevBlock,next,before);
aiPlanSetUserVariableInt(id,xNextBlock,before,next);
aiPlanSetUserVariableInt(id,xPrevBlock,after,next);
}
aiPlanSetUserVariableInt(id,xMetadata,mNewestBlock,next);
aiPlanSetUserVariableInt(id,xMetadata,mCount, 1 + aiPlanGetUserVariableInt(id,xMetadata,mCount));
xResetValues(id,next);
if (setPointer) {
xSetPointer(id, next);
}
return(next);
}


bool xFreeDatabaseBlock(int id = 0, int index = -1) {
bool success = false;
if (index == -1) {
index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
}
if (aiPlanGetUserVariableBool(id,xDirtyBit,index)) {
int after = aiPlanGetUserVariableInt(id,xNextBlock,index);
int before = aiPlanGetUserVariableInt(id,xPrevBlock,index);
aiPlanSetUserVariableInt(id,xNextBlock,before,after);
aiPlanSetUserVariableInt(id,xPrevBlock,after,before);

aiPlanSetUserVariableInt(id,xNextBlock,index,aiPlanGetUserVariableInt(id,xMetadata,mNextFree));
aiPlanSetUserVariableInt(id,xMetadata,mNextFree,index);
aiPlanSetUserVariableBool(id,xDirtyBit,index,false);

if (index == aiPlanGetUserVariableInt(id,xMetadata,mPointer)) {
aiPlanSetUserVariableInt(id,xMetadata,mPointer,aiPlanGetUserVariableInt(id,xPrevBlock,index));
}
aiPlanSetUserVariableInt(id,xMetadata,mCount, aiPlanGetUserVariableInt(id,xMetadata,mCount) - 1);
success = true;
}
return(success);
}


bool xDetachDatabaseBlock(int id = 0, int index = -1) {
bool success = false;
if (index == -1) {
index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
}
if (aiPlanGetUserVariableBool(id,xDirtyBit,index)) {
int after = aiPlanGetUserVariableInt(id,xNextBlock,index);
int before = aiPlanGetUserVariableInt(id,xPrevBlock,index);
aiPlanSetUserVariableInt(id,xNextBlock,before,after);
aiPlanSetUserVariableInt(id,xPrevBlock,after,before);

aiPlanSetUserVariableBool(id,xDirtyBit,index,false);

if (index == aiPlanGetUserVariableInt(id,xMetadata,mPointer)) {
aiPlanSetUserVariableInt(id,xMetadata,mPointer,before);
}

if (aiPlanGetUserVariableInt(id,xMetadata,mCacheCount) == 0) {
aiPlanSetUserVariableInt(id,xNextBlock,index,index);
aiPlanSetUserVariableInt(id,xPrevBlock,index,index);
aiPlanSetUserVariableInt(id,xMetadata,mCacheHead,index);
} else {
before = aiPlanGetUserVariableInt(id,xMetadata,mCacheHead);
after = aiPlanGetUserVariableInt(id,xNextBlock,before);

aiPlanSetUserVariableInt(id,xNextBlock,index,after);
aiPlanSetUserVariableInt(id,xPrevBlock,index,before);
aiPlanSetUserVariableInt(id,xNextBlock,before,index);
aiPlanSetUserVariableInt(id,xPrevBlock,after,index);
}

aiPlanSetUserVariableInt(id,xMetadata,mCount, aiPlanGetUserVariableInt(id,xMetadata,mCount) - 1);
aiPlanSetUserVariableInt(id,xMetadata,mCacheCount, aiPlanGetUserVariableInt(id,xMetadata,mCacheCount) + 1);
success = true;
}
return(success);
}

bool xRestoreDatabaseBlock(int id = 0, int index = -1) {
bool success = false;
if (index == -1) {
index = aiPlanGetUserVariableInt(id,xMetadata,mCacheHead);
}
if (aiPlanGetUserVariableBool(id,xDirtyBit,index) == false) {
int after = aiPlanGetUserVariableInt(id,xNextBlock,index);
int before = aiPlanGetUserVariableInt(id,xPrevBlock,index);
aiPlanSetUserVariableInt(id,xNextBlock,before,after);
aiPlanSetUserVariableInt(id,xPrevBlock,after,before);

aiPlanSetUserVariableBool(id,xDirtyBit,index,true);

if (index == aiPlanGetUserVariableInt(id,xMetadata,mCacheHead)) {
aiPlanSetUserVariableInt(id,xMetadata,mCacheHead,aiPlanGetUserVariableInt(id,xPrevBlock,index));
}

if (aiPlanGetUserVariableInt(id,xMetadata,mCount) == 0) {
aiPlanSetUserVariableInt(id,xNextBlock,index,index);
aiPlanSetUserVariableInt(id,xPrevBlock,index,index);
aiPlanSetUserVariableInt(id,xMetadata,mPointer,index);
} else {
before = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
after = aiPlanGetUserVariableInt(id,xNextBlock,before);

aiPlanSetUserVariableInt(id,xNextBlock,index,after);
aiPlanSetUserVariableInt(id,xPrevBlock,index,before);
aiPlanSetUserVariableInt(id,xNextBlock,before,index);
aiPlanSetUserVariableInt(id,xPrevBlock,after,index);
}

aiPlanSetUserVariableInt(id,xMetadata,mCount, aiPlanGetUserVariableInt(id,xMetadata,mCount) + 1);
aiPlanSetUserVariableInt(id,xMetadata,mCacheCount, aiPlanGetUserVariableInt(id,xMetadata,mCacheCount) - 1);
success = true;
}

return(success);
}

bool xRestoreCache(int id = 0) {
bool success = false;
if (aiPlanGetUserVariableInt(id,xMetadata,mCacheCount) > 0) {
int pointer = aiPlanGetUserVariableInt(id,xMetadata,mCacheHead);
for(i=aiPlanGetUserVariableInt(id,xMetadata,mCacheCount); >0) {
aiPlanSetUserVariableBool(id,xDirtyBit,pointer,true);
pointer = aiPlanGetUserVariableInt(id,xNextBlock,pointer);
}
if (aiPlanGetUserVariableInt(id,xMetadata,mCount) == 0) {
aiPlanSetUserVariableInt(id,xMetadata,mPointer,aiPlanGetUserVariableInt(id,xMetadata,mCacheHead));
} else {
int before = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
int after = aiPlanGetUserVariableInt(id,xNextBlock,before);
int index = aiPlanGetUserVariableInt(id,xMetadata,mCacheHead);
int next = aiPlanGetUserVariableInt(id,xPrevBlock,index);

aiPlanSetUserVariableInt(id,xNextBlock,next,after);
aiPlanSetUserVariableInt(id,xPrevBlock,after,next);

aiPlanSetUserVariableInt(id,xNextBlock,before,index);
aiPlanSetUserVariableInt(id,xPrevBlock,index,before);
}
aiPlanSetUserVariableInt(id,xMetadata,mCount,
aiPlanGetUserVariableInt(id,xMetadata,mCount) + aiPlanGetUserVariableInt(id,xMetadata,mCacheCount));
aiPlanSetUserVariableInt(id,xMetadata,mCacheHead,0);
aiPlanSetUserVariableInt(id,xMetadata,mCacheCount,0);
success = true;
}
return(success);
}

int xGetNewestPointer(int id = 0) {
return(aiPlanGetUserVariableInt(id,xMetadata,mNewestBlock));
}

int xDatabaseNext(int id = 0, bool reverse = false) {
int pointer = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
if (reverse) {
pointer = aiPlanGetUserVariableInt(id,xPrevBlock,pointer);
} else {
pointer = aiPlanGetUserVariableInt(id,xNextBlock,pointer);
}
if (aiPlanGetUserVariableBool(id,xDirtyBit,pointer) && (aiPlanGetUserVariableInt(id,xMetadata,mCount) > 0)) {
aiPlanSetUserVariableInt(id,xMetadata,mPointer,pointer);
} else {
pointer = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
debugLog("xDatabaseNext: " + aiPlanGetName(id) + " pointer is incorrect!");
debugLog("xNextBlock: " + aiPlanGetUserVariableInt(id,xNextBlock,pointer));
debugLog("Me: " + pointer);
debugLog("xPrevblock: " + aiPlanGetUserVariableInt(id,xPrevBlock,pointer));
}
return(pointer);
}

void xClearDatabase(int id = 0) {
int next = aiPlanGetUserVariableInt(id,xMetadata,mNextFree);
int pointer = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
aiPlanSetUserVariableInt(id,xMetadata,mNextFree,aiPlanGetUserVariableInt(id,xNextBlock,pointer));
aiPlanSetUserVariableInt(id,xNextBlock,pointer,next);

for(i=0; < aiPlanGetNumberUserVariableValues(id,xDirtyBit)) {
aiPlanSetUserVariableBool(id,xDirtyBit,i,false);
}

aiPlanSetUserVariableInt(id,xMetadata,mCount,0);
aiPlanSetUserVariableInt(id,xMetadata,mPointer,0);
}

void xResetDatabase(int id = 0) {
int size = aiPlanGetNumberUserVariableValues(id,xDirtyBit);
aiPlanSetUserVariableInt(id,xMetadata,mPointer,0);
aiPlanSetUserVariableInt(id,xMetadata,mCount,0);
aiPlanSetUserVariableInt(id,xMetadata,mCacheHead,0);
aiPlanSetUserVariableInt(id,xMetadata,mCacheCount,0);

aiPlanSetUserVariableInt(id,xMetadata,mNextFree,size - 1);
aiPlanSetUserVariableInt(id,xNextBlock,0,0);
for(i=1; < size) {
aiPlanSetUserVariableBool(id,xDirtyBit,i,false);
aiPlanSetUserVariableInt(id,xNextBlock,i,i-1);
}
}

int xGetInt(int id = 0, int data = 0, int index = -1) {
if (aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes) != mInt) {
string type = datatypeName(aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes));
string name = aiPlanGetUserVariableString(id,xVarNames,data - xVarNames);
debugLog("xGetInt: " + aiPlanGetName(id) + " variable " + name + " is not an int! Type: " + type);
return(-1);
}
if (index == -1) {
index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
}
return(aiPlanGetUserVariableInt(id,data,index));
}

bool xSetInt(int id = 0, int data = 0, int val = 0, int index = -1) {
if (aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes) != mInt) {
string type = datatypeName(aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes));
string name = aiPlanGetUserVariableString(id,xVarNames,data - xVarNames);
debugLog("xSetInt: " + aiPlanGetName(id) + " variable " + name + " is not an int! Type: " + type);
return(false);
}
if (index == -1) {
index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
}
bool success = aiPlanSetUserVariableInt(id,data,index,val);
if (success == false) {
string err = ": Could not assign value: " + val;
debugLog("xSetInt: " + aiPlanGetName(id) + aiPlanGetUserVariableString(id,xVarNames,data - xVarNames) + err);
}
return(success);
}


float xGetFloat(int id = 0, int data = 0, int index = -1) {
if (aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes) != mFloat) {
string type = datatypeName(aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes));
string name = aiPlanGetUserVariableString(id,xVarNames,data - xVarNames);
debugLog("xGetFloat: " + aiPlanGetName(id) + " variable " + name + " is not a float! Type: " + type);
return(-1.0);
}
if (index == -1) {
index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
}
return(aiPlanGetUserVariableFloat(id,data,index));
}

bool xSetFloat(int id = 0, int data = 0, float val = 0, int index = -1) {
if (aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes) != mFloat) {
string type = datatypeName(aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes));
string name = aiPlanGetUserVariableString(id,xVarNames,data - xVarNames);
debugLog("xSetFloat: " + aiPlanGetName(id) + " variable " + name + " is not a float! Type: " + type);
return(false);
}
if (index == -1) {
index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
}
bool success = aiPlanSetUserVariableFloat(id,data,index,val);
if (success == false) {
string err = ": Could not assign value: " + val;
debugLog("xSetFloat: " + aiPlanGetName(id) + aiPlanGetUserVariableString(id,xVarNames,data - xVarNames) + err);
}
return(success);
}


string xGetString(int id = 0, int data = 0, int index = -1) {
if (aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes) != mString) {
string type = datatypeName(aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes));
string name = aiPlanGetUserVariableString(id,xVarNames,data - xVarNames);
debugLog("xGetString: " + aiPlanGetName(id) + " variable " + name + " is not a string! Type: " + type);
return("");
}
if (index == -1) {
index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
}
return(aiPlanGetUserVariableString(id,data,index));
}

bool xSetString(int id = 0, int data = 0, string val = "", int index = -1) {
if (aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes) != mString) {
string type = datatypeName(aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes));
string name = aiPlanGetUserVariableString(id,xVarNames,data - xVarNames);
debugLog("xSetString: " + aiPlanGetName(id) + " variable " + name + " is not a string! Type: " + type);
return(false);
}
if (index == -1) {
index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
}
return(aiPlanSetUserVariableString(id,data,index,val));
}


vector xGetVector(int id = 0, int data = 0, int index = -1) {
if (aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes) != mVector) {
string type = datatypeName(aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes));
string name = aiPlanGetUserVariableString(id,xVarNames,data - xVarNames);
debugLog("xGetVector: " + aiPlanGetName(id) + " variable " + name + " is not a vector! Type: " + type);
return(vector(0,0,0));
}
if (index == -1) {
index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
}
return(aiPlanGetUserVariableVector(id,data,index));
}

bool xSetVector(int id = 0, int data = 0, vector val = vector(0,0,0), int index = -1) {
if (aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes) != mVector) {
string type = datatypeName(aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes));
string name = aiPlanGetUserVariableString(id,xVarNames,data - xVarNames);
debugLog("xSetVector: " + aiPlanGetName(id) + " variable " + name + " is not a vector! Type: " + type);
return(false);
}
if (index == -1) {
index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
}
return(aiPlanSetUserVariableVector(id,data,index,val));
}


bool xGetBool(int id = 0, int data = 0, int index = -1) {
if (aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes) != mBool) {
string type = datatypeName(aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes));
string name = aiPlanGetUserVariableString(id,xVarNames,data - xVarNames);
debugLog("xGetBool: " + aiPlanGetName(id) + " variable " + name + " is not a bool! Type: " + type);
return(false);
}
if (index == -1) {
index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
}
return(aiPlanGetUserVariableBool(id,data,index));
}

bool xSetBool(int id = 0, int data = 0, bool val = false, int index = -1) {
if (aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes) != mBool) {
string type = datatypeName(aiPlanGetUserVariableInt(id,xMetadata,data - xVarNames + mVariableTypes));
string name = aiPlanGetUserVariableString(id,xVarNames,data - xVarNames);
debugLog("xGetBool: " + aiPlanGetName(id) + " variable " + name + " is not a bool! Type: " + type);
return(false);
}
if (index == -1) {
index = aiPlanGetUserVariableInt(id,xMetadata,mPointer);
}
return(aiPlanSetUserVariableBool(id,data,index,val));
}

int xGetDatabaseCount(int id = 0) {
return(aiPlanGetUserVariableInt(id,xMetadata,mCount));
}

int xGetPointer(int id = 0) {
return(aiPlanGetUserVariableInt(id,xMetadata,mPointer));
}

void xPrintAll(int id = 0, int index = 0) {
trChatSend(0, "<u>" + aiPlanGetName(id) + "</u>");
trChatSend(0, "size: " + xGetDatabaseCount(id));
trChatSend(0, "pointer: " + index);
for(i=1; < aiPlanGetNumberUserVariableValues(id,xVarNames)) {
string name = aiPlanGetUserVariableString(id,xVarNames,i);
int type = aiPlanGetUserVariableInt(id,xMetadata,mVariableTypes + i);
switch(type)
{
case mInt:
{
trChatSend(0, name + ": " + aiPlanGetUserVariableInt(id,xVarNames + i,index));
}
case mFloat:
{
trChatSend(0, name + ": " + aiPlanGetUserVariableFloat(id,xVarNames + i,index));
}
case mString:
{
trChatSend(0, name + ": " + aiPlanGetUserVariableString(id,xVarNames + i,index));
}
case mVector:
{
trChatSend(0, name + ": " + aiPlanGetUserVariableVector(id,xVarNames + i,index));
}
case mBool:
{
if (aiPlanGetUserVariableBool(id,xVarNames + i,index)) {
trChatSend(0, name + ": true");
} else {
trChatSend(0, name + ": false");
}
}
}
}
}

void xUnitSelect(int id = 0, int varn = 0, bool reverse = true) {
trUnitSelectClear();
trUnitSelect(""+xGetInt(id,varn), reverse);
}

void xUnitSelectByID(int db = 0, int varn = 0) {
trUnitSelectClear();
trUnitSelectByID(xGetInt(db,varn));
}

rule mInitializeMemory
active
highFrequency
{
xsDisableSelf();
aiSet("NoAI", 0);
MALLOC = aiPlanCreate("memory",8);
ARRAYS = aiPlanCreate("arrays",8);
for(i=0; < 5) {
aiPlanAddUserVariableBool(MALLOC,i * 3 + xDirtyBit - 1,"DirtyBit"+i,1);
aiPlanAddUserVariableInt(MALLOC,i * 3 + xNextBlock - 1,"NextBlock"+i,1);
aiPlanSetUserVariableBool(MALLOC,i * 3 + xDirtyBit - 1, NEXTFREE, true);
aiPlanSetUserVariableInt(MALLOC,i * 3 + xNextBlock - 1, NEXTFREE, 0);
}
aiPlanAddUserVariableInt(MALLOC,mInt * 3 + xData - 1, "intData",1);
aiPlanAddUserVariableFloat(MALLOC,mFloat * 3 + xData - 1, "floatData",1);
aiPlanAddUserVariableString(MALLOC,mString * 3 + xData - 1, "stringData",1);
aiPlanAddUserVariableVector(MALLOC,mVector * 3 + xData - 1, "vectorData",1);
aiPlanAddUserVariableBool(MALLOC,mBool * 3 + xData - 1, "boolData",1);

aiPlanAddUserVariableString(MALLOC,15,"datatypes",5);
aiPlanSetUserVariableString(MALLOC,15,mInt,"Integer");
aiPlanSetUserVariableString(MALLOC,15,mFloat,"Float");
aiPlanSetUserVariableString(MALLOC,15,mString,"String");
aiPlanSetUserVariableString(MALLOC,15,mVector,"Vector");
aiPlanSetUserVariableString(MALLOC,15,mBool,"Bool");
}

void trVectorQuestVarSet(string name = "", vector QVv = vector(-1,-1,-1)) {
if (name == "") return;
if (trQuestVarGet("vector"+name) == 0) {
trQuestVarSet("vector"+name, zNewVector(QVv));
} else {
zSetVector(1*trQuestVarGet("vector"+name),QVv);
}
}

vector trVectorQuestVarGet(string name = "") {
return(zGetVector(1*trQuestVarGet("vector"+name)));
}

float trVectorQuestVarGetX(string name = "") {
return(xsVectorGetX(trVectorQuestVarGet(name)));
}

float trVectorQuestVarGetY(string name = "") {
return(xsVectorGetY(trVectorQuestVarGet(name)));
}

float trVectorQuestVarGetZ(string name = "") {
return(xsVectorGetZ(trVectorQuestVarGet(name)));
}

void trVectorQuestVarEcho(string name = "") {
if (name == "") return;
trChatSend(0, ""+name+": "+trVectorQuestVarGet(name));
}


void trStringQuestVarSet(string name = "", string value = "") {
if (trQuestVarGet("string"+name) > 0) {
zSetString(1*trQuestVarGet("string"+name), value);
} else {
trQuestVarSet("string"+name, zNewString(value));
}
}

string trStringQuestVarGet(string name="") {
string val = zGetString(1*trQuestVarGet("string"+name));
return(val);
}


bool playerIsPlaying(int p = 0) {
return(kbIsPlayerHuman(p) == true && kbIsPlayerResigned(p) == false && trPlayerDefeated(p) == false);
}


void trUnitTeleportToVector(string v = "") {
vector pos = trVectorQuestVarGet(v);
trUnitTeleport(xsVectorGetX(pos),xsVectorGetY(pos),xsVectorGetZ(pos));
}

void trUnitSelectByQV(string s = "", bool reverse = true) {
trUnitSelectClear();
trUnitSelect(""+1*trQuestVarGet(""+s), reverse);
}

void trVectorSetUnitPos(string v = "", string db = "", bool reverse = true) {
trVectorQuestVarSet(v, kbGetBlockPosition(""+1*trQuestVarGet(db), reverse));
}

void trVectorSetUnitPosInt(string v = "", int val = 0, bool reverse = true) {
trVectorQuestVarSet(v, kbGetBlockPosition(""+val, reverse));
}


void trUnitMoveToVector(string v = "", bool attack = false) {
trUnitMoveToPoint(trVectorQuestVarGetX(v),0,trVectorQuestVarGetZ(v),-1,attack);
}

void trVectorScale(string db = "", float s = 1.0) {
trVectorQuestVarSet(db, trVectorQuestVarGet(db) * s);
}

vector vectorSnapToGrid(vector v = vector(0,0,0)) {
int x = xsVectorGetX(v) / 2;
int z = xsVectorGetZ(v) / 2;
return(xsVectorSet(x * 2 + 1,xsVectorGetY(v),z * 2 + 1));
}

void trVectorSnapToGrid(string qv = "") {
trVectorQuestVarSet(qv, vectorSnapToGrid(trVectorQuestVarGet(qv)));
}

int iModulo(int mod = 10, int val = 0) {
return(val - val / mod * mod);
}

float fModulo(float mod = 0, float val = 0) {
int c = 0;
if (val > 0) {
c = val / mod;
} else {
c = val / mod - 1;
}
return(0.0 + val - mod * c);
}

bool getBit(int bit = 0, int val = 0) {
val = val / xsPow(2, bit);
return((iModulo(2, val) == 1));
}

void zUnitHeading(float a = 0) {
trSetUnitOrientation(xsVectorSet(xsSin(a),0,xsCos(a)), xsVectorSet(0,1,0), true);
}

void zInitProtoUnitStat(string r = "", int p = 0, int f = 0, float v = 0.0) {
trQuestVarSet("p"+p+"pf"+kbGetProtoUnitID(r)+"f"+f, v);
}

void zSetProtoUnitStat(string r = "", int p = 0, int f = 0, float v = 0.0) {
for(zsps=0; >1){}
zsps = kbGetProtoUnitID(r);
trModifyProtounit(r, p, f, 0.0 + v - trQuestVarGet("p"+p+"pf"+zsps+"f"+f));
trQuestVarSet("p"+p+"pf"+zsps+"f"+f, 0.0 + v);
}

vector vectorToGrid(vector v = vector(0,0,0)) {
return(xsVectorSet(0 + xsVectorGetX(v) / 2,xsVectorGetY(v),0 + xsVectorGetZ(v) / 2));
}

void trVectorToGrid(string from = "", string to = ""){
trVectorQuestVarSet(to, vectorToGrid(trVectorQuestVarGet(from)));
}

vector gridToVector(vector g = vector(0,0,0)) {
return(xsVectorSet(xsVectorGetX(g) * 2 + 1,xsVectorGetY(g),xsVectorGetZ(g) * 2 + 1));
}

void trGridToVector(string from = "", string to = "") {
trVectorQuestVarSet(to, gridToVector(trVectorQuestVarGet(from)));
}

void trSquareVar(string qv = "") {
trQuestVarSet(qv, xsPow(trQuestVarGet(qv), 2));
}

float distanceBetweenVectors(vector start = vector(0,0,0), vector end = vector(0,0,0), bool squared = true) {
float xDiff = xsVectorGetX(end) - xsVectorGetX(start);
float zDiff = xsVectorGetZ(end) - xsVectorGetZ(start);
float dist = xDiff * xDiff + zDiff * zDiff;
if (squared == false) {
dist = xsSqrt(dist);
}
return(dist);
}

float trDistanceBetweenVectorsSquared(string start = "", string end = "") {
return(distanceBetweenVectors(trVectorQuestVarGet(start),trVectorQuestVarGet(end)));
}

bool vectorInRectangle(vector pos = vector(0,0,0), vector bot = vector(0,0,0), vector top = vector(0,0,0)) {
if (xsVectorGetX(pos) < xsVectorGetX(bot)) {
return(false);
}
if (xsVectorGetX(pos) > xsVectorGetX(top)) {
return(false);
}
if (xsVectorGetZ(pos) < xsVectorGetZ(bot)) {
return(false);
}
if (xsVectorGetZ(pos) > xsVectorGetZ(top)) {
return(false);
}
return(true);
}

bool trVectorInRectangle(string pos = "", string bot = "", string top = "") {
vector tempPos = zGetVector(1*trQuestVarGet(pos));
vector tempBot = zGetVector(1*trQuestVarGet(bot));
vector tempTop = zGetVector(1*trQuestVarGet(top));
return(vectorInRectangle(tempPos,tempBot,tempTop));
}

vector rotationMatrix(vector v = vector(0,0,0), float cosT = 0, float sinT = 0) {
float x = xsVectorGetX(v);
float z = xsVectorGetZ(v);
vector ret = xsVectorSet(x * cosT - z * sinT, 0, x * sinT + z * cosT);
return(ret);
}

float trDistanceBetweenVectors(string start = "", string end = "") {
return(distanceBetweenVectors(trVectorQuestVarGet(start),trVectorQuestVarGet(end),false));
}

float distanceBetweenVectors3d(vector start = vector(0,0,0), vector end = vector(0,0,0), bool squared = true) {
float xdiff = xsVectorGetX(start) - xsVectorGetX(end);
float ydiff = xsVectorGetY(start) - xsVectorGetY(end);
float zdiff = xsVectorGetZ(start) - xsVectorGetZ(end);
float dist = xdiff * xdiff + ydiff * ydiff + zdiff * zdiff;
if (squared == false) {
dist = xsSqrt(dist);
}
return(dist);
}

float trDistanceBetweenVectors3d(string start = "", string end = "") {
return(distanceBetweenVectors3d(trVectorQuestVarGet(start),trVectorQuestVarGet(end),false));
}

float unitDistanceToVector(int name = 0, vector v = vector(0,0,0), bool squared = true) {
vector temp = kbGetBlockPosition(""+name,true);
return(distanceBetweenVectors(temp,v,squared));
}

float trDistanceToVectorSquared(string qv = "", string v = "") {
return(unitDistanceToVector(1*trQuestVarGet(qv),trVectorQuestVarGet(v)));
}

float trDistanceToVector(string qv = "", string v = "") {
return(unitDistanceToVector(1*trQuestVarGet(qv),trVectorQuestVarGet(v),false));
}

vector vectorSetFromAngle(float angle = 0) {
return(xsVectorSet(xsSin(angle), 0, xsCos(angle)));
}

void trVectorSetFromAngle(string qv = "", float angle = 0) {
trVectorQuestVarSet(qv,xsVectorSet(xsSin(angle), 0, xsCos(angle)));
}

float angleBetweenVectors(vector from = vector(0,0,0), vector to = vector(0,0,0)) {
float a = xsVectorGetX(to) - xsVectorGetX(from);
a = a / (xsVectorGetZ(to) - xsVectorGetZ(from));
a = xsAtan(a);
if (xsVectorGetZ(from) > xsVectorGetZ(to)) {
if (xsVectorGetX(from) > xsVectorGetX(to)) {
a = a - PI;
} else {
a = a + PI;
}
}
return(a);
}

float trAngleBetweenVectors(string from = "", string to = "") {
return(angleBetweenVectors(trVectorQuestVarGet(from),trVectorQuestVarGet(to)));
}

float angleOfVector(vector dir = vector(0,0,0)) {
float a = xsVectorGetX(dir) / xsVectorGetZ(dir);
a = xsAtan(a);
if (0.0 > xsVectorGetZ(dir)) {
if (0.0 > xsVectorGetX(dir)) {
a = a - PI;
} else {
a = a + PI;
}
}
return(a);
}

float trAngleOfVector(string v = "") {
return(angleOfVector(trVectorQuestVarGet(v)));
}

vector getUnitVector(vector start = vector(0,0,0), vector end = vector(0,0,0), float mod = 1.0) {
float xdiff = xsVectorGetX(end) - xsVectorGetX(start);
float zdiff = xsVectorGetZ(end) - xsVectorGetZ(start);
float dist = xsSqrt(xdiff * xdiff + zdiff * zdiff);
vector ret = vector(1,0,0);
if (dist > 0) {
ret = xsVectorSet(xdiff / dist * mod, 0, zdiff / dist * mod);
}
return(ret);
}

vector trGetUnitVector(string start = "", string end = "", float mod = 1.0) {
return(getUnitVector(trVectorQuestVarGet(start),trVectorQuestVarGet(end),mod));
}

vector getUnitVector3d(vector start = vector(0,0,0), vector end = vector(0,0,0), float mod = 1.0) {
float xdiff = xsVectorGetX(end) - xsVectorGetX(start);
float ydiff = xsVectorGetY(end) - xsVectorGetY(start);
float zdiff = xsVectorGetZ(end) - xsVectorGetZ(start);
float dist = xsSqrt(xdiff * xdiff + ydiff * ydiff + zdiff * zdiff);
vector ret = vector(0,1,0);
if (dist > 0) {
ret = xsVectorSet(xdiff / dist * mod, ydiff / dist * mod, zdiff / dist * mod);
}
return(ret);
}

vector trGetUnitVector3d(string start = "", string end = "", float mod = 1.0) {
return(getUnitVector3d(trVectorQuestVarGet(start),trVectorQuestVarGet(end),mod));
}

vector crossProduct(vector a = vector(0,0,0), vector b = vector(0,0,0)) {
float x = xsVectorGetY(a) * xsVectorGetZ(b) - xsVectorGetZ(a) * xsVectorGetY(b);
float y = xsVectorGetZ(a) * xsVectorGetX(b) - xsVectorGetX(a) * xsVectorGetZ(b);
float z = xsVectorGetX(a) * xsVectorGetY(b) - xsVectorGetY(a) * xsVectorGetX(b);
vector ret = xsVectorSet(x, y, z);
return(ret);
}

float dotProduct(vector a = vector(0,0,0), vector b = vector(0,0,0)) {
return(xsVectorGetX(a) * xsVectorGetX(b) + xsVectorGetZ(a) * xsVectorGetZ(b));
}

bool terrainIsType(vector v = vector(0,0,0), int type = 0, int subtype = 0) {
bool isType = trGetTerrainType(xsVectorGetX(v),xsVectorGetZ(v)) == type;
isType = trGetTerrainSubType(xsVectorGetX(v),xsVectorGetZ(v)) == subtype;
return(isType);
}

bool trTerrainIsType(string qv = "", int type = 0, int subtype = 0) {
return(terrainIsType(trVectorQuestVarGet(qv),type,subtype));
}

void modularCounterInit(string name = "", int size = 0) {
trQuestVarSet("counter" + name + "size", size);
trQuestVarSet("counter" + name + "pointer", 1);
trQuestVarSet(name, 1);
}

int modularCounterNext(string name = "") {
trQuestVarSet("counter" + name + "pointer", 1 + trQuestVarGet("counter" + name + "pointer"));
if (trQuestVarGet("counter" + name + "pointer") > trQuestVarGet("counter" + name + "size")) {
trQuestVarSet("counter" + name + "pointer", 1);
}
trQuestVarSet(name, trQuestVarGet("counter"+name+"pointer"));
return(0 + trQuestVarGet("counter" + name + "pointer"));
}

int peekModularCounterNext(string name = "") {
trQuestVarSet("counter" + name + "fake", 1 + trQuestVarGet("counter" + name + "pointer"));
if (trQuestVarGet("counter" + name + "fake") >= trQuestVarGet("counter" + name + "size")) {
trQuestVarSet("counter" + name + "fake", 1);
}
return(0 + trQuestVarGet("counter" + name + "fake"));
}

bool yDatabaseCreateIfNull(string dbname = "", int count = 0) {
bool created = false;
if (trQuestVarGet("database"+dbname) == 0) {
if (count < 0) {
count = 0;
}
trQuestVarSet("database"+dbname, xInitDatabase(dbname, count));
created = true;
}
return(created);
}

bool yVariableExists(string dbname = "", string varname = "") {
int db = trQuestVarGet("database"+dbname);
int var = trQuestVarGet("database"+dbname+varname);
return(db * var > 0);
}

float yGetVarAtIndex(string db = "", string var = "", int index = 0) {
if (yVariableExists(db, var)) {
return(xGetFloat(1*trQuestVarGet("database"+db),1*trQuestVarGet("database"+db+var),index));
} else {
return(0);
}
}

float yGetVar(string db = "", string var = "") {
return(yGetVarAtIndex(db, var, -1));
}

string yGetStringAtIndex(string db = "", string var = "", int index = 0) {
if (yVariableExists(db, var)) {
return(xGetString(1*trQuestVarGet("database"+db),1*trQuestVarGet("database"+db+var),index));
} else {
return("");
}
}

string yGetString(string db = "", string var = "") {
return(yGetStringAtIndex(db, var, -1));
}

vector yGetVectorAtIndex(string db = "", string var = "", int index = 0) {
if (yVariableExists(db, var)) {
return(xGetVector(1*trQuestVarGet("database"+db),1*trQuestVarGet("database"+db+var),index));
} else {
return(vector(0,0,0));
}
}

vector yGetVector(string db = "", string var = "") {
return(yGetVectorAtIndex(db, var, -1));
}

void ySetVarAtIndex(string db = "", string var = "", float val = 0, int index = 0) {
if (yVariableExists(db, var)) {
xSetFloat(1*trQuestVarGet("database"+db),1*trQuestVarGet("database"+db+var),val,index);
} else {
yDatabaseCreateIfNull(db, index);
trQuestVarSet("database"+db+var, xInitAddFloat(1*trQuestVarGet("database"+db),var));
xSetFloat(1*trQuestVarGet("database"+db),1*trQuestVarGet("database"+db+var),val,index);
}
}

void ySetVar(string db = "", string var = "", float val = 0) {
ySetVarAtIndex(db, var, val, -1);
}

void ySetStringAtIndex(string db = "", string var = "", string val = "", int index = 0) {
if (yVariableExists(db, var)) {
xSetString(1*trQuestVarGet("database"+db),1*trQuestVarGet("database"+db+var),val,index);
} else {
yDatabaseCreateIfNull(db, index);
trQuestVarSet("database"+db+var, xInitAddFloat(1*trQuestVarGet("database"+db),var));
xSetString(1*trQuestVarGet("database"+db),1*trQuestVarGet("database"+db+var),val,index);
}
}

void ySetString(string db = "", string var = "", string val = "") {
ySetStringAtIndex(db, var, val, -1);
}

void ySetVectorAtIndex(string db = "", string var = "", vector val = vector(0,0,0), int index = 0) {
if (yVariableExists(db, var)) {
xSetVector(1*trQuestVarGet("database"+db),1*trQuestVarGet("database"+db+var),val,index);
} else {
yDatabaseCreateIfNull(db, index);
trQuestVarSet("database"+db+var, xInitAddFloat(1*trQuestVarGet("database"+db),var));
xSetVector(1*trQuestVarGet("database"+db),1*trQuestVarGet("database"+db+var),val,index);
}
}

void ySetVector(string db = "", string var = "", vector val = vector(0,0,0)) {
ySetVectorAtIndex(db, var, val, -1);
}

int yDatabaseNext(string db = "", bool select = false, bool reverse = false) {
xDatabaseNext(1*trQuestVarGet("database"+db), reverse);
int u = yGetVar(db, "unitName");
trQuestVarSet(db, u);
if (select) {
trUnitSelectClear();
trUnitSelect(""+u, true);
return(kbGetBlockID(""+u, true));
} else {
return(u);
}
}

void yRemoveFromDatabase(string db = "") {
xFreeDatabaseBlock(1*trQuestVarGet("database"+db));
}

int yGetNewestPointer(string db = "") {
return(xGetNewestPointer(1*trQuestVarGet("database"+db)));
}

void yAddUpdateVar(string db = "", string var = "", float val = 0) {
ySetVarAtIndex(db, var, val, yGetNewestPointer(db));
}

void yAddUpdateString(string db = "", string var = "", string val = "") {
ySetStringAtIndex(db, var, val, yGetNewestPointer(db));
}

void yAddUpdateVector(string db = "", string var = "", vector val = vector(0,0,0)) {
ySetVectorAtIndex(db, var, val, yGetNewestPointer(db));
}

int yAddToDatabase(string db = "", string val = "") {
yDatabaseCreateIfNull(db);
int id = trQuestVarGet("database"+db);
int next = xAddDatabaseBlock(id);
yAddUpdateVar(db, "unitName", trQuestVarGet(val));
return(next);
}

int yGetPointer(string db = "") {
return(xGetPointer(1*trQuestVarGet("database"+db)));
}

bool ySetPointer(string db = "", int index = 0) {
bool safe = xSetPointer(1*trQuestVarGet("database"+db), index);
if (safe) {
trQuestVarSet(db, yGetVar(db, "unitName"));
}
return(safe);
}


int yGetDatabaseCount(string db = "") {
return(xGetDatabaseCount(1*trQuestVarGet("database"+db)));
}

int yGetUnitAtIndex(string db = "", int index = 0) {
return(1*yGetVarAtIndex(db, "unitName", index));
}

void ySetUnitAtIndex(string db = "", int index = 0, int value = 0) {
ySetVarAtIndex(db, "unitName", value, index);
}

void ySetUnit(string db = "", int value = 0) {
ySetVar(db, "unitName", value);
}

void yClearDatabase(string db = "") {
xClearDatabase(1*trQuestVarGet("database"+db));
}


int yFindLatestReverse(string qv = "", string proto = "", int p = 0) {
int id = kbGetProtoUnitID(proto);
trUnitSelectClear();
for(x=trGetNextUnitScenarioNameNumber(); >trQuestVarGet(qv)) {
int i = kbGetBlockID(""+x, true);
if (kbGetUnitBaseTypeID(i) == id) {
trUnitSelectClear();
trUnitSelectByID(i);
if (trUnitIsOwnedBy(p)) {
trQuestVarSet(qv, x);
return(i);
}
}
}
return(-1);
}

int yFindLatest(string qv = "", string proto = "", int p = 0) {
int id = kbGetProtoUnitID(proto);
trUnitSelectClear();
int next = trGetNextUnitScenarioNameNumber() - 1;
int current = trQuestVarGet(qv);
while(next > current) {
current = current + 1;
int i = kbGetBlockID(""+current, true);
if (kbGetUnitBaseTypeID(i) == id) {
trUnitSelectClear();
trUnitSelectByID(i);
if (trUnitIsOwnedBy(p)) {
trQuestVarSet(qv, current);
return(i);
}
}
}
return(-1);
}
rmSwitchToTrigger(rmCreateTrigger("zenowashere"));
rmSetTriggerPriority(4);
rmSetTriggerActive(false);
rmSetTriggerLoop(false);
rmSetTriggerRunImmediately(true);
rmAddTriggerEffect("SetIdleProcessing");
rmSetTriggerEffectParam("IdleProc",");}}/*");
code("int deployLocHeading(float posX = 0.0, float PosZ = 0.0, string unit = \"\", int p = 0, float heading = 0.0){");
code("int unitId = trGetNextUnitScenarioNameNumber();");
code("trArmyDispatch(\"\"+p+\",0\",unit,1,posX,0,PosZ,heading,true);");
code("if(unitId != trGetNextUnitScenarioNameNumber()){");
code("return (unitId);");
code("} else {");
code("return (-1);");
code("}");
code("}");

code("int deployLoc(float posX = 0.0, float PosZ = 0.0, string unit = \"\", int p = 0){");
code("int unitId = trGetNextUnitScenarioNameNumber();");
code("trArmyDispatch(\"\"+p+\",0\",unit,1,posX,0,PosZ,0,true);");
code("if(unitId != trGetNextUnitScenarioNameNumber()){");
code("return (unitId);");
code("} else {");
code("return (-1);");
code("}");
code("}");

code("void playSound(string soundName = \"\"){");
code("trSoundPlayPaused(\"\"+soundName+\"\", \"1\", -1, \"\", \"\");");
code("}");

code("int deployLocRandomHeading(float posX = 0.0, float PosZ = 0.0, string unit = \"\", int p = 0){");
code("int unitId = trGetNextUnitScenarioNameNumber();");
code("trQuestVarSetFromRand(\"heading\", 0, 359, true);");
code("trArmyDispatch(\"\"+p+\",0\",unit,1,posX,0,PosZ,1*trQuestVarGet(\"heading\"),true);");
code("if(unitId != trGetNextUnitScenarioNameNumber()){");
code("return (unitId);");
code("} else {");
code("return (-1);");
code("}");
code("}");

code("int getTerrainType(string name = \"\"){");
code("if(name == \"GrassA\")return (0);");
code("if(name == \"GrassB\")return (0);");
code("if(name == \"GrassDirt25\")return (0);");
code("if(name == \"GrassDirt50\")return (0);");
code("if(name == \"GrassDirt75\")return (0);");
code("if(name == \"CliffGreekB\")return (0);");
code("if(name == \"GreekRoad Burnt\")return (0);");
code("if(name == \"GreekRoad BurntB\")return (0);");
code("if(name == \"GaiaCreepA\")return (0);");
code("if(name == \"GaiaCreepASnow\")return (0);");
code("if(name == \"GaiaCreepASand\")return (0);");
code("if(name == \"GaiaCreepB\")return (0);");
code("if(name == \"GaiaCreepBorder\")return (0);");
code("if(name == \"GaiaCreepBorderSnow\")return (0);");
code("if(name == \"GaiaCreepBorderSand\")return (0);");
code("if(name == \"SavannahA\")return (0);");
code("if(name == \"SavannahB\")return (0);");
code("if(name == \"SavannahC\")return (0);");
code("if(name == \"SavannahD\")return (0);");
code("if(name == \"JungleA\")return (0);");
code("if(name == \"JungleB\")return (0);");
code("if(name == \"JungleDirt25\")return (0);");
code("if(name == \"JungleDirt50\")return (0);");
code("if(name == \"JungleDirt75\")return (0);");
code("if(name == \"CliffJungleB\")return (0);");
code("if(name == \"PlainA\")return (0);");
code("if(name == \"PlainB\")return (0);");
code("if(name == \"PlainDirt25\")return (0);");
code("if(name == \"PlainDirt50\")return (0);");
code("if(name == \"PlainDirt75\")return (0);");
code("if(name == \"CliffPlainB\")return (0);");
code("if(name == \"DirtA\")return (0);");
code("if(name == \"DirtB\")return (0);");
code("if(name == \"DirtC\")return (0);");
code("if(name == \"SandA\")return (0);");
code("if(name == \"SandB\")return (0);");
code("if(name == \"SandC\")return (0);");
code("if(name == \"SandD\")return (0);");
code("if(name == \"CliffEgyptianB\")return (0);");
code("if(name == \"SandDirt50\")return (0);");
code("if(name == \"SandDirt50b\")return (0);");
code("if(name == \"SnowA\")return (0);");
code("if(name == \"SnowB\")return (0);");
code("if(name == \"SnowGrass25\")return (0);");
code("if(name == \"SnowGrass50\")return (0);");
code("if(name == \"SnowGrass75\")return (0);");
code("if(name == \"SnowSand25\")return (0);");
code("if(name == \"SnowSand50\")return (0);");
code("if(name == \"SnowSand75\")return (0);");
code("if(name == \"CliffNorseB\")return (0);");
code("if(name == \"OlympusA\")return (0);");
code("if(name == \"OlympusB\")return (0);");
code("if(name == \"OlympusC\")return (0);");
code("if(name == \"OlympusTile\")return (0);");
code("if(name == \"TundraGrassA\")return (0);");
code("if(name == \"TundraGrassB\")return (0);");
code("if(name == \"TundraRockA\")return (0);");
code("if(name == \"TundraRockB\")return (0);");
code("if(name == \"MarshA\")return (0);");
code("if(name == \"MarshB\")return (0);");
code("if(name == \"MarshC\")return (0);");
code("if(name == \"MarshD\")return (0);");
code("if(name == \"MarshE\")return (0);");
code("if(name == \"MarshF\")return (0);");
code("if(name == \"EgyptianRoadA\")return (0);");
code("if(name == \"GreekRoadA\")return (0);");
code("if(name == \"NorseRoadA\")return (0);");
code("if(name == \"JungleRoadA\")return (0);");
code("if(name == \"PlainRoadA\")return (0);");
code("if(name == \"TundraRoadA\")return (0);");
code("if(name == \"CityTileA\")return (0);");
code("if(name == \"CityTileAtlantis\")return (0);");
code("if(name == \"CityTileAtlantisCoral\")return (0);");
code("if(name == \"CityTileWaterPool\")return (0);");
code("if(name == \"CityTileWaterEdgeA\")return (0);");
code("if(name == \"CityTileWaterEdgeB\")return (0);");
code("if(name == \"CityTileWaterEdgeEndA\")return (0);");
code("if(name == \"CityTileWaterEdgeEndB\")return (0);");
code("if(name == \"CityTileWaterEdgeEndC\")return (0);");
code("if(name == \"CityTileWaterEdgeEndD\")return (0);");
code("if(name == \"CityTileWaterCornerA\")return (0);");
code("if(name == \"CityTileWaterCornerB\")return (0);");
code("if(name == \"CityTileWaterCornerC\")return (0);");
code("if(name == \"CityTileWaterCornerD\")return (0);");
code("if(name == \"HadesBuildable1\")return (0);");
code("if(name == \"HadesBuildable2\")return (0);");
code("if(name == \"ForestFloorPalm\")return (0);");
code("if(name == \"ForestFloorPine\")return (0);");
code("if(name == \"ForestFloorPineSnow\")return (0);");
code("if(name == \"ForestFloorOak\")return (0);");
code("if(name == \"ForestFloorGaia\")return (0);");
code("if(name == \"ForestFloorSavannah\")return (0);");
code("if(name == \"ForestFloorDeadPine\")return (0);");
code("if(name == \"ForestFloorTundra\")return (0);");
code("if(name == \"ForestFloorMarsh\")return (0);");
code("if(name == \"ForestFloorJungle\")return (0);");
code("if(name == \"Water\")return (1);");
code("if(name == \"CliffA\")return (2);");
code("if(name == \"CliffGreekA\")return (2);");
code("if(name == \"CliffEgyptianA\")return (2);");
code("if(name == \"CliffNorseA\")return (2);");
code("if(name == \"CliffJungleA\")return (2);");
code("if(name == \"CliffPlainA\")return (2);");
code("if(name == \"Dam\")return (2);");
code("if(name == \"Hades3\")return (2);");
code("if(name == \"Hades5\")return (2);");
code("if(name == \"Hades6\")return (2);");
code("if(name == \"Hades7\")return (2);");
code("if(name == \"HadesCliff\")return (2);");
code("if(name == \"Hades4\")return (2);");
code("if(name == \"BlackRock\")return (2);");
code("if(name == \"UnderwaterRockA\")return (3);");
code("if(name == \"UnderwaterRockB\")return (3);");
code("if(name == \"UnderwaterRockC\")return (3);");
code("if(name == \"UnderwaterRockD\")return (3);");
code("if(name == \"UnderwaterRockE\")return (3);");
code("if(name == \"UnderwaterRockF\")return (3);");
code("if(name == \"UnderwaterIceA\")return (3);");
code("if(name == \"UnderwaterIceB\")return (3);");
code("if(name == \"UnderwaterIceC\")return (3);");
code("if(name == \"CoralA\")return (3);");
code("if(name == \"CoralB\")return (3);");
code("if(name == \"CoralC\")return (3);");
code("if(name == \"CoralC2\")return (3);");
code("if(name == \"CoralD\")return (3);");
code("if(name == \"CoralE\")return (3);");
code("if(name == \"CoralF\")return (3);");
code("if(name == \"ShorelineSandA\")return (4);");
code("if(name == \"ShorelineAegeanA\")return (4);");
code("if(name == \"ShorelineAegeanB\")return (4);");
code("if(name == \"ShorelineAegeanC\")return (4);");
code("if(name == \"ShorelineRedSeaA\")return (4);");
code("if(name == \"ShorelineRedSeaB\")return (4);");
code("if(name == \"ShorelineRedSeaC\")return (4);");
code("if(name == \"ShorelineNorwegianA\")return (4);");
code("if(name == \"ShorelineNorwegianB\")return (4);");
code("if(name == \"ShorelineNorwegianC\")return (4);");
code("if(name == \"ShorelineMediterraneanA\")return (4);");
code("if(name == \"ShorelineMediterraneanB\")return (4);");
code("if(name == \"ShorelineMediterraneanC\")return (4);");
code("if(name == \"ShorelineMediterraneanD\")return (4);");
code("if(name == \"ShorelineAtlanticA\")return (4);");
code("if(name == \"ShorelineAtlanticB\")return (4);");
code("if(name == \"ShorelineAtlanticC\")return (4);");
code("if(name == \"ShorelineTundraA\")return (4);");
code("if(name == \"ShorelineTundraB\")return (4);");
code("if(name == \"ShorelineTundraC\")return (4);");
code("if(name == \"ShorelineTundraD\")return (4);");
code("if(name == \"ShorelineJungleA\")return (4);");
code("if(name == \"ShorelineJungleB\")return (4);");
code("if(name == \"ShorelineJungleC\")return (4);");
code("if(name == \"ShorelinePlainA\")return (4);");
code("if(name == \"ShorelinePlainB\")return (4);");
code("if(name == \"ShorelinePlainC\")return (4);");
code("if(name == \"ShorelinePlainD\")return (4);");
code("if(name == \"RiverSandyA\")return (4);");
code("if(name == \"RiverSandyB\")return (4);");
code("if(name == \"RiverSandyC\")return (4);");
code("if(name == \"RiverSandyShallowA\")return (4);");
code("if(name == \"RiverGrassyA\")return (4);");
code("if(name == \"RiverGrassyB\")return (4);");
code("if(name == \"RiverGrassyC\")return (4);");
code("if(name == \"RiverIcyA\")return (4);");
code("if(name == \"RiverIcyB\")return (4);");
code("if(name == \"RiverIcyC\")return (4);");
code("if(name == \"RiverMarshA\")return (4);");
code("if(name == \"RiverMarshB\")return (4);");
code("if(name == \"RiverMarshC\")return (4);");
code("if(name == \"IceA\")return (5);");
code("if(name == \"IceB\")return (5);");
code("if(name == \"IceC\")return (5);");
code("if(name == \"MiningGround\")return (5);");
code("if(name == \"Black\")return (5);");
code("if(name == \"Hades1\")return (5);");
code("if(name == \"Hades2\")return (5);");
code("if(name == \"Hades4Passable\")return (5);");
code("if(name == \"Hades8\")return (5);");
code("if(name == \"Hades9\")return (5);");
code("}");
code("int getTerrainSubType(string name = \"\"){");
code("if(name == \"GrassA\")return (0);");
code("if(name == \"GrassB\")return (1);");
code("if(name == \"GrassDirt25\")return (2);");
code("if(name == \"GrassDirt50\")return (3);");
code("if(name == \"GrassDirt75\")return (4);");
code("if(name == \"CliffGreekB\")return (5);");
code("if(name == \"GreekRoad Burnt\")return (6);");
code("if(name == \"GreekRoad BurntB\")return (7);");
code("if(name == \"GaiaCreepA\")return (8);");
code("if(name == \"GaiaCreepASnow\")return (9);");
code("if(name == \"GaiaCreepASand\")return (10);");
code("if(name == \"GaiaCreepB\")return (11);");
code("if(name == \"GaiaCreepBorder\")return (12);");
code("if(name == \"GaiaCreepBorderSnow\")return (13);");
code("if(name == \"GaiaCreepBorderSand\")return (14);");
code("if(name == \"SavannahA\")return (15);");
code("if(name == \"SavannahB\")return (16);");
code("if(name == \"SavannahC\")return (17);");
code("if(name == \"SavannahD\")return (18);");
code("if(name == \"JungleA\")return (19);");
code("if(name == \"JungleB\")return (20);");
code("if(name == \"JungleDirt25\")return (21);");
code("if(name == \"JungleDirt50\")return (22);");
code("if(name == \"JungleDirt75\")return (23);");
code("if(name == \"CliffJungleB\")return (24);");
code("if(name == \"PlainA\")return (25);");
code("if(name == \"PlainB\")return (26);");
code("if(name == \"PlainDirt25\")return (27);");
code("if(name == \"PlainDirt50\")return (28);");
code("if(name == \"PlainDirt75\")return (29);");
code("if(name == \"CliffPlainB\")return (30);");
code("if(name == \"DirtA\")return (31);");
code("if(name == \"DirtB\")return (32);");
code("if(name == \"DirtC\")return (33);");
code("if(name == \"SandA\")return (34);");
code("if(name == \"SandB\")return (35);");
code("if(name == \"SandC\")return (36);");
code("if(name == \"SandD\")return (37);");
code("if(name == \"CliffEgyptianB\")return (38);");
code("if(name == \"SandDirt50\")return (39);");
code("if(name == \"SandDirt50b\")return (40);");
code("if(name == \"SnowA\")return (41);");
code("if(name == \"SnowB\")return (42);");
code("if(name == \"SnowGrass25\")return (43);");
code("if(name == \"SnowGrass50\")return (44);");
code("if(name == \"SnowGrass75\")return (45);");
code("if(name == \"SnowSand25\")return (46);");
code("if(name == \"SnowSand50\")return (47);");
code("if(name == \"SnowSand75\")return (48);");
code("if(name == \"CliffNorseB\")return (49);");
code("if(name == \"OlympusA\")return (50);");
code("if(name == \"OlympusB\")return (51);");
code("if(name == \"OlympusC\")return (52);");
code("if(name == \"OlympusTile\")return (53);");
code("if(name == \"TundraGrassA\")return (54);");
code("if(name == \"TundraGrassB\")return (55);");
code("if(name == \"TundraRockA\")return (56);");
code("if(name == \"TundraRockB\")return (57);");
code("if(name == \"MarshA\")return (58);");
code("if(name == \"MarshB\")return (59);");
code("if(name == \"MarshC\")return (60);");
code("if(name == \"MarshD\")return (61);");
code("if(name == \"MarshE\")return (62);");
code("if(name == \"MarshF\")return (63);");
code("if(name == \"EgyptianRoadA\")return (64);");
code("if(name == \"GreekRoadA\")return (65);");
code("if(name == \"NorseRoadA\")return (66);");
code("if(name == \"JungleRoadA\")return (67);");
code("if(name == \"PlainRoadA\")return (68);");
code("if(name == \"TundraRoadA\")return (69);");
code("if(name == \"CityTileA\")return (70);");
code("if(name == \"CityTileAtlantis\")return (71);");
code("if(name == \"CityTileAtlantisCoral\")return (72);");
code("if(name == \"CityTileWaterPool\")return (73);");
code("if(name == \"CityTileWaterEdgeA\")return (74);");
code("if(name == \"CityTileWaterEdgeB\")return (75);");
code("if(name == \"CityTileWaterEdgeEndA\")return (76);");
code("if(name == \"CityTileWaterEdgeEndB\")return (77);");
code("if(name == \"CityTileWaterEdgeEndC\")return (78);");
code("if(name == \"CityTileWaterEdgeEndD\")return (79);");
code("if(name == \"CityTileWaterCornerA\")return (80);");
code("if(name == \"CityTileWaterCornerB\")return (81);");
code("if(name == \"CityTileWaterCornerC\")return (82);");
code("if(name == \"CityTileWaterCornerD\")return (83);");
code("if(name == \"HadesBuildable1\")return (84);");
code("if(name == \"HadesBuildable2\")return (85);");
code("if(name == \"ForestFloorPalm\")return (86);");
code("if(name == \"ForestFloorPine\")return (87);");
code("if(name == \"ForestFloorPineSnow\")return (88);");
code("if(name == \"ForestFloorOak\")return (89);");
code("if(name == \"ForestFloorGaia\")return (90);");
code("if(name == \"ForestFloorSavannah\")return (91);");
code("if(name == \"ForestFloorDeadPine\")return (92);");
code("if(name == \"ForestFloorTundra\")return (93);");
code("if(name == \"ForestFloorMarsh\")return (94);");
code("if(name == \"ForestFloorJungle\")return (95);");
code("if(name == \"Water\")return (0);");
code("if(name == \"CliffA\")return (0);");
code("if(name == \"CliffGreekA\")return (1);");
code("if(name == \"CliffEgyptianA\")return (2);");
code("if(name == \"CliffNorseA\")return (3);");
code("if(name == \"CliffJungleA\")return (4);");
code("if(name == \"CliffPlainA\")return (5);");
code("if(name == \"Dam\")return (6);");
code("if(name == \"Hades3\")return (7);");
code("if(name == \"Hades5\")return (8);");
code("if(name == \"Hades6\")return (9);");
code("if(name == \"Hades7\")return (10);");
code("if(name == \"HadesCliff\")return (11);");
code("if(name == \"Hades4\")return (12);");
code("if(name == \"BlackRock\")return (13);");
code("if(name == \"UnderwaterRockA\")return (0);");
code("if(name == \"UnderwaterRockB\")return (1);");
code("if(name == \"UnderwaterRockC\")return (2);");
code("if(name == \"UnderwaterRockD\")return (3);");
code("if(name == \"UnderwaterRockE\")return (4);");
code("if(name == \"UnderwaterRockF\")return (5);");
code("if(name == \"UnderwaterIceA\")return (6);");
code("if(name == \"UnderwaterIceB\")return (7);");
code("if(name == \"UnderwaterIceC\")return (8);");
code("if(name == \"CoralA\")return (9);");
code("if(name == \"CoralB\")return (10);");
code("if(name == \"CoralC\")return (11);");
code("if(name == \"CoralC2\")return (12);");
code("if(name == \"CoralD\")return (13);");
code("if(name == \"CoralE\")return (14);");
code("if(name == \"CoralF\")return (15);");
code("if(name == \"ShorelineSandA\")return (0);");
code("if(name == \"ShorelineAegeanA\")return (1);");
code("if(name == \"ShorelineAegeanB\")return (2);");
code("if(name == \"ShorelineAegeanC\")return (3);");
code("if(name == \"ShorelineRedSeaA\")return (4);");
code("if(name == \"ShorelineRedSeaB\")return (5);");
code("if(name == \"ShorelineRedSeaC\")return (6);");
code("if(name == \"ShorelineNorwegianA\")return (7);");
code("if(name == \"ShorelineNorwegianB\")return (8);");
code("if(name == \"ShorelineNorwegianC\")return (9);");
code("if(name == \"ShorelineMediterraneanA\")return (10);");
code("if(name == \"ShorelineMediterraneanB\")return (11);");
code("if(name == \"ShorelineMediterraneanC\")return (12);");
code("if(name == \"ShorelineMediterraneanD\")return (13);");
code("if(name == \"ShorelineAtlanticA\")return (14);");
code("if(name == \"ShorelineAtlanticB\")return (15);");
code("if(name == \"ShorelineAtlanticC\")return (16);");
code("if(name == \"ShorelineTundraA\")return (17);");
code("if(name == \"ShorelineTundraB\")return (18);");
code("if(name == \"ShorelineTundraC\")return (19);");
code("if(name == \"ShorelineTundraD\")return (20);");
code("if(name == \"ShorelineJungleA\")return (21);");
code("if(name == \"ShorelineJungleB\")return (22);");
code("if(name == \"ShorelineJungleC\")return (23);");
code("if(name == \"ShorelinePlainA\")return (24);");
code("if(name == \"ShorelinePlainB\")return (25);");
code("if(name == \"ShorelinePlainC\")return (26);");
code("if(name == \"ShorelinePlainD\")return (27);");
code("if(name == \"RiverSandyA\")return (28);");
code("if(name == \"RiverSandyB\")return (29);");
code("if(name == \"RiverSandyC\")return (30);");
code("if(name == \"RiverSandyShallowA\")return (31);");
code("if(name == \"RiverGrassyA\")return (32);");
code("if(name == \"RiverGrassyB\")return (33);");
code("if(name == \"RiverGrassyC\")return (34);");
code("if(name == \"RiverIcyA\")return (35);");
code("if(name == \"RiverIcyB\")return (36);");
code("if(name == \"RiverIcyC\")return (37);");
code("if(name == \"RiverMarshA\")return (38);");
code("if(name == \"RiverMarshB\")return (39);");
code("if(name == \"RiverMarshC\")return (40);");
code("if(name == \"IceA\")return (0);");
code("if(name == \"IceB\")return (1);");
code("if(name == \"IceC\")return (2);");
code("if(name == \"MiningGround\")return (3);");
code("if(name == \"Black\")return (4);");
code("if(name == \"Hades1\")return (5);");
code("if(name == \"Hades2\")return (6);");
code("if(name == \"Hades4Passable\")return (7);");
code("if(name == \"Hades8\")return (8);");
code("if(name == \"Hades9\")return (9);");
code("}");

code("void grantGodPowerNoRechargeNextPosition(int p = 0, string power = \"\", int count = 0) {");
code("for(tempPowerTech = -1; > 1){}");
code("for(tempPosition = -1; > 1){}");
code("if(power==\"Animal Magnetism\")tempPowerTech=227;");
code("if(power==\"Audrey\")tempPowerTech=407;");
code("if(power==\"Barrage\")tempPowerTech=546;");
code("if(power==\"Blessing of Zeus\")tempPowerTech=351;");
code("if(power==\"Bolt\")tempPowerTech=221;");
code("if(power==\"Bronze\")tempPowerTech=175;");
code("if(power==\"Bronze XP05\")tempPowerTech=457;");
code("if(power==\"Call to Arms\")tempPowerTech=547;");
code("if(power==\"Cease Fire\")tempPowerTech=147;");
code("if(power==\"Cease Fire Nomad\")tempPowerTech=376;");
code("if(power==\"Change Caladria\")tempPowerTech=464;");
code("if(power==\"Change Chimera\")tempPowerTech=463;");
code("if(power==\"Change Cyclops\")tempPowerTech=462;");
code("if(power==\"Change Hydra\")tempPowerTech=467;");
code("if(power==\"Change Manticore\")tempPowerTech=465;");
code("if(power==\"Change Nemean\")tempPowerTech=466;");
code("if(power==\"Chaos\")tempPowerTech=409;");
code("if(power==\"Chicken Storm\")tempPowerTech=388;");
code("if(power==\"Citadel\")tempPowerTech=232;");
code("if(power==\"Create Gold\")tempPowerTech=84;");
code("if(power==\"Curse\")tempPowerTech=229;");
code("if(power==\"Earth Dragon\")tempPowerTech=557;");
code("if(power==\"Earthquake\")tempPowerTech=239;");
code("if(power==\"Eclipse\")tempPowerTech=214;");
code("if(power==\"Examination\")tempPowerTech=550;");
code("if(power==\"Flaming Weapons\")tempPowerTech=223;");
code("if(power==\"Flood\")tempPowerTech=555;");
code("if(power==\"Flood Weak\")tempPowerTech=556;");
code("if(power==\"Forest Fire\")tempPowerTech=248;");
code("if(power==\"Forest Fire SPC\")tempPowerTech=594;");
code("if(power==\"Frost\")tempPowerTech=57;");
code("if(power==\"Gaia Forest\")tempPowerTech=418;");
code("if(power==\"Gaia Forest SPC\")tempPowerTech=505;");
code("if(power==\"Geyser\")tempPowerTech=552;");
code("if(power==\"Goatunheim\")tempPowerTech=391;");
code("if(power==\"Great Hunt\")tempPowerTech=146;");
code("if(power==\"Healing Spring\")tempPowerTech=228;");
code("if(power==\"Heroize\")tempPowerTech=439;");
code("if(power==\"Hesperides\")tempPowerTech=436;");
code("if(power==\"Implode\")tempPowerTech=442;");
code("if(power==\"Inferno\")tempPowerTech=558;");
code("if(power==\"Journey\")tempPowerTech=548;");
code("if(power==\"Lightning Storm\")tempPowerTech=42;");
code("if(power==\"Locust Swarm\")tempPowerTech=43;");
code("if(power==\"Meteor\")tempPowerTech=61;");
code("if(power==\"Nidhogg\")tempPowerTech=235;");
code("if(power==\"Pestilence\")tempPowerTech=249;");
code("if(power==\"Plenty\")tempPowerTech=236;");
code("if(power==\"Prosperity\")tempPowerTech=211;");
code("if(power==\"Ragnorok\")tempPowerTech=234;");
code("if(power==\"Rain\")tempPowerTech=156;");
code("if(power==\"Recreation\")tempPowerTech=543;");
code("if(power==\"Restoration\")tempPowerTech=134;");
code("if(power==\"Reverse Time\")tempPowerTech=406;");
code("if(power==\"Reverse Wonder\")tempPowerTech=434;");
code("if(power==\"Sandstorm\")tempPowerTech=231;");
code("if(power==\"Seed of Gaia\")tempPowerTech=485;");
code("if(power==\"Sentinel\")tempPowerTech=230;");
code("if(power==\"Serpents\")tempPowerTech=226;");
code("if(power==\"Skeleton Power\")tempPowerTech=129;");
code("if(power==\"Snow Storm\")tempPowerTech=172;");
code("if(power==\"Son of Osiris\")tempPowerTech=237;");
code("if(power==\"SPCLightning Storm\")tempPowerTech=468;");
code("if(power==\"SPCMeteor\")tempPowerTech=334;");
code("if(power==\"Spiders\")tempPowerTech=438;");
code("if(power==\"Spy\")tempPowerTech=222;");
code("if(power==\"Tartarian Gate\")tempPowerTech=419;");
code("if(power==\"Timber Harvest\")tempPowerTech=545;");
code("if(power==\"TitanGate\")tempPowerTech=444;");
code("if(power==\"Tornado\")tempPowerTech=44;");
code("if(power==\"Tornado XP05\")tempPowerTech=458;");
code("if(power==\"Traitors\")tempPowerTech=408;");
code("if(power==\"Traitors SPC\")tempPowerTech=491;");
code("if(power==\"Tremor\")tempPowerTech=414;");
code("if(power==\"Tsunami\")tempPowerTech=598;");
code("if(power==\"Undermine\")tempPowerTech=152;");
code("if(power==\"Underworld Passage\")tempPowerTech=133;");
code("if(power==\"Uproot\")tempPowerTech=553;");
code("if(power==\"Uproot SPC\")tempPowerTech=554;");
code("if(power==\"Vision\")tempPowerTech=220;");
code("if(power==\"Volcano\")tempPowerTech=410;");
code("if(power==\"Vortex\")tempPowerTech=431;");
code("if(power==\"Walking Berry Bushes\")tempPowerTech=389;");
code("if(power==\"Walking Woods\")tempPowerTech=233;");
code("if(power==\"Water Damage\")tempPowerTech=615;");
code("if(power==\"Well of Urd\")tempPowerTech=366;");
code("if(power==\"Year of the Goat\")tempPowerTech=544;");
code("if(tempPowerTech>=0){");
code("if(trGetGPData(p, 0, 0) == tempPowerTech)tempPosition=0;");
code("if(trGetGPData(p, 0, 1) == tempPowerTech)tempPosition=1;");
code("if(trGetGPData(p, 0, 2) == tempPowerTech)tempPosition=2;");
code("if(trGetGPData(p, 0, 3) == tempPowerTech)tempPosition=3;");
code("if(trGetGPData(p, 0, 4) == tempPowerTech)tempPosition=4;");
code("if(tempPosition>=0){");
code("trSetGPData(p, 5, tempPosition, 0 - trGetGPData(p, 5, tempPosition));");
code("trSetGPData(p, 1, tempPosition, count);");
code("trSetGPData(p, 2, tempPosition, 0 - trGetGPData(p, 2, tempPosition));");
code("} else {");
code("if((trGetGPData(p, 1, 0) > 0 || trGetGPData(p, 2, 0) > 0) == false){");
code("tempPosition=0;");
code("} else if((trGetGPData(p, 1, 1) > 0 || trGetGPData(p, 2, 1) > 0) == false){");
code("tempPosition=1;");
code("} else if((trGetGPData(p, 1, 2) > 0 || trGetGPData(p, 2, 2) > 0) == false){");
code("tempPosition=2;");
code("} else {");
code("tempPosition=3;");
code("}");
code("trTechGodPowerAtPosition(p, power, 0, tempPosition + 1);");
code("trSetGPData(p, 5, tempPosition, 0 - trGetGPData(p, 5, tempPosition));");
code("trSetGPData(p, 1, tempPosition, count - trGetGPData(p, 1, tempPosition) + trGetGPData(p, 2, tempPosition));");
code("trSetGPData(p, 2, tempPosition, 0 - trGetGPData(p, 2, tempPosition));");
code("}");
code("}");
code("}");

code("void GPSetRechargeTime(int p = 0, string power =\"\", int time = 1000) {");
code("for(tempPowerTech = -1; > 1){}");
code("for(tempPosition = -1; > 1){}");
code("if(power==\"Animal Magnetism\")tempPowerTech=227;");
code("if(power==\"Audrey\")tempPowerTech=407;");
code("if(power==\"Barrage\")tempPowerTech=546;");
code("if(power==\"Blessing of Zeus\")tempPowerTech=351;");
code("if(power==\"Bolt\")tempPowerTech=221;");
code("if(power==\"Bronze\")tempPowerTech=175;");
code("if(power==\"Bronze XP05\")tempPowerTech=457;");
code("if(power==\"Call to Arms\")tempPowerTech=547;");
code("if(power==\"Cease Fire\")tempPowerTech=147;");
code("if(power==\"Cease Fire Nomad\")tempPowerTech=376;");
code("if(power==\"Change Caladria\")tempPowerTech=464;");
code("if(power==\"Change Chimera\")tempPowerTech=463;");
code("if(power==\"Change Cyclops\")tempPowerTech=462;");
code("if(power==\"Change Hydra\")tempPowerTech=467;");
code("if(power==\"Change Manticore\")tempPowerTech=465;");
code("if(power==\"Change Nemean\")tempPowerTech=466;");
code("if(power==\"Chaos\")tempPowerTech=409;");
code("if(power==\"Chicken Storm\")tempPowerTech=388;");
code("if(power==\"Citadel\")tempPowerTech=232;");
code("if(power==\"Create Gold\")tempPowerTech=84;");
code("if(power==\"Curse\")tempPowerTech=229;");
code("if(power==\"Earth Dragon\")tempPowerTech=557;");
code("if(power==\"Earthquake\")tempPowerTech=239;");
code("if(power==\"Eclipse\")tempPowerTech=214;");
code("if(power==\"Examination\")tempPowerTech=550;");
code("if(power==\"Flaming Weapons\")tempPowerTech=223;");
code("if(power==\"Flood\")tempPowerTech=555;");
code("if(power==\"Flood Weak\")tempPowerTech=556;");
code("if(power==\"Forest Fire\")tempPowerTech=248;");
code("if(power==\"Forest Fire SPC\")tempPowerTech=594;");
code("if(power==\"Frost\")tempPowerTech=57;");
code("if(power==\"Gaia Forest\")tempPowerTech=418;");
code("if(power==\"Gaia Forest SPC\")tempPowerTech=505;");
code("if(power==\"Geyser\")tempPowerTech=552;");
code("if(power==\"Goatunheim\")tempPowerTech=391;");
code("if(power==\"Great Hunt\")tempPowerTech=146;");
code("if(power==\"Healing Spring\")tempPowerTech=228;");
code("if(power==\"Heroize\")tempPowerTech=439;");
code("if(power==\"Hesperides\")tempPowerTech=436;");
code("if(power==\"Implode\")tempPowerTech=442;");
code("if(power==\"Inferno\")tempPowerTech=558;");
code("if(power==\"Journey\")tempPowerTech=548;");
code("if(power==\"Lightning Storm\")tempPowerTech=42;");
code("if(power==\"Locust Swarm\")tempPowerTech=43;");
code("if(power==\"Meteor\")tempPowerTech=61;");
code("if(power==\"Nidhogg\")tempPowerTech=235;");
code("if(power==\"Pestilence\")tempPowerTech=249;");
code("if(power==\"Plenty\")tempPowerTech=236;");
code("if(power==\"Prosperity\")tempPowerTech=211;");
code("if(power==\"Ragnorok\")tempPowerTech=234;");
code("if(power==\"Rain\")tempPowerTech=156;");
code("if(power==\"Recreation\")tempPowerTech=543;");
code("if(power==\"Restoration\")tempPowerTech=134;");
code("if(power==\"Reverse Time\")tempPowerTech=406;");
code("if(power==\"Reverse Wonder\")tempPowerTech=434;");
code("if(power==\"Sandstorm\")tempPowerTech=231;");
code("if(power==\"Seed of Gaia\")tempPowerTech=485;");
code("if(power==\"Sentinel\")tempPowerTech=230;");
code("if(power==\"Serpents\")tempPowerTech=226;");
code("if(power==\"Skeleton Power\")tempPowerTech=129;");
code("if(power==\"Snow Storm\")tempPowerTech=172;");
code("if(power==\"Son of Osiris\")tempPowerTech=237;");
code("if(power==\"SPCLightning Storm\")tempPowerTech=468;");
code("if(power==\"SPCMeteor\")tempPowerTech=334;");
code("if(power==\"Spiders\")tempPowerTech=438;");
code("if(power==\"Spy\")tempPowerTech=222;");
code("if(power==\"Tartarian Gate\")tempPowerTech=419;");
code("if(power==\"Timber Harvest\")tempPowerTech=545;");
code("if(power==\"TitanGate\")tempPowerTech=444;");
code("if(power==\"Tornado\")tempPowerTech=44;");
code("if(power==\"Tornado XP05\")tempPowerTech=458;");
code("if(power==\"Traitors\")tempPowerTech=408;");
code("if(power==\"Traitors SPC\")tempPowerTech=491;");
code("if(power==\"Tremor\")tempPowerTech=414;");
code("if(power==\"Tsunami\")tempPowerTech=598;");
code("if(power==\"Undermine\")tempPowerTech=152;");
code("if(power==\"Underworld Passage\")tempPowerTech=133;");
code("if(power==\"Uproot\")tempPowerTech=553;");
code("if(power==\"Uproot SPC\")tempPowerTech=554;");
code("if(power==\"Vision\")tempPowerTech=220;");
code("if(power==\"Volcano\")tempPowerTech=410;");
code("if(power==\"Vortex\")tempPowerTech=431;");
code("if(power==\"Walking Berry Bushes\")tempPowerTech=389;");
code("if(power==\"Walking Woods\")tempPowerTech=233;");
code("if(power==\"Water Damage\")tempPowerTech=615;");
code("if(power==\"Well of Urd\")tempPowerTech=366;");
code("if(power==\"Year of the Goat\")tempPowerTech=544;");
code("if(tempPowerTech>=0){");
code("if(trGetGPData(p, 0, 0) == tempPowerTech)tempPosition=0;");
code("if(trGetGPData(p, 0, 1) == tempPowerTech)tempPosition=1;");
code("if(trGetGPData(p, 0, 2) == tempPowerTech)tempPosition=2;");
code("if(trGetGPData(p, 0, 3) == tempPowerTech)tempPosition=3;");
code("if(trGetGPData(p, 0, 4) == tempPowerTech)tempPosition=4;");
code("if(tempPosition>=0){");
code("if(false){");
code("trSetGPData(p, 5, tempPosition, time);");
code("} else {");
code("trSetGPData(p, 5, tempPosition, time - trGetGPData(p, 5, tempPosition));");
code("}");
code("}");
code("}");
code("}");


code("void refreshPassability(){");
code("trPaintTerrain(0, 0, 0, 0, trGetTerrainType(0, 0), trGetTerrainSubType(0, 0), true);");
code("}");

code("void characterDialog(string character = \"\", string message = \"\", string portrait = \"\"){");
code("trSoundPlayFN(\"\",\"1\",-1,\"\"+character+\":\"+message,portrait);");
code("}");

code("void modifyProtounitAbsolute(string protounit = \"\", int p = 0, int field = 0, float value = 0.0){");
code("if(field == 6){");
code("trModifyProtounit(protounit, p, field, -9999999999999999999.0);");
code("trModifyProtounit(protounit, p, field, value);");
code("} else if(field == 5 || field == 7 || field == 10 || field == 13){");
code("trModifyProtounit(protounit, p, field, 2147483648.0);");
code("trModifyProtounit(protounit, p, field, 2147483648.0);");
code("trModifyProtounit(protounit, p, field, value);");
code("} else {");
code("trModifyProtounit(protounit, p, field, 9999999999999999999.0);");
code("trModifyProtounit(protounit, p, field, -9999999999999999999.0);");
code("trModifyProtounit(protounit, p, field, value);");
code("}");
code("}");

code("void paintShopSquare(int posX = 0, int PosZ = 0, string terrain = \"\"){");
code("int terrainType = getTerrainType(terrain);");
code("int terrainSubType = getTerrainSubType(terrain);");
code("trPaintTerrain(posX+1, PosZ+1, posX+1, PosZ+1, 0, 80, false);");
code("trPaintTerrain(posX+1, PosZ, posX+1, PosZ, 0, 74, false);");
code("trPaintTerrain(posX+1, PosZ-1, posX+1, PosZ-1, 0, 81, false);");
code("trPaintTerrain(posX, PosZ-1, posX, PosZ-1, 0, 75, false);");
code("trPaintTerrain(posX-1, PosZ-1, posX-1, PosZ-1, 0, 82, false);");
code("trPaintTerrain(posX-1, PosZ, posX-1, PosZ, 0, 74, false);");
code("trPaintTerrain(posX-1, PosZ+1, posX-1, PosZ+1, 0, 83, false);");
code("trPaintTerrain(posX, PosZ+1, posX, PosZ+1, 0, 75, false);");
code("trPaintTerrain(posX, PosZ, posX, PosZ, terrainType, terrainSubType, false);");
code("}");



code("void CounterShow(int xx = 0){");
code("string colourString = \"<color={PlayerColor(\"+xx+\")}>\";");
code("string incomeString = \"Income: \"+1*trQuestVarGet(\"P\"+xx+\"Income\")+\" | Lives: \"+1*trQuestVarGet(\"P\"+xx+\"Lives\");");
code("string LivesString = \"\"+1*trQuestVarGet(\"P\"+xx+\"Lives\")+\" | \"+1*trQuestVarGet(\"P\"+xx+\"Lives\");");
code("string iconString = \"<icon=(16)(icons/icon resource wood)>\";");
code("trSetCounterDisplay(colourString+incomeString);");
code("}");

code("void ColouredTimer(int c = 0, string text = \"\", int time = 0, string name = \"countdown\", int eventID = -1){");
code("string colourString = \"<color={PlayerColor(\"+c+\")}>\";");
code("trCounterAddTime(name, time, 0, colourString + text, eventID);");
code("}");

code("void ColouredIconTimer(int c = 0, string icon =\"\", string text = \"\", int time = 0,");
code("string name = \"countdown\", int eventID = -1){");
code("string colourString = \"<color={PlayerColor(\"+c+\")}>\";");
code("string iconString = \"<icon=(20)(\"+icon+\")>\";");
code("trCounterAddTime(name, time, 0, colourString + iconString + text, eventID);");
code("}");

code("void OverlayTextPlayerColor(int p = 0){");
code("if(p == 0)trOverlayTextColour(153, 102, 0);");
code("if(p == 1)trOverlayTextColour(50, 50, 255);");
code("if(p == 2)trOverlayTextColour(255, 50, 50);");
code("if(p == 3)trOverlayTextColour(0, 150, 0);");
code("if(p == 4)trOverlayTextColour(50, 235, 255);");
code("if(p == 5)trOverlayTextColour(223, 52, 238);");
code("if(p == 6)trOverlayTextColour(255, 255, 0);");
code("if(p == 7)trOverlayTextColour(255, 102, 0);");
code("if(p == 8)trOverlayTextColour(128, 0, 64);");
code("if(p == 9)trOverlayTextColour(50, 255, 50);");
code("if(p == 10)trOverlayTextColour(179, 251, 186);");
code("if(p == 11)trOverlayTextColour(80, 80, 80);");
code("if(p == 12)trOverlayTextColour(255, 0, 102);");
code("}");

code("void UnitCreate(int player = 0, string protounitname = \"\", int xx = 0, int zz = 0, int xheadingx = 0){");
code("trQuestVarSet(\"CreatingU\", trGetNextUnitScenarioNameNumber());");
code("trArmyDispatch(\"0,0\", \"Dwarf\", 1, xx, 0, zz, xheadingx, true);");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"CreatingU\"));");
code("trMutateSelected(kbGetProtoUnitID(\"\"+protounitname+\"\"));");
code("}");

code("void FloatingUnit(string protounitname=\"\", int xx = 0, int yy = 0, int zz = 0, int xheadingx = 0,");
code("float scalex = 1, float scaley = 1, float scalez = 1){");
code("");
code("trQuestVarSet(\"BuildID\", trQuestVarGet(\"BuildID\") + 1);");
code("trQuestVarSet(\"QVHero\"+(1*trQuestVarGet(\"BuildID\"))+\"\", trGetNextUnitScenarioNameNumber());");
code("trQuestVarSet(\"QVHero\", trGetNextUnitScenarioNameNumber());");
code("trArmyDispatch(\"0,0\", \"Dwarf\", 1, xx, yy, zz, xheadingx, true);");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVHero\"));");
code("trUnitChangeProtoUnit(\"Amanra\");");
code("trQuestVarSet(\"QVRelic\"+(1*trQuestVarGet(\"BuildID\"))+\"\", trGetNextUnitScenarioNameNumber());");
code("trQuestVarSet(\"QVRelic\", trGetNextUnitScenarioNameNumber());");
code("trArmyDispatch(\"0,0\", \"Relic\", 1, xx, yy, zz, trQuestVarGet(\"Heading\"+(1*trQuestVarGet(\"Build\"))+\"\"), true);");
code("trQuestVarCopy(\"QVHero\", \"QVHero\"+(1*trQuestVarGet(\"BuildID\"))+\"\");");
code("trVectorQuestVarSet(\"V1\", kbGetBlockPosition(\"0\"));");
code("trVectorQuestVarSet(\"V1\", xsVectorSet(trVectorQuestVarGetX(\"V1\") + xx,");
code("yy,trVectorQuestVarGetZ(\"V1\") + zz));");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVRelic\"));");
code("trImmediateUnitGarrison(\"\"+(1*trQuestVarGet(\"QVHero\"))+\"\");");
code("trMutateSelected(kbGetProtoUnitID(\"\"+protounitname+\"\"));");
code("trUnitSelectClear();");
code("");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVHero\"), true);");
code("trMutateSelected(kbGetProtoUnitID(\"Wadjet Spit\"));");
code("trQuestVarSet(\"Build\", trQuestVarGet(\"Build\") - 1);");
code("trUnitTeleport(trVectorQuestVarGetX(\"V1\"),trVectorQuestVarGetY(\"V1\"),trVectorQuestVarGetZ(\"V1\"));");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVRelic\"), true);");
code("trSetSelectedScale(scalex, scaley, scalez);");
code("trUnitSetAnimationPath(\"1,0,0,0,0\");");
code("}");

code("void FloatingUnitAnim(string protounitname=\"\", int xx = 0, int yy = 0, int zz = 0, int xheadingx = 0,");
code("float scalex = 1, float scaley = 1, float scalez = 1, string anim=\"0,0,0,0,0\"){");
code("trArmyDispatch(\"0,0\", \"Revealer\", 1, xx, yy, zz, xheadingx, true);");
code("trQuestVarSet(\"BuildID\", trQuestVarGet(\"BuildID\") + 1);");
code("trQuestVarSet(\"QVHero\"+(1*trQuestVarGet(\"BuildID\"))+\"\", trGetNextUnitScenarioNameNumber());");
code("trQuestVarSet(\"QVHero\", trGetNextUnitScenarioNameNumber());");
code("trArmyDispatch(\"0,0\", \"Dwarf\", 1, xx, yy, zz, xheadingx, true);");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVHero\"));");
code("trUnitChangeProtoUnit(\"Amanra\");");
code("trQuestVarSet(\"QVRelic\"+(1*trQuestVarGet(\"BuildID\"))+\"\", trGetNextUnitScenarioNameNumber());");
code("trQuestVarSet(\"QVRelic\", trGetNextUnitScenarioNameNumber());");
code("trArmyDispatch(\"0,0\", \"Relic\", 1, xx, yy, zz, trQuestVarGet(\"Heading\"+(1*trQuestVarGet(\"Build\"))+\"\"), true);");
code("trQuestVarCopy(\"QVHero\", \"QVHero\"+(1*trQuestVarGet(\"BuildID\"))+\"\");");
code("trVectorQuestVarSet(\"V1\", kbGetBlockPosition(\"0\"));");
code("trVectorQuestVarSet(\"V1\", xsVectorSet(trVectorQuestVarGetX(\"V1\") + xx,");
code("yy,trVectorQuestVarGetZ(\"V1\") + zz));");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVRelic\"));");
code("trImmediateUnitGarrison(\"\"+(1*trQuestVarGet(\"QVHero\"))+\"\");");
code("trMutateSelected(kbGetProtoUnitID(\"\"+protounitname+\"\"));");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVHero\"), true);");
code("trMutateSelected(kbGetProtoUnitID(\"Wadjet Spit\"));");
code("trQuestVarSet(\"Build\", trQuestVarGet(\"Build\") - 1);");
code("trUnitTeleport(trVectorQuestVarGetX(\"V1\"),trVectorQuestVarGetY(\"V1\"),trVectorQuestVarGetZ(\"V1\"));");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVRelic\"), true);");
code("trSetSelectedScale(scalex, scaley, scalez);");
code("trUnitSetAnimationPath(\"\"+anim+\"\");");
code("}");

code("void FloatingUnitAnimNoLOS(string protounitname=\"\", int xx = 0, int yy = 0, int zz = 0, int xheadingx = 0,");
code("float scalex = 1, float scaley = 1, float scalez = 1, string anim=\"0,0,0,0,0\"){");
code("trQuestVarSet(\"BuildID\", trQuestVarGet(\"BuildID\") + 1);");
code("trQuestVarSet(\"QVHero\"+(1*trQuestVarGet(\"BuildID\"))+\"\", trGetNextUnitScenarioNameNumber());");
code("trQuestVarSet(\"QVHero\", trGetNextUnitScenarioNameNumber());");
code("trArmyDispatch(\"0,0\", \"Flying Medic\", 1, xx, yy, zz, xheadingx, true);");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVHero\"));");
code("trUnitChangeProtoUnit(\"Amanra\");");
code("trQuestVarSet(\"QVRelic\"+(1*trQuestVarGet(\"BuildID\"))+\"\", trGetNextUnitScenarioNameNumber());");
code("trQuestVarSet(\"QVRelic\", trGetNextUnitScenarioNameNumber());");
code("trArmyDispatch(\"0,0\", \"Relic\", 1, xx, yy, zz, trQuestVarGet(\"Heading\"+(1*trQuestVarGet(\"Build\"))+\"\"), true);");
code("trQuestVarCopy(\"QVHero\", \"QVHero\"+(1*trQuestVarGet(\"BuildID\"))+\"\");");
code("trVectorQuestVarSet(\"V1\", kbGetBlockPosition(\"0\"));");
code("trVectorQuestVarSet(\"V1\", xsVectorSet(trVectorQuestVarGetX(\"V1\") + xx,");
code("yy,trVectorQuestVarGetZ(\"V1\") + zz));");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVRelic\"));");
code("trImmediateUnitGarrison(\"\"+(1*trQuestVarGet(\"QVHero\"))+\"\");");
code("trMutateSelected(kbGetProtoUnitID(\"\"+protounitname+\"\"));");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVHero\"), true);");
code("trMutateSelected(kbGetProtoUnitID(\"Wadjet Spit\"));");
code("trQuestVarSet(\"Build\", trQuestVarGet(\"Build\") - 1);");
code("trUnitTeleport(trVectorQuestVarGetX(\"V1\"),trVectorQuestVarGetY(\"V1\"),trVectorQuestVarGetZ(\"V1\"));");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVRelic\"), true);");
code("trSetSelectedScale(scalex, scaley, scalez);");
code("trUnitSetAnimationPath(\"\"+anim+\"\");");
code("}");

code("void FloatingUnitAnimCiv(string protounitname=\"\", int xx = 0, int yy = 0, int zz = 0, int xheadingx = 0,");
code("float scalex = 1, float scaley = 1, float scalez = 1, string anim=\"0,0,0,0,0\"){");
code("trArmyDispatch(\"0,0\", \"Revealer\", 1, xx, yy, zz, xheadingx, true);");
code("trQuestVarSet(\"BuildID\", trQuestVarGet(\"BuildID\") + 1);");
code("trQuestVarSet(\"QVHero\"+(1*trQuestVarGet(\"BuildID\"))+\"\", trGetNextUnitScenarioNameNumber());");
code("trQuestVarSet(\"QVHero\", trGetNextUnitScenarioNameNumber());");
code("trArmyDispatch(\"0,0\", \"Revealer\", 1, xx, yy, zz, xheadingx, true);");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVHero\"));");
code("trUnitChangeProtoUnit(\"Amanra\");");
code("trQuestVarSet(\"QVRelic\"+(1*trQuestVarGet(\"BuildID\"))+\"\", trGetNextUnitScenarioNameNumber());");
code("trQuestVarSet(\"QVRelic\", trGetNextUnitScenarioNameNumber());");
code("trArmyDispatch(\"0,0\", \"Relic\", 1, xx, yy, zz, trQuestVarGet(\"Heading\"+(1*trQuestVarGet(\"Build\"))+\"\"), true);");
code("trQuestVarCopy(\"QVHero\", \"QVHero\"+(1*trQuestVarGet(\"BuildID\"))+\"\");");
code("trVectorQuestVarSet(\"V1\", kbGetBlockPosition(\"0\"));");
code("trVectorQuestVarSet(\"V1\", xsVectorSet(trVectorQuestVarGetX(\"V1\") + xx,");
code("trVectorQuestVarGetY(\"V1\") + yy,trVectorQuestVarGetZ(\"V1\") + zz));");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVRelic\"));");
code("trImmediateUnitGarrison(\"\"+(1*trQuestVarGet(\"QVHero\"))+\"\");");
code("trMutateSelected(kbGetProtoUnitID(\"\"+protounitname+\"\"));");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVHero\"), true);");
code("trMutateSelected(kbGetProtoUnitID(\"Wadjet Spit\"));");
code("trQuestVarSet(\"Build\", trQuestVarGet(\"Build\") - 1);");
code("trUnitTeleport(trVectorQuestVarGetX(\"V1\"),trVectorQuestVarGetY(\"V1\"),trVectorQuestVarGetZ(\"V1\"));");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVRelic\"), true);");
code("trSetSelectedScale(scalex, scaley, scalez);");
code("}");

code("void FloatingUnitAnim4(string protounitname=\"\", int xx = 0, int yy = 0, int zz = 0, int xheadingx = 0,");
code("float scalex = 1, float scaley = 1, float scalez = 1, string anim=\"0,0,0,0,0\", int p = 0){");
code("trArmyDispatch(\"\"+p+\",0\", \"Revealer\", 1, xx, yy, zz, xheadingx, true);");
code("trQuestVarSet(\"BuildID\", trQuestVarGet(\"BuildID\") + 1);");
code("trQuestVarSet(\"QVHero\"+(1*trQuestVarGet(\"BuildID\"))+\"\", trGetNextUnitScenarioNameNumber());");
code("trQuestVarSet(\"QVHero\", trGetNextUnitScenarioNameNumber());");
code("trArmyDispatch(\"\"+p+\",0\", \"Flying Medic\", 1, xx, yy, zz, xheadingx, true);");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVHero\"));");
code("trUnitChangeProtoUnit(\"Amanra\");");
code("trQuestVarSet(\"QVRelic\"+(1*trQuestVarGet(\"BuildID\"))+\"\", trGetNextUnitScenarioNameNumber());");
code("trQuestVarSet(\"QVRelic\", trGetNextUnitScenarioNameNumber());");
code("trArmyDispatch(\"\"+p+\",0\", \"Relic\", 1, xx, yy, zz, trQuestVarGet(\"Heading\"+(1*trQuestVarGet(\"Build\"))+\"\"), true);");
code("trQuestVarCopy(\"QVHero\", \"QVHero\"+(1*trQuestVarGet(\"BuildID\"))+\"\");");
code("trVectorQuestVarSet(\"V1\", kbGetBlockPosition(\"0\"));");
code("trVectorQuestVarSet(\"V1\", xsVectorSet(trVectorQuestVarGetX(\"V1\") + xx,");
code("yy,trVectorQuestVarGetZ(\"V1\") + zz));");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVRelic\"));");
code("trImmediateUnitGarrison(\"\"+(1*trQuestVarGet(\"QVHero\"))+\"\");");
code("trMutateSelected(kbGetProtoUnitID(\"\"+protounitname+\"\"));");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVHero\"), true);");
code("trMutateSelected(kbGetProtoUnitID(\"Wadjet Spit\"));");
code("trQuestVarSet(\"Build\", trQuestVarGet(\"Build\") - 1);");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVRelic\"), true);");
code("trSetSelectedScale(scalex, scaley, scalez);");
code("trUnitSetAnimationPath(\"\"+anim+\"\");");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVHero\"), true);");
code("trUnitTeleport(trVectorQuestVarGetX(\"V1\"),yy,trVectorQuestVarGetZ(\"V1\"));");
code("}");

code("void FloatingUnitAnim5(string protounitname=\"\", int xx = 0, int yy = 0, int zz = 0, int xheadingx = 0,");
code("float scalex = 1, float scaley = 1, float scalez = 1, string anim=\"0,0,0,0,0\", int p = 0){");
code("trArmyDispatch(\"\"+p+\",0\", \"Revealer\", 1, xx, yy, zz, xheadingx, true);");
code("trQuestVarSet(\"BuildID\", trQuestVarGet(\"BuildID\") + 1);");
code("trQuestVarSet(\"QVHero\"+(1*trQuestVarGet(\"BuildID\"))+\"\", trGetNextUnitScenarioNameNumber());");
code("trQuestVarSet(\"QVHero\", trGetNextUnitScenarioNameNumber());");
code("trArmyDispatch(\"\"+p+\",0\", \"Flying Medic\", 1, xx, yy, zz, xheadingx, true);");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVHero\"));");
code("trUnitChangeProtoUnit(\"Amanra\");");
code("trQuestVarSet(\"QVRelic\"+(1*trQuestVarGet(\"BuildID\"))+\"\", trGetNextUnitScenarioNameNumber());");
code("trQuestVarSet(\"QVRelic\", trGetNextUnitScenarioNameNumber());");
code("trArmyDispatch(\"\"+p+\",0\", \"Relic\", 1, xx, yy, zz, trQuestVarGet(\"Heading\"+(1*trQuestVarGet(\"Build\"))+\"\"), true);");
code("trQuestVarCopy(\"QVHero\", \"QVHero\"+(1*trQuestVarGet(\"BuildID\"))+\"\");");
code("trVectorQuestVarSet(\"V1\", xsVectorSet(xx, yy, zz));");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVRelic\"));");
code("trImmediateUnitGarrison(\"\"+(1*trQuestVarGet(\"QVHero\"))+\"\");");
code("trMutateSelected(kbGetProtoUnitID(\"\"+protounitname+\"\"));");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVHero\"), true);");
code("trMutateSelected(kbGetProtoUnitID(\"Wadjet Spit\"));");
code("trQuestVarSet(\"Build\", trQuestVarGet(\"Build\") - 1);");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVRelic\"), true);");
code("trSetSelectedScale(scalex, scaley, scalez);");
code("trUnitSetAnimationPath(\"\"+anim+\"\");");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVHero\"), true);");
code("trUnitTeleport(trVectorQuestVarGetX(\"V1\"),trVectorQuestVarGetY(\"V1\"),trVectorQuestVarGetZ(\"V1\"));");
code("}");

code("void FloatingUnitAnim2(string protounitname=\"\", int xx = 0, int yy = 0, int zz = 0, int xheadingx = 0,");
code("float scalex = 1, float scaley = 1, float scalez = 1, string anim=\"0,0,0,0,0\"){");
code("trArmyDispatch(\"0,0\", \"Revealer\", 1, xx, yy, zz, xheadingx, true);");
code("trQuestVarSet(\"BuildID\", trQuestVarGet(\"BuildID\") + 1);");
code("trQuestVarSet(\"QVHero\"+(1*trQuestVarGet(\"BuildID\"))+\"\", trGetNextUnitScenarioNameNumber());");
code("trQuestVarSet(\"QVHero\", trGetNextUnitScenarioNameNumber());");
code("trArmyDispatch(\"0,0\", \"Flying Medic\", 1, 50, yy, 50, xheadingx, true);");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVHero\"));");
code("trUnitChangeProtoUnit(\"Amanra\");");
code("trQuestVarSet(\"QVRelic\"+(1*trQuestVarGet(\"BuildID\"))+\"\", trGetNextUnitScenarioNameNumber());");
code("trQuestVarSet(\"QVRelic\", trGetNextUnitScenarioNameNumber());");
code("trArmyDispatch(\"0,0\", \"Relic\", 1, 50, yy, 50, trQuestVarGet(\"Heading\"+(1*trQuestVarGet(\"Build\"))+\"\"), true);");
code("trQuestVarCopy(\"QVHero\", \"QVHero\"+(1*trQuestVarGet(\"BuildID\"))+\"\");");
code("trVectorQuestVarSet(\"V1\", kbGetBlockPosition(\"0\"));");
code("trVectorQuestVarSet(\"V1\", xsVectorSet(trVectorQuestVarGetX(\"V1\") + xx,");
code("trVectorQuestVarGetY(\"V1\") + yy,trVectorQuestVarGetZ(\"V1\") + zz));");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVRelic\"));");
code("trImmediateUnitGarrison(\"\"+(1*trQuestVarGet(\"QVHero\"))+\"\");");
code("trMutateSelected(kbGetProtoUnitID(\"\"+protounitname+\"\"));");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVHero\"), true);");
code("trMutateSelected(kbGetProtoUnitID(\"Wadjet Spit\"));");
code("trQuestVarSet(\"Build\", trQuestVarGet(\"Build\") - 1);");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVRelic\"), true);");
code("trSetSelectedScale(scalex, scaley, scalez);");
code("trUnitSetAnimationPath(\"\"+anim+\"\");");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVHero\"), true);");
code("trUnitTeleport(trVectorQuestVarGetX(\"V1\"),trVectorQuestVarGetY(\"V1\"),trVectorQuestVarGetZ(\"V1\"));");
code("}");

code("void FloatingUnitAnimIdle(string protounitname=\"\", int xx = 0, int yy = 0, int zz = 0, int xheadingx = 0,");
code("float scalex = 1, float scaley = 1, float scalez = 1, string anim=\"0,0,0,0,0\", int animtype = 2){");
code("trArmyDispatch(\"0,0\", \"Revealer\", 1, xx, yy, zz, xheadingx, true);");
code("trQuestVarSet(\"BuildID\", trQuestVarGet(\"BuildID\") + 1);");
code("trQuestVarSet(\"QVHero\"+(1*trQuestVarGet(\"BuildID\"))+\"\", trGetNextUnitScenarioNameNumber());");
code("trQuestVarSet(\"QVHero\", trGetNextUnitScenarioNameNumber());");
code("trArmyDispatch(\"0,0\", \"Flying Medic\", 1, xx, yy, zz, xheadingx, true);");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVHero\"));");
code("trUnitChangeProtoUnit(\"Amanra\");");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVHero\"));");
code("trUnitOverrideAnimation(animtype, 0, true, true, -1, 0);");
code("trQuestVarSet(\"QVRelic\"+(1*trQuestVarGet(\"BuildID\"))+\"\", trGetNextUnitScenarioNameNumber());");
code("trQuestVarSet(\"QVRelic\", trGetNextUnitScenarioNameNumber());");
code("trArmyDispatch(\"0,0\", \"Ajax\", 1, xx, yy, zz, trQuestVarGet(\"Heading\"+(1*trQuestVarGet(\"Build\"))+\"\"), true);");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVRelic\"));");
code("trUnitOverrideAnimation(animtype, 0, true, true, -1, 0);");
code("trMutateSelected(kbGetProtoUnitID(\"Relic\"));");
code("trQuestVarCopy(\"QVHero\", \"QVHero\"+(1*trQuestVarGet(\"BuildID\"))+\"\");");
code("trVectorQuestVarSet(\"V1\", kbGetBlockPosition(\"0\"));");
code("trVectorQuestVarSet(\"V1\", xsVectorSet(trVectorQuestVarGetX(\"V1\") + xx,");
code("yy,trVectorQuestVarGetZ(\"V1\") + zz));");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVRelic\"));");
code("trImmediateUnitGarrison(\"\"+(1*trQuestVarGet(\"QVHero\"))+\"\");");
code("trMutateSelected(kbGetProtoUnitID(\"\"+protounitname+\"\"));");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVHero\"), true);");
code("trMutateSelected(kbGetProtoUnitID(\"Wadjet Spit\"));");
code("trQuestVarSet(\"Build\", trQuestVarGet(\"Build\") - 1);");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVRelic\"), true);");
code("trSetSelectedScale(scalex, scaley, scalez);");
code("trUnitSetAnimationPath(\"\"+anim+\"\");");
code("trUnitSelectClear();");
code("trUnitSelect(\"\"+1*trQuestVarGet(\"QVHero\"), true);");
code("trUnitTeleport(trVectorQuestVarGetX(\"V1\"),trVectorQuestVarGetY(\"V1\"),trVectorQuestVarGetZ(\"V1\"));");
code("}");


code("void activateFlagTimerEnd(int asdf = 1) {");
code("xsEnableRule(\"FlagTimerEnd\");");
code("}");

code("void activatestartcine(int asdf = 2) {");
code("xsEnableRule(\"startcine\");");
code("}");
code("void activatecustomcontent(int asdf = 3) {");
code("xsEnableRule(\"customcontent\");");
code("}");
code("void activateShopLevel2(int asdf = 4) {");
code("xsEnableRule(\"ShopLevel2\");");
code("}");
code("void activateShopLevel3(int asdf = 5) {");
code("xsEnableRule(\"ShopLevel3\");");
code("}");
code("void activateShopLevel4(int asdf = 6) {");
code("xsEnableRule(\"ShopLevel4\");");
code("}");
code("void activateShopLevel5(int asdf = 7) {");
code("xsEnableRule(\"ShopLevel5\");");
code("}");
code("void activateShopLevel6(int asdf = 8) {");
code("xsEnableRule(\"ShopLevel6\");");
code("}");
code("void activateShopLevel7(int asdf = 9) {");
code("xsEnableRule(\"ShopLevel7\");");
code("}");
code("void activateShopLevel8(int asdf = 10) {");
code("xsEnableRule(\"ShopLevel8\");");
code("}");




code("void paintTreesSlow(string terrain = \"\", string tree = \"\", int xmin = 0, int zmin = 0, int xmax = 0, int zmax = 0){");
code("int terrainType = getTerrainType(terrain);");
code("int terrainSubType = getTerrainSubType(terrain);");
code("trPaintTerrain(xmin, zmin, xmax, zmax, terrainType, terrainSubType, false);");
code("for (x=xmax; >= xmin) {");
code("for (z=zmax; >= zmin) {");
code("trQuestVarSetFromRand(\"heading\", 0, 359, true);");
code("trArmyDispatch(\"0,0\", \"Victory Marker\", 1, x*2, 5.00, z*2, 1*trQuestVarGet(\"Heading\"), false);");
code("}");
code("}");
code("trUnitSelectClear();");
code("trUnitSelect(\"0\");");
code("trUnitChangeInArea(0, 0, \"Victory Marker\", tree, 999.0);");
code("}");

code("void trQuestVarModify(string QV = \"\", string Operator = \"\", int number = 0){");
code("if(Operator == \"+\"){");
code("trQuestVarSet(QV, 1*trQuestVarGet(QV) + number);");
code("}");
code("else if(Operator == \"-\"){");
code("trQuestVarSet(QV, 1*trQuestVarGet(QV) - number);");
code("}");
code("else if(Operator == \"*\"){");
code("trQuestVarSet(QV, 1*trQuestVarGet(QV) * number);");
code("}");
code("else if(Operator == \"/\"){");
code("trQuestVarSet(QV, 1*trQuestVarGet(QV) / number);");
code("}");
code("}");
code("void trPaintTerrainCircle(int posX = 0, int PosZ = 0, int irad = 0, int type = 0, int subtype = 0){");
code("for(tempType = -1; > 1){}");
code("for(tempSubType = -1; > 1){}");
code("for(tempMinX = 0; > 1){}");
code("for(tempMinZ = 0; > 1){}");
code("for(tempMaxX = 0; > 1){}");
code("for(tempMaxZ = 0; > 1){}");
code("for(tempX = 0; > 1){}");
code("for(tempZ = 0; > 1){}");
code("for(tempRadiusCheck = 0; > 1){}");
code("for(tempOldContextPlayer = 0; > 1){}");
code("tempMinX = xsMax(0.0 - posX, -1*irad );");
code("tempMinZ = xsMax(0.0 - PosZ, -1*irad );");
code("tempOldContextPlayer = xsGetContextPlayer();");
code("xsSetContextPlayer(0);");
code("tempMaxX = xsMin(kbGetMapXSize() / 2 - posX - 1, irad );");
code("tempMaxZ = xsMin(kbGetMapZSize() / 2 - PosZ - 1, irad );");
code("xsSetContextPlayer(tempOldContextPlayer);");
code("tempRadiusCheck = irad  * irad  + irad ;");
code("for(tempZ = tempMaxZ; >= tempMinZ){");
code("for(tempX = tempMaxX; >= tempMinX){");
code("if(tempRadiusCheck > (tempX*tempX + tempZ*tempZ)){");
code("trPaintTerrain(tempX + posX, tempZ + PosZ, tempX + posX, tempZ + PosZ, type, subtype, false);");
code("}");
code("}");
code("}");
code("}");

code("void trPaintTerrainCircleOutline(int posX = 0, int PosZ = 0, int irad = 0, int type = 0, int subtype = 0){");
code("for(tempType = -1; > 1){}");
code("for(tempSubType = -1; > 1){}");
code("for(tempMinX = 0; > 1){}");
code("for(tempMinZ = 0; > 1){}");
code("for(tempMaxX = 0; > 1){}");
code("for(tempMaxZ = 0; > 1){}");
code("for(tempX = 0; > 1){}");
code("for(tempZ = 0; > 1){}");
code("for(tempRadiusCheck = 0; > 1){}");
code("for(tempOldContextPlayer = 0; > 1){}");
code("tempMinX = xsMax(0.0 - posX, -1*irad );");
code("tempMinZ = xsMax(0.0 - PosZ, -1*irad );");
code("tempOldContextPlayer = xsGetContextPlayer();");
code("xsSetContextPlayer(0);");
code("tempMaxX = xsMin(kbGetMapXSize() / 2 - posX - 1, irad );");
code("tempMaxZ = xsMin(kbGetMapZSize() / 2 - PosZ - 1, irad );");
code("xsSetContextPlayer(tempOldContextPlayer);");
code("tempRadiusCheck = irad  * irad  + irad ;");
code("for(tempZ = tempMaxZ; >= tempMinZ){");
code("for(tempX = tempMaxX; >= tempMinX){");
code("if(tempRadiusCheck <= (tempX*tempX + tempZ*tempZ)){");
code("trPaintTerrain(tempX + posX, tempZ + PosZ, tempX + posX, tempZ + PosZ, type, subtype, false);");
code("}");
code("}");
code("}");
code("}");

code("");
code("void replaceCircle(int posX = 0, int PosZ = 0, int radius = 0, string oldTerrain = \"\", string newTerrain = \"\"){");
code("int oldTerrainType = getTerrainType(oldTerrain);");
code("int oldTerrainSubType = getTerrainSubType(oldTerrain);");
code("int newTerrainType = getTerrainType(newTerrain);");
code("int newTerrainSubType = getTerrainSubType(newTerrain);");
code("int tempMinX = xsMax(0.0 - posX, 0.0 - radius);");
code("int tempMinZ = xsMax(0.0 - PosZ, 0.0 - radius);");
code("int tempMaxX = xsMin(200 - posX, radius);");
code("int tempMaxZ = xsMin(200 - PosZ, radius);");
code("int tempRadiusCheck = radius * radius + radius;");
code("for(tempZ = tempMaxZ; >= tempMinZ){");
code("for(tempX = tempMaxX; >= tempMinX){");
code("if(tempRadiusCheck >= (tempX*tempX + tempZ*tempZ)){");
code("int terrainType = trGetTerrainType(tempX + posX, tempZ + PosZ);");
code("int terrainSubType = trGetTerrainSubType(tempX + posX, tempZ + PosZ);");
code("if(terrainType == oldTerrainType && terrainSubType == oldTerrainSubType){");
code("trPaintTerrain(tempX + posX, tempZ + PosZ, tempX + posX, tempZ + PosZ, newTerrainType, newTerrainSubType, false);");
code("}");
code("}");
code("}");
code("}");
code("}");

code("void trPaintElevationCircle(int PosX = 0, int PosZ = 0, int Rad = 0, int Height = 0){");
code("for(tempMinX = 0; > 1){}");
code("for(tempMinZ = 0; > 1){}");
code("for(tempMaxX = 0; > 1){}");
code("for(tempMaxZ = 0; > 1){}");
code("for(tempRadiusCheck = 0; > 1){}");
code("for(tempLocX = 0; > 1){}");
code("for(tempLocZ = 0; > 1){}");
code("for(tempOldContextPlayer = 0; > 1){}");
code("tempMinX = xsMax(0.0 - PosX, -1*Rad);");
code("tempMinZ = xsMax(0.0 - PosZ, -1*Rad);");
code("tempOldContextPlayer = xsGetContextPlayer();");
code("xsSetContextPlayer(0);");
code("tempMaxX = xsMin(kbGetMapXSize() / 2 - PosX, Rad);");
code("tempMaxZ = xsMin(kbGetMapZSize() / 2 - PosZ, Rad);");
code("xsSetContextPlayer(tempOldContextPlayer);");
code("tempRadiusCheck = Rad * Rad + Rad;");
code("if(false){");
code("for(tempZ = tempMaxZ; >= tempMinZ){");
code("for(tempX = tempMaxX; >= tempMinX){");
code("if(tempRadiusCheck > (tempX*tempX + tempZ*tempZ)){");
code("tempLocX = tempX + PosX;");
code("tempLocZ = tempZ + PosZ;");
code("trChangeTerrainHeight(tempLocX, tempLocZ, tempLocX, tempLocZ, trGetTerrainHeight(tempLocX, tempLocZ) + Height, false);");
code("}");
code("}");
code("}");
code("} else {");
code("for(tempZ = tempMaxZ; >= tempMinZ){");
code("for(tempX = tempMaxX; >= tempMinX){");
code("if(tempRadiusCheck >= (tempX*tempX + tempZ*tempZ)){");
code("tempLocX = tempX + PosX;");
code("tempLocZ = tempZ + PosZ;");
code("trChangeTerrainHeight(tempLocX, tempLocZ, tempLocX, tempLocZ, Height, false);");
code("}");
code("}");
code("}");
code("}");
code("}");

code("void CTFPaintBase(float PosX = 0, float PosZ = 0){");
code("trPaintTerrainCircle(PosX/2+7,PosZ/2+8,10,2,13);");
code("trPaintElevationCircle(PosX/2+7,PosZ/2+7,11,5);");
code("}");

code("void CTFBuildBase(int p = 1, float PosX = 0, float PosZ = 0){");
code("trQuestVarSet(\"Base\", trGetNextUnitScenarioNameNumber());");

code("trVectorQuestVarSet(\"P\"+p+\"Base\", xsVectorSet(PosX+15, 5, PosZ+15));");
code("");
code("trArmyDispatch(\"\"+p+\",0\", \"Victory Marker\", 1, PosX+14, 0, PosZ+15, 0, false);");
code("trArmyDispatch(\"\"+p+\",0\", \"Victory Marker\", 1, PosX, 0, PosZ+10, 0, false);");
code("trArmyDispatch(\"\"+p+\",0\", \"Victory Marker\", 1, PosX, 0, PosZ+15, 90, false);");
code("trArmyDispatch(\"\"+p+\",0\", \"Victory Marker\", 1, PosX, 0, PosZ+20, 0, false);");

code("trArmyDispatch(\"\"+p+\",0\", \"Victory Marker\", 1, PosX+4, 0, PosZ+24, 135, false);");
code("trArmyDispatch(\"\"+p+\",0\", \"Victory Marker\", 1, PosX+8, 0, PosZ+28, 0, false);");

code("trArmyDispatch(\"\"+p+\",0\", \"Victory Marker\", 1, PosX+13, 0, PosZ+28, 180, false);");
code("trArmyDispatch(\"\"+p+\",0\", \"Victory Marker\", 1, PosX+18, 0, PosZ+28, 0, false);");

code("trArmyDispatch(\"\"+p+\",0\", \"Victory Marker\", 1, PosX+22, 0, PosZ+24, 225, false);");
code("trArmyDispatch(\"\"+p+\",0\", \"Victory Marker\", 1, PosX+26, 0, PosZ+20, 0, false);");


code("trArmyDispatch(\"\"+p+\",0\", \"Victory Marker\", 1, PosX+26, 0, PosZ+15, 270, false);");
code("trArmyDispatch(\"\"+p+\",0\", \"Victory Marker\", 1, PosX+26, 0, PosZ+10, 0, false);");

code("trArmyDispatch(\"\"+p+\",0\", \"Victory Marker\", 1, PosX+22, 0, PosZ+6, 315, false);");
code("");
code("trArmyDispatch(\"\"+p+\",0\", \"Victory Marker\", 1, PosX+18, 0, PosZ+2, 0, false);");

code("trArmyDispatch(\"\"+p+\",0\", \"Victory Marker\", 1, PosX+12, 0, PosZ+2, 180, false);");
code("trArmyDispatch(\"\"+p+\",0\", \"Victory Marker\", 1, PosX+8, 0, PosZ+2, 0, false);");

code("trArmyDispatch(\"\"+p+\",0\", \"Victory Marker\", 1, PosX+4, 0, PosZ+6, 45, false);");

code("");
code("trArmyDispatch(\"\"+p+\",0\", \"Victory Marker\", 1, PosX+11, 0, PosZ+14, 0, false);");
code("trArmyDispatch(\"\"+p+\",0\", \"Victory Marker\", 1, PosX+11, 0, PosZ+16, 0, false);");
code("trArmyDispatch(\"\"+p+\",0\", \"Victory Marker\", 1, PosX+13, 0, PosZ+14, 0, false);");
code("trArmyDispatch(\"\"+p+\",0\", \"Victory Marker\", 1, PosX+13, 0, PosZ+16, 0, false);");

code("yAddToDatabase(\"BaseBlocks\", \"Base\");");
code("trQuestVarModify(\"Base\", \"+\", 1);");
code("trUnitSelectClear();");
code("trUnitSelectByQV(\"Base\", false);");
code("trUnitChangeProtoUnit(\"Atlantis Wall Connector\");");
code("trVectorQuestVarSet(\"P\"+p+\"FlagSlot8\", kbGetBlockPosition(\"\"+1*trQuestVarGet(\"Base\")+\"\"));");
code("trUnitSelectClear();");
code("trQuestVarModify(\"Base\", \"+\", 1);");
code("trUnitSelectByQV(\"Base\", false);");
code("trUnitChangeProtoUnit(\"Atlantis Wall Long\");");
code("trUnitSelectClear();");
code("trQuestVarModify(\"Base\", \"+\", 1);");
code("trUnitSelectByQV(\"Base\", false);");
code("trUnitChangeProtoUnit(\"Atlantis Wall Connector\");");
code("trVectorQuestVarSet(\"P\"+p+\"FlagSlot7\", kbGetBlockPosition(\"\"+1*trQuestVarGet(\"Base\")+\"\"));");
code("trUnitSelectClear();");
code("trQuestVarModify(\"Base\", \"+\", 1);");
code("trUnitSelectByQV(\"Base\", false);");
code("trUnitChangeProtoUnit(\"Gate\");");
code("yAddToDatabase(\"Gates\", \"Base\");");
code("trUnitSelectClear();");
code("trQuestVarModify(\"Base\", \"+\", 1);");
code("trUnitSelectByQV(\"Base\", false);");
code("trUnitChangeProtoUnit(\"Atlantis Wall Connector\");");
code("trVectorQuestVarSet(\"P\"+p+\"FlagSlot6\", kbGetBlockPosition(\"\"+1*trQuestVarGet(\"Base\")+\"\"));");
code("trUnitSelectClear();");
code("trQuestVarModify(\"Base\", \"+\", 1);");
code("trUnitSelectByQV(\"Base\", false);");
code("trUnitChangeProtoUnit(\"Atlantis Wall Long\");");
code("trUnitSelectClear();");
code("trQuestVarModify(\"Base\", \"+\", 1);");
code("trUnitSelectByQV(\"Base\", false);");
code("trUnitChangeProtoUnit(\"Atlantis Wall Connector\");");
code("trVectorQuestVarSet(\"P\"+p+\"FlagSlot5\", kbGetBlockPosition(\"\"+1*trQuestVarGet(\"Base\")+\"\"));");
code("trUnitSelectClear();");
code("trQuestVarModify(\"Base\", \"+\", 1);");
code("trUnitSelectByQV(\"Base\", false);");
code("trUnitChangeProtoUnit(\"Gate\");");
code("yAddToDatabase(\"Gates\", \"Base\");");
code("trUnitSelectClear();");
code("trQuestVarModify(\"Base\", \"+\", 1);");
code("trUnitSelectByQV(\"Base\", false);");
code("trUnitChangeProtoUnit(\"Atlantis Wall Connector\");");
code("trVectorQuestVarSet(\"P\"+p+\"FlagSlot4\", kbGetBlockPosition(\"\"+1*trQuestVarGet(\"Base\")+\"\"));");
code("trUnitSelectClear();");
code("trQuestVarModify(\"Base\", \"+\", 1);");
code("trUnitSelectByQV(\"Base\", false);");
code("trUnitChangeProtoUnit(\"Atlantis Wall Long\");");
code("trUnitSelectClear();");
code("trQuestVarModify(\"Base\", \"+\", 1);");
code("trUnitSelectByQV(\"Base\", false);");
code("trUnitChangeProtoUnit(\"Atlantis Wall Connector\");");
code("trVectorQuestVarSet(\"P\"+p+\"FlagSlot3\", kbGetBlockPosition(\"\"+1*trQuestVarGet(\"Base\")+\"\"));");
code("trUnitSelectClear();");
code("trQuestVarModify(\"Base\", \"+\", 1);");
code("trUnitSelectByQV(\"Base\", false);");
code("trUnitChangeProtoUnit(\"Gate\");");
code("yAddToDatabase(\"Gates\", \"Base\");");
code("trUnitSelectClear();");
code("trQuestVarModify(\"Base\", \"+\", 1);");
code("trUnitSelectByQV(\"Base\", false);");
code("trUnitChangeProtoUnit(\"Atlantis Wall Connector\");");
code("trVectorQuestVarSet(\"P\"+p+\"FlagSlot2\", kbGetBlockPosition(\"\"+1*trQuestVarGet(\"Base\")+\"\"));");
code("trUnitSelectClear();");
code("trQuestVarModify(\"Base\", \"+\", 1);");
code("trUnitSelectByQV(\"Base\", false);");
code("trUnitChangeProtoUnit(\"Atlantis Wall Long\");");
code("trUnitSelectClear();");
code("trQuestVarModify(\"Base\", \"+\", 1);");
code("trUnitSelectByQV(\"Base\", false);");
code("trUnitChangeProtoUnit(\"Atlantis Wall Connector\");");
code("trVectorQuestVarSet(\"P\"+p+\"FlagSlot1\", kbGetBlockPosition(\"\"+1*trQuestVarGet(\"Base\")+\"\"));");
code("trUnitSelectClear();");
code("trQuestVarModify(\"Base\", \"+\", 1);");
code("trUnitSelectByQV(\"Base\", false);");
code("trUnitChangeProtoUnit(\"Gate\");");
code("yAddToDatabase(\"Gates\", \"Base\");");
code("trUnitSelectClear();");
code("trQuestVarModify(\"Base\", \"+\", 1);");
code("trUnitSelectByQV(\"Base\", false);");
code("trUnitChangeProtoUnit(\"Tower Mirror\");");
code("trUnitSelectClear();");
code("trQuestVarModify(\"Base\", \"+\", 1);");
code("trUnitSelectByQV(\"Base\", false);");
code("trUnitChangeProtoUnit(\"Tower Mirror\");");
code("trUnitSelectClear();");
code("trQuestVarModify(\"Base\", \"+\", 1);");
code("trUnitSelectByQV(\"Base\", false);");
code("trUnitChangeProtoUnit(\"Tower Mirror\");");
code("trUnitSelectClear();");
code("trQuestVarModify(\"Base\", \"+\", 1);");
code("trUnitSelectByQV(\"Base\", false);");
code("trUnitChangeProtoUnit(\"Tower Mirror\");");
code("");
code("trUnitSelectClear();");
code("trUnitSelectByID(p);");
code("trUnitTeleport(trVectorQuestVarGetX(\"P\"+p+\"Base\"),");
code("trVectorQuestVarGetY(\"P\"+p+\"Base\"),trVectorQuestVarGetZ(\"P\"+p+\"Base\"));");
code("trUnitChangeProtoUnit(\"Storage Pit\");");

code("}");

code("void setupUnitShop(int slot = 0, string displayname = \"\", string protoname = \"\",");
code("string description = \"\", int cost = 0, int limit = 0) {");
code("trStringQuestVarSet(\"unit\"+slot+\"displayname\", displayname);");
code("trStringQuestVarSet(\"unit\"+slot+\"protoname\", protoname);");
code("trStringQuestVarSet(\"unit\"+slot+\"description\", description);");
code("trQuestVarSet(\"unit\"+slot+\"cost\", cost);");
code("trQuestVarSet(\"unit\"+slot+\"limit\", limit);");
code("}");

code("void setupPowerShop(int slot = 0, string displayname = \"\", string powername = \"\",");
code("string protoname = \"\", string description = \"\", int cost = 0, int idneeded = 0) {");
code("trStringQuestVarSet(\"power\"+slot+\"displayname\", displayname);");
code("trStringQuestVarSet(\"power\"+slot+\"powername\", powername);");
code("trStringQuestVarSet(\"power\"+slot+\"protoname\", protoname);");
code("trStringQuestVarSet(\"power\"+slot+\"description\", description);");
code("trQuestVarSet(\"power\"+slot+\"cost\", cost);");
code("trQuestVarSet(\"power\"+slot+\"id\", idneeded);");
code("}");

code("void playSoundCustom(string BasesoundName = \"\", string CustomsoundName = \"\"){");
code("if(1*trQuestVarGet(\"CustomContent\") == 0){");
code("trSoundPlayPaused(\"\"+BasesoundName+\"\", \"1\", -1, \"\", \"\");");
code("}");
code("else {");
code("trSoundPlayPaused(\"\"+CustomsoundName+\"\", \"1\", -1, \"\", \"\");");
code("}");
code("}");

code("void ColouredIconChat(string colour = \"1,1,1\", string icon = \"\", string chats = \"\"){");
code("trChatSend(0, \"<color=\"+colour+\"><icon=(20)(\"+icon+\")> \"+chats+\"</color>\");");
code("}");

code("void ColouredIconChatToPlayer(int p = 1, string colour = \"1,1,1\", string icon = \"\", string chats = \"\"){");
code("trChatSendToPlayer(0, p, \"<color=\" + colour + \"><icon=(20)(\" + icon + \")> \" + chats + \"</color>\");");
code("}");

code("void PwnPlayer(int p = 0, int v = 0){");
code("trSetPlayerDefeated(p);");
code("OverlayTextPlayerColor(p);");
code("trOverlayText(trStringQuestVarGet(\"p\"+p+\"name\") + \"'s flag has been captured!\", 5.0, 350, 350, 800);");
code("playSound(\"Yeebaagooon\Capture The Flag\Warp.mp3\");");
code("playSound(\"timeshift.wav\");");
code("trCameraShake(5, 0.1);");
code("trPlayerKillAllBuildings(p);");
code("trPlayerKillAllUnits(p);");
code("trUnitSelectClear();");
code("trUnitSelect(\"+p+\");");
code("trUnitChangeProtoUnit(\"Cinematic Block\");");
code("trPlayerGrantResources(v, \"Food\", 1*trPlayerResourceCount(p, \"Food\"));");
code("trPlayerGrantResources(v, \"Wood\", 1*trPlayerResourceCount(p, \"Wood\"));");
code("trPlayerGrantResources(v, \"Gold\", 1*trPlayerResourceCount(p, \"Gold\"));");
code("ColouredIconChatToPlayer(v, \"{PlayerColor(\"+p+\")}\", \"icons\icon resource food\",");
code("\"\"+1*trPlayerResourceCount(p, \"Food\")+\"\");");
code("ColouredIconChatToPlayer(v, \"{PlayerColor(\"+p+\")}\", \"icons\icon resource wood\",");
code("\"\"+1*trPlayerResourceCount(p, \"Wood\")+\"\");");
code("ColouredIconChatToPlayer(v, \"{PlayerColor(\"+p+\")}\", \"icons\icon resource gold\",");
code("\"\"+1*trPlayerResourceCount(p, \"Gold\")+\"\");");
code("trPlayerGrantResources(p, \"Food\", -10000.0);");
code("trPlayerGrantResources(p, \"Wood\", -10000.0);");
code("trPlayerGrantResources(p, \"Gold\", -10000.0);");
code("trPlayerGrantResources(p, \"Favor\", -10000.0);");
code("trQuestVarModify(\"P\"+v+\"FlagsGot\", \"+\", 1);");
code("if(1*trQuestVarGet(\"P\"+v+\"FlagsGot\") < 9){");
code("");
code("");
code("");
code("FloatingUnitAnim4(\"Flag\",");
code("1*trVectorQuestVarGetX(\"P\"+v+\"FlagSlot\"+1*trQuestVarGet(\"P\"+v+\"FlagsGot\")),");
code("1*trVectorQuestVarGetY(\"P\"+v+\"FlagSlot\"+1*trQuestVarGet(\"P\"+v+\"FlagsGot\")),");
code("1*trVectorQuestVarGetZ(\"P\"+v+\"FlagSlot\"+1*trQuestVarGet(\"P\"+v+\"FlagsGot\")),");
code("0, 1, 1, 1, \"0,0,0,0,0\", p);");
code("}");
code("}");



code("void PaintAtlantisArea (int x0 = 0, int z0 = 0, int x1 = 0, int z1 = 0, int fill1 = 0, int fill2 = 0){");
code("");
code("trPaintTerrain(x0, z1, x0, z1, 0, 83, false);");
code("trPaintTerrain(x1, z1, x1, z1, 0, 80, false);");
code("");
code("trPaintTerrain(x0, z0, x0, z0, 0, 82, false);");
code("trPaintTerrain(x1, z0, x1, z0, 0, 81, false);");
code("");
code("trPaintTerrain(x1-1, z1, x0+1, z1, 0, 75, false);");
code("trPaintTerrain(x1-1, z0, x0+1, z0, 0, 75, false);");
code("");
code("trPaintTerrain(x1, z1-1, x1, z0+1, 0, 74, false);");
code("trPaintTerrain(x0, z1-1, x0, z0+1, 0, 74, false);");
code("");
code("trPaintTerrain(x1-1, z1-1, x0+1, z0+1, fill1, fill2, false);");
code("}");
code("rmSetStatusText(\"\",0.01);");
code("int MapSize = 100;");
code("rmSetMapSize(200, 200);");
code("rmSetSeaLevel(0);");
code("rmSetSeaType(\"greek river\");");
code("rmTerrainInitialize(\"GrassB\",3);");
code("rmSetLightingSet(\"Default\");");

code("int cNumberNonGaiaPlayers = "+cNumberNonGaiaPlayers+";");
code("int QuickStart = 0;");
code("string MapVersion = \"Test Version\";");
code("string MapName = \"Zoo Quest.xs\";");

code("rule Initialise");
code("active");
code("highFrequency");
code("runImmediately");
code("{");
code("characterDialog(\"Waiting for everyone to connect.\", \" \", \"icons\special e son of osiris icon 64\");");
code("trUIFadeToColor(0, 0, 0, 0, 10000, false);");
code("trFadeOutAllSounds(0.1);");
code("trFadeOutMusic(0.1);");
code("xsEnableRule(\"WorldBuild\");");
code("if(QuickStart == 0){");
code("}");
code("trBlockAllSounds(true);");
code("trArmyDispatch(\"0,0\", \"Cinematic Block\", 1, 0, 0, 0, 0, false);");
code("for(p = 1; <= cNumberNonGaiaPlayers){");
code("deployLocHeading(0, p*2, \"Victory Marker\", p, 180);");
code("}");
code("trSetFogAndBlackmap(false, false);");
for(p=1; <= cNumberNonGaiaPlayers) {
code("trStringQuestVarSet(\"p"+p+"name\", \""+rmGetPlayerName(p)+"\");");
}
code("xsDisableSelf();");
code("}");

code("rule START");
code("active");
code("highFrequency");
code("{");
code("aiSet(\"NoAI\", 0);");
code("trPlayerKillAllGodPowers(0);");
code("for(p = 1; <= cNumberNonGaiaPlayers){");
code("trSetCivAndCulture(p, 3, 1);");
code("trPlayerGrantResources(p, \"Food\", -10000.0);");
code("trPlayerGrantResources(p, \"Wood\", -10000.0);");
code("trPlayerGrantResources(p, \"Gold\", -10000.0);");
code("trPlayerGrantResources(p, \"Favor\", -10000.0);");
code("trPlayerKillAllGodPowers(p);");
code("modifyProtounitAbsolute(\"Vision Revealer\", p, 2, 24);");
code("modifyProtounitAbsolute(\"Vision Revealer\", p, 8, 999999);");
code("}");
code("");
code("");
code("trShowImageDialog(\"world a tamarisk tree leaf\", MapName + \" by Yeebaagooon\");");
code("gadgetUnreal(\"ShowImageBox-BordersTop\");");
code("gadgetUnreal(\"ShowImageBox-BordersBottom\");");
code("gadgetUnreal(\"ShowImageBox-BordersLeft\");");
code("gadgetUnreal(\"ShowImageBox-BordersRight\");");
code("gadgetUnreal(\"ShowImageBox-BordersLeftTop\");");
code("gadgetUnreal(\"ShowImageBox-BordersLeftBottom\");");
code("gadgetUnreal(\"ShowImageBox-BordersRightBottom\");");
code("gadgetUnreal(\"ShowImageBox-BordersRightTop\");");
code("gadgetUnreal(\"ShowImageBox-CloseButton\");");
code("pause(0);");
code("characterDialog(\"Initialising map\", \" \", \"icons\special e son of osiris icon 64\");");
code("xsEnableRule(\"load1\");");
code("xsDisableSelf();");
code("}");

code("rule load1");
code("inactive");
code("highFrequency");
code("{");
code("characterDialog(\"Loading map.\", \"\"+MapVersion+\"\", \"icons\special e son of osiris icon 64\");");
code("xsEnableRule(\"load2\");");
code("trBlockAllSounds(false);");
code("xsDisableSelf();");
code("}");

code("rule load2");
code("inactive");
code("highFrequency");
code("{");
code("characterDialog(\"Loading map..\", \"\"+MapVersion+\"\", \"icons\special e son of osiris icon 64\");");
code("xsEnableRule(\"load3\");");
code("xsDisableSelf();");
code("}");

code("rule load3");
code("inactive");
code("highFrequency");
code("{");
code("if((trTime()-cActivationTime) >= 1){");
code("characterDialog(\"Loading map...\", \"\"+MapVersion+\"\", \"icons\special e son of osiris icon 64\");");
code("aiSet(\"NoAI\", 0);");
code("for(p = 1; <= cNumberNonGaiaPlayers){");
code("trPlayerGrantResources(p, \"Food\", -10000.0);");
code("trPlayerGrantResources(p, \"Wood\", -10000.0);");
code("trPlayerGrantResources(p, \"Gold\", -10000.0);");
code("trPlayerGrantResources(p, \"Favor\", -10000.0);");
code("trPlayerKillAllGodPowers(p);");
code("");
code("");
code("}");
code("xsEnableRule(\"load4\");");
code("xsDisableSelf();");
code("}");
code("}");

code("rule load4");
code("inactive");
code("highFrequency");
code("{");
code("if((trTime()-cActivationTime) >= 1){");
code("");
code("trUnblockAllSounds();");
code("trLetterBox(false);");
code("trUIFadeToColor(0,0,0,1000,1,false);");
code("trOverlayTextColour(255, 125, 0);");
code("gadgetUnreal(\"ShowImageBox\");");
code("trOverlayText(MapName, 8.0, 566, 35, 1000);");
code("trSetUnitIdleProcessing(true);");
code("xsDisableSelf();");
code("paintShopSquare(3,3, \"Black\");");
code("UnitCreate(0, \"Hoplite\", 8, 8, 0);");
code("while(cNumberNonGaiaPlayers>=trQuestVarGet(\"PlayerID\")) {");
code("trQuestVarSet(\"PlayerID2\", 0);");
code("while(cNumberNonGaiaPlayers>=trQuestVarGet(\"PlayerID2\")) {");
code("trPlayerSetDiplomacy(trQuestVarGet(\"PlayerID\"), trQuestVarGet(\"PlayerID2\"), \"Enemy\");");
code("trPlayerSetDiplomacy(trQuestVarGet(\"PlayerID2\"), trQuestVarGet(\"PlayerID\"), \"Enemy\");");
code("trQuestVarSet(\"PlayerID2\", trQuestVarGet(\"PlayerID2\")+1);}");
code("trQuestVarSet(\"PlayerID\", trQuestVarGet(\"PlayerID\")+1);}");
code("}");
code("}");

code("rule customcontent");
code("inactive");
code("highFrequency");
code("{");
code("xsDisableSelf();");
code("trQuestVarSet(\"CustomContent\", 1);");
code("}");
code("rule Technologies");
code("inactive");
code("highFrequency");
code("{");
code("for(p = 1; <= cNumberNonGaiaPlayers){");
code("trTechSetStatus(p, 1, 4);");
code("trTechSetStatus(p, 2, 4);");
code("trTechSetStatus(p, 116, 4);");
code("trTechSetStatus(p, 29, 4);");
code("trTechSetStatus(p, 353, 0);");
code("trTechSetStatus(p, 394, 0);");
code("trTechSetStatus(p, 510, 0);");
code("trTechSetStatus(p, 145, 0);");
code("trTechSetStatus(p, 144, 0);");
code("trTechSetStatus(p, 143, 0);");
code("trTechSetStatus(p, 379, 0);");
code("trTechSetStatus(p, 28, 4);");
code("trTechSetStatus(p, 30, 4);");
code("trTechSetStatus(p, 350, 4);");
code("trTechSetStatus(p, 27, 4);");
code("for(n=930; >0) {");
code("trForbidProtounit(p,kbGetProtoUnitName(n));");
code("}");
code("}");
code("");
code("");
code("xsDisableSelf();");
code("}");

code("rule Stats");
code("inactive");
code("highFrequency");
code("{");
code("trModifyProtounit(\"Dwarf\", 0, 55, 4);");
code("for(p = 1; <= cNumberNonGaiaPlayers){");
code("trModifyProtounit(\"Dwarf\", p, 55, 4);");
code("");
code("");
code("modifyProtounitAbsolute(\"Atlantis Wall Long\", p, 0, 10000000);");
code("modifyProtounitAbsolute(\"Atlantis Wall Connector\", p, 0, 10000000);");
code("modifyProtounitAbsolute(\"Tower Mirror\", p, 0, 10000000);");
code("modifyProtounitAbsolute(\"Storage Pit\", p, 0, 10000000);");
code("trUnforbidProtounit(p, \"Outpost\");");
code("modifyProtounitAbsolute(\"Outpost\", p, 16, 0);");
code("modifyProtounitAbsolute(\"Outpost\", p, 17, 100);");
code("modifyProtounitAbsolute(\"Mercenary\", p, 8, 1);");
code("modifyProtounitAbsolute(\"Farm\", p, 16, 0);");
code("modifyProtounitAbsolute(\"Farm\", p, 17, 100);");
code("modifyProtounitAbsolute(\"Farm\", p, 18, 0);");
code("modifyProtounitAbsolute(\"Tower\", p, 16, 0);");
code("modifyProtounitAbsolute(\"Tower\", p, 17, 250);");
code("modifyProtounitAbsolute(\"Tower\", p, 18, 0);");
code("modifyProtounitAbsolute(\"Tower\", p, 10, 5);");
code("modifyProtounitAbsolute(\"Ape of Set\", p, 16, 50);");
code("modifyProtounitAbsolute(\"Ape of Set\", p, 17, 0);");
code("modifyProtounitAbsolute(\"Ape of Set\", p, 18, 0);");
code("modifyProtounitAbsolute(\"Ape of Set\", p, 19, 0);");
code("modifyProtounitAbsolute(\"Ape of Set\", p, 6, 0);");
code("modifyProtounitAbsolute(\"Ape of Set\", p, 3, 1);");
code("modifyProtounitAbsolute(\"Market\", p, 16, 0);");
code("modifyProtounitAbsolute(\"Market\", p, 17, 400);");
code("modifyProtounitAbsolute(\"Market\", p, 18, 0);");
code("modifyProtounitAbsolute(\"Market\", p, 10, 1);");
code("}");
code("xsDisableSelf();");
code("}");

rmAddTriggerEffect("SetIdleProcessing");
rmSetTriggerEffectParam("IdleProc",");*/rule _zenowashereagain inactive {if(true){xsDisableSelf();//");
rmSetStatusText("", 0.99);}