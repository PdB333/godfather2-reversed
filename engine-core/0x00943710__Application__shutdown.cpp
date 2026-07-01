// FUNC_NAME: Application::shutdown

void __fastcall Application::shutdown(undefined4 *this)
{
    int *refCountedObj;
    int *vtablePtr;
    int *tempPtr;
    undefined4 *globalObj1;
    undefined4 *globalObj2;

    // Set vtable pointers for this object
    this[0] = &PTR_FUN_00d8b3b0; // Virtual table
    this[4] = &PTR_LAB_00d8b38c; // Additional vtable at +0x10
    this[0x13] = &PTR_LAB_00d8b388; // Vtable at +0x4C
    this[0x14] = &PTR_LAB_00d8b378; // Vtable at +0x50

    // Release object at offset 0x100 (this[0x40])
    refCountedObj = (int *)this[0x40];
    if (refCountedObj != (int *)0x0) {
        FUN_004226c0(); // Unknown: maybe decrement global ref count?
        vtablePtr = (int *)*refCountedObj;
        tempPtr = vtablePtr + 1;
        *tempPtr = *tempPtr + -1; // Decrement reference count (this might be a class with ref count at offset 4)
        if (*tempPtr == 0) {
            // Call destructor through vtable (offset 4)
            (**(code **)(*vtablePtr + 4))();
        }
        FUN_009c8eb0(refCountedObj); // Release/free object
    }

    // Release global singleton DAT_01130618
    globalObj1 = DAT_01130618;
    if (DAT_01130618 != (undefined4 *)0x0) {
        // Call release method via vtable (offset 4? second virtual)
        (**(code **)(*(int *)DAT_01130618[4] + 4))(*DAT_01130618, 0);
        if (globalObj1[3] != 0) {
            (**(code **)(*(int *)globalObj1[4] + 4))(globalObj1[3], 0);
        }
        // Call some function (offset 0xC)
        (**(code **)(*(int *)globalObj1[4] + 0xc))();
        FUN_009c8eb0(globalObj1);
    }

    // Release global singleton DAT_01130614
    globalObj2 = DAT_01130614;
    if (DAT_01130614 != (undefined4 *)0x0) {
        (**(code **)(*(int *)DAT_01130614[4] + 4))(*DAT_01130614, 0);
        if (globalObj2[3] != 0) {
            (**(code **)(*(int *)globalObj2[4] + 4))(globalObj2[3], 0);
        }
        (**(code **)(*(int *)globalObj2[4] + 0xc))();
        FUN_009c8eb0(globalObj2);
    }

    // Nullify globals
    DAT_01130618 = (undefined4 *)0x0;
    DAT_01130614 = (undefined4 *)0x0;

    // Destroy static objects
    FUN_004086d0(&DAT_0112fe64);
    FUN_004086d0(&DAT_0112fe88);
    FUN_004086d0(&DAT_0112fe98);

    // Release optional object at offset 0xF0
    if (this[0x3c] != 0) {
        FUN_009c8f10(this[0x3c]);
    }

    // Reset vtable to base (restore for final cleanup)
    this[0x2e] = &PTR_FUN_00d8b334;
    FUN_004de130();
    FUN_004083d0();
    this[0x13] = &PTR_LAB_00d8b33c;

    DAT_0112af90 = 0;
    FUN_005c16e0();
    return;
}