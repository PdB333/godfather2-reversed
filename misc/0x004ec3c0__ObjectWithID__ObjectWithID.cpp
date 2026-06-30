// FUNC_NAME: ObjectWithID::ObjectWithID
void __thiscall ObjectWithID::ObjectWithID(int param_2)
{
  // Set vtable pointer to class's vtable
  *this = &vtable_ObjectWithID;  // PTR_LAB_00e372c4
  // Initialize next pointer or flags to 0
  this[1] = 0;  // +0x04: likely m_pNext or m_flags
  if (param_2 != -1)
  {
    // Assign provided ID
    this[2] = param_2;  // +0x08: m_id
    return;
  }
  // Auto-assign a unique ID from global counter
  int newId = g_nextID + 1;
  this[2] = g_nextID;  // +0x08: m_id
  g_nextID = newId;
}