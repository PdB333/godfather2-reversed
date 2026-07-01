// FUNC_NAME: Vehicle::updateEngineSound
undefined4 __fastcall Vehicle::updateEngineSound(int this)
{
  undefined1 soundParams [76];
  
  if (*(int *)(this + 0x104) != 0) {
    // +0x110: engine sound parameters struct (offset from this)
    // +0x104: engine sound handle/pointer
    FUN_00977090(this + 0x110, soundParams);  // GetEngineSoundParameters
    FUN_004df720(soundParams);                // UpdateSound3D
  }
  return 0;
}