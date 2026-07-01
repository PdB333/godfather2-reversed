// FUNC_NAME: Iterator::dereference
// Function at 0x008eb0a0: Dereferences an iterator, returning a pointer to the data at offset 0xc from the current element.
// Iterator struct: [0] container pointer, [4] current element pointer.
// Container struct: [0] begin, [4] end pointer.
// Asserts if container is null or current equals container->end.

void assertionFailed(); // FUN_00b97aea - debug assertion failure

int* __fastcall Iterator::dereference(int* thisPtr)
{
    // thisPtr[0] = container pointer
    // thisPtr[1] = current element pointer
    if (thisPtr[0] == 0) {
        assertionFailed();
    }
    // Container's end pointer is at offset +4 from container
    if (thisPtr[1] == *(int*)(thisPtr[0] + 4)) {
        assertionFailed();
    }
    // Return pointer to data at offset 0xc within the current element
    return (int*)(thisPtr[1] + 0xc);
}