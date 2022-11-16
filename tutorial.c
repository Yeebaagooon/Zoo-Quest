rule TutorialTerrain
highFrequency
active
{
	if (trTime() > cActivationTime + 1) {
		xsDisableSelf();
		trLetterBox(false);
		trPaintTerrain(0,0,35,cNumberNonGaiaPlayers*8,2,4);
		for(p=1 ; < cNumberNonGaiaPlayers){
			trPlayerSetDiplomacy(0, p, "Enemy");
			trPaintTerrain(5,((p*8)-2),30,((p*8+4)-2),0,2);
			trPaintTerrain(7,p*8,7,p*8,0,73); //start sq
			trPaintTerrain(28,p*8+2,28,p*8-2,0,74); //end line
			trQuestVarSet("P"+p+"Unit", trGetNextUnitScenarioNameNumber());
			UnitCreate(p, "Hero Greek Jason", 14, p*16, 90);
			UnitCreate(0, "Revealer", 14, p*16, 90);
			spyEffect(1*trQuestVarGet("P"+p+"Unit"), kbGetProtoUnitID("White Tiger"), xsVectorSet(dPlayerData,xSpyID,p), vector(1,1,1));
			//spyEffect(1*trQuestVarGet("P"+p+"Unit"), kbGetProtoUnitID("Gazelle"), vector(1,1,1), vector(1,1,1));
		}
	}
}
