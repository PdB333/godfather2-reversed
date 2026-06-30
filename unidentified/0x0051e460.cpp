// FUNC_0051e460: Math::Vector4::clamp
// Clamps each component of this vector between the corresponding components of minVec and maxVec.
// This is a SSE-optimized implementation performing min then max.
// Parameters:
//   minVec - pointer to the minimum bound vector (16 bytes, 4 floats)
//   maxVec - pointer to the maximum bound vector (16 bytes, 4 floats)
void __thiscall Vector4::clamp(const Vector4* minVec, const Vector4* maxVec) {
    __m128& self = *(__m128*)m_data; // m_data is float[4] at offset 0x00
    __m128 minVal = *(__m128*)minVec->m_data;
    __m128 maxVal = *(__m128*)maxVec->m_data;
    __m128 clamped = _mm_min_ps(self, minVal);   // clamp lower
    clamped = _mm_max_ps(clamped, maxVal);       // clamp upper
    self = clamped;
}