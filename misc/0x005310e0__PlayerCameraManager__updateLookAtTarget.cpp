// FUNC_NAME: PlayerCameraManager::updateLookAtTarget
void PlayerCameraManager::updateLookAtTarget(void)

{
  undefined4 in_XMM0_Da; // rotation quaternion or euler
  undefined4 in_XMM1_Da; // zoom distance or fov
  undefined1 local_20 [8]; // unused camera transform data
  undefined4 local_18;
  undefined4 local_14;
  
  // Global camera lookAt position/rotation buffer
  _DAT_01219a10 = in_XMM0_Da; // camera orientation quaternion
  _DAT_01219a14 = in_XMM1_Da; // camera distance/zoom
  
  // Check if current camera type is the default gameplay camera (DAT_01219940)
  // And if the camera's current target (DAT_01219954) matches the expected target ID (DAT_01219a48)
  // DAT_012058e8 likely holds a pointer to the active camera type struct
  if ((DAT_012058e8 == &DAT_01219940) && (DAT_01219954 == DAT_01219a48)) {
    local_18 = 0;
    local_14 = 0;
    // If the camera has a valid attachment node (DAT_01219a18 != 0),
    // update the camera matrix with the node's world transform
    if (DAT_01219a18 != 0) {
      // FUN_0060add0 likely transforms camera position/orientation from node local space
      // Arguments: target node pointer, attachment node pointer, output transform
      FUN_0060add0(DAT_01219954, DAT_01219a18, local_20);
    }
  }
  return;
}