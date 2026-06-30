// FUNC_NAME: DataNode::assign
// Function address: 0x006e03b0
// Role: Deep copy assignment for a data node in a doubly-linked list structure.
// Copies all data fields from source node, handles external data pointer replacement,
// and updates back-pointer in the external data object.
// Structure layout (int* offsets, each 4 bytes):
//   +0x00: pExternalData (int*) - pointer to externally managed data object
//   +0x04: oldBackPointer (int) - temporary storage for the old back-pointer from external data
//   +0x08: char field1
//   +0x09 to +0x0B: padding? (then 8-byte aligned? but code copies char at +0x08 as byte)
//   Int fields continue up to +0x25 (0x94 bytes from start? actually +0x25 is offset 0x94)
//   Then 8-byte fields at +0x26, +0x28, +0x2A, +0x2C, +0x2E (0x98, 0xA0, 0xA8, 0xB0, 0xB8 byte offsets)
//   Total size approximately 0xC0 bytes (192 bytes)

int* __thiscall DataNode::assign(int* thisPtr, int* source)
{
    int savedData;

    // Self-assignment guard
    if (thisPtr == source) {
        return thisPtr;
    }

    savedData = *source; // source->pExternalData

    // If our current data pointer differs, release old data and acquire new with back-pointer fix
    if (*thisPtr != savedData) {
        if (*thisPtr != 0) {
            // Release old external data (likely decrement refcount or unlink)
            DataNode::releaseData(thisPtr);
        }
        *thisPtr = savedData;
        if (savedData != 0) {
            // Save the old back-pointer from the external data object into our temporary field
            thisPtr[1] = *(int*)(savedData + 4); // +0x04 of external data holds back-pointer to owner node
            // Update external data's back-pointer to point to this node
            *(int**)(savedData + 4) = thisPtr;
        }
    }

    // Copy all remaining fields from source to this node
    // +0x08 byte
    *(char*)(thisPtr + 2) = (char)source[2];
    // +0x0C eight bytes (two ints)
    *(int64*)(thisPtr + 3) = *(int64*)(source + 3);
    // +0x14 int
    thisPtr[5] = source[5];
    // +0x18 byte
    *(char*)(thisPtr + 6) = (char)source[6];
    // +0x1C int
    thisPtr[7] = source[7];
    // +0x20 int
    thisPtr[8] = source[8];
    // +0x24 int
    thisPtr[9] = source[9];
    // +0x28 int
    thisPtr[10] = source[10];
    // +0x2C int
    thisPtr[11] = source[11];
    // +0x30 int
    thisPtr[12] = source[12];
    // +0x34 int
    thisPtr[13] = source[13];
    // +0x38 int
    thisPtr[14] = source[14];
    // +0x3C int
    thisPtr[15] = source[15];
    // +0x40 int
    thisPtr[16] = source[16];
    // +0x44 int
    thisPtr[17] = source[17];
    // +0x48 int
    thisPtr[18] = source[18];
    // +0x4C int
    thisPtr[19] = source[19];
    // +0x50 int
    thisPtr[20] = source[20];
    // +0x54 int
    thisPtr[21] = source[21];
    // +0x58 int
    thisPtr[22] = source[22];
    // +0x5C int
    thisPtr[23] = source[23];
    // +0x60 int
    thisPtr[24] = source[24];
    // +0x64 int
    thisPtr[25] = source[25];
    // +0x68 int
    thisPtr[26] = source[26];
    // +0x6C int
    thisPtr[27] = source[27];
    // +0x70 int
    thisPtr[28] = source[28];
    // +0x74 int
    thisPtr[29] = source[29];
    // +0x78 int
    thisPtr[30] = source[30];
    // +0x7C int
    thisPtr[31] = source[31];
    // +0x80 int
    thisPtr[32] = source[32];
    // +0x84 int
    thisPtr[33] = source[33];
    // +0x88 int
    thisPtr[34] = source[34];
    // +0x8C int
    thisPtr[35] = source[35];
    // +0x90 int
    thisPtr[36] = source[36];
    // +0x94 int
    thisPtr[37] = source[37];
    // +0x98 int64 (8 bytes)
    *(int64*)(thisPtr + 38) = *(int64*)(source + 38); // +0x26 offset (0x98 bytes)
    // +0xA0 int64
    *(int64*)(thisPtr + 40) = *(int64*)(source + 40); // +0x28 offset
    // +0xA8 int64
    *(int64*)(thisPtr + 42) = *(int64*)(source + 42); // +0x2A offset
    // +0xB0 int64
    *(int64*)(thisPtr + 44) = *(int64*)(source + 44); // +0x2C offset
    // +0xB8 int64
    *(int64*)(thisPtr + 46) = *(int64*)(source + 46); // +0x2E offset

    return thisPtr;
}