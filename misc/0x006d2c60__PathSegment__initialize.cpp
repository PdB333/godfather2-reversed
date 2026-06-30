// FUNC_NAME: PathSegment::initialize

void __thiscall PathSegment::initialize(float *startPos, float *startOrientation, float *endPos)
{
  // Store start position (x,y,z,w) at offsets 0x10-0x1c
  *(float *)(this + 0x10) = startPos[0];
  *(float *)(this + 0x14) = startPos[1];
  *(float *)(this + 0x18) = startPos[2];
  *(float *)(this + 0x1c) = startPos[3];

  // Store start orientation (quaternion) at offsets 0x20-0x2c
  *(undefined4 *)(this + 0x20) = startOrientation[0];
  *(undefined4 *)(this + 0x24) = startOrientation[1];
  *(undefined4 *)(this + 0x28) = startOrientation[2];
  *(undefined4 *)(this + 0x2c) = startOrientation[3];

  // Compute delta = endPos - startPos, store at 0x60-0x6c
  float dx = endPos[0] - startPos[0];
  float dy = endPos[1] - startPos[1];
  float dz = endPos[2] - startPos[2];
  // dw is not needed; force 0 at 0x6c
  *(float *)(this + 0x60) = dx;
  *(float *)(this + 0x64) = dy;
  *(float *)(this + 0x68) = dz;
  *(float *)(this + 0x6c) = 0.0f;

  // Zero out some unused fields (0x40-0x5c range)
  *(undefined4 *)(this + 0x40) = 0;
  *(undefined4 *)(this + 0x44) = 0;
  *(undefined4 *)(this + 0x48) = 0;
  *(undefined4 *)(this + 0x4c) = 0;
  *(undefined4 *)(this + 0x50) = 0;
  *(undefined4 *)(this + 0x54) = 0;
  *(undefined4 *)(this + 0x58) = 0;
  *(undefined4 *)(this + 0x5c) = 0;

  // Store end position (x,y,z,w) at offsets 0x30-0x3c
  *(float *)(this + 0x30) = endPos[0];
  *(float *)(this + 0x34) = endPos[1];
  *(float *)(this + 0x38) = endPos[2];
  *(float *)(this + 0x3c) = endPos[3];

  // Initialize other fields
  *(byte *)(this + 0x7c) = 0;   // some flag
  *(undefined4 *)(this + 0x80) = 0; // unknown
  *(undefined4 *)(this + 0x78) = 0; // unknown

  // Set speed factor (global constants)
  *(float *)(this + 0x84) = DAT_00e510d4 * DAT_00d5eee4; // likely maxSpeed or time

  // Compute distance from start to end
  float sdx = *(float *)(this + 0x10) - endPos[0];
  float sdy = *(float *)(this + 0x14) - endPos[1];
  float sdz = *(float *)(this + 0x18) - endPos[2];
  *(float *)(this + 0x88) = sqrt(sdx*sdx + sdy*sdy + sdz*sdz);

  // Zero progress variables
  *(undefined4 *)(this + 0x70) = 0; // proportion/ time
  *(undefined4 *)(this + 0x74) = 0; // unknown

  // Set two constants (likely max speed / acceleration)
  *(undefined4 *)(this + 0x8c) = DAT_00e51134;
  *(undefined4 *)(this + 0x90) = DAT_00e51188;

  // Clear global flag
  DAT_0112a863 = 0;

  // Zero remaining field
  *(undefined4 *)(this + 0x94) = 0;

  // Attempt to set up interpolation; if first check fails, try second
  float *startPtr = (float *)(this + 0x10);
  bool check1 = FUN_006d0ee0(startPtr, endPos, 0);
  if (!check1) {
    bool check2 = FUN_006d1890(startPtr, endPos);
    if (check2) {
      // Recompute delta (might be adjusted due to collision or something)
      float dy2 = endPos[1] - *(float *)(this + 0x14);
      float dz2 = endPos[2] - *(float *)(this + 0x18);
      float dw2 = endPos[3] - *(float *)(this + 0x1c);
      *(float *)(this + 0x60) = endPos[0] - *startPtr;
      *(float *)(this + 0x64) = dy2;
      *(float *)(this + 0x68) = dz2;
      *(float *)(this + 0x6c) = dw2; // though dw2 will be 0 as endPos[3] - startPos[3]? but startPos[3] was stored, so it may not be zero.
    }
  }
}