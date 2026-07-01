// FUNC_NAME: RingBuffer::popFront
void __fastcall RingBuffer::popFront(int this)
{
  int *piVar1;
  
  if (*(undefined4 **)(this + 0x48) != (undefined4 *)0x0) {
    *(int *)(this + 0x34) = *(int *)(this + 0x34) + -1;
    piVar1 = (int *)(this + 0x34);
    if (0x7fffffff < *(uint *)(this + 0x34)) {
      *piVar1 = *(int *)(this + 0x40) + -1;
    }
    *(undefined4 *)(*(int *)(this + 0x3c) + *piVar1 * 4) = **(undefined4 **)(this + 0x48);
    if (*(int *)(this + 0x38) == *piVar1) {
      *(int *)(this + 0x38) = *(int *)(this + 0x38) + -1;
    }
    if (0x7fffffff < *(uint *)(this + 0x38)) {
      *(int *)(this + 0x38) = *(int *)(this + 0x40) + -1;
    }
    FUN_008d6740(piVar1);
  }
  piVar1 = (int *)(this + 4);
  if ((*(int *)(this + 0x18) != 0) || (*piVar1 != 0)) {
    if (*(code **)(this + 0x18) != (code *)0x0) {
      (**(code **)(this + 0x18))(piVar1);
      return;
    }
    (*(code *)*piVar1)(this);
  }
  return;
}