// FUNC_NAME: setField0x6c
// Address: 0x00478680
// Role: Simple setter for a 4-byte field at offset 0x6c in an object.
// This is a __thiscall member function; the field is overwritten with the provided value.
void __thiscall setField0x6c(int this_ptr, int value) {
    *(int*)(this_ptr + 0x6c) = value; // +0x6c: unknown field
}