// FUNC_NAME: SimManager::collectObjects
// Address: 0x008c1c70
// Role: Collects object IDs from an array of 16-byte elements, filtering by a hash table and game mode, and stores them into a dynamic array.

struct DynamicIntArray {
    int* data;      // +0x00
    int count;      // +0x04
    int capacity;   // +0x08
};

// External helper functions (likely from EARS engine)
extern int __cdecl getObjectIndex(void* element);          // FUN_008bf220
extern int __cdecl getObjectType(void* element, int flag); // FUN_00446100
extern int __cdecl getGameMode();                          // FUN_00791750
extern void __cdecl debugLog(int level);                   // FUN_00790110
extern void __cdecl debugPrint(int param);                 // FUN_00790d30
extern void __cdecl growArray(int newCapacity);            // FUN_006b1e10

int __thiscall SimManager::collectObjects(void* elementArray, int param3, int elementCount, DynamicIntArray* outputArray)
{
    int* currentElement = (int*)elementArray;
    int counter = elementCount;

    if (elementCount != 0) {
        do {
            int objectIndex = getObjectIndex(currentElement);
            int objectId = 0;

            if (objectIndex < 0) {
                // Hash table lookup failed
                int type = getObjectType(currentElement, 0);
                if (type != 0) {
                    int gameMode = getGameMode();
                    if (gameMode < 3) {
                        debugLog(1);
                        debugPrint(param3);
                    }
                    objectId = type; // Use type as fallback ID
                }
            } else {
                // Look up in hash table at this+0x1a4 (array of pointers)
                int* hashTable = *(int**)(this + 0x1a4);
                int* objectPtr = (int*)hashTable[objectIndex];
                if (objectPtr != 0) {
                    objectId = *(int*)(objectPtr + 8); // Object ID at offset +8
                } else {
                    // Object not found, fallback to type
                    int type = getObjectType(currentElement, 0);
                    if (type != 0) {
                        int gameMode = getGameMode();
                        if (gameMode < 3) {
                            debugLog(1);
                            debugPrint(param3);
                        }
                        objectId = type;
                    }
                }
            }

            if (objectId != 0) {
                // Ensure output array has space
                if (outputArray->count == outputArray->capacity) {
                    int newCapacity = (outputArray->capacity == 0) ? 1 : outputArray->capacity * 2;
                    growArray(newCapacity);
                    // Note: growArray likely updates outputArray->data and capacity globally
                }
                int* slot = outputArray->data + outputArray->count;
                outputArray->count++;
                if (slot != 0) {
                    *slot = objectId;
                }
            }

            currentElement = (int*)((int)currentElement + 0x10);
            counter--;
        } while (counter != 0);
    }

    return elementCount << 4; // Total bytes processed
}