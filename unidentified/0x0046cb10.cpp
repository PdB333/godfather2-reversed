// FUN_0046cb10: vec3Magnitude
float vec3Magnitude(const float* v) {
    // Compute Euclidean norm of a 3D vector: sqrt(x^2 + y^2 + z^2)
    return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}