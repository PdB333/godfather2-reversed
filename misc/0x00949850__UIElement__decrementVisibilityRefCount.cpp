// FUNC_NAME: UIElement::decrementVisibilityRefCount
void __fastcall UIElement::decrementVisibilityRefCount(int thisPtr)
{
  char buffer[256]; // local_100
  int *refCountPtr = (int *)(thisPtr + 400); // +0x190: visibility reference count
  
  *refCountPtr = *refCountPtr - 1;
  if ((*refCountPtr == 0) && (*(char *)(thisPtr + 0x18) != '\0')) { // +0x18: name string
    __snprintf(buffer, 0x100, "%s._visible", thisPtr + 0x18);
    FUN_0059ee00(buffer, 1); // likely setProperty or setScriptVar
  }
}