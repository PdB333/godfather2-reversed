// FUNC_NAME: GodfatherGameManager::setupGameState
void GodfatherGameManager::setupGameState(int param_1, int param_2)
{
  int iVar1;
  code *pcVar2;
  int *piVar3;
  
  FUN_005c1ad0(); // likely some initialization
  FUN_0095b320(0); // reset something
  piVar3 = DAT_0112fee4; // global game manager pointer
  iVar1 = *DAT_0112fee4; // dereference to get base
  DAT_0112fee4[0x4d] = param_2; // store param_2 at offset +0x134 (0x4d*4)
  pcVar2 = *(code **)(iVar1 + 0x6c); // get function pointer at +0x6c
  piVar3[0x19] = param_1; // store param_1 at offset +0x64 (0x19*4)
  (*pcVar2)(); // call the function pointer
  (**(code **)(*piVar3 + 0x28))(); // call another function at +0x28
  return;
}