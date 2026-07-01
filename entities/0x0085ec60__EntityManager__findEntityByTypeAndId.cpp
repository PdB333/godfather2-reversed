// FUNC_NAME: EntityManager::findEntityByTypeAndId
undefined4 __fastcall EntityManager::findEntityByTypeAndId(undefined4 param_1, int param_2, int param_3)
{
  int in_EAX;
  undefined4 uVar1;
  int unaff_ESI;
  
  if ((((param_3 != 0) && (unaff_ESI != 0)) && (param_2 != 0)) &&
     ((in_EAX != 0 && (param_3 == param_2)))) {
    uVar1 = FUN_005f5ec0(unaff_ESI,in_EAX);
    return uVar1;
  }
  return 0;
}