// FUNC_NAME: setGlobalTransform
// Copies a transform (quaternion + translation) from a 7-float array to global state.
// The input is a pointer to floats in the order: quat.x, quat.y, quat.z, quat.w, pos.x, pos.y, pos.z.
void setGlobalTransform(const float* transform)
{
    // Each 64-bit global stores two consecutive floats from the array.
    _DAT_0120ec6c = *(const uint64_t*)&transform[0]; // quat.x, quat.y
    _DAT_0120ec74 = *(const uint64_t*)&transform[2]; // quat.z, quat.w
    _DAT_0120ec7c = *(const uint64_t*)&transform[4]; // pos.x, pos.y
    DAT_0120ec84 = *(const uint32_t*)&transform[6];  // pos.z
}