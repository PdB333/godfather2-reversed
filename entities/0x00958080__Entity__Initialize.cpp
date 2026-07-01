// FUNC_NAME: Entity::Initialize
void Entity::Initialize(void* param_2) // param_2 likely points to the entity instance
{
    // +0x10: pointer to entity data block; +0x58: some flag or size field
    uint32_t data = *(uint32_t*)(*(int32_t*)((uint32_t)param_2 + 0x10) + 0x58);
    uint32_t zero1 = 0;
    uint32_t zero2 = 0;

    // Clear a temporary 12-byte structure (e.g., Bounds or Vector)
    EA::Memory::MemZero(&data, 0); // 0 may indicate default size

    GlobalUpdateFunction(); // Unknown global initialization step
    ThisMethod(param_2);    // Possibly calls another member function on the entity
}