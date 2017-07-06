#if !defined(TEXT_H)
#define TEXT_H

void NameToString(int name)
{
	if (name == Normal)
		cout << "Normal";
	else if (name == BashMan)
		cout << "BashMan";
	else if (name == SlashMan)
		cout << "SlashMan";
	else if (name == ThrustMan)
		cout << "ThrustMan";
	else if (name == PierceMan)
		cout << "PierceMan";
	else if (name == ClampMan)
		cout << "ClampMan";
	else if (name == CrushMan)
		cout << "CrushMan";
	else if (name == EDmgMan)
		cout << "EDmgMan";
	else if (name == FireMan)
		cout << "FireMan";
	else if (name == IceMan)
		cout << "IceMan";
	else if (name == ElecMan)
		cout << "ElecMan";
	else if (name == AcidMan)
		cout << "AcidMan";


	else if (name == ArmorGuy)
		cout << "ArmorGuy";
	else if (name == Ninja)
		cout << "Ninja";
	else if (name == StrongMan)
		cout << "StrongMan";
	else if (name == FireMage)
		cout << "FireMage";
	else if (name == IceMage)
		cout << "IceMage";
	else if (name == ElecMage)
		cout << "ElecMage";
	else if (name == FireBattleMage)
		cout << "FireBattleMage";
	else if (name == IceBattleMage)
		cout << "IceBattleMage";
	else if (name == ElecBattleMage)
		cout << "ElecBattleMage";
	else if (name == Batman)
		cout << "Batman";
}

void GroupNameToString(groupname GroupName)
{
	if (GroupName == stdgroup)
		cout << "StdGroup";
	else if (GroupName == cutgroup)
		cout << "CutGroup";
	else if (GroupName == firegroup)
		cout << "FireGroup";
	else if (GroupName == icegroup)
		cout << "IceGroup";
	else if (GroupName == elecgroup)
		cout << "ElecGroup";
}

void ActionToString(int action)
{
	if (action == strike)
		cout << "Strike";
	else if (action == dodge)
		cout << "Dodge";
	else if (action == rest)
		cout << "Stamina";
	else if (action == fullrest)
		cout << "FullRest";
	else if (action == recover)
		cout << "Recover";
	else if (action == survive)
		cout << "Survive";
	else if (action == rmvfire)
		cout << "RmvFire";
	else if (action == rmvice)
		cout << "RmvIce";
	else if (action == execute)
		cout << "Execute";
	else if (action == unstun)
		cout << "Unstun";
	else if (action == pickupitem)
		cout << "PickUp";
	else if (action == stand)
		cout << "Stand";
	else if (action == mvtoexecute)
		cout << "MvToExecute";
	else if (action == noaction)
		cout << "NoAction";
	else
		cout << "UNLISTED ACTION";
}

void DmgTypeToString(int name)
{
	if (name == Dmg)
		cout << "Dmg";
	else if (name == Bash)
		cout << "Bash";
	else if (name == Slash)
		cout << "Slash";
	else if (name == Fire)
		cout << "Fire";
	else if (name == OnFire)
		cout << "OnFire";
	else if (name == Ice)
		cout << "Ice";
	else if (name == Frozen)
		cout << "Frozen";
	else if (name == Elec)
		cout << "Elec";
	else if (name == Stun)
		cout << "Stun";
	else if (name == EDmg)
		cout << "EDmg";
}

void BAToString(int BA)
{
	if (BA == Head)
		cout << "Head";
	else if (BA == Torso)
		cout << "Torso";
	else if (BA == LArm)
		cout << "LArm";
	else if (BA == RArm)
		cout << "RArm";
	else if (BA == LLeg)
		cout << "LLeg";
	else if (BA == RLeg)
		cout << "RLeg";
	else if (BA == Eyes)
		cout << "Eyes";
	else if (BA == Miss)
		cout << "Miss";
}

void PrintStatus(character *player)
{
	if (player->Vitals.Dmg >= 4)
		cout << "Vitals Trauma, ";
	if (player->LArm.Dmg >= 4)
		cout << "LArm Trauma, ";
	if (player->RArm.Dmg >= 4)
		cout << "RArm Trauma, ";
	if (player->LLeg.Dmg >= 4)
		cout << "LLeg Trauma, ";
	if (player->RLeg.Dmg >= 4)
		cout << "RLeg Trauma, ";
	if (player->Eyes.damaged)
		cout << "Blinded, ";
	if (player->RArm.severed)
		cout << "Severed RArm, ";
	if (player->LArm.severed)
		cout << "Severed LArm, ";
	if (player->RLeg.severed)
		cout << "Severed RLeg, ";
	if (player->LLeg.severed)
		cout << "Severed LLeg, ";
	if (player->Vitals.Dmg >= 5)
		cout << "Dead";

	cout << "\n";
}

