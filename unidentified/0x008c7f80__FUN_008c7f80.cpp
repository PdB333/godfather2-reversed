// FUNC_NAME: SomeClass::update
void SomeClass::update(int param_1)
{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(param_1 + 0x40); // +0x40: some member pointer
  if (*(int *)(param_1 + 0xfc) == 0) { // +0xfc: flag indicating something is not active
    FUN_008c7e30(param_1); // handle initialization or setup
  }
  FUN_008c74d0(uVar1); // process the member pointed to by +0x40
  FUN_008c4790(param_1); // perform main update logic
  return;
}