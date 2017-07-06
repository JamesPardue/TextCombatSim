#include <iostream>
using namespace std;
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <fstream>
#include <time.h>  
#include <string.h>
#include <fstream>

#include "comstruct.h"
#include "text.h"

static bool LOGGING;
static bool MULTI;

int Check(int skillvalue, int focus)
{
	int result = 0;
	if (skillvalue > 0)
	{
		for (int i = 1; i <= skillvalue; ++i)
		{
			int d8 = rand() % 8 + 1;
			if (d8 == 8)
				++result;
		}
		for (int i = 0; i < focus; ++i)
		{
			int base = rand() % 6 + 1;
			if ((base == 5) || (base == 6))
				++result;
		}
	}
	return result;
}

void BARoll(character *player, bool vitaltarget)
{
	/*
	int BA = rand() % 6 + 1;
	int Dir = rand() % 2 + 1;
	int DirNum = rand() % 3 + 1;
	if (!vitaltarget)
	{
	if (BA == 1)
	{
	if (DirNum == 2)
	player->Damage.BArea = Eyes;
	else
	player->Damage.BArea = Head;
	}
	else if ((BA == 2) || (BA == 3))
	player->Damage.BArea = Torso;
	else if (BA == 4 && Dir == 1)
	player->Damage.BArea = LArm;
	else if (BA == 4 && Dir == 2)
	player->Damage.BArea = RArm;
	else if (BA == 5 && Dir == 1)
	player->Damage.BArea = LLeg;
	else if (BA == 5 && Dir == 2)
	player->Damage.BArea = RLeg;
	else if (BA == 6)
	player->Damage.DamageVital = true;
	}
	/*
	if (vitaltarget || player->Damage.DamageVital)
	{
	++player->Damage.BArea;
	int BA = rand() % 6 + 1;
	if (BA == 1)
	{
	if (DirNum == 3)
	player->Damage.BArea = Eyes;
	else
	player->Damage.BArea = Head;
	}
	else if ((BA == 2) || (BA == 3))
	player->Damage.BArea = Torso;
	else if (BA == 4 && Dir == 1)
	player->Damage.BArea = LArm;
	else if (BA == 4 && Dir == 2)
	player->Damage.BArea = RArm;
	else if (BA == 5 && Dir == 1)
	player->Damage.BArea = LLeg;
	else if (BA == 5 && Dir == 2)
	player->Damage.BArea = RLeg;
	else if (BA == 6)
	player->Damage.BArea = Head;
	}
	if(player->Damage.BArea == Head || player->Damage.BArea == Eyes)
	++player->Damage.DamageAmount;
	*/
}

int DetermineHitSkill(character *player)
{
	int HitSkill = player->HitSkill;
	if (player->RArm.crippled)
	{
	}

	if (player->Blinded);

	HitSkill += player->StrikeBonus;

	return HitSkill;
}

int DetermineDodgeSkill(character *player)
{
	int DodgeSkill = 0;
	DodgeSkill = player->DodgeSkill;

	return DodgeSkill;
}

int DetermineDmgSkill(character* player)
{
	int DmgSkill = player->DmgSkill;
	if (player->RArm.crippled)
	{
		if (!player->LArm.crippled)
		{
			DmgSkill = player->DmgSkill;
		}
		else
			DmgSkill = 0;
	}

	DmgSkill = DmgSkill + player->WeaponBonus;

	return DmgSkill;
}

int DetermineRmvFireSkill(character *player)
{
	int RmvFireSkill = 0;
	RmvFireSkill = player->DodgeSkill;

	return RmvFireSkill;
}

int DetermineRmvIceSkill(character *player)
{
	int RmvIceSkill = 0;
	RmvIceSkill = player->DmgSkill;

	return RmvIceSkill;
}

int DetermineVitSkill(character *player)
{
	int VitSkill = player->VitSkill;
	return VitSkill;
}

void DetermineDamageValues(character *player, bool primary, bool vitaltargeted)
{
	if (player->Damage.DamageType != None)
	{
		if (primary)
			player->Damage.DamageAmount = Check(DetermineDmgSkill(player), 1);
		else
			player->Damage.DamageAmount = Check(DetermineDmgSkill(player), 0);

		if (!player->Disarmed)
			player->Damage.DamageAmount += player->WeaponSuccess;
		if (player->Prone)
			--player->Damage.DamageAmount;
		BARoll(player, vitaltargeted);
	}
	if (player->Damage.ExDmgType != None)
	{
		player->Damage.ExDmgAmount = Check(player->MagSkill, 0) + player->ExDmgSuccess;
	}
	if (player->Damage.SEType != None)
	{
		player->Damage.SEAmount = Check(player->MagSkill, 0) + player->SESuccess;
		if (player->Stunned)
			--player->Damage.SEAmount;
		if (player->Stunned2)
			--player->Damage.SEAmount;
	}
}

void Attack(character *attacker, character *defender)
{
	int HitValue = attacker->Rolls.HitValue - defender->Rolls.DodgeValue;
	attacker->Rolls.HitValue = HitValue;

	if (HitValue >= 4)
		attacker->Damage.BArea = Eyes;
	else if (HitValue >= 3)
		attacker->Damage.BArea = Head;
	else if (HitValue >= 2)
		attacker->Damage.BArea = Torso;
	else if (HitValue >= 1)
	{
		if (defender->RLeg.Dmg > 0 && defender->RLeg.Dmg < 6)
			attacker->Damage.BArea = RLeg;
		if (defender->LLeg.Dmg > 0 && defender->LLeg.Dmg < 6)
			attacker->Damage.BArea = LLeg;
		if (defender->RArm.Dmg > 0 && defender->RArm.Dmg < 6)
			attacker->Damage.BArea = RArm;
		if (defender->LArm.Dmg > 0 && defender->LArm.Dmg < 6)
			attacker->Damage.BArea = LArm;
		else
		{
			int BA = rand() % 10 + 1;
			if (BA >= 1 && BA <= 3)
				attacker->Damage.BArea = RArm;
			else if (BA >= 4 && BA <= 6)
				attacker->Damage.BArea = RLeg;
			else if (BA >= 7 && BA <= 9)
				attacker->Damage.BArea = LLeg;
			else if (BA == 10)
				attacker->Damage.BArea = LArm;
		}
	}
	else
	{
		attacker->Damage.DamageAmount = 0;
		attacker->Damage.ExDmgAmount = 0;
		attacker->Damage.SEAmount = 0;
		attacker->Damage.BArea = Miss;
	}
	/*
	Hit = (attacker->Rolls.HitValue - defender->Rolls.DodgeValue > 0);
	if (attacker->ExecutePos && (defender->Rolls.DodgeValue == 0))
	Hit = true;

	if (Hit)
	{
	if (attacker->ExecutePos && LOGGING)
	{
	NameToString(defender->Name);
	cout << " executes for " << attacker->Damage.DamageAmount << ".\n";
	}
	}
	else
	{
	attacker->Damage.DamageAmount = 0;
	attacker->Damage.ExDmgAmount = 0;
	if (LOGGING)
	{
	if (attacker->Rolls.HitValue - defender->Rolls.DodgeValue <= 0)
	{
	NameToString(defender->Name);
	cout << " dodges ";
	NameToString(attacker->Name);
	cout << ".\n";
	}
	}
	}
	*/
}

