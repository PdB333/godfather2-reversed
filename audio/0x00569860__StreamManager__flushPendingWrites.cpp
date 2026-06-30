// FUNC_NAME: StreamManager::flushPendingWrites
void __fastcall StreamManager::flushPendingWrites(int *this)
{
  int iVar1;
  int iVar2;
  
  FUN_00ab4db0(&DAT_00e2cbe8); // lock mutex
  iVar2 = this[0xca]; // +0x328: pendingWriteCount
  iVar1 = iVar2;
  for (; (iVar1 != 0 && (0 < iVar2)); iVar2 = iVar2 + -1) {
    (**(code **)(*this + 0x40))(this[0x8a]); // vtable[0x10] -> flushSingleWrite(this[0x228] -> writeBuffer)
    iVar1 = this[0xca]; // re-read pendingWriteCount
  }
  this[0x89] = 0; // +0x224: currentWriteOffset
  this[0xcb] = 0; // +0x32c: pendingWriteCount (already zeroed by loop)
  FUN_00ab4e70(); // unlock mutex
  return;
}