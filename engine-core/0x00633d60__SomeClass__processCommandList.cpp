// FUNC_NAME: SomeClass::processCommandList
// 0x00633d60 - This function interprets a list of commands (type+value pairs) for an object.
// It traverses a hash table to find or execute actions based on command types (e.g., 5, 7).
// The 'this' pointer accesses data at offset 0x10 and then +0x58.
// Commands are stored as pairs (type, arg) where type 5 and 7 trigger special behavior.
// It uses a recursion depth limiter (100) and calls error handlers if indices are invalid.

/// @brief Process a sequence of commands from a list.
/// @param this Pointer to the owning object.
/// @param depth Recursion depth counter (0 initial, max 100).
/// @param unused Unused parameter (padding?).
/// @param data Pointer to data block (two ints) to write on type 5 success.
void SomeClass::processCommandList(void* this, int depth, int unused, int* data) {
    int commandType;
    int key;
    int* node;
    int* bucket;
    int* hashTable;
    int* entry;
    int* nextNode;
    int* resultNode;

    // Initialize depth counter (local renamed from param_1)
    int* commandList = (int*)0x0; // Initially null, but actually the depth counter
    depth = 0; // Overwrite first parameter with depth starting value

    // Loop through commands (each command is a pair of ints: type, value)
LAB_00633d72:
    commandType = *commandList; // Get type from current command
    if (commandType != 5) {
        // If type is not 5, get the object's hash table base
        hashTable = *(int**)(*(int*)(this + 0x10) + 0x58); // +0x10 -> +0x58
        if (commandType == 5) {
            // Type 5 again? Dead code due to earlier check, but keep logic
            // Compute bucket index using hash from key
            int* bucketBase = *(int**)(*(int*)(commandList[1] + 8) + 0x10); // Get bucket array from command's arg
            int hashShift = *(unsigned char*)(*(int*)(commandList[1] + 8) + 7) & 0x1f;
            int mask = (1 << hashShift) - 1;
            int bucketIndex = mask & *(unsigned int*)(hashTable + 8); // hashTable+8 is some hash value
            bucket = bucketBase + bucketIndex * 0x14; // Each bucket entry is 20 bytes (0x14)
            do {
                if (*bucket == 4 && bucket[1] == hashTable) { // Check type and key match
                    goto LAB_00633ed3;
                }
                bucket = (int*)bucket[4]; // Follow next pointer
            } while (bucket != (int*)0x0);
            goto LAB_00633e55; // Not found, error path
        }
        if (commandType == 7) {
            // Type 7: similar lookup but different error handling
            int* bucketBase2 = *(int**)(*(int*)(commandList[1] + 8) + 0x10);
            int hashShift2 = *(unsigned char*)(*(int*)(commandList[1] + 8) + 7) & 0x1f;
            int mask2 = (1 << hashShift2) - 1;
            int bucketIndex2 = mask2 & *(unsigned int*)(hashTable + 8);
            bucket = bucketBase2 + bucketIndex2 * 0x14;
            do {
                if (*bucket == 4 && bucket[1] == hashTable) {
                    goto LAB_00633ed3;
                }
                bucket = (int*)bucket[4];
            } while (bucket != (int*)0x0);
            goto LAB_00633e55;
        }
        // For other types, set resultNode to a global error node (DAT_00e2a93c)
        resultNode = &DAT_00e2a93c;
        goto LAB_00633e60;
    }

    // Type 5 handling
    key = commandList[1]; // arg for type 5 command
    int* somePointer = FUN_00638020(); // Get some output pointer
    if (*somePointer != 0) {
        // If pointer is pre-allocated, write data to it
        *somePointer = *data;
        somePointer[1] = data[1];
        return;
    }

    // No pre-allocated pointer, do hash table lookup
    int* commandArgData = *(int**)(key + 8); // +8 from the command argument
    if ((*(unsigned char*)(commandArgData + 6) & 2) == 0) { // Check flag at +6
        hashTable = *(int**)(*(int*)(this + 0x10) + 0x58);
        int* bucketBase3 = *(int**)(commandArgData + 0x10); // Bucket array from command arg
        int hashShift3 = *(unsigned char*)(commandArgData + 7) & 0x1f;
        int mask3 = (1 << hashShift3) - 1;
        int bucketIndex3 = mask3 & *(unsigned int*)(hashTable + 8);
        int* bucket3 = bucketBase3 + bucketIndex3 * 0x14;
        do {
            if (*bucket3 == 4 && bucket3[1] == hashTable) {
                resultNode = bucket3 + 2; // data starts at offset 8
                if (bucket3[2] == 0) { // Check first data word
                    *(unsigned char*)(commandArgData + 6) |= 2; // Set flag
                    resultNode = (int*)0x0;
                }
                goto LAB_00633ded;
            }
            bucket3 = (int*)bucket3[4];
        } while (bucket3 != (int*)0x0);
        // Not found: set flag and null result
        *(unsigned char*)(commandArgData + 6) |= 2;
        resultNode = (int*)0x0;
    } else {
        resultNode = (int*)0x0;
    }

LAB_00633ded:
    if (resultNode == (int*)0x0) {
        goto LAB_00633df1; // Re-execute the write
    }
    goto LAB_00633e6f; // Process the result node

LAB_00633ed3:
    resultNode = bucket + 2; // Data starts at offset 8
LAB_00633e5a:
    if (*resultNode == 0) {
LAB_00633e60:
        FUN_006336f0("index"); // Error: index not found
    }
LAB_00633e6f:
    if (*resultNode == 6) {
        FUN_00633b40(resultNode, commandList); // Execute action with result node and command list
        return;
    }
    // Move to next command in list
    depth++;
    commandList = resultNode; // Follow the result node's chain? Actually commandList is overwritten
    if (depth > 100) {
        FUN_00633920(); // Handle recursion overflow
        return;
    }
    goto LAB_00633d72;
}