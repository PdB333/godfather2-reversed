// FUNC_NAME: MissionManager::cleanupAirportMarkers
void __fastcall MissionManager::cleanupAirportMarkers(int this)
{
  // Call cleanup function for the airport marker at index (this+4)
  // Each marker is 0x2C bytes, base address is s_marker_airport
  FUN_004d3d90(s_marker_airport_00e56a7c + *(int *)(this + 4) * 0x2c);
  
  // If there's an active airport marker (this+0x214 != 0), destroy it
  // this+0x210 = marker handle/ID, this+0x214 = marker object pointer
  if (*(int *)(this + 0x214) != 0) {
    FUN_004d43f0(*(undefined4 *)(this + 0x210), 0, *(undefined4 *)(this + 0x214));
  }
}