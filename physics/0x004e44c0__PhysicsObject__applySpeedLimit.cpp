// FUNC_NAME: PhysicsObject::applySpeedLimit
void __thiscall PhysicsObject::applySpeedLimit(float param_1, void *param_2, int param_3) {
    // this is assumed to be a PhysicsObject with fields:
    // +0x00: float velX
    // +0x04: float velY
    // +0x08: float velZ
    // +0x0C: float speedSquared (or speed magnitude)
    // Global threshold at DAT_00e2af44 (probably max allowed speed)
    
    float *fields = reinterpret_cast<float *>(this);
    float currentSpeed = fields[3]; // offset +0x0C

    if (DAT_00e2af44 < currentSpeed) {
        // Speed exceeds limit; call function to apply correction
        // FUN_0052fc90 takes: velX, velY, velZ, speed, param2, param3, param1
        FUN_0052fc90(fields[0], fields[1], fields[2], fields[3], param_2, param_3, param_1);
    }
}