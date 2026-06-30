// FUNC_NAME: BaseVehicle::setMotorSpeed
void __thiscall BaseVehicle::setMotorSpeed(float speedInput)
{
  // Constants: likely conversion from game units to physics units and time step factor
  extern float _DAT_00d5c458; // physics time step multiplier
  extern float DAT_00e445c8;  // speed scaling factor

  double scaledSpeed = (double)(speedInput * DAT_00e445c8 * _DAT_00d5c458);
  updatePhysicsState(); // internal engine call (FUN_00b99e20) – side effect, no return used
  this->m_speed = (float)scaledSpeed; // offset +0x50: motor speed or desired linear velocity
}