// FUNC_NAME: SimNpc::setTargetEntity
int __thiscall SimNpc::setTargetEntity(int thisPtr, int targetPtr)
{
  // Compare current target entity at +0xC4 with target's target entity at +0x150
  if (*(int *)(thisPtr + 0xC4) != *(int *)(targetPtr + 0x150)) {
    // Update the target entity reference
    *(int *)(thisPtr + 0xC4) = *(int *)(targetPtr + 0x150);
    // Call a handler for the change (e.g., recalculate state, notify AI)
    FUN_0086cb20();
  }
  return 1; // Always succeeds
}