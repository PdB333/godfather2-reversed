// FUNC_NAME: JobManager::cleanupJobList
void __fastcall JobManager::cleanupJobList(int *this)
{
  int iVar1;
  int index;
  int iVar3;
  
  index = this[1] + -1;
  if (-1 < index) {
    iVar3 = index * 0x10;
    do {
      iVar1 = *(int *)(*this + iVar3);
      if (iVar1 != 0) {
        // Call the job's destructor via vtable at offset +0xC
        (**(code **)(*this + iVar3 + 0xc))(iVar1);
      }
      index = index + -1;
      iVar3 = iVar3 + -0x10;
    } while (-1 < index);
  }
  this[1] = 0; // Set count to zero
  FUN_009c8f10(*this); // Free the job list array (likely operator delete[])
  *this = 0;   // Null the array pointer
  this[2] = 0; // Reset capacity
  return;
}