void ApplyDamage(character *player, damage dmg)
{
	int TotalStandard = 0;

	TotalStandard = dmg.DamageAmount + dmg.ExDmgAmount;

	if (LOGGING)
	{
		if (TotalStandard > 0)
		{
			NameToString(player->Name);
			cout << " gets hit in the ";
			BAToString(dmg.BArea);
			cout << " for " << TotalStandard << ".\n";
		}
	}
	armor A1;
	armor *Armor = &A1;
	InitArmor(&A1);
	if (player->HeadArmor.BodyArea == dmg.BArea)
		Armor = &player->HeadArmor;
	else if (player->TorsoArmor.BodyArea == dmg.BArea)
		Armor = &player->TorsoArmor;
	else if (player->LArmArmor.BodyArea == dmg.BArea)
		Armor = &player->LArmArmor;
	else if (player->RArmArmor.BodyArea == dmg.BArea)
		Armor = &player->RArmArmor;
	else if (player->LLegArmor.BodyArea == dmg.BArea)
		Armor = &player->LLegArmor;
	else if (player->RLegArmor.BodyArea == dmg.BArea)
		Armor = &player->RLegArmor;

	if (Armor->Armored && (Armor->DamageRemaining > 0))
	{
		TotalStandard -= Armor->DR;
		while ((Armor->PaddingRemaining > 0) && (TotalStandard > 0))
		{
			--Armor->PaddingRemaining;
			--TotalStandard;
		}
		if (TotalStandard < 0)
			TotalStandard = 0;
		if (Armor->PaddingRemaining >= 0)
		{
			Armor->DamageRemaining -= TotalStandard;
		}
	}

	if (TotalStandard > 0)
	{
		player->ExecutePos = false;
		if (dmg.DamageType == Elec)
		{
			if (TotalStandard >= 3)
				player->Stunned = true;
			if ((dmg.BArea == RArm) || (dmg.BArea == LArm)
				|| (dmg.BArea == RLeg) || (dmg.BArea == LLeg))
				dmg.BArea = Torso;
		}

		switch (dmg.BArea)
		{
		case(Head) : player->Vitals.Dmg += TotalStandard;
			++player->Vitals.Dmg;
			if (TotalStandard + 1 >= 3)
				++player->Vitals.PermDmg;
			break;
		case(Torso) : player->Vitals.Dmg += TotalStandard;
			if (TotalStandard >= 3)
				++player->Vitals.PermDmg;
			break;
		case(LArm) : player->LArm.Dmg += TotalStandard;
			if (TotalStandard >= 3)
				++player->LArm.PermDmg;
			break;
		case(RArm) : player->RArm.Dmg += TotalStandard;
			if (TotalStandard >= 3)
				++player->RArm.PermDmg;
			break;
		case(LLeg) : player->LLeg.Dmg += TotalStandard;
			if (TotalStandard >= 3)
				++player->LLeg.PermDmg;
			break;
		case(RLeg) : player->RLeg.Dmg += TotalStandard;
			if (TotalStandard >= 3)
				++player->RLeg.PermDmg;
			break;
		case(Eyes) :
			player->Eyes.damage += 1;
			player->Vitals.Dmg += TotalStandard;
			++player->Vitals.Dmg;
			if (TotalStandard + 1 >= 3)
				++player->Vitals.PermDmg;
			break;
		}
		/*
		if (player->LArm.Dmg > 6)
		{
			player->Vitals.Dmg += (player->LArm.Dmg - 6);
			player->LArm.Dmg = 6;
		}
		if (player->RArm.Dmg > 6)
		{
			player->Vitals.Dmg += (player->RArm.Dmg - 6);
			player->RArm.Dmg = 6;
		}
		if (player->LLeg.Dmg > 6)
		{
			player->Vitals.Dmg += (player->LLeg.Dmg - 6);
			player->LLeg.Dmg = 6;
		}
		if (player->RLeg.Dmg > 6)
		{
			player->Vitals.Dmg += (player->RLeg.Dmg - 6);
			player->RLeg.Dmg = 6;
		}
		*/

		if (dmg.DamageType == Bash)
			player->Shock = true;
		if (dmg.DamageType == Slash)
			player->Bleeding = true;
		/*
		if (dmg.DamageType == Bash && (dmg.BArea == Head || dmg.BArea == Eyes))
			player->Stunned = true;
		if (dmg.DamageType == Bash && (dmg.BArea == RLeg || dmg.BArea == LLeg) && TotalStandard >= 3)
			player->Prone = true;
		if (dmg.DamageType == Bash && dmg.BArea == RArm && TotalStandard >= 3)
			player->Disarmed = true;

		if (dmg.DamageType == Slash)
			player->Bleeding = true;
		if (dmg.DamageType == Slash && TotalStandard >= 3)
			player->HeavyBleeding = true;
			*/
	}

	if (dmg.SEAmount > 0)
	{
		if (dmg.SEType == OnFire)
		{
			player->OnFire += dmg.SEAmount;
			if (player->OnFire > 3)
				player->OnFire = 3;
			/*
			if(dmg.BArea == Head || dmg.BArea == Torso || dmg.BArea == Eyes)
			player->Vitals.OnFire = true;
			if(dmg.BArea == RArm)
			player->RArm.OnFire = true;
			if(dmg.BArea == LArm)
			player->LArm.OnFire = true;
			if(dmg.BArea == RLeg)
			player->RLeg.OnFire = true;
			if(dmg.BArea == LLeg)
			player->LLeg.OnFire = true;
			*/
		}

		if (dmg.SEType == Frozen)
		{
			player->Frozen += dmg.SEAmount;
			if (player->Frozen > 3)
				player->Frozen = 3;
			/*
			if(dmg.BArea == Head || dmg.BArea == Torso || dmg.BArea == Eyes)
			player->Frozen = true;
			if(dmg.BArea == RArm)
			player->RArm.Frozen = true;
			if(dmg.BArea == LArm)
			player->LArm.Frozen = true;
			if(dmg.BArea == RLeg)
			player->RLeg.Frozen = true;
			if(dmg.BArea == LLeg)
			player->LLeg.Frozen = true;
			*/
		}

		if (dmg.SEType == Stun)
		{
			/*
			if (dmg.SEAmount >= 2)
				player->Stunned = true;
			if (dmg.SEAmount >= 3)
				player->Stunned2 = true;
				*/
		}
	}
}

