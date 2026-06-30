// FUNC_NAME: someGlobalGetter
// Address: 0x00552250
// Role: Retrieves a status or error code from a subsystem indexed by 0x2006.
// Calls FUN_004af8c0 which likely returns a pointer to a manager or state object,
// then checks the first field for zero and returns it.

int getErrorStatus() {
    int localBuffer[2]; // used to hold output from manager query

    // Query manager with ID 0x2006 (possibly an error code or subsystem ID)
    queryManager(localBuffer, 0x2006);

    // Ensure the first field is non-zero; redundant but acts as safety
    if (localBuffer[0] == 0) {
        localBuffer[0] = 0;
    }

    return localBuffer[0];
}