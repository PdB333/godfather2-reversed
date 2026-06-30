// FUNC_NAME: SomeClass::releaseResources
void SomeClass::releaseResources(void)
{
  // this pointer is in ESI (unaff_ESI)
  // Release first resource at +0x10
  if (*(int *)(this + 0x10) != 0) {
    // Call vtable[1] (release/destroy) on the object at +0x10
    (**(code **)(**(int **)(this + 0xc) + 4))(*(int *)(this + 0x10),0);
    *(undefined4 *)(this + 0x10) = 0;
  }
  // Call vtable[3] on the object at +0xc (some cleanup method)
  (**(code **)(**(int **)(this + 0xc) + 0xc))();
  // Release second resource at +0x8
  if (*(int *)(this + 8) != 0) {
    // Call vtable[1] (release/destroy) on the object at +0x8
    (**(code **)(**(int **)(this + 4) + 4))(*(int *)(this + 8),0);
    *(undefined4 *)(this + 8) = 0;
  }
  // Call vtable[3] on the object at +0x4 (some cleanup method)
  (**(code **)(**(int **)(this + 4) + 0xc))();
  return;
}