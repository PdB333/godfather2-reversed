// FUNC_NAME: InputManager::initSingleton
void InputManager::initSingleton(void)
{
  // Clear a large data block (0x240 bytes) starting at offset 4 (mData)
  _memset(this + 1, 0, 0x240);

  // Set member fields after the data block
  this->field_0x91 = 0;   // +0x244
  this->field_0x92 = 0;   // +0x248
  this->field_0x93 = 0;   // +0x24C
  this->field_0x94 = 0;   // +0x250
  this->field_0x95 = 0;   // +0x254
  this->field_0x96_byte = 0; // +0x258 (byte)

  // Set vtable pointer
  this->vtable = &PTR_FUN_00e3fd80;  // vtable for InputManager

  // Store singleton pointer
  g_InputManager = this;  // DAT_01223514 -> global singleton pointer
}