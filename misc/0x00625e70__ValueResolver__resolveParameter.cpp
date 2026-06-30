// FUNC_NAME: ValueResolver::resolveParameter
void __fastcall ValueResolver::resolveParameter(ValueResolver* this, int seed)
{
    // If seed is less than 1, call initialization/assert
    if (seed < 1) {
        assertOrInit(); // FUN_00625430
    }

    // Get pointer to data block (offset +0x8 in this)
    int* dataPtr = *(int**)(this + 0x8); // this->mData

    // The header is located 8 bytes before the data pointer
    // Header layout: [int type, int rawFloat] (treated as two ints)
    int* header = dataPtr - 2;                        // header[0] = type, header[1] = rawFloat

    int type = header[0];
    float floatVal = *(float*)&header[1];            // reinterpret second int as float

    if (type == 3) {
        // Check if the float value is a normal number (not NaN)
        // NaN cast to int and back is not equal to itself
        if ((float)(int)floatVal == floatVal) {
            // Valid float; use type 3 generator
            int* result = (int*)getType3Result();    // FUN_00637f10
            header[0] = result[0];
            header[1] = result[1];
            return;
        }
        // Float is NaN – fall through to default
    }
    else if (type == 4) {
        // Type 4 uses a different generator
        int* result = (int*)getType4Result();        // FUN_00637f90
        header[0] = result[0];
        header[1] = result[1];
        return;
    }

    // Default generator for any other type or invalid float
    int* result = (int*)getDefaultResult();          // FUN_00637ea0
    header[0] = result[0];
    header[1] = result[1];
}