//---Controls
//\Yeebaagooon\Zoo Quest\Test sound.mp3
int QuickStart = 0;
string MapVersion = "Test Version";
string MapName = "Zoo Quest.xs";

int dPlayerData = 0;
int xSpyID = 0;

rule setup_first_databases
active
highFrequency
{
	dPlayerData = xInitDatabase("playerData");
	xSpyID = xInitAddInt(dPlayerData, "Spy id", 0);
	xsDisableSelf();
	for(p=1; <= cNumberNonGaiaPlayers) {
		xAddDatabaseBlock(dPlayerData, true);
	}
}
