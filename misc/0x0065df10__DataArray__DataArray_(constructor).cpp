// FUNC_NAME: DataArray::DataArray (constructor)
// Address: 0x0065DF10
// Role: Initializes a dynamic array container with given capacity.
// The class holds a pointer to a header struct (12 bytes), a count, capacity, a global value, and an extra buffer.
void __thiscall DataArray::DataArray(uint initialCapacity)
{
    // Allocate header block (12 bytes)
    int* header = (int*)FUN_009c8e50(12); // likely operator new
    if (header != nullptr) {
        // Allocate data buffer: (initialCapacity + 1) * 4 bytes
        int* data = (int*)FUN_009c8e80((initialCapacity + 1) * 4); // likely operator new
        // Data pointer stored at header offset +8
        header[2] = data;
    } else {
        header = nullptr;
    }
    this->header = header;          // +0x00
    this->capacity = 0;             // +0x04
    this->count = initialCapacity;  // +0x08
    this->globalField = DAT_00e35654; // +0x0C (some global constant)
    this->field4 = 0;               // +0x10
    // Initialize data array elements to zero
    for (uint i = 0; i <= initialCapacity; i++) {
        header[2][i] = 0;
    }
    // Allocate an additional buffer (uninitialized)
    this->otherBuffer = (int*)FUN_009c8e80((initialCapacity + 1) * 4); // +0x14
}