// FUNC_NAME: Object::initializeManagerLink
void __thiscall Object::initializeManagerLink(Object *thisPtr)
{
  int *managerPtr;
  
  managerPtr = getSomeManager();
  if (managerPtr == (int *)0x0) {
    managerPtr = (int *)0x0;
  }
  else {
    managerPtr = (int *)((int)managerPtr + -0x58); // Subtract offset to get containing object
  }
  // Store the resulting pointer at offset +0x190 (param_1[100])
  *((int **)&thisPtr->field_0x190) = managerPtr;
  // Call virtual function at vtable+0x1a0 (index 104)
  (*(thisPtr->vtable + 0x1a0))();
  return;
}