/*
it uses build at pointer instead

For database count use DB first then > smaller number as DB size changes

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


[COMMENT]
Cinematic
Messages in stage 1 before poachers after chest for objectives
Flashing zebras


[BUG LIST]
skul062

MG3 that disturbing terrain glitch
?HP regen overlap
Minigame S4 revives dead players

//DELETE
*/

//---Controls
//\Yeebaagooon\Zoo Quest\Test sound.mp3
int QuickStart = 4;
// 3 for goat
int Stage = 0;
string MapVersion = "Test Version";
string MapName = "Zoo Quest.xs";
string GazelleProto = "Hero Greek Jason";
string RhinoProto = "Ajax";
string RhinoDrinkProto = "Physician";
vector StageVector = vector(0,0,0);
vector EndPoint = vector(0,0,0);
string LeaveTerrain = "";
string GoatProto = "Hero Greek Heracles";
string CrocProto = "Villager Norse";
string ChickenProto = "Hero Norse";

//EVENTS
const int EVENT_BUILD_HOUSE = 28;
const int EVENT_BUILD_GRANARY = 29;
const int EVENT_BUILD_STOREHOUSE = 30;
const int EVENT_REMOVE_CAM_TRACKS = 26;
const int EVENT_BUILD_AT_CURSOR = 31;
bool IGUnit = false;
int IGName = 0;
string unitcheck = "";

//MAP STUFF
float timediff = 0.0;
int timelast = 0;
vector MapCentre = vector(0,0,0);
int StageRequirement = 0;
int StageScore = 0;
int PlayersDead = 0;
int FlagUnitID = 0;
int FlagSFXID = 0;
int ChestsFound = 0;
int BerryTotal = 0;
int ChestsTotal = 0;
int CliffType = 2;
int CliffSubType = 2;
bool TutorialMode = false;
int ActPart = 0;
int PoachersDead = 0;
int PoachersTarget = 0;
int ShrinesGot = 0;
int ShrinesMax = 0;
int ShrineTimeMin = 80;
int ShrineTarget = 0;
int ShrineTimeMax = 200;
int Zebras = 0;
int CrocProgress = 0;
int CrocTarget = 0;

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
int FencesDone = 0;
int SquaresDown = 0;

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
int xHPRegen = 0;
int xHPRegenTime = 0;
int xHPRegenNext = 0;
int xSecondSpy = 0;
int xRhinoDrinkTime = 0;
int xRhinoChargeTime = 0;
int xRhinoChargeTimeMax = 0;
int xGoatTarget = 0;
int xGoatJumpDist = 0;
int xTimeout = 0;
int xSwimming = 0;
int xCrocLandSpeed = 0;
int xCrocWaterSpeed = 0;
int xCrocSprintSpeed = 0;
int xCrocBonusTime = 0;
int xCrocBonusTimer = 0;
int xCrocSprintRechargeTime = 0;
int xCrocSprintRechargeTimer = 0;
int xCrocSprintDuration = 0;
int xCrocSprintEndTime = 0;
int xCrocSprintState = 0;
int xCrocSize = 0;
int xCrocFood = 0;
int xCrocNext = 0;
int xQuestions = 0;
int xQuestionsCorrect = 0;
int xAnswer = 0;
int xQuestionAnswer = 0;

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
	xHPRegen = xInitAddInt(dPlayerData, "hp regen", 0);
	xHPRegenTime = xInitAddInt(dPlayerData, "hp regen timer", 0);
	xHPRegenNext = xInitAddInt(dPlayerData, "hp regen counter", 0);
	xSecondSpy = xInitAddInt(dPlayerData, "spy id", 0);
	xRhinoDrinkTime = xInitAddFloat(dPlayerData, "drink time", 5);
	xRhinoChargeTime = xInitAddFloat(dPlayerData, "rhino charge", 15);
	xRhinoChargeTimeMax = xInitAddInt(dPlayerData, "rhino charge max", 15);
	xGoatTarget = xInitAddVector(dPlayerData, "goat target", vector(0,0,0));
	xGoatJumpDist = xInitAddFloat(dPlayerData, "goat jump dist", 0.0);
	xTimeout = xInitAddInt(dPlayerData, "goat jump timeout", 1000);
	xSwimming = xInitAddBool(dPlayerData, "swimming", false);
	xCrocLandSpeed = xInitAddFloat(dPlayerData, "croc land speed", 3.0);
	xCrocWaterSpeed = xInitAddFloat(dPlayerData, "croc swim speed", 5.0);
	xCrocSprintSpeed = xInitAddFloat(dPlayerData, "speed multiply", 1.5);
	xCrocBonusTime = xInitAddInt(dPlayerData, "xc", 3);
	xCrocBonusTimer = xInitAddInt(dPlayerData, "xc", 30);
	xCrocSprintRechargeTime = xInitAddInt(dPlayerData, "xc", 20);
	xCrocSprintRechargeTimer = xInitAddInt(dPlayerData, "xc", 20);
	xCrocSprintDuration = xInitAddInt(dPlayerData, "xc", 2500);
	xCrocSprintEndTime = xInitAddInt(dPlayerData, "the end time of the sprint", 0);
	xCrocSprintState = xInitAddInt(dPlayerData, "xc", 0);
	xCrocSize = xInitAddInt(dPlayerData, "xc", 1);
	xCrocFood = xInitAddFloat(dPlayerData, "xc", 0);
	xCrocNext = xInitAddFloat(dPlayerData, "next food", 0);
	xQuestions = xInitAddInt(dPlayerData, "qs mg", 0);
	xQuestionsCorrect = xInitAddInt(dPlayerData, "qs mg", 0);
	xAnswer = xInitAddInt(dPlayerData, "player answer", -1);
	xQuestionAnswer = xInitAddInt(dPlayerData, "correct answer", -1);
	for(p=1; <= cNumberNonGaiaPlayers) {
		xAddDatabaseBlock(dPlayerData, true);
	}
	
	dDestroyMe = xInitDatabase("destroyme");
	xDestroyName = xInitAddInt(dDestroyMe, "unit id", -1);
	xDestroyTime = xInitAddInt(dDestroyMe, "timeMS", 1);
	xsDisableSelf();
}
