// FUNC_NAME: AerodynamicComponent::applyAerodynamicForces
void __fastcall AerodynamicComponent::applyAerodynamicForces(int thisPtr)
{
  float *forceResult;
  float velocityDiff;
  
  // Subtract ambient wind speed (stored at DAT_01205228) from the object's velocity
  velocityDiff = *(float *)(thisPtr + 0x7c) - DAT_01205228;
  
  // Call to set up aerodynamic force calculation parameters (function ID 8, drag coefficient 0x8a259734)
  FUN_0043d020(8, thisPtr + 0x20, 0x8a259734, 0xffffffff);
  
  // Get pointer to the force output vector (two floats)
  forceResult = (float *)FUN_0043d590();
  
  // Clamp velocity difference to non-negative (no negative drag)
  if (velocityDiff <= 0.0) {
    velocityDiff = 0.0;
  }
  
  // Set resulting forces: drag force along velocity axis (x-component) and lift force (y-component from +0x80)
  *forceResult = velocityDiff;
  forceResult[1] = *(float *)(thisPtr + 0x80);
  
  // Apply the computed forces to the object (function ID 1 indicates final application)
  FUN_0043d5c0(1);
  
  return;
}