// FUNC_NAME: ObjectIdRegistry::removeByKey
// Reconstructed C++ for function at 0x0082b9d0
// Purpose: Find and remove an object from a dynamic array by matching a 4-int key.
// This is a member function of a container that stores an array of pointers to objects.
// The object structure has a 16-byte key at offsets +0x1c, +0x20, +0x24, +0x28.

class ObjectIdRegistry {
    int** objectArray;     // +0x08: pointer to array of pointers to objects
    int   numObjects;      // +0x0c: current number of objects in the array
public:
    // Remove the object whose key (4 ints) matches the key given by param_2.
    // Returns a pointer to the removed object, or 0 if not found.
    // The key in each object is stored as: int key[4] at offsets +0x1c, +0x20, +0x24, +0x28.
    int* removeByKey(int* key) {
        uint currentSize = this->numObjects;          // uVar1
        uint idx = 0;                                 // uVar3

        if (currentSize != 0) {
            int** ptr = this->objectArray;            // piVar4 iterates over the array
            do {
                int* obj = *ptr;                      // iVar2 = pointer to the object
                // Compare the four-key field of the object with the input key
                if ( (obj[0x1c/4] == key[0]) &&
                     (obj[0x20/4] == key[1]) &&
                     (obj[0x24/4] == key[2]) &&
                     (obj[0x28/4] == key[3]) ) {
                    // Found: shift all subsequent elements left by one
                    if (idx < currentSize - 1) {
                        do {
                            this->objectArray[idx] = this->objectArray[idx + 1];
                            idx++;
                        } while (idx < this->numObjects - 1U);
                    }
                    this->numObjects--;
                    return obj;                       // Return the pointer to the removed object
                }
                idx++;
                ptr++;
            } while (idx < currentSize);
        }
        return 0;                                     // Not found
    }
};