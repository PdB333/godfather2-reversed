// FUNC_NAME: EARSObject::reinitialize
void __thiscall EARSObject::reinitialize(EARSObject *this)
{
  // Set initial vtable pointers (base class vtables)
  this->vtable = &VTable_Base;                          // +0x00
  this->vtable2 = &VTable_Sub1;                          // +0x3C (offset 0xf * 4)
  this->vtable3 = &VTable_Sub2;                          // +0x48 (offset 0x12 * 4)
  this->vtable4 = &VTable_Sub3;                          // +0x50 (offset 0x14 * 4)

  // If object has been previously registered (ID != -1), unregister it
  if (this->engineId != -1)                              // +0x74 (offset 0x1d * 4)
  {
    unregisterFromEngine();                              // 0x00441e00
  }

  // Free global resource references
  freeResource(&g_resource1);                            // DAT_0120e93c
  freeResource(&g_resource2);                            // DAT_0120e924

  // Free and reinitialize internal child objects
  freeResource(&this->childObject1);                     // +0x54 (offset 0x15 * 4)
  initializeChildObject(&this->childObject1);            // placement new / ctor

  freeResource(&this->childObject2);                     // +0x5c (offset 0x17 * 4)
  initializeChildObject(&this->childObject2);

  initializeChildObject(&this->childObject3);            // +0x64 (offset 0x19 * 4)

  // Rebuild internal state (virtual reset)
  rebuildInternalState(this);                            // 0x00477cd0

  // Switch to final vtable (most derived)
  this->vtable4 = &VTable_Derived;                       // +0x50

  // Final global initialisation
  performGlobalInit();                                   // 0x0046c640
}