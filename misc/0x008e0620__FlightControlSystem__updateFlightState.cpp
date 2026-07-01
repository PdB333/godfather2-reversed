// FUNC_NAME: FlightControlSystem::updateFlightState
void __fastcall FlightControlSystem::updateFlightState(int this)
{
  char bIsVehicleActive;
  uint uFlightMode;
  
  // Check if vehicle pointer is valid (offset +0x190 = m_pVehicle)
  if (*(int *)(this + 0x190) != 0) {
    // Check if flight is enabled/active
    bIsVehicleActive = FUN_00481620();
    if (bIsVehicleActive != '\0') {
      // Check if autopilot is engaged
      bIsVehicleActive = FUN_008dee80();
      if (bIsVehicleActive == '\0') {
        // Process flight input if autopilot not active
        FUN_008df9c0(*(undefined4 *)(*(int *)(this + 0x190) + 0x1ef4));
      }
      // Update flight dynamics
      FUN_008de510();
      
      // Check if current altitude matches target altitude (global)
      // +0x218 = m_fCurrentAltitude, 0x00d577a0 = _DAT_TARGET_ALTITUDE
      if (*(float *)(this + 0x218) == _DAT_00d577a0) {
        // Set flight mode to hover
        FUN_008e0460(1);
        
        // Determine flight mode based on vehicle state
        // +0x1ef4 = some flight state flag
        uFlightMode = -(uint)(*(int *)(*(int *)(this + 0x190) + 0x1ef4) != 0) & 2;
        
        // Store flight mode at +0x22c = m_uFlightMode
        *(uint *)(this + 0x22c) = uFlightMode;
        
        // Set hovering state at +0x23c = m_bIsHovering
        *(bool *)(this + 0x23c) = uFlightMode == 0;
      }
    }
  }
}