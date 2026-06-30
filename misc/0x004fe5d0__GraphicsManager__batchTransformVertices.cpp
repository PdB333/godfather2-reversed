// FUNC_NAME: GraphicsManager::batchTransformVertices
void __thiscall GraphicsManager::batchTransformVertices(int thisPtr, void* outputBuffer)
{
    float* matrix;
    int numPoints;
    float threshold;
    float area;
    float* transformedPtr;
    int i;
    int pointDataPtr;
    float local_210;
    float fStack_20c;
    float fStack_208;
    float transformed[100]; // 25 vertices * 4 floats
    unsigned char perVertexData[25];
    unsigned char luVar2;

    // Check if transformation is needed
    if ((*(int*)(thisPtr + 0x68) > 1) &&
        ((*(unsigned char*)(thisPtr + 0x78) & 1) == 0) &&
        (*(float*)(thisPtr + 0x70) * *(float*)(thisPtr + 0x6c) > DAT_00e2af44))
    {
        // Store the number of vertices (as byte)
        perVertexData[0] = *(unsigned char*)(thisPtr + 0x68);

        // Store the input transformation matrix (4x4 float, row-major)
        matrix = (float*)in_EAX; // Actually passed via EAX, treat as matrix
        float m00 = matrix[0];  float m01 = matrix[1];  float m02 = matrix[2];  float m03 = matrix[3];
        float m10 = matrix[4];  float m11 = matrix[5];  float m12 = matrix[6];  float m13 = matrix[7];
        float m20 = matrix[8];  float m21 = matrix[9];  float m22 = matrix[10]; float m23 = matrix[11];
        float m30 = matrix[12]; float m31 = matrix[13]; float m32 = matrix[14]; float m33 = matrix[15];

        // Setup transformation context (e.g., identity matrix)
        FUN_0048ee40();

        // Transform each vertex
        numPoints = *(int*)(thisPtr + 0x68);
        pointDataPtr = *(int*)(thisPtr + 0x60); // Base pointer to vertex data
        float wConstant = DAT_00e2b1a4; // Usually 1.0 for homogeneous coordinate

        for (i = 0; i < numPoints; i++)
        {
            FUN_00414aa0(); // Updates some global state and returns pointer to vertex in extraout_EDX
            // extraout_EDX holds current vertex pointer (from pointDataPtr + some offset)
            // The function likely modifies extraout_EDX based on i
            float x = local_210; // These are from the vertex data, extracted previously
            float y = fStack_20c;
            float z = fStack_208;
            // w = 1.0 (from wConstant)

            // Store transformed point (4 components) into temporary array
            transformedPtr = (float*)((int)transformed + (int)(extraout_EDX - pointDataPtr));
            transformedPtr[0] = x * m00 + y * m10 + z * m20 + wConstant * m30;
            transformedPtr[1] = x * m01 + y * m11 + z * m21 + wConstant * m31;
            transformedPtr[2] = x * m02 + y * m12 + z * m22 + wConstant * m32;
            transformedPtr[3] = x * m03 + y * m13 + z * m23 + wConstant * m33;

            // Store per-vertex byte (e.g., alpha or bone weight index)
            luVar2 = *(unsigned char*)(extraout_EDX + 0xc);
            perVertexData[i] = luVar2;
        }

        // Pack transformed data into output buffer using custom stack allocator
        int* allocPtr = (int*)(DAT_01206880 + 0x14);
        *(void**)(DAT_01206880 + 0x14) = &PTR_LAB_01124ecc;
        *allocPtr += 4;
        *(int*)(*allocPtr) = (int)outputBuffer;
        // Align destination pointer
        void* dst = (void*)((uint)(*allocPtr + 0x13) & 0xfffffff0);
        *allocPtr = (int)dst;
        memcpy(dst, transformed, 0x1b0); // Copies transformed vertices (24 bytes? Actually 0x1b0=432 bytes, includes perVertexData? But perVertexData is separate)
        *allocPtr += 0x1b0;
    }
}