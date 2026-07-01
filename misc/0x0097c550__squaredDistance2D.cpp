// FUNC_NAME: squaredDistance2D
// Address: 0x0097c550
// Computes the squared Euclidean distance between a 2D point stored in an object
// (at offsets 0x10 and 0x18) and a 2D point given as a float array (with x at [0] and y at [2]).
// Returns a double (extended precision in original x87 code).

double squaredDistance2D(const void* object, const float* point) {
    // Object's position: x at +0x10, y at +0x18 (likely part of a 3D vector with z at +0x20)
    float objX = *(const float*)((const char*)object + 0x10);
    float objY = *(const float*)((const char*)object + 0x18);

    // Input point: x at index 0, y at index 2 (probably due to padding or array indexing)
    float ptX = point[0];
    float ptY = point[2];

    double dx = static_cast<double>(objX - ptX);
    double dy = static_cast<double>(objY - ptY);

    return dx * dx + dy * dy;
}