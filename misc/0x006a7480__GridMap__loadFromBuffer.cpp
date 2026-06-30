// FUNC_NAME: GridMap::loadFromBuffer
uint* __thiscall GridMap::loadFromBuffer(uint param_1, uint* param_2)
{
    uint* pHeader;
    uint* pData;
    uint* pDataEnd;
    uint width, height;
    uint* pDestRow;
    uint* pDestCol;
    uint* pDestBase;
    uint temp;

    // Allocate or obtain a buffer from the resource system
    pHeader = (uint*)FUN_0049c9c0();
    *(uint**)(param_1 + 0x430) = pHeader;          // m_pBuffer

    // Data starts after the 2-uint header (width, height)
    pData = pHeader + 2;
    *(uint**)(param_1 + 0x434) = pData;            // m_pDataStart

    // Calculate end pointer: base + (size from param_2->field_0x18 - 8)
    // param_2 is a pointer to a resource descriptor containing total data size at +0x18
    *(uint**)(param_1 + 0x438) = (uint*)(*(int*)(param_2 + 0x18) - 8 + (int)pData); // m_pDataEnd

    // Total data size = width * 0x24 (36 bytes per element)
    *(uint*)(param_1 + 0x43c) = *pHeader * 0x24;   // m_rowSize or m_elementSize

    // Read and clamp dimensions
    width = *pHeader;
    height = pHeader[1];

    if (width > 7)
        width = 8;
    if (height > 31)
        height = 32;

    *(uint*)(param_1 + 0x2c) = width;   // m_width
    *(uint*)(param_1 + 0x28) = height;  // m_height

    // Fill the 2D grid (stored at offset 0x30, stride 8 per row)
    if (height != 0)
    {
        pDestBase = (uint*)(param_1 + 0x30); // m_data[0][0]
        pDestRow = pDestBase;
        do
        {
            pDestCol = pDestRow;
            for (uint col = width; col != 0; col--)
            {
                if (pData < *(uint**)(param_1 + 0x438))
                {
                    // Read a 36-byte element and convert to a single uint
                    temp = FUN_004dafd0(pData);
                    *pDestCol = temp;
                    pData += 9; // advance by 9 uints (36 bytes)
                }
                else
                {
                    *pDestCol = 0;
                }
                pDestCol++;
            }
            // Move to next row (stride of 8 elements)
            pDestRow = pDestBase + 8;
            pDestBase = pDestRow;
            height--;
        } while (height != 0);
    }

    return pHeader;
}