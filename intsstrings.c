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

//DELETE
*/

//---Controls
//\Yeebaagooon\Zoo Quest\Test sound.mp3
int QuickStart = 0;
int Stage = 0;
string MapVersion = "Test Version";
string MapName = "Zoo Quest.xs";
string GazelleProto = "Hero Greek Jason";
vector StageVector = vector(0,0,0);
string LeaveTerrain = "";

//EVENTS
const int EVENT_BUILD_HOUSE = 28;
const int EVENT_BUILD_GRANARY = 29;
const int EVENT_BUILD_STOREHOUSE = 30;
const int EVENT_REMOVE_CAM_TRACKS = 26;
const int EVENT_BUILD_AT_CURSOR = 31;

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

int dDestroyMe = 0;
int xDestroyName = 0;
int xDestroyTime = 0;


rule setup_first_databases
active
highFrequency
{
	dPlayerData = xInitDatabase("playerData");
	xSpyID = xInitAddInt(dPlayerData, "Spy id", 0);
	xOldAnim = xInitAddInt(dPlayerData, "Anim id", 0);
	xTarget = xInitAddInt(dPlayerData, "target id", 0);
	xPlayerActive = xInitAddBool(dPlayerData, "player alive", true);
	xVectorHold = xInitAddVector(dPlayerData, "hold vector");
	xStopDeath = xInitAddBool(dPlayerData, "player immortal", false);
	xTeleportDue = xInitAddInt(dPlayerData, "tp due", 0);
	xPlayerUnitID = xInitAddInt(dPlayerData, "unitId", -1);
	xReadyToLeave = xInitAddBool(dPlayerData, "leave area", false);
	xConstantPos = xInitAddVector(dPlayerData, "position", vector(0,0,0));
	xsDisableSelf();
	for(p=1; <= cNumberNonGaiaPlayers) {
		xAddDatabaseBlock(dPlayerData, true);
	}
	
	dDestroyMe = xInitDatabase("destroyme");
	xDestroyName = xInitAddInt(dDestroyMe, "unit id", -1);
	xDestroyTime = xInitAddInt(dDestroyMe, "timeMS", 1);
}
