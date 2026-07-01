// FUNC_NAME: Entity::applyBoneTransform
// Function address: 0x008dc750
// Role: Applies a 4-component transform (with fourth component zeroed) to the entity's skeleton if the skeleton and its associated data are initialized.

void __thiscall Entity::applyBoneTransform(const float* transformData)
{
    // Check skeleton pointer at +0x1BC and its internal data at +0x8.
    if (*(uint32_t*)(this + 0x1BC) != 0 && *(uint32_t*)(*(uint32_t*)(this + 0x1BC) + 8) != 0)
    {
        // Copy the incoming transform, forcing the fourth component to 0.
        float localTransform[4];
        localTransform[0] = transformData[0];
        localTransform[1] = transformData[1];
        localTransform[2] = transformData[2];
        localTransform[3] = 0.0f;

        // Apply the transform to the animation/skeleton system.
        // The second parameter (0) likely indicates a specific operation mode.
        FUN_009f1820(localTransform, 0);
    }
}