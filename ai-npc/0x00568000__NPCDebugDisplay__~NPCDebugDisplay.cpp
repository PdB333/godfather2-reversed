// FUNC_NAME: NPCDebugDisplay::~NPCDebugDisplay
// Function address: 0x00568000
// This function is the destructor for NPCDebugDisplay. It releases sub-objects, cleans up vtable pointers, and clears a global flag.

void __thiscall NPCDebugDisplay::~NPCDebugDisplay(NPCDebugDisplay *this)
{
  // Adjust vtable pointers for multiple inheritance during destruction
  *(int *)this = (int)&g_vtable_NPCDebugDisplay;            // +0x00: set primary vtable
  *(int *)((char *)this + 4) = (int)&g_secondaryVtable1;    // +0x04: set secondary vtable

  // If a sub-object exists at offset 0x34, call its virtual function (index 2, +8)
  if (*(void **)((char *)this + 0x34) != (void *)0x0)
  {
    (**(void (__thiscall ***)(NPCDebugDisplay *))(*(int *)((char *)this + 0x34) + 8))(this);
  }
  // Clear the pointer at offset 0x34
  *(int *)((char *)this + 0x34) = 0;

  // If a managed object at offset 0x350 exists, delete it via its function pointer at offset 0x35c
  if (*(int *)((char *)this + 0x350) != 0)
  {
    (*(void (__cdecl **)(int))(*(int *)((char *)this + 0x35c)))(*(int *)((char *)this + 0x350));
  }

  // Set base class vtable to purecall (final cleanup)
  *(int *)((char *)this + 0x34c) = (int)&g_purecall_vtable;   // +0x34c: base vtable
  *(int *)((char *)this + 0x38) = (int)&g_someFunction;       // +0x38: another vtable entry

  // External cleanup function (likely a global destructor or allocator teardown)
  FUN_00ad9db0();

  // Release another sub-object at offset 0x10 via function pointer at offset 0x1c
  if (*(int *)((char *)this + 0x10) != 0)
  {
    (*(void (__cdecl **)(int))(*(int *)((char *)this + 0x1c)))(*(int *)((char *)this + 0x10));
  }

  // Adjust secondary vtable again
  *(int *)((char *)this + 4) = (int)&g_secondaryVtable2;     // +0x04: final secondary vtable

  // Clear global flag indicating debug display is active
  g_debugDisplayActiveFlag = 0;   // 0x01223484

  // Finalize primary vtable to purecall
  *(int *)this = (int)&g_purecall_vtable_primary;            // +0x00: final pure vtable
}