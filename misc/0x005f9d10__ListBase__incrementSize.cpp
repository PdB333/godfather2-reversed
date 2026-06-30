// FUNC_NAME: ListBase::incrementSize
void __thiscall ListBase::incrementSize(void)
{
  // +0x1c: current size/count
  int& count = *(int *)(this + 0x1c);
  if (count == 0x3fffffff) {
    // List size would overflow, throw an exception
    // Throw string "list<T> too long"
    FUN_0043f9f0("list<T> too long", 0x10);
    // Exception handling setup
    // ... (omitted for clarity, following original decompiled)
    std::_Throw((exception *)&local_24);
  }
  count++;
}