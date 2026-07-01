// FUNC_NAME: PlayerGroundSM::updateMovement
void __thiscall PlayerGroundSM::updateMovement(int *this, float dt)
{
  uint uVar1;
  int iVar2;
  char cVar3;
  int *piVar4;
  float10 fVar5;
  float fVar6;
  float fVar7;
  undefined1 uStack_1d;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  undefined4 local_10;
  float local_c;
  undefined4 local_8;
  float fStack_4;
  
  local_10 = 0;
  local_c = 0.0;
  local_8 = 0;
  FUN_0085f890(&local_10,&local_c,&local_8); // Get current movement state (forward, strafe, turn)
  fVar5 = (float10)(**(code **)(*this + 0x1a8))(); // Get speed from virtual function at +0x1a8
  fVar7 = (float)this[0x402]; // +0x1008 - current speed
  fStack_14 = (float)(fVar5 * (float10)_DAT_00e4498c); // Desired speed scaled by global
  fStack_18 = 0.0; // Forward movement
  fStack_1c = 0.0; // Strafe movement
  uStack_1d = 0; // Turn flag
  if (((uint)this[0x3ca] >> 0xe & 1) == 0) { // Check if not in cover
    if ((0.0 < (float)this[0x28b]) && (0.0 >= fVar7)) { // +0xA2C - health > 0 and speed <= 0
      FUN_00549a50(0); // Set forward movement to 0
      FUN_00549a70(0x3f800000); // Set strafe movement to 1.0
      return;
    }
  }
  else {
    FUN_00861be0(&fStack_18,&fStack_1c,&uStack_1d,&fStack_14); // Handle cover movement
  }
  if (((uint)this[0x3ca] >> 0x14 & 1) == 0) { // Check if not in air
    if (((float)this[0x3da] < 0.0) || (0.0 < fVar7)) { // +0xF68 - slope or speed > 0
      if (((float)this[0x3d8] <= 0.0) || (0.0 < (float)this[0x406])) { // +0xF60 - not grounded or +0x1018 - velocity > 0
        if (0.0 < (float)this[0x3dc]) { // +0xF70 - some positive value
          FUN_00866760(&fStack_18,&fStack_1c,&uStack_1d,&local_10); // Handle slope movement
        }
        if (this[0x464] == 0) { // +0x1190 - check if not in vehicle
          if (DAT_00d75ca8 <= local_c) {
            if (DAT_00d75ca4 <= fStack_14) {
              if (local_c <= fStack_14 * DAT_00d5ef70) {
                fStack_1c = fStack_14 / local_c;
              }
              else {
                fStack_1c = 0.0;
              }
            }
            else {
              fStack_1c = 0.0;
            }
          }
          else {
            fStack_1c = DAT_00d5eee4;
          }
        }
        else {
          fVar7 = (float)this[0x3d5]; // +0xF54 - vehicle speed
          if (fStack_14 <= fVar7) {
            fStack_18 = _DAT_00d5780c;
            if (fVar7 - DAT_00d75860 < fStack_14) {
              fStack_18 = (fVar7 - DAT_00d75860) / fStack_14;
            }
          }
          else if (fStack_14 <= fVar7 + DAT_00d75860) {
            fStack_18 = 0.0;
          }
          else {
            fStack_1c = (_DAT_00d5780c / (fVar7 + DAT_00d7585c)) * fStack_14;
            if (_DAT_00d5780c < fStack_1c) {
              fStack_1c = _DAT_00d5780c;
            }
          }
        }
        fVar7 = DAT_00d68260;
        if (((uint)this[0x322] >> 7 & 1) != 0) { // Check if sprinting
          fVar5 = (float10)(**(code **)(*this + 0x2cc))(); // Get sprint speed
          local_c = (float)fVar5;
          fVar7 = local_c;
        }
        if ((fVar7 < fStack_14) ||
           ((1 < this[0x3cc] && (((uint)this[0x3ca] >> 0x16 & 1) != 0)))) { // +0xF30 - some count > 1 and bit 22 set
          FUN_0085fb40(&fStack_18,&fStack_1c,&uStack_1d,local_8); // Apply movement constraints
        }
        if (((uint)this[0x3ca] >> 0x1c & 1) != 0) { // Check if sprinting
          this[0x402] = (int)((float)this[0x402] - dt); // Decrease speed over time
        }
        if ((float)this[0x402] <= DAT_00d7587c) { // Speed below threshold
          FUN_00865d80(DAT_00d5d7b8); // Transition to idle state
        }
        if (((uint)this[0x3ca] >> 0x1c & 1) == 0) { // Not sprinting
          if ((0.0 < (float)this[0x406]) && ((float)this[0x3d8] <= 0.0)) { // +0x1018 - velocity > 0 and not grounded
            FUN_0085fe70(dt,&fStack_18,&fStack_1c,&uStack_1d,fStack_14); // Apply air movement
          }
        }
        else {
          FUN_008666b0(dt,&fStack_18,&fStack_1c,&uStack_1d,fStack_14); // Apply sprint movement
        }
      }
      else {
        FUN_00866390(dt,&fStack_18,&fStack_1c,&uStack_1d,&local_10); // Handle grounded movement
      }
    }
    else {
      local_c = (float)this[1000] * DAT_00d5ef70; // +0xFA0 - some value * global
      FUN_0085fa40(&fStack_18,&fStack_1c,&uStack_1d,(float)this[0x3e6] - local_c,local_c); // Handle slope sliding
    }
  }
  else {
    fStack_1c = _DAT_00d5780c; // Max strafe
    uStack_1d = 1; // Turn flag set
    if (fStack_14 < DAT_00d75700) { // Desired speed below threshold
      if (((uint)this[0x3ca] >> 0x15 & 1) == 0) { // Check if not in jump
        FUN_008621d0(); // Start jump
        this[0x3ca] = this[0x3ca] & 0xffefffff; // Clear bit 20
      }
      else {
        cVar3 = (**(code **)(*this + 0x294))(); // Check if can jump
        if ((((cVar3 != '\0') && (cVar3 = (**(code **)(*this + 0x290))(), cVar3 == '\0')) &&
            ((((uint)this[0x322] >> 0xb & 1) == 0 ||
             ((piVar4 = (int *)FUN_00542d70(), piVar4 == (int *)0x0 ||
              (cVar3 = (**(code **)(*piVar4 + 0x44))(), cVar3 == '\0')))))) &&
           ((*(byte *)((int)this + 0xc8a) & 1) != 0)) { // +0xC8A - some flag
          (**(code **)(*this + 0x2ac))(); // Perform jump
        }
      }
    }
  }
  uVar1 = this[0x3ca];
  if (((((uVar1 >> 0x1a & 1) != 0) || ((uVar1 >> 0x19 & 1) != 0)) && ((float)this[0x3d8] <= 0.0))
     && ((uVar1 >> 0xe & 1) == 0)) { // Check if falling or sliding and not grounded and not in cover
    FUN_00866040(&fStack_18,&fStack_1c,&uStack_1d,fStack_14); // Apply falling movement
  }
  fVar7 = (float)this[0x3da]; // +0xF68 - slope
  if ((fVar7 < 0.0) && (DAT_00e44750 <= fVar7)) {
    fStack_18 = fVar7 * fStack_18 * DAT_00e44718; // Scale forward movement by slope
  }
  FUN_00549a90(local_10); // Set turn direction
  iVar2 = this[0xd8]; // +0x360 - pointer to some object
  fStack_4 = ((float)(*(uint *)(*(int *)(iVar2 + 0x48) + 0xb4) & DAT_00e44680) +
             (float)(*(uint *)(*(int *)(iVar2 + 0x48) + 0x174) & DAT_00e44680)) * _DAT_00d5c458; // Calculate some force
  if (fStack_4 <= _DAT_00d5780c) {
LAB_00866e90:
    if ((0.0 < fStack_18) &&
       (fVar7 = (*(float *)(*(int *)(iVar2 + 0x48) + 0x2e8) +
                *(float *)(*(int *)(iVar2 + 0x48) + 0x228)) * _DAT_00d5c458, DAT_00d5efa4 < fVar7))
    {
      fVar6 = DAT_00d5ef90;
      if (fVar7 <= DAT_00d75728) {
        fVar7 = DAT_00d75728 - fVar7;
        if (0.0 < fVar7) {
          if (DAT_00d75ca0 <= fVar7) {
            fVar7 = DAT_00d75ca0;
          }
        }
        else {
          fVar7 = 0.0;
        }
        fVar7 = fVar7 * DAT_00e44790;
        if ((DAT_00d5ef90 <= fVar7) && (fVar6 = fVar7, _DAT_00d5780c < fVar7)) {
          fVar6 = _DAT_00d5780c;
        }
      }
      if (fVar6 < fStack_18) {
        fStack_18 = fVar6;
      }
    }
LAB_00866f24:
    if (fStack_1c <= 0.0) {
      fStack_1c = 0.0;
      goto LAB_00866f3c;
    }
    if (fStack_1c < _DAT_00d5780c) goto LAB_00866f3c;
  }
  else {
    fVar7 = DAT_00d68260;
    if (((uint)this[0x322] >> 7 & 1) != 0) { // Check if sprinting
      fVar5 = (float10)(**(code **)(*this + 0x2cc))(); // Get sprint speed
      local_c = (float)fVar5;
      fVar7 = local_c;
    }
    if (fStack_4 <= DAT_00d75738) {
      if (0.0 < fStack_18) {
        fVar7 = DAT_00d75738 - fStack_4;
        if (0.0 < fVar7) {
          if (DAT_00d5ef70 <= fVar7) {
            fVar7 = DAT_00d5ef70;
          }
        }
        else {
          fVar7 = 0.0;
        }
        fStack_18 = fVar7 * fStack_18 * DAT_00e44880;
        goto LAB_00866e90;
      }
      goto LAB_00866f24;
    }
    if (fStack_14 <= fVar7 * _DAT_00d5c458) goto LAB_00866e90;
    fStack_1c = (fStack_4 - DAT_00d75738) * DAT_00d5f520 * _DAT_00d5c458 + fStack_1c;
    fStack_18 = 0.0;
    if (fStack_1c <= _DAT_00d5780c) goto LAB_00866f24;
  }
  fStack_1c = _DAT_00d5780c;
LAB_00866f3c:
  if (0.0 < fStack_18) {
    if (_DAT_00d5780c <= fStack_18) {
      fStack_18 = _DAT_00d5780c;
    }
  }
  else {
    fStack_18 = 0.0;
  }
  if (((uint)this[0x322] >> 0xb & 1) == 0) { // Check if not sprinting
    fVar5 = (float10)FUN_00549a00(); // Get current forward movement
    fStack_4 = (float)fVar5;
    fVar7 = (float)this[0x40b] * dt + fStack_4; // +0x102C - acceleration * dt + current
    if (fVar7 < fStack_18) {
      fStack_18 = fVar7;
    }
  }
  FUN_00549a50(fStack_18); // Set forward movement
  if ((0.0 < fStack_1c) &&
     (fVar7 = (*(float *)(*(int *)(iVar2 + 0x48) + 0x168) +
              *(float *)(*(int *)(iVar2 + 0x48) + 0xa8)) * _DAT_00d5c458, DAT_00d5efa4 < fVar7)) {
    fVar7 = DAT_00d75730 - fVar7;
    if (0.0 < fVar7) {
      if (DAT_00e44614 <= fVar7) {
        fVar7 = DAT_00e44614;
      }
    }
    else {
      fVar7 = 0.0;
    }
    fVar7 = _DAT_00d5780c - fVar7 * _DAT_00d75c9c;
    if (_DAT_00d5780c < fVar7) {
      fVar7 = _DAT_00d5780c;
    }
    if (fVar7 < fStack_1c) {
      fStack_1c = fVar7;
    }
  }
  fVar5 = (float10)FUN_00549a10(); // Get current strafe movement
  fStack_4 = (float)fVar5;
  fVar7 = (float)this[0x40a] * dt + fStack_4; // +0x1028 - acceleration * dt + current
  if (fVar7 < fStack_1c) {
    fStack_1c = fVar7;
  }
  if (_DAT_00d5780c < fStack_1c) {
    fStack_1c = _DAT_00d5780c;
  }
  FUN_00549a70(fStack_1c); // Set strafe movement
  FUN_00549ab0(uStack_1d); // Set turn flag
  return;
}