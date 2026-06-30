// FUNC_NAME: ResourceHandle::~ResourceHandle
void __thiscall ResourceHandle::~ResourceHandle(uint this)
{
  undefined localBuffer[8];
  
  // Call sub-destructor with local buffer, this pointer, the resource value (first 4 bytes of pointed object), and the pointer itself
  FUN_006961f0(localBuffer,this,*(uint *)*(uint *)(this + 4),this,*(uint *)(this + 4));
  
  // Release the resource object
  FUN_009c8eb0(*(uint *)(this + 4));
  
  // Clear the resource pointer and auxiliary field
  *(uint *)(this + 4) = 0;
  *(uint *)(this + 8) = 0;
}