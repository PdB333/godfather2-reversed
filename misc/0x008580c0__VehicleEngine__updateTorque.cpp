// FUNC_NAME: VehicleEngine::updateTorque

void __thiscall VehicleEngine::updateTorque(void *this) {
    float torqueValue = *(float *)((int)this + 0x44) * g_enginePowerScale; // +0x44: base torque, g_enginePowerScale: global power scale (DAT_00e44584)
    // +0x40: flags byte, bit0 = clamp to minimum torque flag
    if (*(byte *)((int)this + 0x40) & 1) {
        float minTorque = getMinTorque(); // FUN_008cefa0 returns minimum allowed torque
        if (torqueValue < minTorque) {
            torqueValue = minTorque;
        }
    }
    // +0x40 flags bits 1-3: apply torque flag
    if (*(byte *)((int)this + 0x40) & 0xe) {
        setTorque(torqueValue); // FUN_008cf100 applies the torque value to the engine model
    }
}