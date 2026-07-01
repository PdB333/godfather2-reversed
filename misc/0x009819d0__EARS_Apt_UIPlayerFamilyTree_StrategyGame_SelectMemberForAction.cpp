// Xbox PDB: EARS_Apt_UIPlayerFamilyTree_StrategyGame_SelectMemberForAction
// FUNC_NAME: CrewLeaderComponent::onMemberSelected
void __fastcall CrewLeaderComponent::onMemberSelected(int this)
{
  uint *slotData;
  
  slotData = (uint *)(DAT_0112989c + 0x18 + *(int *)(this + 0x6c) * 0x24); // +0x6c = memberIndex, slot size 0x24
  if (slotData != (uint *)0x0) {
    *slotData = *slotData | 4; // Set flag 0x4 on slot (e.g., selected/active)
    *(undefined1 *)(this + 0x128) = 1; // +0x128 = memberSelected flag
    FUN_005a04a0("MemberSelected",0,&DAT_00d8fe44,0); // Fire event "MemberSelected"
    FUN_00981060(); // Update UI or state
    return;
  }
  return;
}