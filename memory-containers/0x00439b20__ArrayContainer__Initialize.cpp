// FUNC_NAME: ArrayContainer::Initialize

class ArrayContainer {
public:
    // Offsets relative to this:
    // +0x00: pointer to internal block (struct)
    // +0x04: int count (0)
    // +0x08: uint maxSize (param)
    // +0x0C: int someGlobal (DAT_00e35654)
    // +0x10: int anotherCounter (0)
    // +0x14: pointer to second array (allocated later)

    void Initialize(uint size) {
        // Store global value into field at +0x0C
        this->field_0C = DAT_00e35654;   // possibly a maximum or flag

        this->field_04 = 0;               // count
        this->field_08 = size;            // store size
        this->field_10 = 0;               // another counter

        // Allocate internal block (0x18 bytes)
        int* internalBlock = (int*)FUN_009c8e50(0x18);
        if (internalBlock != 0) {
            // Initialize internal block fields
            internalBlock[1] = 0;   // +0x04
            internalBlock[2] = 0;   // +0x08
            internalBlock[3] = 0;   // +0x0C
            internalBlock[4] = 0;   // +0x10

            // Allocate primary array: size+1 elements of 4 bytes
            uint allocSize = (size + 1) * 4;
            internalBlock[5] = (int)FUN_009c8e80(allocSize); // +0x14
        }

        // Store internal block pointer
        this->internalBlock = internalBlock;

        // Zero out the primary array
        uint i = 0;
        do {
            int* arrayPtr = (int*)this->internalBlock[5];
            arrayPtr[i] = 0;
            i++;
        } while (i <= size);

        // Allocate secondary array of same size and store at +0x14
        uint secAllocSize = (size + 1) * 4;
        this->field_14 = (int*)FUN_009c8e80(secAllocSize);
    }

private:
    // Assuming following struct layout (offsets from this):
    int* internalBlock;      // +0x00
    int field_04;            // +0x04
    uint field_08;           // +0x08
    int field_0C;            // +0x0C
    int field_10;            // +0x10
    int* field_14;           // +0x14
};