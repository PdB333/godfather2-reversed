// FUNC_NAME: setTargetPosition
// Function at 0x004deb80: Sets a target position vector (with optional 4th component) in an object.
// If the input vector is non-null and its x,y,z components are not all zero, copies it into the object's storage
// at offsets +0xD0–0xDC and sets a pointer at +0xBC to that internal storage.
// Otherwise, zeroes the storage and nullifies the pointer.
void __fastcall setTargetPosition(float *inputVec, int targetObject)
{
  if ((inputVec != (float *)0x0) &&
      ((inputVec[0] != 0.0f || inputVec[1] != 0.0f || inputVec[2] != 0.0f)))
  {
    float x = inputVec[0];
    float y = inputVec[1];
    float z = inputVec[2];
    float w = inputVec[3];                      // Fourth component (scale/quaternion? unused in zero check)

    *(float *)(targetObject + 0xD0) = x;        // +0xD0: targetPos.x
    *(float *)(targetObject + 0xD4) = y;        // +0xD4: targetPos.y
    *(float *)(targetObject + 0xD8) = z;        // +0xD8: targetPos.z
    *(float *)(targetObject + 0xDC) = w;        // +0xDC: targetPos.w
    *(float **)(targetObject + 0xBC) = (float *)(targetObject + 0xD0); // +0xBC: pointer to targetPos
    return;
  }

  // Null or zero vector → clear target
  *(int *)(targetObject + 0xD0) = 0;
  *(int *)(targetObject + 0xD4) = 0;
  *(int *)(targetObject + 0xD8) = 0;
  *(int *)(targetObject + 0xBC) = 0;            // Clear pointer as well
}