void CheckExertion(character *player)
{
	if (LOGGING)
	{
		cout << "Exertion[" << player->Exertion << "/6]";
		if (player->Fatigue > 0)
			cout << " Fatigue[" << player->Fatigue << "/6]";
		cout << '\n';
	}

	if (player->Exertion >= 11)
	{
		if (LOGGING)
		{
			NameToString(player->Name);
			cout << " is exhausted.\n";
		}
		player->Exhausted = true;
	}
}

void CheckDamage(character *player)
{
	if (player->RArm.Dmg >= 6)
	{
		if (LOGGING && !player->RArm.crippled)
		{
			NameToString(player->Name);
			cout << "'s RArm has been Crippled.\n";
		}
		player->RArm.crippled = true;
		player->Disarmed = true;
	}
	if (player->LArm.Dmg > 3)
	{
		if (LOGGING && !player->LArm.crippled)
		{
			NameToString(player->Name);
			cout << "'s LArm has been Crippled.\n";
		}
		player->LArm.crippled = true;
	}
	if (player->LLeg.Dmg > 3 || player->RLeg.Dmg > 3)
	{
		if (LOGGING && !player->Crippled)
		{
			NameToString(player->Name);
			cout << "'s Legs have been Crippled.\n";
		}
		player->Crippled = true;
	}
	else
		player->Crippled = false;
	if (player->Crippled)
	{
		player->Prone = true;
	}
	if (player->Eyes.damage > player->Eyes.redundancy)
	{
		if (LOGGING && !player->Blinded)
		{
			NameToString(player->Name);
			cout << " has been Blinded.\n";
		}
		player->Eyes.damaged = true;
		player->Blinded = true;
	}

	if (player->Vitals.Dmg > 3) //(player->Head.damage > 3 || player->Torso.damage > 3)
	{
		if (LOGGING && !player->Wounded)
		{
			NameToString(player->Name);
			cout << " has been Wounded.\n";
		}
		player->Wounded = true;
	}
	if (player->Vitals.Dmg < player->Vitals.PermDmg)
		player->Vitals.Dmg = player->Vitals.PermDmg;
	if (player->RLeg.Dmg < player->RLeg.PermDmg)
		player->RLeg.Dmg = player->RLeg.PermDmg;
	if (player->LLeg.Dmg < player->LLeg.PermDmg)
		player->LLeg.Dmg = player->LLeg.PermDmg;
	if (player->RArm.Dmg < player->RArm.PermDmg)
		player->RArm.Dmg = player->RArm.PermDmg;
	if (player->LArm.Dmg < player->LArm.PermDmg)
		player->LArm.Dmg = player->LArm.PermDmg;
}

void CheckBleeding(character *player)
{
	if (player->StopBleeding)
	{
		player->Bleeding = false;
		player->HeavyBleeding = false;
	}
	if (player->Bleeding && !player->ResistBleeding)
		++player->Vitals.Dmg;
	if (player->HeavyBleeding && !player->ResistBleeding)
		++player->Vitals.Dmg;

	player->ResistBleeding = false;
	player->StopBleeding = false;
}

void CheckFire(character *player)
{
	bool FireOverrun = false;

	if (player->OnFire > 0)
	{
		++player->Vitals.Dmg;
		if (player->OnFire > 1)
		{
			++player->Vitals.Dmg;
			if (player->OnFire > 2)
			{
				++player->Vitals.Dmg;
				++player->Vitals.PermDmg;
			}
		}
	}
	/*
	if (player->RArm.OnFire)
	{
	if(player->RArm.Dmg >= 6)
	FireOverrun = true;
	else
	{
	++player->RArm.Dmg;
	//++player->RArm.PermDmg;
	++player->RArm.Dmg;
	++player->RArm.PermDmg;
	}
	}
	if (player->LArm.OnFire)
	{
	if(player->LArm.Dmg >= 6)
	FireOverrun = true;
	else
	{
	++player->LArm.Dmg;
	//++player->LArm.PermDmg;
	++player->LArm.Dmg;
	++player->LArm.PermDmg;
	}
	}
	if (player->RLeg.OnFire)
	{
	if(player->RLeg.Dmg >= 6)
	FireOverrun = true;
	else
	{
	++player->RLeg.Dmg;
	//++player->RLeg.PermDmg;
	++player->RLeg.Dmg;
	++player->RLeg.PermDmg;
	}
	}
	if (player->LLeg.OnFire)
	{
	if(player->LLeg.Dmg >= 6)
	FireOverrun = true;
	else
	{
	++player->LLeg.Dmg;
	//++player->LLeg.PermDmg;
	++player->LLeg.Dmg;
	++player->LLeg.PermDmg;
	}
	}
	if (player->Vitals.OnFire)
	{
	++player->Vitals.Dmg;
	//++player->Vitals.PermDmg;
	++player->Vitals.Dmg;
	++player->Vitals.PermDmg;
	}
	*/
}

void CheckIce(character *player)
{
	if (player->Frozen >= 3)
		;// ++player->Vitals.Dmg;
	/*
	int TempIceLimbs = 0;
	if(player->RArm.Frozen)
	++TempIceLimbs;
	if(player->LArm.Frozen)
	++TempIceLimbs;
	if(player->RLeg.Frozen)
	++TempIceLimbs;
	if(player->LLeg.Frozen)
	++TempIceLimbs;

	player->IceLimbs = TempIceLimbs;
	*/
}

void CheckElec(character* player)
{
}

void DetermineHitLocation(character *player)
{

}

void EndStep(character *player)
{
	CheckFire(player);
	CheckIce(player);
	CheckElec(player);
	CheckBleeding(player);
	CheckDamage(player);
	CheckExertion(player);

	if (player->Target->Active)
		player->ExecutePos = false;
}

void ApplyStatus(character *player)
{
	player->Exerting = false;
	player->Active = false;
}

void CheckDeath(character *player)
{
	if (player->Vitals.Dmg >= 6)
	{
		player->Wounded = true;
		player->Dead = true;
		if (LOGGING && !player->Dead)
		{
			NameToString(player->Name);
			cout << " has been Killed.\n";
		}
	}

	if (((player->RArm.crippled) && (player->LArm.crippled)) || (player->Blinded))
	{
		if (LOGGING)
		{
			NameToString(player->Name);
			cout << " is too fucked up to fight.\n";
		}
		player->Wounded = true;
		player->Dead = true;
	}
}

