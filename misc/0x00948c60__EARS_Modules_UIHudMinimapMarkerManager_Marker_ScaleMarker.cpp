// Xbox PDB: EARS_Modules_UIHudMinimapMarkerManager_Marker_ScaleMarker
// FUNC_NAME: GodfatherObject::setScale
void __thiscall GodfatherObject::setScale(int thisObject, float scale)
{
  char buffer [256]; // local_100 - stack buffer for string formatting
  
  if (*(char *)(thisObject + 0x1dc) == '\0') {
    // If the object does not have a parent (animation/animated group)
    if (*(float *)(thisObject + 0x1d8) == _DAT_00d5780c) {
      return; // No change needed
    }
    // Directly set xscale and yscale separately
    __snprintf(buffer, 0x100, "%s._xscale", thisObject + 0x18); // name + 0x18
    FUN_0059ecb0(buffer, DAT_00d5e288); // scale value from global
    __snprintf(buffer, 0x100, "%s._yscale", thisObject + 0x18);
    FUN_0059ecb0(buffer, DAT_00d5e288);
    scale = _DAT_00d5780c; // default scale value
  }
  else {
    // If the object has a parent (is part of an animation hierarchy)
    if (scale == *(float *)(thisObject + 0x1d8)) {
      return; // No change needed
    }
    // Compute uniform scale based on global min/max range
    float fVar1 = (_DAT_00e5736c - _DAT_00e57368) * scale + _DAT_00e57368;
    __snprintf(buffer, 0x100, "%s._xscale", thisObject + 0x18);
    FUN_0059ecb0(buffer, fVar1);
    __snprintf(buffer, 0x100, "%s._yscale", thisObject + 0x18);
    FUN_0059ecb0(buffer, fVar1);
  }
  *(float *)(thisObject + 0x1d8) = scale; // +0x1D8: mCurrentScale
}