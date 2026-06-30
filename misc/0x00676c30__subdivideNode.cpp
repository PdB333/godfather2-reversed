// FUNC_NAME: subdivideNode
void __fastcall subdivideNode(int sizeThreshold,
                              int coordA,
                              void* nodeData,
                              int minX,
                              int minY,
                              int maxX,
                              int maxY,
                              int minZ,
                              int maxZ,
                              int coordB)
{
    int* stackPtr;
    int* stackPopPtr;
    int tempX, tempY, tempZ;
    int midX1, midX2, midY1, midY2, midZ1, midZ2;
    int stackDepth;
    int stackBuffer[144]; // Stack of 9-element frames (max 16 levels)

    // Compute size in X direction: uses coordA, minX, maxX, minZ, coordB?
    tempX = (((maxX - minX) - minZ) + coordA) * 3 + 4 >> 3;
    stackPtr = stackBuffer; // Start of stack, points to next free slot

    if (tempX < 0) tempX = -tempX;
    if (sizeThreshold < tempX) sizeThreshold = tempX;

    // Compute size in Y direction: uses minY, maxY, maxZ, coordB?
    tempY = (((maxY - minY) - maxZ) + coordB) * 3 + 4 >> 3;
    if (tempY < 0) tempY = -tempY;
    if (sizeThreshold < tempY) sizeThreshold = tempY;

    // Reduce sizeThreshold until it's smaller than the node's detail level
    // nodeData+0x2200 is presumably a "maxLevel" or "detailThreshold"
    stackDepth = 0;
    for (; *(int*)((char*)nodeData + 0x2200) < sizeThreshold; sizeThreshold >>= 2)
    {
        stackDepth++;
    }

    while (true)
    {
        // Subdivision loop: while depth > 0, split the current node
        while (stackDepth > 0)
        {
            // Compute midpoints for the current node
            // param order: (minX, minY, maxX, maxY, minZ, maxZ, coordA, coordB)
            midX1 = (maxX + coordA + 1) >> 1;
            midX2 = (coordA + 1 + minZ) >> 1;
            tempX = (minX + (maxX + coordA) * 3 + 4 + minZ) >> 3;
            *stackPtr = tempX;                              // frame[0]: some X-split value
            stackDepth--;
            tempY = (minY + (maxY + coordB) * 3 + 4 + maxZ) >> 3;
            *(stackPtr + 1) = tempY;                        // frame[1]: some Y-split value
            *(stackPtr + 2) = (midX2 + 1 + midX1) >> 1;     // frame[2]: ?midX?
            midY1 = (coordB + 1 + maxZ) >> 1;
            midY2 = (maxY + coordB + 1) >> 1;
            *(stackPtr + 3) = (midY1 + 1 + midY2) >> 1;      // frame[3]: ?midY?
            *(stackPtr + 4) = midX2;                         // frame[4]: first X midpoint
            *(stackPtr + 5) = midY1;                         // frame[5]: first Y midpoint
            *(stackPtr + 6) = minZ;                          // frame[6]: Z1 (original minZ)
            *(stackPtr + 7) = maxZ;                          // frame[7]: Z2 (original maxZ)
            *(stackPtr + 8) = stackDepth;                    // frame[8]: remaining depth for this branch

            // Update bounds for the next subdivision (going deeper into the first child)
            maxX = (minX + 1 + maxX) >> 1;
            maxY = (minY + 1 + maxY) >> 1;
            coordA = (midX1 + 1 + maxX) >> 1;
            stackPtr += 9; // Advance stack pointer
            coordB = (maxY + 1 + midY2) >> 1;
            minZ = tempX;
            maxZ = tempY;
        }

        // Process leaf node (size is small enough)
        FUN_006767c0(minX, minY, minZ, maxZ);

        if (stackPtr <= stackBuffer) break; // Stack empty

        // Pop the previous frame from the stack
        stackDepth = *(stackPtr - 1);   // frame[8]: depth for previous level
        stackPopPtr = stackPtr - 2;     // pointer to frame[7]
        int* var1 = stackPtr - 3;       // pointer to frame[6]
        coordB = *(stackPtr - 4);       // frame[5]
        maxZ = *(stackPtr - 6);         // frame[3]
        maxY = *(stackPtr - 7);         // frame[2]
        coordA = *(stackPtr - 5);       // frame[4]
        minY = *(stackPtr - 8);         // frame[1]
        stackPtr -= 9;                  // Move to start of popped frame
        minX = *stackPtr;                // frame[0]
        minZ = *var1;                    // frame[6]
        maxZ = *stackPopPtr;             // frame[7]
    }
}