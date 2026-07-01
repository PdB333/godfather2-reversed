// FUNC_NAME: SomeClass::setSomeValue
void __thiscall setSomeValue(int this, int param_2)
{
  int local_8;
  
  // ROUND is likely a macro for rounding a float to nearest integer
  // DAT_01129908 + 0x14 is some global float value, possibly a config or game setting
  local_8 = (int)(longlong)ROUND(*(float *)(DAT_01129908 + 0x14));
  
  // Store the rounded value at offset +100 (0x64) - likely a member variable
  *(int *)(this + 100) = local_8;
  
  // Clamp the value to 50000 maximum
  if (50000 < local_8) {
    *(int *)(this + 100) = 50000;
  }
  
  // If param_2 is less than or equal to the stored value, update offset +0x60
  if (param_2 <= *(int *)(this + 100)) {
    *(int *)(this + 0x60) = param_2;
  }
  
  // Call some function with the value at offset +0x60, this+0x50, and constant 5
  // This might be setting up a timer, cooldown, or some game mechanic
  FUN_00604000(*(int *)(this + 0x60), this + 0x50, 5);
  
  return;
}