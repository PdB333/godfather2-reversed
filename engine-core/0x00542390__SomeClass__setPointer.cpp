// FUNC_NAME: SomeClass::setPointer
void SomeClass::setPointer(void* newPointer)
{
    // If there is an existing pointer, release it
    if (this->pointer_0x10 != nullptr) {
        releaseOldPointer(this);
        releaseOldPointerSub(this + 8);
        someCleanupFunction();
    }
    
    // Assign the new pointer
    this->pointer_0x10 = newPointer;
    
    // If the new pointer is valid, acquire it
    if (newPointer != nullptr) {
        acquireNewPointer(this);
        acquireNewPointerSub(this + 8);
        someInitFunction();
    }
}