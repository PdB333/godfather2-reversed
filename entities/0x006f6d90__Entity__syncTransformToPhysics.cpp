// FUNC_NAME: Entity::syncTransformToPhysics
void __fastcall Entity::syncTransformToPhysics(Entity* thisPtr)
{
    // Check dirty transform flag (bit 1 at offset 0xf4)
    if ((*(uint32_t*)((uint8_t*)thisPtr + 0xf4) >> 1 & 1) != 0)
    {
        // Access global physics manager pointer (DAT_012233a0)
        // Verify the manager's vtable/type ID is valid and not a sentinel (0x1f30)
        if ((**(int***)(DAT_012233a0 + 4) != 0) && (**(int***)(DAT_012233a0 + 4) != (int*)0x1f30))
        {
            // Get the Havok rigid body associated with a global entity (DAT_0112a9fc)
            int* physBody = (int*)FUN_0043b870(DAT_0112a9fc);
            if (physBody != 0)
            {
                // Copy 4 floats (position/orientation) from entity's transform at +0xa4
                // to physics body's transform at +0xb0
                physBody[0x2c] = *(int*)((uint8_t*)thisPtr + 0xa4);  // +0xb0/4
                physBody[0x2d] = *(int*)((uint8_t*)thisPtr + 0xa8);  // +0xb4/4
                physBody[0x2e] = *(int*)((uint8_t*)thisPtr + 0xac);  // +0xb8/4
                physBody[0x2f] = *(int*)((uint8_t*)thisPtr + 0xb0);  // +0xbc/4
            }
        }
        // Clear dirty transform flag (bit 1)
        *(uint32_t*)((uint8_t*)thisPtr + 0xf4) &= 0xfffffffd;
    }
}