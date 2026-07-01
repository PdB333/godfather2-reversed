// FUNC_NAME: SomeClass::Constructor
// Function at 0x0098f1e0: Constructor for an object in EA EARS engine.
// Calls base initializer (FUN_0098f0c0) and optionally allocates 128-byte buffer if parameter flag has bit 0 set.
// This pattern is common in EA frameworks (e.g., objects that can be stack or heap allocated).
// Reconstructed as a __thiscall returning `this`.

undefined4 __thiscall SomeClass::Constructor(SomeClass *this, byte bAllocateBuffer)
{
  // Base class / common initialization
  this->initBase();  // FUN_0098f0c0

  // If the low bit of bAllocateBuffer is set, allocate a 0x80 (128) byte internal buffer
  if ((bAllocateBuffer & 1) != 0) {
    this->allocateInternalBuffer(this, 0x80);  // FUN_0043b960 - likely placement new or allocator
  }

  return this;
}