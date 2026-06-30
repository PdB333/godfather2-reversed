// FUNC_NAME: GameObject::setEnabled
bool GameObject::setEnabled() {
    // Global lock/mutex at 0x0120e944
    int lockVar = gLockMutex;
    lockMutex(&lockVar, 0); // Likely acquires a critical section or mutex

    // Get object based on 'this' pointer (passed in ESI)
    GameObject* obj = (GameObject*)getObjectFromHandle(this);
    if (obj != nullptr) {
        // Set bit 0x100 in flags at offset 0x50 (known flag: e.g., kFlag_Enabled)
        obj->flags |= 0x100;
    }
    return true; // Always returns success
}