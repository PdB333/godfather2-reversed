// FUNC_NAME: MetaModelManager::MetaModelManager
undefined4 * __thiscall MetaModelManager::MetaModelManager(undefined4 *thisPtr, undefined4 parent1, undefined4 parent2)
{
  ushort uVar1;
  undefined4 allocResult;
  int iVar3;
  undefined **heapPtr;
  bool heapIsNull;
  int allocInfo[3]; // local_c, local_8, local_4

  heapPtr = gHeap; // DAT_012054bc
  heapIsNull = (gHeap == (undefined **)0x0);
  gThisSingleton = thisPtr; // DAT_0122342c

  // Initialize vtable and fields
  thisPtr[1] = &PTR_FUN_00e3522c; // first vtable
  thisPtr[2] = 0;
  thisPtr[3] = &PTR_FUN_00e2f19c; // second vtable? (overwritten later)
  thisPtr[4] = 1;
  thisPtr[5] = 0;
  thisPtr[0] = &PTR_FUN_00e31160; // main vtable

  thisPtr[1] = &PTR_LAB_00e31164; // overwritten vtable entry
  thisPtr[3] = &PTR_LAB_00e31170; // overwritten vtable entry

  thisPtr[6] = 0;
  thisPtr[7] = 0;
  thisPtr[8] = 0;
  thisPtr[9] = parent1;
  thisPtr[10] = parent2;

  // Zero out alloc info
  allocInfo[0] = 0;
  allocInfo[1] = 0;
  allocInfo[2] = 0;

  if (heapIsNull) {
    heapPtr = &PTR_PTR_0110ae94;
    gHeap = &PTR_PTR_0110ae94;
  }

  // Allocate first subobject (+0x38, +0x3C)
  allocResult = FUN_004265d0(allocInfo, heapPtr);
  thisPtr[0xe] = allocResult;  // +0x38
  thisPtr[0xf] = heapPtr;      // +0x3C
  (**(code **)(*heapPtr + 8))(); // call heap->init()?

  heapPtr = gHeap;
  heapIsNull = (gHeap == (undefined **)0x0);

  thisPtr[0xb] = 0; // +0x2C
  thisPtr[0xd] = 0; // +0x34
  thisPtr[0xc] = 0; // +0x30

  allocInfo[0] = 0;
  allocInfo[1] = 0;
  allocInfo[2] = 0;

  if (heapIsNull) {
    heapPtr = &PTR_PTR_0110ae94;
    gHeap = &PTR_PTR_0110ae94;
  }

  // Allocate second subobject (+0x4C, +0x50)
  allocResult = FUN_004265d0(allocInfo, heapPtr);
  thisPtr[0x13] = allocResult; // +0x4C
  thisPtr[0x14] = heapPtr;     // +0x50
  (**(code **)(*heapPtr + 8))();

  heapPtr = gHeap;
  heapIsNull = (gHeap == (undefined **)0x0);

  thisPtr[0x10] = 0; // +0x40
  thisPtr[0x12] = 0; // +0x48
  thisPtr[0x11] = 0; // +0x44
  thisPtr[0x15] = 0; // +0x54

  allocInfo[0] = 0;
  allocInfo[1] = 0;
  allocInfo[2] = 0;

  if (heapIsNull) {
    heapPtr = &PTR_PTR_0110ae94;
    gHeap = &PTR_PTR_0110ae94;
  }

  // Allocate third subobject (+0x64, +0x68)
  allocResult = FUN_004265d0(allocInfo, heapPtr);
  thisPtr[0x19] = allocResult; // +0x64
  thisPtr[0x1a] = heapPtr;     // +0x68
  (**(code **)(*heapPtr + 8))();

  heapPtr = gHeap;
  heapIsNull = (gHeap == (undefined **)0x0);

  thisPtr[0x16] = 0; // +0x58
  thisPtr[0x18] = 0; // +0x60
  thisPtr[0x17] = 0; // +0x5C

  allocInfo[0] = 0;
  allocInfo[1] = 0;
  allocInfo[2] = 0;

  if (heapIsNull) {
    heapPtr = &PTR_PTR_0110ae94;
    gHeap = &PTR_PTR_0110ae94;
  }

  // Allocate fourth subobject (+0x78, +0x7C)
  allocResult = FUN_004265d0(allocInfo, heapPtr);
  thisPtr[0x1e] = allocResult; // +0x78
  thisPtr[0x1f] = heapPtr;     // +0x7C
  (**(code **)(*heapPtr + 8))();

  thisPtr[0x1b] = 0; // +0x6C
  thisPtr[0x1d] = 0; // +0x74
  thisPtr[0x1c] = 0; // +0x70

  // Handle resource-related globals
  if (DAT_012069d4 != 0) {
    _DAT_012069d8 = _DAT_012069d8 + 1;
    iVar3 = FUN_00407da0();
    if (iVar3 == 0) {
      FUN_004084d0(&DAT_012069d4, 0x8000);
    } else {
      uVar1 = *(ushort *)(iVar3 + 0x14);
      *(ushort *)(iVar3 + 0x14) =
           ((short)((int)((uint)uVar1 * 2) >> 1) + 1U ^ uVar1) & 0x7fff ^ uVar1;
    }
  }

  // Copy something from global
  if (DAT_01206970 != 0) {
    FUN_00407e60(thisPtr + 3, &DAT_01206970);
  }

  // Initialize parent objects (call vtable+8 for each)
  (**(code **)(*(int *)thisPtr[9] + 8))(); // parent1->init()
  (**(code **)(*(int *)thisPtr[10] + 8))(); // parent2->init()

  // Register with meta system
  FUN_0049c6e0("MetaModel", 1);
  FUN_0049c6e0("MM_InstanceLightingData", 1);

  return thisPtr;
}