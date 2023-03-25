rule Help_Chat
inactive
highFrequency
{
	for(p = 1; < cNumberNonGaiaPlayers){
		xSetPointer(dPlayerData, p);
		string extrachat = "You can refresh already active shrines.";
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
					case 3:
					{
						ColouredChat("1,1,0", "<u>Q:</u> Jump");
						ColouredChat("0.8,0.8,0", "Jump towards the cursor");
						ColouredChat("1,1,0", "<u>W:</u> Interract");
						ColouredChat("0.8,0.8,0", "Interract with a world object, try it!");
						trChatSend(0, "Collect relics (W) to buy god powers");
						if(InMinigame == false){
							if(Difficulty < 2){
								trMessageSetText("OBJECTIVE: Activate shrines (W) and then make your way to the zone." + extrachat, 10000);
							}
							else{
								trMessageSetText("OBJECTIVE: Activate shrines (W) and then make your way to the zone.", 10000);
							}
						}
						else{
							if(xGetBool(dPlayerData, xStopDeath) == true){
								trMessageSetText("MINIGAME: Sink 6 squares. Interract (W) with columns to do this.", 10000);
							}
							else{
								trMessageSetText("You were not on the white tile when the minigame started, so are not counted as playing.", 10000);
							}
						}
					}
					case 4:
					{
						ColouredChat("1,1,0", "<u>Q:</u> Sprint");
						ColouredChat("0.8,0.8,0", "Gain a temporary speed boost");
						ColouredChat("1,1,0", "<u>W:</u> Eat");
						ColouredChat("0.8,0.8,0", "Eat a Zebra if close enough");
						ColouredChat("0.8,0.8,0", "You can also eat other world objects");
						ColouredChat("1,1,0", "<u>E:</u> Ranged attack");
						ColouredChat("0.8,0.8,0", "Temporary ranged attack (requires relics)");
						if(InMinigame == false){
							trMessageSetText("OBJECTIVE: Eat zebras to grow in size. Grow to level 7.", 10000);
						}
						else{
							if(xGetBool(dPlayerData, xStopDeath) == false){
								trMessageSetText("You were not on the white tile when the minigame started, so are not counted as playing.", 10000);
							}
						}
					}
					case 5:
					{
						ColouredChat("1,1,0", "<u>E:</u> All towers shoot");
						ColouredChat("0.8,0.8,0", "All towers fire at the cursor, ignoring range");
						ColouredChat("0.8,0.8,0", "After you expend your charges, they recharge");
						ColouredChat("1,1,0", "<u>R:</u> Convert relics");
						ColouredChat("0.8,0.8,0", "Changes nearby relics to landmines");
					}
				}
			}
		}
	}
}
