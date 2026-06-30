// FUNC_NAME: Animation::decompressVertices
// Address: 0x0058a330
// Role: Decompresses animation vertex data from ushort deltas into float positions.
//   Blends compressed delta data with base float data, outputting to a destination buffer.
//   Uses a pseudo-random decision (based on __aullshr result) to determine which components
//   are delta-compressed vs. direct copy.

void __fastcall Animation::decompressVertices(float *outPositions, int startVertex, int endVertex)
{
    float scaleFactor = DAT_00e445cc; // global scaling factor for ushort deltas

    int currentVertex = this->m_currentVertexIndex; // +0x64
    ushort *pCompressed = this->m_pCompressedData; // +0x58
    float *pBase = this->m_pBaseData; // +0x5c

    // First phase: skip vertices from current to startVertex (without output)
    while (currentVertex < startVertex)
    {
        currentVertex = this->m_currentVertexIndex;
        uint64_t randVal = __aullshr();          // generate random 64-bit value
        uint32_t selector = (uint32_t)(randVal & 3);
        if ((selector - 1) < 3) // selector != 0? Actually if (uVar2 & 3) - 1 < 3 (i.e., !=0 if uVar2&3 == 1,2,3)
        {
            // Skip 2 ushorts (one delta? but no output)
            pCompressed += 2;
        }
        else
        {
            // Skip 6 ushorts (three deltas? but no output)
            pCompressed += 6;
        }
        pBase += 3; // advance base by one vertex (3 floats)
        currentVertex++;
        this->m_currentVertexIndex = currentVertex;
    }

    // Second phase: decompress and output from startVertex to endVertex
    while (true)
    {
        if (endVertex <= currentVertex)
        {
            break;
        }

        currentVertex = this->m_currentVertexIndex;
        uint64_t randVal = __aullshr();
        uint32_t selector = (uint32_t)(randVal & 3);

        ushort *compressed = pCompressed;
        float *base = pBase;

        switch (selector)
        {
        case 1:
            // Delta only in X, copy Y and Z from base
            outPositions[0] = (float)*compressed * scaleFactor + base[0];
            outPositions[1] = base[1];
            outPositions[2] = base[2];
            compressed += 1; // one ushort used
            break;
        case 2:
            // Delta only in Y
            outPositions[0] = base[0];
            outPositions[1] = (float)*compressed * scaleFactor + base[1];
            outPositions[2] = base[2];
            compressed += 1;
            break;
        case 3:
            // Delta only in Z
            outPositions[0] = base[0];
            outPositions[1] = base[1];
            outPositions[2] = (float)*compressed * scaleFactor + base[2];
            compressed += 1;
            break;
        default: // case 0
            // Delta in all three components
            outPositions[0] = (float)*compressed * scaleFactor + base[0];
            outPositions[1] = (float)compressed[1] * scaleFactor + base[1];
            outPositions[2] = (float)compressed[2] * scaleFactor + base[2];
            compressed += 3;
            break;
        }

        pBase = base + 3;
        pCompressed = compressed;

        currentVertex++;
        outPositions += 3;

        this->m_pCompressedData = pCompressed; // +0x58
        this->m_pBaseData = pBase; // +0x5c
        this->m_currentVertexIndex = currentVertex; // +0x64
    }
}