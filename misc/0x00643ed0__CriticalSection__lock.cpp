// FUNC_NAME: CriticalSection::lock
PRTL_CRITICAL_SECTION_DEBUG CriticalSection::lock(void)
{
  LPCRITICAL_SECTION this;
  
  EnterCriticalSection(this);
  this[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&(this[1].DebugInfo)->Type + 1);
  return this[1].DebugInfo;
}