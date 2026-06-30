// FUNC_NAME: UnknownClass::initFromFloat
// Function address: 0x006c1ab0
// Role: Initialization of an object with a single float input, sets timers/flags/state.

void __thiscall UnknownClass::initFromFloat(float* inputValue)
{
    // Global time/constant, likely current game time (e.g., dt or frame timestamp)
    // DAT_00e44564 - *inputValue gives elapsed time since a given reference.
    double elapsed = (double)(DAT_00e44564 - *inputValue);

    // Unknown utility functions – likely global system updates or physics step
    FUN_00b9a9fa();
    FUN_006daa50();

    // Store elapsed time as float at offset 0x10
    *(float*)(this + 0x10) = (float)elapsed;

    // Clear consecutive float fields (maybe velocity, position, or other stats)
    *(int*)(this + 0x14) = 0;   // +0x14: float zero
    *(int*)(this + 0x18) = 0;   // +0x18: float zero
    *(int*)(this + 0x1c) = 0;   // +0x1c: float zero

    // Set boolean/flag at offset 0x30 to true (active?)
    *(bool*)(this + 0x30) = true;

    // Set boolean at offset 0x38 to true
    *(bool*)(this + 0x38) = true;

    // Clear int at offset 0x34 (maybe counter)
    *(int*)(this + 0x34) = 0;

    // Clear bytes at offsets 0x39-0x3c (four more flags)
    *(bool*)(this + 0x39) = false;
    *(bool*)(this + 0x3a) = false;
    *(bool*)(this + 0x3b) = false;
    *(bool*)(this + 0x3c) = false;

    // Process the input float further (perhaps store copy or update derived data)
    FUN_006c0810(inputValue);

    // Zero six floats from +0x4c to +0x60 (position, orientation, or other vectors)
    *(float*)(this + 0x4c) = 0.0f;
    *(float*)(this + 0x50) = 0.0f;
    *(float*)(this + 0x54) = 0.0f;
    *(float*)(this + 0x58) = 0.0f;
    *(float*)(this + 0x5c) = 0.0f;
    *(float*)(this + 0x60) = 0.0f;

    // Store global value (DAT_00d5eea0) at offset 0x64 (100 decimal)
    *(int*)(this + 0x64) = DAT_00d5eea0;

    // Clear three more floats from +0x68 to +0x70
    *(float*)(this + 0x68) = 0.0f;
    *(float*)(this + 0x6c) = 0.0f;
    *(float*)(this + 0x70) = 0.0f;

    return;
}