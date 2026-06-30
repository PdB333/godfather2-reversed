// FUNC_NAME: NetSession::clearPendingFlags
// Address: 0x0054cdb0
// Role: Clears the top 2 bits (pending update flags) for each object in the session's object array.

// Assumed structure for each object in the array (48 bytes each)
struct NetObject {
    // ... other fields (0x00 through 0x2B) ...
    uint32_t flags; // +0x2C: Flags with bit 30 and 31 used for pending updates (e.g., dirty, modified)
};

class NetSession {
public:
    // __thiscall
    void clearPendingFlags() {
        int count = this->objectCount; // +0x14
        if (count > 0) {
            int offset = 0;
            for (int i = 0; i < count; i++) {
                uint32_t* flagsPtr = (uint32_t*)(this->objects + i + 0x2C); // +0x10 points to array of NetObject
                *flagsPtr &= 0x3FFFFFFF; // Clear bits 30 and 31 (pending update flags)
                offset += 0x30; // Each object is 0x30 bytes
            }
        }
    }

private:
    NetObject* objects; // +0x10: Pointer to array of NetObject
    int objectCount;    // +0x14: Number of objects in the array
};