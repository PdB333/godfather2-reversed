// FUNC_NAME: EARS::AudioManager::dispatchAmbientSound
void __thiscall EARS::AudioManager::dispatchSound(int this, undefined4 param_2)
{
  undefined4 uVar1;
  undefined1 local_220 [176];
  undefined1 local_170 [176];
  undefined1 local_c0 [188];
  
  if (*(int *)(this + 0x24) == 0) {
    // +0x24 = soundType (0=ambient, 1=dynamic)
    uVar1 = FUN_0082e550(local_c0,param_2); // prepareAmbientSource
    FUN_0082a610(uVar1); // playSound
    return;
  }
  if (*(int *)(this + 0x24) != 1) {
    // Unknown sound type, treat as dynamic
    uVar1 = FUN_0082e330(local_170,param_2,0); // prepareDynamicSource
    FUN_0082a610(uVar1); // playSound
    return;
  }
  // Sound type 1: dynamic
  uVar1 = FUN_0082e330(local_220,param_2,0); // prepareDynamicSource
  FUN_0082a610(uVar1); // playSound
  return;
}