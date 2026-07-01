// FUNC_NAME: EARSObject::constructor
void __fastcall EARSObject::constructor(undefined4 *this)
{
  // Call base class constructor (likely EARS::Framework::Object or similar)
  // 0xfe84b724 is a vtable offset or type ID, 4 is size/alignment
  FUN_0083f250(0xfe84b724, 4);
  
  // Set vtable pointer at offset +0x158 (0x56 * 4)
  this[0x56] = &PTR_LAB_00d74158;
  
  // Store this pointer in global DAT_0112a694 (likely singleton instance)
  DAT_0112a694 = this;
  
  // Set primary vtable pointer at offset +0x0
  *this = &PTR_FUN_00d74178;
  
  // Set additional vtable/interface pointers:
  // +0x3C (0xF * 4) - likely an interface or secondary vtable
  this[0xf] = &PTR_LAB_00d74164;
  // +0x48 (0x12 * 4) - another interface
  this[0x12] = &PTR_LAB_00d74160;
  // +0x158 (0x56 * 4) - override previous vtable
  this[0x56] = &PTR_LAB_00d7415c;
  
  return;
}