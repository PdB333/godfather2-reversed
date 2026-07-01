// FUNC_NAME: Vehicle::updateEngineSound
void __thiscall Vehicle::updateEngineSound(int this, undefined4 param_2)
{
  char cVar1;
  int *piVar2;
  float10 fVar3;
  undefined1 local_d;
  float fStack_c;
  undefined4 local_8;
  float fStack_4;
  
  // +0x9c: engine state (0 = off, 0x48 = some state)
  if (((*(int *)(this + 0x9c) != 0) && (*(int *)(this + 0x9c) != 0x48)) &&
     (cVar1 = FUN_0087ae60(), cVar1 == '\0')) {
    local_8 = param_2;
    // +0x74: vtable pointer, call method at offset 4 (likely getSoundPosition)
    (**(code **)(*(int *)(this + 0x74) + 4))(&local_8,&local_d);
    fStack_c = DAT_012067e8; // global engine sound volume multiplier
    FUN_00894e50(0x2bc2e885, DAT_012067e8, 0); // play engine sound (hash 0x2bc2e885)
    piVar2 = (int *)FUN_007ff880(); // get current vehicle instance
    if (piVar2 != (int *)0x0) {
      fVar3 = (float10)(**(code **)(*piVar2 + 0x1a8))(); // get engine RPM
      fStack_4 = (float)fVar3;
      if ((float10)DAT_00d58cbc < fVar3) { // compare with RPM threshold
        FUN_008934e0(0x59e1d13d, &stack0xffffffec); // start gear shift sound (hash 0x59e1d13d)
        if (0.0 < fStack_4) {
          FUN_00894ea0(0x59e1d13d, fStack_4, 0); // set gear shift pitch based on RPM
        }
        FUN_00894e50(0xa6ad7e03, fStack_4 * _DAT_00d5e28c * fStack_c, 0); // play gear shift sound with volume
      }
    }
  }
  return;
}