// FUNC_NAME: SceneNode::getTransformHandle
int __fastcall SceneNode::getTransformHandle(int *thisPtr)
{
  undefined4 *transformDataPtr;
  int result;
  undefined4 localTransform[4]; // 16 bytes: likely a quaternion or 4-float vector
  
  transformDataPtr = (undefined4 *)thisPtr[1]; // +0x04: transform data pointer
  if ((transformDataPtr != (undefined4 *)0x0) && (thisPtr[0] != 0) && (*(char *)(thisPtr[0] + 6) == '\x04')) {
    // Copy 16 bytes of transform data (e.g., position or quaternion)
    localTransform[0] = *transformDataPtr;
    localTransform[1] = transformDataPtr[1];
    localTransform[2] = transformDataPtr[2];
    localTransform[3] = transformDataPtr[3];
    result = resolveTransformToHandle(localTransform, 0);
    if (result != 0) {
      return result;
    }
  }
  return 0;
}