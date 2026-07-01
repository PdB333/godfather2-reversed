// FUNC_NAME: Player::updateState
char __thiscall Player::updateState(int *this, int *param_2)
{
  code *pcVar1;
  char cVar2;
  char cVar3;
  uint uVar4;
  int iVar5;
  uint unaff_EBX;
  undefined4 unaff_EBP;
  int unaff_retaddr;
  int *piVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 local_4;
  
  cVar3 = (char)((uint)unaff_EBP >> 0x18);
  local_4 = 0;
  cVar2 = (**(code **)(*param_2 + 0x10))(0x383225a1,&local_4);
  uVar4 = -(uint)(cVar2 != '\0') & unaff_EBX;
  piVar6 = param_2;
  cVar2 = FUN_00795a90(param_2,1);
  if (cVar2 == '\0') {
    if (this[0xcb] != 0) { // +0x32C - some state flag
      uVar7 = 0x796c08;
      cVar2 = FUN_00481620(); // check if game is paused
      if (cVar2 == '\0') {
        FUN_004a8ec0(param_2 + 0x16); // update animation
        FUN_007962e0(piVar6,uVar7); // play sound
        return cVar3;
      }
      if ((this[0xd2] != 0) && (this[0xd2] != 0x48)) { // +0x348 - some index
        if (this[0xd2] == 0) {
          iVar5 = 0;
        }
        else {
          iVar5 = this[0xd2] + -0x48;
        }
        *(int *)(iVar5 + 0x330) = unaff_retaddr;
        FUN_00794930(param_2); // update state machine
      }
      this[0xcc] = unaff_retaddr; // +0x330 - store return address
      uVar7 = 0x796c6b;
      cVar3 = FUN_00794930(param_2);
      if (cVar3 != '\0') {
        uVar8 = 0x796c7e;
        cVar2 = FUN_00481660(); // check some condition
        if (cVar2 != '\0') {
          FUN_004a8ec0(param_2 + 0x16); // update animation
          FUN_00796250(uVar7,uVar8); // play sound
          return cVar3;
        }
      }
    }
  }
  else {
    if ((uVar4 != 0) && (_DAT_00d5780c < DAT_01205228 - (float)this[0xc5])) { // +0x314 - timer
      pcVar1 = *(code **)(*this + 0xb0);
      this[0xc5] = (int)DAT_01205228; // reset timer
      (*pcVar1)(this + 0xdc,0); // call some method
    }
    if (((this[0x9c] != 0) && (uVar4 != 0)) && (((uint)this[0xaf] >> 0x16 & 1) == 0)) { // +0x270 - entity pointer, +0x2BC - flags
      this[0xaa] = DAT_00d5ddec; // +0x2A8 - set some value
      this[0xaf] = this[0xaf] | 0x400000; // set flag bit 22
      iVar5 = FUN_006b07e0(this[0x9c]); // check entity
      if (((iVar5 != 0) && (cVar2 = FUN_006b48b0(), cVar2 != '\0')) &&
         ((((uint)this[0xaf] >> 0x1d & 1) == 0 && (uVar4 != 0)))) { // check flag bit 29
        FUN_0079f100(0x27,0); // play sound effect 0x27
      }
    }
  }
  return cVar3;
}