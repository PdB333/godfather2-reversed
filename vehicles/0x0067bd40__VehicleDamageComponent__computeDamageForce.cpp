// FUNC_NAME: VehicleDamageComponent::computeDamageForce
void VehicleDamageComponent::computeDamageForce(int *outForceX, int *outForceY)
{
  int forceX1 = FUN_00676010();
  int forceX2 = FUN_00676010();
  *outForceX = forceX1 + forceX2 + *(int *)(this + 0xF0); // +0xF0: damageForceX accumulator
  
  int forceY1 = FUN_00676010();
  int forceY2 = FUN_00676010();
  *outForceY = forceY1 + forceY2 + *(int *)(this + 0xF4); // +0xF4: damageForceY accumulator
}