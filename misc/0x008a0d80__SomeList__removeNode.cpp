// FUNC_NAME: SomeList::removeNode
void __thiscall SomeList::removeNode(int this, int node)
{
  int local_8;
  undefined4 local_4;
  
  if (node == 0) {
    local_8 = 0;
  }
  else {
    local_8 = node + 0x48;
  }
  local_4 = 0;
  if (local_8 != 0) {
    local_4 = *(undefined4 *)(local_8 + 4);
    *(int **)(local_8 + 4) = &local_8;
  }
  FUN_0089fac0(this + 0x10, &local_8);
  if (local_8 != 0) {
    FUN_004daf90(&local_8);
  }
  return;
}