// FUNC_NAME: aes_ecb_decrypt
void aes_ecb_decrypt(byte *ct, byte *pt, uint *skey)
{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  char *pcVar10;
  byte local_c;
  
  if (pt == (byte *)0x0) {
    pcVar10 = "_ARGCHK '%s' failure on line %d of file %s\n";
    iVar2 = FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s\n","pt != NULL",0x175,
                         "..\\src\\libtomcrypt\\aes.c");
    _fprintf((FILE *)(iVar2 + 0x40),pcVar10);
  }
  if (ct == (byte *)0x0) {
    pcVar10 = "_ARGCHK '%s' failure on line %d of file %s\n";
    iVar2 = FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s\n","ct != NULL",0x176,
                         "..\\src\\libtomcrypt\\aes.c");
    _fprintf((FILE *)(iVar2 + 0x40),pcVar10);
  }
  if (skey == (uint *)0x0) {
    pcVar10 = "_ARGCHK '%s' failure on line %d of file %s\n";
    iVar2 = FUN_00b995f7("_ARGCHK '%s' failure on line %d of file %s\n","skey != NULL",0x177,
                         "..\\src\\libtomcrypt\\aes.c");
    _fprintf((FILE *)(iVar2 + 0x40),pcVar10);
  }
  uVar3 = CONCAT31(CONCAT21(CONCAT11(*ct,ct[1]),ct[2]),ct[3]) ^
          *(uint *)(skey + 0x40); // +0x100 bytes = 0x40 words
  uVar9 = CONCAT31(CONCAT21(CONCAT11(ct[4],ct[5]),ct[6]),ct[7]) ^
          *(uint *)(skey + 0x41); // +0x104
  uVar4 = CONCAT31(CONCAT21(CONCAT11(ct[8],ct[9]),ct[10]),ct[0xb]) ^
          *(uint *)(skey + 0x42); // +0x108
  uVar5 = CONCAT31(CONCAT21(CONCAT11(ct[0xc],ct[0xd]),ct[0xe]),ct[0xf]) ^
          *(uint *)(skey + 0x43); // +0x10c
  uVar6 = *(uint *)(&DAT_00e292e0 + (uVar5 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_00e296e0 + (uVar4 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_00e28ee0 + (uVar3 >> 0x18) * 4) ^
          *(uint *)(&DAT_00e29ae0 + (uVar9 & 0xff) * 4) ^ *(uint *)(skey + 0x44); // +0x110
  uVar7 = *(uint *)(&DAT_00e296e0 + (uVar5 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_00e28ee0 + (uVar9 >> 0x18) * 4) ^
          *(uint *)(&DAT_00e292e0 + (uVar3 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_00e29ae0 + (uVar4 & 0xff) * 4) ^ *(uint *)(skey + 0x45); // +0x114
  uVar8 = *(uint *)(&DAT_00e28ee0 + (uVar4 >> 0x18) * 4) ^
          *(uint *)(&DAT_00e292e0 + (uVar9 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_00e296e0 + (uVar3 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_00e29ae0 + (uVar5 & 0xff) * 4) ^ *(uint *)(skey + 0x46); // +0x118
  uVar3 = *(uint *)(&DAT_00e28ee0 + (uVar5 >> 0x18) * 4) ^
          *(uint *)(&DAT_00e292e0 + (uVar4 >> 0x10 & 0xff) * 4) ^
          *(uint *)(&DAT_00e296e0 + (uVar9 >> 8 & 0xff) * 4) ^
          *(uint *)(&DAT_00e29ae0 + (uVar3 & 0xff) * 4) ^ *(uint *)(skey + 0x47); // +0x11c
  iVar2 = *(int *)(skey + 0x80) >> 1; // +0x200 bytes = 0x80 words, number of rounds
  puVar1 = skey + 0x48; // +0x120
  while (iVar2 = iVar2 + -1, iVar2 != 0) {
    uVar9 = *(uint *)(&DAT_00e292e0 + (uVar3 >> 0x10 & 0xff) * 4) ^
            *(uint *)(&DAT_00e296e0 + (uVar8 >> 8 & 0xff) * 4) ^
            *(uint *)(&DAT_00e28ee0 + (uVar6 >> 0x18) * 4) ^
            *(uint *)(&DAT_00e29ae0 + (uVar7 & 0xff) * 4) ^ *puVar1;
    uVar4 = *(uint *)(&DAT_00e296e0 + (uVar3 >> 8 & 0xff) * 4) ^
            *(uint *)(&DAT_00e28ee0 + (uVar7 >> 0x18) * 4) ^
            *(uint *)(&DAT_00e292e0 + (uVar6 >> 0x10 & 0xff) * 4) ^
            *(uint *)(&DAT_00e29ae0 + (uVar8 & 0xff) * 4) ^ puVar1[1];
    uVar5 = *(uint *)(&DAT_00e28ee0 + (uVar8 >> 0x18) * 4) ^
            *(uint *)(&DAT_00e292e0 + (uVar7 >> 0x10 & 0xff) * 4) ^
            *(uint *)(&DAT_00e296e0 + (uVar6 >> 8 & 0xff) * 4) ^
            *(uint *)(&DAT_00e29ae0 + (uVar3 & 0xff) * 4) ^ puVar1[2];
    uVar3 = *(uint *)(&DAT_00e28ee0 + (uVar3 >> 0x18) * 4) ^
            *(uint *)(&DAT_00e292e0 + (uVar8 >> 0x10 & 0xff) * 4) ^
            *(uint *)(&DAT_00e296e0 + (uVar7 >> 8 & 0xff) * 4) ^
            *(uint *)(&DAT_00e29ae0 + (uVar6 & 0xff) * 4) ^ puVar1[3];
    uVar6 = *(uint *)(&DAT_00e292e0 + (uVar3 >> 0x10 & 0xff) * 4) ^
            *(uint *)(&DAT_00e296e0 + (uVar5 >> 8 & 0xff) * 4) ^
            *(uint *)(&DAT_00e28ee0 + (uVar9 >> 0x18) * 4) ^
            *(uint *)(&DAT_00e29ae0 + (uVar4 & 0xff) * 4) ^ puVar1[4];
    uVar7 = *(uint *)(&DAT_00e296e0 + (uVar3 >> 8 & 0xff) * 4) ^
            *(uint *)(&DAT_00e28ee0 + (uVar4 >> 0x18) * 4) ^
            *(uint *)(&DAT_00e292e0 + (uVar9 >> 0x10 & 0xff) * 4) ^
            *(uint *)(&DAT_00e29ae0 + (uVar5 & 0xff) * 4) ^ puVar1[5];
    uVar8 = *(uint *)(&DAT_00e28ee0 + (uVar5 >> 0x18) * 4) ^
            *(uint *)(&DAT_00e292e0 + (uVar4 >> 0x10 & 0xff) * 4) ^
            *(uint *)(&DAT_00e296e0 + (uVar9 >> 8 & 0xff) * 4) ^
            *(uint *)(&DAT_00e29ae0 + (uVar3 & 0xff) * 4) ^ puVar1[6];
    uVar3 = *(uint *)(&DAT_00e28ee0 + (uVar3 >> 0x18) * 4) ^
            *(uint *)(&DAT_00e292e0 + (uVar5 >> 0x10 & 0xff) * 4) ^
            *(uint *)(&DAT_00e296e0 + (uVar4 >> 8 & 0xff) * 4) ^
            *(uint *)(&DAT_00e29ae0 + (uVar9 & 0xff) * 4) ^ puVar1[7];
    puVar1 = puVar1 + 8;
  }
  uVar4 = *(uint *)(&DAT_00e29ee0 + (uVar3 >> 0x10 & 0xff) * 4) & 0xff0000 ^
          *(uint *)(&DAT_00e29ee0 + (uVar8 >> 8 & 0xff) * 4) & 0xff00 ^
          *(uint *)(&DAT_00e29ee0 + (uVar6 >> 0x18) * 4) & 0xff000000 ^
          (uint)(byte)(&DAT_00e29ee0)[(uVar7 & 0xff) * 4] ^ *puVar1;
  *pt = (byte)(uVar4 >> 0x18);
  pt[1] = (byte)(uVar4 >> 0x10);
  pt[2] = (byte)(uVar4 >> 8);
  pt[3] = (byte)uVar4;
  uVar4 = *(uint *)(&DAT_00e29ee0 + (uVar6 >> 0x10 & 0xff) * 4) & 0xff0000 ^
          *(uint *)(&DAT_00e29ee0 + (uVar3 >> 8 & 0xff) * 4) & 0xff00 ^
          *(uint *)(&DAT_00e29ee0 + (uVar7 >> 0x18) * 4) & 0xff000000 ^
          (uint)(byte)(&DAT_00e29ee0)[(uVar8 & 0xff) * 4] ^ puVar1[1];
  pt[4] = (byte)(uVar4 >> 0x18);
  pt[5] = (byte)(uVar4 >> 0x10);
  pt[6] = (byte)(uVar4 >> 8);
  pt[7] = (byte)uVar4;
  uVar4 = *(uint *)(&DAT_00e29ee0 + (uVar7 >> 0x10 & 0xff) * 4) & 0xff0000 ^
          *(uint *)(&DAT_00e29ee0 + (uVar6 >> 8 & 0xff) * 4) & 0xff00 ^
          *(uint *)(&DAT_00e29ee0 + (uVar8 >> 0x18) * 4) & 0xff000000 ^
          (uint)(byte)(&DAT_00e29ee0)[(uVar3 & 0xff) * 4] ^ puVar1[2];
  pt[8] = (byte)(uVar4 >> 0x18);
  pt[9] = (byte)(uVar4 >> 0x10);
  pt[10] = (byte)(uVar4 >> 8);
  pt[0xb] = (byte)uVar4;
  uVar6 = *(uint *)(&DAT_00e29ee0 + (uVar8 >> 0x10 & 0xff) * 4) & 0xff0000 ^
          *(uint *)(&DAT_00e29ee0 + (uVar7 >> 8 & 0xff) * 4) & 0xff00 ^
          *(uint *)(&DAT_00e29ee0 + (uVar3 >> 0x18) * 4) & 0xff000000 ^
          (uint)(byte)(&DAT_00e29ee0)[(uVar6 & 0xff) * 4] ^ puVar1[3];
  pt[0xc] = (byte)(uVar6 >> 0x18);
  pt[0xd] = (byte)(uVar6 >> 0x10);
  pt[0xe] = (byte)(uVar6 >> 8);
  pt[0xf] = (byte)uVar6;
  return;
}