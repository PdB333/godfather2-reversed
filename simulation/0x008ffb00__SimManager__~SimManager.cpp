// FUNC_NAME: SimManager::~SimManager

// Address: 0x008ffb00
// Role: Destructor for SimManager class. Destroys all contained SimObject elements,
// then destroys the base object, frees the element array memory, and marks the manager as inactive.

void __thiscall SimManager::~SimManager(SimManager *this) {
    int count;
    void **elementPtr;
    uint newCount;

    // Set vtable pointer to this class's vtable (normally done in constructor/destructor)
    this->vtable = (void **)0x00d81700;

    // Iterate over the array of element pointers, destroying from the end
    count = this->elementCount; // +0x0C
    while (count != 0) {
        // Get the last element in the array (pointer to a SimObject)
        elementPtr = *(void ***)(this->pElementArray + (count - 1) * 4); // +0x08
        newCount = count - 1;

        // Call destructor on that element (virtual destructor with argument 1)
        if (elementPtr != NULL) {
            (**(void (__thiscall **)(void *, int))elementPtr)(elementPtr, 1);
        }

        // Shift remaining elements down? (Condition never true as written; likely a bug or different logic)
        if (newCount < this->elementCount - 1) {
            do {
                elementPtr = (void **)(this->pElementArray + newCount * 4);
                *elementPtr = *(elementPtr + 1);
                newCount++;
            } while (newCount < this->elementCount - 1);
        }

        // Decrement element count
        this->elementCount = count - 1; // +0x0C
        count = this->elementCount;
    }

    // Call virtual destructor on the base object (offset 0x0C in vtable)
    (**(void (__thiscall **)(void *))(*(int *)this->pBaseObject + 0x0C))(); // +0x04

    // Free the array memory if allocated
    if (this->pElementArray != NULL) { // +0x08
        FUN_009c8f10(this->pElementArray);  // deallocation function (likely operator delete)
    }

    // Mark object as destroyed by setting vtable to a sentinel
    this->vtable = (void **)0x00d816fc;

    // Clear global singleton flag
    _DAT_0112ff10 = 0;  // g_simManagerExists
}