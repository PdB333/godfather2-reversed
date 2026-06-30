// FUNC_NAME: SomeContainer::addElement
void __fastcall SomeContainer::addElement(int param_1)
{
  int in_EAX;
  
  if (*(int *)(param_1 + 0x2c) != *(int *)(in_EAX + 0x200)) {
    // Swap the element at the current index with the element at the new index
    *(int *)(*(int *)(*(int *)(in_EAX + 0x1fc) + *(int *)(in_EAX + 0x200) * 4) + 0x2c) =
         *(int *)(param_1 + 0x2c);
    *(undefined4 *)(*(int *)(in_EAX + 0x1fc) + *(int *)(param_1 + 0x2c) * 4) =
         *(undefined4 *)(*(int *)(in_EAX + 0x1fc) + *(int *)(in_EAX + 0x200) * 4);
    *(int *)(*(int *)(in_EAX + 0x1fc) + *(int *)(in_EAX + 0x200) * 4) = param_1;
    *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(in_EAX + 0x200);
  }
  *(int *)(in_EAX + 0x200) = *(int *)(in_EAX + 0x200) + 1;
  return;
}