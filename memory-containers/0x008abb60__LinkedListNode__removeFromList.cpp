// FUNC_NAME: LinkedListNode::removeFromList
void __fastcall LinkedListNode::removeFromList(int this)
{
  FUN_004bc3f0();
  *(undefined ***)(this + 0x38) = &PTR_LAB_00e35c24;
  *(undefined ***)(this + 0x28) = &PTR_LAB_00e317cc;
  if (*(int *)(this + 0x18) != 0) {
    if (*(int *)(this + 0x1c) == 0) {
      *(undefined4 *)(*(int *)(this + 0x18) + 4) = *(undefined4 *)(this + 0x20);
    }
    else {
      *(undefined4 *)(*(int *)(this + 0x1c) + 8) = *(undefined4 *)(this + 0x20);
    }
    if (*(int *)(this + 0x20) != 0) {
      *(undefined4 *)(*(int *)(this + 0x20) + 4) = *(undefined4 *)(this + 0x1c);
    }
  }
  FUN_0064d150();
  return;
}