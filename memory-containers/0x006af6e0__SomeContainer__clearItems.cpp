// FUNC_NAME: SomeContainer::clearItems
void __fastcall SomeContainer::clearItems(int this)
{
  uint i;
  
  if (*(int *)(this + 0xc) != 0) {
    i = 0;
    do {
      FUN_006b6110(); // likely release/delete each item
      i = i + 1;
    } while (i < *(uint *)(this + 0xc));
  }
  return;
}