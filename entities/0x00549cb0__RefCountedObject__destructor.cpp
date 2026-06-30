// FUNC_NAME: RefCountedObject::destructor
void __thiscall RefCountedObject::destructor(RefCountedObject *this)
{
  // +0xC0: pointer to a shared inner ref-counted object (subObject)
  InnerRefCounted *subObject = (InnerRefCounted *)this->field_C0;
  
  // Update vtable to base class (destructor step)
  this->vtable = &PTR_FUN_00e39bc8;
  
  if (subObject != nullptr) {
    // Inner object structure (at offset 0: vtable, offset 4: short refCount1, offset 6: short refCount2)
    if (*(short *)(&subObject->refCount1) != 0) { // refCount1 at +4
      // Decrement refCount2 at offset 6
      short newRefCount2 = --(*(short *)((int)subObject + 6)); // refCount2 at +6
      if (newRefCount2 == 0) {
        // Call the inner object's release virtual function (vtable[0]) with param 1
        (*(void (__thiscall **)(InnerRefCounted *, int))subObject->vtable)(subObject, 1);
      }
    }
    this->field_C0 = nullptr; // Clear pointer
  }
}