// FUNC_NAME: Geometry::tessellateTrianglePatch
uint __fastcall Geometry::tessellateTrianglePatch(Vector4* inputPoints, int param2, int param3, Vector4* outputBuffer, int* outputCount)
{
    // inputPoints: 3 control points (each Vector4 with w constant)
    // param2, param3: subdivision parameters (param3 incremented by 0x10 per iteration)
    // outputBuffer: destination for generated vertices (groups of 3 Vector4 per output triangle)
    // outputCount: updated with number of vertices written

    // Local buffers for ping-pong subdivision (two sets of control points, each 3*4=12 floats, plus some extra)
    float bufferA[12];   // first set of control points (3 x Vector4)
    float bufferB[12];   // second set
    float* buffers[2] = { bufferA, bufferB };

    int currentSet = 0;          // which buffer is current
    int controlPointCount = 3;   // number of control points in current set

    // Copy input points into bufferA (indices 0,1,2 + constant w at index 3, 7, 11? Actually structured as point0: x,y,z,w at indices 0-3, point1 at 4-7, point2 at 8-11)
    bufferA[0] = inputPoints[0].x;
    bufferA[1] = inputPoints[0].y;
    bufferA[2] = inputPoints[0].z;
    bufferA[3] = constantW;                // DAT_00e2b1a4 (likely 1.0f)
    bufferA[4] = inputPoints[1].x;
    bufferA[5] = inputPoints[1].y;
    bufferA[6] = inputPoints[1].z;
    bufferA[7] = constantW;
    bufferA[8] = inputPoints[2].x;
    bufferA[9] = inputPoints[2].y;
    bufferA[10] = inputPoints[2].z;
    bufferA[11] = constantW;

    int subdivideStep = param2 - param3;    // difference for subdivision level
    // Perform 6 subdivision steps
    for (int step = 0; step < 6; step++)
    {
        int parity = step & 1;  // alternate between 0 and 1
        float* src = buffers[parity];
        float* dst = buffers[1 - parity];

        // Call helper to subdivide the control point set (3 points -> 2 sets stored in dst)
        // FUN_00521dd0 returns 0 on failure
        uint result = subdivideControlPoints(src, controlPointCount, param3, dst);
        if (result == 0)
        {
            goto failure;   // early exit
        }
        // Update control point count based on subdivision (each call doubles?)
        // The helper updates the count in the first element of dst?
        // Actually in the original code, the count is stored in local_2bc[0] which is part of the control point array
        // We'll assume the helper returns the new count or updates it.
        controlPointCount = *((int*)dst + 0); // read from offset 0 of dst (assumed to store count)
        param3 += 0x10;  // increment stride for next step
    }

    // If final control point count > 2, output triangles
    if (controlPointCount > 2)
    {
        int written = *outputCount; // initial count
        float* curRead = bufferB + (currentSet ? 12 : 0); // actually need to use the final buffer
        // The output writes groups of 3 Vector4 (each 16 bytes) in sequence
        // The loop iterates over (controlPointCount - 2) groups, each group writes 3 vertices
        for (int i = 0; i < controlPointCount - 2; i++)
        {
            // Write triangle: three vertices (12 floats)
            outputBuffer[written + 0] = curRead[0];  // first vertex
            outputBuffer[written + 1] = curRead[1];
            outputBuffer[written + 2] = curRead[2];
            outputBuffer[written + 3] = curRead[3];
            outputBuffer[written + 4] = curRead[4];  // second vertex
            outputBuffer[written + 5] = curRead[5];
            outputBuffer[written + 6] = curRead[6];
            outputBuffer[written + 7] = curRead[7];
            outputBuffer[written + 8] = curRead[8];  // third vertex
            outputBuffer[written + 9] = curRead[9];
            outputBuffer[written + 10] = curRead[10];
            outputBuffer[written + 11] = curRead[11];

            curRead += 12;  // move to next set of control points?
            written += 3;   // three vertices written
        }
        *outputCount = written;
        return 0x100;   // success flag
    }

failure:
    return 0;   // failure (clear low byte, high byte zero)
}