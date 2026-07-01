// FUNC_NAME: UnkClass::destroy
// Function at 0x00816080 - Destructor / cleanup method for an unknown class.
// This function is called from multiple constructors/destructors and likely
// performs orderly teardown: destroys a sub‑object at offset 0x10, releases
// a resource controlled by a byte flag at offset 0xc, and runs a global
// cleanup step.
void __fastcall UnkClass::destroy(void *thisPtr)
{
    // 0x10: sub‑object (e.g., a member struct or another object)
    // Call its destructor.
    destroySubObject((int)thisPtr + 0x10);

    // 0x0c: byte flag (ownership, resource type, or state)
    // Release the associated resource.
    releaseResource(*(byte *)((int)thisPtr + 0xc));

    // Perform any final global cleanup (e.g., reference counting, pool return).
    finalizeCleanup();
}