void RemoveFire(character *player)
{
	//player->ResistFire = true;
	int temprmvfire = player->Rolls.RmvFireValue;
	player->OnFire -= temprmvfire;
	if (player->OnFire < 0)
		player->OnFire = 0;
	/*
	if (temprmvfire >= 2)
	{
	player->Vitals.OnFire = false;
	player->RArm.OnFire = false;
	player->LArm.OnFire = false;
	player->RLeg.OnFire = false;
	player->LLeg.OnFire = false;
	}
	*/
}

void RemoveIce(character *player)
{
	int temprmvice = player->Rolls.RmvIceValue;
	player->Frozen -= temprmvice;
	if (player->Frozen < 0)
		player->Frozen = 0;
	/*
	if (temprmvice >= 2)
	{
	player->Frozen = false;
	player->RArm.Frozen = false;
	player->LArm.Frozen = false;
	player->RLeg.Frozen = false;
	player->LLeg.Frozen = false;
	}
	*/
}

void Unstun(character *player)
{
	int tempunstun = player->Rolls.UnstunValue;

	if (tempunstun >= 1)
	{
		player->Shock = false;
	}

	if (tempunstun >= 2)
	{
		player->Stunned = false;
		player->Stunned2 = false;
	}
	else if (tempunstun == 1)
	{	
		if (!player->Stunned2)
			player->Stunned = false;
		else
		{
			player->Stunned = true;
			player->Stunned2 = false;
		}
	}
}

void Rest(character *player)
{
	player->Exertion -= player->Rolls.RestValue;
	if (player->Exertion < 0)
		player->Exertion = 0;
}

void Survive(character *player)
{
	int TempSurvive = player->Rolls.SurviveValue;

	if (player->Bleeding && !player->HeavyBleeding)
	{
		player->ResistBleeding = true;
		--TempSurvive;
	}
	else if (player->HeavyBleeding && TempSurvive >= 2)
	{
		player->ResistBleeding = true;
		--TempSurvive;
		--TempSurvive;
	}

	while (TempSurvive > 0 && player->ResistBleeding)
	{
		player->StopBleeding = true;
		--TempSurvive;
	}
}

void Recover(character *player)
{
	int TempRecov = player->Rolls.RecoverValue;

	while (TempRecov > 0)
	{
		bool healed = false;

		if (player->Vitals.Dmg > 0 && player->Vitals.Dmg <= player->Vitals.PermDmg)
		{
			--player->Vitals.Dmg;
			healed = true;
		}
		else if (player->RLeg.Dmg > 0 && player->RLeg.Dmg <= player->RLeg.PermDmg)
		{
			--player->RLeg.Dmg;
			healed = true;
		}
		else if (player->LLeg.Dmg > 0 && player->LLeg.Dmg <= player->LLeg.PermDmg)
		{
			--player->LLeg.Dmg;
			healed = true;
		}
		else if (player->RArm.Dmg > 0 && player->RArm.Dmg <= player->RArm.PermDmg)
		{
			--player->RArm.Dmg;
			healed = true;
		}
		else if (player->LArm.Dmg > 0 && player->LArm.Dmg <= player->LArm.PermDmg)
		{
			--player->LArm.Dmg;
			healed = true;
		}

		--TempRecov;
	}
}

void RollValues(character *player)
{
	InitRolls(&player->Rolls);
	bool Prime;
	for (int ActionNum = 0; ActionNum < 3; ++ActionNum)
	{
		if (player->Actions[ActionNum].ActionType == noaction)
		{
		}
		else
		{
			if (ActionNum == 0 && (player->Fatigue == 0))
				Prime = true;
			else
				Prime = false;

			if (player->Actions[ActionNum].ActionType == strike)
			{
				if (Prime)
					player->Rolls.HitValue = Check(DetermineHitSkill(player), 1);
				else
					player->Rolls.HitValue = Check(DetermineHitSkill(player), 0);

				if (!player->Disarmed)
					player->Rolls.HitValue += player->StrikeSuccess;
				if (player->Stunned)
					--player->Rolls.HitValue;
				if (player->Stunned2)
					--player->Rolls.HitValue;
				if (player->Stunned3)
					--player->Rolls.HitValue;
				if (player->IceLimbs > 0);
				player->Rolls.HitValue -= player->IceLimbs;
				if (player->RArm.Dmg > 3 && player->RArm.Dmg < 6)
				{
					++player->RArm.PermDmg;
				}
				if (player->RArm.Dmg >= 6 || player->RArm.Frozen)
				{
					--player->Rolls.HitValue;
				}
				int j = 0;
				if (player->Rolls.HitValue < 0)
					j++;
				if (player->Rolls.HitValue > 0)
				{
					DetermineDamageValues(player, Prime, false);
				}
				j++;
			}
			else if (player->Actions[ActionNum].ActionType == dodge)
			{
				if (Prime)
					player->Rolls.DodgeValue = Check(DetermineDodgeSkill(player), 2) + player->DodgeSuccess;
				else
					player->Rolls.DodgeValue = Check(DetermineDodgeSkill(player), 0) + player->DodgeSuccess;
				if (player->Stunned)
					--player->Rolls.DodgeValue;
				if (player->Stunned2)
					--player->Rolls.DodgeValue;
				if (player->Stunned3)
					--player->Rolls.DodgeValue;
				if (player->Prone)
					--player->Rolls.DodgeValue;
				if (player->IceLimbs > 0);
				player->Rolls.DodgeValue -= player->IceLimbs;
			}
			else if (player->Actions[ActionNum].ActionType == rest)
			{
				if (Prime)
					player->Rolls.RestValue = Check(DetermineVitSkill(player), 2);
				else
					player->Rolls.RestValue = Check(DetermineVitSkill(player), 2);
				if (player->Fit)
					++player->Rolls.RestValue;
			}
			else if (player->Actions[ActionNum].ActionType == fullrest)
			{
				player->Rolls.RestValue = Check(DetermineVitSkill(player), 2) + 1;
				if (player->Fit)
					++player->Rolls.RestValue;
			}
			else if (player->Actions[ActionNum].ActionType == recover)
			{
				if (Prime)
					player->Rolls.RecoverValue = Check(DetermineVitSkill(player), 2);
				else
					player->Rolls.RecoverValue = Check(DetermineVitSkill(player), 0);
			}
			else if (player->Actions[ActionNum].ActionType == survive)
			{
				if (Prime)
					player->Rolls.SurviveValue = Check(DetermineVitSkill(player), 2);
				else
					player->Rolls.SurviveValue = Check(DetermineVitSkill(player), 0);
			}
			else if (player->Actions[ActionNum].ActionType == rmvfire)
			{
				if (Prime)
					player->Rolls.RmvFireValue = Check(DetermineRmvFireSkill(player), 2);
				else
					player->Rolls.RmvFireValue = Check(DetermineRmvFireSkill(player), 0);
			}
			else if (player->Actions[ActionNum].ActionType == rmvice)
			{
				if (Prime)
					player->Rolls.RmvIceValue = Check(DetermineRmvIceSkill(player), 2);
				else
					player->Rolls.RmvIceValue = Check(DetermineRmvIceSkill(player), 0);
			}
			else if (player->Actions[ActionNum].ActionType == unstun)
			{
				if (Prime)
					player->Rolls.UnstunValue = Check(player->VitSkill, 2);
				else
					player->Rolls.UnstunValue = Check(player->VitSkill, 0);
			}
			else if (player->Actions[ActionNum].ActionType == stand)
			{
				if (Prime)
					player->Rolls.StandValue = Check(player->DodgeSkill, 2) + 1;
				else
					player->Rolls.StandValue = Check(player->DodgeSkill, 0) + 1;
				if (player->IceLimbs > 0);
				player->Rolls.StandValue -= player->IceLimbs;
				if (player->Stunned)
					--player->Rolls.StandValue;
			}
			else if (player->Actions[ActionNum].ActionType == pickupitem)
			{
				if (Prime)
					player->Rolls.PickUpItemValue = Check(player->DodgeSkill, 2) + 1;
				else
					player->Rolls.PickUpItemValue = Check(player->DodgeSkill, 0) + 1;
				if (player->IceLimbs > 0);
				player->Rolls.PickUpItemValue -= player->IceLimbs;
				if (player->Stunned)
					--player->Rolls.PickUpItemValue;
			}
			else if (player->Actions[ActionNum].ActionType == execute)
			{
				player->Rolls.HitValue = Check(DetermineHitSkill(player), Prime) + player->StrikeSuccess;
				player->Damage.DamageAmount = 1 + (Check(DetermineDmgSkill(player), Prime) + player->WeaponSuccess);
				player->Damage.DamageVital = true;
				player->Damage.ExDmgAmount = Check(player->MagSkill, Prime) + player->ExDmgSuccess;
				player->Damage.BArea = Head;
			}
			if (player->Actions[ActionNum].exert)
				player->Exerting = true;
			if (player->Actions[ActionNum].active)
				player->Active = true;
		}
	}
	if (player->Exerting)
	{
		if (player->Vitals.Dmg > 3)
			++player->Vitals.PermDmg;
		if (player->RLeg.Dmg > 3)
			++player->RLeg.PermDmg;
		if (player->LLeg.Dmg > 3)
			++player->LLeg.PermDmg;
		if (player->RArm.Dmg > 3)
			++player->RArm.PermDmg;
		if (player->LArm.Dmg > 3)
			++player->LArm.PermDmg;
	}

	//if (LOGGING)
	//ActionValuesToString(player);
}

