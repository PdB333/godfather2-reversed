// FUNC_NAME: someBufferProcessingFunction
void someBufferProcessingFunction(void)
{
    int* edi; // unaff_EDI
    int* esi; // unaff_ESI
    int buffer[4]; // local_1c, structure with 4 ints

    // Calculate a count based on difference between two pointers
    int count = ((esi - edi) / 4 + 1) / 2; // local_1c[3]

    buffer[0] = 0;
    buffer[1] = 0;
    buffer[2] = 0;
    // buffer[3] is assigned above

    // Initialize or process the buffer
    initializeBuffer(); // FUN_00651530

    // If buffer[0] is non-zero, free it
    if (buffer[0] != 0) {
        freeMemory(buffer[0]); // FUN_009c8eb0
    }
}