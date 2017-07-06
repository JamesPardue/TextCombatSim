#if !defined(COMSTRUCT_H)
#define COMSTRUCT_H

static const int TOTALACTIONS = 20;
static const int GROUPSIZE = 20;
static const int TOTALCHARACTERS = 40;

enum groupname
{
	stdgroup,
	cutgroup,
	firegroup,
	icegroup,
	elecgroup,
	elementgroup
};

enum actiontype
{
	noaction,
	strike,
	dodge,
	recover,
	survive,
	rest,
	fullrest,
	rmvfire,
	rmvice,
	mvtoexecute,
	execute,
	unstun,
	stand,
	pickupitem
};

enum trauma
{
	HeadTrauma,
	TorsoTrauma,
	BloodLossTrauma,
	LimbTrauma,
	BurnTrauma,
	IceTrauma,
};

enum dmgtype
{
	None,
	Dmg,
	Bash,
	Slash,
	Thrust,
	Pierce,
	Clamp,
	Crush,
	EDmg,
	Fire,
	OnFire,
	Ice,
	Frozen,
	Elec,
	Stun,
	Acid,
};

enum directions
{
	Left,
	Right
};

enum charactername
{
	Normal,
	BashMan,
	SlashMan,
	ThrustMan,
	PierceMan,
	ClampMan,
	CrushMan,
	EDmgMan,
	FireMan,
	IceMan,
	ElecMan,
	AcidMan,

	ArmorGuy,
	Ninja,
	StrongMan,
	FireMage,
	IceMage,
	ElecMage,
	FireBattleMage,
	IceBattleMage,
	ElecBattleMage,
	Batman,
};

enum charactertype
{

};

enum limbtype
{
	Vital,
	Head,
	Torso,
	LArm,
	RArm,
	LLeg,
	RLeg,
	Eyes,
	Miss,
};

struct damage
{
	int DamageType;
	int DamageAmount;

	int ExDmgType;
	int ExDmgAmount;

	int SEType;
	int SEAmount;

	int BArea;
	bool DamageVital;
};

struct vitals
{
	int Dmg;
	int PermDmg;
	bool OnFire;
};

struct limb
{
	int Dmg;
	int PermDmg;
	bool crippled;
	bool severed;
	int Frozen;
	bool OnFire;
};

struct sense
{
	int damage;
	int redundancy;
	bool damaged;
};

struct rolls
{
	int HitValue;
	int DodgeValue;
	int RecoverValue;
	int SurviveValue;
	int RestValue;
	int RmvFireValue;
	int RmvIceValue;
	int UnstunValue;
	int StandValue;
	int PickUpItemValue;
};

struct weight
{
	int min;
	int max;
};

struct armor
{
	int BodyArea;
	bool Armored;
	int PaddingTotal;
	int PaddingRemaining;
	int DR;
	int DamageTotal;
	int DamageRemaining;
};

struct action
{
	actiontype ActionType;
	bool used;
	int weight;
	bool exert;
	bool active;

	int AP;

	int AC;
	int MC;
	int PC;

	int EP;
	int SP;
};

struct actionDB
{
	action ActionList[TOTALACTIONS];
	int TotalActions;
};

struct point
{
	int X;
	int Y;
};

struct character
{
	charactername Name;
	charactertype CharType;
	int WoundWins;
	int DeathWins;

	vitals Vitals;
	limb LArm;
	limb RArm;
	limb LLeg;
	limb RLeg;
	sense Eyes;

	bool Bleeding;
	bool HeavyBleeding;
	bool ResistBleeding;
	bool StopBleeding;

	bool ResistFire;
	bool IgnoreWound;

	bool Fit;
	int Exertion;
	int Fatigue;
	int Spirit;

	bool Resting;
	bool Exhausted;

	bool Stunned;
	bool Stunned2;
	bool Stunned3;
	bool Prone;
	bool Disarmed;

	int Frozen;
	int OnFire;
	int Shock;

	int IceLimbs;

	int HitSkill;
	int DmgSkill;
	int DodgeSkill;
	int VitSkill;
	int StaSkill;
	int MagSkill;

	int Focus;

	bool ExecutePos;
	bool DenyExecute;

	bool Dead;
	bool Wounded;
	bool Blinded;
	bool Crippled;

	int Recovery;

	damage Damage;
	character* Target;

	int DodgeSuccess;
	int StrikeBonus;
	int StrikeSuccess;
	int WeaponBonus;
	int WeaponSuccess;
	int ExDmgBonus;
	int ExDmgSuccess;
	int SESuccess;

