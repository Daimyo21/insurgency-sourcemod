#if defined _insurgency_included
  #endinput
#endif
#define _insurgency_included

//#include <sourcemod>
//#include <sdktools>
//#include <loghelper>

#define MAX_DEFINABLE_WEAPONS 100
#define MAX_WEAPON_LEN 32
#define MAX_SQUAD_LEN 32
#define MAX_CLASS_LEN 64
#define MAX_CONTROLPOINTS 32
#define PREFIX_LEN 7
#define MAX_SQUADS 8
#define SQUAD_SIZE 8

native Ins_ObjectiveResource_GetProp(const String:prop[], size=4, element=0);
native Ins_GetWeaponGetMaxClip1(weapon);
native Float:Ins_ObjectiveResource_GetPropFloat(const String:prop[], size=4, element=0);
native Ins_ObjectiveResource_GetPropEnt(const String:prop[], element=0);
native bool:Ins_ObjectiveResource_GetPropBool(const String:prop[], element=0);
native Ins_ObjectiveResource_GetPropVector(const String:prop[], Float:vec[3], element=0);
native Ins_ObjectiveResource_GetPropString(const String:prop[], String:buffer[], maxlen);

native bool:Ins_InCounterAttack();

native Ins_GetPlayerScore(client);
native Ins_GetPlayerClass(client, String:buffer[], maxlen);
native Ins_GetClassName(squad,squad_slot);
//native GameLogic_();

native Ins_GetWeaponName(weaponid, String:buffer[], maxlen);
native Ins_GetWeaponId(String:weapon_name[]);

enum Teams
{
	TEAM_NONE = 0,
	TEAM_SPECTATORS,
	TEAM_SECURITY,
	TEAM_INSURGENTS,
}
enum RoundStatFields
{
	STAT_KILLS = 0,
	STAT_DEATHS,
	STAT_SHOTS,
	STAT_HITS,
	STAT_GRENADES,
	STAT_CAPTURES,
	STAT_CACHES,
	STAT_DMG_GIVEN,
	STAT_DMG_TAKEN,
	STAT_TEAMKILLS,
	STAT_SCORE,
	STAT_SUPPRESSIONS,
	STAT_ACCURACY,
}
enum Hitgroups
{
	HITGROUP_GENERIC = 0,
	HITGROUP_HEAD,
	HITGROUP_CHEST,
	HITGROUP_STOMACH,
	HITGROUP_LEFTARM,
	HITGROUP_RIGHTARM,
	HITGROUP_LEFTLEG,
	HITGROUP_RIGHTLEG,
}
#define LOG_HIT_OFFSET     7 
enum WeaponStatFields
{
	LOG_HIT_SHOTS = 0,
	LOG_HIT_HITS,
	LOG_HIT_KILLS,
	LOG_HIT_HEADSHOTS,
	LOG_HIT_TEAMKILLS,
	LOG_HIT_DAMAGE,
	LOG_HIT_DEATHS,
	LOG_HIT_GENERIC,
	LOG_HIT_HEAD,
	LOG_HIT_CHEST,
	LOG_HIT_STOMACH,
	LOG_HIT_LEFTARM,
	LOG_HIT_RIGHTARM,
	LOG_HIT_LEFTLEG,
	LOG_HIT_RIGHTLEG,
}


stock AddFolderToDownloadTable(const String:Directory[], bool:recursive=false)
{
	decl String:FileName[64], String:Path[512];
	new Handle:Dir = OpenDirectory(Directory), FileType:Type;
	while(ReadDirEntry(Dir, FileName, sizeof(FileName), Type))
	{
		if(Type == FileType_Directory && recursive)
		{
			FormatEx(Path, sizeof(Path), "%s/%s", Directory, FileName);
			AddFolderToDownloadTable(FileName,recursive);
			continue;
		}
		if (Type != FileType_File)
			continue;
		FormatEx(Path, sizeof(Path), "%s/%s", Directory, FileName);
		AddFileToDownloadsTable(Path);
	}
	return;
}

/* Returns True if the client is an ingame player, False otherwise.
 * Checks are performed in the order least likely to spew an error.
 *
 * @return                  If the client is a valid client.
 */
stock bool:IsValidClient(client) {

  return (client > 0 && client <= MaxClients &&
    IsClientConnected(client) && IsClientInGame(client) &&
    !IsClientReplay(client) && !IsClientSourceTV(client));

}

/**
 * Counts the players in a team, alive or dead.
 *
 * @param team             Team index.
 * @return                 Number of players.
 */
stock Team_CountPlayers(team) {

  new count = 0;
  for (new i = 1; i <= MaxClients; i++) {
    if (IsValidClient(i) && GetClientTeam(i) == team) {
      count++;
    }
  }
  return count;

}

/**
 * Counts the number of living players in a team.
 *
 * @param team             Team index.
 * @return                 Number of living players.
 */
stock Team_CountAlivePlayers(team) {

   new count = 0;
   for (new i = 1; i <= MaxClients; i++) {
     if (IsValidClient(i) && GetClientTeam(i) == team && IsPlayerAlive(i)) {
       count++;
     }
   }
   return count;

 }
/*
stock Client_IsValid(client, bool:checkConnected)
{
	if (client > 4096) {
		client = EntRefToEntIndex(client);
	}

	if (client < 1 || client > MaxClients) {
		return false;
	}

	if (checkConnected && !IsClientConnected(client)) {
		return false;
	}
	
	return true;
}
*/
