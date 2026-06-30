// FUNC_NAME: SomeManager::handleItemActivation
// Function address: 0x00569810
// Purpose: Look up an index by ID, and if valid, call a virtual activation method on that index.
// The function acquires a mutex before the lookup and releases it afterwards.

class SomeManager {
public:
    // Virtual table at offset 0x40: virtual void onItemActivated(int index);
    virtual void onItemActivated(int index) = 0;

    // Assumed global mutex functions (likely from EA thread library)
    extern void lockMutex(void *mutex);
    extern void unlockMutex(void *mutex);

    static int findIndexByID(int id); // FUN_005695c0

    // The internal array of item indices or handles starts at offset 0x8a * 4 = 0x228
    // We access as an array of ints relative to this pointer.
    int* getItemArray() {
        return reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x228);
    }

    void handleItemActivation(int param_2) {
        // Acquire mutex (likely a global critical section)
        lockMutex(&DAT_00e2cbe8);

        // Look up the parameter and get an index
        int index = findIndexByID(param_2);
        if (index >= 0) {
            // Call virtual function at vtable offset 0x40 with the element from the array
            // The array element is at this + 0x228 + index * 4
            int value = getItemArray()[index];
            this->onItemActivated(value);
        }

        // Release mutex
        unlockMutex(&DAT_00e2cbe8);
    }

    // External data reference (address 0x00e2cbe8)
    static int DAT_00e2cbe8; // placeholder for the mutex variable
};