// FUNC_NAME: VehicleBrain::resetForces
void __thiscall VehicleBrain::resetForces(void)
{
    int count = *(int *)(this + 0x4c); // mVehicleCount
    if (count > 0) {
        int arrayBase = *(int *)(this + 0x48); // mpVehicles (array of Vehicle structs, size 0xC0 each)
        int offset = 0;
        do {
            Vehicle* vehicle = (Vehicle*)(arrayBase + offset);
            vehicle->field_0xA8 = 0; // likely mLinearVelocityX
            vehicle->field_0xAC = 0; // mLinearVelocityY
            vehicle->field_0xB0 = 0; // mLinearVelocityZ
            vehicle->field_0xB4 = 0; // mTorque or mAngularVelocity
            offset += 0xC0;
            count--;
        } while (count > 0);
    }
}