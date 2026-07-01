// FUNC_NAME: GameManager::~GameManager
void __fastcall GameManager::~GameManager(undefined4 *this)
{
  // Set vtable pointers to destructor-specific vtables (prevent virtual calls during destruction)
  this[0] = &PTR_FUN_00d8051c;          // +0x00: primary vtable
  this[1] = &PTR_LAB_00d8050c;          // +0x04: secondary vtable (interface)
  this[4] = &PTR_LAB_00d804fc;          // +0x10: another vtable

  // Debug/log hash (0xc8ed3b85 likely a class identifier)
  DebugPrintHash(0xc8ed3b85);

  // Release references to global singletons (pair of AddRef/Release to ensure proper refcount)
  AddRef(&g_SomeGlobal1);               // DAT_0112fdb0
  Release(&g_SomeGlobal1);
  AddRef(&g_SomeGlobal2);               // DAT_0112fdb8
  Release(&g_SomeGlobal2);
  Release(&g_SomeGlobal3);              // DAT_0112fdc0 (only Release, no AddRef? Possibly a bug or intentional)
  AddRef(&g_SomeGlobal4);               // DAT_012069c4

  // Delete child objects (offsets in 4-byte units)
  if (this[0x16] != 0) {                // +0x58
    FreeObject(this[0x16]);
  }
  if (this[0x13] != 0) {                // +0x4C
    FreeObject(this[0x13]);
  }
  if (this[0x0E] != 0) {                // +0x38
    FreeObject(this[0x0E]);
  }
  if (this[0x0B] != 0) {                // +0x2C
    FreeObject(this[0x0B]);
  }
  if (this[8] != 0) {                   // +0x20
    FreeObject(this[8]);
  }
  if (this[5] != 0) {                   // +0x14
    FreeObject(this[5]);
  }

  // Switch to final destructor vtable
  this[4] = &PTR_LAB_00e30fe0;          // +0x10: final vtable

  // Static cleanup (e.g., unregister from global lists)
  StaticCleanup();

  // Set primary vtable to a "destroyed" vtable
  this[0] = &PTR_LAB_00d804a0;          // +0x00: destroyed vtable

  // Clear global singleton flag
  g_bGameManagerDestroyed = 0;          // DAT_0112a670
}