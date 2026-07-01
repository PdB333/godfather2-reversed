// Xbox PDB: EARS_Apt_BuddyInfo_GetOnlineStatusDescription
// FUNC_NAME: OnlineBuddyStatus::getStatusString
char * __fastcall OnlineBuddyStatus::getStatusString(int status)
{
  switch(status) {
  case 5:
    return "$mp_online_buddy_offline"; // Buddy is offline
  case 6:
    return "$mp_online_buddy_away";     // Buddy is away
  case 7:
    return "$mp_online_buddy_busy";     // Buddy is busy
  case 8:
    return "$mp_online_buddy_game";     // Buddy is in a game
  case 9:
    return "$mp_online_buddy_online";   // Buddy is online
  default:
    return "";                          // Unknown status
  }
}