// FUNC_NAME: Entity::setCameraTarget
void __thiscall Entity::setCameraTarget(int thisPtr, int newTarget, undefined4 cameraFlags)
{
  // +0x174: current camera target entity pointer (?)
  // +0x178: camera target related flags
  if ((*(int *)(thisPtr + 0x174) == 0) != (newTarget == 0)) {
    *(int *)(thisPtr + 0x174) = newTarget;
    *(undefined4 *)(thisPtr + 0x178) = cameraFlags;
    // Presumably updates camera state or triggers camera system recalculation
    Entity::updateCameraTarget();
  }
  return;
}