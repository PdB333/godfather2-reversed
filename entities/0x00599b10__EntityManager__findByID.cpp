// FUNC_NAME: EntityManager::findByID
// Function at 0x00599b10: Searches for an object by its ID (offset +0x70) in a sparse array.
int EntityManager::findByID(int id)
{
  int count = *(char *)(this + 0x79); // Number of active indices
  if (count == 0) {
    return 0;
  }
  byte *indexArray = (byte *)(this + 0x7a); // Array of indices (0x7a)
  int *dataPtr = *(int **)(this + 0x1bc); // Pointer to internal data block
  int *typeArray = *(int **)(dataPtr + 0x24); // Array of type codes per slot
  int **objectArray = *(int ***)(dataPtr + 0x20); // Array of object pointers per slot

  for (int i = 0; i < count; ++i) {
    int idx = indexArray[i];
    int type = typeArray[idx];
    if (type != -2) {
      // Debug/log call when slot is not marked invalid (-2)
      (**(code **)(*DAT_01205590 + 4))();
    }
    int *obj = objectArray[idx];
    if (*(int *)(obj + 0x70) == id) { // Object ID field at offset +0x70
      return (int)obj;
    }
  }
  return 0;
}