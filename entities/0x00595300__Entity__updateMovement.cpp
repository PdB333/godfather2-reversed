// FUNC_NAME: Entity::updateMovement

void __thiscall Entity::updateMovement(float deltaTime) {
    // Call internal update logic (likely physics or animation)
    sub_00595490(deltaTime);

    // Check if some condition is active (e.g., movement input)
    char isActive = sub_00595610();
    if (isActive == '\0') {
        // Clear bit 9 (0x200) in flags at +0x7c
        *(uint32_t*)(this + 0x7c) &= ~0x200;
    } else {
        // Set bit 9 in flags
        *(uint32_t*)(this + 0x7c) |= 0x200;
    }

    // Virtual call on a sub-object at +0xc0 using a global vtable pointer
    // The function takes: (int, float, int, float, void*)
    // Arguments: 0, fieldAt0x158 * deltaTime, 0, 1.0f, pointer to sub-object
    // This likely performs a transformation (e.g., scale, lerp, or force application)
    (**(code**)(*(int*)DAT_012055a8 + 4))(
        0,
        *(float*)(this + 0x158) * deltaTime,
        0,
        0x3f800000,           // 1.0f
        (void*)(this + 0xc0)  // sub-object (matrix/vector)
    );
}