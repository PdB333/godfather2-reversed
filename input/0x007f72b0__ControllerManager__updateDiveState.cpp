// FUNC_NAME: ControllerManager::updateDiveState
void __thiscall updateDiveState(int thisPtr, int param_2, int param_3)

{
  // Compare heights (+0x14) against global dive threshold (DAT_00d71c48)
  if ((*(float *)(param_2 + 0x14) <= DAT_00d71c48 && DAT_00d71c48 != *(float *)(param_2 + 0x14)) ||
     (*(float *)(param_3 + 0x14) <= DAT_00d71c48 && DAT_00d71c48 != *(float *)(param_3 + 0x14))) {
    // Set dive bit (bit 3) in flags at +0x970
    *(uint *)(thisPtr + 0x970) = *(uint *)(thisPtr + 0x970) | 8;
  }
  // Clear dive bit if both heights are above another threshold (DAT_00d5c458)
  if (((((*(uint *)(thisPtr + 0x970) >> 3 & 1) != 0) && ((*(uint *)(thisPtr + 0x974) >> 3 & 1) != 0)
       ) && (_DAT_00d5c458 < *(float *)(param_2 + 0x14))) &&
     (_DAT_00d5c458 < *(float *)(param_3 + 0x14))) {
    *(uint *)(thisPtr + 0x970) = *(uint *)(thisPtr + 0x970) & 0xfffffff7;
  }
  return;
}