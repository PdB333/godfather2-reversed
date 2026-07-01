// FUNC_NAME: EntityManager::findByID
// Function at 0x008c12a0: Searches an array of objects by ID field at offset +0x08.
// Class layout: this+0x1a4 = pointer to array of object pointers, this+0x1a8 = count.
int* EntityManager::findByID(int id) {
    uint count = *(uint*)(this + 0x1a8); // number of objects in array
    if (count != 0) {
        int** objectArray = *(int***)(this + 0x1a4); // pointer to array of object pointers
        for (uint i = 0; i < count; i++) {
            // Each object has an ID at offset +0x08
            if (*(int*)(objectArray[i] + 8) == id) {
                return objectArray[i];
            }
        }
    }
    return 0;
}