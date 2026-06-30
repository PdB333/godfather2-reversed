// FUNC_NAME: BaseVehicle::updateSteeringOrSomething
void BaseVehicle::updateSteeringOrSomething(void)

{
  int *this; // eax, points to vehicle object
  int unaff_ESI; // some other vehicle state pointer

  // Check if front wheel steer is equal to rear wheel steer (locked/straight)
  if (this[3] == this[4]) { // +0x0C = frontSteer, +0x10 = rearSteer
    BaseVehicle::someSubFunction(); // likely checkSpeedOrApplyBrake?
    return;
  }
  BaseVehicle::someSubFunction(); // always call this first?
  // Vehicle type check: 0xB is probably "car" or "normal vehicle"
  if (*this == 0xb) { // +0x00 = vehicleType
    if (this[3] == this[4]) { // again check if steering is locked
      return;
    }
    // If current speed is less than or equal to some threshold, apply steering
    if (*(int *)(unaff_ESI + 0x34) <= this[1]) { // +0x34 = speed or throttle, +0x04 = steerInput
      BaseVehicle::steerWheels(this[1]); // steerWheels(input)
      return;
    }
  }
  BaseVehicle::someOtherSubFunction(); // maybe handle drifting or reset?
  return;
}