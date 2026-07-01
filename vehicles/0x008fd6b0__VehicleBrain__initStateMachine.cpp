// FUNC_NAME: VehicleBrain::initStateMachine
void __thiscall VehicleBrain::initStateMachine(VehicleBrain *this)
{
  int stateMachine;
  char *namePtr;

  // Allocate a 0xF0 byte state machine object
  stateMachine = FUN_009c8e50(0xF0);  // behaviorAlloc
  if (stateMachine == 0) {
    stateMachine = 0;
  }
  else {
    stateMachine = FUN_00982280(0);  // behaviorConstructor
  }

  // Get debug name from this->debugName (+0x30), default to global constant
  namePtr = *(char **)((int)this + 0x30);
  if (namePtr == (char *)0x0) {
    namePtr = (char *)&DAT_0120546e;  // default debug name string
  }
  FUN_00981eb0(namePtr);  // setStateMachineDebugName

  FUN_00982400(1);  // setStateMachineDebugMode(1)

  // Check if this->carController (+0x1c) has a specific flag at +0xC0
  if (*(int *)(*(int *)((int)this + 0x1C) + 0xC0) != 0) {
    // Player-driven vehicle path
    *(int *)(stateMachine + 0xC) = 1;  // mode = 1
    FUN_008fcae0(stateMachine, 0x61D7B25, 1);  // addTransition(hash, priority)
    FUN_008fcae0(stateMachine, 0x97AAD499, 0); // addTransition(hash, priority)
    *(code **)(stateMachine + 0x14) = FUN_008fd610;  // setTickFunction(brainTick)
    FUN_00982E10();  // finalizeStateMachine
    return;
  }
  // AI-driven vehicle path
  *(int *)(stateMachine + 0xC) = 3;          // mode = 3
  *(int *)(stateMachine + 0x20) = 0x14D8DA9E; // some hash/id
  *(code **)(stateMachine + 0x14) = FUN_008fd610; // setTickFunction(brainTick)
  FUN_00982E10();  // finalizeStateMachine
}