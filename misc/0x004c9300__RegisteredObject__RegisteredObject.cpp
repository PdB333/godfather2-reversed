// FUNC_NAME: RegisteredObject::RegisteredObject

#pragma once

// Based on reverse engineering of FUN_004c9300
// Constructor for objects that register themselves into a global manager list.
// The manager holds a dynamic array of (callbackPtr, objectPtr) pairs.
// The callback 0x004c97f0 is likely a static update/destroy function.

// Forward declare the global manager structure
struct ObjectManager {
    // +0x1738: array of entries (pointer to dynamic array)
    int* entries;           // offset 0x1738
    // +0x173c: number of entries currently in use
    int entryCount;         // offset 0x173c
    // +0x1740: capacity of the array
    int entryCapacity;      // offset 0x1740
};

// Each entry in the manager list: (void* callback, RegisteredObject* object)
struct ManagerEntry {
    void* callback;       // fixed to 0x004c97f0
    RegisteredObject* object;
};

// Global singleton pointer to the object manager
extern ObjectManager* gObjectManager;

// Global debug name buffer (if non-zero, name is copied into the object)
extern int gDebugNameBuffer;

// Forward declarations of helper functions
extern void BaseClassConstructor(RegisteredObject* this); // FUN_005e4870
extern void ReallocObjectManagerArray(int newCapacity);   // FUN_005e3000
extern void StringCopy(char* dst, char* src);             // FUN_00407e60

class RegisteredObject {
public:
    // Offset +0x000: vtable pointer (if any) – not shown in code
    // Offset +0x004: name buffer (char array or pointer)
    char name[32]; // assumed fixed-size buffer (size unknown)

    RegisteredObject() {
        // Call base class constructor
        BaseClassConstructor(this);

        ObjectManager* mgr = gObjectManager;
        int count = mgr->entryCount;
        int capacity = mgr->entryCapacity;

        // Resize array if full
        if (count == capacity) {
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            ReallocObjectManagerArray(newCapacity);
        }

        // Add self to the manager list
        int index = mgr->entryCount;
        ManagerEntry* entry = reinterpret_cast<ManagerEntry*>(
            mgr->entries + index * sizeof(ManagerEntry));
        mgr->entryCount = index + 1;

        if (entry != nullptr) {
            // Fixed callback pointer – likely a static function for this class
            entry->callback = reinterpret_cast<void*>(0x004c97f0);
            entry->object = this;
        }

        // Copy debug name if global buffer is set
        if (gDebugNameBuffer != 0) {
            // Copy from global debug name into this object's name at +4
            StringCopy(&this->name[0], reinterpret_cast<char*>(&gDebugNameBuffer));
        }
    }
};