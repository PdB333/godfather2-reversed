// FUNC_NAME: StreamReader::readToken
void StreamReader::readToken(void)
{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 uVar3;
  byte *pbVar4;
  int iVar5;
  uint uVar6;
  uint *unaff_EDI;
  uint local_c;
  int local_8;
  int local_4;
  
  // Get the output buffer pointer from the stream state (offset +0x28 = stream state struct)
  puVar1 = (undefined4 *)unaff_EDI[10];
  local_8 = 0;
  // Ensure buffer capacity is at least 32 bytes
  if (((uint)puVar1[1] < 5) && ((uint)puVar1[1] < 0x20)) {
    uVar3 = FUN_006279a0(puVar1[1],0x20);  // reallocate buffer
    *puVar1 = uVar3;
    puVar1[1] = 0x20;
  }
  local_c = 0x20;
  do {
    puVar1 = (undefined4 *)unaff_EDI[10];
    // Check if buffer needs expansion for remaining space
    if (((uint)puVar1[1] < local_c - 0x1b) && ((uint)puVar1[1] < local_c)) {
      uVar6 = local_c;
      if (local_c < 0x20) {
        uVar6 = 0x20;
      }
      uVar3 = FUN_006279a0(puVar1[1],uVar6);
      puVar1[1] = uVar6;
      *puVar1 = uVar3;
    }
    // Store current character in output buffer
    *(char *)(local_8 + *(int *)unaff_EDI[10]) = (char)*unaff_EDI;
    local_8 = local_8 + 1;
    iVar5 = *(int *)unaff_EDI[9];
    local_c = local_c + 1;
    *(int *)unaff_EDI[9] = iVar5 + -1;
    // Read next character from stream
    if (iVar5 == 0) {
      piVar2 = (int *)unaff_EDI[9];
      pbVar4 = (byte *)(*(code *)piVar2[2])(0,piVar2[3],&local_4);
      if ((pbVar4 == (byte *)0x0) || (local_4 == 0)) {
        uVar6 = 0xffffffff;
      }
      else {
        piVar2[1] = (int)pbVar4;
        *piVar2 = local_4 + -1;
        uVar6 = (uint)*pbVar4;
        piVar2[1] = (int)(pbVar4 + 1);
      }
    }
    else {
      pbVar4 = *(byte **)(unaff_EDI[9] + 4);
      uVar6 = (uint)*pbVar4;
      *(byte **)(unaff_EDI[9] + 4) = pbVar4 + 1;
    }
    *unaff_EDI = uVar6;
    iVar5 = _isalnum(uVar6);
  } while ((iVar5 != 0) || (*unaff_EDI == 0x5f));  // alphanumeric or underscore
  // Null-terminate the token
  *(undefined1 *)(local_8 + *(int *)unaff_EDI[10]) = 0;
  return;
}