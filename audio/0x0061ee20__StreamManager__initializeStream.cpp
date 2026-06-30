// FUNC_NAME: StreamManager::initializeStream
undefined1 __thiscall StreamManager::initializeStream(int this, byte *streamName, undefined4 param3, int param4)
{
  byte bVar1;
  char cVar2;
  int in_EAX;
  byte *pbVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  byte *pbVar7;
  bool bVar8;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  FUN_0061e9d0(); // likely cleanup/reset
  if (streamName != (byte *)0x0) {
    if (in_EAX == 0) {
      // Compare stream names (case-sensitive, 2-byte steps? possibly UTF-16)
      pbVar3 = streamName;
      pbVar7 = (byte *)(this + 0xc); // +0xC: stream name buffer
      do {
        bVar1 = *pbVar3;
        bVar8 = bVar1 < *pbVar7;
        if (bVar1 != *pbVar7) {
LAB_0061ee71:
          iVar4 = (1 - (uint)bVar8) - (uint)(bVar8 != 0);
          goto LAB_0061ee76;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar3[1];
        bVar8 = bVar1 < pbVar7[1];
        if (bVar1 != pbVar7[1]) goto LAB_0061ee71;
        pbVar3 = pbVar3 + 2;
        pbVar7 = pbVar7 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_0061ee76:
      if (iVar4 != 0) {
        _strncpy((char *)(this + 0xc), (char *)streamName, 0x80); // copy stream name
        cVar2 = FUN_0061e810(this); // validate stream name?
        if (cVar2 == '\0') {
          return 0;
        }
      }
      FUN_0061e960(param3); // process parameter
      *(undefined1 *)(this + 0x94) = 0; // +0x94: flag (0 = new stream)
      local_c = 0x10004; // allocation flags
      local_8 = 1;
      local_4 = 0;
      iVar4 = FUN_009c8e50(0x48); // allocate memory (0x48 bytes)
      if (iVar4 == 0) {
        *(undefined4 *)(this + 0x90) = 0; // +0x90: stream handle
      }
      else {
        uVar5 = FUN_004b4d10(&local_c); // initialize stream handle
        *(undefined4 *)(this + 0x90) = uVar5;
      }
    }
    else {
      // Existing stream handle provided
      _strncpy((char *)(this + 0xc), (char *)streamName, 0x80);
      *(undefined1 *)(this + 0x94) = 1; // +0x94: flag (1 = existing stream)
      *(int *)(this + 0x90) = in_EAX; // +0x90: store existing handle
    }
  }
  if (*(int *)(this + 0x90) != 0) {
    // Allocate stream buffer (0x280 bytes)
    iVar4 = FUN_009c8e50(0x280);
    if (iVar4 == 0) {
      uVar5 = 0;
    }
    else {
      if (*(int *)(this + 0x90) == 0) {
        iVar4 = 0;
      }
      else {
        iVar4 = *(int *)(this + 0x90) + 4;
      }
      uVar5 = FUN_00d087f0(iVar4, DAT_01143360, 0, 0); // create buffer
    }
    *(undefined4 *)(this + 0x98) = uVar5; // +0x98: buffer pointer
    
    // Allocate decoder object (0xE0 bytes)
    puVar6 = (undefined4 *)FUN_009c8f80(); // get allocator
    local_c = 2;
    local_8 = 0x10;
    local_4 = 0;
    iVar4 = (**(code **)*puVar6)(0xe0, &local_c); // allocate decoder
    if (iVar4 == 0) {
      uVar5 = 0;
    }
    else {
      uVar5 = FUN_0061f3e0(); // construct decoder
    }
    *(undefined4 *)(this + 0x9c) = uVar5; // +0x9C: decoder pointer
    
    // Allocate callback object (8 bytes)
    puVar6 = (undefined4 *)FUN_009c8e50(8);
    if (puVar6 == (undefined4 *)0x0) {
      puVar6 = (undefined4 *)0x0;
    }
    else {
      *puVar6 = &PTR_LAB_00e413c4; // vtable pointer
    }
    *(undefined4 **)(this + 0xac) = puVar6; // +0xAC: callback object
    
    if (((*(int *)(this + 0x98) != 0) && (*(int *)(this + 0x9c) != 0)) &&
       (puVar6 != (undefined4 *)0x0)) {
      // Initialize audio system components
      FUN_00d