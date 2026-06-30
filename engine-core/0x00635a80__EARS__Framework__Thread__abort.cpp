// FUNC_NAME: EARS::Framework::Thread::abort
void __fastcall Thread::abort(int this, int exitCode)
{
  if (*(int *)(this + 0x50) != 0) {
    *(int *)(*(int *)(this + 0x50) + 0x44) = exitCode; // +0x44: exit code field in thread data
    // +0x04: jmp_buf offset
    longjmp(*(int *)(*(int *)(this + 0x50) + 4), 1);
  }
  // +0x10: vtable pointer, +0x28: virtual function for cleanup/terminate
  (**(code **)(*(int *)(this + 0x10) + 0x28))(this);
  _exit(1);
}