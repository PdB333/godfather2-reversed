// FUNC_NAME: forEachActiveObject
void forEachActiveObject(void (*callbackFunction)(void* object)) {
    // Iterate over an array of 128 objects (0x60 bytes each) starting at global pointer DAT_012053cc.
    // The array seems to be a pool of game objects or controllers.
    // Offset +0x40 is an active flag (int32).
    int objectIndex = 0;
    do {
        void* object = (char*)DAT_012053cc + objectIndex;
        if (*(int*)((char*)object + 0x40) != 0) {
            // If the object is active, call the callback with the object pointer.
            callbackFunction(object);
        }
        objectIndex += 0x60; // Advance to next object (size of each entry).
    } while (objectIndex < 0x3000); // 128 entries * 0x60 = 0x3000 total size.
}