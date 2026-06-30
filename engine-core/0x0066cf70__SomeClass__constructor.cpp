// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(int *param_1)
{
  undefined4 *unaff_ESI;
  
  unaff_ESI[1] = 0;
  unaff_ESI[2] = &PTR_LAB_00e4449c;
  *unaff_ESI = &PTR_FUN_00e4448c;
  unaff_ESI[2] = &PTR_LAB_00e44498;
  unaff_ESI[3] = param_1;
  DAT_012234cc = unaff_ESI;
  (**(code **)(*param_1 + 8))();
  unaff_ESI[4] = 0;
  FUN_0049c6e0(&DAT_00e44488,1);
  return;
}