// FUNC_NAME: BaseObject::~BaseObject
BaseObject::~BaseObject() {
    if (this != nullptr) {
        // Internal cleanup routine (FUN_005683c0)
        cleanupInternal();
    }
}