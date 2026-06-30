// FUNC_NAME: Entity::copyOrientationTo
void __thiscall Entity::copyOrientationTo(Entity* source, Entity* target)
{
    // Copy quaternion rotation from source+0x10 to target+0xA0
    float* srcRotation = (float*)((uint8_t*)source + 0x10);
    float* dstRotation = (float*)((uint8_t*)target + 0xA0);

    dstRotation[0] = srcRotation[0]; // +0x10 -> +0xA0 (x)
    dstRotation[1] = srcRotation[1]; // +0x14 -> +0xA4 (y)
    dstRotation[2] = srcRotation[2]; // +0x18 -> +0xA8 (z)
    dstRotation[3] = srcRotation[3]; // +0x1C -> +0xAC (w)

    // Apply rotation update (global function at 0x004338A0)
    applyRotationUpdate();
}