void ApplyAction(character *player, character *target)
{
	if (LOGGING && player->Rolls.HitValue == 0 &&
		((player->Actions[0].ActionType == strike) ||
		(player->Actions[1].ActionType == strike) ||
		(player->Actions[2].ActionType == strike)))
	{
		NameToString(player->Name);
		cout << " misses.\n";
	}
	if (player->Rolls.DodgeValue > 0)
	{
		player->Target->ExecutePos = false;
	}
	if (player->Rolls.RecoverValue > 0)
	{
		Recover(player);
	}
	if (player->Rolls.SurviveValue > 0)
	{
		Survive(player);
	}
	if (player->Rolls.RmvFireValue > 0)
	{
		RemoveFire(player);
	}
	if (player->Rolls.RmvIceValue > 0)
	{
		RemoveIce(player);
	}
	if (player->Rolls.UnstunValue > 0)
	{
		Unstun(player);
	}
	if (player->Rolls.HitValue > 0)
	{
		Attack(player, target);
	}
	if (player->Rolls.RestValue > 0)
	{
		Rest(player);
	}
	if (player->Rolls.StandValue > 0)
	{
		player->Prone = false;
	}
	if (player->Rolls.PickUpItemValue > 0)
	{
		player->Disarmed = false;
	}
	if (player->Actions[0].ActionType == mvtoexecute)
	{
		player->ExecutePos = true;
		if (LOGGING)
		{
			NameToString(player->Name);
			cout << " prepares to execute.\n";
		}
	}
	if (LOGGING)
		ActionValuesToString(player);
}

void CopyActionDB(actionDB *TempActionDB, actionDB* ActionDB)
{
	TempActionDB->TotalActions = 0;
	for (int i = 0; i < ActionDB->TotalActions; ++i)
	{
		TempActionDB->ActionList[i].ActionType = ActionDB->ActionList[i].ActionType;
		TempActionDB->ActionList[i].weight = ActionDB->ActionList[i].weight;
		TempActionDB->ActionList[i].AP = ActionDB->ActionList[i].AP;
		TempActionDB->ActionList[i].EP = ActionDB->ActionList[i].EP;
		TempActionDB->ActionList[i].SP = ActionDB->ActionList[i].SP;
		++TempActionDB->TotalActions;
	}

	ResetActionUse(TempActionDB);
}

void AdjustActionWeight(character *player, actiontype ActionType, int WeightAdjust)
{
	for (int i = 0; i < TOTALACTIONS; ++i)
	{
		if (player->TempActionDB.ActionList[i].ActionType == ActionType)
		{
			player->TempActionDB.ActionList[i].weight = WeightAdjust;
		}
	}
}

