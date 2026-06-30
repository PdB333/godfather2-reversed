// FUNC_NAME: StreamBufferManager::initialize
void StreamBufferManager::initialize()
{
    // Set up vtable pointers for multiple base classes (offset 0 and 4)
    this->vtable0 = &g_vtable_StreamBufferManagerBase1;   // PTR_LAB_00e444a0
    this->vtable1 = &g_vtable_StreamBufferManagerBase2;   // PTR_LAB_00e444bc

    // Initialize constants
    this->someFlags = 1;                                   // unaff_ESI[2] = 1
    this->bufferSize = 480000;                             // unaff_ESI[4] = 480000
    this->channelCount = 0x10;                             // unaff_ESI[5] = 0x10

    // Allocate a large buffer (likely PCM audio data)
    int allocFlags[3] = { 2, 0x10, 0 };                    // local_c, local_8, local_4
    this->audioBuffer = (uint8_t*)FUN_009c8ef0(480000, allocFlags);  // unaff_ESI[3]

    // Allocate internal stream object (size 0x520 = 1312 bytes)
    int internalSize = 0x520;
    int* internalObj = (int*)FUN_009c8e50(internalSize);
    if (internalObj)
    {
        // Initialize the internal object with the buffer and parameters
        internalObj = FUN_00643f20(this->audioBuffer, this->bufferSize, 0, 0, 0, 0);
    }
    this->stream = internalObj;                            // unaff_ESI[6]

    if (internalObj)
    {
        // Configure stream flags and timeouts
        *(uint8_t*)(internalObj + 0x46d) = 0;               // active flag = false
        *(int*)(internalObj + 0x494) = 0x7fffffff;          // max play time
        *(int*)(internalObj + 0x490) = 0;                   // start offset

        // Lock the stream's critical section
        CRITICAL_SECTION* pCS = *(CRITICAL_SECTION**)(internalObj + 0x4e8);
        if (pCS)
        {
            EnterCriticalSection(pCS);
            // Adjust debug info (likely a flag or refcount manipulation)
            pCS[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&pCS[1].DebugInfo->Type + 1);
        }

        // Call internal method to finalize initialization
        FUN_00647b20(internalObj);

        // Clear all bits except the low bit (retain some flag)
        *(uint32_t*)(internalObj + 4) &= 1;

        if (pCS)
        {
            // Restore debug info and leave critical section
            pCS[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&pCS[1].DebugInfo[-1].SpareWORD + 1);
            LeaveCriticalSection(pCS);
        }

        // Store a callback pointer and back-pointer to this manager
        *(void**)(internalObj + 0x4ac) = &g_streamCallbackFunction;  // LAB_0066d6d0
        *(void**)(internalObj + 0x4b0) = this;
    }
}