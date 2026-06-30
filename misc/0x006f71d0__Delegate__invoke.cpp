// FUNC_NAME: Delegate::invoke
// Function address: 0x006f71d0
// This class represents a simple delegate/callback with a void* context.
// Layout:
//   +0x00: function pointer (void (*)(uint32_t, uint32_t, void*))
//   +0x04: context data (void*)

class Delegate {
public:
    typedef void (*Callback)(uint32_t param1, uint32_t param2, void *context);

    Callback callback; // +0x00
    void *context;     // +0x04

    void __thiscall invoke(uint32_t param1, uint32_t param2) {
        if (this->callback != nullptr) {
            this->callback(param1, param2, this->context);
        }
    }
};