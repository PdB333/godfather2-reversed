// FUNC_NAME: UnknownClass::~UnknownClass (destructor with pointer cleanup at +0x0C)
void __fastcall UnknownClass::~UnknownClass(UnknownClass* this) 
{
    // +0x00: vtable pointer. Set to parent vtable (base class destructor stub)
    this->vtable = (void**)(PTR_FUN_00d5d89c);
    
    // +0x0C: pointer to dynamically allocated child data
    if (this->ptrAt0C != 0) {
        // Release the child data – possibly calls operator delete or a custom deallocator
        FUN_004daf90(&(this->ptrAt0C));   // Pass address of the pointer to allow nullification
    }
    
    // Finalize: set vtable to purecall to prevent further virtual dispatch
    this->vtable = (void**)(PTR___purecall_00e407a4);
}