// FUNC_NAME: ResizeElements (global array reallocation)
void ResizeElements(void)
{
    undefined4 *pNewArray;
    uint newCapacity;
    undefined4 *pOldArray;
    undefined4 *pWrite;
    // unaff_EDI is the requested new capacity (likely passed in EDI register)
    uint requestedCapacity = unaff_EDI;

    pNewArray = (undefined4 *)DAT_01218f28;           // g_pElements
    newCapacity = (uint)DAT_01218f30;                 // g_capacity
    if ((DAT_01218f30 < requestedCapacity) &&
        (pNewArray = (undefined4 *)FUN_009c8e80(requestedCapacity * 8), // allocate new block: each element is 8 bytes
         newCapacity = requestedCapacity,
         DAT_01218f28 != (undefined4 *)0x0))          // g_pElements old pointer
    {
        newCapacity = 0;
        pWrite = pNewArray;
        pOldArray = DAT_01218f28;                     // g_pElements
        if (DAT_01218f2c != 0)                        // g_size
        {
            do {
                if (pWrite != (undefined4 *)0x0) {
                    *pWrite = pOldArray[newCapacity * 2];          // copy element (8 bytes: two ints)
                    pWrite[1] = pOldArray[newCapacity * 2 + 1];
                    pOldArray = DAT_01218f28;                      // reload base (not strictly needed)
                }
                newCapacity = newCapacity + 1;
                pWrite = pWrite + 2;                               // advance by 2 ints (one element)
            } while (newCapacity < DAT_01218f2c);                  // g_size
        }
        FUN_009c8f10(pOldArray);                                   // free old array
        newCapacity = requestedCapacity;
    }
    DAT_01218f30 = newCapacity;                                     // update g_capacity
    DAT_01218f28 = pNewArray;                                        // update g_pElements
    return;
}