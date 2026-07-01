// Xbox PDB: EARS_Apt_UIHud_HideTextMessage
// FUNC_NAME: GodfatherGameManager::hideTextMessage
void GodfatherGameManager::hideTextMessage(char param_1)

{
  undefined1 *puVar1;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  puVar1 = &DAT_00e36d94; // +0x94: some text message data
  if (param_1 == '\0') {
    puVar1 = &DAT_00e36da0; // +0xA0: alternative text message data
  }
  FUN_005a04a0("HideTextMessage",0,&DAT_00d8a64c,1,puVar1); // likely a message/event dispatch function
  local_c = DAT_01130440; // some global state
  local_8 = 0;
  local_4 = 0;
  FUN_00408a00(&local_c,0); // likely a cleanup/reset function
  return;
}