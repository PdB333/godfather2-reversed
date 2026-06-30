// FUNC_NAME: copyVector3FromHandle
// Address: 0x00752aa0
// Copies a 12-byte Vector3 (3 floats) from a handle array if conditions are met.
// param1: out - pointer to destination Vector3
// param2/3: unused parameters (possibly part of calling convention or reserve)
// param4: handleEntry - pointer to an array of ints (size unknown), where [0] = valid flag, [2] = pointer to source Vector3
// param5: flag - pointer to an additional validity flag
bool copyVector3FromHandle(Vector3* out, int unused1, int unused2, int* handleEntry, int* flag) {
    bool success = false;
    if (*handleEntry != 0 && *flag != 0) {
        // handleEntry[2] is the pointer to the source Vector3 data
        Vector3* src = (Vector3*)handleEntry[2];
        *out = *src;
        success = true;
    }
    return success;
}