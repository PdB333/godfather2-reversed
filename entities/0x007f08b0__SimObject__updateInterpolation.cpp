// FUNC_NAME: SimObject::updateInterpolation
void __fastcall SimObject::updateInterpolation(void* this) {
    float currentTime = g_simulationTime; // _DAT_00d5780c: global simulation time in seconds
    float timeDelta = currentTime - *(float*)((int)this + 0xF4); // saved previous time? +0xF4: lastUpdateTime

    // Retrieve two pointers at offsets +0x4 and +0x8
    int* objA = *(int**)((int)this + 0x4); // pointer to first child object (e.g., animation state)
    int* objB = *(int**)((int)this + 0x8); // pointer to second child object

    // Call a method on each object's target (offset +0x138), passing a computed time value
    // The third parameter is: currentTime - (timeDelta * timeDelta) — a parabolic blend? 
    // This likely sets an interpolation target frame/position using a decelerating time factor.
    FUN_007f27a0(
        *(void*)((int)objA + 0x138), // +0x138: target field (e.g., animation clip handle)
        *(void*)((int)objB + 0x138), // +0x138: target field for second object
        currentTime - (timeDelta * timeDelta) // computed effective time for interpolation
    );
}