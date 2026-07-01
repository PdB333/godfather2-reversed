// FUNC_NAME: getResourceHandle
// Function at 0x007faa70 - Retrieves a resource handle from an object if it has a valid flag at offset +0x10.
// The constant 0x2002 likely corresponds to a resource type or request ID.
int getResourceHandle(void* pObject) {
    int result = 0;
    // Check if object is non-null and the byte at offset +0x10 is non-zero (indicating resource present)
    if (pObject != nullptr && *(char*)(pObject + 0x10) != 0) {
        int handle[2]; // buffer for resource handle (only first element used)
        // Call to resource retrieval function (FUN_004af8c0) with type 0x2002
        FUN_004af8c0(handle, 0x2002);
        result = 0;
        if (handle[0] != 0) {
            result = handle[0];
        }
    }
    return result;
}