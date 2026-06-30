// FUNC_NAME: EARS::Array::getElement
// Function address: 0x00632aa0
// Role: Returns an element from a dynamic array based on an internal offset index.
//       Uses flags to control behavior: bit0 = invalid, bit1 = use pointer to load index.
//       Computes element index from stored offset and a base value from type info.
//       Returns -1 on failure.

int EARS::Array::getElement() {
    // this->flags at offset 0x8
    if ((this->flags & 1) == 0) {
        if ((this->flags & 2) != 0) {
            // this->ptr at offset 0x10 is a pointer to an int that holds the index
            this->index = *(int*)this->ptr; // offset 0xC
        }
        // Get type info from vtable[-1] (RTTI pointer) + 0xC
        int* typeInfo = *(int**)(*(int*)this + -4); // vtable[-1]
        int baseOffset = *(int*)(typeInfo + 0xC); // base offset for array
        // Compute element index: (storedOffset - baseOffset) / 4 - 1
        int elemIndex = (this->index - baseOffset >> 2) - 1;
        if (elemIndex >= 0) {
            int* array = *(int**)(typeInfo + 0x14); // pointer to array data
            if (array != 0) {
                return array[elemIndex];
            }
            return 0;
        }
    }
    return -1;
}