// FUNC_NAME: Camera::updateCameraTransform
void __fastcall Camera::updateCameraTransform(Camera *this) {
  float resultPosition[4]; // stack array for virtual call result
  float transformedVectors[6]; // stack space for multiple vectors
  float vecA[3]; // x,y,z from virtual call
  float vecB[3]; // x,y,z from globals
  float vecC[3];
  float vecD[3];
  float *someVtablePtr = *(float **)(this + 0x58); // pointer to vtable-based object (e.g., TransformNode)
  float *handlePtr; // will be used as handle

  // Initialize local vectors from global constants (likely camera offset / equilibrium)
  vecB[0] = DAT_00d6fa18;   // +0x00
  vecB[1] = DAT_00d5ccf8;   // +0x04
  vecB[2] = DAT_00d6fa18;   // +0x08
  vecC[0] = 0.0f;           // +0x0c
  vecC[1] = DAT_00d6fa10;   // +0x10
  vecC[2] = DAT_00d6fa14;   // +0x14
  vecD[0] = DAT_00d6fa10;   // +0x18
  vecD[1] = 0.0f;           // +0x1c (local_14)

  // Virtual call to get position/transform of some node (likely camera pivot)
  // vtable offset 0x48 -> getPosition or getWorldPosition
  (*(void (__thiscall **)(float *))(*someVtablePtr + 0x48))(resultPosition);

  // Accumulate vectors using the result and global constants
  vecC[0] = vecC[0] + resultPosition[0];  // fStack_40
  vecC[1] = resultPosition[1] + vecC[1];  // local_3c = y
  vecB[0] = resultPosition[1] + vecB[0];  // x component from y?
  vecC[2] = resultPosition[2] + vecC[2];  // fStack_38 = z
  vecB[1] = resultPosition[2] + vecB[1];  // y component from z?
  vecD[0] = vecD[0] + _DAT_00d5780c;      // additional global offset
  // fStack_34[0] = fStack_34[0] + resultPosition[0]; // this line missing? Actually fStack_34 is used later but not defined here. It might be on stack.
  // fStack_34 is a variable passed to FUN_00850d80; it appears to be partially computed from the result.
  transformedVectors[3] = transformedVectors[3] + resultPosition[0]; // fStack_34
  vecB[2] = vecB[2] + _DAT_00d5780c;      // more global offset

  // Call transformation function: likely multiply by view matrix or transform
  // piVar1, handle at this+0x7c, stack offset (&fStack_34), this+0xe0
  FUN_00850d80(someVtablePtr, (undefined4 *)(this + 0x7c), &transformedVectors[3], this + 0xe0);

  // Apply the result to the camera (likely set camera transform)
  FUN_00851210(*(undefined4 *)(this + 0x7c));

  // Check conditions for special camera modes
  if ((DAT_01129820 == 0) && (((uint)someVtablePtr[0x927] >> 1 & 1) != 0)) {
    // Special camera mode (e.g., cinematic or don control)
    FUN_007e49d0();
    return;
  }
  // Normal update
  FUN_007e17b0();
}