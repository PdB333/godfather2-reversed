// FUNC_NAME: ObjectManager::getOrCreateObject
undefined4 * __thiscall ObjectManager::getOrCreateObject(int thisPtr, int objectID)
{
  int index;
  undefined4 *result;

  if (objectID != 0) {
    index = getIndexFromID(objectID);  // FUN_00849a70
    if ((index >= 0) && (*(int *)(*(int *)(thisPtr + 0x10) + index * 4) != 0)) {
      result = (undefined4 *)createObject();  // FUN_00849530
      return result;
    }
  }
  return &nullObject;  // DAT_01218244
}