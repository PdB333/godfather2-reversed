// FUNC_NAME: ComponentBase::attachToSlot
void ComponentBase::attachToSlot(void* slotPtr, int parentComponent) {
    // slotPtr is likely a pointer to a component slot structure (two fields)
    // parentComponent: handle to parent component (0 if none)
    int childHandle;
    
    // Store this component's address into the slot's first field
    *(void**)slotPtr = this;
    
    // Call virtual function at vtable[2] (pre-attach initialization)
    (this->*vtable[2])();
    
    if (parentComponent != 0) {
        // Register child and get handle
        childHandle = FUN_004265d0(parentComponent, this); // allocate child slot ID
        // Store handle in slot's second field
        *((int*)slotPtr + 1) = childHandle;
        
        // Call virtual function at vtable[1] with parent and flags=0
        (this->*vtable[1])(parentComponent, 0);
        
        // Call virtual function at vtable[3] (post-attach finalize)
        (this->*vtable[3])();
        return;
    }
    // No parent: zero out handle
    *((int*)slotPtr + 1) = 0;
    
    // Still call finalize
    (this->*vtable[3])();
}