// FUNC_NAME: EngineObject::initFromSource
void __fastcall EngineObject::initFromSource(EngineObject *this, int sourceObject)
{
  this->field_0x04 = 0;
  this->field_0x08 = 0;
  this->vtablePtr = &PTR_LAB_00e42d64;                  // Set vtable/class descriptor
  this->field_0x10 = *(uint32_t *)(sourceObject + 0x10);
  this->field_0x0C = *(uint32_t *)(sourceObject + 0x0C);
  *(uint8_t *)(this + 0x14) = 0;                        // Zero the byte at offset +0x14
  return;
}