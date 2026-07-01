// FUNC_NAME: FlashBangEffect::update
void __thiscall FlashBangEffect::update(int *this, int param_2)
{
  int *piVar1;
  int iVar2;
  char cVar3;
  uint uVar4;
  float fVar5;
  float fVar6;
  
  iVar2 = DAT_0112bb50; // global game manager pointer
  if ((*(int *)(param_2 + 0x1c78) != 0) &&
     (piVar1 = (int *)(*(int *)(param_2 + 0x1c78) + -0x48), piVar1 != (int *)0x0)) {
    // Check if param_2 has a valid entity at offset +0x1c78, which appears to be a player/local player
    param_2 = 0;
    cVar3 = (**(code **)(*piVar1 + 0x10))(0x55859efa,&param_2); // virtual function call, likely isLocalPlayer or similar
    if ((cVar3 != '\0') && (param_2 != 0)) {
      cVar3 = FUN_007f7b90(); // check if player is affected by flashbang
      if (cVar3 != '\0') {
        this[1] = 1; // set state to affected
        fVar5 = *(float *)(iVar2 + 0x6c);
        goto LAB_007eec84;
      }
    }
  }
  cVar3 = FUN_007f7c50(); // check other condition (maybe camera visibility)
  fVar5 = _DAT_00d5780c; // default flash duration
  if (cVar3 == '\0') {
    this[1] = 0; // state = none
  }
  else {
    this[1] = 2; // state = partially affected
    fVar5 = *(float *)(iVar2 + 0x70); // shorter duration for partial
  }
LAB_007eec84:
  if (this[0] == 0) { // if active state is 0 (fading in?)
    fVar5 = DAT_012067e8 * fVar5; // scale duration
  }
  else {
    fVar5 = DAT_012067e8 / fVar5; // inverse scale for fading out
  }
  fVar6 = (float)this[2]; // current timer
  this[2] = (int)(fVar6 - fVar5); // decrement timer
  if (fVar6 - fVar5 <= 0.0) { // timer expired
    if (this[0] == 0) { // was fading in
      this[0] = 1; // switch to fading out
      fVar5 = *(float *)(iVar2 + 0x48); // fade out duration
      fVar6 = *(float *)(iVar2 + 0x4c); // fade out randomness
    }
    else { // was fading out (or idle)
      this[0] = 0; // back to fading in
      fVar5 = *(float *)(iVar2 + 0x40); // fade in duration
      fVar6 = *(float *)(iVar2 + 0x44); // fade in randomness
    }
    uVar4 = DAT_010c2678 & DAT_012054b4; // random index
    DAT_012054b4 = DAT_012054b4 + 1; // increment counter
    this[2] = (int)(*(float *)(&DAT_010c2680 + uVar4 * 4) * fVar6 + fVar5); // set new timer with randomness
  }
  return;
}