// FUNC_NAME: Entity::constructor
void __thiscall Entity::constructor(Entity *this)
{
  undefined **local_18;
  undefined4 local_14;
  undefined4 local_10;
  void *mallocResult;
  undefined4 local_8;
  undefined local_4;
  
  // Initialize vtable pointer (offsets are for a generic EARS object)
  this->vtable = &g_EntityVtable; // +0x00: vtable pointer (PTR_LAB_00e43124)
  
  // Clear reference counts
  this->refCount1 = 0; // +0x04
  this->refCount2 = 0; // +0x08
  
  // Clear resource handles
  this->resourceHandle1 = 0; // +0x18
  this->resourceHandle2 = 0; // +0x1c
  
  // Local structure for streaming buffer allocation
  local_18 = &g_StreamBufferVtable; // PTR_LAB_00e42d64 - stream buffer type
  local_8 = 0x5dc; // 1500 bytes - typical UDP/TCP packet size
  local_14 = 0;
  local_10 = 0;
  
  // Allocate streaming buffer
  mallocResult = malloc(0x5dc);
  
  // Flag for cleanup: 1 means allocated
  local_4 = 1;
  
  // Call StreamBuffer constructor on the allocated memory
  StreamBuffer::constructor(mallocResult, &local_18);
  
  // Initialize the entity's network streaming state
  Entity::initNetworkStreaming(this, &local_18);
  
  // Register with the entity manager
  EntityManager::registerEntity();
  
  return;
}