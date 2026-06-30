// FUNC_NAME: Entity::activateResource
void __fastcall Entity::activateResource(int thisPtr)
{
  if (DAT_012058e8 != thisPtr) {
    *(int *)(thisPtr + 0xa4) = 1;    // +0xa4: m_active flag
    DAT_012058e8 = thisPtr;          // Global active entity pointer
    FUN_0060a460(*(int *)(thisPtr + 0x10)); // likely resource reference or callback
    FUN_0060a460(*(int *)(thisPtr + 0x14)); // another resource or cleanup
    return;
  }
  *(int *)(thisPtr + 0xa4) = 0;      // Deactivate if already active
  return;
}