void ChooseActions(character* player)
{
	CopyActionDB(&player->TempActionDB, &player->ActionDB);

	int TempTotalActionSlots = 3;
	int TempActiveSlots = 2;
	int TempMoveSlots = 1;

	if (player->Frozen >= 1)
	{
		--TempActiveSlots;
		
		if (player->Frozen >= 2)
		{
			--TempActiveSlots;
			if (player->Frozen >= 3)
			{
				--TempMoveSlots;
			}
		}
	}

	if (player->Shock)
	{
		--TempActiveSlots;
	}

	int choice = 0;
	actiontype ActionChoices[300];
	player->Actions[0] = AllActionDB.ActionList[noaction];
	player->Actions[1] = AllActionDB.ActionList[noaction];
	player->Actions[2] = AllActionDB.ActionList[noaction];

	if (player->Blinded)
	{
		player->Actions[0] = AllActionDB.ActionList[noaction];
		player->Actions[1] = AllActionDB.ActionList[noaction];
		player->Actions[2] = AllActionDB.ActionList[noaction];
	}
	else if (player->Exertion >= 12)
	{
		player->Actions[0] = AllActionDB.ActionList[rest];
		player->Actions[1] = AllActionDB.ActionList[noaction];
		player->Actions[2] = AllActionDB.ActionList[noaction];
	}
	else if (player->ExecutePos)
	{
		player->Actions[0] = AllActionDB.ActionList[execute];
		player->Actions[1] = AllActionDB.ActionList[noaction];
		player->Actions[2] = AllActionDB.ActionList[noaction];
	}
	/*
	else if (player->Frozen || (player->RArm.Frozen && player->LArm.Frozen))
	{
	player->Actions[0] = AllActionDB.ActionList[rmvice];
	player->Actions[1] = AllActionDB.ActionList[rest];
	player->Actions[2] = AllActionDB.ActionList[noaction];
	player->Exertion += AllActionDB.ActionList[rmvice].EP;
	}
	*/
	else
	{
		if (player->Vitals.Dmg > 3)
			AdjustActionWeight(player, recover, 50);

		if (player->Bleeding)
			AdjustActionWeight(player, survive, 50);

		if (player->Exertion > 3)
			AdjustActionWeight(player, rest, 40);

		if (player->Stunned)
			AdjustActionWeight(player, unstun, 50);

		if (player->Shock)
			AdjustActionWeight(player, unstun, 50);

		if (player->Prone && !player->Crippled)
			AdjustActionWeight(player, stand, 40);

		if (player->Disarmed && player->RArm.Dmg < 6)
			AdjustActionWeight(player, pickupitem, 40);

		if (player->OnFire > 0)
			AdjustActionWeight(player, rmvfire, 25);
		if (player->OnFire > 1)
			AdjustActionWeight(player, rmvfire, 50);
		if (player->OnFire > 2)
			AdjustActionWeight(player, rmvfire, 65);

		if (player->Frozen > 0)
			AdjustActionWeight(player, rmvice, 25);
		if (player->Frozen > 1)
			AdjustActionWeight(player, rmvice, 50);
		if (player->Frozen > 2)
			AdjustActionWeight(player, rmvice, 65);

		/*
		if (player->LArm.OnFire)
		AdjustActionWeight(player, rmvfire, 25);
		if (player->RArm.OnFire || player->RLeg.OnFire || player->LLeg.OnFire)
		AdjustActionWeight(player, rmvfire, 40);
		if (player->Vitals.OnFire)
		AdjustActionWeight(player, rmvfire, 65);
		*/
		/*
		if (player->LArm.Frozen)
		AdjustActionWeight(player, rmvice, 25);
		if (player->RArm.Frozen || player->RLeg.Frozen || player->LLeg.Frozen)
		AdjustActionWeight(player, rmvice, 50);
		*/
		/*
		if (player->Target->Frozen && !player->Frozen)
		{
		AdjustActionWeight(player, mvtoexecute, 40);
		}
		*/

		if (player->Target->ExecutePos)
		{
			AdjustActionWeight(player, recover, 0);
			AdjustActionWeight(player, rest, 0);
			AdjustActionWeight(player, dodge, 25);
		}

		//for (int ActionNum = 0; ActionNum < player->CurrentActionLimit; ++ActionNum)
		int FailSafe = 0;
		int ActionNum = 0;
		while (TempTotalActionSlots > 0)
		{
			int WeightNum = 0;
			for (int j = 0; j < player->TempActionDB.TotalActions; ++j)
			{
				if (!player->TempActionDB.ActionList[j].used)
				{
					int ActionWeight = 0;
					ActionWeight = player->TempActionDB.ActionList[j].weight;

					for (int i = WeightNum; i < WeightNum + ActionWeight; ++i)
					{
						ActionChoices[i] = player->TempActionDB.ActionList[j].ActionType;
					}
					WeightNum += ActionWeight;
				}
			}
			int ActionChoice = rand() % WeightNum;
			if (AllActionDB.ActionList[ActionChoices[ActionChoice]].EP <= (11 - player->Exertion - player->Fatigue) &&
				AllActionDB.ActionList[ActionChoices[ActionChoice]].SP <= (6 - player->Spirit) &&
				//AllActionDB.ActionList[ActionChoices[ActionChoice]].AP <= TempAP)
				(
				AllActionDB.ActionList[ActionChoices[ActionChoice]].AC <= TempActiveSlots &&
				AllActionDB.ActionList[ActionChoices[ActionChoice]].MC <= TempMoveSlots &&
				AllActionDB.ActionList[ActionChoices[ActionChoice]].PC
				+ AllActionDB.ActionList[ActionChoices[ActionChoice]].MC
				+ AllActionDB.ActionList[ActionChoices[ActionChoice]].AC <= TempTotalActionSlots
				))
			{
				player->Actions[ActionNum] = AllActionDB.ActionList[ActionChoices[ActionChoice]];
				player->Exertion += AllActionDB.ActionList[ActionChoices[ActionChoice]].EP;
				if (player->Exertion > 6)
				{
					player->Fatigue += (player->Exertion - 6);
				}
				player->Spirit += AllActionDB.ActionList[ActionChoices[ActionChoice]].SP;

				TempActiveSlots -= AllActionDB.ActionList[ActionChoices[ActionChoice]].AC;
				TempMoveSlots -= AllActionDB.ActionList[ActionChoices[ActionChoice]].MC;
				TempTotalActionSlots -= AllActionDB.ActionList[ActionChoices[ActionChoice]].PC;
				TempTotalActionSlots -= AllActionDB.ActionList[ActionChoices[ActionChoice]].AC;
				TempTotalActionSlots -= AllActionDB.ActionList[ActionChoices[ActionChoice]].MC;

				for (int k = 0; k < player->TempActionDB.TotalActions; ++k)
				{
					if (player->Actions[ActionNum].ActionType == player->TempActionDB.ActionList[k].ActionType)
					{
						player->TempActionDB.ActionList[k].used = true;
					}
				}
				++ActionNum;
			}
			++FailSafe;
			if (FailSafe > 50)
				TempTotalActionSlots = 0;
			if (ActionNum > 3)
				TempTotalActionSlots = 0;
		}
	}

	ResetActionUse(&player->TempActionDB);
}

