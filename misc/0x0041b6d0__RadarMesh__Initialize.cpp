// FUNC_NAME: RadarMesh::Initialize
void __fastcall RadarMesh::Initialize(int this)
{
    uint uVar8 = 0;
    bool bAlreadyInitialized = (s_pRadarVertexBuffer != nullptr);  // DAT_01205348
    *(uint *)(this + 8) = 0;  // some flag/state

    if (!bAlreadyInitialized) {
        // Allocate vertex buffer (0x180 bytes = 384 bytes)
        s_pRadarVertexBuffer = (uint *)Allocate(0x180, 0, 0, 0x12);  // FUN_0060b620
        // Allocate index buffer (0x76 bytes = 118 bytes)
        s_pRadarIndexBuffer = (uint *)Allocate(0x76, 0, 0, 0x12);  // FUN_0060c080

        uint *pVertexData;
        if (*(char *)((int)s_pRadarVertexBuffer + 7) == '\0') {
            // buffer not locked, get data pointer directly
            pVertexData = (uint *)s_pRadarVertexBuffer[4];
            *(char *)((int)s_pRadarVertexBuffer + 0x1d) = 1;  // mark locked?
        } else {
            uint flags = 0;
            uint *tempPtr = nullptr;
            if (*(char *)((int)s_pRadarVertexBuffer + 3) != '\0') {
                flags = 0x3000;
            }
            // Lock buffer: call vtable offset 0x2c on buffer object
            (*(code **)(**(int **)s_pRadarVertexBuffer + 0x2c))(*(int *)s_pRadarVertexBuffer, 0, 0, &tempPtr, flags);
            pVertexData = tempPtr;
        }

        // similar for index buffer
        uint *pIndexData;
        if (*(char *)((int)s_pRadarIndexBuffer + 10) == '\0') {
            pIndexData = (uint *)s_pRadarIndexBuffer[7];
            *(char *)((int)s_pRadarIndexBuffer + 0x29) = 1;
        } else {
            uint flags = 0;
            if (*(char *)((int)s_pRadarIndexBuffer + 2) != '\0') {
                flags = 0x3000;
            }
            (*(code **)(**(int **)s_pRadarIndexBuffer + 0x2c))(*(int *)s_pRadarIndexBuffer, 0, 0, (uint *)((int)s_pRadarIndexBuffer + 5), flags);
            pIndexData = (uint *)((int)s_pRadarIndexBuffer + 5);
        }

        // Fill vertex buffer header (6 dwords)
        pVertexData[0] = 0;
        pVertexData[1] = 0;
        pVertexData[2] = 0;
        pVertexData[3] = 0;
        pVertexData[4] = 0;
        pVertexData[5] = g_fRadius;  // DAT_00e2b1a4

        float *pPositions = (float *)(pVertexData + 6);   // 15 vertex positions (x,y,z)
        float *pNormals = (float *)(pVertexData + 0x35);  // 15 vertex normals (x,y,z) -- offset 0x35*4 = 212 bytes from start

        // Generate 15 vertices around a circle (angle step = 2*pi/15)
        uint i = 0;
        do {
            double angle = (double)(int)i * (2.0 * M_PI / 15.0);  // approximate constant from DAT_00e447b8? Actually uses DAT_00e447b8 as multiplier
            // Note: The original code uses a global multiply constant; we simplify here.

            float sinVal, cosVal;
            SinCos(angle, &sinVal, &cosVal);  // FUN_00b99fcb and FUN_00b99e20

            // Outer ring position
            pPositions[i * 3 + 0] = cosVal * g_fRadius;  // x
            pPositions[i * 3 + 1] = sinVal * g_fRadius;  // y
            pPositions[i * 3 + 2] = 0.0f;                 // z

            // Inner ring position (scaled by radius)
            pNormals[i * 3 + 0] = cosVal * 0.8f;  // example: inner radius?
            pNormals[i * 3 + 1] = sinVal * 0.8f;
            pNormals[i * 3 + 2] = g_fRadius;

            i++;
        } while (i < 15);

        // Generate index data (triangle strip for ring)
        ushort *pIndices = (ushort *)pIndexData;
        uint v = 0;
        do {
            uint vNext = v + 1;
            if (vNext > 14) {
                vNext = 0;
            }
            if (v != 0) {
                *pIndices = 0;
                pIndices++;
            }
            pIndices[0] = (ushort)(v + 2);
            pIndices[1] = (ushort)(vNext + 2);
            pIndices[2] = (ushort)(v + 17);
            pIndices[3] = (ushort)(vNext + 17);
            pIndices[4] = 1;
            if (vNext > 14) break;
            pIndices[5] = 1;
            pIndices += 7;
            v = vNext;
        } while (v < 15);

        // Unlock vertex buffer if needed
        if (*(char *)((int)s_pRadarVertexBuffer + 7) == '\0') {
            *(char *)((int)s_pRadarVertexBuffer + 0x1d) = 0;
        } else {
            (*(code **)(**(int **)s_pRadarVertexBuffer + 0x30))(*(int *)s_pRadarVertexBuffer);
        }

        // Unlock index buffer and compute min/max
        if (*(char *)((int)s_pRadarIndexBuffer + 10) == '\0') {
            *(char *)((int)s_pRadarIndexBuffer + 0x29) = 0;
        } else {
            uint count = s_pRadarIndexBuffer[3];
            ushort minIdx = 0xffff;
            ushort maxIdx = 0;
            if (count != 0) {
                uint j = 0;
                do {
                    ushort val = *(ushort *)(s_pRadarIndexBuffer[5] + j * 2);
                    if (val < minIdx) minIdx = val;
                    if (maxIdx <= val) maxIdx = val;
                    j++;
                } while (j < count);
            }
            *(ushort *)((int)s_pRadarIndexBuffer + 4) = minIdx;
            *(ushort *)((int)s_pRadarIndexBuffer + 0x12) = maxIdx; // +18 bytes
            // Unlock
            (**(code **)(**(int **)s_pRadarIndexBuffer + 0x30))(*(int *)s_pRadarIndexBuffer);
        }

        // Store sizes and derived values
        s_nRadarIndexCount = 0x76;      // DAT_01205350
        float x = g_fSomething;         // DAT_00e447b0
        CosApprox(&x);                  // FUN_00b99e20
        s_fRadarAspectRatio = g_fRadius / x; // DAT_01205354
    }
    return;
}