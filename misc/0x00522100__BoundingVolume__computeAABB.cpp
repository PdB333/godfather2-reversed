// FUNC_NAME: BoundingVolume::computeAABB
void __thiscall BoundingVolume::computeAABB(float outMin[4], float outMax[4]) {
    // 'this' points to an array of three 16-byte vectors (float4) representing points or positions
    // First vector at offset 0, second at +0x10, third at +0x20
    __m128 first = _mm_load_ps(reinterpret_cast<const float*>(this));
    _mm_store_ps(outMin, first);
    _mm_store_ps(outMax, first);

    // Process the remaining two vectors (offsets +0x10 and +0x20)
    const float* points = reinterpret_cast<const float*>(reinterpret_cast<const uint8_t*>(this) + 16);
    for (int i = 0; i < 2; ++i) {
        __m128 v = _mm_load_ps(points);
        _mm_store_ps(outMin, _mm_min_ps(_mm_load_ps(outMin), v));
        _mm_store_ps(outMax, _mm_max_ps(_mm_load_ps(outMax), v));
        points += 4; // advance by 16 bytes (4 floats)
    }
}