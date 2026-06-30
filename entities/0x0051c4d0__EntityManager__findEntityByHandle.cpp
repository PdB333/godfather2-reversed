// FUNC_NAME: EntityManager::findEntityByHandle
int EntityManager::findEntityByHandle(int this, undefined4 handle)
{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = 0;
  if (0 < *(short *)(this + 0x80)) { // +0x80: entityCount (short)
    piVar2 = (int *)(this + 0xf4); // +0xf4: entityArray (array of pointers, stride 20 bytes = 5 ints)
    do {
      if ((*piVar2 != 0) && (iVar1 = (**(code **)(*(int *)*piVar2 + 0x38))(handle), iVar1 != 0)) {
        // +0x38: vtable offset for "matchesHandle" or "getHandle" virtual function
        return iVar1;
      }
      iVar3 = iVar3 + 1;
      piVar2 = piVar2 + 5; // stride 20 bytes (5 ints) per entity slot
    } while (iVar3 < *(short *)(this + 0x80));
  }
  return 0;
}