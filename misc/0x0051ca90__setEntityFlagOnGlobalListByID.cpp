// FUNC_NAME: setEntityFlagOnGlobalListByID

void __fastcall setEntityFlagOnGlobalListByID(undefined4 unused, int id)
{
    int* pNode = (int*)DAT_01205514;
    while (pNode != 0)
    {
        if (id == 0)
        {
            // Set flag on all nodes
            unsigned int* pFlags = (unsigned int*)(pNode + 3);   // offset +0x0C
            *pFlags |= 0x20000000;
        }
        else
        {
            int derivedId;
            int* pPtr = (int*)pNode[0x31];                      // offset +0xC4
            if (pPtr == 0)
                derivedId = 0;
            else
                derivedId = (int)pPtr - 0x48;                   // subtract 0x48 from pointer value

            if (id == derivedId)
            {
                unsigned int* pFlags = (unsigned int*)(pNode + 3);   // offset +0x0C
                *pFlags |= 0x20000000;
            }
        }
        pNode = (int*)pNode[5];                                 // offset +0x14, next node
    }
}