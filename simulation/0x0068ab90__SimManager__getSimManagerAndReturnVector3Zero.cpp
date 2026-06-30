// FUNC_NAME: SimManager::getSimManagerAndReturnVector3Zero
void SimManager::getSimManagerAndReturnVector3Zero(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  puVar1 = (undefined4 *)SimManager::getSimManager();
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  (**(code **)*puVar1)(param_1,&local_c);
  return;
}