// FUNC_NAME: PlayerCamera::adjustCameraZoom
void __thiscall PlayerCamera::adjustCameraZoom(int this, int zoomDelta)
{
  int *piVar1;
  int currentZoom;
  char cVar3;
  int newZoom;
  int clampedZoom;
  
  currentZoom = DAT_01130044;
  clampedZoom = FUN_009185a0(); // getCurrentZoomLevel
  if (0x80 < (uint)(clampedZoom + zoomDelta)) {
    newZoom = 0;
    if (*(uint *)(this + 0xa0) < *(uint *)(this + 0x98)) { // +0x98: minZoom, +0xa0: currentZoom
      *(int *)(this + 0xa4) = *(int *)(this + 0xa4) + zoomDelta; // +0xa4: targetZoom
      piVar1 = (int *)(currentZoom + 0xc0); // global zoom modifier
      *piVar1 = *piVar1 - zoomDelta;
      clampedZoom = zoomDelta;
    }
    else if (*(uint *)(this + 0x9c) < *(uint *)(this + 0xa4)) { // +0x9c: maxZoom, +0xa4: targetZoom
      newZoom = clampedZoom - zoomDelta;
      *(uint *)(this + 0xa0) = *(uint *)(this + 0xa0) - zoomDelta; // +0xa0: currentZoom
    }
    currentZoom = *(int *)(currentZoom + 0xb8); // camera mode
    if (((currentZoom == 10) || (currentZoom == 0xb)) || (currentZoom == 0xc)) {
      FUN_00917490(newZoom, clampedZoom); // updateChaseCameraZoom
      return;
    }
    if (currentZoom == 0x19) {
      FUN_00917580(newZoom, clampedZoom); // updateFirstPersonZoom
      return;
    }
    cVar3 = FUN_00917030(); // isCutsceneActive
    if (cVar3 != '\0') {
      FUN_00917670(newZoom, clampedZoom); // updateCutsceneZoom
      return;
    }
    cVar3 = FUN_00917060(); // isCinematicCamera
    if (cVar3 != '\0') {
      FUN_00917760(newZoom, clampedZoom); // updateCinematicZoom
    }
  }
  return;
}