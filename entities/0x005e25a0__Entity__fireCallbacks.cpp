// FUNC_NAME: Entity::fireCallbacks
void Entity::fireCallbacks(int thisPtr, undefined4 param_2, undefined4 param_3)
{
  uint callbackCount;
  uint i;
  
  callbackCount = *(uint *)(thisPtr + 0x173c);
  if ((callbackCount != 0) && (i = 0, callbackCount != 0)) {
    do {
      // Call each registered callback function pointer from the callback array
      // Array is at +0x1738, each entry is 8 bytes: [callbackFunc, callbackParam]
      (**(code **)(*(int *)(thisPtr + 0x1738) + i * 8))
                (param_2,param_3,*(undefined4 *)(*(int *)(thisPtr + 0x1738) + 4 + i * 8));
      i = i + 1;
    } while (i < callbackCount);
  }
  return;
}