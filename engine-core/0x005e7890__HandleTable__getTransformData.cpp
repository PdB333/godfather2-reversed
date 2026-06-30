// FUNC_NAME: HandleTable::getTransformData
// Address: 0x005e7890
// Retrieves a 16-byte transform (4 floats) from an internal handle table.
// The handle is a 32-bit value where the low byte is the index and the high 24 bits are a fixed pattern (0xad1031)
// The check validates that the handle decodes to a valid index within the table count.

bool __thiscall HandleTable::getTransformData(uint handle, float* outTransform) const {
    byte count = *(byte*)(this + 0x1c);                 // Count of valid entries
    if (((handle ^ 0xad103100) < count) && (count != 0) && ((byte)handle < count)) {
        // Array of pointers to transform data objects starts at this+4.
        int* entry = *(int**)(this + 4 + ((byte)handle) * 4);
        if (entry != 0) {
            // Transform data stored at offsets 0x50-0x5c (4 floats, e.g., quaternion or position+padding)
            outTransform[0] = *(float*)((char*)entry + 0x50);
            outTransform[1] = *(float*)((char*)entry + 0x54);
            outTransform[2] = *(float*)((char*)entry + 0x58);
            outTransform[3] = *(float*)((char*)entry + 0x5c);
            return true;
        }
    }
    return false;
}