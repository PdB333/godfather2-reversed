// FUNC_NAME: EventHandler::EventHandler
// Address: 0x005e0800
// Description: Constructor for an event handler wrapper. Takes a pointer to an object with a vtable (pObject) and an optional handle (handle).
// The object is stored at this+0x14, and the converted handle at this+0x18.
// The vtable interface is assumed to have four methods: [0]=unknown, [1]=SetHandle, [2]=AddRef, [3]=Finalize.

class EventHandler {
public:
    void* m_pObject;   // offset +0x14, pointer to an object with vtable
    void* m_handle;     // offset +0x18, possibly a handle or secondary pointer
};

// Helper functions (assumed from callees)
static void* ConvertHandle(void* handle, void* pObject);   // FUN_004265d0
static void Finalize(void* pObject, void* handle);         // FUN_005e1150

EventHandler* __thiscall EventHandler_Constructor(EventHandler* this, void* pObject, void* handle) {
    // vtable call at offset +8 (likely AddRef)
    (*(void (__thiscall **)(void*))(*((int*)pObject) + 2))(pObject);

    void* convertedHandle;
    if (handle == 0) {
        convertedHandle = 0;
    } else {
        convertedHandle = ConvertHandle(handle, pObject);
    }
    Finalize(pObject, convertedHandle);

    this->m_pObject = pObject;

    // Second vtable call at offset +8 (likely AddRef again)
    (*(void (__thiscall **)(void*))(*((int*)pObject) + 2))(pObject);

    if (handle != 0) {
        convertedHandle = ConvertHandle(handle, this->m_pObject);
        this->m_handle = convertedHandle;

        // vtable call at offset +4 (likely SetHandle with flags)
        (*(void (__thiscall **)(void*, void*, int))(*((int*)pObject) + 1))(pObject, handle, 0);

        // vtable call at offset +0xC (likely Finalize)
        (*(void (__thiscall **)(void*))(*((int*)pObject) + 3))(pObject);
    } else {
        this->m_handle = 0;

        // vtable call at offset +0xC
        (*(void (__thiscall **)(void*))(*((int*)pObject) + 3))(pObject);
    }

    return this;
}