// FUNC_NAME: PlayerSM::setCurrentState
void __thiscall PlayerSM::setCurrentState(int this, undefined4 stateId)
{
  *(undefined4 *)(this + 0xa50) = stateId;  // +0xa50: currentState
  *(undefined4 *)(this + 0xa78) = 0;        // +0xa78: stateTimer
  *(undefined1 *)(this + 0xa54) = 0;        // +0xa54: stateFlags (byte)
  *(undefined1 *)(this + 0xa55) = 0;        // +0xa55: stateFlags2 (byte)
  *(undefined4 *)(this + 0xa70) = 0;        // +0xa70: stateData1
  *(undefined4 *)(this + 0xa74) = 0;        // +0xa74: stateData2
  *(undefined1 *)(this + 0xa56) = 1;        // +0xa56: stateActive (byte) - set to true
  FUN_0045ee00(this + 4000, 1);             // +0xfa0: some sub-object initialization
  return;
}