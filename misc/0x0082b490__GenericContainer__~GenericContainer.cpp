// FUNC_NAME: GenericContainer::~GenericContainer
// Address: 0x0082b490
// Destructor: cleans up an array of owned objects (likely derived from EARS::Framework::Entity or similar)
// Offsets: +0x00 vtable pointer, +0x08 pointer to array of object pointers, +0x0C count of objects in array

void __thiscall GenericContainer::~GenericContainer(GenericContainer* this)
{
    unsigned int i;
    void** objectArray;
    unsigned int numObjects;

    // Set vtable to a specific destroying vtable (likely for base class cleanup)
    *(void***)this = (void**)(&PTR_FUN_00d73840);

    // Check if the array pointer is non-null
    if (this->numObjects != 0) {
        // Iterate over each object pointer in the array
        for (i = 0; i < this->numObjects; i++) {
            objectArray = (void**)(this->objectArray[i]); // each element is a pointer to an object
            if (objectArray != (void**)0x0) {
                // Call the object's vtable function at index 0 with argument 1 (likely destructor or release)
                (**(code**)objectArray)(1);
            }
        }
    }

    // Free the array memory itself
    if (this->objectArray != (void**)0x0) {
        FUN_009c8f10(this->objectArray); // likely operator delete[] or free
    }
    return;
}