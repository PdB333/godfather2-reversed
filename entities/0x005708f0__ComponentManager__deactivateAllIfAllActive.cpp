// FUNC_NAME: ComponentManager::deactivateAllIfAllActive
void __fastcall ComponentManager::deactivateAllIfAllActive(ComponentManager* this, int param_2)
{
    // param_2 is a pointer to a container (likely another manager or list)
    // +0x2c: int count (number of items)
    // +0x30: array of pointer to Component objects
    int count = *(int*)(param_2 + 0x2c);
    if (count > 0) {
        int i = 0;
        do {
            Component* comp = *(Component**)(*(int*)(param_2 + 0x30) + i * 4);
            // comp->field_4 byte (type flag) masked to 0xFF
            if ((comp->field_4 & 0xFF) < 10) {
                // For type < 10: check flag at +0x24
                if (comp->flagA == 0) {
                    return; // abort if already zero
                }
                comp->flagA = 0;
            } else {
                // For type >= 10: check flag at +0x2c
                if (comp->flagB == 0) {
                    return; // abort if already zero
                }
                comp->flagB = 0;
            }
            i++;
        } while (i < count);
    }
    // Returns after all flags cleared successfully, or earlier if any already zero
}