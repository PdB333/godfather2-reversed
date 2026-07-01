// FUNC_NAME: Player::setupFromCharacterData
void __thiscall Player::setupFromCharacterData(int thisPtr, int characterData)
{
  char isValid;
  int iVar2;
  int chrDataBase;
  int *puVar4;
  int *puVar5;
  int local_2c0;  // +0x00 struct start
  char local_2bc [700]; // +0x04 struct data (700 bytes)
  
  if (characterData != 0) {
    isValid = '\0';
    chrDataBase = 0;
    if (*(int *)(DAT_0112b9b4 + 0x34) != -1) {
      chrDataBase = *(int *)(*(int *)(DAT_0112b9b4 + 0x28) + *(int *)(DAT_0112b9b4 + 0x34) * 4);
      isValid = FUN_009bca20(*(undefined4 *)(chrDataBase + 0x28));
    }
    local_2c0 = 0;
    _memset(local_2bc,0,700);
    if (isValid != '\0') {
      FUN_009bbcc0(*(undefined4 *)(chrDataBase + 0x28),&local_2c0);
    }
    iVar2 = FUN_009c8e50(0x2f8);  // allocation size 0x2f8 = 760 bytes
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = FUN_007a0f80(thisPtr);  // constructor
    }
    puVar4 = &local_2c0;
    puVar5 = (int *)(iVar2 + 0x38);  // +0x38 = data field offset
    for (int i = 0xb0; i != 0; i = i + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    FUN_0064ef60(iVar2);  // finalize/register
  }
  return;
}