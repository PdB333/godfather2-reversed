// FUNC_NAME: EARSObject::destructor
void __fastcall EARSObject::destructor(int thisPtr)
{
  // Check if the object at +0x4c is non-null and release it
  if (*(int *)(thisPtr + 0x4c) != 0) {
    FUN_004df600(); // Likely operator delete or release
  }
  // Check if the object at +0x50 is non-null and release it
  if (*(int *)(thisPtr + 0x50) != 0) {
    FUN_004df600(); // Likely operator delete or release
  }
  // Call base class destructor or cleanup
  FUN_00481570(); // Base destructor
  // Decrement global reference count or unregister from manager
  FUN_004086d0(&DAT_012069c4); // Global object list or reference counter
}