// FUN_NAME: Entity::computeTargetDistanceSq (address 0x006fd320)
float Entity::computeTargetDistanceSq() {
    // Check if the pointer at +0x10 (likely a component or interface holder) is valid
    if (this->pComponent != nullptr && reinterpret_cast<unsigned long>(this->pComponent) != 0x48) {
        // The pointer is actually an offset from the containing object? Subtract 0x48 to get base
        int* basePtr = reinterpret_cast<int*>(reinterpret_cast<unsigned long>(this->pComponent) - 0x48);
        int outInterface = 0;

        // Virtual call: (*basePtr)[0x10] is likely a type-identification function (e.g., getInterface)
        // Constant 0x38523fc3 could be an interface GUID or RTTI hash
        bool hasInterface = (reinterpret_cast<bool(__thiscall*)(void*, unsigned long, int*)>(
            (*reinterpret_cast<int**>(basePtr))[0x10 / 4]  // index 4 in vtable (since 0x10 bytes = 4 entries)
        ))(basePtr, 0x38523fc3, &outInterface);

        if (hasInterface) {
            // outInterface is now non-zero if the interface is found
            if (outInterface != 0) {
                // Check a global pointer (likely the player or target entity)
                int** globalPtr = reinterpret_cast<int**>(DAT_012233a0);
                if (globalPtr[1] != nullptr && reinterpret_cast<unsigned long>(globalPtr[1]) != 0x1f30) {
                    // Get position components from possibly internally tracked entities
                    // FUN_00471610 likely returns a pointer to a position structure (float x, y, z at +0x30, +0x34, +0x38)
                    int* posA = reinterpret_cast<int* (__fastcall*)()>(0x00471610)();
                    int* posB = reinterpret_cast<int* (__fastcall*)()>(0x00471610)();

                    float dx = *reinterpret_cast<float*>(posB + 0x30/4) - *reinterpret_cast<float*>(posA + 0x30/4);
                    float dy = *reinterpret_cast<float*>(posB + 0x34/4) - *reinterpret_cast<float*>(posA + 0x34/4);
                    float dz = *reinterpret_cast<float*>(posB + 0x38/4) - *reinterpret_cast<float*>(posA + 0x38/4);
                    return dx * dx + dy * dy + dz * dz;
                }
            }
        }
    }
    return 0.0f;
}