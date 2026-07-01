// FUNC_NAME: SomeManager::createFromData
// Address: 0x00832c90
// Creates an object from data packet and optional owner. Returns 1 on success, 0 on failure.

#include <cstdint>

// Forward declarations for external functions
extern int* __stdcall FUN_0082afb0(int* data);          // Find or get existing object from data
extern uint32_t* __stdcall FUN_009c8f80();               // Get memory manager singleton
extern int* __thiscall FUN_00822f30();                   // Constructor for the object
extern void __thiscall FUN_00832360(int* obj);           // Register/initialize the object

class SomeManager {
public:
    int* field_0;       // vtable pointer
    int* field_4;       // unknown
    int* dataBlock;     // +8 (offset 0x8), used as param_1[2]
    // ... other fields
};

class SomeObject {
public:
    // vtable at +0x00
    virtual void addRef(int* owner);    // vtable+4
    // ... other virtuals
    int field_0[7];                     // offset 0x00 - 0x1B (7*4 = 28 bytes)
    int dataFromPacket[4];              // +0x1C = offset 28 (indices 7,8,9,10)
    int field_11[4];                    // +0x2C = offset 44 (indices 11,12,13,14)? Actually indices 0xf..0x12 are offsets 0x3C..0x48? Wait offset in 4-byte words: index 0xf -> offset 0xf*4 = 0x3C, index 0x10 -> 0x40, etc.
    // Actually piVar3[0xf] = offset 0x3C, piVar3[0x10] = 0x40, piVar3[0x11] = 0x44, piVar3[0x12] = 0x48. So the copied data goes at +0x3C.
    int blockData[4];                   // +0x3C (offset 60)
};

int __thiscall SomeManager::createFromData(int* data, int owner) {
    bool isNewObject = true;
    char isValid;
    int* newObject;
    uint32_t* memoryManager;

    // Check if the data object is valid via a virtual call on data
    isValid = (**(char (__thiscall**)(int*))(*(int*)data + 0x14))(data);
    if (isValid == 0) {
        return 0;   // Data not valid
    }

    // Try to find an existing object from the data
    newObject = FUN_0082afb0(data);
    if (newObject == nullptr) {
        isNewObject = false;
        memoryManager = FUN_009c8f80();  // Get memory manager
        // Allocate 0x110 bytes via memory manager's alloc function (vtable+0)
        int allocResult = (**(int (__thiscall**)(uint32_t*, int, void*))*memoryManager)(memoryManager, 0x110, &stack0xfffffff0);
        if (allocResult != 0) {
            newObject = FUN_00822f30();  // Construct the object
            if (newObject != nullptr) {
                goto LAB_00832d10;
            }
        }
        return 0;   // Allocation or construction failed
    }

LAB_00832d10:
    // Copy data from the packet (16 bytes -> 4 ints) to the new object at offsets +0x1C
    newObject[7] = data[0];
    newObject[8] = data[1];
    newObject[9] = data[2];
    newObject[10] = data[3];

    // If this manager has a data block, copy additional fields to the new object
    if (this->dataBlock != 0) {
        newObject[0xf] = *(int*)(this->dataBlock + 0x24);   // +0x24 -> offset 36
        newObject[0x10] = *(int*)(this->dataBlock + 0x28);   // +0x28 -> offset 40
        newObject[0x11] = *(int*)(this->dataBlock + 0x2c);   // +0x2C -> offset 44
        newObject[0x12] = *(int*)(this->dataBlock + 0x30);   // +0x30 -> offset 48
    }

    // If an owner is provided, call addRef (vtable+4)
    if (owner != 0) {
        (**(void (__thiscall**)(int*, int))*newObject)(newObject, owner);
    }

    // If we created a new object (not recycled), register it
    if (!isNewObject) {
        FUN_00832360(newObject);
    }

    return 1;   // Success
}