// FUNC_NAME: Entity::getComponentByHash
int* Entity::getComponentByHash(void* param_1) // param_1 is likely 'this' (entity pointer)
{
    int* componentPtr;
    char isReady;
    int objectComponent;
    int typeId;

    componentPtr = nullptr;

    // Acquire a lock or reference for the component type identified by hash 0x38523fc3
    acquireComponentLock(param_1, 0x38523fc3);
    setComponentAccessMode(1); // Set thread-safe access mode

    isReady = isComponentManagerReady();
    if (isReady == '\0') {
        // Component manager not ready, initialize it
        initializeComponentManager();
        componentPtr = getComponentManager();
        if (componentPtr != nullptr) {
            // Check if any of the first four component slots are occupied
            if (componentPtr[0] != 0) {
                return componentPtr;
            }
            if (componentPtr[1] != 0) {
                return componentPtr;
            }
            if (componentPtr[2] != 0) {
                return componentPtr;
            }
            if (componentPtr[3] != 0) {
                return componentPtr;
            }
        }
    }

    // Fallback: try to get the component directly from the object
    objectComponent = getComponentFromObject(param_1);
    if (objectComponent != 0) {
        // Check the type ID at offset 0x18 (vtable?) then offset 8
        typeId = *(int*)(*(int*)(objectComponent + 0x18) + 8);
        if (typeId == 0x1961bed || typeId == -0xc0deffc) {
            // Return pointer to component data at offset 0x1c
            return (int*)(objectComponent + 0x1c);
        }
    }

    return componentPtr;
}