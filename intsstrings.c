//---Controls
//\Yeebaagooon\Zoo Quest\Test sound.mp3
int QuickStart = 0;
string MapVersion = "Test Version";
string MapName = "Zoo Quest.xs";

int dPlayerData = 0;
int xSpyID = 0;
int xOldAnim = 0;
int xTarget = 0;

rule setup_first_databases
active
highFrequency
{
	dPlayerData = xInitDatabase("playerData");
	xSpyID = xInitAddInt(dPlayerData, "Spy id", 0);
	xOldAnim = xInitAddInt(dPlayerData, "Anim id", 0);
	xTarget = xInitAddInt(dPlayerData, "target id", 0);
	xsDisableSelf();
	for(p=1; <= cNumberNonGaiaPlayers) {
		xAddDatabaseBlock(dPlayerData, true);
	}
}
