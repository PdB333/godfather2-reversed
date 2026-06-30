// FUN_0044bb90: ResourceStream::initialize
#include <cstdint>

// Global state: active stream stack (for recursion tracking)
static int32_t g_streamCounter = 0;                     // DAT_0120547c
static void* g_streamStack[256];                         // DAT_01163ffc (arbitrary size)

// External declarations (prototypes for callees)
void __thiscall baseClassConstructor(void* thisObj, uint32_t param2);  // FUN_004a7560
void* __fastcall getGlobalResourceManager();             // FUN_004a37d0
bool __thiscall allocateStreamHandle(void* thisObj);     // FUN_0044b8b0
uint32_t __fastcall createResourceStream(void* handler, uint32_t resourceId, uint32_t param3); // FUN_004a3da0

class ResourceStream {
public:
    // Vtable pointer at offset 0x00
    void** vtable_ptr;  // PTR_FUN_00e31440

    // Some data pointer at offset 0x04
    void* data_ptr;     // PTR_LAB_00e314c8

    // Stream handle at offset 0x14 (from this + 0x14) -- actually unaff_ESI[5] sets streamHandle
    uint32_t streamHandle; // +0x14

    // Constructor (or initializer) called when attaching to a package
    // param2: base class argument (e.g., type)
    // param3: additional resource identifier 
    // param4: optional existing package pointer (if 0, retrieved from global manager)
    void __thiscall initialize(uint32_t param2, uint32_t param3, void* param4) {
        // Call base class constructor (likely sets up vtable at offset 0, etc.)
        baseClassConstructor(this, param2);

        // Set vtable pointer and data pointer
        this->vtable_ptr = &PTR_FUN_00e31440;   // *unaff_ESI = &PTR_FUN_00e31440;
        this->data_ptr = &PTR_LAB_00e314c8;     // unaff_ESI[4] = &PTR_LAB_00e314c8;

        // Initialize stream handle to 0
        this->streamHandle = 0;                 // unaff_ESI[5] = 0;

        // If no package provided, retrieve from global resource manager
        if (param4 == nullptr) {
            void* mgr = getGlobalResourceManager();
            if (mgr == nullptr) return;
            param4 = *(void**)((uint8_t*)mgr + 0x1c); // +0x1c -> package pointer?
            if (param4 == nullptr) return;
        }

        // Get resource identifier from package
        uint32_t resourceId = *(uint32_t*)((uint8_t*)param4 + 0x14);
        if (resourceId != 0) {
            // Push this onto global stack (for recursion management)
            g_streamCounter++;
            g_streamStack[g_streamCounter] = this;

            // Try to allocate a stream handle
            if (allocateStreamHandle(this)) {
                // Create actual stream resource
                uint32_t handle = createResourceStream(this, resourceId, param3);
                g_streamCounter--;
                this->streamHandle = handle;
            } else {
                g_streamCounter--;
                this->streamHandle = 0;
            }
        }
        // else: resourceId == 0 -> nothing to do
    }
};