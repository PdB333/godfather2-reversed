// FUNC_NAME: WhiteboxCar::createWheel
undefined4* __thiscall WhiteboxCar::createWheel(void* this, undefined4 wheelId, float steerAngle, float suspensionCompression, undefined4 parentObject)
{
  // +0x80: wheelRadius or restingLength
  // +0x84: suspension stiffness (or inverse)
  // +0x90-0x9c: quaternion representing chassis orientation (x, y, z, w)
  float chassisOrientation[4]; // stored at this+0x90
  float wheelRadius = *(float*)((int)this + 0x80);
  float suspensionFactor = *(float*)((int)this + 0x84);

  // Compute suspension offset based on compression and a global constant
  float baseOffset = suspensionFactor * suspensionCompression + _DAT_01126040;

  // Compute a scaled difference between steerAngle and compression
  float scaledDiff = (steerAngle - suspensionCompression) * suspensionFactor;
  if (scaledDiff <= baseOffset) {
    scaledDiff = baseOffset + DAT_00e2e780; // some minimal length adjustment
  }

  // The suspension force/direction vector multiplied by scaledDiff
  // This seems to rotate the suspension vector by the chassis orientation quaternion
  float suspensionVector[4];
  suspensionVector[0] = chassisOrientation[0] * scaledDiff; // x
  suspensionVector[1] = chassisOrientation[1] * scaledDiff; // y
  suspensionVector[2] = chassisOrientation[2] * scaledDiff; // z
  suspensionVector[3] = chassisOrientation[3] * scaledDiff; // w

  // Similarly, compute a base direction vector multiplied by baseOffset
  float baseVector[4];
  baseVector[0] = chassisOrientation[0] * baseOffset;
  baseVector[1] = chassisOrientation[1] * baseOffset;
  baseVector[2] = chassisOrientation[2] * baseOffset;
  baseVector[3] = chassisOrientation[3] * baseOffset;

  // Use thread-local storage for memory allocation
  TlsGetValue(DAT_01139810);

  // Allocate a temporary transform structure (64 bytes)
  int tempTransform = Memory::allocate(64, 0x27);
  *(short*)(tempTransform + 4) = 64; // store size

  // Build a transformation matrix/transform from the two vectors and wheel radius
  int transformHandle = FUN_00a65bb0(&suspensionVector, &baseVector, wheelRadius * suspensionCompression);

  // Allocate the actual wheel attachment object (368 bytes)
  int* wheelAttachment = (int*)Memory::allocate(0x170, 0x31);
  *(short*)(wheelAttachment + 1) = 0x170; // store size

  // Copy transform data from the temporary structure into the global transform pool
  FUN_009f0c70(transformHandle, &DAT_011397d0, parentObject);

  // Set the vtable pointer
  *wheelAttachment = (int)&PTR_FUN_00e39ec0;

  // Store the wheel ID and the parent vehicle
  wheelAttachment[0x58] = (int)wheelId;
  wheelAttachment[0x59] = (int)this;

  // Initialize some game-specific state
  FUN_0043b490();

  // Send a notification (event code 0x2001) about the wheel creation
  FUN_009f01f0(0x2001, wheelId, 0);

  return (undefined4*)wheelAttachment;
}