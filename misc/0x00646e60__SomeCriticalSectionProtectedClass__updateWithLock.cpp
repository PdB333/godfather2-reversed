// FUNC_NAME: SomeCriticalSectionProtectedClass::updateWithLock
void __fastcall SomeCriticalSectionProtectedClass::updateWithLock(int thisPtr)
{
  LPCRITICAL_SECTION criticalSection;
  
  criticalSection = *(LPCRITICAL_SECTION *)(thisPtr + 0x4e8); // +0x4E8: critical section pointer
  if (criticalSection != (LPCRITICAL_SECTION)0x0) {
    EnterCriticalSection(criticalSection);
    // Increment lock count (hacky debug info manipulation)
    criticalSection[1].DebugInfo =
         (PRTL_CRITICAL_SECTION_DEBUG)((int)&(criticalSection[1].DebugInfo)->Type + 1);
  }
  
  // Call the actual update logic
  FUN_00646ea0(thisPtr);
  
  if (criticalSection != (LPCRITICAL_SECTION)0x0) {
    // Decrement lock count
    criticalSection[1].DebugInfo =
         (PRTL_CRITICAL_SECTION_DEBUG)((int)&criticalSection[1].DebugInfo[-1].SpareWORD + 1);
    LeaveCriticalSection(criticalSection);
  }
  return;
}