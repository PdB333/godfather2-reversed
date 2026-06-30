// FUNC_NAME: Component::releaseResources
// Function address: 0x005b3030
// This function checks a flag (bit 15 of first uint) and cleans up a pointer stored in the component, then delegates to base release.

void Component::releaseResources() {
    // Check bit 15 of the flags field at offset 0x00
    if (!(this->flags & (1 << 15))) {
        return;
    }

    // If there's a manager associated (stored at offset 0x54)
    if (this->managerPtr != nullptr) {
        // Retrieve the manager instance (likely from a global or factory)
        SomeManager* mgr = reinterpret_cast<SomeManager*>(FUN_005bc1e0());

        // If a component ID pointer (at offset 0x34) is non‑null, 
        // compare it with the manager's current component
        if (this->componentId != nullptr) {
            uint* current = reinterpret_cast<uint*>(FUN_005bb150(mgr));
            // If this component is the one registered, remove it
            if (current == this->componentId) {
                FUN_005bad80(mgr); // removes from manager
            }
        }
    }

    // Call base class release or finalize
    FUN_005aa310();
}