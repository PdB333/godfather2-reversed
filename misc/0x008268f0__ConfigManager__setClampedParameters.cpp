// FUNC_NAME: ConfigManager::setClampedParameters
void __thiscall ConfigManager::setClampedParameters(int param_2, int param_3, int param_4, int param_5, int param_6)
{
  // Local scratch for default values (reused by decompiled pattern)
  int local_8;          // placeholder for default max (used uninitialized in original, assume 0xbb8)
  int local_4 = 0;      // zero sentinel
  int* puVar1;

  // Clamp param_2 to [0, 0xbb8] (3000) and store at +0x5c
  local_8 = 0xbb8; // assumed max, original used uninitialized local_8
  puVar1 = &local_8;
  if ((param_2 < 0xbb9) && (puVar1 = &local_4, -1 < param_2)) {
      puVar1 = &param_2;
  }
  *(int*)(this + 0x5c) = *puVar1;

  // Clamp param_3 to [0, 0x16c] (364) and store at +0x60
  param_2 = 0x16c;    // max value for this field
  local_4 = 0;
  if (param_3 < 0x16d) {
      puVar1 = &local_4;
      if (-1 < param_3) {
          puVar1 = &param_3;
      }
  } else {
      puVar1 = &param_2;
  }
  *(int*)(this + 0x60) = *puVar1;

  // Clamp param_4 to [0, 0x17] (23) and store at +0x64
  param_2 = 0x17;
  param_3 = 0;
  if (param_4 < 0x18) {
      puVar1 = &param_3;
      if (-1 < param_4) {
          puVar1 = &param_4;
      }
  } else {
      puVar1 = &param_2;
  }
  *(int*)(this + 0x64) = *puVar1;

  // Clamp param_5 to [0, 0x3b] (59) and store at +0x68
  param_2 = 0x3b;
  param_3 = 0;
  if (param_5 < 0x3c) {
      puVar1 = &param_3;
      if (-1 < param_5) {
          puVar1 = &param_5;
      }
  } else {
      puVar1 = &param_2;
  }
  *(int*)(this + 0x68) = *puVar1;

  // Clamp param_6 to [0, 0x3b] (59) and store at +0x6c
  param_2 = 0x3b;
  param_3 = 0;
  if (param_6 < 0x3c) {
      puVar1 = &param_3;
      if (-1 < param_6) {
          puVar1 = &param_6;
      }
  } else {
      puVar1 = &param_2;
  }
  *(int*)(this + 0x6c) = *puVar1;

  // Zero out two additional fields
  *(int*)(this + 0x7c) = 0;
  *(int*)(this + 0x80) = 0;
}