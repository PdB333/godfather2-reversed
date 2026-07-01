// FUNC_NAME: HavokWheeledVehicle::resetInputState
// Function at 0x0080e610 - Resets two vehicle dynamics fields (8-byte and 4-byte) to zero, likely clearing input state or a timestamp+gear combination.

void __thiscall HavokWheeledVehicle::resetInputState(void)
{
  int vehicleDynamics = *(int *)((int)this + 0x50); // pointer to dynamics sub-struct (+0x50)
  *(long long *)(vehicleDynamics + 0x424) = 0;      // clear 8-byte field (e.g., input impulse or timestamp)
  *(int *)(vehicleDynamics + 0x42c) = 0;            // clear 4-byte field (e.g., gear or brake flag)
}