	rolls Rolls;

	armor HeadArmor;
	armor TorsoArmor;
	armor LArmArmor;
	armor RArmArmor;
	armor LLegArmor;
	armor RLegArmor;

	actionDB ActionDB;
	actionDB TempActionDB;
	action Actions[3];
	int ActionLimit;
	int CurrentActionLimit;
	bool Exerting;
	bool Active;

	point P;
};

struct chargroup
{
	character Group[GROUPSIZE];
	int GroupTotal;
	groupname GroupName;
};

static actionDB AllActionDB;
static actionDB DefActionDB[TOTALACTIONS];
static character CharList[TOTALCHARACTERS];

void DataOutName(ofstream *DataOut, groupname Group, charactername Type)
{
	if (Type == Normal)
		*DataOut << "Normal";
	else if (Type == BashMan)
		*DataOut << "BashMan";
	else if (Type == SlashMan)
		*DataOut << "SlashMan";
	else if (Type == ThrustMan)
		*DataOut << "ThrustMan";
	else if (Type == PierceMan)
		*DataOut << "PierceMan";
	else if (Type == ClampMan)
		*DataOut << "ClampMan";
	else if (Type == CrushMan)
		*DataOut << "CrushMan";
	else if (Type == EDmgMan)
		*DataOut << "EDmgMan";
	else if (Type == FireMan)
		*DataOut << "FireMan";
	else if (Type == IceMan)
		*DataOut << "IceMan";
	else if (Type == ElecMan)
		*DataOut << "ElecMan";
	else if (Type == AcidMan)
		*DataOut << "AcidMan";

	else if (Type == ArmorGuy)
		*DataOut << "ArmorGuy";
	else if (Type == Ninja)
		*DataOut << "Ninja";
	else if (Type == StrongMan)
		*DataOut << "StrongMan";
	else if (Type == FireMage)
		*DataOut << "FireMage";
	else if (Type == IceMage)
		*DataOut << "IceMage";
	else if (Type == ElecMage)
		*DataOut << "ElecMage";
	else if (Type == FireBattleMage)
		*DataOut << "FireBattleMage";
	else if (Type == IceBattleMage)
		*DataOut << "IceBattleMage";
	else if (Type == ElecBattleMage)
		*DataOut << "ElecBattleMage";
	else if (Type == Batman)
		*DataOut << "Batman";
}

void InitVitals(vitals *Vitals)
{
	Vitals->Dmg = 0;
	Vitals->PermDmg = 0;
	Vitals->OnFire = false;
}

void InitLimb(limb *Limb)
{
	Limb->Dmg = 0;
	Limb->PermDmg = 0;
	Limb->crippled = false;
	Limb->severed = false;
	Limb->Frozen = 0;
	Limb->OnFire = false;
}

void InitSense(sense *Sense)
{
	Sense->damage = 0;
	Sense->redundancy = 1;
	Sense->damaged = false;
}

void InitRolls(rolls *Rolls)
{
	Rolls->HitValue = 0;
	Rolls->DodgeValue = 0;
	Rolls->RecoverValue = 0;
	Rolls->SurviveValue = 0;
	Rolls->RestValue = 0;
	Rolls->RmvFireValue = 0;
	Rolls->RmvIceValue = 0;
	Rolls->UnstunValue = 0;
	Rolls->StandValue = 0;
	Rolls->PickUpItemValue = 0;
}

void InitDamage(damage *Damage)
{
	Damage->DamageAmount = 0;
	Damage->ExDmgAmount = 0;
	Damage->SEAmount = 0;
	Damage->DamageVital = false;
}

