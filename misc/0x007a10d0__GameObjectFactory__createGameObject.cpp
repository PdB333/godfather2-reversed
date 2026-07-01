// FUNC_NAME: GameObjectFactory::createGameObject
void __fastcall GameObjectFactory::createGameObject(void* context) {
    char isActive;
    int allocatedObj;
    int constructedObj;
    undefined4* srcPtr;
    undefined4* dstPtr;
    int copyCount;

    isActive = g_isGameActive(); // Check if game is active
    if (isActive != '\0') {
        allocatedObj = allocateMemory(0x2f8); // Allocate 760 bytes for object
        if (allocatedObj == 0) {
            allocatedObj = 0;
        } else {
            constructedObj = constructObject(context); // Initialize object with context
        }
        // Copy 0xB0 dwords (0x2C0 bytes) from stack (implicit struct) to object + 0x38
        srcPtr = (undefined4*)&stack0x00000004; // Stack source (struct passed by value)
        dstPtr = (undefined4*)(constructedObj + 0x38);
        for (copyCount = 0xb0; copyCount != 0; copyCount = copyCount + -1) {
            *dstPtr = *srcPtr;
            srcPtr = srcPtr + 1;
            dstPtr = dstPtr + 1;
        }
        registerObject(constructedObj); // Register the object
    }
    return;
}