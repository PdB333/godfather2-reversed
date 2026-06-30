// FUNC_NAME: StreamManager::StreamManager
// 0x006f9e20 - Constructor for StreamManager, initializes 29 stream slots and other members
undefined4 * __fastcall StreamManager::StreamManager(StreamManager *this) {
    int i;
    int *pStringData;

    // Initialize base members
    this->m_isInitialized = 1;                                 // param_1[1]
    this->m_currentCount = 0;                                  // param_1[2]
    this->m_vtablePtr1 = &PTR_LAB_00d60a04;                    // param_1[3] - some vtable reference
    DAT_0112aa9c = this;                                       // global singleton pointer
    this->vtable = &PTR_FUN_00d60a1c;                          // *param_1 - vtable
    this->m_vtablePtr2 = &PTR_LAB_00d60a18;                    // param_1[3] overwritten - another vtable
    this->m_pResource1 = 0;                                    // param_1[4] - pointer to resource
    this->m_pResource2 = 0;                                    // param_1[5] - pointer to resource
    this->m_pStreamData1 = 0;                                  // param_1[6]
    this->m_pResource3 = 0;                                    // param_1[7]
    this->m_pStreamData2 = 0;                                  // param_1[8]
    this->m_pResource4 = 0;                                    // param_1[9]
    this->m_pResource5 = 0;                                    // param_1[10]
    this->m_pResource6 = 0;                                    // param_1[0xb]
    this->m_pResource7 = 0;                                    // param_1[0xc]

    // Initialize 29 stream slots (each 0x38 bytes)
    for (i = 0; i < 29; i++) {
        Stream *stream = &this->m_streams[i];                  // offset: 0x44 (param_1[0x11]) + i*0x38
        stream->m_active = 1;                                  // param_1[0x12] = 1
        stream->m_pad1 = 0;                                    // param_1[0x13] = 0
        stream->vtable = &PTR_FUN_00d60a08;                    // *puVar3 - vtable for stream
        stream->m_pCallback = 0;                               // param_1[0x15] = 0
        stream->m_pDataA = 0;                                  // param_1[0x16] = 0
        stream->m_pDataB = 0;                                  // param_1[0x17] = 0
        stream->m_pBuffer = 0;                                 // param_1[0x18] = 0
        stream->m_pBufferEnd = 0;                              // param_1[0x19] = 0
        stream->m_pReadPos = 0;                                // param_1[0x1a] = 0
        stream->m_pWritePos = 0;                               // param_1[0x1b] = 0

        // Initialize stream internals (calls something related to stream setup)
        FUN_006bccd0();

        stream->m_pad2 = 0;                                    // param_1[0x14] = 0
        stream->m_pad3 = 0;                                    // param_1[0x1c] = 0

        // If callback exists, call it (should be null here)
        if (stream->m_pCallback != 0) {
            (*(code *)stream->m_pCallback)();
        }

        // Reset callback and clean up pad fields
        stream->m_pCallback = 0;
        stream->m_pDataB = 0;                                  // param_1[0x17] = 0 (redundant)
        stream->m_pDataA = 0;                                  // param_1[0x16] = 0
        stream->m_pad4 = 0;                                    // param_1[0x1d] = 0

        // Set byte flags at the end of the stream structure
        *(char*)&stream->m_flags = 1;                          // low byte of [0x1e]
        *(char*)((int)&stream->m_pBuffer + 0x19) = 0;          // byte at offset 0x19 from m_pBuffer
    }

    // Allocate and store a string (or identifier)
    pStringData = (int *)FUN_004dddd0();                       // allocate some data
    this->m_string = (StringObj *)FUN_004265d0(&local, pStringData); // construct string
    this->m_stringData = pStringData;                          // store raw pointer
    (**(code **)(*pStringData + 8))();                         // call vtable function on the string

    // Additional member initialization
    this->m_pad5 = 0;                                          // param_1[0x1b6] = 0
    this->m_pad6 = 0;                                          // param_1[0x1b5] = 0
    this->m_pad7 = 0;                                          // param_1[0x1b7] = 0
    this->m_pResource2 = 0;                                    // param_1[5] = 0 (overwrites previous)

    // Release previously stored resources (cleanup from previous state)
    FUN_009c8f10(this->m_pResource1);                          // delete/release resource1
    this->m_pResource1 = 0;
    this->m_pStreamData1 = 0;                                  // param_1[6] = 0
    this->m_pStreamData2 = 0;                                  // param_1[8] = 0
    FUN_009c8f10(this->m_pResource3);                          // release resource3
    this->m_pResource3 = 0;
    this->m_pResource4 = 0;                                    // param_1[9] = 0

    // Clean up a potential pointer (offset 0x3C)
    if (this->m_pLuaObj != 0) {                                // param_1[0xf] = old pointer
        FUN_004daf90(this->m_pLuaObj);                         // release Lua object?
        this->m_pLuaObj = 0;
    }

    // Call final initialization function
    FUN_006f9c90();
    this->m_pad8 = 0;                                          // param_1[0xd] = 0

    return this;
}