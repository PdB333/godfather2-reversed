// FUNC_NAME: DataBlock::transferHandle

#include <cstdint>

// Global sentinel value (null handle)
extern uint32_t kNullHandle; // DAT_00e2b1a4

// Structure representing a 16-byte data block with sentinel
struct DataBlock {
    uint32_t data0; // +0x00
    uint32_t data1; // +0x04
    uint32_t data2; // +0x08
    uint32_t data3; // +0x0C, sentinel (set to kNullHandle when empty)
};

// Forward declarations of internal engine functions
void FUN_0056d810();
void FUN_0056d370(int32_t, int32_t, int32_t, DataBlock* dest);
void FUN_0056d370(int32_t, int32_t, int32_t);

// __thiscall member function: transfers or initializes a DataBlock
void __thiscall DataBlock::transferHandle(DataBlock* dest, uint32_t flags) {
    // Check bits 3-5 of flags (mask 0x38)
    if ((flags & 0x38) == 0) {
        // Init: clear destination block and set sentinel
        dest->data0 = 0;
        dest->data1 = 0;
        dest->data2 = 0;
        dest->data3 = kNullHandle;
        return;
    }
    if ((flags & 0x38) == 0x38) {
        // Move: copy this block to destination, then clear this block
        dest->data0 = this->data0;
        dest->data1 = this->data1;
        dest->data2 = this->data2;
        dest->data3 = this->data3;
        this->data0 = 0;
        this->data1 = 0;
        this->data2 = 0;
        this->data3 = kNullHandle;
        return;
    }
    // Unsupported flag combination: handle error via internal functions
    FUN_0056d810();
    FUN_0056d370(0, 0, 0, dest);
    FUN_0056d370(0, 0, 0);
}