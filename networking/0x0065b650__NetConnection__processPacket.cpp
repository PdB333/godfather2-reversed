// FUNC_NAME: NetConnection::processPacket
void NetConnection::processPacket(int param_1, uint *param_2)

{
  short *psVar1;
  uint *puVar2;
  uint uVar3;
  uint *puVar4;
  int iVar5;
  undefined4 *puVar6;
  int in_EAX;
  void *pvVar7;
  byte *pbVar8;
  undefined1 *puVar9;
  undefined4 *puVar10;
  char cVar11;
  byte bVar12;
  uint uVar13;
  uint *puVar14;
  
  uVar13 = *param_2 & 0x3ff;
  for (puVar14 = *(uint **)(param_1 + 0x6000 + uVar13 * 4); puVar14 != (uint *)0x0;
      puVar14 = (uint *)puVar14[2]) {
    if (*param_2 == *puVar14) {
      *(uint *)(puVar14[4] + 0xc) = puVar14[3];
      *(uint *)(puVar14[3] + 0x10) = puVar14[4];
      puVar14[3] = param_1 + 0x8018;
      puVar14[4] = *(uint *)(param_1 + 0x8028);
      *(uint **)(param_1 + 0x8028) = puVar14;
      *(uint **)(puVar14[4] + 0xc) = puVar14;
      goto LAB_0065b757;
    }
  }
  puVar14 = *(uint **)(param_1 + 0x800c);
  *(uint *)(puVar14[4] + 0xc) = puVar14[3];
  *(uint *)(puVar14[3] + 0x10) = puVar14[4];
  puVar14[3] = param_1 + 0x8018;
  puVar14[4] = *(uint *)(param_1 + 0x8028);
  *(uint **)(param_1 + 0x8028) = puVar14;
  *(uint **)(puVar14[4] + 0xc) = puVar14;
  puVar2 = (uint *)(param_1 + 0x6000 + (*puVar14 & 0x3ff) * 4);
  uVar3 = *(uint *)(param_1 + 0x6000 + (*puVar14 & 0x3ff) * 4);
  while (uVar3 != 0) {
    puVar4 = (uint *)*puVar2;
    if (puVar4 == puVar14) {
      *puVar2 = puVar14[2];
      break;
    }
    puVar2 = puVar4 + 2;
    uVar3 = puVar4[2];
  }
  if (*puVar14 != 0) {
    FUN_0065a440();
  }
  uVar3 = *param_2;
  *puVar14 = uVar3;
  if (uVar3 != 0) {
    psVar1 = (short *)(*(int *)(DAT_01205a34 + uVar3 * 4) + 0xe);
    *psVar1 = *psVar1 + 1;
  }
  *(undefined1 *)(puVar14 + 5) = 0;
  puVar14[2] = *(uint *)(param_1 + 0x6000 + uVar13 * 4);
  *(uint **)(param_1 + 0x6000 + uVar13 * 4) = puVar14;
LAB_0065b757:
  param_2 = (uint *)puVar14[1];
  FUN_0064b810(10,&param_2);
  param_2 = (uint *)CONCAT31(param_2._1_3_,(char)puVar14[5]);
  cVar11 = (char)puVar14[5];
  if (*(uint *)(in_EAX + 0x30) < *(int *)(in_EAX + 0x18) + 1U) {
    uVar13 = (*(uint *)(in_EAX + 0x30) + 8 >> 3) + 0x5dc;
    if (*(uint *)(in_EAX + 0x10) < uVar13) {
      if (*(char *)(in_EAX + 0x14) != '\0') {
        *(uint *)(in_EAX + 0x10) = uVar13;
        pvVar7 = _realloc(*(void **)(in_EAX + 0xc),uVar13);
        *(void **)(in_EAX + 0xc) = pvVar7;
        *(uint *)(in_EAX + 0x2c) = uVar13 * 8;
        *(uint *)(in_EAX + 0x30) = uVar13 * 8;
        cVar11 = (char)param_2;
        goto LAB_0065b7c3;
      }
    }
    else {
      *(uint *)(in_EAX + 0x10) = uVar13;
    }
    *(undefined1 *)(in_EAX + 0x1c) = 1;
  }
  else {
LAB_0065b7c3:
    pbVar8 = (byte *)((*(uint *)(in_EAX + 0x18) >> 3) + *(int *)(in_EAX + 0xc));
    bVar12 = '\x01' << ((byte)*(uint *)(in_EAX + 0x18) & 7);
    if (cVar11 == '\0') {
      *pbVar8 = *pbVar8 & ~bVar12;
    }
    else {
      *pbVar8 = *pbVar8 | bVar12;
    }
    *(int *)(in_EAX + 0x18) = *(int *)(in_EAX + 0x18) + 1;
    if (cVar11 != '\0') {
      return;
    }
  }
  if (*puVar14 == 0) {
    puVar9 = &DAT_00e2f044;
  }
  else {
    puVar9 = (undefined1 *)(*(int *)(DAT_01205a34 + *puVar14 * 4) + 0x10);
  }
  FUN_0064c760(puVar9,0xff);
  if ((_DAT_01223ba4 & 1) == 0) {
    _DAT_01223ba4 = _DAT_01223ba4 | 1;
    FUN_0065ba80();
    _atexit((_func_4879 *)&LAB_00d51450);
  }
  puVar10 = DAT_01223ba0;
  _DAT_01223b98 = _DAT_01223b98 + 1;
  if (DAT_01223ba0 == (undefined4 *)0x0) {
    puVar10 = (undefined4 *)FUN_0065bd60(DAT_01223b9c);
    puVar6 = DAT_01223ba0;
    if (puVar10 != (undefined4 *)0x0) {
      puVar10[2] = 0;
      goto LAB_0065b879;
    }
  }
  else {
    puVar6 = (undefined4 *)*DAT_01223ba0;
    if (DAT_01223ba0 != (undefined4 *)0x0) {
      puVar6 = DAT_01223ba0 + 2;
      DAT_01223ba0 = (undefined4 *)*DAT_01223ba0;
      *puVar6 = 0;
      goto LAB_0065b879;
    }
  }
  DAT_01223ba0 = puVar6;
  puVar10 = (undefined4 *)0x0;
LAB_0065b879:
  puVar10[1] = puVar14;
  if (puVar10[2] != 0) {
    FUN_0065a440();
  }
  uVar13 = *puVar14;
  puVar10[2] = uVar13;
  if (uVar13 != 0) {
    psVar1 = (short *)(*(int *)(DAT_01205a34 + uVar13 * 4) + 0xe);
    *psVar1 = *psVar1 + 1;
  }
  *puVar10 = 0;
  iVar5 = *(int *)(*(int *)(param_1 + 0x8030) + 0x120);
  if (*(int *)(iVar5 + 8) != 0) {
    **(undefined4 **)(iVar5 + 0xc) = puVar10;
    *(undefined4 **)(iVar5 + 0xc) = puVar10;
    return;
  }
  *(int *)(iVar5 + 8) = (int)puVar10;
  *(undefined4 **)(iVar5 + 0xc) = puVar10;
  return;
}