// FUNC_NAME: CallbackRegistry::invokeCallbacks
// Function address: 0x005e64b0
// Role: Iterates over a list of callback entries and invokes each function pointer with the given parameters.

typedef void (__thiscall *CallbackFunc)(void *param2, void *param3, void *userData);

struct CallbackEntry {
    CallbackFunc func;   // +0x00: function pointer
    void*      userData; // +0x04: associated user data
};

// The class containing the callback list.
// Offsets:
//   +0x602C: CallbackEntry* m_callbackList
//   +0x6030: uint32_t       m_callbackCount
class CallbackRegistry {
public:
    void __thiscall invokeCallbacks(void *param2, void *param3) const;
};

void __thiscall CallbackRegistry::invokeCallbacks(void *param2, void *param3) const {
    uint32_t count = this->m_callbackCount; // +0x6030
    if (count != 0) {
        CallbackEntry* list = this->m_callbackList; // +0x602C
        for (uint32_t i = 0; i < count; ++i) {
            list[i].func(param2, param3, list[i].userData);
        }
    }
}