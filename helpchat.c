rule Help_Chat
inactive
highFrequency
{
	for(p = 1; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		if(trCurrentPlayer() == p){
			if(trChatHistoryContains("HELP", p)){
				trChatHistoryClear();
				ColouredIconChat("1,0.5,0", ActIcon(Stage), "<u>" + ActName(Stage) + "</u>");
				ColouredChat("1,1,1", "<u>ABILITIES:</u>");
				switch(Stage)
				{
					case 1:
					{
						ColouredChat("1,1,0", "<u>Q:</u> Jump forward");
						ColouredChat("0.8,0.8,0", "You must move after each jump before jumping again");
						if(InMinigame == false){
							if(1*trQuestVarGet("BerriesEaten") < BerryTarget){
								trMessageSetText("OBJECTIVE: Eat the required number of berries by moving near them. Then enter the extraction zone.", 12000);
							}
							else{
								trMessageSetText("OBJECTIVE: All players must enter the extraction zone.", 10000);
							}
						}
						else{
							if(xGetBool(dPlayerData, xStopDeath) == true){
								trMessageSetText("MINIGAME: Reach the flag by jumping over the lava.", 10000);
							}
							else{
								trMessageSetText("You were not on the white tile when the minigame started, so are not counted as playing.", 10000);
							}
						}
					}
					case 2:
					{
						ColouredChat("1,1,0", "<u>Q:</u> Toggle charge");
						ColouredChat("0.8,0.8,0", "Use this ability when walking to toggle charge");
						ColouredChat("1,1,0", "<u>W:</u> Drink");
						ColouredChat("0.8,0.8,0", "Use when near water to drink, giving stamina to charge");
						if(InMinigame == false){
							if(ActPart == 1){
								trMessageSetText("OBJECTIVE: Break one fence in all of the 8 large fence lines.", 10000);
							}
							if(ActPart == 2){
								trMessageSetText("OBJECTIVE: Kill the required number of poachers. Then enter the extraction zone.", 10000);
							}
							if(ActPart == 3){
								trMessageSetText("OBJECTIVE: All players must enter the extraction zone.", 10000);
							}
						}
						else{
							if(xGetBool(dPlayerData, xStopDeath) == true){
								trMessageSetText("MINIGAME: Fling all villagers into the firey pit.", 10000);
							}
							else{
								trMessageSetText("You were not on the white tile when the minigame started, so are not counted as playing.", 10000);
							}
						}
					}
				}
			}
		}
	}
}
