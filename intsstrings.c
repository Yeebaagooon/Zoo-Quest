/*
it uses build at pointer instead

[10:54 PM]
Yeebaagooon:
9

[10:54 PM]
Zenophobia:
turns out anything can be tasked to build a building
even if it's not a villager

[10:54 PM]
Yeebaagooon:
never knew that
so instant structure

[10:54 PM]
Zenophobia:
yeah with negative build points
and of course the cost needs to be set to 0

since kbGetBlockPosition requires the unit name
instead of the id


FIX PAINT TREES SO LIKE A CHECKBOARD - actually ok for stage one

DEER QUEST
Eat berries
Survive poacher
Find and gather in clearing

[COMMENT]
Tidy up
Sort tutorial + intro
*Change vision to build order from worldbuild
?Data
Engage level 1
Fix tree paint


BUG
Deer hurt sound for all

//DELETE
*/

//---Controls
//\Yeebaagooon\Zoo Quest\Test sound.mp3
int QuickStart = 2;
int Stage = 0;
string MapVersion = "Test Version";
string MapName = "Zoo Quest.xs";
string GazelleProto = "Hero Greek Jason";
string RhinoProto = "Royal Guard";
vector StageVector = vector(0,0,0);
vector EndPoint = vector(0,0,0);
string LeaveTerrain = "";

//EVENTS
const int EVENT_BUILD_HOUSE = 28;
const int EVENT_BUILD_GRANARY = 29;
const int EVENT_BUILD_STOREHOUSE = 30;
const int EVENT_REMOVE_CAM_TRACKS = 26;
const int EVENT_BUILD_AT_CURSOR = 31;

//MAP STUFF
float timediff = 0.0;
int timelast = 0;
vector MapCentre = vector(0,0,0);
int StageRequirement = 0;
int StageScore = 0;
int PlayersDead = 0;
int FlagUnitID = 0;
int ChestsFound = 0;
int BerryTotal = 0;
int ChestsTotal = 0;
int CliffType = 2;
int CliffSubType = 2;

//DB STUFF
int DestroyNumber = 0;
int NewDestroyNumber = 0;
int DontDestroyBelow = 0;
int PlayersActive = 10;
int BerryTarget = 0;
int PlayersMinigaming = 0;
int PlayersReadyToLeave = 0;
int MinigameWins = 0;
int GlobalTimerMS = 0;
bool InMinigame = false;
bool MinigameFound = false;

int dPlayerData = 0;
int xSpyID = 0;
int xOldAnim = 0;
int xTarget = 0;
int xPlayerActive = 0;
int xVectorHold = 0;
int xStopDeath = 0;
int xTeleportDue = 0;
int xPlayerUnitID = 0;
int xReadyToLeave = 0;
int xConstantPos = 0;
int xPlayerDead = 0;
int xLogJumps = 0;
int xCharge = 0;
int xRhinoWalk = 0;
int xRhinoRun = 0;

int dDestroyMe = 0;
int xDestroyName = 0;
int xDestroyTime = 0;


rule setup_first_databases
active
highFrequency
{
	dPlayerData = xInitDatabase("playerData");
	xPlayerUnitID = xInitAddInt(dPlayerData, "unit id", 0);
	xSpyID = xInitAddInt(dPlayerData, "Spy id", 0);
	xOldAnim = xInitAddInt(dPlayerData, "Anim id", 0);
	xTarget = xInitAddInt(dPlayerData, "target id", 0);
	xPlayerActive = xInitAddBool(dPlayerData, "player alive", true);
	xVectorHold = xInitAddVector(dPlayerData, "hold vector", vector(0,0,0));
	xStopDeath = xInitAddBool(dPlayerData, "player immortal", false);
	xTeleportDue = xInitAddInt(dPlayerData, "tp due", 0);
	xPlayerUnitID = xInitAddInt(dPlayerData, "unitId", -1);
	xReadyToLeave = xInitAddBool(dPlayerData, "leave area", false);
	xConstantPos = xInitAddVector(dPlayerData, "position", vector(0,0,0));
	xPlayerDead = xInitAddBool(dPlayerData, "dead", false);
	xLogJumps = xInitAddInt(dPlayerData, "jump", 0);
	xCharge = xInitAddBool(dPlayerData, "charge", false);
	xRhinoWalk = xInitAddFloat(dPlayerData, "rhino base speed", 4.0);
	xRhinoRun = xInitAddFloat(dPlayerData, "rhino run speed", 9.5);
	xsDisableSelf();
	for(p=1; <= cNumberNonGaiaPlayers) {
		xAddDatabaseBlock(dPlayerData, true);
	}
	
	dDestroyMe = xInitDatabase("destroyme");
	xDestroyName = xInitAddInt(dDestroyMe, "unit id", -1);
	xDestroyTime = xInitAddInt(dDestroyMe, "timeMS", 1);
}
