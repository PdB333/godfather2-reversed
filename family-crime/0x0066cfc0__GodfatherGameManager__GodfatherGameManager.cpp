// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Address: 0x0066cfc0
// Constructor for the top-level game manager. Sets vtable, calls base class constructor,
// initializes global initialization flag, and runs subsystem init. If dynamically allocated,
// optionally calls destructor on error (likely for placement new).

undefined4 * __thiscall GodfatherGameManager::GodfatherGameManager(undefined4 *this, byte allocated)
{
  // Set primary vtable pointer (offset 0x00)
  *this = &s_GodfatherGameManagerVTable;

  // Set secondary vtable pointer (offset 0x08) – possibly for a base class or interface
  this[2] = &s_BaseClassVTable1;

  // Call virtual function (index 3) on the object pointed to by param_1[3] (offset 0x0C)
  // This is likely a base class constructor call via a contained subobject.
  (**(code **)(*(int *)this[3] + 12))();

  // Update secondary vtable pointer to a different table (offset 0x08)
  this[2] = &s_BaseClassVTable2;

  // Clear global initialization flag
  gGameManagerInitialized = 0;

  // Call subsystem initialization routine
  initializeSystems();

  // If the object was dynamically allocated (allocated != 0), call the associated destructor
  // to clean up memory on construction failure (standard EA practice).
  if ((allocated & 1) != 0) {
    destructor(this);
  }

  return this;
}