void CharacterInit(character *player)
{
	InitVitals(&player->Vitals);
	InitLimb(&player->LArm);
	InitLimb(&player->RArm);
	InitLimb(&player->LLeg);
	InitLimb(&player->RLeg);
	InitSense(&player->Eyes);

	player->Stunned = false;
	player->Stunned2 = false;
	player->Stunned3 = false;
	player->Prone = false;
	player->Disarmed = false;

	player->Frozen = false;
	player->IceLimbs = 0;

	player->Fit = true;
	player->Exertion = 0;
	player->Fatigue = 0;
	player->Spirit = 0;

	player->Resting = false;
	player->Exhausted = false;

	player->Frozen = 0;
	player->OnFire = 0;
	player->Shock = 0;

	player->Bleeding = false;
	player->HeavyBleeding = false;
	player->StopBleeding = false;

	player->ExecutePos = false;
	player->DenyExecute = false;

	player->Wounded = false;
	player->Dead = false;
	player->Blinded = false;

	player->Recovery = 0;
	player->Crippled = false;

	player->ResistBleeding = false;
	player->ResistFire = false;
	player->IgnoreWound = false;

	InitRolls(&player->Rolls);

	player->Damage.DamageAmount = 0;
	player->Damage.ExDmgAmount = 0;
	player->Damage.SEAmount = 0;

	player->HeadArmor.BodyArea = Head;
	player->HeadArmor.PaddingRemaining = player->HeadArmor.PaddingTotal;
	player->HeadArmor.DamageRemaining = player->HeadArmor.DamageTotal;
	player->TorsoArmor.BodyArea = Torso;
	player->TorsoArmor.PaddingRemaining = player->TorsoArmor.PaddingTotal;
	player->TorsoArmor.DamageRemaining = player->TorsoArmor.DamageTotal;
	player->LArmArmor.BodyArea = LArm;
	player->LArmArmor.PaddingRemaining = player->LArmArmor.PaddingTotal;
	player->LArmArmor.DamageRemaining = player->LArmArmor.DamageTotal;
	player->RArmArmor.BodyArea = RArm;
	player->RArmArmor.PaddingRemaining = player->RArmArmor.PaddingTotal;
	player->RArmArmor.DamageRemaining = player->RArmArmor.DamageTotal;
	player->LLegArmor.BodyArea = LLeg;
	player->LLegArmor.PaddingRemaining = player->LLegArmor.PaddingTotal;
	player->LLegArmor.DamageRemaining = player->LLegArmor.DamageTotal;
	player->RLegArmor.BodyArea = RLeg;
	player->RLegArmor.PaddingRemaining = player->RLegArmor.PaddingTotal;
	player->RLegArmor.DamageRemaining = player->RLegArmor.DamageTotal;

	player->ActionLimit = 3;
	player->CurrentActionLimit = player->ActionLimit;
	player->Exerting = false;
	player->Active = false;
}

void InitArmor(armor *Armor)
{
	Armor->Armored = false;
	Armor->DR = 0;
	Armor->PaddingTotal = 0;
	Armor->DamageTotal = 0;
}

void InitBasicStats(character *player)
{
	player->WoundWins = 0;
	player->DeathWins = 0;

	player->HitSkill = 5;
	player->DmgSkill = 5;
	player->DodgeSkill = 5;
	player->VitSkill = 5;
	player->StaSkill = 5;
	player->MagSkill = 5;

	player->Focus = 2;

	player->Damage.DamageType = Dmg;
	player->Damage.ExDmgType = None;
	player->Damage.SEType = None;

	player->DodgeSuccess = 0;
	player->StrikeBonus = 0;
	player->StrikeSuccess = 0;
	player->WeaponBonus = 0;
	player->WeaponSuccess = 1;
	player->ExDmgBonus = 0;
	player->ExDmgSuccess = 0;
	player->SESuccess = 0;

	InitArmor(&player->HeadArmor);
	InitArmor(&player->TorsoArmor);
	InitArmor(&player->LArmArmor);
	InitArmor(&player->RArmArmor);
	InitArmor(&player->LLegArmor);
	InitArmor(&player->RLegArmor);

	player->Actions[0] = AllActionDB.ActionList[noaction];
	player->Actions[1] = AllActionDB.ActionList[noaction];
	player->Actions[2] = AllActionDB.ActionList[noaction];
}

void InitLightArmor(armor *Armor, int DR, int padding, int DP)
{
	Armor->Armored = true;
	Armor->DR = DR;
	Armor->PaddingTotal = padding;
	Armor->DamageTotal = DP;
}

