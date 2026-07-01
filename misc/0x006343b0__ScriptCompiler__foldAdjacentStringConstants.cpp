// FUNC_NAME: ScriptCompiler::foldAdjacentStringConstants

void ScriptCompiler::foldAdjacentStringConstants(ScriptWorkspace* workspace, int stackCount, int startIndex)
{
    char buffer[92];
    
    do {
        // workspace->stack is an array of 8-byte entries (type + value/pointer)
        int* currentEntry = (int*)(workspace->stack + startIndex * 8);  // entry at startIndex
        int* prevEntry = (int*)(workspace->stack + (startIndex - 2) * 8); // entry two before startIndex
        
        int operandsConsumed = 2; // default: assume we consume two operands
        
        if (*prevEntry == 4) { // entry is a string intern ID
            goto processStringChain;
        }
        else if (*prevEntry == 3) { // entry is a float
            // Convert float to string representation
            sprintf(buffer, "%.14g", (double)*(float*)(prevEntry + 1));
            char* p = buffer;
            *prevEntry = 4; // change type to string
            while (*p != '\0') p++;
            unsigned int strId = internString(workspace, buffer);
            *(unsigned int*)(prevEntry + 1) = strId;
            // Fall through to handle the next entry as string
            goto processStringChain;
        }
        else {
            // Not a simple scalar; try to process compound expression
            int result = processCompoundNode(workspace, prevEntry, currentEntry, prevEntry);
            if (result == 0) {
                handleScriptError(); // abort
            }
        }
        
        // Adjust indices for next iteration: move forward by (1 - operandsConsumed)
        stackCount += (1 - operandsConsumed);
        startIndex += (1 - operandsConsumed);
        if (stackCount < 2) {
            return;
        }
        continue;
        
processStringChain:
        // Ensure second operand is also a string (convert if float)
        if (*(int*)(currentEntry - 2) != 4) {
            if (*(int*)(currentEntry - 2) == 3) {
                sprintf(buffer, "%.14g", (double)*(float*)(currentEntry - 2 + 1));
                char* p = buffer;
                *(int*)(currentEntry - 2) = 4;
                while (*p != '\0') p++;
                unsigned int strId = internString(workspace, buffer);
                *(unsigned int*)(currentEntry - 2 + 1) = strId;
            }
        }
        
        // The first string entry (prevEntry) has a string intern ID; get its length
        int firstStrLen = *(int*)(*(int*)(prevEntry + 1) + 0xc);
        if (firstStrLen != 0) {
            // Calculate total length of all consecutive string entries
            unsigned int totalLen = *(int*)(*(int*)(prevEntry - 1) + 0xc) + firstStrLen;
            if (stackCount > 2) {
                int* scanEntry = (int*)(prevEntry - 2); // move two steps back (previous entry)
                do {
                    if (*scanEntry != 4) {
                        if (*scanEntry == 3) {
                            sprintf(buffer, "%.14g", (double)*(float*)(scanEntry + 1));
                            char* p = buffer;
                            *scanEntry = 4;
                            while (*p != '\0') p++;
                            int strId = internString(workspace, buffer);
                            *(int*)(scanEntry + 1) = strId;
                        }
                        else break;
                    }
                    totalLen += *(int*)(scanEntry[1] + 0xc);
                    operandsConsumed++;
                    scanEntry -= 2;
                } while (operandsConsumed < stackCount);
            }
            if (totalLen > 0xfffffffd) {
                handleStringLengthOverflow(workspace);
            }
            
            // Ensure output buffer is large enough
            int bufferStruct = *(int*)(workspace->bufferPtr);
            if (*(unsigned int*)(bufferStruct + 0x1c) < totalLen) {
                if (totalLen < 0x20) totalLen = 0x20;
                int newBuffer = allocateMemory(*(unsigned int*)(bufferStruct + 0x1c));
                *(int*)(bufferStruct + 0x18) = newBuffer;
                *(unsigned int*)(bufferStruct + 0x1c) = totalLen;
            }
            
            int outBuf = *(int*)(bufferStruct + 0x18);
            int offset = 0;
            int remaining = operandsConsumed;
            // Copy all string contents from consecutive entries into output buffer
            int* srcEntry = (int*)(currentEntry + operandsConsumed * -2 + 1); // start from the last string in chain
            while (remaining > 0) {
                size_t len = *(size_t*)(*srcEntry + 0xc);
                memcpy((void*)(outBuf + offset), (void*)(*srcEntry + 0x10), len);
                remaining--;
                offset += len;
                srcEntry += 2; // move to previous entry
            }
            
            // Replace entire chain with a single string entry at the position of the first consumed string
            unsigned int* resultEntry = (unsigned int*)(currentEntry + operandsConsumed * -8);
            *resultEntry = 4;
            *((unsigned int*)resultEntry + 1) = internString(workspace, outBuf);
        }
    } while (true);
}