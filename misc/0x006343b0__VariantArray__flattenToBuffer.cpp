// FUNC_NAME: VariantArray::flattenToBuffer
// Function at 0x006343b0: Flattens an array of variant values (floats/strings) into a single concatenated string buffer.
// Used for serialization of data structures (e.g., network packets, debug output).
// param_1: this pointer (VariantArray object)
// param_2: number of elements to process from the end of the array
// param_3: starting index offset (from the end) into the array

void VariantArray::flattenToBuffer(int param_2, int param_3)
{
    char buffer[92];                 // local_60 - temporary string for float conversion
    int processedCount;              // local_70 - number of elements processed in current iteration
    int totalSize;                   // iVar4 / uVar8 - accumulated size of concatenated strings
    int elementIndex;                // iVar6 - current element pointer offset
    int* elementTypePtr;             // piVar9 - pointer to type field of current element
    int* nextElementTypePtr;         // used for iteration
    int newBufferSize;               // iVar5 - new buffer size after reallocation
    int copyOffset;                  // iVar5 - offset into destination buffer for memcpy
    int remainingElements;           // iStack_6c - counter for copy loop
    char* floatStr;                  // pcVar2 - pointer into buffer for sprintf

    do {
        // Calculate pointer to current element (each element is 8 bytes: type + value)
        elementIndex = *(int*)(this + 0x0C) + 8 + param_3 * 8;
        elementTypePtr = (int*)(elementIndex - 0x10);  // point to type of element at index param_3
        processedCount = 2;  // we will process at least the current and next element

        if (*elementTypePtr == 4) {  // type 4 = string
            // Check the next element (at elementIndex - 8)
            if (*(int*)(elementIndex - 8) != 4) {
                if (*(int*)(elementIndex - 8) != 3) goto LAB_00634626;  // unknown type
                // Convert float to string
                _sprintf(buffer, "%.14g", (double)*(float*)(elementIndex - 4));
                floatStr = buffer;
                *(int*)(elementIndex - 8) = 4;  // change type to string
                do {
                    // Find end of string
                    char c = *floatStr;
                    floatStr = floatStr + 1;
                } while (c != '\0');
                // Create a string object from the buffer
                int strHandle = createString(this, buffer);
                *(int*)(elementIndex - 4) = strHandle;
            }
            // Now both elements are strings; concatenate them
            int firstStrSize = *(int*)(*(int*)(elementIndex - 4) + 0x0C);  // size of first string
            if (firstStrSize != 0) {
                totalSize = *(int*)(*(int*)(elementIndex - 0x0C) + 0x0C) + firstStrSize;  // sum of both string sizes
                // Process additional elements if param_2 > 2
                if (2 < param_2) {
                    int* prevElementTypePtr = (int*)(elementIndex - 0x18);  // point to element before the two we already have
                    do {
                        if (*prevElementTypePtr != 4) {
                            if (*prevElementTypePtr != 3) break;  // unknown type, stop
                            // Convert float to string
                            _sprintf(buffer, "%.14g", (double)(float)prevElementTypePtr[1]);
                            floatStr = buffer;
                            *prevElementTypePtr = 4;
                            do {
                                char c = *floatStr;
                                floatStr = floatStr + 1;
                            } while (c != '\0');
                            int strHandle = createString(this, buffer);
                            prevElementTypePtr[1] = strHandle;
                        }
                        totalSize = totalSize + *(int*)(prevElementTypePtr[1] + 0x0C);  // add size of this string
                        processedCount = processedCount + 1;
                        prevElementTypePtr = prevElementTypePtr - 2;  // move to previous element
                    } while (processedCount < param_2);
                }
                // Check for overflow (size > 0xFFFFFFFD)
                if (0xFFFFFFFD < (uint)totalSize) {
                    handleOverflow(this);  // likely error or truncation
                }
                // Reallocate buffer if needed
                int* bufferInfo = *(int**)(this + 0x10);  // pointer to buffer management struct
                if (*(uint*)(bufferInfo + 0x1C) < (uint)totalSize) {
                    if (totalSize < 0x20) {
                        totalSize = 0x20;
                    }
                    int newBuffer = reallocateBuffer(*(uint*)(bufferInfo + 0x1C));
                    *(int*)(bufferInfo + 0x18) = newBuffer;
                    *(int*)(bufferInfo + 0x1C) = totalSize;
                }
                // Copy all string data into the buffer
                int destBuffer = *(int*)(bufferInfo + 0x18);
                copyOffset = 0;
                remainingElements = processedCount;
                if (0 < processedCount) {
                    int* srcStrPtr = (int*)(elementIndex + processedCount * -8 + 4);  // start from the last element's string handle
                    do {
                        size_t strSize = *(size_t*)(*srcStrPtr + 0x0C);
                        _memcpy((void*)(destBuffer + copyOffset), (void*)(*srcStrPtr + 0x10), strSize);
                        remainingElements = remainingElements - 1;
                        copyOffset = copyOffset + strSize;
                        srcStrPtr = srcStrPtr + 2;  // move to previous element (since we are going backwards)
                    } while (0 < remainingElements);
                }
                // Replace the first processed element with the concatenated string
                int* firstElement = (int*)(elementIndex + processedCount * -8);
                *firstElement = 4;  // type string
                int concatStrHandle = createString(this, (char*)destBuffer);
                firstElement[1] = concatStrHandle;
            }
        }
        else {
            if (*elementTypePtr == 3) {  // type 3 = float
                // Convert float to string
                _sprintf(buffer, "%.14g", (double)*(float*)(elementIndex - 0x0C));
                floatStr = buffer;
                *elementTypePtr = 4;
                do {
                    char c = *floatStr;
                    floatStr = floatStr + 1;
                } while (c != '\0');
                int strHandle = createString(this, buffer);
                *(int*)(elementIndex - 0x0C) = strHandle;
                goto LAB_0063443d;  // now treat as string case
            }
LAB_00634626:
            // Unknown type or nested structure: call recursive processor
            int result = processNested(this, elementTypePtr, elementIndex - 8, elementTypePtr);
            if (result == 0) {
                errorHandler();  // fatal error
            }
        }
        // Update indices for next iteration
        param_2 = param_2 + (1 - processedCount);
        param_3 = param_3 + (1 - processedCount);
        if (param_2 < 2) {
            return;
        }
    } while (true);
}