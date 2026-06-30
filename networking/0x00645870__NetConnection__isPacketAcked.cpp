// FUNC_NAME: NetConnection::isPacketAcked
bool NetConnection::isPacketAcked(int param_1)

{
  LPCRITICAL_SECTION lpCriticalSection;
  int iVar1;
  uint uVar2;
  int unaff_EDI;
  bool bVar3;
  
  lpCriticalSection = *(LPCRITICAL_SECTION *)(param_1 + 0x4e8);
  if (lpCriticalSection != (LPCRITICAL_SECTION)0x0) {
    EnterCriticalSection(lpCriticalSection);
    lpCriticalSection[1].DebugInfo =
         (PRTL_CRITICAL_SECTION_DEBUG)((int)&(lpCriticalSection[1].DebugInfo)->Type + 1);
  }
  uVar2 = *(uint *)((*(uint *)(unaff_EDI + 4) & 0x7ffffff8) + 4 + unaff_EDI) & 1;
  if (uVar2 == 0) {
    iVar1 = FUN_00644f40(unaff_EDI);
  }
  else {
    iVar1 = FUN_00645060(unaff_EDI);
  }
  bVar3 = iVar1 == 0;
  if (bVar3) {
    bVar3 = false;
    if ((uVar2 == 0) && (unaff_EDI == *(int *)(unaff_EDI + 0xc))) {
      bVar3 = unaff_EDI != *(int *)(param_1 + 0x440);
    }
    bVar3 = !bVar3;
  }
  if (lpCriticalSection != (LPCRITICAL_SECTION)0x0) {
    lpCriticalSection[1].DebugInfo =
         (PRTL_CRITICAL_SECTION_DEBUG)((int)&lpCriticalSection[1].DebugInfo[-1].SpareWORD + 1);
    LeaveCriticalSection(lpCriticalSection);
  }
  return bVar3;
}