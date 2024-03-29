/*
Set up the numbers corresponding to dialogs
const int NPC_RELIC_TRANSPORTER = 0;
const int NPC_RELIC_TRANSPORTER_WTF = 1;
*/
void startNPCDialog(int npc = 0) {
	if (trQuestVarGet("currentNPCProgress") == 0) {
		xsEnableRule("npc_talk_01");
		trQuestVarSet("currentNPC", npc);
		trQuestVarSet("currentNPCProgress", 0);
	}
}

int npcDiag(int npc = 0, int dialog = 0) {
	dialog = dialog + 1;
	string extra = "";
	int p = trCurrentPlayer();
	xSetPointer(dPlayerData, p);
	switch(npc)
	{
		case 1:
		{
			switch(dialog)
			{
				case 1:
				{
					trShowImageDialog("icons\special e son of osiris icon 64", "Hello!");
				}
				case 2:
				{
					trShowImageDialog("sfx a spy", "Test");
				}
				case 3:
				{
					trShowImageDialog("icons\infantry g hoplite icon 64", "Success!");
					dialog = 0;
				}
			}
		}
		case 2:
		{
			switch(dialog)
			{
				case 1:
				{
					uiZoomToProto(""+GazelleProto);
					uiLookAtProto(""+GazelleProto);
					uiMessageBox("Welcome to Zoo Quest. Here's a quick tutorial before we begin.");
				}
				case 2:
				{
					uiMessageBox("Press 'Q' to jump - you will always jump forward.");
					dialog = 0;
				}
			}
		}
		case 3:
		{
			switch(dialog)
			{
				case 1:
				{
					p = trCurrentPlayer();
					if(1*trQuestVarGet("P"+p+"FirstJump") == 0){
						uiMessageBox("Press 'Q' to jump - you will always jump forward.");
					}
					dialog = 0;
				}
			}
		}
		case 4:
		{
			switch(dialog)
			{
				case 1:
				{
					uiMessageBox("Great! Now make it to the end line and we can begin the map.");
				}
				case 2:
				{
					uiMessageBox("Just remember to move after a jump.");
					dialog = 0;
				}
			}
		}
		case 5:
		{
			switch(dialog)
			{
				case 1:
				{
					uiMessageBox("This is a treasure chest, come close to unlock it.");
					dialog = 0;
				}
			}
		}
		case 6:
		{
			switch(dialog)
			{
				case 1:
				{
					uiMessageBox("Now we play as the mighty Rhino.");
				}
				case 2:
				{
					uiMessageBox("Press 'Q' to toggle the charge ability when you are moving.");
				}
				case 3:
				{
					uiMessageBox("Use it to smash through the fence.");
					dialog = 0;
				}
			}
		}
		case 7:
		{
			switch(dialog)
			{
				case 1:
				{
					uiMessageBox("Charging is thristy work, you'll need to replenish stamina by drinking.");
				}
				case 2:
				{
					uiMessageBox("Press 'W' to drink when you are near water (can be map water).");
				}
				case 3:
				{
					uiMessageBox("You'll be immobilised while you drink, so be careful.");
				}
				case 4:
				{
					uiMessageBox("Drink from the fountain to complete this tutorial.");
					dialog = 0;
				}
			}
		}
		case 8:
		{
			switch(dialog)
			{
				case 1:
				{
					uiMessageBox("The mountain goat has a slightly different jump mechanic.");
				}
				case 2:
				{
					uiMessageBox("It will jump directly to the cursor (or as close as allowed) and can double jump.");
					dialog = 0;
				}
			}
		}
		case 9:
		{
			switch(dialog)
			{
				case 1:
				{
					uiMessageBox("Press 'W' to interract with nearby objects (such as the shrine).");
				}
				case 2:
				{
					uiMessageBox("There are several types of object you can interract with in the act.");
					dialog = 0;
				}
			}
		}
		case 10:
		{
			switch(dialog)
			{
				case 1:
				{
					uiMessageBox("Now we play as a fearsome Crocodile!");
				}
				case 2:
				{
					uiMessageBox("You have the ability to swim, so head over to the first island.");
					dialog = 0;
				}
			}
		}
		case 11:
		{
			switch(dialog)
			{
				case 1:
				{
					uiMessageBox("You will notice you are much slower on land.");
				}
				case 2:
				{
					uiMessageBox("You can use 'Q' for a short sprint on land or water.");
				}
				case 3:
				{
					uiMessageBox("If you use it within " + xGetInt(dPlayerData, xCrocBonusTime) + " seconds of leaving the water, you'll go extra fast.");
				}
				case 4:
				{
					uiMessageBox("Unlike the Rhino charge, this sprint lasts a set time and then recharges.");
					dialog = 0;
				}
			}
		}
		case 12:
		{
			switch(dialog)
			{
				case 1:
				{
					uiMessageBox("In this act you start off small and weak.");
				}
				case 2:
				{
					uiMessageBox("But by eating zebras you will grow in size and power.");
				}
				case 3:
				{
					uiMessageBox("Click attack will not work. Press 'W' to kill the zebra when in range.");
					dialog = 0;
				}
			}
		}
		case 13:
		{
			switch(dialog)
			{
				case 1:
				{
					uiMessageBox("You can't right click. Move close and use 'W' to kill.");
					dialog = 0;
				}
			}
		}
		case 14:
		{
			switch(dialog)
			{
				case 1:
				{
					uiMessageBox("For the final act - it's chicken time.");
				}
				case 2:
				{
					uiMessageBox("These devious creatures can build!");
				}
				case 3:
				{
					uiMessageBox("Use 'Q' to build a tower at your pointer.");
					dialog = 0;
				}
			}
		}
		case 15:
		{
			switch(dialog)
			{
				case 1:
				{
					uiMessageBox("Your towers will fire missiles at the enemy!");
				}
				case 2:
				{
					uiMessageBox("Use 'W' to craft an upgrade at the cursor.");
				}
				case 3:
				{
					uiMessageBox("This usually takes a lot longer, but is shorter in tutorial mode.");
					dialog = 0;
				}
			}
		}
		case 16:
		{
			switch(dialog)
			{
				case 1:
				{
					uiMessageBox("Click on a relic to find out what it does.");
				}
				case 2:
				{
					uiMessageBox("Garrison it in your Chicken to gain its benefit.");
					dialog = 0;
				}
			}
		}
		case 17:
		{
			switch(dialog)
			{
				case 1:
				{
					uiMessageBox("Press 'E' for all towers to gain doubleshot.");
				}
				case 2:
				{
					uiMessageBox("This ability lasts for 5 seconds.");
				}
				case 3:
				{
					uiMessageBox("Obviously, it comes with a rehcrage time.");
					dialog = 0;
				}
			}
		}
	}
	return(dialog);
}

rule npc_talk_01
inactive
highFrequency
{
	xsDisableSelf();
	trQuestVarSet("currentNPCProgress",
		npcDiag(1*trQuestVarGet("currentNPC"), 1*trQuestVarGet("currentNPCProgress")));
	if (trQuestVarGet("currentNPCProgress") > 0) {
		trDelayedRuleActivation("npc_talk_02");
	}
}

rule npc_talk_02
inactive
highFrequency
{
	if ((trQuestVarGet("currentNPCProgress") > 0) &&
		(trIsGadgetVisible("ingame-messagedialog") == false) &&
		(trIsGadgetVisible("ShowImageBox") == false)) {
		trDelayedRuleActivation("npc_talk_01");
		xsDisableSelf();
	}
}
