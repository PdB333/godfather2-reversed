// Xbox PDB: void __cdecl luaX_checklimit(struct LexState *,int,int,char const *)
// FUNC_NAME: ConstructionCounter::incrementInstanceCount

void __thiscall ConstructionCounter::incrementInstanceCount(void)
{
  int oldCount;
  char *warningString;
  int warningResult;

  // Call base initialization / tracking method (FUN_0063fad0)
  baseInit();

  // Load current count from offset 0x1c
  oldCount = this->m_instanceCount;  // +0x1c
  if (0x3ffff < oldCount) {
    // Issue warning if count exceeds limit (262143)
    warningString = (char *)formatString("too many %s (limit=%d)", "items in a constructor", 0x3ffff);
    warningResult = logWarning(warningString);
  }

  // Increment secondary counter at offset 0x20
  this->m_numInvocations++;  // +0x20

  // Update primary count to old value +1
  this->m_instanceCount = oldCount + 1;  // +0x1c
}