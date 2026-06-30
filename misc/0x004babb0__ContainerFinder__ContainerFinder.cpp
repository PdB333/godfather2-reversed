// FUNC_NAME: ContainerFinder::ContainerFinder
void __thiscall ContainerFinder::ContainerFinder(ContainerFinder *this, void *containerPtr, int key, uint extraData)
{
  uint index;
  int *elementPtr;
  
  this->vtable = (void **)&PTR_FUN_00e35c30;
  if ((containerPtr == 0) || (*(int *)((char *)containerPtr + 0x14) == 0)) {
    this->container = 0;
    this->data = 0;
  }
  else {
    this->container = containerPtr;
    this->data = extraData;
  }
  this->vtable = (void **)&PTR_FUN_00e35c3c;
  this->key = key;
  if (containerPtr != 0) {
    index = 0;
    if (*(uint *)((char *)containerPtr + 8) != 0) {
      elementPtr = *(int **)((char *)containerPtr + 4);
      do {
        if (elementPtr[2] == key) {
          if (*(int *)(elementPtr + 10) != 0) {
            this->container = containerPtr;
            this->data = extraData;
            return;
          }
          break;
        }
        index = index + 1;
        elementPtr = elementPtr + 0xd;
      } while (index < *(uint *)((char *)containerPtr + 8));
    }
    this->container = 0;
    this->data = 0;
  }
  return;
}