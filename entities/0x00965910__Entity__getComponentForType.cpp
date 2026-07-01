// FUNC_NAME: Entity::getComponentForType
int __fastcall Entity::getComponentForType(Entity* this)
{
    int componentType;
    int* subtypeField;

    // Read entity type from offset +0xDC
    componentType = *(int*)((int)this + 0xDC);

    // Determine which subtype field to use based on entity type
    if (componentType == 0xB) {
        // Type 0xB: use subtype at +0x588
        componentType = *(int*)((int)this + 0x588);
    }
    else if (componentType == 0xC) {
        // Type 0xC: use subtype at +0x6E8
        componentType = *(int*)((int)this + 0x6E8);
    }

    // Return appropriate component pointer based on subtype
    switch (componentType) {
        case 1:
        case 3:
        case 5:
            // Return generic component at +0x2EC
            return (int)this + 0x2EC;
        case 4:
            // Check global singleton (DAT_01223484) - possibly a manager
            if (DAT_01223484 != 0) {
                if (*(int*)(DAT_01223484 + 8) != 0) {
                    // Manager's internal data exists, use same offset as cases 1/3/5
                    return (int)this + 0x2EC;
                }
                // Fall through to case 6/7
            }
            break;
        case 6:
        case 7:
            // Return specialized component at +0x378
            return (int)this + 0x378;
    }

    // No component found
    return 0;
}