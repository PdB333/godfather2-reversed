// FUNC_NAME: ObjectFactory::spawnObject
void __thiscall ObjectFactory::spawnObject() {
    // Check if the game is active and accepting new objects
    if (!isGameActive()) {
        return;
    }

    // Allocate a new object block (size 0x38 = 56 bytes, typical for base game object)
    void* newObject = allocateMemory(0x38);
    if (newObject != nullptr) {
        // Construct the object, passing this factory as the owner/context
        void* object = constructObject(this, newObject); // +0x00: this is the factory, newObject is the memory
        // Register the newly constructed object into the game world
        registerObject(object);
    } else {
        // Allocation failure – report null registration (likely error handling)
        registerObject(nullptr);
    }
}