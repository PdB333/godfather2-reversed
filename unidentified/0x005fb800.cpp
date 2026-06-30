// FUN_NAME: SimObject::compare // 0x005fb800 - Compares two objects by type and ID, returns combined sort key.
// This appears to be a base class method (likely SimObject or NetObject) that:
// - Asserts that the two objects have the same class type (first int field at +0x0)
// - Returns a 32-bit value combining the object's UID (high 24 bits of the ID at +0x4) 
//   with an inequality flag (low byte = 1 if IDs differ, else 0).
// The result is used for sorting/ordering in containers where type must match.

__declspec(naked) void assertFailed(const char* msg) {
    __asm { int 3 } // Placeholder for debug break
}

int __thiscall SimObject::compare(SimObject* thisObj, SimObject* otherObj) {
    // +0x00: typeHash (class type identifier)
    // +0x04: uniqueId (32-bit unique identifier for this instance)
    int typeThis = *(int*)thisObj;
    int typeOther = *(int*)otherObj;

    // Fail if type hash is invalid or does not match
    if ((typeThis == 0) || (typeThis != typeOther)) {
        assertFailed("SimObject::compare: type mismatch or null");
    }

    int idThis = *(int*)((char*)thisObj + 4);
    int idOther = *(int*)((char*)otherObj + 4);

    // Combine the upper 24 bits of this object's ID with a boolean indicating inequality (0/1)
    // This gives a 32-bit sort key suitable for ordered containers.
    int highPart = (idThis >> 8) & 0xFFFFFF;
    int lowPart = (idThis != idOther) ? 1 : 0;
    return (highPart << 8) | lowPart;
}