// FUNC_NAME: ListenerRegistry::registerListener
// Reconstructed C++ for function at 0x00623ea0
// This function registers a listener object with an associated handle.
// The listener is retained (reference count increased) and stored at this+0x0C.
// A binding handle is computed and stored at this+0x10.

// Forward declarations for external functions
typedef unsigned int Handle;
Handle getBindingHandle(int param_2, void* obj); // FUN_004265d0
void setBinding(void* obj, Handle handle);       // FUN_006241d0

// Listener object vtable layout (assumed offsets)
struct ListenerVTable {
    void (*unknown0)();                          // offset 0x00
    void (*setHandleAndFinalize)(int, int);      // offset 0x04 (called with handle and 0)
    void (*addRef)(void* self);                  // offset 0x08 (takes self pointer)
    void (*finalize)();                          // offset 0x0C (no arguments)
};

struct Listener {
    ListenerVTable* vtable;
    // other fields...
};

// Class that holds a reference to a listener and a handle
class ListenerRegistry {
public:
    // Offsets: +0x00: unknown, +0x0C: Listener* m_listener, +0x10: Handle m_handle
    void registerListener(Listener* listener, int handle);
};

void ListenerRegistry::registerListener(Listener* listener, int handle) {
    // Retain the listener (vtable[2])
    listener->vtable->addRef(listener);

    Handle h;
    if (handle == 0) {
        h = 0;
    } else {
        h = getBindingHandle(handle, listener);
    }
    setBinding(listener, h);

    // Store listener pointer at this+0x0C
    this->m_listener = listener;

    // Second call to addRef (vtable[2]) with no arguments – likely a decompilation artifact
    // Possibly intended as a call to a different vtable entry or with the same argument.
    listener->vtable->addRef(); // Note: missing argument in original decompilation

    if (handle != 0) {
        h = getBindingHandle(handle, this->m_listener);
        this->m_handle = h; // offset 0x10
        // Call vtable[1] with handle and 0
        listener->vtable->setHandleAndFinalize(handle, 0);
        // Call vtable[3] with no arguments
        listener->vtable->finalize();
        return;
    }
    this->m_handle = 0; // offset 0x10
    // Call vtable[3] with no arguments
    listener->vtable->finalize();
    return;
}