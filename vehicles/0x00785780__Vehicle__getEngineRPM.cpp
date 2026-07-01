// FUNC_NAME: Vehicle::getEngineRPM
float __fastcall Vehicle::getEngineRPM(int this)
{
  // +0x2C88: pointer to engine/transmission component
  // +0x78: engine RPM value (float)
  return *(float *)(*(int *)(this + 0x2C88) + 0x78);
}