// FUNC_NAME: Vehicle::computeSteeringForce
float __fastcall Vehicle::computeSteeringForce(Vehicle* this) {
  // +0x50: pointer to movement component
  // +0x70: offset of velocity/forward vector within movement component
  int movementPtr = *(int*)(*(int*)((int)this + 0x50) + 0x70);
  if (movementPtr != 0) {
    int* vtablePtr = (int*)(movementPtr - 0x48); // adjust to base of movement object
    if (vtablePtr != nullptr) {
      // get forward/velocity vector from movement component (vtable +0x4c -> getForward)
      Vector3 forward;
      (*(void(__thiscall**)(int, Vector3*))(*vtablePtr + 0x4c))((int)vtablePtr, &forward);
      Vector3 currentForward = forward;
      if (currentForward.magnitudeSq() < 0.001f) { // _DAT_00d5780c = 0.001?
        // fallback to global forward
        int defaultObj = FUN_00471610();
        currentForward = *(Vector3*)(defaultObj + 0x20);
      }
      // normalize forward
      FUN_0056afa0(&currentForward, &currentForward);
      // another component (maybe steering axes)
      int* steeringComp = (int*)(**(code(__thiscall***)(int))(**(int*)((int)this + 0x50) + 0x24))();
      if (steeringComp != nullptr) {
        Vector3 desired;
        (*(void(__thiscall**)(int, Vector3*))(*steeringComp + 0x4c))((int)steeringComp, &desired);
        if (desired.magnitudeSq() < 0.001f) {
          int defaultObj2 = FUN_00471610();
          desired = *(Vector3*)(defaultObj2 + 0x20);
        }
        // normalize desired
        FUN_0056afa0(&desired, &desired);
        // get speed from engine component (offset 0x5c)
        float speed = (**(float(__thiscall**)(int))(**(int*)((int)this + 0x5c) + 0x1b0))();
        float dot = desired.x * currentForward.x + desired.y * currentForward.y + desired.z * currentForward.z;
        float error = speed - dot * 0.5f; // fStack_48 likely a scaling factor (0.5?)
        float result = (error * error * -0.1f + 0.001f) * error; // _DAT_00d75fac = -0.1? approximate
        return result;
      }
    }
  }
  return 0.0f;
}