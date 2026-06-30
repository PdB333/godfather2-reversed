// FUNC_NAME: EARSObject::constructor
uint * EARSObject::constructor(uint *this)
{
  *this = *this & 0xffff8001 | 1;  // Set object type flags: bit0=1 (active), clear bits 1-14
  *(undefined2 *)((int)this + 2) = 0;  // Clear +2 bytes (likely subtype/flags)
  *this = *this | 0x8000;  // Set bit15 (some flag, e.g., "initialized" or "inWorld")
  FUN_005a0980();  // Call base class or subsystem init (e.g., EARS::Object::init)
  this[8] = 0xbeefceec;  // Set magic number at offset +0x20 (8*4) for validation
  return this;
}