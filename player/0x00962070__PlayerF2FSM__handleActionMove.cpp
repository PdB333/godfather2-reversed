// FUNC_NAME: PlayerF2FSM::handleActionMove
undefined4 __thiscall handleActionMove(int *this, int actionId)
{
  int iVar1;
  
  iVar1 = FUN_00466840();
  if (actionId != iVar1) {
    iVar1 = FUN_00466860();
    if (actionId != iVar1) {
      switch(actionId) {
      case 6:
        FUN_005a04a0("MoveLeft",0,&DAT_00d8d914,0);
        return 0;
      case 7:
        FUN_005a04a0("MoveRight",0,&DAT_00d8d914,0);
        return 0;
      case 8:
        FUN_005a04a0("MoveUp",0,&DAT_00d8d914,0);
        return 0;
      case 9:
        FUN_005a04a0("MoveDown",0,&DAT_00d8d914,0);
      }
      return 0;
    }
    this[0x16] = -1; // +0x58 - reset some state
  }
  (**(code **)(*this + 0x2c))(); // call virtual at vtable+0x2c (likely stateMachine::update)
  return 0;
}