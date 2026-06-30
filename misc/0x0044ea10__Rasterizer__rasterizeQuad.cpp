// FUNC_NAME: Rasterizer::rasterizeQuad
void __thiscall Rasterizer::rasterizeQuad(Rasterizer* this, int materialId)
{
    float scale = *(float*)((int)this + 0xc); // +0x0C: scale factor
    float x1 = *(float*)(materialId + 0x20); // assume param_1 is material/object pointer
    float y1 = *(float*)(materialId + 0x28);
    float x2 = *(float*)(materialId + 0x30);
    float y2 = *(float*)(materialId + 0x38);

    float scaled_x1 = scale * x1;
    float scaled_y1 = scale * y1;
    float scaled_x2 = scale * x2;
    float scaled_y2 = scale * y2;

    // Truncation with rounding correction (inlined floor/trunc)
    float trunc_x1 = (float)(DAT_00e44648 | DAT_00e44564 & (uint)scaled_x1);
    trunc_x1 = (scaled_x1 + trunc_x1) - trunc_x1;
    float trunc_y1 = (float)(DAT_00e44648 | DAT_00e44564 & (uint)scaled_y1);
    trunc_y1 = (scaled_y1 + trunc_y1) - trunc_y1;
    float trunc_x2 = (float)(DAT_00e44648 | DAT_00e44564 & (uint)scaled_x2);
    trunc_x2 = (scaled_x2 + trunc_x2) - trunc_x2;
    float trunc_y2 = (float)(DAT_00e44648 | DAT_00e44564 & (uint)scaled_y2);
    trunc_y2 = (scaled_y2 + trunc_y2) - trunc_y2;

    int offsetX = *(int*)((int)this + 0x10); // +0x10: viewport X offset
    int offsetY = *(int*)((int)this + 0x14); // +0x14: viewport Y offset

    int int_x1 = (int)(trunc_x1 - (float)(-(uint)((float)(DAT_00e44564 & (uint)scaled_x1) < trunc_x1 - scaled_x1) & DAT_00e2b1a4)) - offsetX;
    int int_y1 = (int)(trunc_y1 - (float)(-(uint)((float)(DAT_00e44564 & (uint)scaled_y1) < trunc_y1 - scaled_y1) & DAT_00e2b1a4)) - offsetY;
    int int_x2 = (int)(trunc_x2 - (float)(-(uint)((float)(DAT_00e44564 & (uint)scaled_x2) < trunc_x2 - scaled_x2) & DAT_00e2b1a4)) - offsetX;
    int int_y2 = (int)(trunc_y2 - (float)(-(uint)((float)(DAT_00e44564 & (uint)scaled_y2) < trunc_y2 - scaled_y2) & DAT_00e2b1a4)) - offsetY;

    int width = *(int*)((int)this + 4); // +0x04: buffer width (max x)

    // Check if any of the coordinates are out of bounds (negative or >= width)
    if (int_x1 >= 0 && int_y1 >= 0 && int_x2 < width && int_y2 < width)
    {
        // Clamp to valid range
        if (int_x1 < 0) int_x1 = 0;
        if (int_y1 < 0) int_y1 = 0;
        if (int_x2 >= width) int_x2 = width - 1;
        if (int_y2 >= width) int_y2 = width - 1;

        int rectHeight = int_y2 - int_y1 + 1;
        int rectWidth = int_x2 - int_x1 + 1;

        // Check if there is enough space in the span buffer
        int bufferCapacity = *(int*)((int)this + 0x18); // +0x18: max entries capacity
        int entryStride = *(int*)((int)this + 0x1c) * 8; // +0x1C: stride * 8? (maybe 8 bytes per entry)
        int currentPtr = *(int*)((int)this + 0x20); // +0x20: current write pointer (offset into buffer)
        int freeSlots = (bufferCapacity + entryStride - currentPtr) >> 3; // number of free entries (8 bytes each)

        if (rectHeight * rectWidth <= freeSlots && int_x1 <= int_x2)
        {
            int* baseBuffer = *(int**)((int)this + 0x24); // +0x24: base buffer for depth/sort values
            int rowOffset = int_y1 * width + int_x1; // start index in the buffer

            for (int row = 0; row < rectHeight; row++)
            {
                int colOffset = rowOffset;
                int* writePtr = (int*)(currentPtr + ((int)this + 0x20)); // note: this is weird but preserve logic
                // Actually the code does: iVar2 = iVar2 + iVar3 * 4 each row, and iVar4 = iVar2 initially per row
                // Better to restructure as nested loops

                // We'll reconstruct using the original variables: int_x1, int_y1, width
                int yCur = int_y1 + row;
                int xStart = int_x1;
                int xEnd = int_x2;

                // The pointer to the span list (linked list style)
                int** spanListPtr = (int**)((int)this + 0x20); // location holding the current write pointer

                // For each column in this row
                for (int x = xStart; x <= xEnd; x++)
                {
                    // Allocate new span node
                    int* newNode = *(int**)((int)this + 0x20); // read current free pointer
                    *(int**)((int)this + 0x20) = newNode + 2; // advance by 2 ints (8 bytes)

                    // Fill the node
                    newNode[0] = materialId; // store the material/object reference
                    newNode[1] = *(int*)((int)(baseBuffer) + (yCur * width + x) * 4); // store the depth/sort value from base buffer

                    // Insert the node into the sorted list? Actually it writes back to the base buffer as a linked list
                    // The line: *(int**)(iVar4 + *(int*)(in_EAX + 0x24)) = piVar1;
                    // This sets the pointer at baseBuffer[x + y*width] to point to the newly allocated node.
                    *(int**)((int)(baseBuffer) + (yCur * width + x) * 4) = newNode;
                }

                // Advance row offset (code uses iVar2 = iVar2 + iVar3 * 4)
                rowOffset += width;
            }
        }
    }
}