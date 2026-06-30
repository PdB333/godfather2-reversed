// FUNC_NAME: ResourceManager::acquireOrCreateResource
uint* ResourceManager::acquireOrCreateResource(uint resourceId, ResourceDescriptor* descriptors, int descriptorCount)
{
    // Hash table lookup for existing resource
    if (resourceId != 0)
    {
        int* bucketHead = gResourceHashTable[resourceId & 0x1FFF];
        for (int* entry = bucketHead; entry != nullptr; entry = (int*)entry[4])
        {
            if (entry[3] == (int)resourceId)
            {
                if (entry != nullptr)
                {
                    uint* data = (uint*)entry[2];
                    if (data != nullptr)
                    {
                        // Found: increment refcount and return
                        if (bucketHead == nullptr)
                            return data;

                        // Find the bucket head again to lock
                        while (bucketHead[3] != (int)resourceId)
                        {
                            bucketHead = (int*)bucketHead[4];
                            if (bucketHead == nullptr)
                                return data;
                        }
                        if (bucketHead == nullptr)
                            return data;

                        LOCK();
                        *bucketHead += 1;
                        UNLOCK();
                        return data;
                    }
                }
                break;
            }
        }
    }

    // Get internal manager data
    int* mgr = getResourceManagerInternal();
    if (mgr == nullptr)
        return nullptr;

    int totalSubSize = 0;
    if (descriptorCount > 0)
    {
        // Compute total size needed for sub-resource data (size categories: 0, 0x10, 0x40)
        int* subEntries = *(int**)(mgr + 0x4C) + (*(int*)(mgr + 0x48) * 8);
        int remaining = descriptorCount;
        int* descPtr = descriptors;
        do {
            int* bucket = nullptr;
            int subSize = 0;
            switch (descPtr[1]) {
                default: subSize = 0; break;
                case 1: case 2: case 3: subSize = 0x10; break;
                case 4: subSize = 0x40; break;
            }
            while (true)
            {
                int* base = *(int**)(mgr + 0x4C);
                if (bucket != nullptr)
                    base = bucket + 8;
                bucket = base;
                if (subEntries <= bucket) break;
                while (*bucket != *descPtr) {
                    bucket += 8;
                    if (subEntries <= bucket) goto nextDesc;
                }
                totalSubSize += subSize;
            }
nextDesc:
            descPtr += 0x12; // each descriptor is 0x12 ints (72 bytes)
            remaining--;
        } while (remaining != 0);
    }

    int baseSubCount = *(int*)(mgr + 0x48); // number of pre-allocated sub-entries
    int headerSize = baseSubCount * 0x20;   // each sub-entry is 0x20 bytes

    // Allocate memory for resource: header (0x18 dwords = 0x60) + sub-resource array + data
    AllocContext allocCtx;
    allocCtx.flags = 2;
    allocCtx.align = 0x10;
    allocCtx.result = nullptr;
    uint* resource = (uint*)(**(code**)*gGlobalAllocator)(headerSize + 0x60 + totalSubSize, &allocCtx);
    uint* subArray = resource + 0x18;             // +0x60 bytes from start
    uint* subData = subArray + allocCtx.subCount * 8; // each sub-entry is 8 dwords (0x20)

    if (resource != nullptr)
    {
        // Copy initial header from stack (0x18 dwords)
        uint* src = (uint*)&allocCtx;
        uint* dst = resource;
        for (int i = 0x18; i > 0; i--)
        {
            *dst++ = *src++;
        }
    }

    resource[0x0C] = resourceId;              // +0x30: resource ID
    resource[0x0D] = allocCtx.subType;        // +0x34: subtype/category
    resource[0x0F] = (uint)(short)mgr;        // +0x3C: low word = manager index
    *(short*)(resource + 0x0E + 1) = (short)headerSize; // +0x3A: headerSize
    resource[0x13] = (uint)subArray;          // +0x4C: pointer to sub-array
    resource[0x14] = (uint)subData;           // +0x50: pointer to sub-data

    // Clear sub-resource type offsets (5 pairs of byte ranges)
    uint* p = resource + 3;
    for (int i = 5; i > 0; i--)
    {
        *p = 0;
        if (*(int*)((int)&allocCtx - (int)resource + (int)p) != 0)
            *p = 0;
        p += 2;
    }

    // Copy sub-resource entries from allocCtx (if any)
    if (allocCtx.subCount > 0)
    {
        uint* srcSub = (uint*)allocCtx.subArrayPtr;
        uint* dstSub = subArray;
        for (uint i = 0; i < allocCtx.subCount; i++)
        {
            // Copy 0x20 bytes (8 dwords) per sub-entry
            *(undefined8*)dstSub = *(undefined8*)srcSub;
            *(undefined8*)(dstSub + 2) = *(undefined8*)(srcSub + 1);
            *(undefined8*)(dstSub + 4) = *(undefined8*)(srcSub + 2);
            uint extra = *(uint*)((int)srcSub + 0x1C);
            dstSub[6] = *(uint*)(srcSub + 3);
            dstSub[7] = extra;

            // If sub-resource is of type 6 and has a valid index, increment its reference count
            if ((char)dstSub[3] == 6)
            {
                uint idx = dstSub[4];
                if (idx != 0xFFFFFFFF && idx < 0x1000)
                {
                    int* objDesc = (int*)(gObjectDescriptorArray + idx * 0x38); // each descriptor 0x38 bytes
                    if (objDesc != nullptr)
                    {
                        *objDesc += 1; // increment reference
                    }
                }
            }

            srcSub += 8; // advance by 0x20 bytes
            dstSub += 8;
        }
    }

    // Now link the descriptors to sub-resource data
    uint* dataPtr = subData;
    if (descriptorCount > 0)
    {
        uint* curDesc = (uint*)descriptors;
        int remaining = descriptorCount;
        do {
            int* bucket = nullptr;
            while (true)
            {
                if (bucket == nullptr)
                    bucket = (int*)resource[0x13]; // subArray
                else
                    bucket += 8;
                int* end = (int*)(resource[0x12] * 0x20 + resource[0x13]); // subArray + subCount*0x20
                if (end <= bucket) break;
                while (*bucket != *curDesc) {
                    bucket += 8;
                    if (end <= bucket) goto nextDesc2;
                }
                // Found matching sub-entry
                int offset = (int)(bucket - (int*)resource[0x13]) >> 5; // index in sub-array
                uint sizeCategory = 0;
                for (int k = 0; k < 5; k++)
                {
                    byte low = *(byte*)((int)resource + 0x3E + k);
                    byte high = *(byte*)((int)resource + 0x43 + k);
                    if (low <= offset && offset < high)
                    {
                        sizeCategory = resource[2 + k * 2]; // from resource+2, spaced by 2 dwords
                        break;
                    }
                }
                int addSize = 0;
                switch ((char)bucket[3])
                {
                    default: addSize = 0; break;
                    case 1: case 2: case 3: addSize = 0x10; break;
                    case 4: addSize = 0x40; break;
                }
                bucket[4] = (int)dataPtr; // set data pointer
                releaseResourceReference(sizeCategory);
                dataPtr = (uint*)((int)dataPtr + addSize);
            }
nextDesc2:
            curDesc += 0x12;
            remaining--;
        } while (remaining != 0);
    }

    // Process custom actions for each sub-resource type (5 types)
    uint* typePtr = resource + 3; // points to 5 pairs (type, something)
    for (int i = 5; i > 0; i--)
    {
        if (*typePtr != 0 && *typePtr != 1)
        {
            int* obj = (int*)typePtr[-1]; // some object pointer
            if (obj != nullptr)
            {
                char cVar3 = (**(code**)(*obj + 0x2C))(); // virtual call
                if (descriptorCount != 0)
                {
                    uint* desc = (uint*)(descriptors + 1); // skip first?
                    int remain = descriptorCount;
                    do {
                        int id = desc[-1]; // resource ID from descriptor
                        int match = compareResourceId(obj[4], id); // compare with obj's derived IDs
                        uint* matchedObj = nullptr;
                        if (match == 0)
                        {
                            if (obj[5] != 0)
                            {
                                match = compareResourceId(obj[5], id);
                                if (match != 0)
                                    matchedObj = (uint*)obj[5];
                            }
                        }
                        else
                        {
                            matchedObj = (uint*)obj[4];
                        }
                        if (match != 0)
                        {
                            int type = *desc;
                            size_t dataSize = 0;
                            switch (type)
                            {
                                default: dataSize = 0; break;
                                case 1: case 2: case 3: dataSize = 0x10; break;
                                case 4: dataSize = 0x40; break;
                            }
                            if (cVar3 == 0) // not a callback?
                            {
                                if (dataSize == 0)
                                {
                                    if (type == 0)
                                    {
                                        // Direct pointer copy
                                        uint* srcPtr = (uint*)desc[1];
                                        resource->flags |= 0x40000; // mark as dirty?
                                        // Fall through to finalization
                                    }
                                }
                                else
                                {
                                    memset(&stackCopy, 0, dataSize);
                                    size_t copySize = 0;
                                    switch (type)
                                    {
                                        case 0: copySize = 4; break;
                                        case 1: copySize = 8; break;
                                        case 2: copySize = 0xC; break;
                                        case 3: copySize = 0x10; break;
                                        case 4: copySize = 0x40; break;
                                        default: copySize = 0;
                                    }
                                    memcpy(&stackCopy, desc + 1, copySize);
                                }
                            }
                            else
                            {
                                // Callback version
                                int stackId = desc[-1];
                                char stackType = (char)*desc;
                                uint* stackObj = matchedObj;
                                uint* stackCopy2 = (uint*)&stackCopy;
                                int stackMatch = match;
                                releaseResourceReference(obj);
                                if (stackType == 6)
                                {
                                    if (stackObj != nullptr && stackObj != (uint*)0xFFFFFFFF && (uint)stackObj < 0x1000)
                                    {
                                        int* objDesc = (int*)(gObjectDescriptorArray + (int)stackObj * 0x38);
                                        if (objDesc != nullptr)
                                        {
                                            if (*objDesc == 1 && objDesc[2] == 3)
                                            {
                                                deallocateResource(objDesc[1], 0);
                                                stackObj = nullptr;
                                            }
                                            else
                                            {
                                                *objDesc = 2;
                                                stackObj = nullptr;
                                            }
                                        }
                                    }
                                    // Cleanup reference
                                    stackObj = nullptr;
                                }
                                else if (stackType == 0)
                                {
                                    // Direct pointer
                                    memset(&stackCopy2, 0, 0x10);
                                    *(undefined4*******)&stackCopy = (undefined4*******)(undefined4*)stackObj;
                                }
                            }
                        }
nextDesc3:
                        desc += 0x12;
                        remain--;
                    } while (remain != 0);
                }
            }
        }
        typePtr += 2;
        if (i == 1)
        {
            // Finalize: mark resource as having custom data
            *resource |= 0x40000;
            // Insert into hash table
            int* bucket = gResourceHashTable[resource[0x0D] & 0x1FFF];
            if (bucket != nullptr)
            {
                while (bucket[3] != (int)resource[0x0D])
                {
                    bucket = (int*)bucket[4];
                    if (bucket == nullptr)
                    {
                        releaseResourceInternal();
                        return resource;
                    }
                }
                if (bucket != nullptr)
                {
                    LOCK();
                    *bucket += 1;
                    UNLOCK();
                }
            }
            releaseResourceInternal();
            return resource;
        }
    }
}