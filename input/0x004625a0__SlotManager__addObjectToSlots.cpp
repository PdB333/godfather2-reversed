// FUNC_NAME: SlotManager::addObjectToSlots
// Function address: 0x004625a0
// This function iterates over all registered slots (held in this) and adds the given object (obj)
// to each slot that matches its type ID or list of IDs. It prevents duplicate entries across slots
// that share the same key (first four ints of the slot entry). The object is reference counted.
// Uses a critical section for thread safety.

// Slot type info structure (pointed to by slot +0x10)
struct SlotTypeInfo {
    int field0[2];       // +0x00
    int otherID;         // +0x08  // ID used to match against obj's type list
    int slotTypeID;      // +0x0c  // ID used to match against obj's ownID
    int field_10;        // +0x10
    int field_14;        // +0x14
    int field_18;        // +0x18
    int field_1c;        // +0x1c
    int updateCallback;  // +0x20  // handle/callback notified on add
};

// Slot entry structure (size 0x28)
struct SlotEntry {
    int key0;            // +0x00
    int key1;            // +0x04
    int key2;            // +0x08
    int key3;            // +0x0c
    SlotTypeInfo* typeObject; // +0x10
    int* dynamicArray;   // +0x18  // base of pointer array for stored objects
    int arraySize;       // +0x1c
    int arrayCapacity;   // +0x20
    int flags;           // +0x24  // if zero, slot is active
};

// Object being added (param_2)
struct SlotObject {
    int field_0[2];      // +0x00
    int ownID;           // +0x08
    int field_0c;        // +0x0c
    int field_10;        // +0x10
    // ... many fields ...
    int idListCount;     // +0x44
    int* idList;         // +0x48
};

// External functions (prototypes)
static void EnterCriticalSection(void* lock);
static void LeaveCriticalSection(void* lock);
static int* ReallocateArray(int* oldArray, int newCapacity); // FUN_004630a0
static void AddRef(SlotObject* obj); // FUN_00570790
static void NotifyUpdate(int callbackHandle); // FUN_00462ae0

// Helper macro to access i-th slot from manager's list
#define GET_SLOT(base, index) ((SlotEntry*)((char*)(base) + (index) * 0x28))

bool SlotManager::addObjectToSlots(SlotObject* obj) {
    // Critical section lock (shared mutex at 0x00e2e3d4)
    EnterCriticalSection(&DAT_00e2e3d4);

    uint slotCount = *(uint*)(this + 0x20);
    SlotEntry* slotBase = *(SlotEntry**)(this + 0x1c);
    bool added = false;

    for (uint i = 0; i < slotCount; i++) {
        SlotEntry* slot = GET_SLOT(slotBase, i);

        // Slot must be active (flags == 0)
        if (slot->flags != 0) continue;

        SlotTypeInfo* typeInfo = slot->typeObject;
        if (typeInfo == nullptr) continue;

        // Check if obj matches this slot's type
        bool matches = false;
        if (typeInfo->slotTypeID == obj->ownID) {
            matches = true;
        } else if (obj->idListCount > 0) {
            int* list = obj->idList;
            for (int j = 0; j < obj->idListCount; j++) {
                if (list[j] == typeInfo->otherID) {
                    matches = true;
                    break;
                }
            }
        }

        if (!matches) continue;

        // Duplicate check: if another slot with the same key already contains obj, skip
        bool duplicate = false;
        for (uint k = 0; k < slotCount; k++) {
            if (k == i) continue;
            SlotEntry* otherSlot = GET_SLOT(slotBase, k);
            // Compare the full 16-byte key
            if (otherSlot->key0 == slot->key0 &&
                otherSlot->key1 == slot->key1 &&
                otherSlot->key2 == slot->key2 &&
                otherSlot->key3 == slot->key3) {
                // Check if obj is in other slot's array
                if (otherSlot->arraySize > 0) {
                    int* arr = otherSlot->dynamicArray;
                    for (int m = 0; m < otherSlot->arraySize; m++) {
                        if (arr[m] == (int)obj) {
                            duplicate = true;
                            break;
                        }
                    }
                }
                if (duplicate) break;
            }
        }
        if (duplicate) continue;

        // Grow the dynamic array if full
        if (slot->arraySize >= slot->arrayCapacity) {
            int newCapacity = slot->arrayCapacity > 0 ? slot->arrayCapacity * 2 : 1;
            slot->dynamicArray = (int*)ReallocateArray(slot->dynamicArray, newCapacity);
            slot->arrayCapacity = newCapacity;
        }

        // Add obj to the slot's array
        slot->dynamicArray[slot->arraySize] = (int)obj;
        slot->arraySize++;

        // Increase reference count on obj
        AddRef(obj);

        // Notify via type info's callback
        if (typeInfo->updateCallback != 0) {
            NotifyUpdate(typeInfo->updateCallback);
        }

        added = true;
    }

    LeaveCriticalSection(&DAT_00e2e3d4);
    return added;
}