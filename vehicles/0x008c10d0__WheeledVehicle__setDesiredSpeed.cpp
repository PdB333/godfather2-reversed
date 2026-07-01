// FUNC_NAME: WheeledVehicle::setDesiredSpeed
void WheeledVehicle::setDesiredSpeed(uint targetSpeed, int param_2)
{
  uint currentSpeed;
  
  if (*(int *)(param_2 + 0xfc) == 0) {
    currentSpeed = FUN_006b18a0(); // likely getVehicleSpeed() or similar
    if (currentSpeed < targetSpeed) {
      // Need to accelerate - apply throttle
      FUN_008c0b10(*(undefined4 *)(param_2 + 0x38), targetSpeed - currentSpeed, 1); // accelerate(speedDiff, direction)
      return;
    }
    if (targetSpeed < currentSpeed) {
      // Need to decelerate - apply brake
      FUN_008be590(*(undefined4 *)(param_2 + 0x38), currentSpeed - targetSpeed); // brake(speedDiff)
    }
  }
  return;
}