// FUNC_NAME: Container::getElementPtr
// Function at 0x00693e10: Validates a container pointer and index (or element pointer), then returns a pointer to the element data at offset 0xC.
// Container structure (pointed to by param_1[0]): 
//   +0x00: void* data (pointer to array of elements)
//   +0x04: int count (number of elements)
// The second parameter (param_1[1]) is either an index (int) or a pointer to an element.
// The check ensures that param_1[0] is not null and that param_1[1] is not equal to container->count (out-of-bounds).
// Then returns param_1[1] + 0xC, which when cast back yields a pointer to the element's data at offset 12 (e.g., a member field).
int __fastcall Container::getElementPtr(int* param_1)
{
    // Assert container pointer is valid
    if (*param_1 == 0) {
        EARSErrorHandler::fatalAssert(); // FUN_00b97aea
    }
    // Assert index (or pointer) is not equal to the stored count (out-of-bounds)
    if (param_1[1] == *(int*)(*param_1 + 4)) {
        EARSErrorHandler::fatalAssert();
    }
    // Return the data pointer (or offset) by adding 0xC to the index/element pointer.
    return param_1[1] + 0xC;
}