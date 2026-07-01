// FUNC_NAME: GameObject::invokeComponentMethod
void __fastcall GameObject::invokeComponentMethod(int thisPtr) {
    // +0x0C: pointer to base class subobject vtable (adjustment for multiple inheritance)
    int* baseVtable = *(int**)(thisPtr + 0x0C);
    // Virtual call: baseVtable[2] -> returns pointer to a component/interface
    int* componentPtr = reinterpret_cast<int* (__fastcall*)()>(baseVtable[2])();
    // Dereference component to get its vtable
    int* compVtable = *reinterpret_cast<int**>(componentPtr);
    // Virtual call: compVtable[3] -> component method (e.g., update, process)
    reinterpret_cast<void (__fastcall*)()>(compVtable[3])();
}