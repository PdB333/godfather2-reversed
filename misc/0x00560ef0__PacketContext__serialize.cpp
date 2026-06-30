// FUNC_NAME: PacketContext::serialize

void __thiscall PacketContext::serialize(int thisPtr)
{
  int savedBufPtr;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int savedEBX;
  int savedESI;
  int savedEDI;
  int *piVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  int *pStack_b4;
  int local_b0;
  int iStack_ac;
  undefined4 uStack_a8;
  undefined4 *puStack_a4;
  undefined4 uStack_94;
  int iStack_90;
  int local_8c;
  uint uStack_88;
  uint uStack_84;
  undefined4 uStack_80;
  uint uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 local_70 [3];
  char local_63;
  
  // +0x08: some context pointer
  savedBufPtr = *(int *)(in_EAX + 8);
  // +0xb0: mode/state byte
  local_63 = *(char *)(thisPtr + 0xb0);
  puStack_a4 = local_70;
  // +0x9c: some data value
  uStack_a8 = *(undefined4 *)(thisPtr + 0x9c);
  pStack_b4 = (int *)0x560f2d;
  iStack_ac = thisPtr;

  local_8c = savedBufPtr;
  // +0x20: first sub-serializer vtable
  (**(code **)(**(int **)(thisPtr + 0x20) + 0xc))();

  uVar5 = *(uint *)(thisPtr + 0xc4);
  // +0xbc: data buffer pointer
  iStack_90 = *(int *)(thisPtr + 0xbc);
  *(char *)(thisPtr + 0xb0) = uStack_74._1_1_;
  local_8c = 0;
  uStack_88 = 0;
  uStack_84 = 0x80000000;

  if (0 < (int)uVar5) {
    pStack_b4 = (int *)0x4;
    FUN_00aa4110(&local_8c, ((int)uVar5 < 0) - 1 & uVar5);
  }

  // Copy data from +0xc0 buffer into local buffer
  iVar1 = 0;
  if (0 < *(int *)(thisPtr + 0xc4)) {
    do {
      *(undefined4 *)(local_8c + iVar1 * 4) = *(undefined4 *)(*(int *)(thisPtr + 0xc0) + iVar1 * 4);
      iVar1 = iVar1 + 1;
    } while (iVar1 < *(int *)(thisPtr + 0xc4));
  }

  pStack_b4 = &iStack_90;
  puVar7 = &uStack_80;
  uStack_88 = uVar5;
  // +0x24: second sub-serializer vtable
  (**(code **)(**(int **)(thisPtr + 0x24) + 0xc))(savedESI, thisPtr);

  iVar1 = 0;
  *(undefined4 *)(thisPtr + 0xbc) = savedEDI;
  if (0 < *(int *)(thisPtr + 0xc4)) {
    do {
      *(undefined4 *)(*(int *)(thisPtr + 0xc0) + iVar1 * 4) = *(undefined4 *)(savedESI + iVar1 * 4);
      iVar1 = iVar1 + 1;
    } while (iVar1 < *(int *)(thisPtr + 0xc4));
  }

  // +0x11c: some state value
  uStack_78 = *(undefined4 *)(thisPtr + 0x11c);
  // +0xd0: another data value
  local_70[0] = *(undefined4 *)(thisPtr + 0xd0);
  uStack_74 = CONCAT22(*(short *)(thisPtr + 0xcd),
                       CONCAT11(*(char *)(thisPtr + 0xcc),
                                *(char *)(*(int *)(thisPtr + 0x1c) + 0x20)));
  iVar3 = iStack_ac;
  // +0x2c: third sub-serializer vtable
  (**(code **)(**(int **)(thisPtr + 0x2c) + 0xc))(iStack_ac);

  *(char *)(thisPtr + 0xce) = uStack_80._3_1_;
  *(uint *)(thisPtr + 0xd0) = uStack_7c;
  savedBufPtr = *(int *)(thisPtr + 0xb8);
  *(char *)(thisPtr + 0xcc) = uStack_80._1_1_;
  pStack_b4 = *(int **)(thisPtr + 0xb4);
  *(char *)(thisPtr + 0xcd) = uStack_80._2_1_;
  iVar1 = thisPtr;
  puVar8 = puVar7;
  // +0x28: fourth sub-serializer vtable
  (**(code **)(**(int **)(thisPtr + 0x28) + 0xc))(puVar7, thisPtr, &stack0xffffff64, &local_8c, &pStack_b4);

  uVar5 = *(uint *)(thisPtr + 0xa4);
  *(undefined4 **)(thisPtr + 0xb8) = &uStack_80;
  *(int *)(thisPtr + 0xb4) = thisPtr;
  local_8c = 0;
  uStack_88 = 0;
  uStack_84 = 0x80000000;
  uStack_80 = 0;
  uStack_7c = 0;
  uStack_78 = 0x80000000;

  if (0 < (int)uVar5) {
    // Allocate buffer for string data
    FUN_00aa4110(&uStack_80, ((int)uVar5 < 0) - 1 & uVar5, 1);
  }

  iVar4 = *(int *)(thisPtr + 0xa4);
  uStack_7c = uVar5;

  // Grow buffer if needed
  if ((int)(uStack_84 & 0x3fffffff) < iVar4) {
    iVar2 = (uStack_84 & 0x3fffffff) * 2;
    if (iVar2 <= iVar4) {
      iVar2 = iVar4;
    }
    FUN_00aa4110(&local_8c, iVar2, 4);
  }

  // Copy string data from +0xa0 buffer
  iVar2 = 0;
  if (0 < *(int *)(thisPtr + 0xa4)) {
    do {
      *(char *)(uStack_80 + iVar2) = *(char *)(iVar2 + *(int *)(thisPtr + 0xa0));
      iVar2 = iVar2 + 1;
    } while (iVar2 < *(int *)(thisPtr + 0xa4));
  }

  // +0xac: string capacity
  uStack_74 = *(undefined4 *)(thisPtr + 0xac);
  piVar6 = &savedBufPtr;
  iVar2 = thisPtr;
  uStack_88 = iVar4;
  // +0x30: fifth sub-serializer vtable
  (**(code **)(**(int **)(thisPtr + 0x30) + 0xc))(iVar3, thisPtr, piVar6, &local_8c);

  // Copy serialized string data back to object buffer
  iVar3 = 0;
  if (0 < local_8c) {
    do {
      *(char *)(iVar3 + *(int *)(thisPtr + 0xa0)) = *(char *)(iStack_90 + iVar3);
      iVar3 = iVar3 + 1;
    } while (iVar3 < local_8c);
  }

  // Copy data to +0x124 buffer
  iVar3 = 0;
  if (0 < savedEBX) {
    do {
      *(undefined4 *)(*(int *)(thisPtr + 0x124) + iVar3 * 4) = *(undefined4 *)(savedESI + iVar3 * 4);
      iVar3 = iVar3 + 1;
    } while (iVar3 < savedEBX);
  }

  // +0xac: update string capacity
  *(uint *)(thisPtr + 0xac) = uStack_84;

  // +0x34: sixth sub-serializer vtable  
  (**(code **)(**(int **)(thisPtr + 0x34) + 0xc))(iVar1, thisPtr, *(undefined4 *)(thisPtr + 0x118), *(undefined4 *)(thisPtr + 0x120));

  // +0x38: seventh sub-serializer vtable
  (**(code **)(**(int **)(thisPtr + 0x38) + 0xc))(iVar2, thisPtr, &iStack_90);

  // Save serialization context/state
  *(int *)(thisPtr + 0x130) = savedESI;      // +0x130: saved context ptr
  *(int *)(thisPtr + 0x134) = savedEBX;      // +0x134: saved context count
  *(undefined4 *)(thisPtr + 0x138) = uStack_94; // +0x138: saved state
  *(int *)(thisPtr + 0x13c) = iStack_90;     // +0x13c: saved buffer ptr
  *(int *)(thisPtr + 0x140) = local_8c;      // +0x140: saved data count
  *(uint *)(thisPtr + 0x144) = uStack_88;    // +0x144: saved size
  *(uint *)(thisPtr + 0x148) = uStack_84;    // +0x148: saved capacity
  *(int *)(thisPtr + 0x14c) = uStack_80;     // +0x14c: saved buffer ptr

  // If mode == 2 (write mode), clear serialized data chunks
  if ((*(int *)(thisPtr + 0x10c) == 2) && (iVar1 = 0, 0 < *(int *)(thisPtr + 0x4c))) {
    iVar3 = 0;
    do {
      iVar4 = *(int *)(thisPtr + 0x48) + iVar3;
      iVar1 = iVar1 + 1;
      // Clear chunk header fields
      *(undefined4 *)(iVar4 + 0xa8) = 0;  // +0xa8: chunk type
      *(undefined4 *)(iVar4 + 0xac) = 0;  // +0xac: chunk size
      *(undefined4 *)(iVar4 + 0xb4) = 0;  // +0xb4: chunk flags
      *(undefined4 *)(iVar4 + 0xb0) = 0;  // +0xb0: chunk offset
      iVar3 = iVar3 + 0xc0;               // Each chunk is 0xC0 bytes
    } while (iVar1 < *(int *)(thisPtr + 0x4c));
  }

  // Free temporary buffers
  if (-1 < (int)puStack_a4) {
    uVar5 = (uint)puStack_a4 & 0x3fffffff;
    TlsGetValue(DAT_01139810);
    FUN_00aa26e0(iStack_ac, uVar5, 0x17);
  }

  iVar1 = savedBufPtr;
  if (-1 < savedBufPtr) {
    TlsGetValue(DAT_01139810);
    FUN_00aa26e0(puVar8, iVar1 * 4, 0x17);
  }

  if (-1 < (int)puVar7) {
    TlsGetValue(DAT_01139810);
    FUN_00aa26e0(piVar6, (int)puVar7 * 4, 0x17);
  }

  return;
}