void PrintDamage(character *player)
{
	if (player->HeadArmor.Armored)
	{
		NameToString(player->Name);
		cout << "Head Amr: " << player->HeadArmor.DR << " " << player->HeadArmor.PaddingRemaining << "/" << player->HeadArmor.PaddingTotal << "P"
			<< " " << player->HeadArmor.DamageRemaining << "/" << player->HeadArmor.DamageTotal << "D\n";
	}
	if (player->TorsoArmor.Armored)
	{
		NameToString(player->Name);
		cout << "Torso Amr: " << player->TorsoArmor.DR << " " << player->TorsoArmor.PaddingRemaining << "/" << player->TorsoArmor.PaddingTotal << "P"
			<< " " << player->TorsoArmor.DamageRemaining << "/" << player->TorsoArmor.DamageTotal << "D\n";
	}
	if (player->LArmArmor.Armored)
	{
		NameToString(player->Name);
		cout << "LArm Amr: " << player->LArmArmor.DR << " " << player->LArmArmor.PaddingRemaining << "/" << player->LArmArmor.PaddingTotal << "P"
			<< " " << player->LArmArmor.DamageRemaining << "/" << player->LArmArmor.DamageTotal << "D\n";
	}
	if (player->RArmArmor.Armored)
	{
		NameToString(player->Name);
		cout << "RArm Amr: " << player->RArmArmor.DR << " " << player->RArmArmor.PaddingRemaining << "/" << player->RArmArmor.PaddingTotal << "P"
			<< " " << player->RArmArmor.DamageRemaining << "/" << player->RArmArmor.DamageTotal << "D\n";
	}
	if (player->LLegArmor.Armored)
	{
		NameToString(player->Name);
		cout << "LLeg Amr: " << player->LLegArmor.DR << " " << player->LLegArmor.PaddingRemaining << "/" << player->LLegArmor.PaddingTotal << "P"
			<< " " << player->LLegArmor.DamageRemaining << "/" << player->LLegArmor.DamageTotal << "D\n";
	}
	if (player->RLegArmor.Armored)
	{
		NameToString(player->Name);
		cout << "RLeg Amr: " << player->RLegArmor.DR << " " << player->RLegArmor.PaddingRemaining << "/" << player->RLegArmor.PaddingTotal << "P"
			<< " " << player->RLegArmor.DamageRemaining << "/" << player->RLegArmor.DamageTotal << "D\n";
	}
	NameToString(player->Name);
	cout << " Dmg: Vitals[" << player->Vitals.Dmg;
	if (player->HeavyBleeding)
		cout << "H";
	if (player->Bleeding)
		cout << "B";
	if (player->Vitals.OnFire)
		cout << "F";
	if (player->Frozen)
		cout << "I";
	if (player->Vitals.PermDmg > 0)
		cout << "P" << player->Vitals.PermDmg;
	cout << "]";
	cout << " LArm[" << player->LArm.Dmg;
	if (player->LArm.OnFire)
		cout << "F";
	if (player->LArm.Frozen)
		cout << "I";
	if (player->LArm.PermDmg > 0)
		cout << "P" << player->LArm.PermDmg;
	cout << "]";
	cout << " RArm[" << player->RArm.Dmg;
	if (player->RArm.OnFire)
		cout << "F";
	if (player->RArm.Frozen)
		cout << "I";
	if (player->RArm.PermDmg > 0)
		cout << "P" << player->RArm.PermDmg;
	cout << "]";
	cout << " LLeg[" << player->LLeg.Dmg;
	if (player->LLeg.OnFire)
		cout << "F";
	if (player->LLeg.Frozen)
		cout << "I";
	if (player->LLeg.PermDmg > 0)
		cout << "P" << player->LLeg.PermDmg;
	cout << "]";
	cout << " RLeg[" << player->RLeg.Dmg;
	if (player->RLeg.OnFire)
		cout << "F";
	if (player->RLeg.Frozen)
		cout << "I";
	if (player->RLeg.PermDmg > 0)
		cout << "P" << player->RLeg.PermDmg;
	cout << "]";
	cout << " Effects[";
	if (player->OnFire > 0)
	{
		cout << "Fire:" << player->OnFire << " ";
	}
	if (player->Frozen > 0)
	{
		cout << "Ice:" << player->Frozen << " ";
	}
	if (player->Stunned)
		cout << "Stun ";
	if (player->Shock)
		cout << "Daze ";
	if (player->Prone)
		cout << "Prone";
	if (player->Disarmed)
		cout << "Disarm";
	cout << "]\n";
}

