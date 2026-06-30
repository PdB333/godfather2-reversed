// FUNC_NAME: ComponentManager::initializeComponent
// Function address: 0x00500b50
// This function initializes a child component (pointed by ESI) 
// using configuration data from EAX, within the context of a manager object (this in ECX).

void ComponentManager::initializeComponent(Component* component, ComponentData* data)
{
    // Global initialization call (likely sets up some engine state)
    FUN_00533cc0();

    // Set vtable pointer for the component (vtable at 0x00e37d00)
    component->vtable = &PTR_FUN_00e37d00;

    // Check if initialization should be skipped (flag at manager +0x0d)
    if (*(char*)(this + 0x0d) == '\0') {
        // Store data pointer into component at offset 0x24 (ES[9])
        component->data = data;

        // Initialize component fields
        component->field_0x44 = 0;          // ESI[0x11]
        component->field_0x48 = FUN_004dafd0(); // ESI[0x12] - some global handle

        // Check flags in data object at offset 0x24 for bit 0x40000000
        if ((*(uint32*)(data + 0x24) & 0x40000000) == 0) {
            // Allocate a child object if global count < 19 (DAT_010c2328)
            if (DAT_010c2328 < 19) {
                component->childObject = (ChildObject*)FUN_004eb950(1); // ESI[0x11]
            } else {
                component->childObject = nullptr;
            }

            // If allocation failed, set initialization flag and return
            if (component->childObject == nullptr) {
                *(uint8*)(this + 0x0c) = 1;
                return;
            }

            // Initialize child object's field at offset 0x10 to 0
            component->childObject->field_0x10 = 0;
        }

        // Handle scale factor based on data flags
        if ((*(uint8*)(data + 0x24) & 4) == 0) {
            // Direct copy from data at offset 0x30
            component->scale = *(float*)(data + 0x30); // ESI[0x0b] = offset 0x2c
        } else {
            // Use a computed value from another function (FUN_004e41b0)
            component->scale = FUN_004e41b0() * *(float*)(data + 0x30);
        }

        // Set remaining component fields
        component->field_0x3c = DAT_00e2b1a4; // ESI[0x0f] - global constant
        component->field_0x28 = component->scale; // ESI[0x0a]
        component->field_0x40 = 0; // ESI[0x10]

        // Finalize component setup
        FUN_00500980(component);
    }
}