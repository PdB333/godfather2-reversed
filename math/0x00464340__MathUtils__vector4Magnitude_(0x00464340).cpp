// FUNC_NAME: MathUtils::vector4Magnitude (0x00464340)
// Compute the Euclidean length (norm) of a 4D vector (float[4]).
// Assumes param_1 points to a contiguous array of at least 4 floats.
inline float vector4Magnitude(const float* v) {
    return std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);
}