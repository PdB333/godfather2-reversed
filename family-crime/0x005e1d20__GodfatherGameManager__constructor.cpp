// FUNC_NAME: GodfatherGameManager::constructor

void __thiscall GodfatherGameManager::constructor(GodfatherGameManager *this)
{
  // Set vtable to initial table (likely base class or intermediate)
  *(void **)this = &PTR_FUN_00e3f470;

  // Call base class or member initialization function
  baseClassInit(this); // FUN_005e1e50

  // Free a sub-object if it exists (pointer at offset +0x1738)
  if (*(int *)((int)this + 0x1738) != 0) {
    freeSubObject(*(void **)((int)this + 0x1738)); // FUN_009c8f10
  }

  // Initialize 4 slots (e.g., player slots, controller slots, etc.)
  int i = 4;
  do {
    initSlot(); // FUN_005e8260
    i--;
  } while (i >= 0);

  // Switch to final vtable (full class)
  *(void **)this = &PTR_LAB_00e3f474;

  // Clear a global flag
  g_gameManagerConstructed = 0; // DAT_0122350c
}