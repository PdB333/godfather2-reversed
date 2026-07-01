// FUNC_NAME: Player::handleDamage
void __thiscall Player::handleDamage(int this, int damageAmount)
{
  int *piVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  float10 fVar6;
  float10 fVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  
  piVar1 = *(int **)(this + 0x5c); // +0x5C: playerData pointer
  iVar4 = FUN_00800a90(); // getCurrentSentient
  if (iVar4 != 0) {
    FUN_00776570(iVar4); // applyDamage
    fVar3 = (float)damageAmount;
    if (damageAmount < 0) {
      fVar3 = fVar3 + DAT_00e44578; // float rounding constant
    }
    *(float *)(this + 0x98) = fVar3 * DAT_00d5efb8; // +0x98: damageMultiplier
    iVar5 = _rand();
    iVar2 = *(int *)(iVar4 + 0x328); // +0x328: sentient health
    fVar6 = (float10)FUN_00701020(); // getRandomFloat
    fVar7 = (float10)iVar2;
    if (iVar2 < 0) {
      fVar7 = fVar7 + (float10)DAT_00e44578;
    }
    *(float *)(this + 0x94) = // +0x94: damageValue
         (float)((float10)iVar5 * (float10)DAT_00e44590 * (float10)_DAT_00d6819c + fVar7 * fVar6 +
                (float10)*(float *)(this + 0x98));
    piVar1[0x7d6] = piVar1[0x7d6] | 0x400000; // set damage flag
    (**(code **)(*piVar1 + 0x264))(); // updateHealthBar
    piVar1[0x7d6] = piVar1[0x7d6] & 0xffbfffff; // clear damage flag
    if (*(char *)(iVar4 + 0x1aa) == '\x01') { // +0x1AA: isPlayer
      uVar8 = 2; // damage type: player
    }
    else {
      uVar8 = 3; // damage type: npc
    }
    FUN_00777200(uVar8); // playDamageSound
    if ((*(uint *)(this + 0xac) >> 10 & 1) != 0) { // +0xAC: flags, bit 10 = isDead
      uVar9 = 0;
      uVar8 = FUN_006fbc40(0,0); // getDeathAnimation
      FUN_007f96a0(0,5,uVar8,uVar9); // playAnimation
      FUN_006fbc70(); // cleanupDeath
    }
  }
  return;
}