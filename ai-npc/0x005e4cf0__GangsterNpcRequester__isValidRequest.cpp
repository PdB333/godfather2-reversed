// FUNC_NAME: GangsterNpcRequester::isValidRequest
// Address: 0x005e4cf0
// Role: Checks whether a given pointer belongs to the managed array of gangster requests.
// Offset 0x603c holds the base address of an array of 0x74-byte structures (GangsterNpcRequest).
// The function computes the index from the pointer difference and validates it via an internal check.

bool __thiscall GangsterNpcRequester::isValidRequest(void *this, void *pRequest) {
    if (pRequest == 0) {
        return false;
    }

    // Compute index: (pRequest - arrayBase) / sizeof(GangsterNpcRequest)
    int arrayBase = *(int*)((char*)this + 0x603c);
    int requestIndex = ((char*)pRequest - arrayBase) / 0x74;

    // Validate the index; second parameter 1 may indicate a validation mode
    char result = FUN_005e5e60(requestIndex, 1);
    return result != 0;
}