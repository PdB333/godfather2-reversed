// FUNC_NAME: BaseEntity::initEntity
void __thiscall BaseEntity::initEntity(int param2, int param3, int param4)
{
    // +0x24: entityIdLow, +0x28: entityIdHigh
    // +0x30: positionX, +0x34: positionY, +0x38: positionZ
    // +0x3c: someConstant (presumably a world pointer or global)
    // +0x40: param2 (e.g., size or rotation)
    // +0x44: param3 (e.g., scale or time)
    // +0x48: active flag (boolean)

    *(undefined4 *)(this + 0x30) = 0;
    *(undefined4 *)(this + 0x34) = 0;
    *(undefined4 *)(this + 0x38) = 0;
    *(undefined4 *)(this + 0x3c) = _DAT_00d5780c;  // global constant
    *(undefined4 *)(this + 0x40) = param2;
    *(undefined4 *)(this + 0x44) = param3;

    if (param4 != 0)
    {
        // Param4 likely a resource or asset object with a vtable at +0x58
        // Calling its getID or getHash function (function pointer from vtable entry 1)
        undefined4 *puVar1 = (undefined4 *)(**(code **)(*(int *)(param4 + 0x58) + 4))(local_8);
        *(undefined4 *)(this + 0x24) = *puVar1;
        *(undefined4 *)(this + 0x28) = puVar1[1];
    }

    *(undefined1 *)(this + 0x48) = 0;  // set active flag to false

    FUN_00408680(&DAT_012069c4);  // likely a lock or reference counter increment
    FUN_00481530();               // likely a global state update
    return;
}