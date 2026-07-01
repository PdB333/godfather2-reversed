// FUNC_NAME: DialogTreeManager::getProbabilityWeightedChoice
float10 __thiscall DialogTreeManager::getProbabilityWeightedChoice(int this, undefined4 param_2, int *param_3, int param_4, int param_5)
{
  undefined1 *local_10;
  undefined4 local_c;
  undefined4 local_8;
  code *local_4;
  
  local_10 = (undefined1 *)0x0;
  local_c = 0;
  local_8 = 0;
  local_4 = (code *)0x0;
  if (0 < param_5) {
    param_4 = param_4 * 2;
    do {
      // Convert array of 16-bit IDs to string representation
      FUN_004dda40(*(undefined2 *)(*param_3 + param_4),&local_10);
      param_4 = param_4 + 2;
      param_5 = param_5 + -1;
    } while (param_5 != 0);
    if (local_10 != (undefined1 *)0x0) goto LAB_0098a2fc;
  }
  local_10 = &DAT_0120546e; // Default/fallback string
  
LAB_0098a2fc:
  // Call probability calculation based on entity state at +0x38
  fVar2 = (float10)FUN_0048bf40(local_10,*(undefined4 *)(this + 0x38),param_2);
  fVar2 = fVar2 * (float10)DAT_0120588c; // Scale factor
  if (local_10 != (undefined1 *)0x0) {
    (*local_4)(local_10); // Free allocated string
    fVar2 = (float10)(float)fVar2;
  }
  return fVar2;
}