// FUNC_NAME: Entity::applyDirectionalOffset
void __thiscall Entity::applyDirectionalOffset(int this, int *manager)
{
    undefined4 roundedValue;
    float *dataPtr;
    int playerTransform;
    float vNorm[3];
    float factor;
    float speed;
    float dx, dy, dz;
    undefined4 transformResult[3];

    // State check: only apply if in state 4 (e.g., "aiming" or "moving")
    if (*(int *)(this + 0x40) == 4) {
        // Resolve data source: if manager[0x6f1] provides a valid pointer, use it; otherwise fallback to default
        undefined *dataSource;
        if ((manager[0x6f1] == 0) ||
            (dataSource = *(undefined **)(manager[0x6f1] + 0x38), dataSource == (undefined *)0x0)) {
            dataSource = &DAT_00e53b50;  // default data block
        }

        // Round the float at offset 0xc0 to get index/resource ID
        roundedValue = (undefined4)(longlong)ROUND(*(float *)(dataSource + 0xc0));

        // Look up that resource and get a pointer to vector data
        undefined4 resourceHandle = FUN_006eb670(roundedValue);
        dataPtr = (float *)FUN_007f9780(resourceHandle);

        // Get the current player/camera transform (expected to contain a forward vector)
        playerTransform = FUN_00471610();

        // Extract forward direction from transform (offsets 0x20, 0x24, 0x28 likely part of a matrix)
        vNorm[0] = *(float *)(playerTransform + 0x20);
        vNorm[1] = *(float *)(playerTransform + 0x24);
        vNorm[2] = *(float *)(playerTransform + 0x28);

        // Normalize the direction vector (in-place)
        FUN_0056afa0(vNorm, vNorm);

        // Get speed factor: vtable call at (+0x1c0) returns some scalar, multiply by global constant
        speed = (float)((**(code **)(*manager + 0x1c0))() * (float10)DAT_00d5779c);

        // Compute movement offset in that direction
        dx = vNorm[0] * speed;
        dy = vNorm[1] * speed;
        dz = vNorm[2] * speed;

        // Second transformation: get a rotated version of the motion vector
        playerTransform = FUN_00471610();
        float inputVector[3];
        inputVector[0] = *dataPtr;        // from looked-up data
        inputVector[1] = dataPtr[1];
        inputVector[2] = dataPtr[2];

        // Use global constant for identity (perhaps default orientation)
        // Note: _DAT_00d5780c is an undefined4 constant used here
        FUN_0056b420(playerTransform, inputVector, transformResult);

        // Write transformed vector into this object's position
        *(undefined4 *)(this + 0x14) = transformResult[0];
        *(undefined4 *)(this + 0x18) = transformResult[1];
        *(undefined4 *)(this + 0x1c) = transformResult[2];

        // Add the directional offset to the position
        *(float *)(this + 0x14) = *(float *)(this + 0x14) + dx;
        *(float *)(this + 0x18) = *(float *)(this + 0x18) + dy;
        *(float *)(this + 0x1c) = *(float *)(this + 0x1c) + dz;
    }
    return;
}