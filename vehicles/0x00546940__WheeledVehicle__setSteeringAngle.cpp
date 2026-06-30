//FUNC_NAME: WheeledVehicle::setSteeringAngle
void __thiscall WheeledVehicle::setSteeringAngle(int this, float angle)
{
    // this+0x380: pointer to VehicleControlState (or similar sub-structure)
    // VehicleControlState+0x08: steering angle field (float)
    // DAT_00e445c8: conversion factor (e.g., degrees to radians or normalized to actual)
    *(float *)(*(int *)(this + 0x380) + 8) = angle * DAT_00e445c8;
}