// FUNC_NAME: Resource::loadFromFile (tentative, 0x006fe750)
// This function loads a resource from a file, with various flag-driven behaviors
// It appears to handle textures, compressed data, or streaming assets
// Known class fields: +0x10 (type/index), +0x18 (stream handle), +0x24 (global pointer), +0x28 (some index), +0x2c (load flags), +0x35 (byte flag)

bool __thiscall Resource::loadFromFile(Resource *this, const char *filePath, uint loadFlags, int userData)
{
    bool result = false;
    char stringBuffer[10]; // local_78 used for temp string building
    int iVar1;
    uint uVar2;
    int iVar3;
    char cVar4;
    int iVar5;
    char *stringPtr;
    undefined8 streamId;
    undefined4 streamId2;
    undefined4 local_8c;
    char *autoFreePtr;
    undefined4 autoFreeFields[2];
    code *destructorCallback;
    byte local_4f;
    undefined4 local_48;
    undefined4 local_44;
    undefined1 auStack_2c[4];
    undefined1 auStack_28[24];
    int thisPtr;
    undefined1 auStack_c[12];

    memset(stringBuffer, 0, sizeof(stringBuffer));
    if ((this->m_streamHandle == 0) && (filePath != NULL))
    {
        // Attempt to open the file via a manager or loader
        iVar5 = FUN_00455f50(filePath, 0, 0); // likely a file existence check or open
        if (iVar5 != 0)
        {
            // Possibly init string formatting machinery
            FUN_005e30c0(); 
            cVar4 = FUN_004a84d0(stringBuffer, iVar5); // likely sprintf or path conversion
            if (cVar4 != '\0')
            {
                this->m_loadFlags = loadFlags;
                iVar3 = DAT_0112a9f4; // global base pointer (e.g., texture manager)
                stringBuffer[0] = &LAB_006fdc30; // set vtable pointer? (constant)

                // Determine if compressed or special format based on flags
                if ((loadFlags & 0xc4) == 0) // bits 2,6,7 clear => uncompressed
                {
                    local_4f = 0;
                }
                else
                {
                    local_4f = 1;
                    if ((loadFlags & 0x100) == 0) // bit8 clear
                    {
                        if ((loadFlags & 0x10) == 0) // bit4 clear
                        {
                            local_48 = _DAT_00d5780c;  // global constants for format
                            local_44 = DAT_00d5f53c;
                        }
                        else
                        {
                            local_48 = DAT_00d5eee4;
                            local_44 = DAT_00d5efa4;
                        }
                    }
                }

                thisPtr = (int)this;
                FUN_006fbe70(userData, auStack_2c, auStack_28); // parse extra options

                // If flag 0x8 (bit3) set, attempt to allocate a slot in a pool
                if ((loadFlags & 8) != 0)
                {
                    cVar4 = FUN_006fd0a0(); // check if slot available
                    if (cVar4 != '\0')
                    {
                        int *pIndex = (int *)((int)this + 0x28); // m_slotIndex field
                        cVar4 = FUN_006fbef0(pIndex); // get next free slot
                        if ((cVar4 != '\0') && (*pIndex != -1))
                        {
                            int *pSlot = (int *)(*pIndex * 0x58 + 0x78 + iVar3); // slot base
                            if (pSlot != NULL)
                            {
                                if (*pSlot == 0)
                                {
                                    *pSlot = 1; // mark as in use
                                    pSlot[1] = 0;
                                }
                                pSlot[9] = userData; // store user data
                                FUN_006fd660(*pIndex); // finalize slot allocation
                            }
                        }
                    }
                }

                this->m_globalData = DAT_01205210; // store some global
                this->m_byteField = 0;

                // Create automatic free structure (like unique_ptr with custom deleter)
                autoFreePtr = NULL;
                autoFreeFields[0] = 0;
                autoFreeFields[1] = 0;
                destructorCallback = NULL;

                cVar4 = FUN_004a8460(&autoFreePtr, iVar5, 0); // allocate memory for stream
                result = false;
                if (cVar4 != '\0')
                {
                    stringPtr = autoFreePtr;
                    if (autoFreePtr == NULL)
                    {
                        stringPtr = &DAT_0120546e; // default empty string
                    }
                    cVar4 = FUN_005e2a80(&local_8c, stringPtr, stringBuffer); // open stream (returns handle)
                    if (cVar4 == '\0')
                    {
                        FUN_006fd030(); // cleanup on failure
                    }
                    else
                    {
                        uVar2 = this->m_loadFlags;
                        this->m_streamHandle = local_8c; // store stream handle

                        if ((uVar2 & 0x40) == 0) // bit6 clear
                        {
                            if ((char)uVar2 < '\0') // bit7 set (sign bit)
                            {
                                cVar4 = FUN_006fcf20(); // prepare something
                                if (cVar4 == '\0')
                                {
                                    undefined8 *pStreamInfo = (undefined8 *)FUN_00424fb0(auStack_c, 0); // get stream identifier
                                    streamId = *pStreamInfo;
                                    streamId2 = *(undefined4 *)(pStreamInfo + 1);
                                }
                                FUN_005e2ce0(this->m_streamHandle, &streamId); // associate identifier
                                result = true;
                            }
                            else
                            {
                                // If there's a previous data and flags match, possibly copy over
                                if ((this->m_type != 0) && (this->m_type != 0x48) && ((uVar2 & 4) != 0))
                                {
                                    if (this->m_type == 0)
                                    {
                                        iVar5 = 0;
                                    }
                                    else
                                    {
                                        iVar5 = this->m_type - 0x48;
                                    }
                                    int *pCopyTarget = (int *)FUN_0046a1f0(iVar5, 0x38523fc3); // find copy target
                                    if (pCopyTarget != NULL)
                                    {
                                        iVar5 = FUN_00471610(); // get some offset (maybe size)
                                        FUN_005e2ce0(this->m_streamHandle, iVar5 + 0x30); // write to stream
                                        if ((this->m_loadFlags & 0x20) == 0) // bit5 clear
                                        {
                                            undefined4 uVar9 = (**(code **)(*pCopyTarget + 0x58))(); // call a method on target
                                            FUN_005e2d30(this->m_streamHandle, uVar9); // set something on stream
                                        }
                                    }
                                }
                                result = true;
                            }
                        }
                        else // bit6 set
                        {
                            FUN_00424fb0(&streamId, 0); // get stream id
                            FUN_005e2ce0(this->m_streamHandle, &streamId); // associate
                            result = true;
                        }
                    }
                }
                if (autoFreePtr != NULL)
                {
                    destructorCallback(autoFreePtr); // free if custom deleter exists
                }
            }
        }
    }
    return result;
}