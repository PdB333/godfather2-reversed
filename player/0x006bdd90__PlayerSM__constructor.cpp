// FUNC_NAME: PlayerSM::constructor
undefined4 * __thiscall PlayerSM::constructor(PlayerSM *this, undefined4 param_2)
{
  BaseClass::constructor(param_2);
  this->vtable = (void **)&g_vtable_PlayerSM;
  this->mStateVtableA = (void **)&g_vtable_StateA;
  this->mStateVtableB = (void **)&g_vtable_StateB;
  this->mCurrentState = 0;
  this->mTimer1 = 0;          // +0x84, uint16
  this->mTimer2 = 0;          // +0x86, uint16
  this->mFlags1 = 0;          // +0x88
  this->mFlags2 = 0;          // +0x8C
  this->mFlags3 = 0;          // +0x90
  this->mFlags4 = 0;          // +0x94
  return this;
}