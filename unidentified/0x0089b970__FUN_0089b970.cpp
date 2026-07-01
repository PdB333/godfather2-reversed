// FUNC_NAME: SomeClass::processComponentEffect
// Function at 0x0089b970: Retrieves a subcomponent from this+0x19c and calls a function on its field at +0x44.
// Likely part of an object that manages audio or visual effects triggered by a child component.

void __thiscall SomeClass::processComponentEffect()
{
    // +0x19c: offset to a child component pointer (e.g., audio component, VFX component)
    int* childComponent = reinterpret_cast<int*>(getChildComponent(this + 0x19c)); // FUN_009b9c60
    if (childComponent != nullptr) {
        // +0x44: offset to an effect handler or resource pointer within the child component
        void* effectHandle = reinterpret_cast<void*>(childComponent[0x44 / 4]); // read dword at +0x44
        onComponentTrigger(effectHandle); // FUN_007a6390
    }
}