// FUNC_NAME: UnknownClass::checkDistanceToTarget
// Address: 0x007452b0
// This function compares the squared distance between two positions (obtained via FUN_00471610) against a threshold.
// The positions are stored as floats at offsets +0x30, +0x34, +0x38 from the returned pointers.
// The return value is a packed 32-bit value: high 24 bits encode part of the second position's address,
// low 8 bits set to 1 if out-of-range, 0 if within range.

int __thiscall UnknownClass::checkDistanceToTarget(float maxDistance)
{
    // Read pointer to a component at +0x5C
    int* pComponent = *(int**)(this + 0x5C);
    if (pComponent != nullptr)
    {
        // Derive a container pointer by subtracting 0x48 from the component pointer
        int* pContainer = (int*)((uint8_t*)pComponent - 0x48);
        if (pContainer != nullptr)
        {
            // Get two position pointers (likely self and target)
            float* pPos1 = (float*)FUN_00471610(); // Position of first entity
            float* pPos2 = (float*)FUN_00471610(); // Position of second entity

            // Compute squared distance between positions
            float dx = pPos1[0x30 / 4] - pPos2[0x30 / 4]; // x at +0x30
            float dy = pPos1[0x34 / 4] - pPos2[0x34 / 4]; // y at +0x34
            float dz = pPos1[0x38 / 4] - pPos2[0x38 / 4]; // z at +0x38
            float distanceSq = dx*dx + dy*dy + dz*dz;

            // Extract 24-bit identifier from pPos2 address (shift right 8 bits)
            uint32_t addrPart = ((uint32_t)(pPos2 + 0x30 / 4)) >> 8;
            uint32_t result;

            if (distanceSq <= maxDistance)
            {
                // Within range: low byte 0
                result = (addrPart << 8) & 0xFFFFFF00;
            }
            else
            {
                // Out of range: low byte 1
                result = (addrPart << 8) | 0x1;
            }
            return result;
        }
    }

    // Fallback: use pComponent address to derive identifier
    uint32_t addrPart = ((uint32_t)pComponent) >> 8;
    return (addrPart << 8) | 0x1;
}