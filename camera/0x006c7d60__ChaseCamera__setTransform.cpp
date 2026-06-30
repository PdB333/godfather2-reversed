// FUNC_NAME: ChaseCamera::setTransform

void __thiscall ChaseCamera::setTransform(int this, void* transform, bool updateImmediate)
{
    // Temporary array for extracting rotation/quaternion (3 floats)
    float temp[3]; // Not explicitly used as output, passed to subfunctions

    // Extract orientation (likely quaternion) from transform source
    // FUN_00425060 may return pointer to rotation data (x,y,z) stored in temp
    undefined4* rotPtr = (undefined4*)FUN_00425060(temp, transform);

    // +0x40: current orientation.x, +0x44: current orientation.y, +0x48: current orientation.z
    *(undefined4*)(this + 0x40) = rotPtr[0];
    *(undefined4*)(this + 0x44) = rotPtr[1];
    *(undefined4*)(this + 0x48) = rotPtr[2];
    // +0x4c: fourth component (scale or w) – taken from global _DAT_00d5780c
    *(undefined4*)(this + 0x4c) = _DAT_00d5780c;

    // Extract position from transform
    // FUN_00424fb0 returns pointer to position data (x,y,z)
    undefined4* posPtr = (undefined4*)FUN_00424fb0(temp, transform);

    // +0x20: current position.x, +0x24: current position.y, +0x28: current position.z
    *(undefined4*)(this + 0x20) = posPtr[0];
    *(undefined4*)(this + 0x24) = posPtr[1];
    *(undefined4*)(this + 0x28) = posPtr[2];
    // +0x2c: fourth component for position (scale or w)
    *(undefined4*)(this + 0x2c) = _DAT_00d5780c;

    // Copy orientation to interpolated/target orientation fields
    // +0x22c..+0x234: target orientation (interpolated)
    *(undefined4*)(this + 0x22c) = *(undefined4*)(this + 0x40);
    *(undefined4*)(this + 0x230) = *(undefined4*)(this + 0x44);
    *(undefined4*)(this + 0x234) = *(undefined4*)(this + 0x48);
    // +0x208..+0x210: secondary orientation (maybe previous frame)
    *(undefined4*)(this + 0x208) = *(undefined4*)(this + 0x40);
    *(undefined4*)(this + 0x20c) = *(undefined4*)(this + 0x44);
    *(undefined4*)(this + 0x210) = *(undefined4*)(this + 0x48);

    // Copy position to interpolated/target position fields
    // +0x238..+0x240: target position
    *(undefined4*)(this + 0x238) = *(undefined4*)(this + 0x20);
    *(undefined4*)(this + 0x23c) = *(undefined4*)(this + 0x24);
    *(undefined4*)(this + 0x240) = *(undefined4*)(this + 0x28);
    // +0x214..+0x21c: secondary position
    *(undefined4*)(this + 0x214) = *(undefined4*)(this + 0x20);
    *(undefined4*)(this + 0x218) = *(undefined4*)(this + 0x24);
    *(undefined4*)(this + 0x21c) = *(undefined4*)(this + 0x28);

    // Extract a scalar (maybe field of view or zoom) using FUN_004250f0
    float fov = (float)FUN_004250f0(transform);
    *(float*)(this + 0x50) = fov;

    // If immediate update requested, call a helper to reset interpolation smoothing
    if (updateImmediate)
    {
        FUN_006c5c70(); // Presumably resets interpolation state
    }
}