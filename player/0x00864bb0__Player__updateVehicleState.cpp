// FUNC_NAME: Player::updateVehicleState
// Function address: 0x00864bb0
// Handles state transition between on-foot and vehicle modes, retrieving a component (e.g. vehicle) and updating flags, camera, fade.
int __thiscall Player::updateVehicleState(int *componentObj, int transitionArg)
{
  int *currentObj = componentObj;
  bool isTransitionAllowed = checkCondition1(currentObj);             // FUN_00543050
  bool isStateValid = checkTransitionValidity(currentObj, transitionArg); // FUN_0087cdd0
  if (!isStateValid) {
    return 0;
  }
  resetSomeState(0);                                                  // FUN_0087bc20

  componentObj = 0;
  bool componentRetrieved = currentObj->getComponentByHash(0xd80c71d2, &componentObj); // vtable+0x10

  int ebxFlag;                 // Uninitialized register value from caller (EBX)
  int componentMask = (componentRetrieved) ? ebxFlag : 0;

  if (isTransitionAllowed) {
    if (componentMask) {
      this->vehicleFlags &= ~1u;      // +0xf28: bit 0 cleared
      setFadeAlpha(1.0f);             // FUN_00878630
    }
    updateCamera();                    // FUN_008621d0
    if (this->isInVehicle) {          // +0x7cc
      disableSomething(0);             // FUN_0087f870
    }
  }

  if (componentMask) {
    releaseComponent(0);               // FUN_0087f950
    if (globalComponent != 0) {        // DAT_0112dfd4
      deleteObject(globalComponent);   // FUN_004daf90
      globalComponent = 0;
    }
  }
  return 1;
}