// FUNC_NAME: Array::appendFromContainer
// Function address: 0x00922200
// This function appends items from a container (obtained via GetList/GetNextItem) into a dynamic array.
// The array structure is assumed to be: [buffer (int*), size (int), capacity (int)] at offsets +0x00, +0x04, +0x08.

class Array {
public:
    int* buffer;     // +0x00 - pointer to allocated int array
    int size;        // +0x04 - number of elements currently stored
    int capacity;    // +0x08 - allocated capacity (number of int slots)

    void appendFromContainer();
};

// External functions (stubs from callees)
void GetList(void* outIter);           // FUN_009217e0 - initializes iterator with count and data pointer
int  GetNextItem();                    // FUN_00891980 - returns next item (0 means no more or error)
void GrowArray(int newCapacity);       // FUN_00920b30 - reallocates array to new capacity, updates pointers
void FreeList(void* dataPtr);          // FUN_009c8f10 - frees the iterator's data

void Array::appendFromContainer() {
    // Local iterator structure matching the data layout passed to GetList
    struct Iterator {
        int* data;   // local_c - pointer to item source
        uint count;  // local_8 - number of items to iterate
        int unused;  // local_4 - not used in this function
    } iter;

    iter.data = nullptr;
    iter.count = 0;
    iter.unused = 0;

    GetList(&iter);

    // Iterate over all items from the container
    for (uint i = 0; i < iter.count; ++i) {
        int item = GetNextItem();
        if (item != 0) {
            // Check if we need to grow the array
            if (size == capacity) {
                int newCap = (capacity == 0) ? 1 : (capacity * 2);
                GrowArray(newCap);
                // buffer and capacity are updated by GrowArray
            }
            // Append the item
            buffer[size] = item;
            ++size;
        }
    }

    // Clean up the iterator's data if any
    if (iter.data != nullptr) {
        FreeList(iter.data);
    }
}