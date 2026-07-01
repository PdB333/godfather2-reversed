// FUNC_NAME: Player::updateCoverAdrenaline

void __thiscall Player::updateCoverAdrenaline(int *this, float dt)
{
  int iVar1;
  char cVar2;
  float fVar3;

  cVar2 = FUN_00481620(); // isGamePaused
  if ((cVar2 != '\0') && (cVar2 = FUN_0089c630(), cVar2 != '\0')) { // isCinematicPlaying
    return;
  }
  if ((this[0x1a] == 0) || (this[0x1a] == 0x48)) { // state: idle or cover
    iVar1 = *this;
    cVar2 = (**(code **)(iVar1 + 0x28c))(); // isAdrenalineActive? (no arg)
    (**(code **)(iVar1 + 0x54))((cVar2 != '\0') + '\x01'); // setState (idle=1, active=2)
    iVar1 = *this;
    cVar2 = (**(code **)(iVar1 + 0x28c))(0xc0); // isStateFlagSet(0xC0)
    (**(code **)(iVar1 + 0x5c))((-(uint)(cVar2 != '\0') & 0xffffffc0) + 0x80); // setAdrenalineState
  }
  cVar2 = (**(code **)(*this + 0x140))(); // canUseAdrenaline
  if ((cVar2 != '\0') &&
     (((int *)this[0x17d] == (int *)0x0 || // animationController maybe
      (cVar2 = (**(code **)(*(int *)this[0x17d] + 0x38))(), cVar2 == '\0')))) { // isControllerActive
    FUN_00807ee0(dt); // updateCharacterMovement
    FUN_007f6260(); // updatePhysics
    if ((0.0 < (float)this[0x1eb]) && // adrenalineTimerRemaining
       (fVar3 = (float)this[0x1eb] - dt, this[0x1eb] = (int)fVar3, fVar3 <= 0.0)) {
      this[0x1eb] = DAT_00d5ccf8; // reset timer from global constant
      iVar1 = _DAT_00d5780c;
      this[0x1ec] = _DAT_00d5780c; // store related values
      this[0x1ed] = iVar1;
      FUN_007f64a0(); // onAdrenalineExpired
    }
  }
  FUN_007fd140(dt); // updateComponents
  FUN_007fbba0(); // postUpdate
  return;
}