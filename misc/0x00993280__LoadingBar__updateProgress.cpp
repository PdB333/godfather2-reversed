// FUNC_NAME: LoadingBar::updateProgress
void __fastcall LoadingBar::updateProgress(LoadingBar *this)
{
  float fVar1;
  float progress;
  undefined4 colorStart;
  undefined4 colorMiddle;
  undefined1 colorEnd;
  
  // +0x50 : progress counter (0-10)
  if (*(uint *)(this + 0x50) < 10) {
    *(uint *)(this + 0x50) = *(uint *)(this + 0x50) + 1;
    FUN_005a04a0("SetBar", 0, &DAT_00d921ec, 0);  // Update bar fill level
    fVar1 = (float)*(int *)(this + 0x50);
    if (*(int *)(this + 0x50) < 0) {
      fVar1 = fVar1 + DAT_00e44578;
    }
    progress = fVar1 * DAT_00e576b8 * DAT_00d58cbc + DAT_00d92140;  // Calculate progress bar width
    fVar1 = DAT_00d9213c;  // Min bar width
    if ((progress < DAT_00d9213c) || (fVar1 = DAT_00d92140, DAT_00d92140 < progress)) {
      progress = fVar1;  // Clamp to min/max
    }
    FUN_0090cec0(progress);  // Render bar at calculated width
    colorStart = DAT_011304d8;
    colorMiddle = 0;
    colorEnd = 0;
    FUN_00408a00(&colorStart, 0);  // Set start color for gradient
    return;
  }
  FUN_005a04a0("FlashBar", 0, &DAT_00d921ec, 0);  // Full, flash effect
  colorStart = DAT_011302c0;
  colorMiddle = 0;
  colorEnd = 0;
  FUN_00408a00(&colorStart, 0);  // Set flash color
  return;
}