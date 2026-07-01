// FUNC_NAME: SystemManager::SystemManager
// Address: 0x0083b1d0
// Constructor for a system manager with heap allocation flag.
// Class size appears to be 0x14c (332 bytes).
// Offsets are in DWORDs; actual byte offsets: +0x00 vtable, +0x3C and +0x48 function pointers,
// +0x148 is written twice (likely decompiler artifact – possibly +0x148 and +0x14C?).

class SystemManager {
public:
    SystemManager(char flag) {
        // Set virtual table pointer at offset +0x00
        *(void**)this = (void*)0x00d74270;

        // Set additional function table pointers
        *(void**)((uint)this + 0x3C) = (void*)0x00d74260;   // offset +0x0F (0x3C)
        *(void**)((uint)this + 0x48) = (void*)0x00d7425C;   // offset +0x12 (0x48)

        // Note: Two assignments to offset +0x52 (0x148) – overwritten, possibly bug in decompilation
        *(void**)((uint)this + 0x148) = (void*)0x00d74258;  // offset +0x52
        *(void**)((uint)this + 0x148) = (void*)0x00d74254;  // overwrites previous

        // Reset global initialization flag (DAT_0112a678)
        *((int*)0x0112a678) = 0;

        // Call internal initialization function (FUN_0083f0e0)
        initializeSystem();

        // If object was heap-allocated, call operator delete (FUN_0043b960)
        // This pattern is unusual – potentially condition should be reversed or missing failure check.
        if (flag & 1) {
            operator delete(this, 0x14c);  // operator delete(void*, size_t)
        }
    }

private:
    void initializeSystem();  // placeholder for FUN_0083f0e0
};