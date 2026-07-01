// Xbox PDB: EARS_Apt_UIScoreboard_HideRespawnTimer
// FUNC_NAME: HudManager::hideUIElements
void __thiscall HudManager::hideUIElements(int thisPtr, uint hideFlags)
{
  // Store hide flags at offset +0x5C (likely member: m_hideFlags)
  *(uint *)(thisPtr + 0x5c) = hideFlags;

  // Send script command to hide CSA (Crew Style Action) message
  callLuaFunction("HideCSAMessage", 0, &DAT_00d77dc0, 0);

  // Send script command to hide respawn timer
  callLuaFunction("HideRespawnTimer", 0, &DAT_00d77dc0, 0);

  // Additional cleanup / state update
  HudManager::updateHiddenState(thisPtr);
}