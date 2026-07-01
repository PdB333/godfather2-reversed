// FUNC_NAME: Vehicle::updateSteeringAndSpeed
undefined4 __thiscall Vehicle::updateSteeringAndSpeed(int *this, float deltaTime)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float10 extraout_ST0;
  float10 extraout_ST0_00;
  float10 fVar6;
  float10 extraout_ST0_01;
  float10 extraout_ST0_02;
  float fVar7;
  float fVar8;
  double dVar9;
  float fVar10;
  float fVar11;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  float fStack_30;
  undefined1 auStack_2c [4];
  float fStack_28;
  int iStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  
  bVar1 = true;
  (**(code **)(*this + 0x1b0))(); // getSpeed
  fVar7 = DAT_00e44868; // minSpeed
  fVar8 = _DAT_00d7576c; // maxSpeed
  fVar11 = (float)extraout_ST0; // currentSpeed
  fVar10 = 0.0;
  if ((float)this[0x3da] <= 0.0 && (float)this[0x3da] != 0.0) { // engineOn check
    fVar10 = (float)this[0x3df]; // throttleInput
    if (fVar10 < 0.0) {
      if (((DAT_00e44868 <= fVar10) && // minSpeed check
          (this[0x3df] = (int)(fVar10 - deltaTime), fVar10 - deltaTime < fVar7)) &&
         (((uint)this[0x3ca] >> 0x1b & 1) != 0)) { // brakeFlag check
        this[0x3ca] = this[0x3ca] & 0xf7ffffff; // clear brakeFlag
      }
    }
    else {
      this[0x3df] = (int)(fVar10 + deltaTime);
      if ((fVar8 < fVar10 + deltaTime) && (cVar2 = FUN_008613b0(), cVar2 != '\0')) { // maxSpeed reached
        this[0x3df] = (int)(DAT_00e44564 - deltaTime); // set throttle to max - delta
        this[0x3ca] = this[0x3ca] & 0xfbffffff; // clear some flag
        if (((float)this[0x3df] <= DAT_00e44868 && DAT_00e44868 != (float)this[0x3df]) &&
           (((byte)((uint)this[0x3ca] >> 0x1b) & 1) != 0)) {
          this[0x3ca] = this[0x3ca] & 0xf7ffffff; // clear brakeFlag
        }
      }
    }
    fVar8 = DAT_00d7578c; // some speed threshold
    fVar10 = 0.0;
    if (((float)this[0x3da] <= DAT_00d5ccf8 && DAT_00d5ccf8 != (float)this[0x3da]) && // engineOn check
       (((0.0 < (float)this[0x3d8] || (0.0 < (float)this[0x3dc])) || // steeringInput or accelerationInput
        (((uint)this[0x3ca] >> 0x1b & 1) == 0)))) { // brakeFlag not set
      if ((float)this[0x406] <= 0.0) { // handbrake check
        fVar7 = (float)this[0x3d5] * DAT_00d5c454; // steeringInput * steeringFactor
        fVar10 = DAT_00d75860; // minSteeringAngle
        if ((fVar7 <= DAT_00d75860) || (fVar10 = DAT_00d756ec, DAT_00d756ec <= fVar7)) {
          fVar7 = fVar10;
        }
        if (fVar11 < fVar7) { // currentSpeed < steeringAngle
          fVar7 = (float)this[0x3de]; // slideTimer
          this[0x3de] = (int)(deltaTime + fVar7);
          if (deltaTime + fVar7 <= fVar8) goto LAB_0086836b;
          this[0x3e4] = this[0x3e4] + 1; // slideCount
        }
        this[0x3de] = 0; // reset slideTimer
      }
LAB_0086836b:
      fVar8 = DAT_00d5ef70; // some threshold
      if (fVar11 <= DAT_00d75cd0) { // currentSpeed <= lowSpeedThreshold
        fVar7 = (float)this[0x3d7]; // idleTimer
        this[0x3d7] = (int)(fVar7 + deltaTime);
        if ((((fVar8 < fVar7 + deltaTime) && ((float)this[0x3d8] <= 0.0)) && // steeringInput <= 0
            ((float)this[0x3dc] <= 0.0)) && // accelerationInput <= 0
           (((float)this[0x3dc] < 0.0 && (cVar2 = FUN_008671a0(), cVar2 != '\0')))) {
          this[0x3d7] = 0; // reset idleTimer
        }
        bVar1 = false;
      }
      fVar10 = 0.0;
      fVar8 = (float)this[0x3dc]; // accelerationInput
      fVar7 = deltaTime;
      if (fVar8 <= 0.0) {
        if (DAT_00e44750 < fVar8) { // some threshold
          this[0x3dc] = (int)(fVar8 - deltaTime); // decrease acceleration
        }
      }
      else {
        this[0x3dc] = (int)(fVar8 - deltaTime); // decrease acceleration
        if (fVar8 - deltaTime <= 0.0) {
          FUN_0085ec00(this[0x3f4],this[0x3f5] & 0x7fffffff,(uint)this[0x3f5] >> 0x1f); // setEngineSound
          this[0x3f2] = (int)(float)extraout_ST0_00; // engineRPM
          if (DAT_00d5ef70 < (float)this[0x3d7]) { // idleTimer > threshold
            bVar1 = false;
          }
        }
      }
      fVar8 = (float)this[0x3d8]; // steeringInput
      if (fVar8 <= fVar10) {
        if (DAT_00d75cc8 < fVar8) { // some threshold
          this[0x3d8] = (int)(fVar8 - fVar7); // decrease steering
        }
      }
      else {
        this[0x3d8] = (int)(fVar8 - fVar7); // decrease steering
        if (fVar8 - fVar7 <= fVar10) {
          FUN_00601970(this[0x452],&fStack_1c); // getForwardVector
          iVar3 = FUN_00471610(); // getRightVector
          iVar4 = FUN_00471610(); // getUpVector
          iVar5 = FUN_00471610(); // getForwardVector
          if (DAT_00d75ccc <= // some threshold
              *(float *)(iVar4 + 0x24) * fStack_18 + *(float *)(iVar3 + 0x20) * fStack_1c +
              *(float *)(iVar5 + 0x28) * fStack_14) { // dot product check
            *(ulonglong *)(this + 0x3fb) = CONCAT44(fStack_18,fStack_1c); // store direction
            this[0x3fd] = (int)fStack_14;
          }
          else {
            iVar3 = FUN_00471610(); // getRightVector
            iVar4 = FUN_00471610(); // getUpVector
            iVar5 = FUN_00471610(); // getForwardVector
            if (*(float *)(iVar4 + 0x24) * (float)this[0x3fc] +
                (float)this[0x3fb] * *(float *)(iVar3 + 0x20) +
                *(float *)(iVar5 + 0x28) * (float)this[0x3fd] < DAT_00d75ccc) { // dot product check
              this[0x3d8] = DAT_00d5d934; // set steering to some value
              this[0x3ca] = this[0x3ca] | 0x10000; // set some flag
            }
          }
          fVar10 = 0.0;
          if ((float)this[0x3d8] <= 0.0 && (float)this[0x3d8] != 0.0) {
            FUN_00866240(); // resetSteering
            fVar10 = 0.0;
          }
        }
        if (DAT_00d5ef70 < (float)this[0x3d7]) { // idleTimer > threshold
          this[0x3e4] = this[0x3e4] + 1; // slideCount
          this[0x3d7] = (int)fVar10; // reset idleTimer
        }
        bVar1 = false;
      }
      if (fVar10 < (float)this[0x3d7]) {
        this[0x3d7] = (int)fVar10; // reset idleTimer
      }
    }
  }
  if (fVar10 < (float)this[0x3d8]) {
    bVar1 = false;
  }
  if (3 < this[0x3e4]) { // slideCount > 3
    FUN_00867a30(); // handleSlide
    fVar10 = 0.0;
  }
  if (!bVar1) {
    return 0;
  }
  fStack_28 = (float)this[0x414]; // positionX
  fStack_34 = (float)this[0x452]; // forwardVector
  iStack_24 = this[0x415]; // positionY
  fStack_20 = (float)this[0x416]; // positionZ
  fVar8 = (float)this[0x3f1]; // speed
  if (fVar8 != fVar10) {
    dVar9 = (double)fStack_34;
    FUN_00b99e20(); // sin
    fStack_28 = fStack_28 - (float)dVar9 * fVar8; // update positionX
    dVar9 = (double)fStack_34;
    FUN_00b99fcb(); // cos
    fStack_20 = (float)dVar9 * fVar8 + fStack_20; // update positionZ
  }
  fVar6 = (float10)FUN_00470250(&fStack_28); // getAngle
  fStack_34 = (float)fVar6; // currentAngle
  fVar6 = (float10)(**(code **)(*this + 0x1b8))(); // getTargetAngle
  fStack_38 = (float)fVar6; // targetAngle
  fVar8 = DAT_00d75744; // some angle threshold
  if ((((uint)this[0x3ca] >> 0xe & 1) == 0) && // some flag check
     (fVar6 = (float10)(**(code **)(*this + 0x1b0))(), fVar8 = DAT_00d7573c,
     (float10)_DAT_00d7574c < fVar6)) { // speed check
    fVar8 = DAT_00d75744;
  }
  FUN_00875220(this,&fStack_28); // updatePosition
  fStack_30 = (float)extraout_ST0_01; // newAngle
  fVar7 = (float)((uint)fStack_30 & DAT_00e44680); // angleDiff
  if (DAT_00d5f00c <= fVar7) { // angleDiff threshold
    fVar10 = fStack_30 - (float)this[0x452]; // angleDelta
    if (fVar10 <= DAT_00d5eeec) {
      if (fVar10 < DAT_00e44588) {
        fVar10 = fVar10 + DAT_00d5d70c; // wrap around
      }
    }
    else {
      fVar10 = fVar10 - DAT_00d5d70c; // wrap around
    }
    fStack_3c = DAT_00d7578c; // some speed threshold
    if (fVar10 < DAT_00d5f00c) goto LAB_00868862;
  }
  fVar10 = fStack_38; // targetAngle
  if (DAT_00d6a16c < fVar7) { // angleDiff > some threshold
    fVar7 = _DAT_00d5780c - fVar7 * _DAT_00d75cc4; // calculate steering factor
    if (0.0 < fVar7) {
      if (_DAT_00d5780c <= fVar7) {
        fVar7 = _DAT_00d5780c;
      }
      fVar10 = fVar7 * fStack_38; // apply steering factor
    }
    else {
      fVar10 = fStack_38 * 0.0; // no steering
    }
  }
  fVar7 = (float)this[1000] + fVar8; // some offset + angle threshold
  if (fVar10 < fVar7) {
    fVar10 = fVar7;
  }
  if (DAT_00d75780 < fVar10) { // maxAngle
    fVar10 = DAT_00d75780;
  }
  if (fVar10 * DAT_00e4483c < fStack_34) { // angle check
    return 0;
  }
  fStack_3c = DAT_00d5c454; // some factor
  if ((fStack_34 < fVar10) && (fStack_3c = DAT_00d5ef70, fStack_34 < fVar7)) {
    fStack_3c = DAT_00d75750; // another factor
  }
