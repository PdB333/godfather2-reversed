// FUNC_NAME: AsyncFileReader::readCompleteCallback
undefined4 __fastcall AsyncFileReader::readCompleteCallback(int *this)
{
  int *piVar1;
  BOOL BVar2;
  uint _Size;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  int local_50c;
  undefined4 local_504 [321];
  
  if (*this == this[7]) { // +0x00 == +0x1C (expected read offset matches actual)
    piVar1 = (int *)this[5]; // +0x14: pointer to read request
    iVar4 = *piVar1; // request type
    if ((iVar4 != 4) || (*(ushort *)(piVar1 + 1) == 0)) { // not a chunked read or no chunks
      this[8] = -0x10000; // +0x20: error code
    }
    else {
      _Size = (this[9] - 0xcU) / (uint)*(ushort *)(piVar1 + 1); // +0x24: total size minus header / num chunks
      this[0xc] = this[0xb] + 8; // +0x30: current read position = buffer start + 8
      local_50c = 0;
      if ((short)piVar1[1] != 0) { // chunk count
        do {
          _memset(local_504,0,0x504); // clear 1284-byte buffer
          _memcpy(local_504,(void *)this[0xc],_Size); // copy chunk data
          puVar3 = (undefined4 *)this[2]; // +0x08: output buffer
          if (puVar3 < (undefined4 *)this[3]) { // +0x0C: output buffer end
            this[2] = (int)(puVar3 + 0x141); // advance by 1284 bytes
            if (puVar3 != (undefined4 *)0x0) {
              puVar6 = local_504;
              for (iVar5 = 0x141; iVar5 != 0; iVar5 = iVar5 + -1) {
                *puVar3 = *puVar6;
                puVar6 = puVar6 + 1;
                puVar3 = puVar3 + 1;
              }
            }
          }
          else {
            FUN_0069a140(puVar3,local_504); // overflow handler
          }
          this[8] = this[8] + 1; // +0x20: increment processed count
          this[0xc] = this[0xc] + _Size; // advance read position
          local_50c = local_50c + 1;
        } while (local_50c < (int)(uint)*(ushort *)(this[5] + 4)); // chunk count
      }
    }
    this[0xc] = 0; // +0x30: reset read position
    BVar2 = CloseHandle((HANDLE)this[6]); // +0x18: file handle
    if (BVar2 == 0) {
      uVar7 = 2; // error closing handle
    }
    else {
      this[6] = -1; // +0x18: invalidate handle
      uVar7 = 8; // success
    }
    if (iVar4 != 4) { // if not a chunked read, reinitialize
      FUN_00699210(); // free memory
      puVar3 = (undefined4 *)FUN_009c8e50(8); // allocate 8 bytes
      if (puVar3 == (undefined4 *)0x0) {
        puVar3 = (undefined4 *)0x0;
      }
      else {
        *puVar3 = 4; // set type to chunked read
        *(undefined2 *)(puVar3 + 1) = 0; // chunk count = 0
        *(undefined2 *)((int)puVar3 + 6) = 0; // padding
      }
      this[5] = (int)puVar3; // +0x14: new request
      iVar4 = FUN_00ab8560(0,puVar3,8); // queue new read
      this[7] = iVar4; // +0x1C: expected offset
      *this = iVar4; // +0x00: current offset
    }
    return uVar7;
  }
  BVar2 = CloseHandle((HANDLE)this[6]); // +0x18: file handle
  if (BVar2 != 0) {
    this[6] = -1; // +0x18: invalidate handle
  }
  return 7; // mismatch error
}