void Survive1(character *player)
{
	/*
	while (((player->FireTotal > 0) || (player->Vitals.bleeding > 0) || (player->IceTotal > 3))
	&& (!(player->Dead)))
	{
	if (LOGGING)
	cout << "::Survive::\n";
	bool fireprime = true;
	bool iceprime = false;
	if ((player->Vitals.bleeding > player->FireTotal) || (player->FireTotal <= 0))
	fireprime = false;
	if ((player->FireTotal == 0) && (player->Vitals.bleeding == 0))
	iceprime = true;

	InitRolls(&player->Rolls);

	if (player->FireTotal > 0)
	player->Rolls.RmvFireValue = Check(DetermineRmvFireSkill(player), fireprime);
	if (player->Vitals.bleeding > 0)
	player->Rolls.RecoverValue = Check(player->VitSkill, fireprime);
	if (player->IceTotal > 3)
	player->Rolls.RmvIceValue = Check(player->DmgSkill, iceprime);

	if (player->Rolls.RmvFireValue > 0)
	{
	RemoveFire(player);
	}
	if (player->Rolls.RecoverValue > 0)
	{
	Recover(player);
	}
	if (player->Rolls.RmvIceValue > 0)
	{
	RemoveIce(player);
	}
	CheckBleeding(player);
	CheckFire(player);
	CheckIce(player);

	if (LOGGING)
	{
	if (player->FireTotal > 0)
	cout << "RF" << player->Rolls.RmvFireValue << " Fire" << player->FireTotal
	<< " W" << player->Vitals.damage << "    ";
	if (player->Vitals.bleeding > 0)
	cout << "Rec" << player->Rolls.RecoverValue << " Bleed" << player->Vitals.bleeding
	<< " BL" << player->BleedingFails << "    ";
	if (player->IceTotal > 3)
	cout << "RI" << player->Rolls.RmvIceValue << " Ice" << player->IceTotal
	<< " W" << player->Vitals.damage << "     ";
	cout << '\n';
	}

	CheckDeath(player);
	}
	*/
}

