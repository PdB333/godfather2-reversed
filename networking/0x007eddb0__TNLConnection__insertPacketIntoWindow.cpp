// FUNC_NAME: TNLConnection::insertPacketIntoWindow
void TNLConnection::insertPacketIntoWindow(int *this, int param_2, int param_3, undefined4 param_4)
{
  int iVar1;
  
  iVar1 = FUN_007ecb80(param_3, *(undefined4 *)(param_3 + 4), param_4);
  FUN_007edbf0(1);
  *(int *)(param_3 + 4) = iVar1;
  **(int **)(iVar1 + 4) = iVar1;
  if (param_2 == 0) {
    FUN_00b97aea();
  }
  iVar1 = *(int *)(param_3 + 4);
  if (iVar1 == *(int *)(param_2 + 0x18)) {
    FUN_00b97aea();
  }
  this[1] = iVar1;
  *this = param_2;
  return;
}