// FUNC_NAME: ContainerManager::destroyAllObjects
void __thiscall ContainerManager::destroyAllObjects(int this, int container) {
  uint i = 0;
  if (*(int *)(container + 0x104) != 0) { // container->objectCount
    int *objArray = (int *)(container + 4); // pointer to array of objects
    do {
      int sizeMinus1 = *(int *)(this + 0x1c) - 1; // size of listener list (0-based)
      int object = *objArray; // current object
      if (-1 < sizeMinus1) {
        // Call each registered listener callback (function pointer) with the object
        undefined4 **callbackArray = (undefined4 **)(this + 8 + sizeMinus1 * 4);
        do {
          (**(code **)(*(int *)*callbackArray + 4))(object); // listener->onObjectDestroyed?
          sizeMinus1--;
          callbackArray--;
        } while (-1 < sizeMinus1);
      }
      uint j = 0;
      *(undefined1 *)(object + 0x128) = 1; // mark object as destroyed
      if (*(int *)(object + 0x14c) != 0) { // object->subHandleCount
        undefined4 **handleArray = (undefined4 **)(object + 300); // +0x12c
        do {
          releaseHandle(*handleArray); // release each sub-handle
          j++;
          handleArray++;
        } while (j < *(uint *)(object + 0x14c));
      }
      *(undefined4 *)(object + 0x14c) = 0; // reset sub-handle count
      i++;
      objArray++;
    } while (i < *(uint *)(container + 0x104));
  }
  containerCleanup(container); // possibly clear container internal state
  globalCleanup();
  return;
}