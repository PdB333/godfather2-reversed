// FUNC_NAME: AudioManager::updateSoundParameters
void __fastcall AudioManager::updateSoundParameters(int *this)
{
  int iVar1;
  code *pcVar2;
  uint uVar3;
  int iVar4;
  byte bVar5;
  uint uVar6;
  float10 fVar7;
  float local_4;
  
  iVar1 = this[0x3f5]; // +0xFD4 - previousSoundState
  uVar6 = 1;
  if (this[0x433] == 0) { // +0x10CC - soundEnabled
LAB_008659f2:
    if ((this[0x3f4] == -1) || (uVar6 != (this[0x3f5] & 0x7fffffffU))) { // +0xFD0 - soundIndex, +0xFD4 - soundState
      uVar3 = _rand();
      this[0x3f4] = (int)((ulonglong)uVar3 / (0x7fff / (ulonglong)uVar6)); // +0xFD0 - soundIndex
    }
    this[0x3f5] = uVar6; // +0xFD4 - soundState
  }
  else {
    if ((this[0x436] == 0) || // +0x10D8 - soundPriority
       (uVar6 = FUN_008628e0(this[0x433],this[0x435],this[0x436],this[0x438]), // +0x10CC, +0x10D4, +0x10D8, +0x10E0
       uVar6 != 0)) goto LAB_008659f2;
    this[0x3f5] = 1; // +0xFD4 - soundState
    this[0x3f4] = 0; // +0xFD0 - soundIndex
  }
  local_4 = DAT_00d756fc; // defaultVolume
  bVar5 = (byte)((uint)this[0x322] >> 0xb) & 1; // +0xC88 - flags
  if (((uint)this[0x322] >> 0xb & 1) == 0) { // check mute flag
    if (((uint)this[0x3ca] >> 0xe & 1) == 0) { // +0xF28 - soundFlags
      if (this[0x3f4] == -1) { // +0xFD0 - soundIndex
        this[0x3f4] = 0;
      }
      if (this[0x3f5] == -1) { // +0xFD4 - soundState
        this[0x3f5] = 1;
      }
      fVar7 = (float10)FUN_008658d0(1,2,this + 0x414,this[0x3f5] & 0x7fffffff); // +0x1050 - soundParams
      local_4 = (float)fVar7;
      bVar5 = (byte)((uint)this[0x322] >> 0xb) & 1;
      if (((uint)this[0x322] >> 0xb & 1) == 0) {
        uVar6 = this[0x3ca]; // +0xF28 - soundFlags
        goto LAB_00865aaa;
      }
    }
    else {
      pcVar2 = *(code **)(*this + 0x2c8); // vtable +0x2C8 - getVolume
      this[0x3f4] = 0; // +0xFD0 - soundIndex
      fVar7 = (float10)(*pcVar2)();
      local_4 = (float)fVar7;
      bVar5 = (byte)((uint)this[0x322] >> 0xb) & 1;
      if (((uint)this[0x322] >> 0xb & 1) == 0) {
        uVar6 = this[0x3ca]; // +0xF28 - soundFlags
LAB_00865aaa:
        if ((uVar6 >> 0xe & 1) == 0) { // check volume multiplier flag
          local_4 = (float)this[0x3d6] * local_4; // +0xF58 - volumeMultiplier
        }
      }
    }
  }
  else {
    this[0x3f4] = 0; // +0xFD0 - soundIndex
  }
  this[0x3d5] = (int)local_4; // +0xF54 - finalVolume
  if ((bVar5 == 0) && (((uint)this[0x3ca] >> 0xe & 1) == 0)) { // not muted and no volume multiplier
    if ((float)this[0x402] != 0.0) goto LAB_00865c00; // +0x1008 - panValue
    fVar7 = (float10)FUN_0085ec00(this[0x3f4],this[0x3f5] & 0x7fffffff,0); // +0xFD0, +0xFD4
    this[0x3f2] = (int)(float)fVar7; // +0xFC8 - pan
  }
  else {
    this[0x3f2] = 0; // +0xFC8 - pan
  }
  if (this[0x3f4] < (int)(this[0x3f5] & 0x7fffffffU)) { // +0xFD0 < +0xFD4
    iVar4 = _rand();
    this[0x3f2] = // +0xFC8 - pan
         (int)(((float)iVar4 * DAT_00e44590 * DAT_00e4475c - _DAT_00d75754) + (float)this[0x3f2]);
  }
  else {
    iVar4 = _rand();
    this[0x3f2] = (int)((float)this[0x3f2] - (float)iVar4 * DAT_00e44590 * _DAT_00d75754); // +0xFC8 - pan
  }
LAB_00865c00:
  if (iVar1 == -1) {
    this[0x3f1] = this[0x3f2]; // +0xFC4 - previousPan = pan
  }
  return;
}