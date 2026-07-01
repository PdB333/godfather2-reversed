// FUNC_NAME: PlayerSM::updateState
void __thiscall PlayerSM::updateState(int *this, char param_2, undefined4 param_3, undefined4 param_4)

{
  int iVar1;
  float10 fVar2;
  float fVar3;
  undefined4 *puStack_e8;
  undefined4 *puStack_e4;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  int iStack_90;
  uint uStack_8c;
  undefined1 auStack_88 [4];
  int iStack_84;
  int iStack_80;
  int iStack_7c;
  undefined1 auStack_70 [12];
  undefined1 auStack_64 [12];
  undefined4 uStack_58;
  undefined4 uStack_48;
  undefined4 uStack_38;
  undefined4 uStack_28;
  
  // Check bit 0x13 of flags at +0xC88 (0x322*4)
  if (((uint)this[0x322] >> 0x13 & 1) == 0) {
    puStack_e4 = (undefined4 *)0x868d9a;
    FUN_008622a0(); // likely some debug/assert
  }
  else {
    puStack_e4 = (undefined4 *)0x868d93;
    FUN_008621d0(); // likely some debug/assert
  }
  this[0x3cc] = 0; // +0xF30 - clear some timer/counter
  puStack_e4 = (undefined4 *)0x868db7;
  iVar1 = FUN_005466a0(); // get game manager or similar
  puStack_e4 = (undefined4 *)0x868dc0;
  FUN_009f2000(); // some engine call
  puStack_e4 = &DAT_01139820;
  (**(code **)(*(int *)(iVar1 + 0xd0) + 0x40))(); // vtable call on some object
  FUN_009f2000();
  puStack_e8 = &DAT_01139820;
  (**(code **)(*(int *)(iVar1 + 0xd0) + 0x44))(); // vtable call
  uStack_c4 = 0;
  uStack_c0 = 0;
  uStack_bc = 0;
  uStack_b8 = 0;
  uStack_b0 = 0;
  uStack_ac = 0;
  uStack_a8 = 0;
  uStack_a4 = 0;
  uStack_9c = 0;
  uStack_c8 = _DAT_00d5780c; // some global constant
  uStack_b4 = _DAT_00d5780c;
  uStack_a0 = _DAT_00d5780c;
  uStack_8c = 0;
  iStack_90 = 0;
  uStack_94 = 0;
  uStack_98 = 0;
  (**(code **)(**(int **)(iVar1 + 0x10) + 0x1c))(&uStack_c8,0,auStack_88); // get some transform/matrix
  this[0x3f6] = iStack_80; // +0xFD8
  this[0x3f7] = iStack_90; // +0xFDC
  this[1000] = iStack_7c; // +0xFA0
  this[0x3e9] = uStack_8c & DAT_00e44680; // +0xFA4
  this[0x3f0] = iStack_84; // +0xFC0
  this[0x3ca] = this[0x3ca] & 0xffff7fff; // +0xF28 - clear bit 15
  if ((*(byte *)(this + 0x3ca) & 1) == 0) { // check bit 0 of +0xF28
    if (((uint)this[0x322] >> 0xb & 1) == 0) { // check bit 0xB of +0xC88
      iVar1 = FUN_005faf10(this + 0x3d1); // +0xF44 - get some object
    }
    else {
      iVar1 = *(int *)(DAT_0112af68 + 0x194); // global pointer
    }
    if (iVar1 == 0) {
      FUN_008621d0(); // debug/assert
      puStack_e8 = (undefined4 *)&DAT_01139800;
    }
    else {
      if (param_2 == '\0') {
        FUN_00875190(auStack_70,0); // init some structure
        iVar1 = FUN_00471610(); // get player or similar
        FUN_0043a210(&puStack_e4,iVar1 + 0x20); // get some pointer
        FUN_00601760(this + 0x3d1,auStack_70,&puStack_e4,0); // set up something
      }
      else {
        FUN_00868b20(param_3,param_4); // handle input/action
        uStack_58 = 0;
        uStack_48 = 0;
        uStack_38 = 0;
        uStack_28 = _DAT_00d5780c;
        FUN_005fe860(auStack_64); // get some state
        (**(code **)(*this + 0x28))(auStack_64); // vtable call on this
      }
      this[0x441] = this[0x441] & 0xfffffffe; // +0x1104 - clear bit 0
      this[0x440] = this[0x3d5]; // +0xF54 -> +0x1100
      if (this[0x3cb] == 2) { // +0xF2C - state check
        iVar1 = FUN_00471610(); // get player
        fVar3 = (float)this[0x3d5]; // +0xF54
        if (((uint)this[0x322] >> 0xb & 1) != 0) {
          fVar2 = (float10)FUN_00860e70(); // get some time/scale
          fVar3 = (float)fVar2;
        }
        puStack_e4 = (undefined4 *)(*(float *)(iVar1 + 0x20) * fVar3); // multiply by speed
        FUN_005466c0(&puStack_e4); // set speed
        FUN_0085f170(); // update movement
        FUN_00851210(this[0x3e5]); // +0xF94 - update animation
      }
    }
  }
  if (((this[0x3cb] == 0) || (this[0x3cb] == 1)) || ((*(byte *)(this + 0x3ca) & 1) != 0)) {
    this[0x441] = this[0x441] | 1; // +0x1104 - set bit 0
    this[0x440] = 0; // +0x1100
    FUN_00851230(this[0x3e5]); // +0xF94 - stop animation
  }
  FUN_008659a0(); // some post-update
  if ((char)this[499] != (char)puStack_e8) {
    FUN_0087f870(puStack_e8); // handle state change
  }
  this[0x3ca] = this[0x3ca] | 0x1000000; // +0xF28 - set bit 24
  return;
}