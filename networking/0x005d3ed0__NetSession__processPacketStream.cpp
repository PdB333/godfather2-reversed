// FUNC_NAME: NetSession::processPacketStream
int* NetSession::processPacketStream(int* stream, int* outParam)
{
  char cVar1;
  int iVar2;
  int* piVar3;
  char* pcVar4;
  undefined4 uVar5;
  int* piVar6;
  int iVar7;
  undefined4* puVar8;
  int iVar9;
  int* piVar10;
  undefined4 local_24;
  undefined4 local_1c;
  int local_18;
  char local_14[4];
  int local_10;
  int local_c;
  int local_8;
  int local_4;
  
  piVar3 = stream;
  piVar6 = (int*)stream[1]; // +0x04: current read position
  iVar9 = 0;
  *outParam = 0;
  piVar10 = outParam;
  if (piVar6 != (int*)0x0) {
    local_4 = *stream; // +0x00: base position
    stream[4] = 0; // +0x10: flags
    *stream = (int)piVar6;
    stream[4] = 4;
    iVar2 = *piVar6;
    stream[4] = 4;
    if (iVar2 == 0x61707866) { // 'fxpa' - packet magic
      iVar2 = stream[3]; // +0x0C: size
      DAT_0103ae2c = DAT_0103ae2c + 1; // global packet counter
      *outParam = DAT_0103ae2c;
      stream[4] = 0;
      local_18 = 0;
      stream = (int*)0x61707866;
      if (iVar2 != 8 && -1 < iVar2 + -8) {
        do {
          local_10 = piVar3[4]; // +0x10: current read offset
          iVar2 = *piVar3; // +0x00: base offset
          local_24 = CONCAT13(*(undefined1*)(local_10 + 3 + iVar2),
                              CONCAT12(*(undefined1*)(local_10 + 2 + iVar2),
                                       CONCAT11(*(undefined1*)(local_10 + 1 + iVar2),
                                                *(undefined1*)(local_10 + iVar2))));
          piVar3[4] = local_10 + 4;
          if (local_24 == 0x61707866) { // 'fxpa' - packet start
            local_10 = local_10 + 8;
            piVar3[4] = local_10;
          }
          else if (local_24 == 0x74783468) { // 'h4xt' - text header
            piVar3[4] = local_10 + 8;
            local_18 = FUN_00616b20(); // createTextStream
          }
          else if (local_24 == 0x74783474) { // 't4xt' - text data
            iVar7 = local_10 + 8;
            local_8 = iVar9 + 1;
            local_c = DAT_0103ae2c + 1;
            DAT_0103ae2c = local_c;
            piVar3[4] = iVar7;
            __snprintf(local_14, 4, "%d", local_8);
            pcVar4 = local_14;
            do {
              cVar1 = *pcVar4;
              pcVar4 = pcVar4 + 1;
            } while (cVar1 != '\0');
            uVar5 = FUN_00ab8560(local_18, local_14, (int)pcVar4 - (int)(local_14 + 1)); // writeToStream
            uVar5 = FUN_00611000(uVar5); // getString
            FUN_006065a0(uVar5, 1); // logMessage
            stream = (int*)((uint)stream & 0xffffff00);
            FUN_0061a2e0(iVar7 + iVar2, &stream); // processTextData
            iVar9 = local_c;
            FUN_005d3070(local_c); // handlePacket
            piVar6 = (int*)(DAT_01206880 + 0x14); // global +0x14
            **(undefined4**)(DAT_01206880 + 0x14) = &PTR_LAB_01126adc;
            *piVar6 = *piVar6 + 4;
            *(int*)*piVar6 = iVar9;
            *piVar6 = *piVar6 + 4;
            puVar8 = (undefined4*)(*piVar6 + 3U & 0xfffffffc);
            *piVar6 = (int)puVar8;
            *puVar8 = uVar5;
            *piVar6 = *piVar6 + 4;
            iVar9 = local_8;
            piVar10 = outParam;
          }
          iVar2 = local_10 + 4;
          piVar3[4] = iVar2;
          iVar7 = iVar2 + *piVar3;
          local_1c._0_2_ = CONCAT11(*(undefined1*)(iVar7 + 1), *(undefined1*)(iVar2 + *piVar3));
          local_1c = CONCAT13(*(undefined1*)(iVar7 + 3),
                              CONCAT12(*(undefined1*)(iVar7 + 2), (undefined2)local_1c));
          piVar3[4] = local_1c + local_10;
        } while (local_1c + local_10 < piVar3[3] + -8);
        if (local_18 != 0) {
          outParam = (int*)DAT_01206880;
          FUN_005d3e00(*piVar10, local_18); // cleanupTextStream
        }
      }
      *piVar3 = local_4;
    }
  }
  return piVar10;
}