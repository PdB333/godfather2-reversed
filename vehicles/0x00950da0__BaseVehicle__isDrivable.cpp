// FUNC_NAME: BaseVehicle::isDrivable
undefined4 __fastcall BaseVehicle::isDrivable(int this)
{
  int state = *(int *)(this + 0x16c);
  if ((state == 1 || state == 2) && *(float *)(this + 0x170) <= 0.0f) {
    return 1;
  }
  return 0;
}