// FUNC_NAME: GameConfig::getValueByHash
void __thiscall GameConfig::getValueByHash(GameConfig *this, int *outValue, int *outDefault)
{
  // +0x2E14: m_defaultValue
  *outDefault = *(int *)((int)this + 0x2E14);
  
  // 0x4edbd77 is likely hash of a config key string
  char found = HashTableLookup(0x4edbd77, outValue);
  if (found == '\0') {
    // If lookup fails, use global fallback
    *outValue = DAT_00e448d8;
  }
  return;
}