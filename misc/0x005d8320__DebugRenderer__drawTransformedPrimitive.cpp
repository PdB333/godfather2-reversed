// FUNC_NAME: DebugRenderer::drawTransformedPrimitive

// Function address: 0x005d8320
// Likely draws a debug primitive (e.g., line, sphere) with a transformation matrix and colors.

void __thiscall DebugRenderer::drawTransformedPrimitive(
    uint param_1, // this
    DebugCommandBuffer* buffer, // param_2 - buffer to write debug commands
    float* transform, // param_3 - 4x4 transformation matrix (row-major)
    float* position, // param_4 - float[4] position (x,y,z,w)
    uint* colorStart, // param_5 - RGBA color for start
    uint* colorEnd, // param_6 - RGBA color for end
    uint* colorFill, // param_7 - RGBA color for fill
    uint argbColor // param_8 - additional color in ARGB format
)
{
    DebugGeometry geometry; // local object, constructed on stack
    // Call to constructor (FUN_005c5320) - initializes geometry with some defaults
    geometry.DebugGeometry();

    // Extract position components (w is not used directly here)
    float fX = position[0];
    float fY = position[1];
    float fZ = position[2];
    float fW = position[3];

    // Copy colorStart into a local variable for transformation (why? maybe for lighting?)
    uint startColor = colorStart[0];
    uint startColor1 = colorStart[1]; // probably unused? but stored
    uint startColor2 = colorStart[2];
    uint startColor3 = colorStart[3];

    // Transform the start color? Actually, matrix * position computes a new vector.
    // The following lines compute transformed coordinates using the matrix.
    // Matrix multiplication: transformed = position * matrix (row vector * matrix)
    float transX = transform[0*4+0] * fX + transform[1*4+0] * fY + transform[2*4+0] * fZ + transform[3*4+0] * fW;
    float transY = transform[0*4+1] * fX + transform[1*4+1] * fY + transform[2*4+1] * fZ + transform[3*4+1] * fW;
    float transZ = transform[0*4+2] * fX + transform[1*4+2] * fY + transform[2*4+2] * fZ + transform[3*4+2] * fW;
    float transW = transform[0*4+3] * fX + transform[1*4+3] * fY + transform[2*4+3] * fZ + transform[3*4+3] * fW;

    // Store transformed result back to a temporary local
    float transformed[4] = {transX, transY, transZ, transW};

    // Another transformation of the same position? This looks like a copy of the original position
    // but stored in another local variable (maybe for different purposes)
    float otherPos[4] = {fX, fY, fZ, fW};
    // FUN_0056b420 appears to be a matrix-vector multiply, but the calls are different:
    // First call transforms 'startColor' (which is actually a vector of floats?) with transform.
    // But startColor is a uint, not a float. This is suspicious.
    // Possibly the decompiler misidentified the types. The callee FUN_0056b420 likely expects float*.
    // Debug geometry struct uses floats, so we treat them as floats.
    // We'll model as:
    //   geometry.transformVertex(transform, transformed, vertex1);
    //   geometry.transformVertex(transform, otherPos, vertex2);
    //   geometry.transformVertex(transform, colorStartAsFloats, colorVertex);
    // But since we don't know the exact semantics, we preserve the structure.

    // Call to matrix-vector multiply functions (FUN_0056b420)
    geometry.transformVertex(transform, &startColor, otherLocal); // first call - transforms startColor? Actually address of startColor is passed
    geometry.transformVertex(transform, &otherPos, vertex2Local); // second call
    geometry.transformVertex(transform, &startColor, vertex3Local); // third call? Actually looks like same as first? The decompilation shows three calls.

    // Assign output colors
    uint outputColor1 = colorEnd[0];   // local_a0
    uint outputColor2 = colorEnd[1];   // local_9c
    uint outputColor3 = colorFill[0];  // local_90
    uint outputColor4 = colorFill[1];  // local_7c

    // Byte-swap the ARGB color to RGBA (or vice versa)
    uint swappedColor = ((argbColor & 0xFF0000) | (argbColor >> 16)) >> 8 
                         | ((argbColor & 0xFF00) | (argbColor << 16)) << 8;

    // Global flag: 0x0119d0ac likely = debugDrawEnabled (1 = enabled)
    if (DAT_0119d0ac == 1) {
        // Begin debug command sequence
        debugBeginCommand(); // FUN_005d8020

        // Write command header (8 = maybe draw line, 7 = another command)
        int* stream = DAT_01206880; // pointer to command stream (stream + 0x14 is current write position)
        // Write vtable pointer for command type
        *(undefined4**)(stream + 0x14) = &g_vtable_DebugDrawCommand; // PTR_LAB_01126bb8
        *(int*)(stream + 0x14) += 4; // advance
        *(undefined4**)(stream + 0x14) = 8; // command ID 8
        *(int*)(stream + 0x14) += 4;

        // Write vertex data (position/color) via another vtable
        *(undefined4**)(stream + 0x14) = &g_vtable_DebugVertex; // PTR_LAB_01126b18
        *(int*)(stream + 0x14) += 4;
        // Write vertex count (1)
        int* writePos = (int*)(stream + 0x14);
        *writePos = 1;
        // Align to 4 bytes? (size 1 + 3 padding? Actually writing 1, then 7, then 5, etc.)
        // The code writes bytes after alignment. We mimic:
        writePos = (int*)(((unsigned int)writePos + 3) & 0xFFFFFFFC);
        *writePos = 1;
        writePos = (int*)(((unsigned int)writePos + 7) & 0xFFFFFFFC);
        *writePos = 5;
        writePos++;
        // Update stream pointer
        stream = (int*)((int)writePos);

        // Submit vertex with swapped color
        submitDebugVertex(*(uint*)(buffer + 0x10), swappedColor); // FUN_005d8140

        // Second command (another vertex)
        debugBeginCommand();
        *(undefined4**)(stream + 0x14) = &g_vtable_DebugDrawCommand;
        *(int*)(stream + 0x14) += 4;
        *(undefined4**)(stream + 0x14) = 7; // command ID 7
        *(int*)(stream + 0x14) += 4;

        *(undefined4**)(stream + 0x14) = &g_vtable_DebugVertex;
        *(int*)(stream + 0x14) += 4;
        writePos = (int*)(stream + 0x14);
        *writePos = 1;
        writePos = (int*)(((unsigned int)writePos + 3) & 0xFFFFFFFC);
        *writePos = 1;
        writePos = (int*)(((unsigned int)writePos + 7) & 0xFFFFFFFC);
        *writePos = 7;
        writePos = (int*)(((unsigned int)writePos + 7) & 0xFFFFFFFC);
        *writePos = 8;
        writePos++;
        stream = (int*)((int)writePos);

        submitDebugVertex(*(uint*)(buffer + 0x10), swappedColor);
        debugBeginCommand();
        return;
    }

    // If debug disabled, just submit the vertex once
    submitDebugVertex(*(uint*)(buffer + 0x10), swappedColor);
    return;
}