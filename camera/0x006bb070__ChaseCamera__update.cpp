// FUNC_NAME: ChaseCamera::update
void __thiscall ChaseCamera::update(int this)
{
  int driver;
  int unkResult;

  if (*(int *)(this + 0x54) != 0) {                       // +0x54: m_pTarget (SimObject*)
    driver = getDriverFromTarget(*(int *)(this + 0x54));  // FUN_006b0ee0: getDriverFromTarget
    *(int *)(this + 0x9c) = driver;                      // +0x9c: m_pDriver
    if (driver != 0) {
      resetCameraState();                                 // FUN_006b4ca0: global reset
      *(int *)(this + 0x90) = 0;                          // +0x90: m_cameraVelocity
      unkResult = getCameraComponent(*(int *)(driver + 0xa8)); // FUN_006babc0: getCameraComponent from driver's offset +0xa8
      *(int *)(this + 0x94) = unkResult;                 // +0x94: m_camera
      if ((*(int *)(this + 0x9c) != 0) && ((*(byte *)(this + 0x84) & 1) != 0)) { // +0x84: m_flags (bit 1 = driving)
        *(int *)(this + 0x98) = *(int *)(*(int *)(this + 0x9c) + 0xac); // +0x98: copy from driver+0xac
        return;
      }
      *(int *)(this + 0x98) = 0;                          // +0x98: m_storedValue
    }
  }
  return;
}