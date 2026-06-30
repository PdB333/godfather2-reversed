// FUNC_NAME: AreaTrigger::isPointInside
// Function at 0x006b7660: Checks if a transformed 3D point lies within world bounds.
// Uses a matrix at this+0x60 (likely a local-to-world transform) and global min/max bounds.
bool AreaTrigger::isPointInside(const Vector3* point) {
    // Copy input point to local storage
    Vector3 localPoint = *point;

    // Unused global (likely a timing value or leftover)
    float unused = _DAT_00d5780c; // +0x00d5780c

    // Transform point via matrix at this+0x60 into local space
    Vector3 transformed; // {local_20, local_1c, local_18}
    FUN_0056b420(this + 0x60, &localPoint, &transformed);

    // World bounds check using global min/max for each axis
    // Globals: DAT_00e44718 (min), _DAT_00d5c458 (max)
    if (transformed.x >= DAT_00e44718 && transformed.x <= _DAT_00d5c458 &&
        transformed.y >= DAT_00e44718 && transformed.y <= _DAT_00d5c458 &&
        transformed.z >= DAT_00e44718 && transformed.z <= _DAT_00d5c458) {
        return true;
    }
    return false;
}