// FUNC_NAME: ObjectManager::processPendingObject
bool ObjectManager::processPendingObject(uint index, int param1, char* outFlag)
{
    // outFlag is set to 1 if processing was done
    *outFlag = 0;

    // Validate index range (max 4096 objects)
    if (index < 0x1000)
    {
        // Array of structures at 0x011a0f28, each 0x38 bytes
        byte* entryBase = &g_objectArray[index * 0x38];
        int* objectPtr = (int*)(entryBase + 0x10); // pointer at offset 0x10

        if (entryBase != nullptr && *objectPtr != 0)
        {
            // Check if the entry's reference count (first byte) > 1
            if (entryBase != nullptr && *entryBase > 1)
            {
                // Check if the object's type field at offset 8 equals 3
                return *(int*)(*(int*)(entryBase + 0x10) + 8) == 3;
            }

            // Call a function to check if processing is allowed
            if (canProcessObject())
            {
                // Check thread-local storage: FS:[0x2c] -> TLS array, then field at +0x34
                // This likely checks if we are on the main thread
                if (*(int*)(**(int**)(__readfsdword(0x2c)) + 0x34) == 0)
                {
                    // Process the object with the given index and param1
                    processObject(index, param1);
                    *outFlag = 1;
                    return true;
                }
                else
                {
                    // Alternative processing path (e.g., defer to main thread)
                    deferProcessing();
                    *outFlag = 1;
                    return true;
                }
            }
        }
    }
    return false;
}