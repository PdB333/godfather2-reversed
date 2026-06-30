// FUNC_NAME: EARSObject::setupClassDescriptor
void __thiscall EARSObject::setupClassDescriptor(EARSObject *this, uint32_t *descriptor)
{
  int magic;
  
  magic = (**(code **)*descriptor)();  // call a function on the descriptor? might be GetTypeID
  if (magic == 0x6862a74c) { // specific class hash (e.g., "SomeClass")
    FUN_0075cd50(this + 0x5c); // unknown, possibly init a member at offset 0x5c
    FUN_0075cd70(*(uint32_t *)(this + 0x68)); // unknown, uses member at +0x68
    // Set up a 64-bit pointer table (likely vtable or function map) at descriptor + 0x78 (since descriptor is uint32_t*)
    *(uint64_t *)(descriptor + 0x78) = ((uint64_t)(uint32_t)&someFunc1) << 32 | (uint32_t)this; // see note: CONCAT44(&LAB_0075a1b0, this)
    *(uint64_t *)(descriptor + 0x80) = reinterpret_cast<uint64_t>(someArg2); // from uStack_10 (not shown)
    *(uint64_t *)(descriptor + 0x88) = ((uint64_t)(uint32_t)&someFunc2) << 32 | (uint32_t)someArg; // CONCAT44(&LAB_0075a2a0, uStack_8)
    *(uint64_t *)(descriptor + 0x90) = ((uint64_t)(uint32_t)&someFunc1) << 32 | (uint32_t)this; // repeated pattern
    *(uint64_t *)(descriptor + 0x98) = reinterpret_cast<uint64_t>(someArg2); // repeat
    *(uint64_t *)(descriptor + 0xA0) = ((uint64_t)(uint32_t)&someFunc2) << 32 | (uint32_t)someArg; // repeat
    descriptor[0x2A] |= 0x60000; // set flags at offset 0xA8 (0x2A * 4)
  }
}
// Note: The CONCAT44 pattern is likely due to decompiler misrepresentation; actual code probably writes two consecutive 32-bit values.
// The constant 0x6862a74c is a class identifier hash. 0x75cd50 and 0x75cd70 are initialization subroutines.