// FUNC_NAME: BehaviorTreeLoader::parseNodes
void __thiscall BehaviorTreeLoader::parseNodes(void *this, unsigned int dataStream)
{
    int *piVar1;
    unsigned int *puVar2;
    unsigned int uVar3;
    unsigned int **ppuVar4;
    unsigned int **ppuVar5;
    bool bVar6;
    char bBitmaskMode; // local_64 - flag for bitmask iteration
    int *pBitmask; // local_60
    unsigned int *pDataArray; // local_5c
    uint index; // local_58
    uint count; // local_54
    unsigned int *currentNode; // local_50
    short indexShort; // local_4c
    unsigned int dataValue; // local_48
    unsigned int **iterator; // local_8

    // Begin deserialization with signature check (0x6b61526f = "kRaO")
    deserializeBegin(dataStream, 0x6b61526f);

    iterator = &this->nodeArray; // local_8 initially points somewhere (stack variable)
    while (true)
    {
        // Determine if we should continue iteration
        if (bBitmaskMode == '\0')
        {
            bVar6 = (*iterator == (unsigned int *)0x0); // pointer-based: stop at null
        }
        else
        {
            bVar6 = (index == count); // bitmask-based: stop at end
        }
        if (bVar6) break;

        // Select node pointer
        if (bBitmaskMode == '\0')
        {
            ppuVar5 = iterator; // use iterator directly
        }
        else
        {
            ppuVar5 = &currentNode; // in bitmask mode, use local variable
        }

        // Check if node has a relative offset type (0x25e3 = 9699)
        if (*(short *)((int)ppuVar5 + 6) == 0x25e3)
        {
            puVar2 = (unsigned int *)(uint)*(ushort *)(ppuVar5 + 1);
        }
        else
        {
            puVar2 = ppuVar5[1];
        }

        // Process node based on the resolved pointer
        if (puVar2 == (unsigned int *)0x0)
        {
            // Backward pointer or absolute address handling
            ppuVar5 = &currentNode;
            if (bBitmaskMode == '\0')
            {
                ppuVar5 = iterator;
            }
            if (*(short *)((int)ppuVar5 + 6) == 0x25e3)
            {
                if (*ppuVar5 == (unsigned int *)0x0)
                {
                    ppuVar5 = (unsigned int **)&DAT_00e2a89b; // fallback global
                }
                else
                {
                    ppuVar5 = (unsigned int **)((int)ppuVar5[2] + (int)*ppuVar5);
                }
            }
            else
            {
                ppuVar5 = ppuVar5 + 2;
            }

            piVar1 = (int *)((int)this + 0x50); // list at +0x50
            clearList(piVar1);
            initList(piVar1); // or resetList
            if ((ppuVar5 != (unsigned int **)0x0) && (*(char *)ppuVar5 != '\0'))
            {
                uVar3 = stringFromNode(ppuVar5);
                addStringToList(piVar1, uVar3);
                if (*piVar1 != 0)
                {
                    appendToStringArray((int)this + 0x3c, piVar1); // +0x3c is string array
                }
            }
        }
        else if (puVar2 == (unsigned int *)0x1)
        {
            // Special marker: store pointer for later use
            ppuVar5 = &currentNode;
            if (bBitmaskMode == '\0')
            {
                ppuVar5 = iterator;
            }
            *(unsigned int **)((int)this + 0x58) = ppuVar5[2]; // store at +0x58
        }

        // Advance iterator
        if (bBitmaskMode == '\0')
        {
            // Pointer-based advancement
            if ((int)index < 0)
            {
                // Backward linking: jump using offset
                iterator = (unsigned int **)((int)iterator + (int)*iterator);
                popNodeStack(); // FUN_0043b140
                // Note: iterator is updated but also local_8 (which is same as iterator) is set
                iterator = (unsigned int **)((int)iterator + (int)*iterator); // double advancement?
                // Actually the decompiled code sets local_8 = (undefined4**)((int)ppuVar4 + (int)*ppuVar4); then calls FUNCTION and does ppuVar4 = local_8 again.
                // This is messy; we reconstruct as best we can.
                // In the original, after the call, ppuVar4 is set to local_8 (which is the advanced pointer).
                // We'll just do pointer arithmetic.
            }
            else if ((int)index < (int)(count - 1))
            {
                index = index + 1;
                iterator = (unsigned int **)((int)iterator + (int)*iterator); // move to next sibling
            }
            else
            {
                // End of list, go to global sentinel (DAT_01163cf8)
                iterator = (unsigned int **)&DAT_01163cf8;
            }
        }
        else
        {
            // Bitmask-based advancement: simple index increment
            index = index + 1;
            if (index != count)
            {
                indexShort = (short)index;
                // Check if bit at this index is set
                if ((*(byte *)((int)pBitmask + (index >> 3)) & (byte)(1 << ((byte)index & 7))) == 0)
                {
                    dataValue = *pDataArray; // read next data value
                    currentNode = pDataArray; // node pointer is data array element
                    pDataArray = pDataArray + 1; // advance data
                }
                else
                {
                    currentNode = (unsigned int *)0x0;
                    dataValue = 0;
                }
            }
        }
    }
    return;
}