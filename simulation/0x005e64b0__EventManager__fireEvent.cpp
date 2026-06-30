// FUNC_NAME: EventManager::fireEvent
// Function at 0x005e64b0: Iterates over a list of registered callbacks and invokes each.
// The callback array is stored at offset +0x602c from 'this', each entry is 8 bytes:
//   [0..3] function pointer (void __thiscall? actually a cdecl/this call? but called with three args: arg1, arg2, userData)
//   [4..7] user data pointer
// The count of entries is at offset +0x6030.

struct CallbackEntry {
    void (*callback)(void*, void*, void*);  // callback(arg1, arg2, userData)
    void* userData;                         // user data passed as third argument
};

void __thiscall EventManager::fireEvent(void* arg1, void* arg2) {
    uint count = *(uint*)(reinterpret_cast<char*>(this) + 0x6030);
    if (count != 0) {
        // The array pointer is at +0x602c (points to an array of CallbackEntry)
        CallbackEntry* entries = reinterpret_cast<CallbackEntry*>(
            *(int*)(reinterpret_cast<char*>(this) + 0x602c)
        );
        for (uint i = 0; i < count; ++i) {
            entries[i].callback(arg1, arg2, entries[i].userData);
        }
    }
}