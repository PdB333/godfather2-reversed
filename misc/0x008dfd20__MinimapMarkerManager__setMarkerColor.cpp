// FUNC_NAME: MinimapMarkerManager::setMarkerColor
void __fastcall MinimapMarkerManager::setMarkerColor(int this)
{
  int markerType;
  
  markerType = *(int *)(this + 0x22c); // +0x22c: marker type enum (0=default, 1=gray, 2=blue)
  if (markerType == 0) {
    // Default color - white
    FUN_0094ac00(*(undefined4 *)(this + 0x240), 0xff, 0, 0); // setColor(r, g, b)
  }
  else {
    if (markerType == 1) {
      // Gray color
      FUN_0094ac00(*(undefined4 *)(this + 0x240), 0x80, 0x80, 0x80);
      return;
    }
    if (markerType == 2) {
      // Blue color
      FUN_0094ac00(*(undefined4 *)(this + 0x240), 0, 0, 0xff);
      return;
    }
  }
  return;
}