// FUNC_NAME: unknown_float_manipulation
undefined1 __fastcall FUN_00781598(undefined4 param_1, code *param_2)
{
  float10 in_ST0;
  undefined1 uStack_5;
  
  // Call the function pointer with a constant argument (0xf8e72f9)
  (*param_2)(0xf8e72f9);
  
  // Extract the high byte (bits 24-31) of the floating-point value in ST0
  // This is done by casting the float to uint and shifting right by 24 bits
  uStack_5 = (undefined1)((uint)(float)in_ST0 >> 0x18);
  
  return uStack_5;
}