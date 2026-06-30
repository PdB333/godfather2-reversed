// FUNC_NAME: InputDeviceManager::setupAxisDefinitions
int __fastcall InputDeviceManager::setupAxisDefinitions(int this_)
{
    void* axisList;
    uint64_t* axisEntry;
    int result;
    int globalSensitivity; // from _DAT_00d5780c
    int invertSensitivity; // from DAT_00d5ccf8

    // Allocate a new axis entry block (size 0x2C = 44 bytes)
    axisList = FUN_009c8e50(0x2C);
    if (axisList != NULL) {
        *(uint32_t*)axisList = 0;           // offset +0x00: prev pointer (init to 0)
    }
    if ((byte*)axisList + 4 != NULL) {
        *(uint32_t*)((byte*)axisList + 4) = 0; // offset +0x04: next pointer
    }
    if ((byte*)axisList + 8 != NULL) {
        *(uint32_t*)((byte*)axisList + 8) = 0; // offset +0x08: some self pointer
    }

    globalSensitivity = _DAT_00d5780c; // global default sensitivity/deadzone
    *(int8_t*)((int)axisList + 0x28) = 1;   // offset +0x28: flag (active?)
    *(int32_t*)(this_ + 4) = (int)axisList; // store pointer to axis list head
    *(int8_t*)((int)axisList + 0x29) = 1;   // offset +0x29: another flag
    // Set up circular linked list: prev/next/self point to itself
    *(int*)(*(int*)(this_ + 4) + 4) = *(int*)(this_ + 4); // offset +0x04 = this
    *(uint32_t*)*(uint32_t*)(this_ + 4) = *(uint32_t*)(this_ + 4); // offset +0x00 = this
    *(int*)(*(int*)(this_ + 4) + 8) = *(int*)(this_ + 4); // offset +0x08 = this
    *(uint32_t*)(this_ + 8) = 0; // some count or next free slot

    // Register each axis with its name and code, using non-inverted sensitivity
    FUN_004d3bc0("X-Axis"); // likely registerAxisName
    axisEntry = (uint64_t*)FUN_00696ed0(&result);
    *axisEntry = 0; // axis code: 0 (no invert, X axis)
    *(uint32_t*)(axisEntry + 1) = globalSensitivity;
    if (result != 0) {
        ((void (*)(int))local_4)(result);
    }

    FUN_004d3bc0("Y-Axis");
    axisEntry = (uint64_t*)FUN_00696ed0(&result);
    *axisEntry = 0x100000000ULL; // axis code: Y axis, no invert (1<<32)
    *(uint32_t*)(axisEntry + 1) = globalSensitivity;
    if (result != 0) {
        ((void (*)(int))local_4)(result);
    }

    FUN_004d3bc0("Z-Axis");
    axisEntry = (uint64_t*)FUN_00696ed0(&result);
    *axisEntry = 0x400000000ULL; // axis code: Z axis (4<<32)
    *(uint32_t*)(axisEntry + 1) = globalSensitivity;
    if (result != 0) {
        ((void (*)(int))local_4)(result);
    }

    FUN_004d3bc0("Z-Rotation");
    axisEntry = (uint64_t*)FUN_00696ed0(&result);
    *axisEntry = 0x500000000ULL; // axis code: Z rotation
    *(uint32_t*)(axisEntry + 1) = globalSensitivity;
    if (result != 0) {
        ((void (*)(int))local_4)(result);
    }

    FUN_004d3bc0("Throttle");
    axisEntry = (uint64_t*)FUN_00696ed0(&result);
    *axisEntry = 0x600000000ULL; // axis code: Throttle
    *(uint32_t*)(axisEntry + 1) = globalSensitivity;
    if (result != 0) {
        ((void (*)(int))local_4)(result);
    }

    FUN_004d3bc0("Rudder");
    axisEntry = (uint64_t*)FUN_00696ed0(&result);
    *axisEntry = 0x700000000ULL; // axis code: Rudder
    *(uint32_t*)(axisEntry + 1) = globalSensitivity;
    if (result != 0) {
        ((void (*)(int))local_4)(result);
    }

    // Now register inverted versions with different sensitivity
    invertSensitivity = DAT_00d5ccf8; // global for inverted axes
    FUN_004d3bc0("X-Axis.Inverted");
    axisEntry = (uint64_t*)FUN_00696ed0(&result);
    *axisEntry = 0; // same axis code but inverted? Actually no bit set? Wait: inverted flag might be separate.
    *(uint32_t*)(axisEntry + 1) = invertSensitivity;
    if (result != 0) {
        ((void (*)(int))local_4)(result);
    }

    FUN_004d3bc0("Y-Axis.Inverted");
    axisEntry = (uint64_t*)FUN_00696ed0(&result);
    *axisEntry = 0x100000000ULL;
    *(uint32_t*)(axisEntry + 1) = invertSensitivity;
    if (result != 0) {
        ((void (*)(int))local_4)(result);
    }

    FUN_004d3bc0("Z-Axis.Inverted");
    axisEntry = (uint64_t*)FUN_00696ed0(&result);
    *axisEntry = 0x400000000ULL;
    *(uint32_t*)(axisEntry + 1) = invertSensitivity;
    if (result != 0) {
        ((void (*)(int))local_4)(result);
    }

    FUN_004d3bc0("Z-Rotation.Inverted");
    axisEntry = (uint64_t*)FUN_00696ed0(&result);
    *axisEntry = 0x500000000ULL;
    *(uint32_t*)(axisEntry + 1) = invertSensitivity;
    if (result != 0) {
        ((void (*)(int))local_4)(result);
    }

    FUN_004d3bc0("Throttle.Inverted");
    axisEntry = (uint64_t*)FUN_00696ed0(&result);
    *axisEntry = 0x600000000ULL;
    *(uint32_t*)(axisEntry + 1) = invertSensitivity;
    if (result != 0) {
        ((void (*)(int))local_4)(result);
    }

    FUN_004d3bc0("Rudder.Inverted");
    axisEntry = (uint64_t*)FUN_00696ed0(&result);
    *axisEntry = 0x700000000ULL;
    *(uint32_t*)(axisEntry + 1) = invertSensitivity;
    if (result != 0) {
        ((void (*)(int))local_4)(result);
    }

    return this_;
}