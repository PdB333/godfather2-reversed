// FUNC_NAME: EARSMemoryManager::EARSMemoryManager
void __thiscall EARSMemoryManager::EARSMemoryManager(EARSMemoryManager *this)
{
  // +0x04: some flag (initialized to 1)
  this->field_04 = 1;
  // +0x08: another field (initialized to 0)
  this->field_08 = 0;
  // +0x0C: vtable pointer for base class (B) – final value after reassignment
  this->baseB_vtable = (void *)&PTR_LAB_00e31710;
  // Global instance pointer
  g_pMemoryManager = this;
  // +0x00: main vtable pointer
  this->vtable = &PTR_FUN_00e31700;
  // +0x0C: first set to one base, then overridden (see above)
  this->baseB_vtable = (void *)&PTR_LAB_00e31710;  // (already set, left for clarity)
  // +0x10: debug sentinel value
  this->debug1 = 0xbadbadba;
  // +0x14: debug sentinel value
  this->debug2 = 0xbeefbeef;
  // +0x18: debug sentinel value
  this->debug3 = 0xeac15a55;
  // +0x20: debug sentinel value
  this->debug4 = 0xbadbadba;
  // +0x24: debug sentinel value
  this->debug5 = 0xbeefbeef;
  // +0x28: debug sentinel value
  this->debug6 = 0xeac15a55;
  // +0x30: clear to zero
  this->field_30 = 0;
  // +0x34: clear to zero
  this->field_34 = 0;
  // +0x38: clear to zero
  this->field_38 = 0;
  // +0x1C: clear to zero
  this->field_1C = 0;
  // +0x18: clear sentinel
  this->debug3 = 0;
  // +0x14: clear sentinel
  this->debug2 = 0;
  // +0x10: clear sentinel
  this->debug1 = 0;
  // +0x2C: clear to zero
  this->field_2C = 0;
  // +0x28: clear sentinel
  this->debug6 = 0;
  // +0x24: clear sentinel
  this->debug5 = 0;
  // +0x20: clear sentinel
  this->debug4 = 0;
}