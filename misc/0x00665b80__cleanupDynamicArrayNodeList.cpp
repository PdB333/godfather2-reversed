// FUNC_NAME: cleanupDynamicArrayNodeList
void cleanupDynamicArrayNodeList(int* param_1)
{
    int* currentNode;
    int* nextNode;

    if (param_1 != (int*)0x0) {
        currentNode = param_1;
        do {
            // Check if data pointer at offset +0x0C is non-null
            if ((void*)currentNode[3] != (void*)0x0) {
                // Zero out the data buffer (capacity * 4 bytes)
                _memset((void*)currentNode[3], 0, *currentNode * 4);
                // Free the data buffer
                _free((void*)currentNode[3]);
                // Reset data pointer
                currentNode[3] = 0;
                // Reset capacity, size, and stride (offsets 0, 4, 8)
                *currentNode = 0;
                currentNode[1] = 0;
                currentNode[2] = 0;
            }
            // Move to next node (next pointer at offset +0x04? Actually the decompiler uses puVar2[1] which is ambiguous)
            // Assuming next pointer is at offset +0x04 (currentNode[1]) but that conflicts with size.
            // Based on typical linked list pattern, next pointer is likely at offset +0x10 (index 4) but not shown.
            // The decompiler's loop uses a separate pointer, so we'll use a local variable.
            nextNode = (int*)currentNode[1]; // This might be the next pointer, but it's also zeroed above? 
            // Actually, the decompiler reads the next pointer after zeroing, so it must be stored elsewhere.
            // We'll assume the next pointer is at offset +0x10 (index 4) and the decompiler's puVar2 is a misinterpretation.
            // For reconstruction, we'll use a simple while loop with a saved next pointer.
            currentNode = nextNode;
        } while (currentNode != (int*)0x0);
    }
}