// FUNC_NAME: Weapon::processAmmoInClip
void __fastcall Weapon::processAmmoInClip(int this)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  void *_Base;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float local_38;
  uint local_30;
  uint local_2c;
  uint local_24;
  uint local_18;
  int local_10 [3];
  code *local_4;
  
  fVar11 = 0.0;
  // +0x104 and +0x100 are likely ammo or clip related values
  fVar9 = *(float *)(this + 0x104) + *(float *)(this + 0x100);
  if (fVar9 < 0.0) {
    // +0x1d0 could be weapon data or owner
    iVar3 = *(int *)(this + 0x1d0);
    if (iVar3 == 0) {
      fVar10 = 0.0;
      fVar12 = 0.0;
    }
    else {
      // +0x58 likely fire rate or time between shots
      // +0x188 maybe a multiplier for fire rate
      fVar10 = *(float *)(iVar3 + 0x58) * *(float *)(this + 0x188);
      fVar12 = *(float *)(iVar3 + 0x58) * *(float *)(this + 0x188);
    }
    // DAT_00e44564 is likely a global time constant or time step
    if (DAT_00e44564 - fVar9 / fVar10 == (float)(int)(DAT_00e44564 - fVar9 / fVar12)) {
      if (iVar3 != 0) {
        fVar11 = *(float *)(iVar3 + 0x58) * *(float *)(this + 0x188);
      }
      local_38 = DAT_00e44564 - fVar9 / fVar11;
    }
    else {
      if (iVar3 == 0) {
        fVar10 = 0.0;
      }
      else {
        fVar10 = *(float *)(iVar3 + 0x58) * *(float *)(this + 0x188);
      }
      if (DAT_00e44564 - fVar9 / fVar10 <= 0.0) {
        if (iVar3 != 0) {
          fVar11 = *(float *)(iVar3 + 0x58) * *(float *)(this + 0x188);
        }
        iVar3 = -1 - (int)(fVar9 / fVar11);
      }
      else {
        if (iVar3 != 0) {
          fVar11 = *(float *)(iVar3 + 0x58) * *(float *)(this + 0x188);
        }
        iVar3 = 1 - (int)(fVar9 / fVar11);
      }
      local_38 = (float)iVar3;
    }
    local_24 = (uint)(longlong)ROUND(local_38);
    // +0x118 and +0x10c are likely counts for different ammo types
    uVar7 = *(int *)(this + 0x118) + *(int *)(this + 0x10c);
    local_38 = (float)local_24;
    // Allocate array for combined ammo
    _Base = (void *)FUN_009c8e80(uVar7 * 4);
    uVar6 = 0;
    local_18 = 0;
    // Copy first ammo type list (+0x108 is pointer to list)
    if (*(int *)(this + 0x10c) != 0) {
      do {
        iVar3 = *(int *)(this + 0x108);
        if (local_18 == uVar7) {
          if (uVar7 == 0) {
            iVar4 = 1;
          }
          else {
            iVar4 = uVar7 * 2;
          }
          FUN_00849170(iVar4);
        }
        puVar1 = (undefined4 *)((int)_Base + local_18 * 4);
        local_18 = local_18 + 1;
        if (puVar1 != (undefined4 *)0x0) {
          *puVar1 = *(undefined4 *)(iVar3 + uVar6 * 4);
        }
        uVar6 = uVar6 + 1;
      } while (uVar6 < *(uint *)(this + 0x10c));
    }
    // Copy second ammo type list (+0x114 is pointer to list)
    uVar6 = 0;
    if (*(int *)(this + 0x118) != 0) {
      do {
        iVar3 = *(int *)(this + 0x114);
        if (local_18 == uVar7) {
          if (uVar7 == 0) {
            iVar4 = 1;
          }
          else {
            iVar4 = uVar7 * 2;
          }
          FUN_00849170(iVar4);
        }
        puVar1 = (undefined4 *)((int)_Base + local_18 * 4);
        local_18 = local_18 + 1;
        if (puVar1 != (undefined4 *)0x0) {
          *puVar1 = *(undefined4 *)(iVar3 + uVar6 * 4);
        }
        uVar6 = uVar6 + 1;
      } while (uVar6 < *(uint *)(this + 0x118));
    }
    // Sort combined ammo array
    if (1 < local_18) {
      _qsort(_Base,local_18,4,(_PtFuncCompare *)&LAB_008bd4d0);
    }
    // Process ammo entries
    local_30 = 0;
    if (local_18 != 0) {
      do {
        iVar3 = *(int *)((int)_Base + local_30 * 4);
        iVar4 = FUN_006b34f0();  // Probably get random or time value
        if (((float)iVar4 < 0.0) && (fVar8 = (float10)FUN_008bd4b0(), (float10)0 < fVar8)) {
          // Complex firing/spawn logic
          fVar8 = (float10)FUN_008bd4b0();
          FUN_008bd4b0();
          iVar5 = FUN_00b9a1c0();
          if ((float)-((float10)iVar4 / fVar8) == (float)iVar5) {
            fVar8 = (float10)FUN_008bd4b0();
            fVar8 = -((float10)iVar4 / fVar8);
          }
          else {
            fVar8 = (float10)FUN_008bd4b0();
            if (-((float10)iVar4 / fVar8) <= (float10)0) {
              FUN_008bd4b0();
              iVar4 = FUN_00b9a1c0();
              iVar5 = -1;
            }
            else {
              FUN_008bd4b0();
              iVar4 = FUN_00b9a1c0();
              iVar5 = 1;
            }
            fVar8 = (float10)(iVar5 - iVar4);
          }
          local_2c = (uint)(longlong)ROUND(fVar8);
          if ((uint)local_38 < local_2c) {
            local_2c = (uint)local_38;
          }
          if (local_2c != 0) {
            uVar2 = *(undefined4 *)(iVar3 + 0x38);  // +0x38 likely ammo count or type
            if (local_2c <= *(uint *)(this + 0x140)) {
              // +0x140 is remaining ammo in clip
              *(uint *)(this + 0x140) = *(uint *)(this + 0x140) - local_2c;
              iVar4 = FUN_006b0ee0(uVar2);  // Check if weapon is valid
              if ((iVar4 != 0) && (uVar6 = FUN_006b18a0(), local_2c <= uVar6)) {
                FUN_006b64b0(local_2c);  // Play sound or effect
              }
            }
            FUN_004d4a60(local_10,1,"{#%u}",0x8a00bb20);  // Format string
            FUN_008c0f50(local_10,iVar3,0);  // Probably spawn or activate projectile
            if (local_10[0] != 0) {
              (*local_4)(local_10[0]);  // Call function pointer
            }
            local_38 = (float)((int)local_38 - local_2c);
          }
        }
      } while ((local_38 != 0.0) && (local_30 = local_30 + 1, local_30 < local_18));
    }
    if (_Base != (void *)0x0) {
      FUN_009c8f10(_Base);  // Free allocated memory
    }
  }
  return;
}