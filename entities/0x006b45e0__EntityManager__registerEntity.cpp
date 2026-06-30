// FUNC_NAME: EntityManager::registerEntity
void __thiscall EntityManager::registerEntity(int thisPtr, int *entityList, int entity, char param4)
{
  uint uVar1;
  bool bVar2;
  char cVar3;
  uint uVar4;
  int iVar5;
  int *piVar6;
  undefined **local_14;
  int local_10;
  undefined4 local_c;
  undefined ***local_8;
  undefined1 local_4;
  
  bVar2 = true;
  // Check if entity should be hidden (param4 == 0, this+0xd4 != 0, and some global condition)
  if (((param4 == '\0') && (*(int *)(thisPtr + 0xd4) != 0)) &&
     (cVar3 = FUN_00791230(), cVar3 != '\0')) {
    bVar2 = false;
  }
  // Set/clear hidden flag (0x800000) on entity's flags at +0x5c
  if (bVar2) {
    *(uint *)(entity + 0x5c) = *(uint *)(entity + 0x5c) | 0x800000;
  }
  else {
    *(uint *)(entity + 0x5c) = *(uint *)(entity + 0x5c) & 0xff7fffff;
  }
  // Clear bit 26 (0x4000000) and set bit 27 (0x8000000) on entity flags
  *(uint *)(entity + 0x5c) = *(uint *