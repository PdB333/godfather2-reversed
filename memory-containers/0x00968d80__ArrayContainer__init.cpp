// FUNC_NAME: ArrayContainer::init
// Address: 0x00968d80
// Role: Initializes an array container with a given capacity and a value, allocating two parallel arrays of (capacity+1)*4 bytes each.

struct ArrayContainerHeader {
    uint field_0;      // +0x00
    uint field_4;      // +0x04
    int* array1;       // +0x08  // first array (zeroed)
};

class ArrayContainer {
public:
    ArrayContainerHeader* header; // +0x00
    int field_4;                  // +0x04 (set to 0)
    uint capacity;                // +0x08
    int someValue;                // +0x0C
    int field_10;                 // +0x10 (set to 0)
    int* array2;                  // +0x14  // second array (uninitialized)

    void __thiscall init(uint capacity, int someValue);
};

void __thiscall ArrayContainer::init(uint capacity, int someValue) {
    // Set fields
    this->someValue = someValue;          // +0x0C
    this->field_4 = 0;                    // +0x04
    this->capacity = capacity;            // +0x08
    this->field_10 = 0;                   // +0x10

    // Allocate header structure (12 bytes)
    ArrayContainerHeader* hdr = (ArrayContainerHeader*)allocate(0xC);
    if (hdr == nullptr) {
        hdr = nullptr;
    } else {
        // Allocate first array: (capacity+1) * 4 bytes
        size_t arraySize = (size_t)(capacity + 1) * 4;
        int* arr1 = (int*)checkedAllocate(arraySize);
        hdr->array1 = arr1;               // +0x08 of header
    }
    this->header = hdr;                   // +0x00

    // Zero out the first array
    uint idx = 0;
    do {
        this->header->array1[idx] = 0;
        idx++;
    } while (idx <= capacity);

    // Allocate second array: (capacity+1) * 4 bytes
    size_t arraySize2 = (size_t)(capacity + 1) * 4;
    this->array2 = (int*)checkedAllocate(arraySize2);  // +0x14
}