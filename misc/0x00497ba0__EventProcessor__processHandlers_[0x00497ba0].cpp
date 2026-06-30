// FUNC_NAME: EventProcessor::processHandlers [0x00497ba0]
// Iterates over an internal array of (handler pointer, userData) pairs
// and invokes the virtual method at vtable+0x34 on each handler.
// The invoked method receives a context struct containing a global engine singleton,
// the userData, and the event parameter passed to this function.

class EventProcessor {
public:
    // +0x00: pointer to array of HandlerEntry structs (each 8 bytes)
    HandlerEntry* m_pHandlers;
    // +0x04: number of entries in the array
    int m_handlerCount;

    // __thiscall: this in ECX (but register EDI is used in this build)
    void __thiscall processHandlers(int eventParam) {
        // Get array base pointer
        HandlerEntry* entry = m_pHandlers;
        // If count is zero, skip
        if (entry != entry + m_handlerCount * 2) { // effectively: if (m_handlerCount != 0)
            do {
                // Build the context structure on the stack
                // Context layout: { void* pEngineSingleton; int userData; int eventParam; }
                struct HandlerContext {
                    void* pGlobal;   // First field: pointer to engine singleton (PTR_LAB_00e35014)
                    int userData;    // Second field: userData from current entry
                    int eventParam;  // Third field: the event parameter (param_1)
                } ctx;
                ctx.pGlobal = (void*)&PTR_LAB_00e35014; // Global engine singleton pointer
                ctx.userData = entry->userData;          // puVar1[1]
                ctx.eventParam = eventParam;             // local_4

                // Call virtual method at offset 0x34 on the handler object
                // entry->pHandler points to an object with a vtable pointer
                void* handlerObj = entry->pHandler;           // *puVar1
                int* vtable = *(int**)handlerObj;             // First DWORD is vtable pointer
                void (*handlerFunc)(HandlerContext*) = (void (*)(HandlerContext*))vtable[0x34 / 4];
                handlerFunc(&ctx);                            // Call with address of context

                // Move to next entry (each entry is 8 bytes: two DWORDs)
                entry++; // increment by 1 (which is +4 bytes in pointer arithmetic for HandlerEntry*)
                // Wait, entry is HandlerEntry*, but the original code increments puVar1 by 2 (since puVar1 was DWORD*)
                // So each HandlerEntry is 8 bytes; we need to handle that carefully.
                // Actually the decompiler shows puVar1 = puVar1 + 2, meaning moving 8 bytes.
                // Since entry is HandlerEntry*, incrementing by 1 moves by 8 bytes correctly.
                // But the loop condition uses pointer arithmetic in bytes: while(puVar1 != (DWORD*)(base + count*8))
                // We need to correctly iterate.
            } while (entry != (HandlerEntry*)((char*)m_pHandlers + m_handlerCount * 8));
        }
    }
};

// Note: The decompiler misrepresents the loop increment; the original binary moves puVar1 by 2 DWORDs (=8 bytes).
// The corrected version above uses HandlerEntry* with size 8, so entry++ moves correctly.
// The if-condition is simplified: since entry = m_pHandlers, entry + m_handlerCount*2 is actually m_pHandlers + m_handlerCount*2*sizeof(HandlerEntry), which is wrong.
// The original code compares puVar1 (which is DWORD*) to puVar1 + m_handlerCount*2, but that's essentially checking if count>0.
// We keep the intent: run loop if m_handlerCount>0.

// The struct HandlerEntry is defined as:
struct HandlerEntry {
    void* pHandler;  // +0x00: pointer to handler object
    int   userData;  // +0x04: associated user data
}; // size = 8

// Global engine singleton pointer (PTR_LAB_00e35014)
extern void* g_pEngineSingleton;

// The function call (void (*)(HandlerContext*))vtable[0x34/4] is interpreted as:
// handlerObj->vtable->someMethod(&ctx);