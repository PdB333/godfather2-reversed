// FUNC_NAME: EARS::Framework::Object::constructor
// Address: 0x006d5f60
// Sets up vtable pointer, initializes embedded sub-object at offset +0x14,
// calls static initialization routine, and optionally handles dynamic allocation flag.

undefined4 * __thiscall EARS::Framework::Object::constructor(undefined4 *thisObj, byte isDynamic)
{
  // Set vtable to class-specific table
  *thisObj = &PTR_FUN_00d5f42c;

  // Store additional function pointers at offsets +0x3C (15*4) and +0x48 (18*4)
  thisObj[0xF] = &PTR_LAB_00d5f41c;
  thisObj[0x12] = &PTR_LAB_00d5f418;

  // Initialize sub-object at offset +0x14 (20 bytes) – likely a base class or member
  FUN_004086d0(thisObj + 0x14);
  FUN_00408310(thisObj + 0x14);

  // Call a static initialization routine (probably engine-wide or class-specific)
  FUN_0046c640();

  // If the object was dynamically allocated (bit 0 of isDynamic set),
  // perform a post-construction allocation hook or cleanup (size 0x6C = 108 bytes)
  if ((isDynamic & 1) != 0) {
    FUN_0043b960(thisObj, 0x6C);
  }

  return thisObj;
}