// FUNC_NAME: EARSObject::isMarkedForDeletion
uint EARSObject::isMarkedForDeletion(uint param_1) // param_1 likely an object handle or index
{
    // Look up the object pointer using the handle/ID.
    // FUN_004025a0 is probably a handle resolver (getObjectByHandle).
    int* objPtr = (int*)FUN_004025a0(param_1); // returns 0 if invalid

    if (objPtr != 0) {
        // Check the sign bit (bit 31) of the DWORD at offset 0x60 from the object.
        // This bit likely indicates "marked for deletion" (highest bit in a flags field).
        return (*(uint*)(objPtr + 0x60 / 4) >> 31); // offset 0x60 = field at objPtr[0x18] in 4-byte units
    }
    // If object doesn't exist, treat it as marked for deletion.
    return 1;
}