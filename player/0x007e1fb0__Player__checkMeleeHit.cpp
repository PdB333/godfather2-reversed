// FUNC_NAME: Player::checkMeleeHit
undefined4 __thiscall Player::checkMeleeHit(int this, int *targetEntity)
{
  float fVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  float10 extraout_ST0;
  float10 fVar6;
  undefined4 uStack_d0;
  float fStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  float fStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined1 uStack_b0;
  undefined4 uStack_ac;
  undefined1 auStack_94 [20];
  undefined1 auStack_80 [32];
  float fStack_60;
  int iStack_20;
  
  iVar4 = *(int *)(this + 0x58); // +0x58: player's entity pointer
  if ((*(char *)(iVar4 + 0x2150) != '\0') && (targetEntity != (int *)0x0)) {
    cVar2 = FUN_007f7c50(); // likely isGamePaused() or similar
    if (cVar2 == '\0') {
      (**(code **)(*targetEntity + 0xc0))(); // virtual call on target, likely getPosition or getBounds
      if (((float10)0 < extraout_ST0) && ((*(byte *)(targetEntity + 0x286) & 1) == 0)) {
        iVar3 = FUN_00471610(); // getPlayerCamera or getActiveCamera
        fVar6 = (float10)FUN_004702b0(iVar3 + 0x30); // getCameraFov or similar
        fVar1 = *(float *)(iVar4 + 0x1f80); // +0x1f80: melee range
        iVar3 = FUN_00691810(); // getGameManager or getSimManager
        if (iVar3 != 0) {
          iVar3 = FUN_00691810();
          if ((*(char *)(iVar3 + 0x1ad) == '\x1a') && ((*(uint *)(iVar4 + 0x8e0) >> 10 & 1) != 0)) {
            cVar2 = FUN_007d3830(targetEntity,iVar4); // likely canTargetEntity
            if (cVar2 != '\0') {
              cVar2 = FUN_007f80e0(targetEntity,*(undefined4 *)(iVar4 + 0x1f74)); // likely isInLineOfSight
              if (cVar2 != '\0') {
                uStack_b0 = 0;
                uStack_ac = 0;
                FUN_00540bc0(0x62,0x10000,0,0); // allocate memory or create object
                uStack_ac = FUN_00540cc0(auStack_94); // initialize something
                iVar4 = FUN_00471610(); // get camera again
                uStack_d0 = *(undefined4 *)(iVar4 + 0x30); // camera position x
                uStack_c8 = *(undefined4 *)(iVar4 + 0x38); // camera position z
                fStack_cc = *(float *)(iVar4 + 0x34) + DAT_00d6bfe4; // camera position y + offset
                uStack_c4 = _DAT_00d5780c; // some constant
                iVar4 = FUN_00471610();
                uStack_c0 = *(undefined4 *)(iVar4 + 0x30);
                uStack_b8 = *(undefined4 *)(iVar4 + 0x38);
                fStack_bc = *(float *)(iVar4 + 0x34) + DAT_00d6bfe4;
                uStack_b4 = _DAT_00d5780c;
                FUN_0046d6a0(); // likely updateWorldTransform or similar
                FUN_009e5ed0(&uStack_d0,auStack_80); // likely performRaycast
                if (iStack_20 != 0) {
                  piVar5 = (int *)FUN_00752dc0(auStack_80); // getHitEntity from raycast result
                  if ((piVar5 == targetEntity) && (fStack_60 * fStack_60 * (float)fVar6 < fVar1 * fVar1))
                  {
                    return 1; // hit successful
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return 0; // no hit
}