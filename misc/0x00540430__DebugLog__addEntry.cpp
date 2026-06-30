// FUNC_NAME: DebugLog::addEntry
// Function address: 0x00540430
// Role: Inserts a new debug log node into a linked list. The node contains a category (4 dwords from EAX), data (4 dwords from param_2), and a message string (param_3). The list head is at +0x40.

struct DebugLogNode {
    char      m_nType;        // +0x00 (always 1)
    uint32_t  m_nCategory0;   // +0x04
    uint32_t  m_nCategory1;   // +0x08
    uint32_t  m_nCategory2;   // +0x0C
    uint32_t  m_nCategory3;   // +0x10
    uint32_t  m_nData0;       // +0x20
    uint32_t  m_nData1;       // +0x24
    uint32_t  m_nData2;       // +0x28
    uint32_t  m_nData3;       // +0x2C
    char      m_szMessage[128]; // +0x30 to +0xAF (127 chars + null)
    DebugLogNode* m_pNext;    // +0xB0
};

void __thiscall DebugLog::addEntry(uint32_t* a_pCategory, uint32_t* a_pData, const char* a_szMessage) {
    DebugLogNode* pNode = (DebugLogNode*)FUN_009c8e50(0xC0); // custom allocator, 0xC0 bytes
    if (pNode != nullptr) {
        // Fill with debug magic markers (filled before real data copied)
        pNode->m_nCategory0 = 0xBADBADBA;
        pNode->m_nCategory1 = 0xBEEFBEEF;
        pNode->m_nCategory2 = 0xEAC15A55;
        pNode->m_nCategory3 = 0x91100911;
    } else {
        pNode = nullptr;
    }

    // Traverse to last node in the linked list
    DebugLogNode* pLast = *(DebugLogNode**)((int)this + 0x40); // m_pFirstNode
    if (pLast != nullptr) {
        while (pLast->m_pNext != nullptr) {
            pLast = pLast->m_pNext;
        }
    }

    // Link new node at end of list
    if (*(DebugLogNode**)((int)this + 0x40) == nullptr) {
        *(DebugLogNode**)((int)this + 0x40) = pNode;
    } else {
        pLast->m_pNext = pNode;
    }

    // Copy category and data fields
    pNode->m_nType = 1;
    pNode->m_nCategory0 = a_pCategory[0];
    pNode->m_nCategory1 = a_pCategory[1];
    pNode->m_nCategory2 = a_pCategory[2];
    pNode->m_nCategory3 = a_pCategory[3];
    pNode->m_nData0 = a_pData[0];
    pNode->m_nData1 = a_pData[1];
    pNode->m_nData2 = a_pData[2];
    pNode->m_nData3 = a_pData[3];

    // Copy message string (up to 127 chars + null at +0xAF)
    const char* pSrc = a_szMessage;
    if (strlen(a_szMessage) > 0x7F) {
        // Fast copy in 4-byte chunks for first 124 bytes, then remaining 3 bytes
        uint32_t* pDestDword = (uint32_t*)((int)pNode + 0x30);
        for (int i = 0x1F; i != 0; --i) {
            *pDestDword = *(uint32_t*)pSrc;
            pSrc += 4;
            pDestDword++;
        }
        *(uint16_t*)pDestDword = *(uint16_t*)pSrc;
        *(char*)((int)pDestDword + 2) = pSrc[2];
        *(char*)((int)pNode + 0xAF) = '\0';
    } else {
        // Byte-by-byte copy until null terminator
        char* pDest = (char*)((int)pNode + 0x30);
        while (*pSrc != '\0') {
            *pDest++ = *pSrc++;
        }
        *pDest = '\0';
    }

    pNode->m_pNext = nullptr;
}