// FUNC_NAME: EARSObject::constructor
int __thiscall EARSObject::constructor(int this, byte constructorFlags)
{
  // Call base class constructor (FUN_004758c0)
  baseConstructor();

  // If the complete object flag is set, call the second virtual function (post-initialization)
  if ((constructorFlags & 1) != 0)
  {
    // Obtain vtable pointer from global class data table
    // DAT_01223410 is a global pointer to a structure containing vtable pointers
    // Offset 0x2d4 holds the vtable pointer for this class
    void **vtable = *(void ***)(g_pClassVTables + 0x2d4);
    // Call virtual function at index 1 (offset 0x4) with argument 0
    ((void (__thiscall *)(int, int))vtable[1])(this, 0);
  }

  return this;
}