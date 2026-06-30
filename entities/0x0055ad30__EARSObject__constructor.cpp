// FUNC_NAME: EARSObject::constructor
int __thiscall EARSObject::constructor(EARSObject *this, byte placementFlag)
{
  // Call base class or common initialization function
  // FUN_0055ad60 likely performs basic initialization (e.g., vtable setup, member zeroing)
  FUN_0055ad60();

  // If the object is not being constructed as part of a larger allocation (placement new),
  // register it under a heap managed via thread-local storage.
  if ((placementFlag & 1) != 0) {
    // Retrieve the thread-local storage value (likely a heap ID or allocator pointer)
    // DAT_01139810 is the TLS index.
    TlsGetValue(DAT_01139810);

    // Register this object with class type 0x0b (11) in the allocation tracking system.
    // param_1 + 4 is the vtable pointer or object size field.
    FUN_00aa26e0(this, *(unsigned short *)(this + 4), 0xb);
  }

  return this;
}