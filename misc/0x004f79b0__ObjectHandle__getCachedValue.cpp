// FUNC_NAME: ObjectHandle::getCachedValue
// Address: 0x004f79b0
// Role: Checks if the handle (4 ints at offsets 0x0-0xC) is non-null (any nonzero), then obtains a global pointer, verifies it points to a valid resource, and returns a cached value from that resource using the handle's first int as an ID. Returns 0 if invalid.

int __thiscall ObjectHandle::getCachedValue(int param2, int param3) {
    int *pGlobal;
    int id;
    int result;

    // Check if the first 16 bytes of the handle are all zero (null/uninitialized).
    // This is a quick validity check: any nonzero field indicates a valid handle.
    if ((this->field0 != 0 || this->field4 != 0) || (this->field8 != 0 || this->fieldC != 0)) {
        pGlobal = (int *)FUN_004e0f60();  // Get pointer to global resource table (e.g., Singleton::getInstance())
        if ((pGlobal != (int *)0x0) && (id = *pGlobal, id != 0)) {
            FUN_0051d730();  // Enter critical section / lock (e.g., Mutex::lock)
            result = FUN_0051c7c0(id, param2, param3);  // Retrieve value from table using id and parameters
            return result;
        }
    }
    return 0;
}