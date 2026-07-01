// FUNC_NAME: GodfatherGameManager::loadGameData
void __thiscall GodfatherGameManager::loadGameData(int *this, undefined4 param_2)
{
  uint uVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  char *pcVar6;
  int *piVar7;
  undefined4 *puVar8;
  bool bVar9;
  int local_70;
  
  // Begin reading data from a stream (likely a save file or config)
  FUN_0055b540(param_2);
  FUN_0043aff0(param_2,0xa5975eb2);
  cVar2 = FUN_0043b120();
  while (cVar2 == '\0') {
    FUN_0043b210();
    iVar3 = FUN_0043ab70();
    if ((iVar3 - 3U < 9) && (iVar3 - 3U < 9)) {
      FUN_0043b210();
      uVar4 = FUN_0043ab90();
      (**(code **)(*this + 0x94))(this + iVar3 + 0x2a9,uVar4);
    }
    else if ((iVar3 - 0xfU < 8) || ((iVar3 - 0xcU < 3 || (iVar3 - 0x17U < 8)))) {
      piVar7 = this + iVar3 * 3 + 0x30c;
      FUN_0043b210(piVar7);
      FUN_0043ac00(piVar7);
    }
    else {
      switch(iVar3) {
      case 0:
        iVar3 = FUN_0043b210();
        this[0x386] = *(int *)(iVar3 + 8);
        break;
      case 1:
        iVar3 = FUN_0043b210();
        this[0x2aa] = *(int *)(iVar3 + 8);
        break;
      case 2:
        iVar3 = FUN_0043b210();
        this[0x2ab] = *(int *)(iVar3 + 8);
        break;
      case 0x1f:
        iVar3 = FUN_0043b210();
        iVar3 = *(int *)(iVar3 + 8);
        if (iVar3 == 0) {
          this[0x369] = 1;
          this[0x36a] = 1;
        }
        else if (iVar3 == 1) {
          this[0x369] = 4;
          this[0x36a] = 2;
        }
        else if (iVar3 == 2) {
          this[0x369] = 0;
          this[0x36a] = 0;
        }
        break;
      case 0x20:
        iVar3 = FUN_0043b210();
        iVar3 = *(int *)(iVar3 + 8);
        if (iVar3 == 0) {
          this[0x36b] = 1;
          this[0x36c] = 1;
        }
        else if (iVar3 == 1) {
          this[0x36b] = 4;
          this[0x36c] = 2;
        }
        else if (iVar3 == 2) {
          this[0x36b] = 0;
          this[0x36c] = 0;
        }
        break;
      case 0x21:
      case 0x22:
      case 0x23:
      case 0x24:
        if (iVar3 - 0x1dU < 8) {
          iVar5 = FUN_0043b210();
          if (*(int *)(iVar5 + 8) == 1) {
            this[iVar3 + 0x34c] = (-(uint)((~(byte)(iVar3 - 0x1dU) & 1) != 0) & 0xfffffffe) + 4;
          }
          else {
            this[iVar3 + 0x34c] = (uint)(*(int *)(iVar5 + 8) == 0);
          }
        }
        break;
      case 0x25:
        FUN_0043b210();
        uVar4 = FUN_0043abc0();
        FUN_00414d70(uVar4);
        break;
      case 0x26:
        FUN_0043b210();
        uVar4 = FUN_0043abc0();
        FUN_00414d70(uVar4);
        break;
      case 0x27:
        FUN_0043b210();
        uVar4 = FUN_0043abc0();
        FUN_00414d70(uVar4);
        break;
      case 0x28:
        FUN_0043b210();
        uVar4 = FUN_0043abc0();
        FUN_00414d70(uVar4);
        break;
      case 0x29:
        FUN_0043b210();
        uVar4 = FUN_0043abc0();
        FUN_00414d70(uVar4);
        break;
      case 0x2a:
        iVar3 = FUN_0043b210();
        this[0x280] = *(int *)(iVar3 + 8);
        break;
      case 0x2b:
        FUN_0043b210();
        uVar4 = FUN_0043abc0();
        FUN_00414d70(uVar4);
        break;
      case 0x2c:
        FUN_0043b210();
        uVar4 = FUN_0043abc0();
        FUN_00414d70(uVar4);
        break;
      case 0x2d:
        FUN_0043b210();
        uVar4 = FUN_0043abc0();
        FUN_00414d70(uVar4);
        break;
      case 0x2e:
        FUN_0043b210();
        uVar4 = FUN_0043abc0();
        FUN_00414d70(uVar4);
        break;
      case 0x2f:
        iVar3 = FUN_0043b210();
        this[0x2d5] = *(int *)(iVar3 + 8);
        break;
      case 0x30:
        iVar3 = FUN_0043b210();
        this[0x2d6] = *(int *)(iVar3 + 8);
        break;
      case 0x31:
        iVar3 = FUN_0043b210();
        this[0x2d7] = *(int *)(iVar3 + 8);
        break;
      case 0x32:
        iVar3 = FUN_0043b210();
        this[0x2d8] = *(int *)(iVar3 + 8);
        break;
      case 0x33:
        iVar3 = FUN_0043b210();
        this[0x2d9] = *(int *)(iVar3 + 8);
        break;
      case 0x34:
        iVar3 = FUN_0043b210();
        this[0x2da] = *(int *)(iVar3 + 8);
        break;
      case 0x35:
        FUN_0043b210();
        uVar4 = FUN_0043abc0();
        FUN_00414d70(uVar4);
        break;
      case 0x36:
        iVar3 = FUN_0043b210();
        this[0x284] = *(int *)(iVar3 + 8);
        break;
      case 0x37:
        iVar3 = FUN_0043b210();
        FUN_007664a0(*(char *)(iVar3 + 8) != '\0',1);
        break;
      case 0x38:
        FUN_0043b210();
        uVar4 = FUN_0043ab90();
        FUN_004089b0(this + 0x2e5,uVar4);
        break;
      case 0x39:
        FUN_0043b210();
        uVar4 = FUN_0043ab90();
        FUN_004089b0(this + 0x2e7,uVar4);
        break;
      case 0x3a:
        iVar3 = FUN_0043b210();
        FUN_00878980(*(undefined4 *)(iVar3 + 8));
        break;
      case 0x3b:
        iVar3 = FUN_0043b210();
        this[0x289] = *(int *)(iVar3 + 8);
        break;
      case 0x3c:
        FUN_0043b210();
        uVar4 = FUN_0043ab90();
        FUN_004089b0(this + 0x2e9,uVar4);
        break;
      case 0x3d:
        FUN_0043b210();
        uVar4 = FUN_0043ab90();
        FUN_00408980(this + 0x2eb,uVar4);
        break;
      case 0x3e:
        iVar3 = FUN_0043b210();
        this[0x1ef] = *(int *)(iVar3 + 8);
        break;
      case 0x3f:
        FUN_0043b210();
        uVar4 = FUN_0043ab90();
        FUN_004089b0(this + 0x2ed,uVar4);
        break;
      case 0x40:
        iVar3 = FUN_0043b210();
        FUN_007664a0(*(int *)(iVar3 + 8) != 0,0x20);
        break;
      case 0x41:
      case 0x42:
      case 0x43:
      case 0x44:
        piVar7 = this + iVar3 * 4 + 0x193;
        FUN_0043b210(piVar7);
        FUN_0043ad10(piVar7);
        break;
      case 0x45:
        iVar3 = FUN_0043b210();
        bVar9 = *(int *)(iVar3 + 8) != 0;
        FUN_007664a0(bVar9,0x40);
        if (bVar9) {
          FUN_00408680(&DAT_0112dfcc);
          FUN_00408680(&DAT_0112dfc4);
        }
        else {
          if ((this[0x322] & 0xffffff7fU) != this[0x322]) {
            (**(code **)(this[0x16] + 0x28))(0x10);
            this[0x322] = this[0x322] & 0xffffff7f;
          }
          this[0x321] = 0;
          FUN_004086d0(&DAT_0112dfcc);
          FUN_004086d0(&DAT_0112dfc4);
        }
        break;
      case 0x46:
        iVar3 = FUN_0043b210();
        this[0x28a] = *(int *)(iVar3 + 8);
        break;
      case 0x47:
        FUN_0043b210();
        uVar4 = FUN_0043abc0();
        FUN_00414d70(uVar4);
        FUN_00408680(&DAT_0112e104);
        FUN_00408680(&DAT_0112adf8);
        FUN_00408680(&DAT_0112e0f4);
        break;
      case 0x48:
        iVar3 = FUN_0043b210();
        this[0x323] = *(int *)(iVar3 + 8);
        break;
      case 0x49:
        iVar3 = FUN_0043b210();
        this[0x324] = *(int *)(iVar3 + 8);
        break;
      case 0x4a:
        iVar3 = FUN_0043b210();
        this[0x325] = *(int *)(iVar3 + 8);
        break;
      case 0x4b:
        iVar3 = FUN_0043b210();
        uVar1 = *(uint *)(iVar3 + 8);
        this[0x286] = uVar1;
        if ((uVar1 & 2) != 0) {
          FUN_004706f0(0x3f800000);
        }
        if ((*(byte *)(this + 0x286) & 0x80) == 0) {
          FUN_00460020(this[0xaf] + -2);
        }
        else {
          FUN_00460020(this[0xaf]);
        }
        break;
      case 0x4d:
        iVar3 = FUN_0043b210();
        this[0x38b] = (int)(*(float *)(iVar3 + 8) * DAT_00e445c8);
        break;
      case 0x4e:
        iVar3 = FUN_0043b210();
        this[0x38c] = *(int *)(iVar3 + 8);
        break;
      case 0x4f:
        iVar3 = FUN_0043b210();
        this[0x38d] = *(int *)(iVar3 + 8);
        break;
      case 0x50:
        iVar3 = FUN_0043b210();
        this[0x38e] = *(int *)(iVar3 + 8);
        break;
      case 0x51:
        iVar3 = FUN_0043b210();
        local_70 = (int)(longlong)ROUND(*(float *)(iVar3 + 8) * DAT_00d60d04);
        this[0x38f] = local_70;
        break;
      case 0x52:
        iVar3 = FUN_0043b210();
        this[0x390] = *(int *)(iVar3 + 8);
        break;
      case 0x53:
        iVar3 = FUN_0043b210();
        this[0x391] = *(int *)(iVar3 + 8);
        break;
      case 0x54:
        iVar3 = FUN_0043b210();
        this[0x392] = *(int *)(iVar3 + 8);
        break;
      case 0x55:
        FUN_0043b210();
        uVar4 = FUN_0043ab90();
        FUN_004d3d90(uVar4);
        if (this[0x398] != 0) {
          FUN_0099b180(this[0x4c],this + 0x39b);
          FUN_00878c20();
        }
        break;
      case 0x56:
        FUN_0043b210();
        pcVar6 = (char *)FUN_0043ab90();
        if ((pcVar6 != (char *)0x0) && (*pcVar6 != '\0')) {
          FUN_004d3d90(&DAT_00e3ed40);
          FUN_004d4300(pcVar6);
        }
      }
    }
    FUN_0043b1a0();
    cVar2 = FUN_0043b120();
  }
  if ((this[0x3c2] == 0) &&
     ((((this[0x3c3] == 0 && (this[0x3c4] == 0)) && (this[0x3c5] == 0)) ||
      (((this[0x3c2] == 0 && (this[0x3c3] == 0)) &&
       ((this[0x3c4] == 0 && (this[0x3c5] == 0)))))))) {
    piVar7 = (int *)FUN_0045d9e0(param_2);
    this[0x3c2] = *piVar7;
    this[0x3c3] = piVar7[1];
    this[0x3c4] = piVar7[2];
    this[0x3c5] = piVar7[3];
  }
  (**(code **)(this[0x1f1] + 4))(param_2);
  (**(code **)(this[0x3a2] + 0x18))(this[0xba]);
  (**(code **)(this[0x3a2] + 0x14))(param_2);
  FUN_00472460();
  if (this[0x2a7] == 0) {
    iVar3 = FUN_009c8ed0(0x10,&stack0xffffff84);
    if (iVar3 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = FUN_0085c0e0(this);
    }
    this[0x2a7] = iVar3;
  }
  if (this[0x2a8] == 0) {
    puVar8 = (undefined4 *)FUN_009c8e50(8);
    if (puVar8 != (undefined4 *)0x0) {
      puVar8[1] = this;
      *puVar8 = &PTR_LAB_00d764cc;
      this[0x2a8] = (int)puVar8;
      return;
    }
    this[0x2a8] = 0;
  }
  return;
}