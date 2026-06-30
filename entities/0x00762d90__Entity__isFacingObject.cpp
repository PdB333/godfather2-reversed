// FUNC_NAME: Entity::isFacingObject
bool __fastcall Entity::isFacingObject(int this) {
    // Get pointer to some manager/transform source (e.g., camera or target)
    char* pTransformSrc1 = reinterpret_cast<char*>(FUN_00471610());  // first object's transform
    Vector3 diff;
    diff.x = *(float*)(pTransformSrc1 + 0x30);
    diff.y = *(float*)(pTransformSrc1 + 0x34);
    diff.z = *(float*)(pTransformSrc1 + 0x38);

    char* pTransformSrc2 = reinterpret_cast<char*>(FUN_00471610());  // second object's transform
    diff.x -= *(float*)(pTransformSrc2 + 0x30);
    diff.y -= *(float*)(pTransformSrc2 + 0x34);
    diff.z -= *(float*)(pTransformSrc2 + 0x38);

    // Normalize the direction vector to the target
    FUN_0056afa0(&diff, &diff); // likely normalize in place

    // Get object's forward direction at offsets 0xAC, 0xB0, 0xB4
    float forwardX = *(float*)(this + 0xAC);
    float forwardY = *(float*)(this + 0xB0);
    float forwardZ = *(float*)(this + 0xB4);

    // Compute dot product
    float dot = forwardX * diff.x + forwardY * diff.y + forwardZ * diff.z;

    // Compare with global threshold (likely configurable)
    if (g_facingThreshold <= dot) {
        return true;
    }
    return false;
}