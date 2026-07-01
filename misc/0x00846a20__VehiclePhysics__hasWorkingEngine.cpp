// FUNC_NAME: VehiclePhysics::hasWorkingEngine
int __fastcall VehiclePhysics::hasWorkingEngine(int thisPtr)
{
  int iVar1;
  
  iVar1 = FUN_004025a0(*(undefined4 *)(*(int *)(thisPtr + 0xfc) + 8));
  // Check if component exists and is in "active" state (3)
  if ((iVar1 != 0) && (*(int *)(iVar1 + 0x24) == 3)) {
    return 1;
  }
  return 0;
}