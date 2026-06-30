// FUN_NAME: arrayAccessChecked
int* arrayAccessChecked(int* arrayDesc, uint index)
{
    int* savedDesc = arrayDesc; // saved pointer to descriptor (offset +0x00: data, +0x04: size)
    // If index >= size, call resize handler
    if ((uint)arrayDesc[1] <= index) {
        arrayDesc = (int*)0; // discard old descriptor pointer
        resizeArray(&arrayDesc); // resize function updates the pointer (new or same descriptor)
    }
    // Return address of element: data pointer + index * 4
    return (int*)(*savedDesc + index * 4);
}