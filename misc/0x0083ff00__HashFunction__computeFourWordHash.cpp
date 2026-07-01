// FUNC_NAME: HashFunction::computeFourWordHash
void __thiscall computeFourWordHash(int *result, int *input)
{
  // Computes a hash by combining four 32-bit values using a linear recurrence:
  // result = ((((input[0] * 0x21) + input[1]) * 0x21 + input[2]) * 0x21) + input[3]
  // Equivalent to: result = input[0]*0x21^3 + input[1]*0x21^2 + input[2]*0x21 + input[3]
  *result = ((input[0] * 0x21 + input[1]) * 0x21 + input[2]) * 0x21 + input[3];
  return;
}