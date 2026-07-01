// FUNC_NAME: EARSObject::destructor
int __thiscall EARSObject::destructor(int this, byte flags)
{
  undefined4 *puVar1;
  int iVar2;
  
  if ((flags & 2) != 0) {
    // Deleting array of objects
    iVar2 = *(int *)(this + -4) + -1;
    if (-1 < iVar2) {
      puVar1 = (undefined4 *)(*(int *)(this + -4) * 0x34 + this + 0x10);
      do {
        // Destroy each element in the array
        if (puVar1[-0xb] != 0) {
          (*(code *)puVar1[-8])(puVar1[-0xb]);
        }
        if (puVar1[-0x10] != 0) {
          (*(code *)puVar1[-0xd])(puVar1[-0x10]);
        }
        iVar2 = iVar2 + -1;
        puVar1 = puVar1 + -0xd;
      } while (-1 < iVar2);
    }
    if ((flags & 1) != 0) {
      FUN_009c8f10(this + -4); // operator delete[]
    }
    return this + -4;
  }
  // Single object destruction
  if (*(int *)(this + 0x18) != 0) {
    (**(code **)(this + 0x24))(*(int *)(this + 0x18));
  }
  if (*(int *)(this + 4) != 0) {
    (**(code **)(this + 0x10))(*(int *)(this + 4));
  }
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // operator delete
  }
  return this;
}