// Xbox PDB: EARS_Apt_UIFamilyMemberInfo_GetWeaponPrice
// FUNC_NAME: BuildingManager::getBuildingPrice
float BuildingManager::getBuildingPrice(float param_1)
{
  undefined4 uVar1;
  
  uVar1 = FUN_004db3a0(param_1,"_PRICE",6);
  param_1 = 0.0;
  FUN_008934e0(uVar1,&param_1);
  return (float)param_1;
}