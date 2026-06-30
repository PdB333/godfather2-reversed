// FUNC_NAME: Entity::memoryManagerDeallocateDual
void Entity::memoryManagerDeallocateDual(void* param_1)
{
  // Dereference global pointer at 0x012234ac to get memory manager,
  // then call a function at vtable offset +0x04 to deallocate with second parameter 0
  // This appears to be a standard EA EARS memory manager interface call
  (**(code (***)(void))(*(int*)(DAT_012234ac + 4) + 4))(param_1, 0);
}