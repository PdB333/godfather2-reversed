// FUNC_NAME: GodfatherGameManager::playSoundForAction
undefined4 GodfatherGameManager::playSoundForAction(undefined4 actionType)

{
  undefined4 soundId;
  undefined4 local_4;
  
  soundId = 0;
  switch(actionType) {
  case 0: // ACTION_KILL
    soundId = 0x13d67513;
    break;
  case 1: // ACTION_INTIMIDATE
    soundId = 0x13d67514;
    break;
  case 2: // ACTION_BRIBE
    soundId = 0x13d67515;
    break;
  case 3: // ACTION_EXTORT
    soundId = 0xba1b8847;
    break;
  case 4: // ACTION_WHACK
    soundId = 0x60d3064e;
    break;
  default:
    goto switchD_0069c55c_default;
  }
  local_4 = 0;
  // Play the sound via audio system
  FUN_006039d0(soundId,&local_4,&actionType);
  // Handle sound completion callback
  FUN_004d3d90(local_4);
  soundId = 1;
switchD_0069c55c_default:
  return soundId;
}