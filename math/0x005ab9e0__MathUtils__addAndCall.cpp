// FUNC_NAME: MathUtils::addAndCall
void __fastcall MathUtils::addAndCall(int *param_1)
{
  int *unaff_ESI;
  int local_14;
  int local_10;
  int local_c;
  
  // Compute sum of ESI[0] and ESI[2], store in local_c
  local_c = unaff_ESI[2] + *unaff_ESI;
  // Get param_1[2] as second operand
  local_10 = param_1[2];
  // Compute sum of param_1[0] and local_10, store in local_14
  local_14 = *param_1 + local_10;
  // Call helper function with addresses of the two sums
  FUN_005aba20(&local_10, &local_14);
  return;
}