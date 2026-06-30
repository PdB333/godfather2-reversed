// FUNC_NAME: BaseVehicle::applySteeringForce
void __thiscall BaseVehicle::applySteeringForce(byte *targetSteering)
{
    // EAX register points to current state struct (e.g., from member data or passed by caller):
    //   ushort currentSteering   = state[0]
    //   ushort currentForwardSpeed = state[2] (offset 4 bytes)
    ushort *currentState; // Set by caller in EAX (not shown in prototype)

    // Constants (likely global vehicle parameters)
    const float MAX_FORWARD_SPEED = DAT_00e44564;   // maximum allowed forward speed
    const float FORCE_SCALE = DAT_00e44820;         // scaling factor for force/steering

    // Forward force: target speed minus scaled current forward speed
    float forwardForce = MAX_FORWARD_SPEED - (float)currentState[2] * FORCE_SCALE;

    // Steering error: target (scaled by 16) minus current steering
    float steeringError = (float)((uint)*targetSteering << 4) - (float)currentState[0];
    // Steering force is proportional error (note sign inversion from original to get positive correction)
    float steeringForce = steeringError * FORCE_SCALE;

    // Apply the computed forces to the vehicle object (this)
    FUN_0056d040(forwardForce, -steeringForce, this); // likely sets velocity or applies impulse
    return;
}