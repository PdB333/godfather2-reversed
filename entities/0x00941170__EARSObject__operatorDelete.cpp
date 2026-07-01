// FUNC_NAME: EARSObject::operatorDelete
int * __thiscall operatorDelete(int *thisPtr, byte flags)
{
  int *vtable;
  int *refCount;
  
  FUN_004226c0(); // Possibly _lock or debug validation
  vtable = (int *)*thisPtr;
  refCount = vtable + 1;
  *refCount = *refCount + -1;
  if (*refCount == 0) {
    (**(code **)(*vtable + 4))(); // vtable[1] = destructor
  }
  if ((flags & 1) != 0) {
    FUN_009c8eb0(thisPtr); // Likely operator delete/free
  }
  return thisPtr;
}