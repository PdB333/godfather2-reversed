// FUNC_NAME: EARS::Framework::NetSession::dispatchMessage
int NetSession::dispatchMessage(int thisPtr) {
    int result;
    int local_4 = 0;
    
    // Hash 0x383225a1 - likely a message type identifier
    char hasHash = (*(code **)(*(int *)thisPtr + 0x10))(0x383225a1, &local_4);
    if (hasHash != '\0') {
        // ESI is a pointer to some object (possibly a global or passed by caller)
        if (esiPtr != 0) {
            // Call a method on the ESI object at offset 0x7cc (vtable entry)
            result = (*(code **)(esiPtr[0x7cc] + 8))();
            return result;
        }
    }
    
    // Second hash check
    local_4 = 0;
    hasHash = (*(code **)(*(int *)thisPtr + 0x10))(0x197c1972, &local_4);
    if (hasHash != '\0') {
        if (esiPtr != 0) {
            // Call a method on this at offset 0x1e4 (likely a getter for an object)
            int *obj = (int *)(*(code **)(*(int *)esiPtr + 0x1e4))();
            if (obj != 0) {
                // Check third hash on the retrieved object
                hasHash = (*(code **)(*obj + 0x10))(0xd80c71d2, &stack0xfffffff4);
                if (hasHash != '\0') {
                    // Call a method on the object (or the original hash pointer?)
                    result = (*(code **)(*(int *)0x383225a1 + 8))();
                    return result;
                }
            }
        }
    }
    
    return -1; // 0xffffffff
}