int main()
{
	srand(time(NULL));

	LOGGING = true;
	bool GRID = true;

	int times = 100;
	if (!LOGGING)
		times = 1000;

	ofstream DataOut;
	DataOut.open("combatmatrix.csv");
	DataOut << ',' << endl;

	InitAllActionDB();
	InitDefActionDB(DefActionDB);

	InitCharList();

	chargroup ElementGroup;
	ElementGroup.GroupName = elementgroup;
	ElementGroup.Group[0] = CharList[Normal];
	ElementGroup.Group[1] = CharList[BashMan];
	ElementGroup.Group[2] = CharList[SlashMan];
	ElementGroup.Group[3] = CharList[Ninja];
	ElementGroup.Group[4] = CharList[StrongMan];
	ElementGroup.Group[5] = CharList[FireMan];
	ElementGroup.Group[6] = CharList[IceMan];
	ElementGroup.Group[7] = CharList[ElecMan];
	ElementGroup.Group[8] = CharList[FireBattleMage];
	ElementGroup.Group[9] = CharList[IceBattleMage];
	ElementGroup.Group[10] = CharList[ElecBattleMage];
	ElementGroup.Group[11] = CharList[Batman];
	ElementGroup.GroupTotal = 12;


	bool roundbuffing = false;
	int roundbuffer = 4;

	int Team1Wins = 0;
	int Team2Wins = 0;
	int TeamTies = 0;
	int TotalTimes = times * GROUPSIZE;

	float CombatAvg[40];
	for (int i = 0; i < 40; ++i)
		CombatAvg[i] = 0;

	chargroup Team1;
	chargroup Team2;
	character Fighter1;
	character Fighter2;

	Team1 = ElementGroup;
	Team2 = ElementGroup;

	int Team1Fighters = Team1.GroupTotal;
	int Team2Fighters = Team2.GroupTotal;
	if (LOGGING)
	{
		Team1Fighters = 1;
		Team2Fighters = 1;
	}

	DataOut << ',';
	for (int Fighter1Num = 0; Fighter1Num < Team1Fighters; ++Fighter1Num)
	{
		DataOutName(&DataOut, Team1.GroupName, Team1.Group[Fighter1Num].Name);
		DataOut << ',';
	}
	DataOut << endl;

	for (int Fighter2Num = 0; Fighter2Num < Team2Fighters; ++Fighter2Num)
	{
		DataOutName(&DataOut, Team2.GroupName, Team2.Group[Fighter2Num].Name);
		DataOut << ',';

		for (int Fighter1Num = 0; Fighter1Num < Team1Fighters; ++Fighter1Num)
		{
			Fighter1 = Team1.Group[Fighter1Num];
			Fighter2 = Team2.Group[Fighter2Num];
			Fighter1.Target = &Fighter2;
			Fighter2.Target = &Fighter1;

			if (LOGGING)
			{
				Fighter1 = CharList[SlashMan];
				Fighter2 = CharList[BashMan];
				Fighter1.Target = &Fighter2;
				Fighter2.Target = &Fighter1;
			}

			int round = 1;

			int woundtotalrounds = 0;
			int woundties = 0;
			int woundrounds1to3 = 0;
			int woundrounds4to7 = 0;
			int woundrounds8to9 = 0;
			int woundrounds10to14 = 0;
			int woundrounds15plus = 0;

			int deathties = 0;
			int deathtotalrounds = 0;
			int deathrounds1to3 = 0;
			int deathrounds4to7 = 0;
			int deathrounds8to9 = 0;
			int deathrounds10to14 = 0;
			int deathrounds15plus = 0;

			for (int i = 0; i < times; i++)
			{
				round = 1;
				CharacterInit(&Fighter1);
				CharacterInit(&Fighter2);
				bool WoundOver = false;
				bool deadcheck = true;

				while (deadcheck)
				{
					if (LOGGING)
						cout << "///" << round << "\\\\\\ \n;";

					InitDamage(&Fighter1.Damage);
					InitDamage(&Fighter2.Damage);

					bool breakround = false;
					if (roundbuffing)
					{
						if (round % roundbuffer == 0)
							breakround = true;
					}

					if (!breakround)
					{
						ChooseActions(&Fighter1);
						ChooseActions(&Fighter2);
						if (LOGGING)
							cout << ":Rolls:\n";
						RollValues(&Fighter1);
						RollValues(&Fighter2);
						if (LOGGING)
							cout << ":Effect:\n";
						ApplyAction(&Fighter1, &Fighter2);
						ApplyAction(&Fighter2, &Fighter1);
					}

					if (LOGGING)
						cout << ":Status:\n";
					EndStep(&Fighter1);
					EndStep(&Fighter2);

					ApplyDamage(Fighter1.Target, Fighter1.Damage);
					ApplyDamage(Fighter2.Target, Fighter2.Damage);

					ApplyStatus(&Fighter1);
					ApplyStatus(&Fighter2);

					CheckDeath(&Fighter1);
					CheckDeath(&Fighter2);

					if (LOGGING)
					{
						PrintDamage(&Fighter1);
						PrintDamage(&Fighter2);
					}

					++round;

					/*
					if (round > 50)
					{
					Fighter1.Dead = true;
					Fighter2.Dead = true;
					}


					if (Fighter1.Dead)
					Survive(&Fighter2);
					if (Fighter2.Dead)
					Survive(&Fighter1);

					/*
					if ((Fighter1.Wounded || Fighter2.Wounded) && (!WoundOver))
					{
					woundtotalrounds += (round - 1);
					if (round <= 3)
					++woundrounds1to3;
					else if (round >= 4 && round <= 7)
					++woundrounds4to7;
					else if (round >= 8 && round <= 9)
					++woundrounds8to9;
					else if (round >= 10 && round <= 14)
					++woundrounds10to14;
					else
					++woundrounds15plus;

					if (LOGGING)
					cout << "!!!!! Wound Match Over, ";

					if (Fighter1.Wounded && Fighter2.Wounded)
					{
					++woundties;
					if (LOGGING)
					cout << "TIE";
					}
					else if (Fighter2.Wounded && !Fighter1.Wounded)
					{
					++Fighter1.WoundWins;
					if (LOGGING)
					{
					NameToString(Fighter1.Name);
					cout << "Wins";
					}
					}
					else if (Fighter1.Wounded && !Fighter2.Wounded)
					{
					++Fighter2.WoundWins;
					if (LOGGING)
					{
					NameToString(Fighter2.Name);
					cout << "Wins";
					}
					}
					if (LOGGING)
					cout << " !!!!!\n";
					WoundOver = true;
					}
					*/

					deadcheck = (!Fighter2.Dead) && (!Fighter1.Dead);

					if (round > 50)
						deadcheck = false;
				}
				deathtotalrounds += (round - 1);
				if (round <= 3)
					++deathrounds1to3;
				else if (round >= 4 && round <= 7)
					++deathrounds4to7;
				else if (round >= 8 && round <= 9)
					++deathrounds8to9;
				else if (round >= 10 && round <= 14)
					++deathrounds10to14;
				else
					++deathrounds15plus;

				if (Fighter1.Dead && Fighter2.Dead)
					++deathties;
				if (Fighter2.Dead && !Fighter1.Dead)
					++Fighter1.DeathWins;
				if (Fighter1.Dead && !Fighter2.Dead)
					++Fighter2.DeathWins;

				if (LOGGING)
				{
					cout << "\n";
					cout << "Rounds: " << round - 1 << "\n";
					if (Fighter1.Dead)
					{
						NameToString(Fighter1.Name);
						cout << " is defeated\n";
					}
					if (Fighter2.Dead)
					{
						NameToString(Fighter2.Name);
						cout << " is defeated.\n";
					}

					cout << "\n";
					NameToString(Fighter1.Name);
					cout << " Status: ";
					PrintStatus(&Fighter1);
					NameToString(Fighter2.Name);
					cout << " Status: ";
					PrintStatus(&Fighter2);
					cout << "\n\n";
				}
				if (LOGGING)
					cin.get();
			}

			if (LOGGING)
			{
				cout << "Char Type: ";
				CharTypeToString(Fighter1.CharType);
				cout << '\n';
				cout << "Average Rounds : Wound:" << (((float)woundtotalrounds) / ((float)times))
					<< ", Death:" << (((float)deathtotalrounds) / ((float)times)) << "\n";
				cout << "Rounds 1 - 3   : Wound:" << (((float)woundrounds1to3 / (float)times) * 100)
					<< "%, Death:" << (((float)deathrounds1to3) / ((float)times) * 100) << "%\n";
				cout << "Rounds 4 - 7   : Wound:" << (((float)woundrounds4to7 / (float)times) * 100)
					<< "%, Death:" << (((float)deathrounds4to7) / ((float)times) * 100) << "%\n";
				cout << "Rounds 8 - 9   : Wound:" << (((float)woundrounds8to9 / (float)times) * 100)
					<< "%, Death:" << (((float)deathrounds8to9) / ((float)times) * 100) << "%\n";
				cout << "Rounds 10 - 14 : Wound:" << (((float)woundrounds10to14 / (float)times) * 100)
					<< "%,  Death:" << (((float)deathrounds10to14) / ((float)times) * 100) << "%\n";
				cout << "Rounds 15+     : Wound:" << (((float)woundrounds15plus / (float)times) * 100)
					<< "%,  Death:" << (((float)deathrounds15plus) / ((float)times) * 100) << "%\n";
				cout << "\n";

				NameToString(Fighter1.Name);
				cout << " Wins: Wound:" << Fighter1.WoundWins << " (" << ((float)Fighter1.WoundWins / (float)times) * 100
					<< "%), Death:" << Fighter1.DeathWins << " (" << ((float)Fighter1.DeathWins / (float)times) * 100 << "%)\n";
				NameToString(Fighter2.Name);
				cout << " Wins: Wound:" << Fighter2.WoundWins << " (" << ((float)Fighter2.WoundWins / (float)times) * 100
					<< "%), Death:" << Fighter2.DeathWins << " (" << ((float)Fighter2.DeathWins / (float)times) * 100 << "%)\n";
				cout << "       Ties: Wound:" << woundties << "  (" << ((float)woundties / (float)times) * 100
					<< "%),  Death:" << deathties << " (" << ((float)deathties / (float)times) * 100 << "%)\n";
				cout << "\n";
			}
			Team1Wins += Fighter1.DeathWins;
			Team2Wins += Fighter2.DeathWins;
			TeamTies += deathties;

			float Diff;
			float Fighter1Per = ((float)Fighter1.DeathWins / (float)times) * 100;
			float Fighter2Per = ((float)Fighter2.DeathWins / (float)times) * 100;
			Diff = (Fighter1Per - Fighter2Per) / 100;
			DataOut << Diff << ',';
			CombatAvg[Fighter1Num] += Diff;
		}

		if (!LOGGING)
		{
			cout << "Final Totals\n";
			GroupNameToString(Team1.GroupName);
			cout << ": " << ((float)Team1Wins / (float)TotalTimes) * 100 << "%\n";
			GroupNameToString(Team2.GroupName);
			cout << ": " << ((float)Team2Wins / (float)TotalTimes) * 100 << "%\n";
			cout << "Ties: " << ((float)TeamTies / (float)TotalTimes) * 100 << "%\n";
		}

		DataOut << endl;
	}

	DataOut << "Average" << ',';
	for (int i = 0; i < Team2Fighters; ++i)
	{
		DataOut << (CombatAvg[i] / (Team2Fighters + 1)) << ',';
	}
	DataOut << endl;

	float GroupTotalAvg = 0;
	for (int i = 0; i < Team2Fighters; ++i)
	{
		GroupTotalAvg += CombatAvg[i];
	}
	DataOut << "Total" << ',' << (GroupTotalAvg / (Team2Fighters + 1));

	DataOut.close();
	cout << "Done";
	cin.get();
}