void InitAllActionDB()
{
	AllActionDB.TotalActions = TOTALACTIONS;

	AllActionDB.ActionList[noaction].ActionType = noaction;
	AllActionDB.ActionList[noaction].exert = false;
	AllActionDB.ActionList[noaction].active = false;
	AllActionDB.ActionList[noaction].AP = 0;
	AllActionDB.ActionList[noaction].AC = 0;
	AllActionDB.ActionList[noaction].MC = 0;
	AllActionDB.ActionList[noaction].PC = 0;
	AllActionDB.ActionList[noaction].EP = 0;
	AllActionDB.ActionList[noaction].SP = 0;

	AllActionDB.ActionList[strike].ActionType = strike;
	AllActionDB.ActionList[strike].exert = true;
	AllActionDB.ActionList[strike].active = true;
	AllActionDB.ActionList[strike].AP = 1;
	AllActionDB.ActionList[strike].AC = 1;
	AllActionDB.ActionList[strike].MC = 0;
	AllActionDB.ActionList[strike].PC = 0;
	AllActionDB.ActionList[strike].EP = 1;
	AllActionDB.ActionList[strike].SP = 0;

	AllActionDB.ActionList[dodge].ActionType = dodge;
	AllActionDB.ActionList[dodge].exert = true;
	AllActionDB.ActionList[dodge].active = true;
	AllActionDB.ActionList[dodge].AP = 1;
	AllActionDB.ActionList[dodge].AC = 1;
	AllActionDB.ActionList[dodge].MC = 0;
	AllActionDB.ActionList[dodge].PC = 0;
	AllActionDB.ActionList[dodge].EP = 1;
	AllActionDB.ActionList[dodge].SP = 0;

	AllActionDB.ActionList[rest].ActionType = rest;
	AllActionDB.ActionList[rest].exert = false;
	AllActionDB.ActionList[rest].active = false;
	AllActionDB.ActionList[rest].AP = 1;
	AllActionDB.ActionList[rest].AC = 0;
	AllActionDB.ActionList[rest].MC = 0;
	AllActionDB.ActionList[rest].PC = 1;
	AllActionDB.ActionList[rest].EP = 0;
	AllActionDB.ActionList[rest].SP = 0;

	AllActionDB.ActionList[fullrest].ActionType = fullrest;
	AllActionDB.ActionList[fullrest].exert = false;
	AllActionDB.ActionList[fullrest].active = false;
	AllActionDB.ActionList[fullrest].AP = 3;
	AllActionDB.ActionList[fullrest].AC = 0;
	AllActionDB.ActionList[fullrest].MC = 0;
	AllActionDB.ActionList[fullrest].PC = 3;
	AllActionDB.ActionList[fullrest].EP = 0;
	AllActionDB.ActionList[fullrest].SP = 0;

	AllActionDB.ActionList[recover].ActionType = recover;
	AllActionDB.ActionList[recover].exert = false;
	AllActionDB.ActionList[recover].active = false;
	AllActionDB.ActionList[recover].AP = 1;
	AllActionDB.ActionList[recover].AC = 0;
	AllActionDB.ActionList[recover].MC = 0;
	AllActionDB.ActionList[recover].PC = 1;
	AllActionDB.ActionList[recover].EP = 0;
	AllActionDB.ActionList[recover].SP = 0;

	AllActionDB.ActionList[survive].ActionType = survive;
	AllActionDB.ActionList[survive].exert = false;
	AllActionDB.ActionList[survive].active = false;
	AllActionDB.ActionList[survive].AP = 1;
	AllActionDB.ActionList[survive].AC = 0;
	AllActionDB.ActionList[survive].MC = 0;
	AllActionDB.ActionList[survive].PC = 1;
	AllActionDB.ActionList[survive].EP = 0;
	AllActionDB.ActionList[survive].SP = 0;

	AllActionDB.ActionList[rmvfire].ActionType = rmvfire;
	AllActionDB.ActionList[rmvfire].exert = false;
	AllActionDB.ActionList[rmvfire].active = false;
	AllActionDB.ActionList[rmvfire].AP = 2;
	AllActionDB.ActionList[rmvfire].AC = 0;
	AllActionDB.ActionList[rmvfire].MC = 0;
	AllActionDB.ActionList[rmvfire].PC = 2;
	AllActionDB.ActionList[rmvfire].EP = 1;
	AllActionDB.ActionList[rmvfire].SP = 0;

	AllActionDB.ActionList[rmvice].ActionType = rmvice;
	AllActionDB.ActionList[rmvice].exert = false;
	AllActionDB.ActionList[rmvice].active = false;
	AllActionDB.ActionList[rmvice].AP = 2;
	AllActionDB.ActionList[rmvice].AC = 0;
	AllActionDB.ActionList[rmvice].MC = 0;
	AllActionDB.ActionList[rmvice].PC = 2;
	AllActionDB.ActionList[rmvice].EP = 1;
	AllActionDB.ActionList[rmvice].SP = 0;

	AllActionDB.ActionList[mvtoexecute].ActionType = mvtoexecute;
	AllActionDB.ActionList[mvtoexecute].exert = false;
	AllActionDB.ActionList[mvtoexecute].active = false;
	AllActionDB.ActionList[mvtoexecute].AP = 3;
	AllActionDB.ActionList[mvtoexecute].AC = 2;
	AllActionDB.ActionList[mvtoexecute].MC = 1;
	AllActionDB.ActionList[mvtoexecute].PC = 1;
	AllActionDB.ActionList[mvtoexecute].EP = 0;
	AllActionDB.ActionList[mvtoexecute].SP = 0;

	AllActionDB.ActionList[execute].ActionType = execute;
	AllActionDB.ActionList[execute].exert = true;
	AllActionDB.ActionList[execute].active = true;
	AllActionDB.ActionList[execute].AP = 3;
	AllActionDB.ActionList[execute].AC = 2;
	AllActionDB.ActionList[execute].MC = 1;
	AllActionDB.ActionList[execute].PC = 1;
	AllActionDB.ActionList[execute].EP = 0;
	AllActionDB.ActionList[execute].SP = 0;

	AllActionDB.ActionList[unstun].ActionType = unstun;
	AllActionDB.ActionList[unstun].exert = true;
	AllActionDB.ActionList[unstun].active = true;
	AllActionDB.ActionList[unstun].AP = 1;
	AllActionDB.ActionList[unstun].AC = 0;
	AllActionDB.ActionList[unstun].MC = 0;
	AllActionDB.ActionList[unstun].PC = 1;
	AllActionDB.ActionList[unstun].EP = 0;
	AllActionDB.ActionList[unstun].SP = 0;

	AllActionDB.ActionList[stand].ActionType = stand;
	AllActionDB.ActionList[stand].exert = false;
	AllActionDB.ActionList[stand].active = false;
	AllActionDB.ActionList[stand].AP = 2;
	AllActionDB.ActionList[stand].AC = 0;
	AllActionDB.ActionList[stand].MC = 1;
	AllActionDB.ActionList[stand].PC = 0;
	AllActionDB.ActionList[stand].EP = 0;
	AllActionDB.ActionList[stand].SP = 0;

	AllActionDB.ActionList[pickupitem].ActionType = pickupitem;
	AllActionDB.ActionList[pickupitem].exert = false;
	AllActionDB.ActionList[pickupitem].active = false;
	AllActionDB.ActionList[pickupitem].AP = 2;
	AllActionDB.ActionList[pickupitem].AC = 1;
	AllActionDB.ActionList[pickupitem].MC = 0;
	AllActionDB.ActionList[pickupitem].PC = 0;
	AllActionDB.ActionList[pickupitem].EP = 0;
	AllActionDB.ActionList[pickupitem].SP = 0;
}

