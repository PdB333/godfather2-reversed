// FUNC_NAME: EARSObject::constructFromParams
void EARSObject::constructFromParams(CreationParams* creationParams) 
{
    // Call base constructor (presumably EARSObject base class init)
    BaseClass::constructor();

    // Set vtable pointer to this class's vtable
    this->vtable = &gVtable_EARSObject; // PTR_FUN_00e377a0

    char initFlag = *(char*)((int)this + 0x0D);
    if (initFlag == '\0') 
    {
        // Store creation parameters pointer at this+0x28
        this->creationParams = creationParams;

        // Get thread-local storage pointer (FS:[0x2C])
        int tlsBase = *(int*)(__readfsdword(0x2C) + 0x2C); // Windows TLS
        int threadIndex = *(int*)(tlsBase + 8); // Some per-thread index

        // Access a dynamic data block at this->dataPtr (offset 0x10)
        int* dataBlock = (int*)(this->dataPtr + 0x10 + threadIndex * 4); // + threadIndex*4

        // Fill the data block with constant values from DAT_00e2b1a4
        int constant = DAT_00e2b1a4; // Some engine constant (likely a float or pattern)
        dataBlock[0] = constant;
        dataBlock[1] = 0;
        dataBlock[2] = 0;
        dataBlock[3] = 0;
        dataBlock[4] = 0;
        dataBlock[5] = constant;
        dataBlock[6] = 0;
        dataBlock[7] = 0;
        dataBlock[8] = 0;
        dataBlock[9] = 0;
        dataBlock[10] = constant;
        dataBlock[11] = 0;

        // Handle translation/accumulation based on creationParams flags
        int flags = creationParams[9]; // +0x24 in param struct
        if ((flags & 0x02) == 0) 
        {
            // Not additive mode
            if ((flags & 0x04) != 0) 
            {
                // Copy position offset to this->dataPtr + 0x40 + threadIndex
                int* dest = (int*)(this->dataPtr + 0x40 + threadIndex * 4);
                dest[0] = creationParams[0x0B]; // x
                dest[1] = creationParams[0x0C]; // y
                dest[2] = creationParams[0x0D]; // z
            }
        }
        else 
        {
            // Additive mode: accumulate values
            float* addDest = (float*)(this->dataPtr + 0x40 + threadIndex * 4);
            *addDest += (float)creationParams[0x0B];
            addDest[1] += (float)creationParams[0x0C];
            addDest[2] += (float)creationParams[0x0D];
        }

        // Set some internal fields
        this->field_0x2C = 0; // unaff_EDI[0xb]
        this->field_0x30 = 0; // unaff_EDI[0xc]
        this->field_0x34 = creationParams[0x0E]; // unaff_EDI[0xd]
        this->field_0x38 = constant; // uVar5 from DAT_00e2b1a4

        // Process first vector (creationParams[0-3]) as a resource hash
        uint hash1 = 0;
        if (creationParams[0] != 0 || creationParams[1] != 0 || 
            creationParams[2] != 0 || creationParams[3] != 0) 
        {
            hash1 = computeHash(); // FUN_004e9270
            if (hash1 != 0 && hash1 != 0xFFFFFFFF && hash1 < 0x1000 && 
                hash1 * 0x38 != 0xEED0D8) // -0x11a0f28 = 0xEE5F0D8? Actually 0x1000*0x38=0x38000, so this check is weird. Keep as is.
            {
                // Access global resource array and increment reference count
                ResourceEntry* resEntry = *(ResourceEntry**)(0x11a0f38 + hash1 * 0x38);
                if (resEntry != nullptr) 
                {
                    resEntry->refCount++;
                }
            }
        }

        // Process second vector (creationParams[4-7]) similarly
        uint hash2 = 0;
        if (creationParams[4] != 0 || creationParams[5] != 0 || 
            creationParams[6] != 0 || creationParams[7] != 0) 
        {
            hash2 = computeHash(); // FUN_004e9270
            if (hash2 != 0 && hash2 != 0xFFFFFFFF && hash2 < 0x1000 && 
                hash2 * 0x38 != 0xEED0D8) 
            {
                ResourceEntry* resEntry = *(ResourceEntry**)(0x11a0f38 + hash2 * 0x38);
                if (resEntry != nullptr) 
                {
                    resEntry->refCount++;
                }
            }
        }

        // Call final initialization with many parameters
        int paramA = this->field_0x14;   // unaff_EDI[5]
        int paramB = *(int*)(this->field_0x04 + 0x10); // unaff_EDI[1] + 0x10
        int paramC = this->dataPtr;      // unaff_EDI[4]
        int paramD = creationParams;     // same as stored

        // Set up a temporary structure at DAT_01206880 + 0x14
        int* tempPtr = (int*)(DAT_01206880 + 0x14);
        *(void***)tempPtr = &gVtable_01124e68; // PTR_FUN_01124e68
        *tempPtr = (int)tempPtr + 4; // increment pointer

        finalizeInit(this, creationParams, paramB, paramC, paramA, hash1); // FUN_004f56c0
    }
}