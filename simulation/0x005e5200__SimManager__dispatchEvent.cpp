// FUNC_NAME: SimManager::dispatchEvent
// Function address: 0x005e5200
// Role: Dispatches an event to a registered handler based on object pointer.
// The method uses a table of handlers indexed by object's position in an object array.
// object is passed in EAX, param on stack.

class SimManager {
public:
    // offset 0x603c: base pointer of object array (each object 0x74 bytes)
    // offset 0x10: handler table (0x30 bytes per entry, max 0x200 entries)
    // Each handler entry:
    //   +0x00: (unknown)
    //   +0x24: function pointer (callback)
    //   +0x28: data value
    //   +0x2c: context pointer

    int dispatchEvent(int object, int param) {
        if (object == 0) {
            return 1;
        }

        // Compute index into object array
        int base = *(int*)((char*)this + 0x603c);
        unsigned int index = (object - base) / 0x74;
        if (index >= 0x200) {
            return 1;
        }

        // Get handler entry at this+0x10 + index * 0x30
        char* entry = (char*)this + 0x10 + index * 0x30;
        if (entry != 0) {
            // Callback at entry+0x24
            void (*callback)(void*, int, int) = *(void (**)(void*, int, int))(entry + 0x24);
            if (callback != 0) {
                void* context = *(void**)(entry + 0x2c);
                int data = *(int*)(entry + 0x28);
                callback(context, param, data);
            }

            // Call secondary handler (FUN_005e64b0)
            FUN_005e64b0(this, *(void**)(entry + 0x2c), param);
        }

        return 1;
    }

private:
    // Forward declaration of callee (placeholder)
    void FUN_005e64b0(void* this_ptr, void* context, int param);
};