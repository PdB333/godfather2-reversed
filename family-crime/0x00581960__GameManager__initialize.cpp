// FUNC_NAME: GameManager::initialize

void __thiscall GameManager::initialize(void)
{
  undefined4 *thisPtr;
  int *piVar1;
  undefined4 *puVar2;
  undefined4 globalConst;
  undefined4 local_18[4]; // buffer for allocation

  globalConst = DAT_00e2b1a4; // some global constant (e.g., 0x3F800000 or similar)

  // Set vtable pointer
  *thisPtr = &PTR_FUN_00e3ac24; // vtable entry

  // Initialize fields
  thisPtr[4] = 8;   // version/type? (offset +0x10)
  thisPtr[7] = 0;   // offset +0x1C
  thisPtr[8] = 0;   // offset +0x20
  thisPtr[9] = globalConst;  // offset +0x24
  thisPtr[10] = globalConst; // offset +0x28
  thisPtr[0xB] = 1;  // offset +0x2C
  *(undefined1 *)(thisPtr + 0xC) = 0; // byte at offset +0x30
  thisPtr[5] = 0xFFFFFFFF; // offset +0x14
  thisPtr[6] = 0xFFFFFFFF; // offset +0x18
  thisPtr[0x12] = 0;  // offset +0x48
  thisPtr[0x11] = 0;  // offset +0x44
  thisPtr[0x10] = 0;  // offset +0x40
  thisPtr[0x13] = globalConst; // offset +0x4C
  piVar1 = DAT_0120556c; // global pointer (e.g., allocator vtable)
  thisPtr[0x16] = 0;  // offset +0x58
  thisPtr[0x15] = 0;  // offset +0x54
  thisPtr[0x14] = 0;  // offset +0x50
  thisPtr[0x17] = globalConst; // offset +0x5C
  thisPtr[0x18] = 0;  // offset +0x60
  thisPtr[0x19] = 0;  // offset +0x64 (will be set below)
  thisPtr[0x1A] = 0;  // offset +0x68

  // Prepare allocation request
  local_18[0] = 0;
  local_18[1] = 0;
  local_18[2] = 0;
  local_18[3] = 0;

  // Allocate sub-object (size 0x14 = 20 bytes)
  puVar2 = (undefined4 *)(**(code **)*piVar1)(0x14, &local_18);
  if (puVar2 != (undefined4 *)0x0) {
    // Initialize sub-object
    local_18[1] = 0;
    local_18[2] = 0;
    local_18[3] = 0;
    globalConst = FUN_004265d0(&local_18, piVar1); // constructor? returns something
    puVar2[3] = globalConst;
    puVar2[4] = piVar1;
    // Call virtual function at offset 8 (maybe base class constructor or init)
    (**(code **)(*piVar1 + 8))();
    puVar2[0] = 0;
    puVar2[2] = 0;
    puVar2[1] = 0;
    // Store allocated sub-object pointer
    thisPtr[0x19] = puVar2; // offset +0x64
    return;
  }
  // On allocation failure, set to null
  thisPtr[0x19] = 0;
  return;
}