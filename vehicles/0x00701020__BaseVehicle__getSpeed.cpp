// FUNC_NAME: BaseVehicle::getSpeed
float __thiscall BaseVehicle::getSpeed(BaseVehicle *this) {
    // +0x478: current speed magnitude (float)
    return *(float *)((char *)this + 0x478);
}