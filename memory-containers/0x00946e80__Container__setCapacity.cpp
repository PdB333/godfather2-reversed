// FUNC_NAME: Container::setCapacity

void __thiscall Container::setCapacity(uint newCapacity)
{
  uint *capacity = reinterpret_cast<uint *>(this + 4); // +0x04: capacity field
  if (*capacity < newCapacity) {
    // Need to grow – call reallocation function (likely allocates or reallocates storage)
    FUN_006b1f00(newCapacity);
    *capacity = newCapacity;
    return;
  }
  if (newCapacity < *capacity) {
    // Shrinking – just update capacity (no reallocation for shrink)
    *capacity = newCapacity;
  }
  // If equal, do nothing
  return;
}