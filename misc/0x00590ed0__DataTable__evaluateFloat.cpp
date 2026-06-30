// FUNC_NAME: DataTable::evaluateFloat
float DataTable::evaluateFloat(KeyStruct* pKey, void* pUserData) {
    // Initialize stack pointers (likely part of a custom stack-based runtime)
    __initCustomRuntime(); // FUN_0058ab50

    // Ensure the local buffer is large enough (at least 256 slots)
    if (m_localStackSize < 0x100) {
        int baseIndex = 0;
        __resizeLocalStack(&baseIndex); // FUN_00591c00
    }

    // Store user data at a fixed offset in the local stack
    *reinterpret_cast<void**>(m_pLocalStack + 0x3fc) = pUserData;

    // Reverse-copy the integer array from pKey into the local stack (descending indices)
    int count = pKey->count; // signed byte at pKey+1
    int i = 0;
    if (count > 0) {
        uint32_t* pSrc = &pKey->values; // array at pKey+0xc
        do {
            uint targetIndex = 0xfe - i;
            // Expand local stack if target index is out of range
            if (m_localStackSize <= targetIndex) {
                int needSize = (targetIndex - m_localStackSize) + 1;
                if (needSize != 0) {
                    __expandLocalStack(m_localStackSize + needSize); // FUN_005822d0
                    uint newSize = needSize + m_localStackSize;
                    do {
                        uint32_t* pSlot = reinterpret_cast<uint32_t*>(m_pLocalStack + m_localStackSize * 4);
                        m_localStackSize++;
                        if (pSlot != nullptr) {
                            *pSlot = 0;
                        }
                    } while (newSize != m_localStackSize);
                }
            }
            uint32_t value = *pSrc;
            pSrc++;
            *reinterpret_cast<uint32_t*>(m_pLocalStack + targetIndex * 4) = value;
            i++;
        } while (i < count);
    }

    // Hash table lookup using keyHash from pKey
    HashTable* pTable = *reinterpret_cast<HashTable**>(m_hashTableField + 0x30); // via offset 0x70 from this
    uint32_t keyHash = pKey->hash; // uint32 at pKey+4
    uint32_t bucketIndex = keyHash % pTable->capacity;
    BucketNode* pNode = pTable->buckets[bucketIndex];

    while (pNode != nullptr) {
        if (pNode->hash == keyHash) {
            if (pNode != nullptr && pNode != reinterpret_cast<BucketNode*>(-4)) {
                uint8_t* pBytecode = reinterpret_cast<uint8_t*>(pNode->data); // pNode[2] is data pointer
                goto found;
            }
            break;
        }
        pNode = pNode->next;
    }
    pBytecode = nullptr;

found:
    if (pBytecode != nullptr) {
        float result = 0.0f;
        // Default float value (maybe from config)
        float defaultResult = DAT_00e2b1a4;
        // Interpret bytecode: first byte lower 6 bits is opcode index
        uint opcode = ((*pBytecode) & 0x3f);
        if (opcode < 0x23) {
            // Call opcode handler: (this, bytecode, &localStack)
            result = reinterpret_cast<OpcodeHandler>(gOpcodeTable[opcode])(this, pBytecode, &m_pLocalStack);
            defaultResult = result;
        }
        // Read target index from bytecode+2 (short)
        int16_t targetSlot = *reinterpret_cast<int16_t*>(pBytecode + 2);
        // Ensure local stack is large enough for this slot
        if (m_localStackSize <= static_cast<uint>(targetSlot)) {
            void* dummy = nullptr;
            __resizeLocalStack(&dummy); // FUN_00591c00
        }
        // Store the evaluated float into the local stack
        *reinterpret_cast<float*>(m_pLocalStack + targetSlot * 4) = defaultResult;
    }

    // Cleanup: destroy the local stack (custom destructors)
    (*(reinterpret_cast<void(__thiscall**)(void*, int)>(*m_pLocalStack + 4)))(m_pLocalStack, 0);
    if (m_localStackSize != 0) {
        (*(reinterpret_cast<void(__thiscall**)(uint32_t, int)>(*m_pStackContext + 4)))(m_localStackSize, 0);
    }
    (*(reinterpret_cast<void(__thiscall**)(void)>(*m_pStackContext + 0xc)))();

    // Return the computed float (unaff_retaddr corresponds to the local float)
    return unaff_retaddr; // this is actually the float value stored or computed
}