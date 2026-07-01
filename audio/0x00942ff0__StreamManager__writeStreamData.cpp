// FUNC_NAME: StreamManager::writeStreamData
void __thiscall StreamManager::writeStreamData(void *this, undefined4 param_2, undefined4 param_3, undefined4 param_4)
{
  // Dereference the current write pointer (+0x14) and write param_2
  **(undefined4 **)((int)this + 0x14) = param_2;
  // Advance the write pointer by 4 bytes
  *(int *)((int)this + 0x14) = *(int *)((int)this + 0x14) + 4;
  // Call helper to write param_3 (likely a size or type) with alignment 4
  FUN_0049c430(&param_3, 4, 4);
  // Dereference the current write pointer and write param_4
  **(undefined4 **)((int)this + 0x14) = param_4;
  // Advance the write pointer by 4 bytes
  *(int *)((int)this + 0x14) = *(int *)((int)this + 0x14) + 4;
}