// FUNC_NAME: SomeClass::cleanupResources
// Function at 0x004bbeb0: Releases three sub-object pointers at offsets +0x0C, +0x18, +0x24.
// Likely called from a destructor or during object cleanup.

// +0x0C: Pointer to first sub-object
// +0x18: Pointer to second sub-object
// +0x24: Pointer to third sub-object

void SomeClass::cleanupResources()
{
    // Release first sub-object if allocated
    if (this->subObject1 != nullptr) {
        freeObject(this->subObject1); // FUN_009c8f10 - assumed custom deallocation
    }

    // Release second sub-object if allocated
    if (this->subObject2 != nullptr) {
        freeObject(this->subObject2);
    }

    // Release third sub-object if allocated
    if (this->subObject3 != nullptr) {
        freeObject(this->subObject3);
    }
}