// FUNC_NAME: SomeClass::dispatchMessageOrNotification
void __thiscall SomeClass::dispatchMessageOrNotification(int thisPtr, undefined4 param2)
{
  // +0x130: Pointer to a delegate/callback object
  if (*(int **)(thisPtr + 0x130) != (int *)0x0) {
    // Call a method at offset +0x44 of the delegate object, passing two arguments.
    // 0x6f74af5b is likely a message/notification ID (e.g., an EARS hash or enum).
    (**(code **)(**(int **)(thisPtr + 0x130) + 0x44))(0x6f74af5b, param2);
  }
  return;
}