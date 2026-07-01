// FUNC_NAME: SimNpc::isMovingTowardsPlayerOrAlly
undefined1 __fastcall SimNpc::isMovingTowardsPlayerOrAlly(int this)
{
  undefined1 result;
  
  result = 0;
  // Check various conditions to see if this NPC is moving towards player or ally:
  // +0x08: movementState/moveType (0=idle, 4=chase/moving to player)
  // +0x1c: some flag or timer (check if <= 5)
  // +0x10: targetEntity pointer
  // +0x0c: bool? flag indicating target is enemy
  if (((((*(int *)(this + 8) == 4) || (*(int *)(this + 8) == 0)) ||
       (5 < *(int *)(this + 0x1c))) ||
      ((*(int *)(this + 0x10) != 0 && (*(char *)(this + 0xc) == '\0')))) &&
     (*(uint *)(this + 0x10) < 4)) {
    result = 1;
  }
  return result;
}