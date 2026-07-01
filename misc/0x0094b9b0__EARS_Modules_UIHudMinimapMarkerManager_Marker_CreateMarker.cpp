// Xbox PDB: EARS_Modules_UIHudMinimapMarkerManager_Marker_CreateMarker
// FUNC_NAME: MissionMarker::createMarker
undefined1 __fastcall MissionMarker::createMarker(undefined4 *this)
{
  char *markerName;
  undefined4 uVar2;
  undefined1 result;
  char idStr [12];
  char buffer [256];
  
  result = 0;
  
  // Get marker type string from a table based on marker type index
  FUN_004d3d90(s_marker_airport_00e56a7c + this[1] * 0x2c);
  
  // If there's a parent marker, remove it first
  if (this[0x85] != 0) {
    FUN_004d43f0(this[0x84], 0, this[0x85]);
  }
  
  // Convert marker ID to string
  __snprintf(idStr, 10, "%u", *this);
  
  // Get marker name pointer (offset +0x18 from this)
  markerName = (char *)(this + 6);
  *markerName = '\0';
  
  // Create the marker via the marker system
  FUN_005a04a0("AddMarker", markerName, &DAT_00d8b2cc, 3, this + 2, idStr, &DAT_0120546e);
  
  // Set flag 0x20000 on the marker (visible flag?)
  this[0x47] = this[0x47] | 0x20000;
  
  // Update marker state
  FUN_005c0d30();
  
  if (*markerName != '\0') {
    // Check if marker should be visible
    if (((uint)this[0x47] >> 6 & 1) != 0) {
      FUN_0094b320(); // Show marker
    }
    
    // Set visibility property
    if ((this[100] != 0) && (*markerName != '\0')) {
      __snprintf(buffer, 0x100, "%s._visible", markerName);
      FUN_0059ee00(buffer, 0); // Set visible to false
    }
    
    // Handle minimap marker
    if (*(char *)(DAT_0112af70 + 0x48) != '\0') {
      uVar2 = FUN_00977420(); // Get minimap manager
      FUN_0094ae10(1, uVar2); // Add marker to minimap
    }
    
    result = 1;
  }
  
  return result;
}