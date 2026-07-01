// FUNC_NAME: SomeClass::pushToQueue
void __thiscall pushToQueue(int this, undefined4 value)
{
  // +0x90c: queue count/index
  // +0x8fc: queue array (element size 4)
  *(undefined4 *)(this + 0x8fc + *(int *)(this + 0x90c) * 4) = value;
  *(int *)(this + 0x90c) = *(int *)(this + 0x90c) + 1;
  return;
}