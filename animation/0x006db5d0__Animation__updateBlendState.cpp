// FUNC_NAME: Animation::updateBlendState
void __thiscall Animation::updateBlendState(int this, float deltaTime)
{
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  // Check if blend state is active (2 = blending)
  if (*(int *)(this + 0x1a8) == 2) {
    // If blend progress has reached or exceeded blend duration
    if (*(float *)(this + 0xd8) <= *(float *)(this + 0xdc)) {
      // Copy 0x19 * 4 = 100 bytes from blend source (+0x74) to animation data (+0x10)
      puVar3 = (undefined4 *)(this + 0x74);
      puVar4 = (undefined4 *)(this + 0x10);
      for (iVar2 = 0x19; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      // Mark blend as complete
      *(undefined4 *)(this + 0x1a8) = 0;
      return;
    }
    // Interpolate blend: call with blend factor (progress/duration)
    FUN_006dacd0(this + 0x74, *(float *)(this + 0xdc) / *(float *)(this + 0xd8));
    // Preserve some flag at +0x1a0 across the call
    undefined1 uVar1 = *(undefined1 *)(this + 0x1a0);
    FUN_006db520(extraout_ECX);
    *(undefined1 *)(this + 0x1a0) = uVar1;
    // Advance blend progress by delta time
    *(float *)(this + 0xdc) = deltaTime + *(float *)(this + 0xdc);
  }
  return;
}