LAB_00868862:
  fStack_3c = fStack_3c * fVar11; // factor * currentSpeed
  if (fStack_3c < DAT_00d75cc0) {
    fStack_3c = DAT_00d75cc0; // clamp to min
  }
  if ((this[0x3cc] == 0) && // some state check
     (cVar2 = FUN_005fe940(auStack_2c,&fStack_30,&fStack_38), fVar11 = DAT_00d69acc, cVar2 != '\0')) // check if near target
  {
    fVar7 = DAT_00e44564 - fStack_30; // distance to target
    this[0x3cd] = (int)fVar7; // store distance
    if (fVar11 <= fVar7) {
      if (fVar7 <= DAT_00e447a4) {
        this[0x3cc] = 1; // state = near
      }
      else {
        this[0x3cc] = 3; // state = far
      }
    }
    else {
      this[0x3cc] = 2; // state = medium
    }
  }
  if (1 < this[0x3cc]) { // not near
    fStack_38 = (float)this[1000] + fVar8; // some offset + angle threshold
    if (this[0x3cc] == 3) { // far
      fStack_38 = fStack_38 + DAT_00d75750; // add extra offset
      fVar11 = DAT_00d68260; // some speed factor
      if (((uint)this[0x322] >> 7 & 1) != 0) { // some flag check
        (**(code **)(*this + 0x2cc))(); // getBoostSpeed
        fVar11 = (float)extraout_ST0_02;
      }
      if (fStack_3c < fVar11) {
        fStack_3c = fVar11; // use boost speed
      }
    }
    if (fStack_38 < fStack_34) { // targetAngle < currentAngle
      fStack_34 = fVar8 * DAT_00d5c454 * fStack_34; // calculate new angle
      if (_DAT_00d5780c < fStack_34) {
        fStack_34 = _DAT_00d5780c; // clamp
      }
      if (((DAT_00e447a4 - fStack_34 * _DAT_00d75cbc <= (float)(this[0x3cd] & DAT_00e44680)) && // distance check
          (_DAT_00d577a0 < (float)this[0x445] - (float)this[0x444])) && // some difference check
         ((float)this[0x445] - (float)this[0x444] <= fStack_3c * deltaTime * DAT_00d5eee4)) { // speed check
        return 0;
      }
    }
  }
  this[0x440] = (int)fStack_3c; // store final speed
  return 1;
}