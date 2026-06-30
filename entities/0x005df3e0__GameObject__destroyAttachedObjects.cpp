// FUNC_NAME: GameObject::destroyAttachedObjects
void __thiscall GameObject::destroyAttachedObjects(void)
{
  if (this->field_0x10 != 0) {
    this->field_0x10->release(0);  // vtable[1] with arg 0
    this->field_0x10 = 0;
  }
  this->field_0x0c->shutdown();  // vtable[3] no args
  if (this->field_0x08 != 0) {
    this->field_0x08->release(0);
    this->field_0x08 = 0;
  }
  this->field_0x04->shutdown();  // vtable[3] no args
  return;
}