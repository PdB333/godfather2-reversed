// FUNC_NAME: ComponentFactory::allocateAndConstruct
undefined4 ComponentFactory::allocateAndConstruct(void *param_1, uint param_2)
{
  int allocResult;
  undefined4 constructorResult;
  // Allocation flags: alignment=0x10, something=2, something else=0
  AllocParams allocParams;
  allocParams.field0 = 2;   // +0x00: flags
  allocParams.field4 = 0x10; // +0x04: alignment
  allocParams.field8 = 0;    // +0x08: maybe tag or zero
  // Attempt to allocate 0xf0 (240) bytes of memory
  allocResult = heapAlloc(0xf0, &allocParams, param_2);
  if (allocResult != 0) {
    // If allocation succeeded, construct object at param_1 using custom allocator
    constructorResult = constructObject(param_1);
    return constructorResult;
  }
  return 0;
}