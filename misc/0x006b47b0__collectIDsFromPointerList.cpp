// FUNC_NAME: collectIDsFromPointerList
// Address: 0x006b47b0
// Role: Iterates over an array of 0x14-byte structures (likely object references) and collects a derived ID/handle into a dynamic array descriptor.
// The dynamic array descriptor (param_3) has the layout: [0] data pointer, [4] current size (count), [8] capacity.
// Returns the total byte size of the input array (count * 0x14).

#include <cstdint>

// Forward declarations for internal helpers
bool isObjectValid(void* ptr);                      // FUN_008c74d0
int* getObjectID(void* object);                     // FUN_008c1320
bool isObjectNull(void* object);                    // FUN_00446100
void resizeDynamicArray(int newCapacity);           // FUN_006b1e10

int collectIDsFromPointerList(void* inputList, int count, int* outputArrayDesc)
{
    if (count == 0)
        return 0;

    char* current = (char*)inputList + 4;  // Skip first field? Actually param_1+4 is used as the struct pointer in loop
    int remaining = count;

    do {
        // Get the pointer to the current structure (offset -4 from current due to increment)
        void* structPtr = *(void**)(current - 4); 

        if (isObjectValid(structPtr)) {
            int* idPtr = getObjectID(current);   // current points to some field within the struct?

            if (idPtr == nullptr) {
                // Fallback: check if the structure itself is null via another function
                if (isObjectNull(current, 0) == 0) 
                    goto next;
            } else {
                // The ID is stored at offset 8 from the returned pointer
                idPtr = (int*)(*(int*)(idPtr + 2));  // Actually offset 8 in bytes, assuming int* is 4 bytes
            }

            if (idPtr != nullptr) {
                int dataCapacity = outputArrayDesc[2];
                int currentSize = outputArrayDesc[1];

                if (currentSize == dataCapacity) {
                    int newCapacity = (dataCapacity == 0) ? 1 : dataCapacity * 2;
                    resizeDynamicArray(newCapacity);
                }

                int* dataArray = (int*)outputArrayDesc[0];
                dataArray[currentSize] = (int)idPtr;
                outputArrayDesc[1] = currentSize + 1;
            }
        }

next:
        current += 0x14;
        remaining--;
    } while (remaining != 0);

    return count * 0x14;
}