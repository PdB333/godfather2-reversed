// FUNC_NAME: MemoryManager::makeAllocationFlags
uint makeAllocationFlags(uint allocationSize)
{
  // Creates allocation flags from size:
  // - Upper 2 bits set to 0xC0 (flags: likely pool/alignment type)
  // - Lower 30 bits encode the size divided by 4 (aligned to 4 bytes)
  return allocationSize >> 2 | 0xc0000000;
}