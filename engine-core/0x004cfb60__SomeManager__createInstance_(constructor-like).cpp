// FUNC_NAME: SomeManager::createInstance (constructor-like)
// Function address: 0x004cfb60
// Role: Allocates and initializes a manager object with two sub-objects (likely input slots)
class SomeSubObject {
public:
    void* vtable;                   // +0x00
    // ... other members (total size 0x1C)
};

class SomeManager {
public:
    void* vtable;                   // +0x00
    SomeSubObject* subObjects[2];   // +0x04, +0x08

    // constructor-like: takes an array of 2 values (8 bytes each) from param_2
    static SomeManager* createInstance(SomeManager* self, uint32_t* someArray) {
        // Store global singleton pointer
        g_SomeManagerInstance = self;

        // Set vtable
        self->vtable = &PTR_FUN_00e36cb8;

        // Allocate and initialize two sub-objects
        for (uint32_t i = 0; i < 2; i++) {
            SomeSubObject* sub = (SomeSubObject*)allocateMemory(0x1C);
            if (sub != nullptr) {
                sub->vtable = &PTR_FUN_00e36cb4;
                // Initialize sub-object with value from array at index i*8
                initializeSubObject(sub, someArray[i * 8]); // FUN_004cfc30
            }
            self->subObjects[i] = sub;
        }
        return self;
    }

private:
    static SomeManager* g_SomeManagerInstance; // DAT_01223398
    static void* allocateMemory(int size); // FUN_009c8e50
    static void initializeSubObject(SomeSubObject* sub, uint32_t initValue); // FUN_004cfc30
};