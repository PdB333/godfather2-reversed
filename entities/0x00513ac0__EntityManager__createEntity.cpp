// FUNC_NAME: EntityManager::createEntity
void EntityManager::createEntity(int *param_1)

{
  LPCRITICAL_SECTION lpCriticalSection;
  int iVar1;
  int iVar2;
  int iVar3;
  int unaff_FS_OFFSET;
  
  iVar2 = DAT_0120541c;
  lpCriticalSection = *(LPCRITICAL_SECTION *)(DAT_0120541c + 0x1b8);
  iVar3 = 0;
  if (lpCriticalSection != (LPCRITICAL_SECTION)0x0) {
    EnterCriticalSection(lpCriticalSection);
    lpCriticalSection[1].DebugInfo =
         (PRTL_CRITICAL_SECTION_DEBUG)((int)&(lpCriticalSection[1].DebugInfo)->Type + 1);
  }
  iVar1 = FUN_00649040(iVar2,0x2a0);  // allocate memory for entity (size 0x2A0 = 672 bytes)
  if (iVar1 == 0) {
    if (lpCriticalSection != (LPCRITICAL_SECTION)0x0) {
      lpCriticalSection[1].DebugInfo =
           (PRTL_CRITICAL_SECTION_DEBUG)((int)&lpCriticalSection[1].DebugInfo[-1].SpareWORD + 1);
      LeaveCriticalSection(lpCriticalSection);
    }
    iVar2 = *(int *)(iVar2 + 0x17c);  // get pointer to default entity data
  }
  else {
    FUN_006492f0();  // initialize newly allocated entity memory
    iVar2 = *(int *)(iVar1 + 8);  // get pointer from allocated entity
    if (lpCriticalSection != (LPCRITICAL_SECTION)0x0) {
      lpCriticalSection[1].DebugInfo =
           (PRTL_CRITICAL_SECTION_DEBUG)((int)&lpCriticalSection[1].DebugInfo[-1].SpareWORD + 1);
      LeaveCriticalSection(lpCriticalSection);
    }
  }
  if (iVar2 != 0) {
    iVar3 = iVar2 - DAT_01205410;
    iVar2 = *(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8) + iVar3;
    if (iVar2 != 0) {
      *(undefined4 *)(iVar2 + 0x50) = 0;
      *(undefined4 *)(iVar2 + 0xa0) = 0;
      *(undefined4 *)(iVar2 + 0xf0) = 0;
      *(undefined4 *)(iVar2 + 0x140) = 0;
      *(undefined4 *)(iVar2 + 400) = 0;
      *(undefined4 *)(iVar2 + 0x1e0) = 0;
      *(undefined4 *)(iVar2 + 0x230) = 0;
      *(undefined4 *)(iVar2 + 0x280) = 0;
    }
  }
  *param_1 = iVar3;  // store entity offset
  param_1[1] = 1;    // mark as valid
  return;
}