// FUNC_NAME: ObjectRef::getPointer
int * __fastcall ObjectRef::getPointer(ObjectRef *this)
{
  uint flags = 0;
  int *dataPtr;
  int localVar;

  // Check if the object is built/present (byte at offset 0x07)
  if (*(char *)(this + 7) != '\0') {
    flags = 0;
    localVar = 0;
    // Check if a specific flag is set (byte at offset 0x03)
    if (*(char *)(this + 3) != '\0') {
      flags = 0x3000; // Some flag like "ensure built"
    }
    dataPtr = (int *)*this; // vtable pointer stored at offset 0
    // Call virtual function at vtable offset 0x2c (e.g., "getPointerInternal")
    (**(code **)(*dataPtr + 0x2c))(dataPtr, 0, 0, &localVar, flags);
    return dataPtr;
  }
  // Object is marked as not built; set destroyed/invalid flag at offset 0x1d
  *(undefined1 *)((int)this + 0x1d) = 1;
  return (int *)this[4]; // Return stored pointer at offset 0x10
}