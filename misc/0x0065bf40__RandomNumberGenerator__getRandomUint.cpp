// FUNC_NAME: RandomNumberGenerator::getRandomUint
uint RandomNumberGenerator::getRandomUint(void)
{
  uint result;

  if (DAT_0120588f == '\0') {
    DAT_0120588f = '\x01';
    FUN_00662100(&DAT_01203740); // seedGenerator
    FUN_006622a0(&DAT_01203740); // initializeGenerator
  }
  FUN_00662350(&result,4,&DAT_01203740); // generateRandomBytes
  // Convert from little-endian to big-endian (network byte order)
  return (((result & 0xff) << 8 | result >> 8 & 0xff) << 8 | result >> 0x10 & 0xff) << 8 |
         result >> 0x18;
}