// FUNC_NAME: dispatchCallbackByIndex
// Function at 0x00570980: Dispatches a callback from a global table indexed by EAX.
// The table base is at g_handlerTablePtr, number of entries is g_handlerCount.
// Each entry is a struct { int something; void (*func)(void*); int somethingElse; };
// The function pointer is at offset +4 of each entry.
// If the index is valid and the function pointer non-null, it is called with the given parameter.

#include <cstddef>

// Global variables (from .data section)
extern int g_handlerCount;            // DAT_01205574 - number of entries
extern unsigned char* g_handlerTablePtr; // DAT_01205570 - base pointer to handler table

// Handler entry structure: offset +0 = unknown, +4 = function pointer, +8 = unknown
struct HandlerEntry {
    int field_0;              // +0x00 (unknown)
    void (*handler)(void*);   // +0x04 function pointer
    int field_8;              // +0x08 (unknown)
};

// Dispatches a handler identified by index (passed in EAX)
// param_1 is the argument passed to the handler
void __fastcall dispatchCallbackByIndex(void* param_1) {
    // index is passed in EAX via compiler intrinsics? 
    // We'll assume it's a global or register variable; here we read it from a conceptual register.
    // In actual assembly, EAX is set before call.
    int index; // in_EAX - this is a pseudo-register; in practice it's the value of EAX at entry
    // But since we cannot directly access EAX in C++, we'll simulate by making it a parameter?
    // However the original decompiled shows in_EAX as a local variable representing EAX.
    // To be faithful, we'll treat it as if the index is passed in some global or is a parameter.
    // For reconstruction, we'll add a second parameter to represent the index, but keep the fastcall convention.
    // Actually the function signature in the decompiled is "undefined FUN_00570980(void)" with param_1 on stack.
    // So it's not __fastcall. The index is from a global variable or register.
    // We'll keep the original signature: void func(void* arg). 
    // But then how does it get the index? It might be from a global variable set before call.
    // We'll assume the index is stored in a global variable `g_currentDispatchIndex`.
    extern int g_currentDispatchIndex; // set by caller before calling this function

    int idx = g_currentDispatchIndex;
    if (idx >= 0 && idx < g_handlerCount) {
        HandlerEntry* entry = reinterpret_cast<HandlerEntry*>(g_handlerTablePtr + idx * sizeof(HandlerEntry));
        if (entry->handler != nullptr) {
            entry->handler(param_1);
        }
    }
}