void InitDefActionDB(actionDB* ActionDB)
{
	ActionDB->TotalActions = 0;

	ActionDB->ActionList[ActionDB->TotalActions] = AllActionDB.ActionList[strike];
	ActionDB->ActionList[ActionDB->TotalActions].used = false;
	ActionDB->ActionList[ActionDB->TotalActions].weight = 50;
	++ActionDB->TotalActions;

	ActionDB->ActionList[ActionDB->TotalActions] = AllActionDB.ActionList[dodge];
	ActionDB->ActionList[ActionDB->TotalActions].used = false;
	ActionDB->ActionList[ActionDB->TotalActions].weight = 25;
	++ActionDB->TotalActions;

	ActionDB->ActionList[ActionDB->TotalActions] = AllActionDB.ActionList[rest];
	ActionDB->ActionList[ActionDB->TotalActions].used = false;
	ActionDB->ActionList[ActionDB->TotalActions].weight = 25;
	++ActionDB->TotalActions;

	ActionDB->ActionList[ActionDB->TotalActions] = AllActionDB.ActionList[fullrest];
	ActionDB->ActionList[ActionDB->TotalActions].used = false;
	ActionDB->ActionList[ActionDB->TotalActions].weight = 0;
	++ActionDB->TotalActions;

	ActionDB->ActionList[ActionDB->TotalActions] = AllActionDB.ActionList[recover];
	ActionDB->ActionList[ActionDB->TotalActions].used = false;
	ActionDB->ActionList[ActionDB->TotalActions].weight = 0;
	++ActionDB->TotalActions;

	ActionDB->ActionList[ActionDB->TotalActions] = AllActionDB.ActionList[survive];
	ActionDB->ActionList[ActionDB->TotalActions].used = false;
	ActionDB->ActionList[ActionDB->TotalActions].weight = 0;
	++ActionDB->TotalActions;

	ActionDB->ActionList[ActionDB->TotalActions] = AllActionDB.ActionList[rmvfire];
	ActionDB->ActionList[ActionDB->TotalActions].used = false;
	ActionDB->ActionList[ActionDB->TotalActions].weight = 0;
	++ActionDB->TotalActions;

	ActionDB->ActionList[ActionDB->TotalActions] = AllActionDB.ActionList[rmvice];
	ActionDB->ActionList[ActionDB->TotalActions].used = false;
	ActionDB->ActionList[ActionDB->TotalActions].weight = 0;
	++ActionDB->TotalActions;

	ActionDB->ActionList[ActionDB->TotalActions] = AllActionDB.ActionList[mvtoexecute];
	ActionDB->ActionList[ActionDB->TotalActions].used = false;
	ActionDB->ActionList[ActionDB->TotalActions].weight = 0;
	++ActionDB->TotalActions;

	ActionDB->ActionList[ActionDB->TotalActions] = AllActionDB.ActionList[execute];
	ActionDB->ActionList[ActionDB->TotalActions].used = false;
	ActionDB->ActionList[ActionDB->TotalActions].weight = 0;
	++ActionDB->TotalActions;

	ActionDB->ActionList[ActionDB->TotalActions] = AllActionDB.ActionList[unstun];
	ActionDB->ActionList[ActionDB->TotalActions].used = false;
	ActionDB->ActionList[ActionDB->TotalActions].weight = 0;
	++ActionDB->TotalActions;

	ActionDB->ActionList[ActionDB->TotalActions] = AllActionDB.ActionList[stand];
	ActionDB->ActionList[ActionDB->TotalActions].used = false;
	ActionDB->ActionList[ActionDB->TotalActions].weight = 0;
	++ActionDB->TotalActions;

	ActionDB->ActionList[ActionDB->TotalActions] = AllActionDB.ActionList[pickupitem];
	ActionDB->ActionList[ActionDB->TotalActions].used = false;
	ActionDB->ActionList[ActionDB->TotalActions].weight = 0;
	++ActionDB->TotalActions;

	for (int i = ActionDB->TotalActions; i < TOTALACTIONS; i++)
	{
		ActionDB->ActionList[i].ActionType = noaction;
	}
}

