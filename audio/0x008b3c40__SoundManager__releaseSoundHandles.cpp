// FUNC_NAME: SoundManager::releaseSoundHandles
void __fastcall SoundManager::releaseSoundHandles(int thisPtr)
{
  char cVar1;
  int iVar2;
  uint uVar3;
  
  // Check if sound system is initialized and active
  if (((*(int *)(DAT_01223484 + 8) != 0) && (cVar1 = FUN_00481620(), cVar1 != '\0')) &&
     (*(int *)(thisPtr + 400) != 0)) {
    uVar3 = 0;
    iVar2 = DAT_01223484;
    // Iterate through active sound handles
    if (*(int *)(thisPtr + 0x1b0) != 0) {
      do {
        // Check if handle index is valid and sound system is ready
        if ((uVar3 < *(uint *)(thisPtr + 400)) && (*(int *)(iVar2 + 0x30) != 0)) {
          // Call virtual function to stop/release each sound handle
          (**(code **)(**(int **)(iVar2 + 0x30) + 8))
                    (*(undefined4 *)(*(int *)(thisPtr + 0x18c) + uVar3 * 4));
          iVar2 = DAT_01223484;
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 < *(uint *)(thisPtr + 0x1b0));
    }
    // Reset handle count and free handle array
    *(undefined4 *)(thisPtr + 400) = 0;
    FUN_009c8f10(*(undefined4 *)(thisPtr + 0x18c));
    *(undefined4 *)(thisPtr + 0x18c) = 0;
    *(undefined4 *)(thisPtr + 0x194) = 0;
  }
  return;
}