// FUNC_NAME: Sentient::~Sentient

#include <cstdint>

// Forward declarations of helper functions (from other modules)
extern void FUN_007d9de0();
extern void FUN_00424df0(uint32_t handle, int32_t size, int32_t, int32_t, int32_t, int32_t);
extern void FUN_00424ee0(uint32_t handle, uint32_t ptr);
extern void FUN_004daf90(void** ptrPtr);
extern void FUN_0080ea60();

// Class layout: offset constants
static constexpr int32_t kOffsFlags = 0xC4;      // param_1[0x31]
static constexpr int32_t kOffsCompPtr1 = 0x58;   // param_1[0x16] – component with vtable
static constexpr int32_t kOffsSubObj1 = 0xA0;    // param_1[0x28]
static constexpr int32_t kOffsSubObj2 = 0x88;    // param_1[0x22]
static constexpr int32_t kOffsSubObj3 = 0x80;    // param_1[0x20]
static constexpr int32_t kOffsSubObj4 = 0x78;    // param_1[0x1e]
static constexpr int32_t kOffsSubObj5 = 0xA8;    // param_1[0x2a]
static constexpr int32_t kOffsSubObj6 = 0xB8;    // param_1[0x2e]
static constexpr int32_t kOffsSubObj7 = 0xB0;    // param_1[0x2c]
static constexpr int32_t kOffsSubObj8 = 0x98;    // param_1[0x26]
static constexpr int32_t kOffsSubObj9 = 0x90;    // param_1[0x24]

void __thiscall Sentient::~Sentient(void* thisPtr)
{
    uint32_t* this_ = static_cast<uint32_t*>(thisPtr);
    uint32_t flags = this_[0x31]; // offset 0xC4

    // Set vtable to destructor-level vtable
    this_[0] = 0x00d6f3cc; // PTR_LAB_00d6f3cc

    if ((flags >> 2) & 1) {
        // Bit 2 set: destroy sub-component
        FUN_007d9de0();
    }

    if ((flags >> 1) & 1) {
        // Bit 1 set: call virtual function at offset 0x304 in component at +0x58
        uint32_t comp = this_[0x16]; // offset 0x58
        if (comp) {
            (**(void (__thiscall**)(int32_t))(*(uint32_t*)comp + 0x304))();
        }
    }

    // --- Cleanup sub-objects ---

    // Sub-object at +0xA0 (param_1[0x28])
    if (this_[0x28] != 0 && this_[0x28] != 0x48) {
        int32_t adjustedSize = (this_[0x28] == 0) ? 0 : this_[0x28] - 0x48;
        uint32_t handle = *(uint32_t*)(0x2494 + this_[0x16]);
        FUN_00424df0(handle, adjustedSize, 0, 1, 0, 0);

        void* subObj = reinterpret_cast<void*>(this_[0x28] - 0x48);
        if (subObj) {
            (*(void(__thiscall**)(void*, int32_t))subObj)(1); // destructor with arg 1
        }
        if (this_[0x28]) {
            FUN_004daf90(&this_[0x28]);
            this_[0x28] = 0;
        }
    }

    // Sub-object at +0x88 (param_1[0x22])
    if (this_[0x22] != 0 && this_[0x22] != 0x48) {
        int32_t adjustedSize = (this_[0x22] == 0) ? 0 : this_[0x22] - 0x48;
        uint32_t handle = *(uint32_t*)(0x2494 + this_[0x16]);
        FUN_00424df0(handle, adjustedSize, 0, 1, 0, 0);
    }

    // Sub-object at +0x80 (param_1[0x20])
    if (this_[0x20] != 0) {
        uint32_t handle = *(uint32_t*)(0x2494 + this_[0x16]);
        FUN_00424ee0(handle, this_[0x20]);

        void* subObj = reinterpret_cast<void*>(this_[0x20]);
        if (subObj) {
            (*(void(__thiscall**)(void*, int32_t))subObj)(1);
        }
        if (this_[0x20]) {
            FUN_004daf90(&this_[0x20]);
            this_[0x20] = 0;
        }
    }

    // Sub-object at +0x78 (param_1[0x1e])
    if (this_[0x1e] != 0 && this_[0x1e] != 0x48) {
        int32_t adjustedSize = (this_[0x1e] == 0) ? 0 : this_[0x1e] - 0x48;
        uint32_t handle = *(uint32_t*)(0x2494 + this_[0x16]);
        FUN_00424df0(handle, adjustedSize, 0, 1, 0, 0);

        // Additional condition: only call destructor if flag bit 0 is set
        if ((this_[0x31] & 1) && this_[0x1e] != 0) {
            void* subObj = reinterpret_cast<void*>(this_[0x1e] - 0x48);
            if (subObj) {
                (*(void(__thiscall**)(void*, int32_t))subObj)(1);
            }
        }
        if (this_[0x1e]) {
            FUN_004daf90(&this_[0x1e]);
            this_[0x1e] = 0;
        }
    }

    // Sub-object at +0xA8 (param_1[0x2a])
    if (this_[0x2a] != 0 && this_[0x2a] != 0x48) {
        int32_t adjustedSize = (this_[0x2a] == 0) ? 0 : this_[0x2a] - 0x48;
        uint32_t handle = *(uint32_t*)(0x2494 + this_[0x16]);
        FUN_00424df0(handle, adjustedSize, 0, 1, 0, 0);

        void* subObj = reinterpret_cast<void*>(this_[0x2a] - 0x48);
        if (subObj) {
            (*(void(__thiscall**)(void*, int32_t))subObj)(1);
        }
        if (this_[0x2a]) {
            FUN_004daf90(&this_[0x2a]);
            this_[0x2a] = 0;
        }
    }

    // Cleanup remaining sub-object pointers (free only, no destructor calls)
    if (this_[0x2e]) {
        FUN_004daf90(&this_[0x2e]);
    }
    if (this_[0x2c]) {
        FUN_004daf90(&this_[0x2c]);
    }
    if (this_[0x2a]) {
        FUN_004daf90(&this_[0x2a]);
    }
    if (this_[0x28]) {
        FUN_004daf90(&this_[0x28]);
    }
    if (this_[0x26]) {
        FUN_004daf90(&this_[0x26]);
    }
    if (this_[0x24]) {
        FUN_004daf90(&this_[0x24]);
    }
    if (this_[0x22]) {
        FUN_004daf90(&this_[0x22]);
    }
    if (this_[0x20]) {
        FUN_004daf90(&this_[0x20]);
    }
    if (this_[0x1e]) {
        FUN_004daf90(&this_[0x1e]);
    }

    // Switch vtable to base class vtable and call base destructor
    this_[0] = 0x00d6b95c; // PTR_LAB_00d6b95c
    FUN_0080ea60();        // base destructor? (likely calls base::~base)
}