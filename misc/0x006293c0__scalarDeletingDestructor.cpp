// FUNC_NAME: scalarDeletingDestructor
int __thiscall scalarDeletingDestructor(int this, int deletionFlags)
{
    // +0x08: vtable pointer (or base class pointer) - assumed
    // +0x1c: m_allocSize or similar
    // LAB_006261e0: address of actual destructor body
    // FUN_00636570: operator delete[] or placement delete

    if (deletionFlags == 0) {
        int local_10[2]; // array for delete info
        local_10[0] = *(int *)(this + 8) - 8; // adjust to allocation header
        local_10[1] = 0xffffffff;             // sentinel: all elements
        deletionFlags = FUN_00636570(&LAB_006261e0, local_10, local_10[0] - *(int *)(this + 0x1c));
        if (deletionFlags == 0) {
            return 0;
        }
    }
    FUN_006292e0(); // actual destructor body
    return deletionFlags;
}