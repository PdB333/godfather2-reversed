// FUNC_NAME: StreamManager::readStreamData
int StreamManager::readStreamData(int param_1, int param_2)
{
  undefined8 uVar1;
  longlong lVar2;
  undefined8 *in_EAX;
  void *pvVar3;
  int iVar4;
  undefined8 local_14;
  longlong local_c;
  
  pvVar3 = _calloc(4,0x40);
  if (pvVar3 == (void *)0x0) {
    return -2;
  }
  local_14 = 0x4000000000;
  local_c = ZEXT48(pvVar3) << 0x20;
  iVar4 = FUN_00665d70(param_1,param_2,0,&local_14);
  if (iVar4 == 0) {
    if ((int)local_c == 1) {
      iVar4 = FUN_006657c0(param_2);
      FUN_00665b40();
      return iVar4;
    }
    uVar1 = *in_EAX;
    lVar2 = in_EAX[1];
    *in_EAX = local_14;
    iVar4 = 0;
    in_EAX[1] = local_c;
    local_14 = uVar1;
    local_c = lVar2;
  }
  FUN_00665b40();
  return iVar4;
}