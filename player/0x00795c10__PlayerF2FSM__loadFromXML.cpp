// FUNC_NAME: PlayerF2FSM::loadFromXML
void __thiscall PlayerF2FSM::loadFromXML(int thisPtr, undefined4 xmlNode)
{
  int *piVar1;
  int iVar2;
  char cVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int *piVar6;
  int iVar7;
  bool bVar8;
  bool bVar9;
  
  FUN_00541a60(xmlNode);
  bVar9 = false;
  bVar8 = false;
  FUN_0043aff0(xmlNode,0x63c15f4e);
  cVar3 = FUN_0043b120();
  if (cVar3 == '\0') {
    do {
      FUN_0043b210();
      uVar4 = FUN_0043ab70();
      switch(uVar4) {
      case 0:
        iVar7 = FUN_0043b210();
        *(undefined4 *)(thisPtr + 0x2ac) = *(undefined4 *)(iVar7 + 8);
        break;
      case 1:
        iVar7 = FUN_0043b210();
        *(float *)(thisPtr + 0x310) = *(float *)(iVar7 + 8) * DAT_00e445c8;
        break;
      case 2:
        iVar7 = FUN_0043b210();
        *(undefined4 *)(thisPtr + 0x318) = *(undefined4 *)(iVar7 + 8);
        break;
      case 3:
        iVar7 = FUN_0043b210();
        *(undefined4 *)(thisPtr + 0x31c) = *(undefined4 *)(iVar7 + 8);
        break;
      case 4:
        iVar7 = FUN_0043b210();
        bVar8 = *(int *)(iVar7 + 8) != 0;
        break;
      case 5:
        iVar7 = FUN_0043b210();
        *(float *)(thisPtr + 0x328) = *(float *)(iVar7 + 8) * DAT_00e445c8;
        break;
      case 6:
        iVar7 = FUN_0043b210();
        *(float *)(thisPtr + 0x324) = *(float *)(iVar7 + 8) * DAT_00e445c8;
        break;
      case 7:
        iVar7 = FUN_0043b210();
        *(undefined4 *)(thisPtr + 0x2b0) = *(undefined4 *)(iVar7 + 8);
        break;
      case 8:
        iVar7 = FUN_0043b210();
        *(undefined4 *)(thisPtr + 700) = *(undefined4 *)(iVar7 + 8);
        cVar3 = FUN_00795a90(0,1);
        if (cVar3 != '\0') {
          *(uint *)(thisPtr + 700) = *(uint *)(thisPtr + 700) | 0x100000;
        }
        if (((*(uint *)(thisPtr + 700) >> 9 & 1) != 0) &&
           (cVar3 = FUN_008b7de0(thisPtr + 0x20), cVar3 == '\0')) {
          *(uint *)(thisPtr + 700) = *(uint *)(thisPtr + 700) | 0x80000;
        }
        break;
      case 9:
        iVar7 = FUN_0043b210();
        *(undefined4 *)(thisPtr + 0x270) = *(undefined4 *)(iVar7 + 8);
        break;
      case 10:
        iVar7 = FUN_0043b210();
        *(undefined4 *)(thisPtr + 0x2c0) = *(undefined4 *)(iVar7 + 8);
        break;
      case 0xb:
        FUN_0043b210();
        uVar4 = FUN_0043ab90();
        FUN_004089b0(thisPtr + 0x274,uVar4);
        break;
      case 0xc:
        FUN_0043b210();
        uVar4 = FUN_0043ab90();
        FUN_004089b0(thisPtr + 0x27c,uVar4);
        break;
      case 0xd:
        FUN_0043b210();
        uVar4 = FUN_0043ab90();
        FUN_004089b0(thisPtr + 0x284,uVar4);
        break;
      case 0xe:
        FUN_0043b210();
        uVar4 = FUN_0043ab90();
        FUN_004089b0(thisPtr + 0x28c,uVar4);
        break;
      case 0xf:
        FUN_0043b210();
        uVar4 = FUN_0043ab90();
        FUN_004089b0(thisPtr + 0x294,uVar4);
        break;
      case 0x10:
        iVar7 = thisPtr + 0x338;
        FUN_0043b210(iVar7);
        FUN_0043ad10(iVar7);
        break;
      case 0x11:
        iVar7 = FUN_0043b210();
        bVar9 = *(int *)(iVar7 + 8) != 0;
        break;
      case 0x12:
        FUN_0043b210();
        uVar4 = FUN_0043ab90();
        FUN_00408980(thisPtr + 0x29c,uVar4);
        break;
      case 0x13:
        FUN_0043b210();
        puVar5 = (undefined4 *)FUN_0043abc0();
        *(undefined4 *)(thisPtr + 0x350) = *puVar5;
        *(undefined4 *)(thisPtr + 0x354) = puVar5[1];
        *(undefined4 *)(thisPtr + 0x358) = puVar5[2];
        *(undefined4 *)(thisPtr + 0x35c) = puVar5[3];
        break;
      case 0x14:
        FUN_0043b210();
        puVar5 = (undefined4 *)FUN_0043abc0();
        *(undefined4 *)(thisPtr + 0x360) = *puVar5;
        *(undefined4 *)(thisPtr + 0x364) = puVar5[1];
        *(undefined4 *)(thisPtr + 0x368) = puVar5[2];
        *(undefined4 *)(thisPtr + 0x36c) = puVar5[3];
        break;
      case 0x15:
        FUN_0043b210();
        puVar5 = (undefined4 *)FUN_0043abc0();
        *(undefined4 *)(thisPtr + 0x370) = *puVar5;
        *(undefined4 *)(thisPtr + 0x374) = puVar5[1];
        *(undefined4 *)(thisPtr + 0x378) = puVar5[2];
        *(undefined4 *)(thisPtr + 0x37c) = puVar5[3];
        break;
      case 0x16:
        FUN_0043b210();
        puVar5 = (undefined4 *)FUN_0043abc0();
        *(undefined4 *)(thisPtr + 0x380) = *puVar5;
        *(undefined4 *)(thisPtr + 900) = puVar5[1];
        *(undefined4 *)(thisPtr + 0x388) = puVar5[2];
        *(undefined4 *)(thisPtr + 0x38c) = puVar5[3];
        break;
      case 0x17:
        FUN_0043b210();
        piVar6 = (int *)FUN_0043abc0();
        piVar1 = (int *)(thisPtr + 0x40c);
        *piVar1 = *piVar6;
        *(int *)(thisPtr + 0x410) = piVar6[1];
        iVar7 = piVar6[2];
        *(int *)(thisPtr + 0x414) = iVar7;
        iVar2 = piVar6[3];
        *(int *)(thisPtr + 0x418) = iVar2;
        if ((((*piVar1 != 0) || (*(int *)(thisPtr + 0x410) != 0)) || (iVar7 != 0)) || (iVar2 != 0))
        {
          cVar3 = FUN_00445250();
          if (cVar3 == '\0') {
            *(undefined4 *)(thisPtr + 0x418) = 0;
            *(undefined4 *)(thisPtr + 0x414) = 0;
            *(undefined4 *)(thisPtr + 0x410) = 0;
            *piVar1 = 0;
          }
          else {
            iVar7 = FUN_00405a80(piVar1);
            if ((iVar7 == 0) || (cVar3 = FUN_00411720(iVar7), cVar3 == '\0')) {
              uVar4 = 2;
            }
            else {
              uVar4 = 0x10;
              *(undefined1 *)(thisPtr + 0x428) = 1;
            }
            if (thisPtr == 0) {
              iVar7 = 0;
            }
            else {
              iVar7 = thisPtr + 0x3c;
            }
            FUN_00403620(uVar4,iVar7,0x8000);
          }
        }
      }
      FUN_0043b1a0();
      cVar3 = FUN_0043b120();
    } while (cVar3 == '\0');
    if (bVar9) {
      *(uint *)(thisPtr + 700) = *(uint *)(thisPtr + 700) | 0x800000;
    }
    if (bVar8) {
      *(uint *)(thisPtr + 700) = *(uint *)(thisPtr + 700) | 0x1000000;
    }
  }
  if (*(int *)(thisPtr + 0x270) == 0) {
    *(uint *)(thisPtr + 700) = *(uint *)(thisPtr + 700) | 0x20;
  }
  return;
}