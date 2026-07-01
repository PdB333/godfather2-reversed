// FUNC_NAME: SomeManager::SomeManager (constructor at 0x911960)
// This function appears to be a constructor for a class (likely derived from a base class).
// It initializes vtable pointers and zeroes out various fields.
// The object size is at least 0x2F9 bytes based on writes to offsets up to 0x2F9.
// Base class constructor is called at 0x5BF9B0.

__thiscall SomeManager::SomeManager()

{
  // Call base class constructor
  BaseClassConstructor(); // FUN_005bf9b0

  // Set vtable pointer at offset 0x4C (19th uint) to a specific vtable
  *((uint32_t*)(this + 0x4C)) = 0x00D83B2C; // &PTR_LAB_00d83b2c

  // Store this pointer in a global data pointer (possibly singleton)
  gSomeManagerGlobal = this; // DAT_01130000 = param_1

  // Set primary vtable pointer at offset 0x00 to a vtable
  *((uint32_t*)(this + 0x00)) = 0x00D83EB0; // &PTR_FUN_00d83eb0

  // Set secondary vtable at offset 0x10 to another vtable
  *((uint32_t*)(this + 0x10)) = 0x00D83E88; // &PTR_LAB_00d83e88

  // Set/override vtable at offset 0x4C to a different vtable
  *((uint32_t*)(this + 0x4C)) = 0x00D83E84; // &PTR_LAB_00d83e84

  // Set vtable at offset 0x50 (20th uint) to a base vtable
  *((uint32_t*)(this + 0x50)) = 0x00D83B18; // &PTR_LAB_00d83b18

  // Set multiple vtable entries (likely for an array of sub-objects or interface slots)
  // All set to the same pointer: 0x00D83B18
  *((uint32_t*)(this + 0xD4)) = 0x00D83B18; // param_1[0x35]
  *((uint32_t*)(this + 0x158)) = 0x00D83B18; // param_1[0x56]
  *((uint32_t*)(this + 0x1DC)) = 0x00D83B18; // param_1[0x77]
  *((uint32_t*)(this + 0x260)) = 0x00D83B18; // param_1[0x98]

  // Clear flags/fields at various byte offsets
  // Clear uint at offset 0x2E8
  *((uint32_t*)(this + 0x2E8)) = 0;           // param_1[0xba] = 0
  // Clear byte at offset 0x2EC
  *((uint8_t*)(this + 0x2EC)) = 0;            // *(byte*)(param_1 + 0xbb) = 0
  // Clear byte at offset 0x2ED
  *((uint8_t*)(this + 0x2ED)) = 0;            // *(byte*)((int)param_1 + 0x2ed) = 0

  // Clear uint at offset 0x2F4
  *((uint32_t*)(this + 0x2F4)) = 0;           // param_1[0xbd] = 0
  // Clear byte at offset 0x2F8
  *((uint8_t*)(this + 0x2F8)) = 0;            // *(byte*)(param_1 + 0xbe) = 0
  // Clear byte at offset 0x2F9
  *((uint8_t*)(this + 0x2F9)) = 0;            // *(byte*)((int)param_1 + 0x2f9) = 0

  // Set uint at offset 0x2F0 to 6 (possibly a version or count)
  *((uint32_t*)(this + 0x2F0)) = 6;           // param_1[0xbc] = 6

  return this;
}