// FUNC_NAME: NotificationManager::dispatchEvent
// Function address: 0x00607dd0
// Role: Iterates over a global static list of callback structures (3-word entries) and invokes each non-null function pointer with a provided argument.
// This is likely a notification/dispatch mechanism used within the EARS engine.

// Global data:
//   DAT_0122232c - Base address of callback array (each entry is 12 bytes, first word is a function pointer)
//   DAT_012224a8 - Count of registered callbacks

// The callback signature: void (__cdecl *)(void* eventData)

#pragma pack(push, 1)
struct CallbackEntry {
    void (__cdecl *callback)(void*); // +0x00
    // +0x04, +0x08: unknown (possibly user data or flags)
    uint32_t unknown1;
    uint32_t unknown2;
};
#pragma pack(pop)

class NotificationManager {
public:
    static void dispatchEvent(void* eventData) {
        uint32_t count = *reinterpret_cast<uint32_t*>(0x012224a8);
        if (count == 0) return;

        CallbackEntry* entries = reinterpret_cast<CallbackEntry*>(0x0122232c);
        for (uint32_t i = 0; i < count; ++i) {
            if (entries[i].callback != nullptr) {
                entries[i].callback(eventData);
            }
        }
    }
};