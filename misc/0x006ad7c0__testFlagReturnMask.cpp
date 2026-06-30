// FUNC_NAME: testFlagReturnMask
// Address: 0x006ad7c0
// This function tests a flag by calling a virtual method on an object.
// It calls the vtable function at offset 0x10 (index 4) which takes (uint, int*) and returns a char.
// Returns the original bitmask (param_2) if the virtual function returns non-zero, otherwise 0.

uint testFlagReturnMask(int* object, uint flagMask) {
    int dummyOutput = 0;
    // Virtual call at vtable+0x10
    char condition = (*(char (**)(int*, uint, int*))(*(int*)object + 0x10))(object, flagMask, &dummyOutput);
    // Convert boolean to mask: -(uint)(condition != 0) produces 0xFFFFFFFF if true, 0 if false
    return -(uint)(condition != 0) & flagMask;
}