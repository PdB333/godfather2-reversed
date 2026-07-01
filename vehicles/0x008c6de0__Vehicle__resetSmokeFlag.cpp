// FUNC_NAME: Vehicle::resetSmokeFlag
void __fastcall Vehicle::resetSmokeFlag(Vehicle *this)
{
  *(undefined1 *)((int)this + 0x3d) = 0;
  return;
}