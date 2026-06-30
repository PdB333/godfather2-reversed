// FUNC_NAME: BoundingShape::computeAABB
// Address: 0x00522100
// Computes axis-aligned bounding box (min and max) from 3 stored vectors (this points to first, then two more).
// Uses SSE minps/maxps for component-wise min/max over 4 floats.

void __thiscall BoundingShape::computeAABB(__m128* outMin, __m128* outMax) const
{
    // Load first vertex
    __m128 v0 = _mm_load_ps(reinterpret_cast<const float*>(this));
    _mm_store_ps(reinterpret_cast<float*>(outMin), v0);
    _mm_store_ps(reinterpret_cast<float*>(outMax), v0);

    // Process remaining two vertices (stored at this+0x10, this+0x20)
    for (int i = 1; i < 3; ++i)
    {
        __m128 vi = _mm_load_ps(reinterpret_cast<const float*>(this) + i * 4);
        *outMin = _mm_min_ps(*outMin, vi);
        *outMax = _mm_max_ps(*outMax, vi);
    }
}