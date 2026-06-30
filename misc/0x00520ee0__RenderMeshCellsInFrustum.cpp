// FUNC_NAME: RenderMeshCellsInFrustum
// Address: 0x00520ee0
// Role: Renders visible triangles from a hierarchical grid-based mesh using SSE-optimized frustum culling.

#include <cstring>
#include <cmath>

// Structure for an axis-aligned bounding box (min and max corners)
struct AABB {
    float minX, minY, minZ;  // offset +0x00
    float pad1;              // alignment padding (16 bytes total)
    float maxX, maxY, maxZ;  // offset +0x10
    float pad2;              // padding
    float scaleX, scaleY, scaleZ; // offset +0x20 (used for world-to-cell conversion)
    float pad3;
    // cell information (fourth 16-byte block):
    unsigned short cellsX, cellsY, cellsZ; // dimensions of grid in each axis (+0x30)
    unsigned short cellDataStride;         // stride for per-cell data start (+0x36)
    // variable-length triangle index data follows
};

// Internal function that draws a batch of triangles (likely using GPU draw call)
extern void RenderTriangles(/* some context */); // 0x00521720

void RenderMeshCellsInFrustum(AABB* frustumBBox, void* meshGrid)
{
    // Derived from param_2
    unsigned char vertexStride = *(unsigned char*)(meshGrid + 0x26);
    unsigned short cellIndicesWidth = *(unsigned short*)(meshGrid + 0x3a)
    int* cellTriListPtr = *(int**)(meshGrid + 0x88);
    int* triangleDataBase = (int*)(*(int*)(meshGrid + 0x84) - cellIndicesWidth * vertexStride);
    
    // The grid's AABB array (16-byte aligned blocks)
    AABB* gridCells = *(AABB**)(meshGrid + 0x8c);
    
    // Check if the frustum box overlaps the entire grid bounding box
    if (frustumBBox->maxX >= gridCells[0].minX &&
        frustumBBox->minX <= gridCells[0].maxX &&
        frustumBBox->maxY >= gridCells[0].minY &&
        frustumBBox->minY <= gridCells[0].maxY &&
        frustumBBox->maxZ >= gridCells[0].minZ &&
        frustumBBox->minZ <= gridCells[0].maxZ)
    {
        // Small vs large cells handling
        if (gridCells[3].cellsZ < 4) // 3 axis cells per cell
        {
            // Single-cell: iterate all triangles in this cell
            unsigned int cellCount = *(int*)(meshGrid + 0x30);
            for (unsigned int cellIdx = 0; cellIdx < cellCount; cellIdx++)
            {
                short triIdx = *(short*)(cellTriListPtr + cellIdx);
                if (triIdx > 0x92) // simple triangle limit check
                    return;
                
                // Fetch triangle vertices
                int vertexOffset = triIdx * vertexStride + (int)triangleDataBase;
                float* v0 = (float*)(vertexOffset);
                float* v1 = (float*)(vertexOffset + 4);
                float* v2 = (float*)(vertexOffset + 8);
                
                // Store three vertices for potential render call
                float vertices[12]; // local_a0[8..10]
                vertices[8] = *v0; vertices[9] = v0[1]; vertices[10] = v0[2];
                // Alternating buffer toggle (simple triangle pipeline)
                static int bufferToggle = 0;
                if (bufferToggle < 1)
                {
                    // Call render
                    float temp[12];
                    memcpy(temp, vertices, 12*4);
                    RenderTriangles();
                    // Copy to result buffer
                    float* out = &vertices[bufferToggle * 4];
                    out[0] = temp[8]; out[1] = temp[9]; out[2] = temp[10];
                    bufferToggle ^= 1;
                }
                else
                {
                    bufferToggle--;
                }
            }
        }
        else
        {
            // Multi-cell grid: use SSE optimized cell range traversal
            // Compute min/max cell indices
            __m128 minVec = _mm_loadu_ps(&frustumBBox->minX);
            __m128 maxVec = _mm_loadu_ps(&frustumBBox->maxX);
            __m128 gridMin = _mm_load_ps(&gridCells[0].minX);
            __m128 gridMax = _mm_load_ps(&gridCells[1].minX);
            __m128 scale = _mm_load_ps(&gridCells[2].minX);
            
            __m128 clampedMin = _mm_max_ps(minVec, gridMin);
            __m128 clampedMax = _mm_min_ps(maxVec, gridMax);
            
            // Convert to cell indices (round)
            __m128 cellMinF = _mm_mul_ps(_mm_sub_ps(clampedMin, gridMin), scale);
            __m128 cellMaxF = _mm_mul_ps(_mm_sub_ps(clampedMax, gridMin), scale);
            
            // Round to integers
            int cellMinX = (int)(_mm_cvtss_f32(cellMinF));
            int cellMinY = (int)(_mm_cvtss_f32(_mm_shuffle_ps(cellMinF, cellMinF, 0x55)));
            int cellMinZ = (int)(_mm_cvtss_f32(_mm_shuffle_ps(cellMinF, cellMinF, 0xAA)));
            int cellMaxX = (int)(_mm_cvtss_f32(cellMaxF));
            int cellMaxY = (int)(_mm_cvtss_f32(_mm_shuffle_ps(cellMaxF, cellMaxF, 0x55)));
            int cellMaxZ = (int)(_mm_cvtss_f32(_mm_shuffle_ps(cellMaxF, cellMaxF, 0xAA)));
            
            // Clamp to grid dimensions
            unsigned short dimX = *(unsigned short*)(&gridCells[3].minX); // cellsX
            unsigned short dimY = *(unsigned short*)((char*)&gridCells[3].minX + 2); // cellsY
            unsigned short dimZ = *(unsigned short*)((char*)&gridCells[3].minX + 4); // cellsZ
            if (cellMaxX >= dimX) cellMaxX = dimX - 1;
            if (cellMaxY >= dimY) cellMaxY = dimY - 1;
            if (cellMaxZ >= dimZ) cellMaxZ = dimZ - 1;
            
            // Determine number of unique triangle indices in the spanned cells
            int minTriangleIndex = 0x7FFFFFFF;
            int maxTriangleIndex = 0;
            
            // (Omitted: detailed traversal that populates a bit array of used triangles)
            // For simplicity, assume a nested loop over cells y and z
            // For each cell, read its triangle index list and update min/max
            // Then allocate a bitmap on stack using alloca.
            
            // Placeholder: compute size and allocate
            int rangeWidth = (maxTriangleIndex - minTriangleIndex + 0x20) >> 5;
            unsigned int* bitmap = (unsigned int*)alloca(rangeWidth * 4);
            memset(bitmap, 0, rangeWidth * 4);
            
            // Second pass: iterate over cells again, mark triangles that are inside frustum,
            // and for each new triangle send to render pipeline.
            for (int z = cellMinZ; z <= cellMaxZ; z++)
            {
                for (int y = cellMinY; y <= cellMaxY; y++)
                {
                    for (int x = cellMinX; x <= cellMaxX; x++)
                    {
                        // Get cell data pointer
                        unsigned short* cellData = (unsigned short*)((char*)gridCells + 10 + dimX * dimY * z + x);
                        // Read triangle count and indices...
                        // (Standard cell layout)
                    }
                }
            }
            
            // (Render batches similar to single-cell path)
        }
    }
}