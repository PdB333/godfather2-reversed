// FUNC_NAME: buildSpriteSheetVertexGrid

void buildSpriteSheetVertexGrid(int unused1, int unused2, VertexBuffer* buffer, const char* gridSpec)
{
    // param_3: buffer -> pointer to vertex buffer structure with fields:
    //   +0x00: size_t headerSize (?)
    //   +0x04: void* vertexData
    //   +0x08: size_t vertexCount (or float for second allocation)
    //   +0x0C: some flag
    // param_4: string containing "_w=cols_h=rows" format

    int cols, rows;
    const char* wStr = _strstr(gridSpec, "_w=");
    if (wStr != nullptr && wStr != (char*)-3) {
        cols = parseColsOrRows(); // FUN_005c71e0 probably returns integer from string
    } else {
        cols = 0;
    }
    int numCols = cols + 1;

    const char* hStr = _strstr(gridSpec, "_h=");
    if (hStr != nullptr && hStr != (char*)-3) {
        rows = parseColsOrRows();
    } else {
        rows = 0;
    }
    int numRows = rows + 1;

    // Source rectangle from first 16 floats of buffer->vertexData
    float* src = (float*)buffer->vertexData;
    float left = src[0x10];  // source u left?
    float top = src[0x11];   // source v top?
    float right = src[0x16]; // source u right?
    float bottom = src[0x17];// source v bottom?

    // Copy source rectangle data to global scratchpad
    float scratchRect[16]; // DAT_0119eac0
    memcpy(scratchRect, src, 16 * sizeof(float));

    // Global counter for vertex count
    int vertexCount = 0; // DAT_0119eafc

    float stepX = (left - right) / (float)cols;  // width step (note order: left - right?)
    float stepY = (top - bottom) / (float)rows;  // height step

    float* outVerts = (float*)0x0119eb00; // global output array
    float yCurrent = bottom; // start y
    if (numCols < numRows) {
        // Iterate rows first
        for (int r = 0; r < rows; r++) {
            if (numRows > 0) {
                vertexCount += numRows * 2;
                float xCurrent = right;
                for (int c = 0; c < numRows; c++) {
                    outVerts[1] = yCurrent;          // vertex1 y
                    outVerts[3] = yCurrent;          // vertex2 y
                    outVerts[0] = xCurrent;          // vertex1 x
                    outVerts[2] = xCurrent + stepX;  // vertex2 x
                    outVerts += 4;
                    yCurrent += stepY;
                }
            }
            // After row, adjust steps (this loop has a bug? It changes stepY and stepX)
            stepY = DAT_00e44564 - stepY;
            yCurrent += stepY;
            right = right + stepX;
        }
    } else {
        // Iterate columns first
        yCurrent = bottom;
        for (int c = 0; c < rows; c++) {
            if (numCols > 0) {
                vertexCount += numCols * 2;
                float xCurrent = right;
                for (int r = 0; r < numCols; r++) {
                    outVerts[0] = xCurrent;          // vertex1 x
                    outVerts[2] = xCurrent;          // vertex2 x
                    outVerts[1] = yCurrent;          // vertex1 y
                    outVerts[3] = yCurrent + stepY;  // vertex2 y
                    outVerts += 4;
                    xCurrent += stepX;
                }
            }
            stepX = DAT_00e44564 - stepX;
            xCurrent = right; // not used? Actually original code had xCurrent = right? Looks buggy.
            yCurrent = yCurrent + stepY;
        }
    }

    // Now allocate new buffer for the generated vertices
    size_t vertexDataSize = scratchRect[0]; // first float of source interpreted as size
    // Allocate via function pointer
    void* newBuffer = (**(code**)*(undefined4**)(DAT_012234ec + 4))(vertexDataSize, &local_14);
    // Actually local_14 was originally src? This part is ambiguous
    // We'll assume it allocates and copies the grid data
    buffer->vertexData = newBuffer;
    memcpy(newBuffer, scratchRect, vertexDataSize);
    buffer->vertexCount = vertexDataSize;
    buffer->someFlag = 0;

    // Call function to process the buffer (maybe update mesh)
    FUN_005c66c0(buffer);

    // Another allocation for the original source? 
    // Second allocation with size = bottom (src[0x17])
    void* originalBuffer = (**(code**)*(undefined4**)(DAT_012234ec + 4))(bottom, &local_14);
    buffer->vertexData = originalBuffer;
    memcpy(originalBuffer, src, bottom);
    buffer->someFlag = 0;
    buffer->vertexCount = bottom; // as float? This is messy
}