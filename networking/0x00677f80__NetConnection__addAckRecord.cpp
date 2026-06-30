// FUNC_NAME: NetConnection::addAckRecord
// Function at 0x00677f80: Inserts a triple record (two shorts and a byte) into a dynamic array, resizing if necessary.
// The array stores per-slot data: an int at base, two shorts and a byte. Used for ACK/packet tracking in TNL networking.
// Member fields (offsets from this):
//   +0x00: pointer to external manager/owner
//   +0x04: ??? (unused here)
//   +0x08: capacity (int) [offset 0x02 in the decompiled code, since ints are 4 bytes)
//   +0x1C: count (short) [offset 0x0E]
//   +0x44: pointer to short array A (offset 0x11)
//   +0x48: pointer to short array B (offset 0x12)
//   +0x4C: pointer to byte array (offset 0x13)
//   +0x50: pointer to base of allocation block (offset 0x14)
//   +0x54: pointer to middle of block (offset 0x15, possibly another int array)
// Allocation uses a custom allocator (FUN_00672f60) with size = (newCapacity+4)*13 bytes.

void NetConnection::addAckRecord(unsigned short param1, unsigned short param2, unsigned char param3)
{
    int* basePtr;          // puVar1
    int* oldBase;          // unaff_EDI
    int capacity;          // iVar10
    short count;           // (short)this->count
    int newCapacity;       // iVar10 after computation
    int allocSize;         // iVar5
    int newBlock;          // iVar3
    int* newBase;          // 
    unsigned short* newShortA; // puVar4
    unsigned short* newShortB; // puVar1
    unsigned char* newByte;    // puVar6
    int oldShortA;         // iVar7
    int oldShortB;         // iVar9
    int oldByte;           // iVar8
    int copyCount;         // local_14
    int* ownerPtr;         // iVar10 (reused)

    oldBase = this;  // unaff_EDI
    capacity = oldBase[2]; // Offset +0x08 (since int array, index 2 is byte offset 8)
    count = (short)oldBase[0x0E / 4]; // offset 0x0E = index 0x0E >> 2 = 3? Wait: careful: in decompiled code, offsets are in bytes, but int array indexing multiplies by 4.
    // Actually in Ghidra, unaff_EDI is an int*, so unaff_EDI[2] means *(int*)((int)unaff_EDI + 8). So we need to stick to byte offsets.
    // We'll compute using pointer arithmetic with byte offsets.
    int* thisInt = reinterpret_cast<int*>(reinterpret_cast<char*>(oldBase));
    // Let's use a struct for clarity.
    struct AckData {
        int* owner;          // +0x00
        int unknown1;        // +0x04
        int capacity;        // +0x08
        // ... many fields, but we only need:
        short count;         // +0x0E (offset 14)
        int padding[?];
        unsigned short* shortA; // +0x44
        unsigned short* shortB; // +0x48
        unsigned char* byteA;   // +0x4C
        int* baseBlock;        // +0x50
        int* middleBlock;      // +0x54
        // etc.
    };
    AckData* self = (AckData*)oldBase;

    if (self->capacity <= (int)self->count) {
        int oldShortA_val = (int)self->shortA;
        int oldShortB_val = (int)self->shortB;
        int oldByte_val = (int)self->byteA;
        // Compute new capacity: old_cap + (old_cap>>1) + 0x20
        newCapacity = self->capacity + (self->capacity >> 1) + 0x20;
        allocSize = newCapacity + 4; // extra 4 slots
        // Allocate block: allocSize * 13 bytes
        newBlock = FUN_00672f60(allocSize * 13); // custom allocator
        self->baseBlock = (int*)newBlock;
        // middleBlock points to start + allocSize*4 (the second int array)
        self->middleBlock = (int*)(newBlock + allocSize * 4);
        // Set pointers for the three arrays after the two int arrays
        newShortA = (unsigned short*)((char*)self->middleBlock + allocSize * 4);
        newShortB = newShortA + allocSize;
        newByte = (unsigned char*)(newShortB + allocSize);
        self->shortA = newShortA;
        self->shortB = newShortB;
        self->byteA = newByte;
        self->capacity = newCapacity;

        copyCount = (int)self->count + 4; // copy count+4 elements? Actually copied from old count.
        // Actually the loop runs for (short)oldBase[0x0E] + 4 times (local_14 = (short)oldBase[0x0E] + 4)
        // This copies the old data into the new arrays.
        if (copyCount > 0) {
            int offsetShortA = oldShortA_val - (int)newShortA; // difference to adjust source
            int offsetShortB = oldShortB_val - (int)newShortA; // note: same base
            int offsetByte = oldByte_val - (int)newByte;       // difference for byte array
            // Actually the code uses:
            // iVar7 = oldShortA - (int)newShortA; (so negative likely)
            // iVar9 = oldShortB - (int)newShortA;
            // iVar10 = (int)newShortB - (int)newShortA;
            // iVar8 = oldByte - (int)newByte;
            // Then loop:
            // *newShortA = *(unsigned short*)(iVar7 + (int)newShortA);
            // *(unsigned short*)(iVar10 + (int)newShortA) = *(unsigned short*)((int)newShortA + iVar9);
            // *(unsigned char*)newByte = *(unsigned char*)(iVar8 + (int)newByte);
            // This is messy; we'll do a simpler copy.
            // Actually the decompiled code copies exactly the old data.
            unsigned short* srcShortA = self->shortA; // old pointer
            unsigned short* srcShortB = self->shortB;
            unsigned char* srcByte = self->byteA;
            for (int i = 0; i < copyCount; i++) {
                newShortA[i] = srcShortA[i];
                newShortB[i] = srcShortB[i];
                newByte[i] = srcByte[i];
            }
        }

        // Free old block if it existed and was replaced
        int owner = *(int*)self->owner;
        if (oldBase[0x14/4] == *(int*)(owner + 0x38)) { // check if old block is the same as some reference?
            *(int*)(owner + 0x70) = 1; // set flag
        }
        else if (oldBase[0x14/4] != 0) {
            // Free old block: pointer is at oldBase[0x14/4] (the baseBlock)
            // Actually the code: if (oldBase[0x14] == something) else if (oldBase[0x14] != 0) { free with -0x10 offset? }
            // It references oldBase[0x14] which is the old baseBlock.
            // The free call uses (*DAT_01206694)(oldBase[0x14] - 0x10);
            void (*freeFunc)(void*) = (void (*)(void*))DAT_01206694;
            freeFunc((void*)(oldBase[0x14/4] - 0x10)); // free with offset header
            // Also decrement reference count at owner+0x0c?
            *(int*)(*(int*)(owner + 0x0c) + *(int*)(oldBase[0x14/4] - 8) * 4) = 0;
            *(int*)(owner + 4) = *(int*)(owner + 4) - 1;
        }
    }

    // Insert new record at the current count position
    int insertIndex = (int)(short)self->count;
    self->shortA[insertIndex] = param1;
    self->shortB[insertIndex] = param2;
    self->byteA[insertIndex] = param3;
    self->count = (short)((int)self->count + 1);
}