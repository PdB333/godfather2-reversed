// FUNC_NAME: BaseVehicle::setEngineForce
// Address: 0x00546940
// Sets a scaled engine force/torque on the vehicle's physics controller.
void __thiscall BaseVehicle::setEngineForce(BaseVehicle* this, float value)
{
    // m_pVehiclePhysicsController at +0x380, m_forceInput at +0x8
    *(float*)(*(int*)((int)this + 0x380) + 8) = value * DAT_00e445c8; // DAT_00e445c8 is a global scale factor (e.g., unit conversion)
}