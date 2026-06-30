// FUNC_NAME: SomeClass::getSomething
uint SomeClass::getSomething(void)
{
  int in_EAX; // this pointer

  if (9 < (*(uint *)(in_EAX + 4) & 0xff)) { // check if num > 9 (field at +4 is a count or status)
    return *(uint *)(in_EAX + 0xc);         // return value from offset +0xC
  }
  return (uint)*(byte *)(in_EAX + 6);       // return byte from offset +6
}