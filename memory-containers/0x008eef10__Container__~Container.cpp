// FUNC_NAME: Container::~Container

void __thiscall Container::~Container(Container *this)
{
    // +0x4: pointer to owned resource (e.g., allocated buffer)
    // +0x8: size/count associated with the resource
    undefined savedData[8]; // temporary storage used by helper, likely unused after

    // Helper function that may copy or prepare the resource before release
    FUN_008ee5b0(savedData, this, *(void **)(this + 4), this, *(void **)(this + 4));
    // Free the resource
    FUN_009c8eb0(*(void **)(this + 4));
    // Clear pointer and size
    *(void **)(this + 4) = 0;
    *(int *)(this + 8) = 0;
}