// FUNC_NAME: Player::isInSameFamilyOrAlly
undefined1 __thiscall Player::isInSameFamilyOrAlly(int this, int otherPlayer)
{
  undefined1 result;
  
  result = 0;
  // Check if family IDs match (family ID stored at +0x1ee8 in player object)
  if (*(int *)(otherPlayer + 0x1ee8) == *(int *)(this + 0x38)) {
    return 1;
  }
  // If other player has no family (family ID == 0) and this player has a don (+0xd4 != 0)
  if ((*(int *)(otherPlayer + 0x1ee8) == 0) && (*(int *)(this + 0xd4) != 0)) {
    // Check if this player is allied with the other player's family
    result = FUN_006aecf0(otherPlayer, _DAT_00d5e20c, 1);
  }
  return result;
}