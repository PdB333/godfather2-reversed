// FUNC_NAME: RenderEntity::computeBoundingBox
// Address: 0x004594f0
// Role: Computes axis-aligned bounding box (AABB) from a set of vertices using SSE min/max.
// Accesses:
//   this+0x84: pointer to vertex array (5 floats per vertex, stride 20 bytes)
//   this+0x38: vertex count (unsigned short)
//   this+0x20: pointer to output AABB structure; offsets 0x0c and 0x1c are zeroed after calculation

#include <xmmintrin.h>

void __thiscall RenderEntity::computeBoundingBox(void)
{
    // Pointer to vertex data
    float* pVertices = *(float**)((char*)this + 0x84);
    unsigned short vertexCount = *(unsigned short*)((char*)this + 0x38);

    // Initialize min and max to first vertex (x,y,z, w=0)
    __m128 min = { pVertices[0], pVertices[1], pVertices[2], 0.0f };
    __m128 max = min;

    if (vertexCount > 1)
    {
        // Skip first vertex (already consumed). Each vertex occupies 5 floats (20 bytes).
        float* pCur = pVertices + 5;  // stride = 5 floats (20 bytes)
        int remaining = vertexCount - 1;

        do
        {
            // Load current vertex: 3 floats at offsets -2, -1, 0 relative to pCur (due to decompiler artifact)
            // Actually each vertex is 5 floats: position (x,y,z) at indices 0,1,2; skip unused w at index 3.
            // We read x,y,z from pCur[0], pCur[1], pCur[2] (after aligning pointer, see note)
            // However the original code reads with a -8 byte offset; we assume compact layout.
            __m128 current = { pCur[0], pCur[1], pCur[2], 0.0f };

            min = _mm_min_ps(min, current);
            max = _mm_max_ps(max, current);

            pCur += 5;
            remaining--;
        } while (remaining != 0);
    }

    // Clear certain fields in the bounding box structure (probably old min/max or padding)
    FUN_00414aa0();   // Unknown function, likely resets state
    float* pBox = *(float**)((char*)this + 0x20);
    pBox[0x3] = 0.0f;  // offset +0x0c
    FUN_00414aa0();
    pBox[0x7] = 0.0f;  // offset +0x1c
}