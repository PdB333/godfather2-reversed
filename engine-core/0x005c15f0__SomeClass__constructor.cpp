// FUNC_NAME: SomeClass::constructor
// Address: 0x005c15f0
// Role: Constructor for SomeClass, initializes base class and sets vtable

// Assumed class hierarchy: SomeClass : BaseClass
// Vtable pointers: PTR_FUN_00e3e78c (base), PTR_LAB_00e3e74c (derived)

#include <cstdint>

// Forward declarations
extern void* PTR_FUN_00e3e78c; // base vtable
extern void* PTR_LAB_00e3e74c; // derived vtable
extern uint32_t DAT_012234ec;   // global pointer to memory manager vtable

// Function prototypes
void FUN_005c0360();            // base class constructor/init
int  FUN_005c43d0(void* thisPtr); // placement init, returns 0 on failure

// Memory manager deallocation function type
typedef void (*DeallocFunc)(void* ptr, int flags);

class SomeClass {
public:
    // Constructor with flags (bit 0 = allocate/init)
    void* constructor(uint8_t flags) {
        // Set base vtable
        *(void**)this = &PTR_FUN_00e3e78c;

        // Call base class constructor
        FUN_005c0360();

        // Initialize fields at offsets +0x08 and +0x0C
        *(uint32_t*)((uint8_t*)this + 0x0C) = 0; // param_1[3]
        *(uint32_t*)((uint8_t*)this + 0x08) = 0; // param_1[2]

        // If pointer at offset +0x04 is non-null, release it
        if (*(void**)((uint8_t*)this + 0x04) != nullptr) {
            // Call deallocation function from memory manager vtable
            DeallocFunc dealloc = *(DeallocFunc*)(*(uint32_t*)(DAT_012234ec + 4) + 4);
            dealloc(*(void**)((uint8_t*)this + 0x04), 0);
        }

        // Clear pointer at offset +0x04
        *(void**)((uint8_t*)this + 0x04) = nullptr;

        // Set derived vtable
        *(void**)this = &PTR_LAB_00e3e74c;

        // If flags has bit 0 set, attempt to initialize further
        if (flags & 1) {
            int result = FUN_005c43d0(this);
            if (result == 0) {
                // On failure, deallocate this object
                DeallocFunc dealloc = *(DeallocFunc*)(*(uint32_t*)(DAT_012234ec + 4) + 4);
                dealloc(this, 0);
            }
        }

        return this;
    }
};