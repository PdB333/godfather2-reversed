// FUNC_NAME: Vehicle::getHeadlightState
uint __fastcall Vehicle::getHeadlightState(int this)
{
  uint result;
  
  result = in_EAX & 0xffffff00;
  if (*(int *)(this + 0x270) != 0) {
    // +0x270: pointer to headlight component or state
    // +700 (0x2BC): headlight state flags, extract bit 28 (0x10000000)
    result = (byte)~(byte)((uint)*(undefined4 *)(this + 700) >> 0x1c) & 0xffffff01;
  }
  return result;
}