// FUNC_NAME: EARSObject::~EARSObject
// Address: 0x004f20a0
// Destructor for EARSObject base class. Handles cleanup of a pooled pointer at offset 0x60 (0x18 * 4) and optional memory deallocation.

undefined4 * __thiscall EARSObject::~EARSObject(undefined4 *this, byte deleteFlag)
{
  int *pooledPtr;
  int *poolManager;

  // Set vtable to first destructor vtable (PTR_FUN_00e37558)
  *this = &PTR_FUN_00e37558;

  // Check if there is a pooled pointer at offset 0x60 (this[0x18])
  if (this[0x18] != 0) {
    // Access global pool manager at DAT_012068e8 + 0x14
    poolManager = (int *)(DAT_012068e8 + 0x14);
    // Set the current pool slot to a sentinel vtable (PTR_LAB_01124ba8)
    **(undefined4 **)(DAT_012068e8 + 0x14) = &PTR_LAB_01124ba8;
    // Advance pool pointer by 4 bytes
    *poolManager = *poolManager + 4;
    // Store the pooled pointer into the pool
    *(int *)*poolManager = this[0x18];
    // Advance pool pointer again
    *poolManager = *poolManager + 4;
    // Clear the pooled pointer in this object
    this[0x18] = 0;
  }

  // Set vtable to final destructor vtable (PTR_LAB_00e37304)
  *this = &PTR_LAB_00e37304;

  // If deleteFlag has bit 0 set, free the object's memory
  if ((deleteFlag & 1) != 0) {
    FUN_009c8eb0(this);  // operator delete or custom deallocation
  }

  return this;
}