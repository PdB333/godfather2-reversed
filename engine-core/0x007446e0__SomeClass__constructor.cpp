// FUNC_NAME: SomeClass::constructor
// Address: 0x007446e0
// Constructor for a class with two vtable pointers (multiple inheritance). 
// First vtable at offset 0x00, second at offset 0x14.
undefined4 * __thiscall SomeClass::constructor(undefined4 *this, byte constructionFlags)
{
  // Set vtable pointers for this object
  *this = (undefined4 *)&PTR_LAB_00d63d40;       // vtable for base class 1 (offset 0x00)
  this[0x14] = (undefined4 *)&PTR_LAB_00d63d3c;  // vtable for base class 2 (offset 0x14)

  // Call base class constructor (likely an EARS engine base)
  FUN_0075cc50();

  // If bit 0 of constructionFlags is set, perform additional cleanup/destruction?
  // Possibly indicating "placement new" or custom allocator handling.
  if ((constructionFlags & 1) != 0) {
    FUN_00624da0(this);
  }

  return this;
}