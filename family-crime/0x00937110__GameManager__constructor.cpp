// FUNC_NAME: GameManager::constructor
void __thiscall GameManager::constructor(GameManager *this)

{
  // Set vtable pointer at offset 0x00
  *this = &vtable_GameManager;

  // Set another pointer at offset 0x10 (likely a function table or static data)
  this->field_0x10 = &g_GameManagerStaticData1;

  // Set pointer at offset 0x4C (maybe a secondary vtable or resource pointer)
  // Note: The decompiler shows two assignments to the same offset; the second might be
  // a different field if offsets are miscalculated, but we keep as is.
  this->field_0x4C = &g_GameManagerStaticData2;
  this->field_0x4C = &g_GameManagerStaticData3;

  // Reset global initialization flag
  g_bGameManagerInitialized = 0;

  // Call global initializer (likely sets up static resources)
  GameManager::staticInitialize();
  return;
}