// FUNC_NAME: UnknownClass::conditionalConstructor
// Function address: 0x0082bd50
// Role: Constructor that calls base class initialization and optionally performs cleanup if the lowest bit of flag is set.

void* __thiscall UnknownClass::conditionalConstructor(byte flag)
{
    // Calls base class initialization (e.g., constructor or virtual base setup)
    this->baseConstructor();  // FUN_0082a340

    // If the LSB of flag is set, invoke cleanup (e.g., destructor or release resources)
    if ((flag & 1) != 0) {
        this->cleanup();  // FUN_009c8eb0
    }

    return this;
}