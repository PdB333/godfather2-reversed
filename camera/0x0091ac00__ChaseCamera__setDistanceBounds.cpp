// FUNC_NAME: ChaseCamera::setDistanceBounds

void __thiscall ChaseCamera::setDistanceBounds(ChaseCamera* this, uint cameraStateIndex)
{
    uint64 hashResult;
    int targetDistance;

    hashResult = FUN_00916c70(cameraStateIndex); // compute hash/ID from state index, returns 64-bit value
    DAT_00e54d0c = (uint32)(hashResult >> 32); // store high part globally (likely a timer or version)
    targetDistance = *(int*)(*(int*)((int)this + 0xa8) + (int)hashResult * 4); // get base distance from camera config array at this+0xa8
    DAT_00e54d24 = 1; // default min distance
    if (0x1e < targetDistance) {
        DAT_00e54d24 = targetDistance - 0x1e; // min = target - 30 units
    }
    DAT_00e54d20 = targetDistance + 0x1e; // max = target + 30 units
    DAT_00e54d28 = DAT_00e54d20; // current max copy
    DAT_00e54d2c = DAT_00e54d24; // current min copy
    FUN_009199b0(1); // update camera ranges (e.g., clamp, notify)
    if (*(char*)((int)this + 0xbd) != '\0') {
        *(byte*)((int)this + 0xbc) = 1; // set lock flag (0xbc)
        *(byte*)((int)this + 0xbd) = 0; // clear pending flag (0xbd)
    }
    return;
}