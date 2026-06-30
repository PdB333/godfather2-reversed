// FUNC_NAME: freeAndClearBufferArray
void __cdecl freeAndClearBufferArray(int** bufferArray) {
    // Iterate over a null-terminated array of pointers to buffer structures.
    // Each structure: [0] = elementCount, [1] = unknown1, [2] = unknown2, [3] = bufferPtr
    // The function frees the buffer and zeroes the structure.
    int** current = bufferArray;
    while (*current != nullptr) {
        int* bufferInfo = *current;
        if (bufferInfo[3] != 0) {
            // Clear the buffer (elementCount * 4 bytes) before freeing
            memset((void*)bufferInfo[3], 0, (size_t)bufferInfo[0] * 4);
            free((void*)bufferInfo[3]);
            bufferInfo[3] = 0;
            bufferInfo[0] = 0;  // elementCount
            bufferInfo[1] = 0;  // unknown1
            bufferInfo[2] = 0;  // unknown2
        }
        current++;
    }
}