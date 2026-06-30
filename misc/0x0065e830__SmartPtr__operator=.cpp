// FUNC_NAME: SmartPtr::operator=
void __thiscall SmartPtr::operator=(int* newPtr)
{
  int* currentPtr = *this->m_ptr; // unaff_EDI dereferenced as the current stored pointer
  if (currentPtr != 0) {
    int* refCountField = currentPtr + 2; // offset 8: reference count
    *refCountField = *refCountField - 1;
    if (*refCountField == 0) {
      // Call destructor through vtable; second entry (offset 8) is typically the destructor
      (*(void (__thiscall**)(int*))(*currentPtr + 8))(currentPtr);
    }
  }
  *this->m_ptr = newPtr;  // store the new pointer
  if (newPtr != 0) {
    *(int*)(newPtr + 8) = *(int*)(newPtr + 8) + 1; // increment reference count at offset 8
  }
}