// FUNC_NAME: VehicleSpeedController::computeSpeedLimit
float VehicleSpeedController::computeSpeedLimit() {
    // param_1 is 'this'
    // this+0x04: pointer to some manager (e.g., SimManager)
    int* manager = *(int**)(this + 4);
    
    // manager+0x24c4: pointer to vehicle sub-struct (e.g., Vehicle::mPhysics)
    int vehiclePhysicsPtr = *(int*)(manager + 0x24c4);
    int* vehicle = nullptr;
    if (vehiclePhysicsPtr != 0) {
        vehicle = (int*)(vehiclePhysicsPtr - 0x48); // Get base Vehicle object (offset -0x48)
    }
    
    // Check some global condition (e.g., is player controlling?)
    int condition1 = FUN_00717700(); // e.g., isPlayerActive()
    float speedModifier = 0.0f;
    
    if ((vehicle != nullptr) && (condition1 != 0)) {
        // Another condition (e.g., is vehicle drivable?)
        char condition2 = FUN_0071bed0(); // e.g., isVehicleOperable()
        if (condition2 != 0) {
            float* outPtr = nullptr;
            // Virtual function at vtable+0x10: getGameVariable(uint32 hash, void*& out)
            bool success = (*(bool (__thiscall**)(int*, uint32, float*))(*vehicle + 0x10))(vehicle, 0x55859efa, &outPtr);
            if (success && (outPtr != nullptr)) {
                int component = *(int*)((int)outPtr + 0x74c); // outPtr points to some component
                if (component != 0 && component != 0x48) {
                    speedModifier = *(float*)(component + 0x190); // +0x190 (400 decimal)
                }
            }
        }
    }
    
    // Now retrieve another component from manager
    int enginePtr = *(int*)(manager + 0x21b8); // e.g., EngineComponent
    float engineSpeed = 0.0f;
    if (enginePtr != 0) {
        engineSpeed = *(float*)(enginePtr + 0x6c); // e.g., currentRPM or speed
    }
    float engineSpeed2 = engineSpeed; // repeated due to decompiler artifact
    
    // Global maximum speed
    extern float g_maxSpeed; // _DAT_00d5780c
    
    // Compute result
    float result = (g_maxSpeed - engineSpeed) * speedModifier + engineSpeed2 * *(float*)(this + 0x50);
    if (g_maxSpeed < result) {
        result = g_maxSpeed;
    }
    return result;
}