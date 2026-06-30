// FUNC_NAME: EARSObject::scalarDeletingDestructor
// Function at 0x00688750: Scalar deleting destructor for an EARS engine object.
// Calls release on a member pointer at +0x140, performs global cleanup,
// and optionally deletes this instance (size 0x160) if flag bit 0 is set.
// Returns the this pointer (consistent with MSVC scalar deleting destructor pattern).

int __thiscall EARSObject::scalarDeletingDestructor(byte flags)
{
    // Release the component/subsystem pointed to at offset 0x140
    if (*(void**)(this + 0x140) != 0) {
        releaseComponent(*(void**)(this + 0x140)); // FUN_004daf90
    }

    // Global cleanup: perhaps memory manager or engine shutdown step
    globalCleanup(); // FUN_00726b40

    // If the "delete this" flag is set (bit 0), free the object memory
    if ((flags & 1) != 0) {
        operatorDelete(this, 0x160); // FUN_0043b960, size matches class size
    }

    return this;
}