// FUNC_NAME: SomeClass::setData

void __thiscall SomeClass::setData(SomeClass *this, const SomeDataContainer *src)
{
  if (src != (const SomeDataContainer *)0x0) {
    if (src != (const SomeDataContainer *)(this + 0x1ac / sizeof(SomeClass))) {
      // +0x1ac: first 8-byte field (e.g., ID or timestamp)
      *(unsigned long long *)(this + 0x1ac) = *(unsigned long long *)src;
      // +0x1b4: second 8-byte field
      *(unsigned long long *)(this + 0x1b4) = *(unsigned long long *)((char *)src + 8);
      // +0x1bc: sub‑object (e.g., GUID, string) – copied via helper
      // FUN_004d3e20 takes a pointer to the source sub‑object (src+16) and
      // writes to the destination (this+0x1bc) using internal state or the this pointer.
      FUN_004d3e20((char *)src + 16);
      // +0x1cc: 32‑bit field
      *(int *)(this + 0x1cc) = *(int *)((char *)src + 0x20);
      // +0x1d0: 32‑bit field
      *(int *)(this + 0x1d0) = *(int *)((char *)src + 0x24);
    }
    return;
  }
  // If source is null, reset the field at +0x1cc to 0
  *(int *)(this + 0x1cc) = 0;
  return;
}