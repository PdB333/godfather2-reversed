// FUNC_NAME: ResourceTableParser::parseDefinitionLine

void __cdecl ResourceTableParser::parseDefinitionLine(ResourceTable* container, char* line)
{
    char delimiters[4]; // +0x00: token delimiters "\t\n "
    char* token;
    int formatVersion;
    char* strToken;
    char* hashStr;
    byte* hashStrPtr;
    ResourceTableEntry* entry;
    int hashValue;
    uint ch;
    char* pairStr;
    byte ch2;

    builtin_strncpy(delimiters, "\t\n ", 4);
    formatVersion = -1;
    token = _strtok(line, delimiters);
    FID_conflict__sscanf(token, "%d\n", &formatVersion);
    if (formatVersion != 4) {
        return; // Ignore lines not matching expected format version
    }

    // Parse the second token (a flag character '0'/'1')
    token = _strtok(NULL, delimiters);
    char flagChar = *token;

    // Parse the third token (a string identifier)
    token = _strtok(NULL, delimiters);

    // Register the string (likely resource name)
    FUN_004d3bc0(token);
    FUN_004d5570(); // Free temporary string? Actually this might be misnamed.

    // Parse the fourth token (a hashable string)
    hashStr = _strtok(NULL, delimiters);
    hashStrPtr = (byte*)hashStr;

    // Compute hash of the hashStr (EA-style lowercase hash with factor 0x1003f)
    hashValue = 0;
    if (hashStrPtr != NULL) {
        ch2 = *hashStrPtr;
        if (ch2 != 0) {
            byte* hashIter = hashStrPtr;
            do {
                ch = (uint)ch2;
                hashIter++;
                if (ch - 0x41 < 0x1a) {
                    ch = ch + 0x20; // Convert uppercase to lowercase
                }
                hashValue = hashValue * 0x1003f + ch;
                ch2 = *hashIter;
            } while (ch2 != 0);
        }
    }

    // Peek at the next token (might be part of the pair loop)
    pairStr = _strtok(NULL, delimiters);

    // Register the hash string and then free? (seems to be a pattern)
    FUN_004d3bc0(hashStr);
    FUN_004d5570();

    // Allocate a new ResourceTableEntry (size 0x28 bytes)
    entry = (ResourceTableEntry*)FUN_009c8e50(0x28);
    if (entry != NULL) {
        // Initialize entry fields
        entry->field0 = 0;
        entry->field1 = 0;
        entry->field2 = 0;
        entry->field3 = 0;
        entry->hash = 0; // field4 initially zeroed, later set
        entry->flagByte1 = 0;
        entry->flagByte2 = 0;
        entry->containerPtr = container; // field6: pointer to parent container
        entry->subEntriesArray = NULL; // field7: dynamic array pointer
        entry->subEntriesCount = 0;    // field8
        entry->subEntriesCapacity = 0; // field9

        // Increment reference count on container? (container has a ref count at offset 0)
        FUN_00412910();
        (*(int*)entry->containerPtr)++; // Increment ref count at container's first int

        // Use default base path if none provided (local_18 expected to be set externally)
        if (basePath == NULL) {
            basePath = &DAT_0120546e; // empty string location
        }
        FUN_004d3d90(basePath);
        FUN_004d53a0(0xd); // Log or debug call

        // Store the computed hash and flag
        entry->hash = hashValue;
        entry->isEnabled = (flagChar == '1'); // bool at offset 0x14

        // Add entry to container's dynamic array (container has fields: array@+0x20c, count@+0x210, capacity@+0x214)
        int currentCount = *(int*)(container + 0x210);
        int currentCapacity = *(int*)(container + 0x214);
        if (currentCount == currentCapacity) {
            // Grow array if needed
            int newCapacity;
            if (currentCapacity == 0) {
                newCapacity = 1;
            } else {
                newCapacity = currentCapacity * 2;
            }
            FUN_00412b60(newCapacity); // Resize container's array
        }
        undefined4* arraySlot = (undefined4*)(*(int*)(container + 0x20c) + currentCount * 4);
        *(int*)(container + 0x210) = currentCount + 1;
        if (arraySlot != NULL) {
            *arraySlot = (undefined4)entry;
        }

        // Now parse the remaining token pairs: string + hex value
        byte* pathBuffer = NULL;
        int pathLen = 0;
        int pathCap = 0;
        code* freeFunc = NULL; // function pointer for memory deallocation

        if (pairStr != NULL) {
            do {
                // Grow subEntries array if needed
                int subCount = entry->subEntriesCount;
                int subCap = entry->subEntriesCapacity;
                if (subCount == subCap) {
                    int newSubCap;
                    if (subCap == 0) {
                        newSubCap = 1;
                    } else {
                        newSubCap = subCap * 2;
                    }
                    FUN_00412af0(newSubCap); // Resize subEntries array
                }
                undefined4* subArraySlot = (undefined4*)(entry->subEntriesArray + entry->subEntriesCount * 8);
                if (subArraySlot != NULL) {
                    *subArraySlot = 0xfe16702f; // Sentinel value
                }
                subArraySlot = (undefined4*)(entry->subEntriesArray + entry->subEntriesCount * 8);
                entry->subEntriesCount = entry->subEntriesCount + 1;

                // Reset path buffer if previously used
                if ((pathCap != 0) && (pathLen != 0)) {
                    *pathBuffer = 0;
                    pathLen = 0;
                }

                // Build full path: basePath + "\\" + pairStr
                if (basePath == NULL) {
                    basePath = &DAT_0120546e; // empty string
                }
                FUN_004d4ad0(&pathBuffer, "%s\\%s", basePath, pairStr);

                // Compute hash of the full path (lowercase)
                byte* hashSrc = pathBuffer;
                if (hashSrc == NULL) {
                    hashSrc = &DAT_0120546e;
                }
                int pathHash = 0;
                if (hashSrc != NULL) {
                    ch2 = *hashSrc;
                    while (ch2 != 0) {
                        ch = (uint)ch2;
                        hashSrc++;
                        if (ch - 0x41 < 0x1a) {
                            ch = ch + 0x20;
                        }
                        pathHash = pathHash * 0x1003f + ch;
                        ch2 = *hashSrc;
                    }
                }
                subArraySlot[1] = pathHash; // Store hash in second int of subEntry

                // Parse the hex value from the next token
                char* valueToken = _strtok(NULL, delimiters);
                FID_conflict__sscanf(valueToken, "0x%x", &subArraySlot[0]);

                // Proceed to next pair
                pairStr = _strtok(NULL, delimiters);
            } while (pairStr != NULL);

            // Free the path buffer if allocated
            if (pathBuffer != NULL) {
                if (freeFunc != NULL) {
                    freeFunc(pathBuffer);
                }
            }
        }

        // Free the basePath string if it was from allocation
        if (basePath != NULL) {
            if (freeFunc != NULL) {
                freeFunc(basePath);
            }
        }
        // Another possible free for local_18 (not shown in decompiled but exists)
        if (basePath2 != NULL) {
            if (freeFunc != NULL) {
                freeFunc(basePath2);
            }
        }
    }
}