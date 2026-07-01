// FUNC_NAME: SomeClass::deinitializeComponent
void __thiscall SomeClass::deinitializeComponent(uint this, uint param_2)
{
  // Call base component deinitialization (likely component base class)
  SomeBaseComponent::deinitialize(this, param_2);
  
  // Notify framework or manager that this component is being destroyed/disabled
  // The parameter inverts the flag: passing true when this was non-zero, false otherwise
  ComponentManager::notifyComponentDeactivated((this != 0));
  
  return;
}