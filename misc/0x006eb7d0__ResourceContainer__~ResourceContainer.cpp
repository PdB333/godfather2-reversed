// FUNC_NAME: ResourceContainer::~ResourceContainer
// Function at 0x006eb7d0: Destructor for ResourceContainer.
// Frees two dynamically allocated members at offsets +0x04 and +0x0C.
void __thiscall ResourceContainer::~ResourceContainer()
{
    // +0x04: pointer to first allocated resource
    if (this->resourceA != nullptr) {
        deallocate(this->resourceA);  // calls FUN_004daf90 – memory deallocation
    }
    // +0x0C: pointer to second allocated resource
    if (this->resourceB != nullptr) {
        deallocate(this->resourceB);
    }
}