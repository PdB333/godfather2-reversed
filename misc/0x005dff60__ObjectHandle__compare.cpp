// FUNC_NAME: ObjectHandle::compare
int ObjectHandle::compare(const ObjectHandle& a, const ObjectHandle& b) {
    // First field: pointer to class descriptor or vtable (non-zero)
    // Second field: unique ID
    if (a.classPtr == nullptr || a.classPtr != b.classPtr) {
        // Assertion failure: types must match
        FUN_00b97aea(); // likely __assert or error handler
    }
    // Return value: high 3 bytes of a.id, low byte = (a.id == b.id)
    return (a.id & 0xFFFFFF00) | (a.id == b.id);
}