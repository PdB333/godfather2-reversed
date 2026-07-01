// FUNC_NAME: StreamManager::enableStreaming
// Function at 0x009858d0 - Enables streaming feature if not already active.
// Checks bit 2 at offset 0x68, calls initialization, then sets bit2 on local and global state.

// Assumed class definition with offsets
class StreamManager {
public:
    ushort flags; // +0x68 (bitfield)
    // ... other members
};

// Global pointer or singleton instance (DAT_011298d4 + 0x10 used as flag storage)
extern StreamManager* gStreamManagerGlobal; // placeholder

void __fastcall StreamManager::enableStreaming(StreamManager* this) {
    // Check if bit2 of flags is clear (feature not enabled)
    if (!((this->flags >> 2) & 1)) {
        // Call initialization routine (e.g., real streaming setup)
        FUN_00911fd0(); // likely StreamManager::initStreaming()

        // Set bit2 in local flags (enable locally)
        this->flags |= 0x4;

        // Also set bit2 in global state at offset 0x10
        *(uint*)((char*)gStreamManagerGlobal + 0x10) |= 0x4;
    }
    return;
}