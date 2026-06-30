// FUNC_NAME: Object::removeSelfFromManager
// Function at 0x0043d1b0: Destructor-like method that unregisters an object from a global manager.
// Reads first 4 ints of this object to build a key, then finds and removes entry from manager array.
// Manager at global g_manager (EDI) has callback object at +0xc and array base at +0x10.

struct KeyStruct {
    int field0;  // from this[0]
    int field4;  // from this[1]
    int field8;  // from this[2]
    int fieldC;  // from this[3]
    int field10; // argument param1
    int field14; // always -1
};

// External functions from manager (found elsewhere)
extern int FindIndexByKey(KeyStruct* key);
extern void NotifyRemoval();

// Global manager pointer (unaff_EDI in asm)
extern void* g_manager; // points to Manager object

// Manager object layout (offsets from g_manager)
struct Manager {
    char pad0[0xC];                 // +0x0 - +0xB
    void* callbackObject;           // +0xC: pointer to an object with vtable
    void* arrayBase;                // +0x10: pointer to start of array
};

// Callback object (has vtable; vtable[1] is the removal callback)
struct CallbackObject {
    void** vtable; // first word is vtable pointer
};

void Object::removeSelfFromManager(int param1) {
    KeyStruct key;
    key.field0 = *(int*)this;      // this+0x0
    key.field4 = *(int*)((char*)this + 4);  // this+0x4
    key.field8 = *(int*)((char*)this + 8);  // this+0x8
    key.fieldC = *(int*)((char*)this + 12); // this+0xC
    key.field10 = param1;
    key.field14 = -1;

    int index = FindIndexByKey(&key);
    if (index >= 0) {
        // Access manager global
        Manager* mgr = (Manager*)g_manager;
        char* arrayStart = (char*)mgr->arrayBase;
        // Item is at arrayStart + 0x18 + index * 0x1C
        int* itemPtr = (int*)(arrayStart + 0x18 + index * 0x1C);
        if (itemPtr != nullptr) {
            int value = *itemPtr;
            if (value != 0) {
                // Call callback via vtable
                CallbackObject* cb = (CallbackObject*)mgr->callbackObject;
                void** vtable = cb->vtable; // first word is vtable
                // vtable[1] (offset 4) is the callback function
                void (*callback)(int, int) = (void (*)(int, int))vtable[1];
                callback(index, 0);
            }
        }
        // Second lookup and notify (likely remove from internal list)
        index = FindIndexByKey(&key);
        if (index >= 0) {
            NotifyRemoval();
        }
    }
}