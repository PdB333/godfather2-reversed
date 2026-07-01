// FUNC_NAME: SomeClass::ensureResourceLoaded
void __fastcall SomeClass::ensureResourceLoaded(int thisPtr)
{
  if (*(int *)(thisPtr + 0x7c) == 0) {
    char* resourceType = *(char**)(thisPtr + 0x6c);
    if (resourceType == (char*)0x0) {
      resourceType = &DAT_0120546e;  // default resource type string
    }
    *(int*)(thisPtr + 0x7c) = FUN_0098f920(
      resourceType,
      *(int*)(thisPtr + 0x60),   // +0x60 likely resource identifier or path
      *(int*)(thisPtr + 100),    // +0x64 resource flags or size
      *(int*)(thisPtr + 0x68)    // +0x68 additional resource parameters
    );
  }
}