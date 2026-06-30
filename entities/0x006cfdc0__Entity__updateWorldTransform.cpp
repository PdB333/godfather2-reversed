// FUNC_NAME: Entity::updateWorldTransform
void __thiscall Entity::updateWorldTransform(uint param2) {
    // Check if the transform component exists (offset +0xD0 likely a flag or pointer to component)
    if (*(int*)(this + 0xD0) != 0) {
        // Get pointer to the transform data structure at +0xD8
        float* transformData = *(float**)(this + 0xD8);
        // Write a vector/quaternion from global constants into the transform data
        // Offsets relative to transformData: +0x10, +0x14, +0x18, +0x1C
        transformData[0x10 / 4] = _DAT_00d5f270;
        transformData[0x14 / 4] = _UNK_00d5f274;
        transformData[0x18 / 4] = _UNK_00d5f278;
        transformData[0x1C / 4] = _UNK_00d5f27c;
        // Notify external system (e.g., audio, physics) with param2
        FUN_004ec1c0(param2);
        // Update renderer or physics with the new transform
        FUN_004df830(transformData);
        // Finalize (e.g., mark dirty, broadcast)
        FUN_006cf860();
    }
}