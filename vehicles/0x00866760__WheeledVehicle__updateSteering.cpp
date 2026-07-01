// FUNC_NAME: WheeledVehicle::updateSteering

void __thiscall WheeledVehicle::updateSteering(uint this)
{
  char conditionResult;
  float10 rawAngle;
  float currentAngle;
  float targetAngle;

  // Fetch current and target steering components? 
  // +0xFA0: m_targetSteer (or acceleration)
  // +0xFA4: m_currentSteer (or speed)
  targetAngle = *(float *)(this + 0xFA4) + *(float *)(this + 4000); // 4000 = 0xFA0

  // Get current rotation angle from quaternion at +0x101C
  rawAngle = (float10)FUN_00470250(this + 0x101C); // Quaternion to angle
  currentAngle = (float)rawAngle;

  // Compute maximum allowed steering angle based on current target
  float maxAngle = targetAngle * DAT_00d5eee4; // steeringMaxRate
  if (maxAngle <= currentAngle)
  {
    float minAngle = targetAngle * DAT_00d75750; // steeringMinRate
    targetAngle = maxAngle; // store the max as new target? (unused later?)

    // Check if we are within the acceptable range and if steering is allowed
    if ((currentAngle < minAngle) &&
        (conditionResult = FUN_00865780(*(uint *)(this + 0xFD0), &currentAngle),
         conditionResult != '\0') &&
        (currentAngle < targetAngle))
    {
      return; // Steering already in desired range, do nothing
    }

    // Reset steering flag and apply new steering angle
    *(uint *)(this + 0xF70) = 0; // m_steeringApplied = false
    rawAngle = (float10)FUN_0085ec00(
        *(uint *)(this + 0xFD0),               // entity ID? 
        *(uint *)(this + 0xFD4) & 0x7FFFFFFF,   // magnitude of signed angle
        *(uint *)(this + 0xFD4) >> 0x1F);       // sign bit
    *(float *)(this + 0xFC8) = (float)rawAngle; // m_steeringAngle = result
  }
}