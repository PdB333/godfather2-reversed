// Function address: 0x0040fc70
// Role: Setter for a member at offset 0x4DC (likely a pointer or handle). Returns the previous value.
int __thiscall CEntity::SetProperty(int newValue)
{
    int oldValue = this->m_nProperty; // +0x4DC
    this->m_nProperty = newValue;
    return oldValue;
}