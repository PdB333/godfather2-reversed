// FUNC_NAME: Entity::setTransform
// Address: 0x006c7d60
// This function sets the transform of an entity from a source transform structure.
// It extracts position, rotation, and a scalar factor, storing them into multiple
// transform slots (current, previous, etc.).

void __thiscall Entity::setTransform(int thisPtr, uint transformSource, char updatePhysics)
{
    float localTransformBuffer[3]; // 12 bytes, used as temporary storage

    // Extract position (3 floats) and pad with global constant (likely 1.0f for homogeneous coordinate)
    float* posData = (float*)FUN_00425060(localTransformBuffer, transformSource);
    *(float*)(thisPtr + 0x40) = posData[0]; // position.x
    *(float*)(thisPtr + 0x44) = posData[1]; // position.y
    *(float*)(thisPtr + 0x48) = posData[2]; // position.z
    *(float*)(thisPtr + 0x4C) = _DAT_00d5780c; // w component (constant, e.g., 1.0)

    // Extract rotation quaternion or orientation (3 floats) and pad with same constant
    float* rotData = (float*)FUN_00424fb0(localTransformBuffer, transformSource);
    *(float*)(thisPtr + 0x20) = rotData[0]; // quaternion.x (or rotation axis)
    *(float*)(thisPtr + 0x24) = rotData[1]; // quaternion.y
    *(float*)(thisPtr + 0x28) = rotData[2]; // quaternion.z
    *(float*)(thisPtr + 0x2C) = _DAT_00d5780c; // quaternion.w (constant, e.g., 1.0)

    // Copy the position and rotation into additional transform slots (likely previous and interpolation)
    // Slot at +0x22C (previous world position?)
    *(float*)(thisPtr + 0x22C) = *(float*)(thisPtr + 0x40);
    *(float*)(thisPtr + 0x230) = *(float*)(thisPtr + 0x44);
    *(float*)(thisPtr + 0x234) = *(float*)(thisPtr + 0x48);

    // Slot at +0x208 (also position)
    *(float*)(thisPtr + 0x208) = *(float*)(thisPtr + 0x40);
    *(float*)(thisPtr + 0x20C) = *(float*)(thisPtr + 0x44);
    *(float*)(thisPtr + 0x210) = *(float*)(thisPtr + 0x48);

    // Slot at +0x238 (previous local rotation?)
    *(float*)(thisPtr + 0x238) = *(float*)(thisPtr + 0x20);
    *(float*)(thisPtr + 0x23C) = *(float*)(thisPtr + 0x24);
    *(float*)(thisPtr + 0x240) = *(float*)(thisPtr + 0x28);

    // Slot at +0x214 (also rotation)
    *(float*)(thisPtr + 0x214) = *(float*)(thisPtr + 0x20);
    *(float*)(thisPtr + 0x218) = *(float*)(thisPtr + 0x24);
    *(float*)(thisPtr + 0x21C) = *(float*)(thisPtr + 0x28);

    // Extract additional scalar (linear speed? time? scale?) and store at +0x50
    float scalar = (float)FUN_004250f0(transformSource);
    *(float*)(thisPtr + 0x50) = scalar;

    // If the update flag is set, refresh physics or collision data
    if (updatePhysics != 0) {
        FUN_006c5c70(); // likely updates bounding box or physics representation
    }
}