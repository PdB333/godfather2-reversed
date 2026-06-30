// FUNC_NAME: EntitySpecManager::EntitySpecManager
// Address: 0x0068ff10
// Role: Constructor for a manager that initializes two dynamic arrays of pointers to static 0x10-byte object specs.
// After filling the first array with all pointers from the static table (0x00e50258 to 0x00e50608), it sorts both arrays using comparator callbacks.

class EntitySpecManager {
public:
    // Vtable pointer (offset +0x00)
    int *vtable;

    // First dynamic array: pointer to array (offset +0x04)
    uint **array1Data;       // +0x04
    int array1Size;          // +0x08
    int array1Capacity;      // +0x0C

    // Second dynamic array: pointer to array (offset +0x10)
    uint **array2Data;       // +0x10
    int array2Size;          // +0x14
    int array2Capacity;      // +0x18

    // Singleton global pointer – set to 'this' during construction
    static EntitySpecManager *g_Singleton; // DAT_01129bb4
};

EntitySpecManager *EntitySpecManager::g_Singleton = nullptr;

// Helper functions (declared elsewhere, not exposed here)
extern void FUN_0068e500(int newCapacity);   // Reallocates the array to given capacity
extern void FUN_0068eca0(uint **arrayPtr);    // Possibly sorts or finalizes the array
extern void FUN_0068fe00(uint *start, uint *end, int elemCount, void (*comparator)(void)); // Sorts or processes array range

// Comparator callbacks (labels in assembly)
extern void LAB_0068e390(void); // Comparator for first array
extern void LAB_0068e370(void); // Comparator for second array

EntitySpecManager* EntitySpecManager::EntitySpecManager() {
    // Store singleton pointer
    g_Singleton = this;

    // Set vtable
    this->vtable = &PTR_FUN_00d5c908;

    // Initialize first array to empty
    this->array1Data = nullptr;
    this->array1Size = 0;
    this->array1Capacity = 0;

    // Initialize second array to empty
    this->array2Data = nullptr;
    this->array2Size = 0;
    this->array2Capacity = 0;

    // Allocate initial capacity of 0x3b (59) for the first array?
    FUN_0068e500(0x3b);

    // Populate array1 with pointers from static table (0x00e50258 .. 0x00e50608, step 0x10)
    uint *src = &DAT_00e50258; // Start of static table (0x10-byte entries)
    uint *endOfTable = &DAT_00e50608; // End of static table
    do {
        // Resize if capacity reached
        if (this->array1Size == this->array1Capacity) {
            int newCapacity = (this->array1Capacity == 0) ? 1 : (this->array1Capacity * 2);
            FUN_0068e500(newCapacity);
            this->array1Capacity = newCapacity; // Note: the realloc should update capacity, but we set it here
        }

        // Write current pointer to next slot in array1
        uint **slot = this->array1Data + this->array1Size;
        this->array1Size++;
        if (slot != nullptr) {
            *slot = src;
        }

        src = (uint*)((int)src + 0x10); // next entry
    } while ((int)src < (int)endOfTable);

    // Process first array: sort or apply comparator
    FUN_0068eca0(&this->array1Data);

    // Sort first array with comparator LAB_0068e390
    uint *array1End = (uint*)((int)this->array1Data + this->array1Size * 4);
    FUN_0068fe00(this->array1Data, array1End, (array1End - this->array1Data) >> 2, &LAB_0068e390);

    // Process second array (currently empty) with comparator LAB_0068e370
    uint *array2End = (uint*)((int)this->array2Data + this->array2Size * 4);
    FUN_0068fe00(this->array2Data, array2End, (array2End - this->array2Data) >> 2, &LAB_0068e370);

    return this;
}