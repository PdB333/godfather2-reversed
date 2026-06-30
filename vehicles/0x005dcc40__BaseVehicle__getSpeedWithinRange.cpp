// FUNC_NAME: BaseVehicle::getSpeedWithinRange
bool BaseVehicle::getSpeedWithinRange(float *outSpeed) {
    BaseVehicle *vehicle = FUN_005dc670(this);
    if (vehicle != nullptr) {
        float speed = vehicle->field_0x280; // +0x280 likely mSpeed or mCurrentSpeed
        *outSpeed = speed;
        if (kMinSpeedThreshold <= speed && speed <= kMaxSpeedThreshold) {
            return true;
        }
    }
    return false;
}