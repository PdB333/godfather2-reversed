// FUNC_NAME: ComponentBase::ComponentBase
// Function address: 0x0077ac70
// Constructor for a component base class that categorizes types into priority groups.

void __thiscall ComponentBase::ComponentBase(ComponentBase *this, int type, int arg3, int arg4)
{
  this->m_vtable = &ComponentBase_vtable; // +0x00: vtable pointer (PTR_FUN_00d68494)
  this->m_type = type;                    // +0x04: type identifier
  this->m_arg3 = arg3;                    // +0x08: third parameter
  this->m_arg4 = arg4;                    // +0x0C: fourth parameter
  this->m_category = 0;                   // +0x10: derived category/priority

  // Map type to a category: 0-3 => category 1, 4-11 => category 2, 12 => category 0
  switch (type)
  {
  case 0:
  case 1:
  case 2:
  case 3:
    this->m_category = 1;
    break;
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 11:
    this->m_category = 2;
    break;
  case 12:
    this->m_category = 0;
    break;
  // Default: no change (remains 0)
  }
}