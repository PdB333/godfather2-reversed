// FUNC_NAME: Player::updateActionPrompts
void Player::updateActionPrompts(int param_1)
{
  uint flags;
  char result;
  int playerState;
  int local_c;
  int local_8;
  int local_4;

  if (param_1 == 0) {
    playerState = 0;
  }
  else {
    playerState = FUN_0043b870(DAT_0112afb8); // GetPlayerState from main instance
  }
  // Check if player state (0x40) minus some threshold (0x4c) is within range (0x00e44598) 
  // and certain gameplay conditions are met
  if (((*(float *)(playerState + 0x40) - *(float *)(playerState + 0x4c) <= DAT_00e44598) &&
      (result = FUN_0078af40(), result != '\0')) && (result = FUN_0078a7d0(), result != '\0')) {
    local_c = DAT_0112afc0; // Some action prompt string ID
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c, 0); // ShowActionPrompt with flags
  }
  local_c = DAT_0112ba94; // Default context action string
  local_8 = 0;
  local_4 = 0;
  FUN_00408a00(&local_c, 0); // ShowActionPrompt (always shown)
  flags = *(uint *)(param_1 + 0x1f98); // Player flags at offset 0x1f98
  if ((flags >> 5 & 1) == 0) {
    if ((flags >> 4 & 1) == 0) {
      if (((flags >> 2 & 1) == 0) &&
         (((flags >> 8 & 1) == 0 || (result = FUN_0071fa50(), result != '\0')))) {
        if ((*(uint *)(param_1 + 0x1f98) >> 3 & 1) == 0) {
          if ((*(uint *)(param_1 + 0x1f98) >> 10 & 1) == 0) {
            return;
          }
          local_c = DAT_0112ba8c; // Prompt for some action (break free?)
        }
        else {
          local_c = DAT_0112ba68; // Prompt for combat action
        }
      }
      else {
        local_c = DAT_0112ba7c; // Prompt for context action (interact?)
      }
    }
    else {
      local_c = DAT_0112ba60; // Prompt for pickup action
    }
  }
  else {
    local_c = DAT_0112ba84; // Prompt for stealth action (chokehold?)
  }
  local_8 = 0;
  local_4 = 0;
  FUN_00408a00(&local_c, 0); // ShowActionPrompt with context-sensitive text
  return;
}