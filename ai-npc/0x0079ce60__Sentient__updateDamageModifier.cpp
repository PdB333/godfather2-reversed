// FUNC_NAME: Sentient::updateDamageModifier
int __thiscall Sentient::updateDamageModifier(int *this, int damageInfo)
{
  bool bVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  undefined4 uStack_c;
  float fStack_8;
  undefined4 uStack_4;
  
  iVar2 = damageInfo;
  iVar4 = *(int *)(damageInfo + 0x30); // +0x30: damageType
  bVar1 = false;
  if (((iVar4 == 2) && (*(int *)(damageInfo + 0xc) != 0)) && (*(int *)(damageInfo + 0xc) != 0x48)) {
    if (*(int *)(damageInfo + 0xc) == 0) {
      piVar6 = (int *)0x0;
    }
    else {
      piVar6 = (int *)(*(int *)(damageInfo + 0xc) + -0x48); // -0x48: offset to parent object
    }
    damageInfo = 0;
    cVar3 = (**(code **)(*piVar6 + 0x10))(0x55859efa,&damageInfo); // virtual call: isPlayerControlled?
    if ((cVar3 != '\0') && (damageInfo != 0)) {
      cVar3 = FUN_00481660(); // isMultiplayer?
      if (cVar3 == '\0') {
        iVar4 = FUN_00471610(); // getPlayer
        uStack_4 = *(undefined4 *)(iVar4 + 0x38);
        fStack_8 = (float)((ulonglong)*(undefined8 *)(iVar4 + 0x30) >> 0x20);
        _uStack_c = CONCAT44(fStack_8 + _DAT_00d5780c,(int)*(undefined8 *)(iVar4 + 0x30));
        cVar3 = FUN_006c0050(&uStack_c,0,0); // isInRange?
        if (cVar3 != '\0') {
          *(float *)(iVar2 + 0x2c) = (float)this[0x808] * *(float *)(iVar2 + 0x2c); // +0x2020: damageMultiplier
        }
      }
    }
  }
  else {
    if (*(int *)(damageInfo + 0xc) == 0) {
      piVar6 = (int *)0x0;
    }
    else {
      piVar6 = (int *)(*(int *)(damageInfo + 0xc) + -0x48);
    }
    if ((piVar6 == this) && ((iVar4 == 5 || (iVar4 == 4)))) {
      *(float *)(damageInfo + 0x2c) = *(float *)(damageInfo + 0x2c) * _DAT_00d6a7a4; // selfDamageMultiplier
      cVar3 = FUN_008a4380(); // isPlayer?
      if (((cVar3 == '\0') && (*(int *)(iVar2 + 4) != 0)) && (*(int *)(iVar2 + 4) != 0x48)) {
        if (*(int *)(iVar2 + 4) == 0) {
          iVar4 = 0;
        }
        else {
          iVar4 = *(int *)(iVar2 + 4) + -0x48;
        }
        iVar4 = FUN_006c12d0(iVar4,0xa5975eb2); // getComponent?
        if ((iVar4 != 0) && ((*(uint *)(iVar4 + 0xa18) >> 0x19 & 1) != 0)) {
          bVar1 = true;
        }
        if (*(int *)(iVar2 + 4) == 0) {
          iVar4 = 0;
        }
        else {
          iVar4 = *(int *)(iVar2 + 4) + -0x48;
        }
        iVar4 = FUN_0079aea0(iVar4,0xf26fb813); // getCrewLeaderComponent?
        if (iVar4 == 0) {
LAB_0079d0a1:
          if (!bVar1) goto LAB_0079d11f;
        }
        else {
          if (*(int *)(iVar4 + 0x2d4) == 0) {
            piVar6 = (int *)0x0;
          }
          else {
            piVar6 = (int *)(*(int *)(iVar4 + 0x2d4) + -0x48);
          }
          if (piVar6 != this) goto LAB_0079d0a1;
          bVar1 = true;
        }
LAB_0079d0a5:
        uVar5 = FUN_0084d420(*(undefined4 *)(iVar2 + 0x30)); // getDamageTypeFlags?
        if ((uVar5 & 8) != 0) {
          iVar4 = FUN_00471610(); // getPlayer
          fVar8 = *(float *)(iVar2 + 0x20) - *(float *)(iVar4 + 0x30); // position delta
          fVar7 = *(float *)(iVar2 + 0x24) - *(float *)(iVar4 + 0x34);
          fVar9 = *(float *)(iVar2 + 0x28) - *(float *)(iVar4 + 0x38);
          fVar8 = SQRT(fVar9 * fVar9 + fVar7 * fVar7 + fVar8 * fVar8);
          if (fVar8 < 0.0) {
            fVar8 = 0.0;
          }
          if ((fVar8 <= (float)this[0x749]) && (0.0 < *(float *)(iVar2 + 0x2c))) { // +0x1D24: damageRange
            bVar1 = false;
          }
        }
      }
    }
    else if (iVar4 == 9) {
      *(float *)(damageInfo + 0x2c) = *(float *)(damageInfo + 0x2c) * _DAT_00d6a7a4;
    }
    else if (iVar4 == 4) {
      cVar3 = FUN_008a4380();
      if (((cVar3 == '\0') && (*(int *)(iVar2 + 4) != 0)) && (*(int *)(iVar2 + 4) != 0x48)) {
        if (*(int *)(iVar2 + 4) == 0) {
          iVar4 = 0;
        }
        else {
          iVar4 = *(int *)(iVar2 + 4) + -0x48;
        }
        iVar4 = FUN_0079aea0(iVar4,0xf26fb813);
        if (iVar4 != 0) {
          if (-1 < *(char *)(iVar4 + 0x39e)) {
            piVar6 = (int *)FUN_0079b520(); // getPlayerCrewLeader?
            if (piVar6 != this) goto LAB_0079d11f;
          }
          *(float *)(iVar2 + 0x2c) = *(float *)(iVar2 + 0x2c) * _DAT_00d6a7a4;
          bVar1 = true;
          goto LAB_0079d0a5;
        }
      }
    }
  }
LAB_0079d11f:
  cVar3 = FUN_008a4380();
  if (cVar3 != '\0') {
    if (*(int *)(iVar2 + 0x30) == 2) {
      if (*(uint *)(iVar2 + 0x3c) == (uint)this[0x1a3] >> 2) {
        fVar8 = (float)this[0xc5b] * *(float *)(iVar2 + 0x2c); // +0x316C: difficultyDamageMultiplier
LAB_0079d181:
        *(float *)(iVar2 + 0x2c) = fVar8;
      }
    }
    else if (*(int *)(iVar2 + 0x30) == 1) {
      fVar8 = (float)this[0xc5c]; // +0x3170: baseDamage
      *(float *)(iVar2 + 0x2c) = fVar8;
      iVar4 = *(int *)(iVar2 + 4);
      if (((iVar4 != 0) && (iVar4 != 0x48)) && ((*(uint *)(iVar4 + 0x1e98) >> 7 & 1) != 0)) {
        fVar8 = fVar8 * DAT_00d6a5b0; // headshotMultiplier
        goto LAB_0079d181;
      }
    }
  }
  if (((uint)this[0x23a] >> 10 & 1) != 0) goto LAB_0079d1df; // +0x8E8: isInvulnerable?
  FUN_0043b870(DAT_01130fa0); // some debug function
  cVar3 = (**(code **)(*this + 0x78))(); // virtual call: isAlive?
  if (cVar3 != '\0') {
    if ((*(int *)(iVar2 + 0xc) == 0) || (*(int *)(iVar2 + 0xc) == 0x48)) goto LAB_0079d1df;
    if (*(int *)(iVar2 + 0xc) == 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = *(int *)(iVar2 + 0xc) + -0x48;
    }
    cVar3 = FUN_009a9b40(iVar4); // isDamageable?
    if (cVar3 == '\0') goto LAB_0079d1df;
  }
  *(undefined4 *)(iVar2 + 0x2c) = 0; // zero out damage
LAB_0079d1df:
  iVar4 = FUN_008001e0(iVar2); // processDamage?
  if (((iVar4 == 0) || (iVar4 == 1)) && (bVar1)) {
    iVar4 = 3; // return kill
  }
  return iVar4;
}