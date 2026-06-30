// FUNC_NAME: debugFree
void debugFree(void* ptr) {
    if (ptr != nullptr) {
        // Allocation header is 8 bytes before user pointer, contains magic 0xDDDD
        if (*(int*)((char*)ptr - 8) == 0xDDDD) {
            // Free the base of the allocation (including header)
            _free((int*)((char*)ptr - 8));
        }
    }
}