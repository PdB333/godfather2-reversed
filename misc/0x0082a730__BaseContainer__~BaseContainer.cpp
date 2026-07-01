// FUNC_NAME: BaseContainer::~BaseContainer
void __fastcall BaseContainer::~BaseContainer(BaseContainer* this)
{
    uint count;
    undefined4** elementPtr;

    // Set vtable to the destructor vtable (prevents further virtual calls)
    this->vtable = &PTR_FUN_00d737b0;

    // Iterate through the array of child objects and call their destructors
    if (this->elementCount != 0) {
        for (count = 0; count < this->elementCount; count++) {
            elementPtr = *(undefined4***)(this->elementArray + count * 4);
            if (elementPtr != nullptr) {
                // Call the first virtual function (likely destructor) with argument 1 (delete flag)
                (**(code**)(*elementPtr))(1);
            }
        }
    }

    // Free the array memory
    if (this->elementArray != nullptr) {
        FUN_009c8f10(this->elementArray); // likely operator delete or free
    }
}