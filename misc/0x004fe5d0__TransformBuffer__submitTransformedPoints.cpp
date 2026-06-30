// FUNC_NAME: TransformBuffer::submitTransformedPoints
void __thiscall TransformBuffer::submitTransformedPoints(float *matrix, uint32_t userData)
{
    // This function transforms a list of points (positions) using a 4x4 transformation matrix
    // and stores them in a custom memory allocator frame buffer.
    // 
    // Class offsets:
    // +0x60: m_pointArray (float*?) - base pointer to point data
    // +0x68: m_pointCount (int)
    // +0x6c: m_scaleX (float)
    // +0x70: m_scaleY (float)  // product m_scaleX * m_scaleY compared to threshold
    // +0x78: m_flags (byte), bit0 = 1 means disabled?
    // 
    // Globals:
    // DAT_00e2af44 - some quality/distance threshold
    // DAT_00e2b1a4 - constant 1.0 or similar (used as homogeneous w)
    // DAT_01206880 - pointer to custom allocator structure

    // Only process if there is more than 1 point, no disable flag, and product > threshold
    if (m_pointCount > 1 && !(m_flags & 1))
    {
        float product = m_scaleX * m_scaleY; // +0x70 * +0x6c
        if (product > g_pointProductThreshold) // DAT_00e2af44
        {
            uint8_t pointIndex = static_cast<uint8_t>(m_pointCount); // save original count?

            // Save the 4x4 matrix from the argument (matrix passed in EAX)
            float m00 = matrix[0], m01 = matrix[1], m02 = matrix[2], m03 = matrix[3];
            float m10 = matrix[4], m11 = matrix[5], m12 = matrix[6], m13 = matrix[7];
            float m20 = matrix[8], m21 = matrix[9], m22 = matrix[10], m23 = matrix[11];
            float m30 = matrix[12], m31 = matrix[13], m32 = matrix[14], m33 = matrix[15];

            // Call helper to initialize point iteration (e.g., reset iterator)
            beginPointIteration(); // FUN_0048ee40

            int count = m_pointCount;
            int base = reinterpret_cast<int>(m_pointArray); // iVar4 = *(this+0x60)
            float transformedPoints[100]; // local_1c0, enough for many points
            uint8_t pointTypes[25]; // auStack_2c

            float globalW = g_homogeneousW; // DAT_00e2b1a4, likely 1.0

            for (int i = 0; i < count; ++i)
            {
                // Get next source point (returns pointer in EDX and sets local vector)
                float x, y, z, w;
                getNextPoint(&x, &y, &z, &w); // FUN_00414aa0, sets local_210, fStack_20c, fStack_208, w from globalW?

                // The call also returns an address in EDX (extraout_EDX) from which we read a type byte at +0xc
                // and compute offset into transformedPoints array
                int pointAddr = reinterpret_cast<int>(&x); // Actually the function returns a pointer in EDX
                // The decompiler shows: extraout_EDX is the returned pointer, then offset = extraout_EDX - iVar4
                // So getNextPoint returns a pointer to some structure that includes position and type.
                // We simulate: the function returns a pointer to a source point structure, we extract type and position.
                float *srcPoint = reinterpret_cast<float*>(getNextPoint()); // but it returns pointer to struct
                // For reconstruction, we'll treat the returned pointer as having position at offsets 0, 4, 8? and type at +0xc.
                uint8_t type = *(reinterpret_cast<uint8_t*>(srcPoint + 3)); // +0xc = 3 floats offset

                // Compute transformed point using matrix multiplication (column-major assumed)
                float tx = x * m00 + y * m10 + z * m20 + w * m30;
                float ty = x * m01 + y * m11 + z * m21 + w * m31;
                float tz = x * m02 + y * m12 + z * m22 + w * m32;
                float tw = x * m03 + y * m13 + z * m23 + w * m33;

                // Store transformed point in array at computed offset
                int arrayBase = reinterpret_cast<int>(transformedPoints);
                int offset = reinterpret_cast<int>(srcPoint) - base;
                float *dest = reinterpret_cast<float*>(arrayBase + offset);
                dest[0] = tx;
                dest[1] = ty;
                dest[2] = tz;
                dest[3] = tw;

                pointTypes[i] = type; // store associated byte
            }

            // Now allocate a slot in the custom memory allocator and copy the data
            Allocator *alloc = reinterpret_cast<Allocator*>(g_customAllocator); // DAT_01206880
            int *allocPtr = reinterpret_cast<int*>(alloc->currentPtr); // +0x14
            // Set vtable or type identifier
            **reinterpret_cast<void***>(&alloc->currentPtr) = &g_transformPointVTable; // PTR_LAB_01124ecc
            *allocPtr += 4; // move pointer
            // Store userData as next slot
            *reinterpret_cast<uint32_t*>(*allocPtr) = userData;
            // Align to 16 bytes
            int aligned = (*allocPtr + 0x13) & ~0xF;
            *allocPtr = aligned;
            // Copy transformed points and types (size 0x1b0 = 432 bytes)
            _memcpy(reinterpret_cast<void*>(aligned), transformedPoints, 0x1b0);
            // Update allocator pointer to after copied data
            *allocPtr = aligned + 0x1b0;
        }
    }
}