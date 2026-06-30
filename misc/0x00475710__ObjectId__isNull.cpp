// FUNC_NAME: ObjectId::isNull
// Address: 0x00475710
// Checks if a 16-byte object ID (4 int32 fields) is all zero (null).
// Returns 1 if null, 0 otherwise.
// Used in networking code for EARS engine.
bool ObjectId::isNull() const {
    // +0x00: data[0]
    // +0x04: data[1]
    // +0x08: data[2]
    // +0x0C: data[3]
    if (data[0] == 0 && data[1] == 0 &&
        data[2] == 0 && data[3] == 0) {
        return true;
    }
    return false;
}