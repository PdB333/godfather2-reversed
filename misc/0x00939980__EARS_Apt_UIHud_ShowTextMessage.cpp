// Xbox PDB: EARS_Apt_UIHud_ShowTextMessage
// FUNC_NAME: Player::showTextMessage
void __thiscall Player::showTextMessage(int this, undefined4 param_2)
{
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  // Call to show text message function with "ShowTextMessage" string
  FUN_005a04a0("ShowTextMessage",0,&DAT_00d8a64c,1,param_2);
  
  // Set flag at offset +0x5c (likely a bitfield for player state flags)
  *(uint *)(this + 0x5c) = *(uint *)(this + 0x5c) | 2;
  
  // Initialize local variables with global data
  local_c = DAT_011304a0;
  local_8 = 0;
  local_4 = 0;
  
  // Call function with the initialized data
  FUN_00408a00(&local_c,0);
  
  return;
}