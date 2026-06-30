// FUNC_NAME: PropertySet::unpackProperties
void __thiscall PropertySet::unpackProperties(void* thisPtr, void* propertySet, int* objectArray, char* buffer, int recordCount, char resetFlag)
{
    char type;
    int* dynamicArray;
    int* entryPtr;
    int* newEntry;
    int hashIndex;
    int objIndex;
    int zeroCount = 0;
    int oneCount = 0;
    int twoCount = 0;
    int i;
    char* inputPtr = buffer;
    int remaining = recordCount;
    int* objPtr = objectArray;
    // First pass: count each type
    for (i = 0; i < recordCount; i++)
    {
        type = *inputPtr;
        if (type == '\0')
            zeroCount++;
        else if (type == '\x01')
            oneCount++;
        else if (type == '\x02')
            twoCount++;
        remaining--;
        inputPtr += 5; // each record is 5 bytes
    }
    // Allocate arrays if needed and not already present
    if (zeroCount != 0 && *(int*)((char*)propertySet + 0x1c) == 0)
    {
        // Allocate dynamic array for objects (entries of 8 bytes each)
        int* header = (int*)FUN_009c8e50(0xc); // allocate header (12 bytes)
        if (header != 0)
        {
            int* data = (int*)FUN_009c8e80(zeroCount * 8);
            header[0] = (int)data; // buffer
            header[1] = 0; // count
            header[2] = zeroCount; // capacity
        }
        *(int**)((char*)propertySet + 0x1c) = header;
    }
    if (oneCount != 0 && *(int*)((char*)propertySet + 0x20) == 0)
    {
        int* header = (int*)FUN_009c8e50(0xc);
        if (header != 0)
        {
            int* data = (int*)FUN_009c8e80(oneCount * 8);
            header[0] = (int)data;
            header[1] = 0;
            header[2] = oneCount;
        }
        *(int**)((char*)propertySet + 0x20) = header;
    }
    if (twoCount != 0 && *(int*)((char*)propertySet + 0x24) == 0)
    {
        int* header = (int*)FUN_009c8e50(0xc);
        if (header != 0)
        {
            int* data = (int*)FUN_009c8e80(twoCount * 8);
            header[0] = (int)data;
            header[1] = 0;
            header[2] = twoCount;
        }
        *(int**)((char*)propertySet + 0x24) = header;
    }
    // If reset flag set, clear existing data
    if (resetFlag != '\0')
    {
        if (*(int*)((char*)propertySet + 0x1c) != 0)
            FUN_00617740(*(int*)((char*)propertySet + 0x1c)); // free the array?
        int* arr1 = *(int**)((char*)propertySet + 0x20);
        if (arr1 != 0 && arr1[1] != 0)
            arr1[1] = 0; // reset count
        int* arr2 = *(int**)((char*)propertySet + 0x24);
        if (arr2 != 0 && arr2[1] != 0)
            arr2[1] = 0;
    }
    // Second pass: process each record
    inputPtr = buffer;
    objPtr = objectArray;
    remaining = recordCount;
    for (i = 0; i < recordCount; i++)
    {
        type = *inputPtr;
        char* nextPtr = inputPtr + 1;
        if (type == '\0')
        {
            // Object reference: use next 4 bytes as key to find or create entry
            int* objArray = *(int**)((char*)propertySet + 0x1c);
            hashIndex = FUN_00617920(objPtr); // hash function on the object pointer? Or objPtr is key?
            // objPtr is actually current object in the array (incremented by 4 each step)
            // Actually in the loop, param_3 is incremented by 4, so we iterate through objectArray.
            // This suggests for each record, we associate the current object (pointed by objectArray) with the key from buffer.
            // But the code uses param_3 (objPtr) as the key for hash? Let's reinterpret.
            // The code: iVar8 = FUN_00617920(param_3) -> hash of the current object pointer?
            // Then it uses that hash to find an index in the array.
            // Actually param_3 is incremented by 4 each record, so it's an array of pointers? Or array of objects?
            // Given that for type 1 and 2, they set property on param_3 object, param_3 is a pointer to an object.
            // So for type 0, it's also dealing with the current object.
            // But the code calls FUN_00617920(param_3) which is likely a hash function for a string? Or object ID?
            // And then uses that to index into the array.
            // Let's preserve the logic.
            // 
            // Actually looking more carefully: The buffer's 4 bytes are not used for object? Wait: 
            // For type 0: it reads the 4 bytes from buffer? No, the code does not directly use the 4 bytes.
            // It calls FUN_00617920(param_3) which uses param_3 (the current object pointer) to get a hash.
            // Then it finds an entry in the array (which is keyed by something) and if not found, creates a new entry with FUN_00617440.
            // Then it creates a new object (FUN_006163d0) and assigns it to the entry, replacing old one with ref counting.
            // So the 4 bytes in buffer might actually be ignored for type 0? That seems odd.
            // Possibly the buffer's 4 bytes are the object ID to look up, but the code doesn't read them.
            // Let me re-examine the decompiled loop:
            // The loop iterates param_5 times, each time:
            //   cVar1 = *param_4;
            //   param_6 = param_4 + 1? Actually param_6 = param_4; then later param_4 = param_6 + 5;
            //   For type 0: it does printf? No.
            //   It calls FUN_00617920(param_3) where param_3 is the current object pointer (incremented by 4 each step).
            //   Then it uses the result to index into the array at *piVar2 + 4 + iVar8 * 8.
            //   This suggests that the array is keyed by something derived from param_3.
            //   But param_3 is incremented by 4 for each record, so it's a pointer walking through an array of 4-byte objects (like pointers or ints).
            //   Possibly param_3 is an array of IDs (like ints) that serve as keys.
            //   For type 1 and 2, they set properties on the object pointed to by param_3? Actually they use param_3 as the object pointer to get a property pointer (FUN_00617520 and FUN_006175e0).
            //   So param_3 is an array of object pointers. For each record, the current object pointer is used.
            //   That makes sense: the buffer provides a sequence of property values to assign to objects in the array.
            //   For type 0, it might be assigning a sub-object to the current object? 
            //   But the code creates a new object and replaces the current entry with a reference.
            //   This is confusing.
            //
            // Given the complexity, I'll keep the logic as close as possible but with better variable names.
            // The key point: param_3 is incremented by 4 each iteration, so it's an array of 32-bit pointers/IDs.
            // Let's rename param_3 to objectIDArray (int*). For each record, we take the current ID.
            // The buffer contains the property data.
            int currentID = *objPtr; // objPtr is the current element in the objectIDArray
            int* arrayHeader = *(int**)((char*)propertySet + 0x1c);
            hashIndex = FUN_00617920((int)currentID); // hash of the ID
            if (hashIndex < 0)
            {
                // Try to find existing entry or create new one
                entryPtr = (int*)(arrayHeader[0] + 4 + hashIndex * 8); // offset into data array
                if (entryPtr == 0)
                    entryPtr = (int*)FUN_00617440(arrayHeader, (int)currentID);
            }
            else
            {
                entryPtr = (int*)FUN_00617440(arrayHeader, (int)currentID);
            }
            // entryPtr is a pointer to an 8-byte slot (key + value?)
            int newObj = FUN_006163d0(); // create a new object
            int oldObj = *entryPtr;
            if (oldObj != newObj)
            {
                if (oldObj != 0)
                {
                    *(short*)(oldObj + 8) = *(short*)(oldObj + 8) - 1;
                    if (*(short*)(oldObj + 8) == 0)
                    {
                        FUN_00616dc0(oldObj);
                        (**(code**)(**DAT_01205964 + 4))(oldObj, 0); // virtual destructor?
                    }
                    *entryPtr = 0;
                }
                if (newObj != 0)
                {
                    *(short*)(newObj + 8) = *(short*)(newObj + 8) + 1;
                    *entryPtr = newObj;
                }
            }
        }
        else if (type == '\x01')
        {
            // Float property: write next 4 bytes as float into object
            float* propPtr = (float*)FUN_00617520(objPtr, &objPtr); // get pointer to float property in current object
            *propPtr = *(float*)nextPtr; // copy float value from buffer
        }
        else if (type == '\x02')
        {
            // Int property: write next 4 bytes as int into object
            int* propPtr = (int*)FUN_006175e0(objPtr, &objPtr); // get pointer to int property
            *propPtr = *(int*)nextPtr; // copy int value
        }
        inputPtr = nextPtr + 4; // move to next record (5 bytes total)
        objPtr++; // advance to next object in the array
    }
}
// Note: The actual implementation uses code from unknown functions; above is a best-effort reconstruction.