// FUNC_NAME: operatorDeleteWithMagicCheck
void operatorDeleteWithMagicCheck(void* ptr)
{
    // Check if pointer is non-null and the magic number (0xDDDD) is present at offset -8
    if ((ptr != 0) && (*(int*)((char*)ptr - 8) == 0xDDDD)) {
        // Free the allocation starting at the magic number location
        _free((int*)((char*)ptr - 8));
    }
}