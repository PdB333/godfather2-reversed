// FUNC_NAME: Entity::setComponentPosition
// Function at 0x005e2320: Sets position data (Vec3) on a sub-component if a flag is set.
// Returns 1 on success, 0 on failure.
// This: in ECX (represented as in_EAX by Ghidra).
// Position pointer passed via EDI register.

struct Vec3 {
    float x, y, z;
};

int __thiscall Entity::setComponentPosition(void* this, const Vec3* position) {
    // Check if the component is enabled (offset 0x1744)
    char* enabledFlag = (char*)((int)this + 0x1744);
    if (*enabledFlag != 0) {
        // Get the sub-component pointer (FUN_005e2150)
        void* component = FUN_005e2150(this); // returns some object
        if (component != 0) {
            // Copy position into component's transform (offsets 0x288-0x290)
            float* destX = (float*)((int)component + 0x288);
            *destX = position->x;
            *(float*)((int)component + 0x28C) = position->y;
            *(float*)((int)component + 0x290) = position->z;
            return 1;
        }
    }
    return 0;
}