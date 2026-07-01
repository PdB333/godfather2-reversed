// FUNC_NAME: SomeClass::initializeFromConfig
int __thiscall SomeClass::initializeFromConfig(int this, int *config)
{
  char cVar1;
  undefined4 uVar2;
  
  uVar2 = (**(code **)(*config + 0x1d4))(); // Call virtual function at vtable+0x1d4 (likely getSomeValue)
  FUN_004d3b50(uVar2); // Some utility function
  *(int *)(this + 0x10) = config[0x7bd]; // +0x10: someField1 = config[1981]
  *(int *)(this + 0x14) = config[0x7be]; // +0x14: someField2 = config[1982]
  *(undefined4 *)(this + 0x18) = 0; // +0x18: flags = 0
  *(uint *)(this + 0x18) = *(uint *)(this + 0x18) | 1; // Set flag bit 0
  cVar1 = FUN_0089c630(); // Check some condition
  if (cVar1 != '\0') {
    *(uint *)(this + 0x18) = *(uint *)(this + 0x18) | 2; // Set flag bit 1
  }
  return this;
}