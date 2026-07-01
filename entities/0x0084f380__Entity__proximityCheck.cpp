// FUNC_NAME: Entity::proximityCheck
undefined4 Entity::proximityCheck(float *position, Entity *triggerObject, undefined4 param_3)
{
    float entityPosX, entityPosY; // local_c and fStack_8 represent a 2D position?
    float dx, dy, dz;
    float triggerPosY;

    dx = *position;
    dz = position[2];
    dy = position[1] + _DAT_00d5cf70; // unknown offset

    // Get trigger object's position via vtable function at offset 0x48
    (**(code **)(*triggerObject + 0x48))(&entityPosX);

    dx = dx - entityPosX;

    if (((float)((uint)dx & DAT_00e44680) <= DAT_00d74f4c) &&
        (dy = dy - entityPosY,
         dy * dy + dx * dx + (_EBX - dz) * (_EBX - dz) <= _DAT_00d5fb0c))
    {
        // Within radius, call trigger event via vtable function at offset 0x10
        (**(code **)(*triggerObject + 0x10))(0xa0d329d6, &stack0x00000000);
    }

    // Call base class implementation
    return FUN_004b0b50(position, triggerObject, triggerObject, param_3);
}