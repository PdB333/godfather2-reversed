// FUNC_NAME: VehicleTire::submitForceCommand
// Function at 0x004f54b0: Submits a force feedback command to a global command list based on tire slip and inputs.
// __thiscall: this pointer in ecx (param_1)
// This function calculates a combined force magnitude from lateral and longitudinal slip components,
// multiplies it with steering and throttle inputs, and pushes a command struct (vtable, this, input2D, magnitude) to a queue.

void __fastcall VehicleTire::submitForceCommand(void* this) // this in ecx
{
    // Constant for clamping slip factors (likely 1.0f or max force)
    const float kMaxClamp = *(float*)0x00e2b1a4;

    // Global command list: pointer to a pointer to the current write position
    // 0x01206880 is a global structure, at offset 0x14 there is a pointer to a buffer (growing stack)
    int* pWritePos = *(int**)(0x01206880 + 0x14);

    // Get the vehicle dynamics object from this+4
    void* pDynamics = *(void**)((char*)this + 4);

    // Read current slip velocity (magnitude) from dynamics at +0x8c
    float currentSlip = *(float*)((char*)pDynamics + 0x8c);

    // Get the wheel index (short) from this+0x0e
    short wheelIndex = *(short*)((char*)this + 0x0e);

    // Access the wheel parameters array inside dynamics at offset 0x10
    // Each wheel struct is 0x24 bytes, with base offset 0x30 from dynamics start
    char* wheelParams = (char*)pDynamics + 0x10 + 0x30 + wheelIndex * 0x24;

    // Lateral slip difference and stiffness
    float lateralDiff = (currentSlip - *(float*)(wheelParams + 0x18)); // slip - idealSlip
    float lateralStiffness = *(float*)(wheelParams + 0x14);
    float lateralFactor = lateralDiff * lateralStiffness;
    if (lateralFactor > 0.0f)
    {
        if (lateralFactor > kMaxClamp)
            lateralFactor = kMaxClamp;
    }
    else
    {
        lateralFactor = 0.0f;
    }

    // Longitudinal slip difference and stiffness
    float longitudinalDiff = (currentSlip - *(float*)(wheelParams + 0x20));
    float longitudinalStiffness = *(float*)(wheelParams + 0x1c);
    float longitudinalFactor = longitudinalDiff * longitudinalStiffness;
    if (longitudinalFactor > 0.0f)
    {
        if (longitudinalFactor > kMaxClamp)
            longitudinalFactor = kMaxClamp;
    }
    else
    {
        longitudinalFactor = 0.0f;
    }

    // Input values from this object (steer, throttle, etc.)
    float steerInput = *(float*)((char*)this + 0x30);
    float throttleInput = *(float*)((char*)this + 0x38);
    float brakeInput = *(float*)((char*)this + 0x34); // used as uVar3 in 64-bit pair

    // Compute final force magnitude: product of all four factors
    float forceMagnitude = lateralFactor * longitudinalFactor * steerInput * throttleInput;

    // Write command to the global list
    // Command struct: [vtable, this, Input2D(steer+brake as 8 bytes), magnitude]
    void** current = (void**)*pWritePos;

    // First write the vtable pointer (class ID)
    *current = (void*)0x01124e90; // VTable for ForceCommand

    // Advance write pointer by 4 bytes (size of pointer)
    int* next = (int*)((char*)current + 4);
    *pWritePos = (int)next;

    // Write 'this' pointer
    *(int*)next = (int)this;
    next = (int*)((char*)next + 4);
    *pWritePos = (int)next;

    // Align to 4-byte boundary (already aligned, but code does alignment)
    int alignedNext = ((int)next + 7) & 0xFFFFFFFC;
    *pWritePos = alignedNext;

    // Write two 4-byte values (steerInput and brakeInput) as one 8-byte value
    *(uint64_t*)alignedNext = ((uint64_t)brakeInput << 32) | ((uint64_t)steerInput & 0xFFFFFFFF);

    // Write force magnitude as float
    *(float*)(alignedNext + 8) = forceMagnitude;

    // Update write pointer to after the 12 bytes (8+4)
    *pWritePos = alignedNext + 12;
}