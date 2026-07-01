// FUNC_NAME: Player::canAttackTarget
undefined4 __fastcall Player::canAttackTarget(int *this)
{
  float fVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  float10 fVar7;
  undefined1 local_c [4];
  int *local_8 [2];
  
  iVar2 = this[0x3e5]; // +0xF94: some manager/container pointer
  iVar5 = 0;
  if (0 < *(int *)(iVar2 + 0xc4)) { // +0xC4: count of something
    do {
      iVar4 = *(int *)(*(int *)(iVar2 + 0xc0) + iVar5 * 4); // +0xC0: array of pointers
      if ((iVar4 != 0) && (*(char *)(iVar4 + 0x10) + iVar4 != 0)) { // +0x10: some validity flag
        FUN_004af8c0(local_8,0x2001); // get some object by type ID 0x2001
        piVar6 = (int *)0x0;
        if (local_8[0] != (int *)0x0) {
          piVar6 = local_8[0];
        }
        if ((piVar6 != (int *)0x0) && (piVar6 != this)) {
          iVar4 = FUN_00471610(); // get player position/transform
          fVar7 = (float10)FUN_00875220(this,iVar4 + 0x30); // distance check
          if (ABS(fVar7) < (float10)_DAT_00d7586c) { // within max attack range
            iVar4 = FUN_00471610();
            fVar7 = (float10)FUN_00470250(iVar4 + 0x30); // angle/direction check
            if ((fVar7 < (float10)_DAT_00d75868) && // within attack angle
               (cVar3 = (**(code **)(*piVar6 + 0x10))(0x10e5319e,local_c), cVar3 != '\0')) { // check if target is valid/attackable
              if ((float)this[0x3df] <= (float)piVar6[0x3df] && // +0xF7C: some priority/level comparison
                  (float)piVar6[0x3df] != (float)this[0x3df]) {
                return 0;
              }
              fVar7 = (float10)(**(code **)(*piVar6 + 0x1b0))(); // get target's health/state
              fVar1 = (float)piVar6[0x3df];
              if (((fVar1 <= DAT_00e44868) && (((uint)piVar6[0x3ca] >> 0x1b & 1) == 0)) && // +0xF28: some flag check
                 (DAT_00d75858 < (float)fVar7)) { // health below threshold
                return 0;
              }
              if (((fVar1 < 0.0) && (DAT_00e44868 < fVar1)) &&
                 ((float)piVar6[0x3da] <= 0.0 && (float)piVar6[0x3da] != 0.0)) { // +0xF68: speed check
                iVar4 = FUN_00471610();
                fVar7 = (float10)FUN_00875220(piVar6,iVar4 + 0x30); // distance to target
                if (ABS(fVar7) < (float10)_DAT_00d75864) { // too close to attack
                  return 0;
                }
              }
            }
          }
        }
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < *(int *)(iVar2 + 0xc4));
  }
  return 1;
}