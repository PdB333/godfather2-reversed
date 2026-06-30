// FUNC_NAME: SomeClass::registerEntityEventListeners
// Address: 0x006bed40
// This function registers event listeners for each non-null entity in a list.
// It appears to set up a callback structure with a vtable pointer (PTR_FUN_00d5dbbc)
// and a hash (0xc1e565d0) for a specific event, then registers it with the object
// pointed to by 'this' (at offset +0x3c).

#include <cstdint>

// Hypothetical descriptor for a list of entity pointers
struct EntityListDescriptor {
    void** items; // param_2[0]
    uint32_t count; // param_2[1]
};

// Hypothetical event functor structure (stack-allocated)
struct EventFunctor {
    uint32_t unknown0; // DAT_0112ad8c
    void** vtablePtr; // points to local variable that holds a pointer to PTR_FUN_00d5dbbc
    uint32_t eventHash; // 0xc1e565d0
    // ... other fields follow
};

// Forward declarations of unknown callees
extern int* __cdecl allocateSomeObject(); // FUN_00791300
extern void __cdecl registerEvent(EventFunctor* functor, void* target, uint32_t flags); // FUN_00408bf0
extern void __cdecl cleanupAllocation(int** alloc); // FUN_004daf90

// Global data
extern uint32_t DAT_0112ad8c;
extern uint32_t DAT_01205228;
extern void* PTR_FUN_00d5dbbc; // Vtable pointer for the functor

void __thiscall SomeClass::registerEntityEventListeners(EntityListDescriptor* list) {
    uint32_t idx = 0;

    if (list->count != 0) {
        do {
            void* entityPtr = list->items[idx];
            if (entityPtr != nullptr) {
                // First allocation – may be a node in a list
                int* alloc1 = allocateSomeObject();
                int* alloc2 = allocateSomeObject();

                // Build the functor on the stack
                EventFunctor functor;
                functor.unknown0 = DAT_0112ad8c;
                functor.vtablePtr = &PTR_FUN_00d5dbbc; // Actually local variable holding the address
                functor.eventHash = 0xc1e565d0; // Hash for a specific event (e.g., "OnDamage")

                // Offsets depend on struct layout; we show the raw operations
                int* adjustedAlloc2 = nullptr;
                if (alloc2 != nullptr) {
                    // +0x48 offset: possibly a link field within a larger structure
                    adjustedAlloc2 = (int*)((char*)alloc2 + 0x48);
                    // Insert into a linked list: store old next pointer, then set self as head
                    int oldNext = *(int*)((char*)adjustedAlloc2 + 4);
                    *(int**)((char*)adjustedAlloc2 + 4) = &adjustedAlloc2;
                    // Note: The above seems to be inserting an empty pointer? Possibly bug or intentional
                    // In the decompiled code, local_18 is assigned but not used elsewhere.
                }

                // Set other functor fields (mostly zeroed)
                functor.unknown1 = 0;
                functor.unknown2 = 0;
                functor.unknown3 = 0;
                // local_30 is the base of the functor; local_2c points to the vtable pointer
                // The stack layout is reconstructed according to local variables

                // Determine target: if 'this' is non-null, add offset 0x3c
                void* target = (this != nullptr) ? (char*)this + 0x3c : nullptr;

                // Register the functor with the target object
                registerEvent(&functor, target, 0);

                // Cleanup the second allocation (if any)
                if (adjustedAlloc2 != nullptr) {
                    cleanupAllocation(&adjustedAlloc2);
                }
            }
            idx++;
        } while (idx < list->count);
    }
}