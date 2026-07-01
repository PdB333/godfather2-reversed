// FUNC_NAME: operator_new_with_size_check
void operator_new_with_size_check(uint size)
{
  // If size is zero, avoid allocation
  if (size == 0) {
    // No-op; size was 0 so no allocation needed
  } else {
    // Check for overflow: if (0xFFFFFFFF / size) < 24, throw std::bad_alloc
    // This is the standard C++ operator new(size_t) overflow check for array new
    if ((uint)(0xFFFFFFFF / (ulonglong)size) < 0x18) {
      //throw std::bad_alloc (size too large)
      std::_Throw((exception *)nullptr);
    }
    // Allocate size * 24 bytes? Actually this calls a memory allocation function (likely operator new)
    FUN_009c8e50(size * 0x18);
  }
  return;
}