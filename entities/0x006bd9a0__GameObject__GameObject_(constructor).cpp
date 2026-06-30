// FUNC_NAME: GameObject::GameObject (constructor)

void __fastcall GameObject::GameObject(uint *this)
{
  // Set primary vtable
  *this = &PTR_FUN_00d5ea9c;
  
  // Set secondary vtables (multiple inheritance or interface pointers)
  this[0xf] = &PTR_LAB_00d5ea8c;  // +0x3C
  this[0x12] = &PTR_LAB_00d5ea88; // +0x48
  this[0x14] = &PTR_LAB_00d5ea70; // +0x50
  
  // If a previously allocated resource exists at +0xD0, release it
  if (this[0x34] != 0) {
    // Release the object referenced by the vtable at +0x50
    ResourceManager::releaseResource((void *)(this + 0x14));
    this[0x34] = 0; // +0xD0
  }
  
  // Reinitialize resource handles (first release any stale references, then acquire default)
  ResourceHandle::release((ResourceHandle *)(this + 0x1c)); // +0x70
  ResourceHandle::release((ResourceHandle *)(this + 0x1e)); // +0x78
  ResourceHandle::release((ResourceHandle *)&DAT_0112a6ac); // global static
  ResourceHandle::release((ResourceHandle *)&DAT_0120e93c); // global static
  
  ResourceHandle::acquire((ResourceHandle *)(this + 0x1c)); // +0x70
  ResourceHandle::acquire((ResourceHandle *)(this + 0x1e)); // +0x78
  ResourceHandle::acquire((ResourceHandle *)(this + 0x20)); // +0x80
  
  // Initialize global engine subsystems
  Engine::initGlobalSubsystems();
}