void ResetActionUse(actionDB* ActionDB)
{
	for (int i = 0; i < ActionDB->TotalActions; i++)
	{
		ActionDB->ActionList[i].used = false;
	}
}

void SetActionDB(character *player, actionDB* ActionDB)
{
	player->ActionDB.TotalActions = 0;
	for (int i = 0; i < ActionDB->TotalActions; ++i)
	{
		player->ActionDB.ActionList[i].ActionType = ActionDB->ActionList[i].ActionType;
		player->ActionDB.ActionList[i].weight = ActionDB->ActionList[i].weight;
		player->ActionDB.ActionList[i].AP = ActionDB->ActionList[i].AP;
		player->ActionDB.ActionList[i].EP = ActionDB->ActionList[i].EP;
		player->ActionDB.ActionList[i].SP = ActionDB->ActionList[i].SP;
		++player->ActionDB.TotalActions;
	}

	ResetActionUse(&player->ActionDB);
}

void InitCharGroup(chargroup *CharGroup, charactername name,
	dmgtype type, dmgtype exdmgtype, actionDB actions[])
{
	CharGroup->GroupTotal = 0;
	for (int i = 0; i < GROUPSIZE; ++i)
	{
		//CharGroup->Group[i].Damage.DamageType = type;
		//CharGroup->Group[i].Damage.ExDmgType = exdmgtype;
	}

	CharGroup->Group[CharGroup->GroupTotal] = CharList[Normal];
	++CharGroup->GroupTotal;

	CharGroup->Group[CharGroup->GroupTotal] = CharList[ArmorGuy];
	++CharGroup->GroupTotal;

	CharGroup->Group[CharGroup->GroupTotal] = CharList[Ninja];
	++CharGroup->GroupTotal;

	CharGroup->Group[CharGroup->GroupTotal] = CharList[StrongMan];
	++CharGroup->GroupTotal;

	CharGroup->Group[CharGroup->GroupTotal] = CharList[FireMage];
	++CharGroup->GroupTotal;

	CharGroup->Group[CharGroup->GroupTotal] = CharList[IceMage];
	++CharGroup->GroupTotal;

	CharGroup->Group[CharGroup->GroupTotal] = CharList[ElecMage];
	++CharGroup->GroupTotal;

	CharGroup->Group[CharGroup->GroupTotal] = CharList[FireBattleMage];
	++CharGroup->GroupTotal;

	CharGroup->Group[CharGroup->GroupTotal] = CharList[IceBattleMage];
	++CharGroup->GroupTotal;

	CharGroup->Group[CharGroup->GroupTotal] = CharList[ElecBattleMage];
	++CharGroup->GroupTotal;

	CharGroup->Group[CharGroup->GroupTotal] = CharList[Batman];
	++CharGroup->GroupTotal;
}

