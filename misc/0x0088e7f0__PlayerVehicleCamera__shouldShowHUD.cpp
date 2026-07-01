// FUNC_NAME: PlayerVehicleCamera::shouldShowHUD
bool PlayerVehicleCamera::shouldShowHUD(void)
{
  int *vtable;
  
  // Check game state manager pointer is valid
  if ((**(int **)(DAT_012233a0 + 4) != 0) &&
     (vtable = (int *)(**(int **)(DAT_012233a0 + 4) + -0x1f30), vtable != (int *)0x0)) {
    // Call a camera-related function via vtable (+0xC0)
    (**(code **)(*vtable + 0xc0))();
    // If the returned pitch/angle value is <= 0, return false (don't show HUD)
    if (extraout_ST0 <= (float10)0) {
      return false;
    }
  }
  // Return whether the HUD visibility flag is set (0 = visible, likely inverted logic)
  return DAT_01129820 == 0;
}