// FUNC_NAME: Vehicle::updateThrottleBrake
void __thiscall Vehicle::updateThrottleBrake(int this, int vehicleData) // param_1 = this (Vehicle), param_2 = vehicleData (some physics/render data)
{
    int direction; // 0 = forward, 1 = reverse? Based on +0xc4 check
    float throttle; // from +0x104
    float clamped;

    direction = 0xffffffff; // -1? Maybe unused initial
    int brakeInput = 0; // iVar2
    if (*(int *)(vehicleData + 0xc4) == 1) { // +0xc4: gear/shift state? 1=reverse?
        direction = 0; // No throttle? wait, uVar1 is set to 0, which might be forward/reverse flag
        brakeInput = -*(int *)(vehicleData + 200); // +0xc8? No, +200 is decimal 0xC8. Could be handbrake or braking force
        FUN_008c1d40(); // likely a sound/engine function related to reverse/brake
    }
    else if (*(int *)(vehicleData + 0xc4) == 0) { // gear/shift state? 0=neutral or driving?
        FUN_006b3220(); // some audio/engine function
        direction = 2; // maybe forward? (2 could be a throttle direction flag)
        brakeInput = -(*(int *)(vehicleData + 0xcc) + *(int *)(vehicleData + 200)); // +0xcc: some other force, e.g., engine braking. Combine with +0xc8.
    }

    if (*(int *)(this + 0x230) != 0) { // +0x230: flag for vehicle being active/visible? Possibly a vehicle sim state
        FUN_00892490((float)brakeInput, (float)direction); // apply throttle/brake forces, direction as float? possibly unused
    }

    // +0x104: current throttle/acceleration value
    float newThrottle = *(float *)(this + 0x104) + (float)brakeInput;

    if (newThrottle <= DAT_00d7bcac) { // clamp min
        *(float *)(this + 0x104) = DAT_00d7bcac;
        return;
    }
    if (DAT_00d7bca8 <= newThrottle) { // clamp max
        newThrottle = DAT_00d7bca8;
    }
    *(float *)(this + 0x104) = newThrottle;
    return;
}