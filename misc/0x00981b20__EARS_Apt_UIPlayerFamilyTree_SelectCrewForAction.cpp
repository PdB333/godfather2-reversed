// Xbox PDB: EARS_Apt_UIPlayerFamilyTree_SelectCrewForAction
// FUNC_NAME: FamilyManager::sendPauseFamilyConfirmCrew
void FamilyManager::sendPauseFamilyConfirmCrew(void)
{
  int iVar1;
  
  iVar1 = FUN_009c8e50(0xf0); // allocate memory for a message (0xf0 bytes)
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_00982280(0); // construct message object
  }
  FUN_00981eb0("$pause_family_confirm_send_crew"); // set message type string
  *(undefined4 *)(iVar1 + 0xc) = 2; // +0x0C: message subtype (2 = confirm send crew)
  *(undefined4 *)(iVar1 + 0x20) = 0xb9754031; // +0x20: some ID or hash
  *(undefined4 *)(iVar1 + 0x1c) = 0x997dee17; // +0x1C: another ID or hash
  *(undefined1 **)(iVar1 + 0x14) = &LAB_00981a70; // +0x14: function pointer or callback
  FUN_00982e10(); // send the message
  return;
}