// EARSObject::constructor
undefined4 __thiscall EARSObject::constructor(byte flags)
{
  // Call base class initializer (likely memset or vtable setup)
  EARSObject::initializeBase();

  // If the object was heap-allocated (flags & 1), invoke the per-class memory manager
  // Global class registry at DAT_01223410; offset 0x2D4 holds this class's memory management vtable.
  // The function at vtable+4 is the deallocation (e.g., operator delete or release).
  if (flags & 1)
  {
    (*(void (__thiscall **)(EARSObject*, uint))(*(int*) (g_ClassRegistry + 0x2D4) + 4))(this, 0);
  }

  return this;
}