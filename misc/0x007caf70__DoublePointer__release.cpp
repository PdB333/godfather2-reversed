// FUNC_NAME: DoublePointer::release
// Function address: 0x007caf70
// Releases two dynamically allocated pointer members at offsets +0x00 and +0x08

struct DoublePointer {
    void* ptr0; // +0x00
    void* ptr8; // +0x08
};

void __thiscall DoublePointer::release() {
    if (ptr8 != nullptr) {
        deallocate(ptr8); // FUN_004daf90 - custom deallocation
    }
    if (ptr0 != nullptr) {
        deallocate(ptr0); // FUN_004daf90 - custom deallocation
    }
}