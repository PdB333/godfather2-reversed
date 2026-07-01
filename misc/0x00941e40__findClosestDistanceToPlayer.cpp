// FUNC_NAME: findClosestDistanceToPlayer
float10 findClosestDistanceToPlayer(undefined4 param_1, undefined4 param_2)
{
  char cVar1;
  float10 fVar2;
  
  param_1 = DAT_00d5f6f0; // Global max distance constant (e.g., 10000.0f)
  cVar1 = FUN_00940450(); // Iterate over active entities/players
  while (cVar1 != '\0') {
    fVar2 = (float10)FUN_009408c0(&DAT_011305d0,&DAT_011305e0,&DAT_011305f0,param_2); // Calculate distance from entity to param_2 position
    if (fVar2 < (float10)param_1) {
      param_1 = (float)fVar2;
    }
    cVar1 = FUN_00940450(); // Next entity
  }
  return (float10)param_1;
}