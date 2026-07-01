// FUNC_NAME: Entity::tickBlendEffects
void __fastcall Entity::tickBlendEffects(void *thisPtr)
{
  // Check if pointer at offset +0x88 is non-null (likely an active script/state machine component)
  if (*(int *)((char *)thisPtr + 0x88) != 0) {
    // Update that component (e.g., script tick, animation state machine update)
    FUN_00922ac0(thisPtr);
  }
  // Test bit 1 (value 0x2) of the flags field at offset +0x170
  // If set, indicates a blend effect is pending or enabled
  if ((*(uint *)((char *)thisPtr + 0x170) >> 1 & 1) != 0) {
    // Apply full blend factor (1.0f) with mode 0 to the blend controller at offset +0x90
    // 0x3f800000 = 1.0f as float
    FUN_00894ea0(*(void **)((char *)thisPtr + 0x90), 1.0f, 0);
  }
}