// FUNC_NAME: GameObject::finalize
class GameObject {
    // +0x00: vtable pointer for first base class (Base1)
    void* mpVTableBase1;
    // +0x04: owned child object associated with Base1
    ChildObject* mpChild1;
    // +0x08: vtable pointer for second base class (Base2)
    void* mpVTableBase2;
    // +0x0C: owned child object associated with Base2
    ChildObject* mpChild2;
};

// Destructor/finalize: Release owned child objects and call base class cleanup.
void __thiscall GameObject::finalize() {
    typedef void (__thiscall *ReleaseFunc)(ChildObject*, bool);
    typedef void (__thiscall *CleanupFunc)();

    // Handle child associated with Base2
    if (mpChild2 != nullptr) {
        // Call virtual release on child2 (vtable+0x04) with false (0)
        ReleaseFunc releaseChild2 = (ReleaseFunc)(*(int*)mpVTableBase2 + 4);
        releaseChild2(mpChild2, false);
        mpChild2 = nullptr;
    }

    // Call Base2's cleanup (vtable+0x0C)
    CleanupFunc cleanupBase2 = (CleanupFunc)(*(int*)mpVTableBase2 + 0x0C);
    cleanupBase2();

    // Handle child associated with Base1
    if (mpChild1 != nullptr) {
        // Call virtual release on child1 (vtable+0x04) with false (0)
        ReleaseFunc releaseChild1 = (ReleaseFunc)(*(int*)mpVTableBase1 + 4);
        releaseChild1(mpChild1, false);
        mpChild1 = nullptr;
    }

    // Call Base1's cleanup (vtable+0x0C)
    CleanupFunc cleanupBase1 = (CleanupFunc)(*(int*)mpVTableBase1 + 0x0C);
    cleanupBase1();
}