// FUNC_NAME: setGlobalOrientation
void setGlobalOrientation(OrientationData* data) {
    // Copy orientation quaternion (x, y, z, w) from input
    gOrientation.x = data->x;
    gOrientation.y = data->y;
    gOrientation.z = data->z;
    gOrientation.w = data->w;

    // Update flags with input's flag at offset 0x20
    gOrientationFlags |= data->flags;

    // If the "use default" flag (0x10000000) is set, reset to default orientation
    if ((gOrientationFlags & 0x10000000) != 0) {
        gOrientation.x = gDefaultOrientation.x;
        gOrientation.y = gDefaultOrientation.y;
        gOrientation.z = gDefaultOrientation.z;
        gOrientation.w = gDefaultOrientation.w;
        gOrientationFlags = 0x10000000;
    }
}