void InitCharList()
{
	//Basic Stats
	//Vit/Dmg/Sta/Hit/Dodge Skill = 5
	//No autosuccess
	//Dmg Type: Std
	//ExDmgType: None

	CharList[Normal].Name = Normal;
	InitBasicStats(&CharList[Normal]);
	CharList[Normal].WeaponSuccess = 1;
	CharList[Normal].StrikeSuccess = 1;
	CharList[Normal].DodgeSuccess = 0;
	CharList[Normal].Fit = false;
	SetActionDB(&CharList[Normal], DefActionDB);

	CharList[BashMan].Name = BashMan;
	InitBasicStats(&CharList[BashMan]);
	CharList[BashMan].Damage.DamageType = Bash;
	CharList[BashMan].WeaponSuccess = 1;
	CharList[BashMan].StrikeSuccess = 1;
	CharList[BashMan].DodgeSuccess = 0;
	SetActionDB(&CharList[BashMan], DefActionDB);

	CharList[SlashMan].Name = SlashMan;
	InitBasicStats(&CharList[SlashMan]);
	CharList[SlashMan].Damage.DamageType = Slash;
	CharList[SlashMan].WeaponSuccess = 1;
	CharList[SlashMan].StrikeSuccess = 1;
	CharList[SlashMan].DodgeSuccess = 0;
	SetActionDB(&CharList[SlashMan], DefActionDB);

	CharList[FireMan].Name = FireMan;
	InitBasicStats(&CharList[FireMan]);
	CharList[FireMan].Damage.DamageType = Fire;
	CharList[FireMan].Damage.SEAmount = 5;
	CharList[FireMan].Damage.SEType = OnFire;
	CharList[FireMan].WeaponSuccess = 1;
	CharList[FireMan].StrikeSuccess = 1;
	CharList[FireMan].DodgeSuccess = 0;
	SetActionDB(&CharList[FireMan], DefActionDB);

	CharList[IceMan].Name = IceMan;
	InitBasicStats(&CharList[IceMan]);
	CharList[IceMan].Damage.DamageType = Ice;
	CharList[IceMan].Damage.SEAmount = 5;
	CharList[IceMan].Damage.SEType = Frozen;
	CharList[IceMan].WeaponSuccess = 1;
	CharList[IceMan].StrikeSuccess = 1;
	CharList[IceMan].DodgeSuccess = 0;
	SetActionDB(&CharList[IceMan], DefActionDB);

	CharList[ElecMan].Name = ElecMan;
	InitBasicStats(&CharList[ElecMan]);
	CharList[ElecMan].Damage.DamageType = Elec;
	CharList[ElecMan].Damage.SEAmount = 5;
	CharList[ElecMan].Damage.SEType = Stun;
	CharList[ElecMan].WeaponSuccess = 1;
	CharList[ElecMan].StrikeSuccess = 1;
	CharList[ElecMan].DodgeSuccess = 0;
	SetActionDB(&CharList[ElecMan], DefActionDB);

	CharList[ArmorGuy].Name = ArmorGuy;
	InitBasicStats(&CharList[ArmorGuy]);
	CharList[ArmorGuy].WeaponSuccess = 1;
	CharList[ArmorGuy].StrikeSuccess = 1;
	InitLightArmor(&CharList[ArmorGuy].HeadArmor, 1, 0, 3);
	InitLightArmor(&CharList[ArmorGuy].TorsoArmor, 1, 0, 3);
	InitLightArmor(&CharList[ArmorGuy].LArmArmor, 1, 0, 3);
	InitLightArmor(&CharList[ArmorGuy].RArmArmor, 1, 0, 3);
	InitLightArmor(&CharList[ArmorGuy].LLegArmor, 1, 0, 3);
	InitLightArmor(&CharList[ArmorGuy].RLegArmor, 1, 0, 3);
	SetActionDB(&CharList[ArmorGuy], DefActionDB);

	CharList[Ninja].Name = Ninja;
	InitBasicStats(&CharList[Ninja]);
	CharList[Ninja].Damage.DamageType = Slash;
	CharList[Ninja].HitSkill = 8;
	CharList[Ninja].DodgeSkill = 8;
	CharList[StrongMan].VitSkill = 3;
	CharList[StrongMan].DmgSkill = 3;
	CharList[Ninja].WeaponSuccess = 1;
	CharList[Ninja].StrikeSuccess = 1;
	CharList[Ninja].DodgeSuccess = 1;
	SetActionDB(&CharList[Ninja], DefActionDB);

	CharList[StrongMan].Name = StrongMan;
	InitBasicStats(&CharList[StrongMan]);
	CharList[StrongMan].Damage.DamageType = Bash;
	CharList[Ninja].HitSkill = 3;
	CharList[Ninja].DodgeSkill = 3;
	CharList[StrongMan].VitSkill = 8;
	CharList[StrongMan].DmgSkill = 8;
	CharList[StrongMan].WeaponSuccess = 3;
	CharList[StrongMan].StrikeSuccess = 1;
	CharList[StrongMan].Fit = false;
	SetActionDB(&CharList[StrongMan], DefActionDB);

	CharList[FireMage].Name = FireMage;
	InitBasicStats(&CharList[FireMage]);
	CharList[FireMage].Damage.DamageType = Fire;
	CharList[FireMage].WeaponSuccess = 0;
	CharList[FireMage].StrikeSuccess = 0;
	SetActionDB(&CharList[FireMage], DefActionDB);

	CharList[IceMage].Name = IceMage;
	InitBasicStats(&CharList[IceMage]);
	CharList[IceMage].Damage.DamageType = Ice;
	CharList[IceMage].WeaponSuccess = 0;
	CharList[IceMage].StrikeSuccess = 0;
	SetActionDB(&CharList[IceMage], DefActionDB);

	CharList[ElecMage].Name = ElecMage;
	InitBasicStats(&CharList[ElecMage]);
	CharList[ElecMage].Damage.DamageType = Elec;
	CharList[ElecMage].WeaponSuccess = 0;
	CharList[ElecMage].StrikeSuccess = 1;
	SetActionDB(&CharList[ElecMage], DefActionDB);

	CharList[FireBattleMage].Name = FireBattleMage;
	InitBasicStats(&CharList[FireBattleMage]);
	CharList[FireBattleMage].Damage.DamageType = Slash;
	CharList[FireBattleMage].Damage.ExDmgType = Fire;
	CharList[FireBattleMage].Damage.SEAmount = 5;
	CharList[FireBattleMage].Damage.SEType = OnFire;
	CharList[FireBattleMage].WeaponSuccess = 1;
	CharList[FireBattleMage].StrikeSuccess = 1;
	CharList[FireBattleMage].ExDmgSuccess = 0;
	SetActionDB(&CharList[FireBattleMage], DefActionDB);

	CharList[IceBattleMage].Name = IceBattleMage;
	InitBasicStats(&CharList[IceBattleMage]);
	CharList[IceBattleMage].Damage.DamageType = Slash;
	CharList[IceBattleMage].Damage.ExDmgType = Ice;
	CharList[IceBattleMage].Damage.SEAmount = 5;
	CharList[IceBattleMage].Damage.SEType = Frozen;
	CharList[IceBattleMage].WeaponSuccess = 1;
	CharList[IceBattleMage].StrikeSuccess = 1;
	CharList[IceBattleMage].ExDmgSuccess = 0;
	SetActionDB(&CharList[IceBattleMage], DefActionDB);

	CharList[ElecBattleMage].Name = ElecBattleMage;
	InitBasicStats(&CharList[ElecBattleMage]);
	CharList[ElecBattleMage].Damage.DamageType = Slash;
	CharList[ElecBattleMage].Damage.ExDmgType = Elec;
	CharList[ElecBattleMage].Damage.SEAmount = 5;
	CharList[ElecBattleMage].Damage.SEType = Stun;
	CharList[ElecBattleMage].WeaponSuccess = 1;
	CharList[ElecBattleMage].StrikeSuccess = 1;
	CharList[ElecBattleMage].ExDmgSuccess = 0;
	SetActionDB(&CharList[ElecBattleMage], DefActionDB);

	CharList[Batman].Name = Batman;
	InitBasicStats(&CharList[Batman]);
	CharList[Batman].Damage.DamageType = Bash;
	CharList[Batman].VitSkill = 10;
	CharList[Batman].DmgSkill = 10;
	CharList[Batman].StaSkill = 10;
	CharList[Batman].HitSkill = 10;
	CharList[Batman].DodgeSkill = 10;
	CharList[Batman].MagSkill = 10;
	CharList[Batman].WeaponSuccess = 2;
	CharList[Batman].StrikeSuccess = 1;
	CharList[Batman].DodgeSuccess = 1;
	SetActionDB(&CharList[Batman], DefActionDB);
}

#endif