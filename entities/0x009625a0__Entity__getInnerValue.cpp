// FUNC_NAME: Entity::getInnerValue
int __thiscall Entity::getInnerValue(void)
{
  int iVar1;
  
  if (this->m_pInner != (InnerClass *)0x0) {
    iVar1 = this->m_pInner->vtable->methodAt0x3C(0);  // +0x3C virtual function
    return iVar1;
  }
  return 0;
}