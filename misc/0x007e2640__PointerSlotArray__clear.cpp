// FUNC_NAME: PointerSlotArray::clear
// Address: 0x007e2640
// Clears a container of 8-byte resource slots by iterating backward and calling a destructor on each valid slot,
// then freeing the slot array memory.

struct PointerSlotArray {
    void* slots;  // +0x00: raw pointer to slot array (each slot 8 bytes; first 4 bytes = non-zero if valid)
    int count;    // +0x04: number of slots in the array
};

// Forward declarations of callees (not implemented here)
void __fastcall destroySlot(void* slot);  // at 0x004daf90 – destroys the resource at the given 8-byte slot
void __fastcall freeMemory(void* ptr);    // at 0x009c8f10 – frees the slot array memory

void __fastcall PointerSlotArray::clear(PointerSlotArray* this) {
    int i = this->count;
    while (--i >= 0) {
        // Each slot is 8 bytes; the first int is the resource handle/pointer
        void* slot = static_cast<char*>(this->slots) + i * 8;
        if (*static_cast<int*>(slot) != 0) {
            destroySlot(slot);
        }
    }
    if (this->slots != nullptr) {
        freeMemory(this->slots);
        this->slots = nullptr;
    }
}