void ActionValuesToString(character *player)
{
	NameToString(player->Name);
	cout << ": ";
	for (int i = 0; i < 3; ++i)
	{
		ActionToString(player->Actions[i].ActionType);
		if (player->Actions[i].ActionType == strike)
		{
			cout << "[" << player->Rolls.HitValue << " Dmg:";
			if (player->Damage.DamageVital)
				cout << "Vital-";
			BAToString(player->Damage.BArea);
			cout << " " << player->Damage.DamageAmount;
			if (player->Damage.ExDmgType != None)
			{
				cout << " ";
				DmgTypeToString(player->Damage.ExDmgType);
				cout << " " << player->Damage.ExDmgAmount;
			}
			if (player->Damage.SEType != None)
			{
				cout << " ";
				DmgTypeToString(player->Damage.SEType);
				cout << " " << player->Damage.SEAmount;
			}
			cout << "]  ";
		}
		else if (player->Actions[i].ActionType == dodge)
			cout << "[" << player->Rolls.DodgeValue << "]  ";
		else if (player->Actions[i].ActionType == recover)
			cout << "[" << player->Rolls.RecoverValue << "]  ";
		else if (player->Actions[i].ActionType == survive)
			cout << "[" << player->Rolls.SurviveValue << "]  ";
		else if (player->Actions[i].ActionType == rest)
			cout << "[" << player->Rolls.RestValue << "]  ";
		else if (player->Actions[i].ActionType == fullrest)
			cout << "[" << player->Rolls.RestValue << "]  ";
		else if (player->Actions[i].ActionType == rmvfire)
			cout << "[" << player->Rolls.RmvFireValue << "]  ";
		else if (player->Actions[i].ActionType == rmvice)
			cout << "[" << player->Rolls.RmvIceValue << "]  ";
		else if (player->Actions[i].ActionType == unstun)
			cout << "[" << player->Rolls.UnstunValue << "]  ";
		else if (player->Actions[i].ActionType == stand)
			cout << "[" << player->Rolls.StandValue << "]  ";
		else if (player->Actions[i].ActionType == pickupitem)
			cout << "[" << player->Rolls.PickUpItemValue << "]  ";
		else if (player->Actions[i].ActionType == mvtoexecute)
			cout << "  ";
		else if (player->Actions[i].ActionType == execute)
		{
			cout << "[" << player->Rolls.HitValue << " Dmg:";
			if (player->Damage.DamageVital)
				cout << "Vital-";
			BAToString(player->Damage.BArea);
			cout << " " << player->Damage.DamageAmount;
			if (player->Damage.ExDmgType != None)
			{
				cout << " ";
				DmgTypeToString(player->Damage.ExDmgType);
				cout << " " << player->Damage.ExDmgAmount;
			}
			cout << "]  ";
		}
		else if (player->Actions[i].ActionType == noaction)
			cout << "  ";
	}
	cout << "\n";
}

void CharTypeToString(charactertype Type)
{
	/*
	if (Type == unarmed_0AS)
	cout << "Unarmed: 0AS";
	else if (Type == armed_1ASdamage)
	cout << "Armed: 1AS_Damage";
	else if (Type == trained_1ASdamage_1ASstrike)
	cout << "Trained: 1AS_Damage 1AS_Strike";
	else if (Type == potent_1ASdamage_1ASexdmg)
	cout << "Potent: 1AS_Damage 1AS_ExDmg";
	else if (Type == trainedandpotent_1ASdamage_1ASstrike_1ASexdmg)
	cout << "Trained + Potent: 1AS_Damage 1AS_Strike 1AS_ExDmg";
	else if (Type == defense_1ASdamage_1ASdodge)
	cout << "Defense: 1AS_Damage 1AS_Dodge";
	else if (Type == traineddefense_1ASdamage_1ASstrike_1ASdodge)
	cout << "Trained + Defense: 1AS_Damage 1AS_Strike 1AS_Dodge";
	else if (Type == armedtough_1ASdamage_1ASstrike_10vigor_10strength)
	cout << "Armed + Tough: 1AS_Damage 1AS_Strike 10_Vigor 10_Strength";
	else if (Type == armeddextrous_1ASdamage_1ASstrike_10strike_10dodge)
	cout << "Armed + Dextrous: 1AS_Damage 1AS_Strike 10_Strike 10_Dodge";
	else if (Type == armedawesome_1ASdamage_1ASstrike_10all)
	cout << "Armed + Awesome: 1AS_Damage 1AS_Strike 10_All";
	*/
}

#endif