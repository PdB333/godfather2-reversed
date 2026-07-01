// FUNC_NAME: Manager::~Manager
void __thiscall Manager::~Manager(Manager *this)
{
  // Cleanup first embedded container at this + 0x50
  int *containerAddr = (int *)((char *)this + 0x50);
  
  // Set vtable pointer
  this->vtable = (void *)0x00d81f80;
  
  // Override function pointers at offsets 0x3C and 0x48 (likely RTTI or virtual method tables)
  *(int *)((char *)this + 0x3C) = (int)0x00d81f70;
  *(int *)((char *)this + 0x48) = (int)0x00d81f6c;
  
  // Destroy embedded sub-object (e.g., an array/list container) at +0x50
  FUN_004086d0(containerAddr);
  
  // Free dynamically allocated buffer if container's internal pointer is non-null
  if (*containerAddr != 0) {
    FUN_00408310(containerAddr);
  }
  
  // Same for container at +0x58
  int *container2Addr = (int *)((char *)this + 0x58);
  if (*container2Addr != 0) {
    FUN_00408310(container2Addr);
  }
  
  // Global cleanup (e.g., singleton destructor or thread pool shutdown)
  FUN_0046c640();
}