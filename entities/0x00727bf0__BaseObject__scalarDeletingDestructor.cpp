// FUNC_NAME: BaseObject::scalarDeletingDestructor
// Address: 0x00727bf0
// Role: Scalar deleting destructor – releases internal resource if pointer stored at offset 0 is non-null, then optionally deallocates object memory.
int* __thiscall BaseObject::scalarDeletingDestructor(int* thisPtr, byte flags) {
    // Check if internal resource pointer is valid
    if (*thisPtr != 0) {
        releaseResource(thisPtr); // FUN_004daf90 – likely a destructor/release call
    }
    // If bit 0 of flags is set, deallocate the object memory
    if ((flags & 1) != 0) {
        operatorDelete(thisPtr); // FUN_009c8eb0 – free memory
    }
    return thisPtr;
}