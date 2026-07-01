// FUNC_NAME: GenericCSA::~GenericCSA
void __fastcall GenericCSA::~GenericCSA(int this)
{
  undefined4 *current;
  undefined4 *next;

  if (*(int *)(this + 0x10) != 0) {
    FUN_004daf90(this + 0x10);
  }
  *(undefined ***)(this + 8) = &PTR_FUN_00e32808; // vtable reset
  current = *(undefined4 **)(this + 0xc); // +0x0C: linked list head
  while (current != (undefined4 *)0x0) {
    next = (undefined4 *)current[1]; // +0x04: next pointer
    current[1] = 0; // clear next
    *current = 0;   // clear data
    current = next;
  }
  return;
}