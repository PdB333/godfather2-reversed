// FUNC_NAME: IndexCollector::collectFromObjects
void __thiscall IndexCollector::collectFromObjects(IndexCollector *this, int someArg, void **objects)
{
  // objects is an array of two pointers: objects[0] and objects[1]
  // Each points to an object with a vtable; method at vtable+0xC is called
  // this->data (offset 0): pointer to int array
  // this->size (offset 4): current number of elements
  // this->capacity (offset 8): allocated capacity

  this->data = 0;
  this->size = 0;
  this->capacity = 0;

  // Call a method on objects[0] with someArg
  typedef void (__thiscall *MethodType)(void *, int);
  MethodType method0 = *(MethodType *)(*(int *)objects[0] + 0xC);
  method0(objects[0], someArg);

  int index = 0;
  do {
    // Call a method on objects[1] with current index
    MethodType method1 = *(MethodType *)(*(int *)objects[1] + 0xC);
    method1(objects[1], index);

    bool isActive = fun_00499ce0();   // global predicate function

    if (isActive) {
      if (this->size == this->capacity) {
        int newCapacity = (this->capacity == 0) ? 1 : this->capacity * 2;
        fun_00486800(newCapacity);   // reallocate internal array (uses global state? likely acts on 'this')
        this->capacity = newCapacity;   // assumption: actual capacity update happens inside fun_00486800
      }
      int *dest = this->data + this->size;   // offset = size * 4
      this->size++;
      if (dest != 0) {
        *dest = index;
      }
    }
    index++;
  } while (index < 0x2b);   // 43 iterations (0 to 42)
}