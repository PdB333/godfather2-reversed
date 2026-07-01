// FUNC_NAME: SimObjectCollection::collectObjectsMatchingFilter

// Function at 0x008ca150
// Iterates over an array of object pointers, filters them using a check object,
// and builds a linked list of result nodes assigned to the output array.
// 
// param_1 (this): SimObjectCollection
//   +0x04: pointer to array of object pointers (each element is an int* pointing to an object)
//   +0x08: count of elements in the array
// param_2: filter (object providing the matching test via virtual function at vtable+0x194)
// param_3: output array of nodes (each node is two ints: object pointer + next pointer)
// param_4: maximum number of results to collect

#include <cstdint>

// Forward declarations of external functions used
extern bool __thiscall matchesFilter(int* filter, uint32_t filterType); // FUN_008c9a80
extern void __thiscall unlinkNode(int* node); // FUN_004daf90 (removes node from linked list)

void __thiscall SimObjectCollection::collectObjectsMatchingFilter(
    int thisPtr,            // param_1
    int* filter,            // param_2
    int* outNodes,          // param_3
    int maxResults          // param_4
) {
    uint32_t index = 0;
    int foundCount = 0;

    int* objectArray = *(int**)(thisPtr + 4);
    uint32_t numObjects = *(uint32_t*)(thisPtr + 8);

    if (numObjects == 0) {
        return;
    }

    do {
        // Dereference the pointer chain: objectArray[index] is an int*,
        // which points to an array of pointers? Actually **(...) gets the first field.
        // Assuming objectArray[index] is a pointer to an object pointer, so we get the object.
        int* currentObject = **(int**)(objectArray + index * 4); // iVar1

        if (currentObject != nullptr) {
            // Check if the filter matches the object type (FUN_008c9a80)
            // The filter's own type check with global constant _DAT_00d64c68
            uint32_t filterType = *(uint32_t*)0x00d64c68;
            if (matchesFilter(filter, filterType)) {
                // Call virtual function at vtable+0x194 (likely "isValidTarget" or "acceptsObject")
                typedef bool (__thiscall* AcceptFunc)(int*, int*);
                AcceptFunc accept = (AcceptFunc)(**(int**)(filter + 0x194));
                if (accept(filter, currentObject)) {
                    int* currentNode = outNodes + foundCount * 2;

                    // If the node already points to a different object, unlink it first
                    if (*currentNode != currentObject) {
                        if (*currentNode != nullptr) {
                            unlinkNode(currentNode);
                        }
                        // Insert the node at the front of the object's linked list
                        // The object has a 'next' pointer at +0x04
                        *currentNode = currentObject;
                        currentNode[1] = *(int*)(currentObject + 4); // save object's old next
                        *(int**)(currentObject + 4) = currentNode;   // attach node to object
                    }

                    foundCount++;
                    if (foundCount == maxResults) {
                        return;
                    }
                }
            }
        }
        index++;
    } while (index < numObjects);
}