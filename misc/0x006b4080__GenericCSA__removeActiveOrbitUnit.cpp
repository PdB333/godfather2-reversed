// FUNC_NAME: GenericCSA::removeActiveOrbitUnit
int __fastcall GenericCSA::removeActiveOrbitUnit(int this)
{
  int removedOrbitUnit;
  char cVar2;
  int iVar3;
  uint index;
  
  index = 0;
  if (*(int *)(this + 0xb8) == 0) { // +0xB8: numActiveOrbitUnits
    return 0;
  }
  while( true ) {
    removedOrbitUnit = *(int *)(*(int *)(this + 0xb4) + index * 4); // +0xB4: activeOrbitUnitArray
    iVar3 = FUN_007914e0(); // Get current NPC ID or state
    if ((iVar3 == *(int *)(this + 0x40)) && (iVar3 = FUN_00791750(), iVar3 < 3)) break; // Check if the NPC is the current player and in a state < 3
    index = index + 1;
    if (*(uint *)(this + 0xb8) <= index) { // +0xB8: numActiveOrbitUnits
      return 0;
    }
  }
  if (index != *(int *)(this + 0xb8) - 1U) { // +0xB8: numActiveOrbitUnits
    // Shift last element into removed slot
    *(undefined4 *)(*(int *)(this + 0xb4) + index * 4) =
         *(undefined4 *)(*(int *)(this + 0xb4) + -4 + *(int *)(this + 0xb8) * 4);
  }
  *(int *)(this + 0xb8) = *(int *)(this + 0xb8) + -1; // Decrement count
  if (removedOrbitUnit != 0) {
    iVar3 = FUN_00791300(); // Get some object from the removed unit
    if ((iVar3 != 0) && (*(int *)(iVar3 + 0x158) != 0)) { // +0x158: some pointer
      *(undefined4 *)(iVar3 + 0x158) = 0;
      cVar2 = FUN_0083e6a0(iVar3); // Check if something is active
      if (cVar2 != '\0') {
        FUN_0083de30(iVar3); // Deactivate/stop something
      }
    }
    FUN_006b2f70(); // GenericCSA::decreaseReferenceCount or similar
  }
  return removedOrbitUnit;
}