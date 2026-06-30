// FUNC_NAME: FileManager::readWavHeader
undefined1 FileManager::readWavHeader(uint *param_1)

{
  uint uVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int local_28;
  int local_24;
  undefined1 local_20 [4];
  ushort local_1c;
  ushort local_1a;
  
  // Initialize output structure
  *(undefined1 *)(param_1 + 0x23) = 0;  // +0x8C: success flag
  *param_1 = 0;                         // +0x00: sample rate
  param_1[1] = 0;                       // +0x04: channels
  param_1[2] = 0;                       // +0x08: data size
  
  // Check if file handle is valid and readable
  if (((char)param_1[3] != '\0') &&     // +0x0C: file handle
     (cVar3 = FUN_004019a0(param_1 + 3), iVar2 = DAT_01223378, cVar3 != '\0')) {
    // Open file for reading
    iVar4 = FUN_004015e0(param_1 + 3,1);
    if (iVar4 != 0) {
      uVar7 = 0;
      iVar5 = FUN_00401780(iVar4,&local_28,8);  // Read 8 bytes (chunk header)
      while (iVar5 == 8) {
        if (local_28 == 0x6468564d) {  // "MdhV" = "MdhV" (little-endian "WAVE" chunk)
          if ((local_24 == 0x20) && (iVar5 = FUN_00401780(iVar4,local_20,0x18), iVar5 == 0x18)) {
            // Read format chunk data (24 bytes)
            *param_1 = (uint)local_1c;  // sample rate
            param_1[1] = (uint)local_1a; // channels
            param_1[2] = *(uint *)(*(int *)(iVar2 + 0x38) + 0xc + iVar4 * 0x10);  // data size
            *(undefined1 *)(param_1 + 0x23) = 1;  // success
          }
          break;
        }
        uVar7 = uVar7 + local_24;
        iVar5 = iVar4 * 0x10 + *(int *)(iVar2 + 0x38);
        uVar1 = *(uint *)(iVar5 + 0xc);
        uVar6 = uVar7;
        if (uVar1 < uVar7) {
          uVar6 = uVar1;
        }
        *(uint *)(iVar5 + 8) = uVar6;
        iVar5 = FUN_00401780(iVar4,&local_28,8);  // Read next chunk header
      }
    }
    FUN_004016d0(iVar4);  // Close file
  }
  return (char)param_1[0x23];  // Return success flag
}