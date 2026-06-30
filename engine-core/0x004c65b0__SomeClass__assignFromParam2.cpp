// FUNC_NAME: SomeClass::assignFromParam2
void __thiscall SomeClass::assignFromParam2(int *param_1, int param_2)
{
  int iVar2;
  int iVar3;
  int *localVar;
  int *ptr;
  int i;

  // Calculate offset to a static table of pointers (e.g., g_shadowSampler)
  // The static table is at address 0x011286b4 (PTR_s_g_shadowSampler_011286b4)
  iVar3 = (int)&PTR_s_g_shadowSampler_011286b4 - (int)param_1;
  i = 5;
  do {
    // Call FUN_0060a580 with param2 and the pointer from the static table
    // FUN_0060a580 likely returns some value based on param2 and the pointer
    *param_1 = FUN_0060a580(param_2, *(int *)(iVar3 + (int)param_1));
    param_1 = param_1 + 1;
    i = i + -1;
  } while (i != 0);
  return;
}