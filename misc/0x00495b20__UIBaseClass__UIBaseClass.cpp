// FUNC_NAME: UIBaseClass::UIBaseClass
undefined4 * __thiscall UIBaseClass::UIBaseClass(UIBaseClass *this)

{
  int iVar1;
  undefined4 *src;
  undefined4 *dest;
  
  // Set vtable pointer (class VTable at 0x00e34fc0)
  this->vtable = (VTable *)&PTR_LAB_00e34fc0;
  
  // Call base class initializer
  UIBaseClass::initBase(this);
  
  // Initialize fields at offsets 0x18 and 0x1C to 0, then zero-fill a large block
  // (offset 0x20 to 0xF8? Actually 0x3a * 4 = 0xE8 bytes from offset 0x20)
  this->field_0x18 = 0;   // +0x18
  this->field_0x1C = 0;   // +0x1C
  src = &this->field_0x18; // start of source (two dwords)
  dest = &this->field_0x20; // start of destination
  for (iVar1 = 0x3a; iVar1 != 0; iVar1 = iVar1 + -1) {
    *dest = *src;
    src = src + 1;
    dest = dest + 1;
  }
  
  // Set specific color/ID values
  this->field_0x68 = 0xff0101;     // +0x68 (default color/ID)
  this->field_0x40 = 0xff0001;     // +0x40
  this->field_0x44 = 0;            // +0x44
  this->field_0x6C = 0;            // +0x6C
  this->field_0x0C = 0x3e80101;    // +0x0C
  this->field_0x10 = 0x3e80201;    // +0x10
  
  return this;
}