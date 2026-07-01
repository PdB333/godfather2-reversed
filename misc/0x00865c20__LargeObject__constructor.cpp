// FUNC_NAME: LargeObject::constructor
// Function at 0x00865c20: Constructor for an object of size 0x11b0 (4528 bytes).
// Calls base initialization, then optionally performs a custom memory operation (e.g., zero-fill or placement new) if the flags byte has bit 0 set.
// Returns the constructed object pointer.

class LargeObject {
public:
    LargeObject* __thiscall constructor(byte flags);
private:
    void baseInit(); // Calls FUN_00864620
};

// Helper: custom memory operation (likely a memset or placement new variant)
void customMemoryOp(void* ptr, size_t size); // FUN_0043b960

LargeObject* __thiscall LargeObject::constructor(byte flags) {
    this->baseInit();
    if ((flags & 1) != 0) {
        customMemoryOp(this, 0x11b0); // Operates on entire object size
    }
    return this;
}