// FUNC_NAME: PlayerSM::updateState
void __fastcall PlayerSM::updateState(int *this)
{
  int state;
  uint uVar2;
  int deltaTime;
  char cVar3;
  
  state = this[0x36];
  if (state == 2) {
    uVar2 = this[0x24];
    deltaTime = (int)(longlong)ROUND(DAT_01206800 * DAT_00d60d04); // frame time
    this[0x43] = this[0x43] + deltaTime;
    if ((uVar2 != 0) && (uVar2 <= (uint)this[0x43])) {
      this[0x43] = uVar2;
      cVar3 = (**(code **)(*this + 0xd4))(); // vtable call at +0xd4
      if (cVar3 == '\0') {
        (**(code **)(*this + 0xb4))(); // vtable call at +0xb4
      }
      else if (((uint)this[0x1f] >> 5 & 1) == 0) {
        FUN_008aab00(); // transition to next state
        FUN_008a97a0(); // update animation
      }
    }
    this[0x45] = this[0x45] + deltaTime;
    if (30000 < (uint)this[0x45]) {
      (**(code **)(this[0x14] + 0x28))(2); // call on component
      if (this[0x44] != -1) {
        FUN_0090dff0(this[0x44]); // release resource
        this[0x44] = -1;
      }
      if (this[0x36] == 2) {
        FUN_008ac410(); // handle timeout
        return;
      }
    }
  }
  else if (state == 3) {
    deltaTime = (int)(longlong)ROUND(DAT_01206800 * DAT_00d60d04);
    this[0x43] = this[0x43] + deltaTime;
    if ((uint)this[0x46] <= (uint)this[0x47]) {
      this[0x43] = 0;
      cVar3 = FUN_00481620(); // check condition
      if (cVar3 != '\0') {
        FUN_008a9950(); // handle success
      }
      this[0x36] = 4;
      return;
    }
    if ((uint)this[0x26] <= (uint)this[0x43]) {
      this[0x47] = this[0x47] + 1;
      UNRECOVERED_JUMPTABLE = *(code **)(*this + 0xdc); // vtable call at +0xdc
      this[0x36] = 0;
      (*UNRECOVERED_JUMPTABLE)(); // indirect jump
      return;
    }
  }
  else if (state == 4) {
    if (this[0x43] == 0) {
      (**(code **)(*this + 0xfc))(); // vtable call at +0xfc
      FUN_0092f2c0(); // cleanup
    }
    deltaTime = (int)(longlong)ROUND(DAT_01206800 * DAT_00d60d04);
    this[0x43] = this[0x43] + deltaTime;
    if ((uint)this[0x27] <= (uint)this[0x43]) {
      if ((DAT_01223484 != 0) && ((*(uint *)(DAT_01223484 + 0x37c) >> 0xb & 1) != 0)) {
        *(uint *)(DAT_01223484 + 0x37c) = *(uint *)(DAT_01223484 + 0x37c) | 0x1000;
        this[0x1f] = this[0x1f] | 0x400;
        return;
      }
      FUN_0092e2e0(); // finalize
      this[0x1f] = this[0x1f] | 0x400;
    }
  }
  return;
}