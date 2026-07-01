// FUNC_NAME: ComponentManager::updateTwoComponents
// Function at 0x008dd040 - Processes two component objects (A and B) with initialization and virtual update call.
// This appears to be part of a manager that holds pointers to sub-components at offsets 0x194 and 0x18c,
// and uses another sub-object at 0x1bc for additional processing.

void ComponentManager::updateTwoComponents() {
    // +0x194: pointer to a component (ComponentA) - points to a member at offset 0x48 within its parent object
    if (this->m_pComponentA != nullptr && this->m_pComponentA != (ComponentA*)0x48) {
        // +0x1bc: pointer to a helper object (m_pHelper)
        if (this->m_pHelper == nullptr) {
            this->ensureHelperInitialized(); // FUN_008dcc60 - creates or initializes the helper
        }
        HelperObject* helper = this->m_pHelper;
        if (helper != nullptr) {
            // +8 in helper: some sub-field that must be non-null
            if (helper->m_pSubObject == nullptr) {
                helper->initializeSubObject(); // FUN_009e7450
            }
            // Get global manager (returns pointer to some manager)
            GlobalManager* mgr = getGlobalManager(); // FUN_00471610
            // Process the helper at offset 0x30
            mgr->processHelperSub(helper + 0x30); // FUN_008dc750

            // Get base of ComponentA's parent object by subtracting 0x48 from the pointer
            ComponentABase* compBase;
            if (this->m_pComponentA == nullptr) {
                compBase = nullptr;
            } else {
                compBase = (ComponentABase*)((uint8_t*)this->m_pComponentA - 0x48);
            }
            // Call virtual function at vtable offset 0x70 (likely an update/destroy)
            compBase->vtable->method70(); // (**(code **)(*piVar2 + 0x70))()
            // Mark update flag
            markUpdateFlag(1); // FUN_007077a0(1)
        }
    }

    // +0x18c: another component (ComponentB) - similar pattern
    if (this->m_pComponentB != nullptr && this->m_pComponentB != (ComponentB*)0x48) {
        // Get base of ComponentB's parent object
        ComponentBBase* compBBase;
        if (this->m_pComponentB == nullptr) {
            compBBase = nullptr;
        } else {
            compBBase = (ComponentBBase*)((uint8_t*)this->m_pComponentB - 0x48);
        }
        compBBase->vtable->method70();

        // Note: original code calls markUpdateFlag(1) twice if m_pComponentB != nullptr
        markUpdateFlag(1);
        if (this->m_pComponentB != nullptr) {
            markUpdateFlag(1);
            return;
        }
        markUpdateFlag(1);
    }
}