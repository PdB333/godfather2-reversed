// FUNC_NAME: SlowMotionEffect::toggleUpdate

undefined4 __fastcall SlowMotionEffect::toggleUpdate(int this)
{
  longlong lVar1;
  float fVar2;
  uint uVar3;
  
  // Check if slow motion is already active and not yet fully started
  if ((*(char *)(this + 0xe8) != '\0') && (*(char *)(this + 0xe9) == '\0') &&
     (DAT_00e44598 < *(float *)(this + 0xc0))) {
    // Save previous state timer values for blending
    *(undefined8 *)(this + 0xc4) = *(undefined8 *)(this + 0xdc);
    *(undefined8 *)(this + 0xd0) = *(undefined8 *)(this + 0xdc);
    *(undefined4 *)(this + 0xcc) = *(undefined4 *)(this + 0xe4);
    *(undefined4 *)(this + 0xd8) = *(undefined4 *)(this + 0xe4);
    *(undefined1 *)(this + 0xe9) = 1;
    // Set current time scale start to a constant (likely slow motion speed)
    fVar2 = DAT_01205214;
    *(float *)(this + 0xc4) = DAT_01205214;
    *(float *)(this + 0xd0) = fVar2;
    // Update end time by adding current threshold
    *(float *)(this + 0xdc) = fVar2 + *(float *)(this + 0xc0);
    // Generate random interpolation value for magnitude
    uVar3 = DAT_010c2678 & DAT_012054b4;
    DAT_012054b4 = DAT_012054b4 + 1;
    *(float *)(this + 0xe0) =
         (*(float *)(this + 0xb0) - *(float *)(this + 0xac)) *
         *(float *)(&DAT_010c2680 + uVar3 * 4) + *(float *)(this + 0xac);
    // Reset current effect duration timer
    *(undefined4 *)(this + 0xe4) = 0;
    // Call the main effect update function
    FUN_006a9870();
    return 1;
  }
  // Stop the slow motion effect: free associated handles
  if (*(int *)(this + 0x88) != 0) {
    FUN_005e6660(*(int *)(this + 0x88));
    *(undefined4 *)(this + 0x88) = 0;
  }
  if (*(int *)(this + 0xa0) != 0) {
    FUN_005e6660(*(int *)(this + 0xa0));
    *(undefined4 *)(this + 0xa0) = 0;
  }
  // Reset global timing system
  FUN_004086d0(&DAT_012069c4);
  // Zero out all timer and state fields
  uVar3 = _DAT_00d5780c;
  lVar1 = (ulonglong)_DAT_00d5780c << 0x20;
  *(longlong *)(this + 0xdc) = lVar1;
  *(longlong *)(this + 0xc4) = lVar1;
  *(longlong *)(this + 0xd0) = lVar1;
  *(uint *)(this + 0xe4) = uVar3;
  *(uint *)(this + 0xcc) = uVar3;
  *(uint *)(this + 0xd8) = uVar3;
  // Clear activation flags
  *(undefined1 *)(this + 0xe8) = 0;
  *(undefined1 *)(this + 0xe9) = 0;
  return 1;
}