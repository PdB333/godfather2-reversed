// FUNC_NAME: StateAllocator::allocAndInit
// Allocation and initialization of a 24-byte state object with default values.
// +0x04: pointer to allocation function (double indirection in binary)
// +0x08: optional fallback buffer pointer (null for heap allocation)
struct State {
    int32_t field_0;   // +0x00
    int32_t field_4;   // +0x04
    int32_t field_8;   // +0x08
    uint8_t pad[8];    // +0x0C - +0x13
    uint8_t activeFlag;  // +0x14  (set to 1)
    uint8_t pendingFlag; // +0x15  (set to 0)
};

class StateAllocator {
public:
    // Allocation function: (this+4) -> pointer to function void* (*)(size_t, void*)
    void* (__cdecl *allocFunc)(size_t size, void* fallback); // simplified – binary uses double indirection
    void* fallbackBuffer;  // +0x08

    void __fastcall allocAndInit();
};

void __fastcall StateAllocator::allocAndInit() {
    void* buf = fallbackBuffer;
    uint32_t stackBuf[3] = {0, 0, 0}; // 12-byte fallback (heap alloc will actually take over)
    if (buf == nullptr) {
        buf = stackBuf;
    }
    // Call allocator (size 0x18 = 24 bytes)
    void* ptr = allocFunc(0x18, buf);
    State* state = (State*)ptr;
    if (state) {
        state->field_0 = 0;
        state->field_4 = 0;
        state->field_8 = 0;
        state->activeFlag  = 1;  // offset 0x14
        state->pendingFlag = 0;  // offset 0x15
    }
}