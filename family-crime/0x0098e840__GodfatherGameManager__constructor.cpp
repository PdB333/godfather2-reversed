// FUNC_NAME: GodfatherGameManager::constructor
undefined4* __fastcall GodfatherGameManager::constructor(GodfatherGameManager* this)
{
  // Call base class constructor (likely Manager::Manager or similar)
  Manager::constructor(static_cast<Manager*>(this));

  // Set secondary vtable pointer at offset 0x4C (for interface/base)
  this->someSecondaryVtable = reinterpret_cast<VirtualFunctionTable*>(0x00d918f8);

  // Store singleton global instance
  g_pGameManager = this;

  // Set primary vtable at offset 0x00
  this->vtable = reinterpret_cast<VirtualFunctionTable*>(0x00d91920);

  // Set another vtable at offset 0x10 (for second base class)
  this->anotherBaseVtable = reinterpret_cast<VirtualFunctionTable*>(0x00d918fc);

  // Zero out a block of 18 DWORDs (offsets 0x50 to 0x94) and a byte at 0x9C
  for (int i = 0; i < 0x12; ++i)
  {
    this->someFieldArray[i] = 0; // offset 0x50 + i*4
  }
  *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(this) + 0x9C) = 0; // flag byte

  return this;
}