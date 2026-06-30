// FUNC_NAME: SceneRenderer::transformAndSortFaces
void __fastcall SceneRenderer::transformAndSortFaces(uint *this, float *matrix)
{
    // matrix is a 3x4 transformation matrix (row-major? Actually used as 4 columns of 3? 
    // Accessed indices: 0,1,2; 4,5,6; 8,9,10; 12,13,14 -> 4 columns of 3 floats each (transformation + translation?).
    // This transform is applied to input vertices.

    float *outVertexBuf;    // +0x14 in this? Actually this[5] is output vertex buffer
    float *inVertexBuf;    // this[1] is input vertex array (stride 0x14)
    byte *vertexFlags;     // this[2] per-vertex byte (maybe material or flags)
    ushort *indexBuffer;   // this[4] triangle index triplets
    uint numVerts;         // this[0]
    uint numTris;          // this[3]
    short *sortKeyBuf;     // this[6] output sort key buffer (pairs: index, depth)
    // this[7] is used as last param to final sort function

    float minDist = 1e30f;
    float maxDist = -1e30f;
    float fVar29, fVar4, fVar5, fVar6;
    int iVar9 = 0;
    int iVar13 = 0;
    uint uVar14 = 0;

    // Global constants (from context)
    float globalZero = DAT_00e2b1a4; // often 1.0
    float wScale = DAT_00e44898;     // scale for something
    float nearClip = DAT_00e2e50c;   // near clip plane distance
    float farClip = DAT_00e44758;    // far clip plane distance

    // Extract transformation matrix columns
    float m00 = matrix[0]; float m01 = matrix[1]; float m02 = matrix[2];
    float m10 = matrix[4]; float m11 = matrix[5]; float m12 = matrix[6];
    float m20 = matrix[8]; float m21 = matrix[9]; float m22 = matrix[10];
    float t0  = matrix[12]; float t1  = matrix[13]; float t2  = matrix[14];

    // First pass: transform all vertices
    if (numVerts != 0)
    {
        do
        {
            // Read input vertex (3 floats at offset iVar13)
            float *inVtx = (float *)(this[1] + iVar13);
            float vx = *inVtx;
            float vy = inVtx[1];
            float vz = inVtx[2];

            float flagScaled = (float)*vertexFlags * wScale;
            // Compute transformed z (depth) and store min/max
            fVar29 = vx * m20 + vy * m21 + vz * m22 + globalZero * t2;
            if (fVar29 < minDist) minDist = fVar29;
            if (fVar29 > maxDist) maxDist = fVar29;

            // Write transformed vertex (4 floats: world/view space position? Actually stored as x,y,z,flag)
            outVertexBuf = (float *)(this[5] + iVar9);
            outVertexBuf[0] = vx * m00 + vy * m01 + vz * m02 + globalZero * t0;
            outVertexBuf[1] = vx * m10 + vy * m11 + vz * m12 + globalZero * t1;
            outVertexBuf[2] = fVar29;   // depth
            outVertexBuf[3] = flagScaled;

            vertexFlags++;
            iVar13 += 0x14;    // input stride (20 bytes)
            iVar9 += 0x10;     // output stride (16 bytes)
            uVar14++;
        } while (uVar14 < numVerts);
    }

    // Second pass: process triangles (build sort keys)
    float depthRange = maxDist - minDist;
    float invRange = 1.0f / (depthRange * DAT_00e2b04c + depthRange); // some formula with global constants
    float depthScale = depthRange * DAT_00e2eff4;    // scale factor for depth
    float zeroEpsilon = DAT_00e2cbe0;               // small epsilon to avoid division by zero?
    float globalOne = DAT_00e2b1a4;                 // 1.0

    // Global constants for lighting/color
    float lightFactor = DAT_00e2cd54;               // light multiplier
    float minNormal = DAT_00f17958;                 // clamp for dot product
    float maxNormal = DAT_00e44890;                 // clamp upper bound
    float cosAngleLimit = DAT_00e2e22c;             // clamp for final depth

    if (numTris != 0)
    {
        ushort *triIndices = (ushort *)this[4];
        uVar14 = 0;
        do
        {
            uint baseOut = this[5];  // transformed vertex buffer base
            // Read three vertex indices for current triangle
            float *v0 = (float *)((uint)*triIndices * 0x10 + baseOut);
            float *v1 = (float *)((uint)triIndices[1] * 0x10 + baseOut);
            float *v2 = (float *)((uint)triIndices[2] * 0x10 + baseOut);

            // Compute two edge vectors
            float e1x = *v0 - *v2;
            float e1y = v0[1] - v2[1];
            float e1z = v0[2] - v2[2];
            float e2x = *v0 - *v1;
            float e2y = v0[1] - v1[1];
            float e2z = v0[2] - v1[2];

            // Compute cross product (normal)
            float nx = e1z * e2y - e1y * e2z;
            float ny = e1x * e2z - e1z * e2x;
            float nz = e1y * e2x - e1x * e2y;

            float lenSq = nx*nx + ny*ny + nz*nz;
            if (lenSq <= zeroEpsilon)
                lenSq = 0.0f;
            else
                lenSq = globalOne / sqrtf(lenSq); // actually inverse length

            nz *= lenSq;    // Only z component used for dot with light? Actually they compute dot with (0,0,1) assumed
            // Clamp nz to [minNormal, maxNormal] then multiply by lightFactor
            if (nz >= 0.0f)
            {
                if (nz <= minNormal)
                    nz = minNormal;
                nz *= lightFactor;
            }
            else
            {
                if (nz >= maxNormal)
                    nz = maxNormal;
            }

            // Compute average depth and material sum for triangle
            float avgDepth = (v0[2] + v1[2] + v2[2]) * 0.333333f; // actually they use v0[2]+v1[2]+v2[2] without division? Wait, they use fVar18 = v0[2]+v1[2]+v2[2] in computation
            float flagSum = (v0[3] + v1[3] + v2[3]) * _UNK_00e369cc; // material/flag sum times global constant
            // Depth computation: combine flag and depth, subtract minDist and depthRange, scale by invRange
            float depthValue = (flagSum * nz * depthScale + avgDepth * _UNK_00e369c8) - (minDist - depthRange);
            depthValue *= invRange;
            // Clamp depth to [0, cosAngleLimit]
            if (depthValue >= 0.0f)
            {
                if (depthValue > cosAngleLimit)
                    depthValue = cosAngleLimit;
            }
            else
                depthValue = 0.0f;

            // Write sort key: index and depth as shorts
            short *outKey = (short *)(this[6] + 2 + uVar14 * 4);
            outKey[0] = (short)(int)depthValue;    // depth in short
            outKey[-1] = (short)uVar14;            // triangle index

            triIndices += 3;
            uVar14++;
        } while (uVar14 < numTris);
    }

    // Final sort: sort triangles by depth (using quicksort/heapsort)
    FUN_004cdc50(this[3], this[6], this[7]);
}