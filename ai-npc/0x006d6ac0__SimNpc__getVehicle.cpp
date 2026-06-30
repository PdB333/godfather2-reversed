// FUNC_NAME: SimNpc::getVehicle
int __fastcall SimNpc::getVehicle(int thisPtr)
{
  if (*(int *)(thisPtr + 0x31a8) != 0) {
    return *(int *)(thisPtr + 0x31a8) + -0x48;
  }
  return 0;
}