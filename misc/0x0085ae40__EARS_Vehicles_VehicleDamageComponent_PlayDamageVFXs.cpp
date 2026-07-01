// Xbox PDB: EARS_Vehicles_VehicleDamageComponent_PlayDamageVFXs
// FUNC_NAME: VehicleSoundSystem::updateVehicleSpeedSound
void __thiscall VehicleSoundSystem::updateVehicleSpeedSound(VehicleSoundSystem *this, void *soundEmitter, float vehicleSpeed, unsigned int *optionalVariation)
{
    unsigned int variation;
    char *soundEventName;
    float vector[3];
    unsigned int *emitterPos;

    // If no variation specified, default to 1
    if (optionalVariation == nullptr) {
        variation = 1;
    } else {
        variation = *optionalVariation;
    }

    // Determine speed category based on thresholds stored at this+0x118, 0x11C, 0x120
    soundEventName = nullptr;
    if (this->field_0x118 <= vehicleSpeed) {
        if (this->field_0x11C <= vehicleSpeed) {
            if (this->field_0x120 <= vehicleSpeed) {
                // Redundant check: same as above
                if (this->field_0x120 <= vehicleSpeed) {
                    soundEventName = "vehicle_fast";
                }
            } else {
                soundEventName = "vehicle_med";
            }
        } else {
            soundEventName = "vehicle_slow";
        }
    } else {
        soundEventName = "vehicle_veryslow";
    }

    // Get position from emitter object (offset +0x0C is likely a 3D position)
    emitterPos = (unsigned int *)(*(int *)(soundEmitter + 0x0C));
    vector[0] = (float)emitterPos[0];
    vector[1] = (float)emitterPos[1];
    vector[2] = (float)emitterPos[2];

    // Play the appropriate sound event at the emitter's position
    FUN_00859b70(soundEventName, variation, vector);
}