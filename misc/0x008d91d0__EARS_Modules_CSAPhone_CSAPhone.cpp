// Xbox PDB: EARS_Modules_CSAPhone_CSAPhone
// FUNC_NAME: CSAPhoneComponent::CSAPhoneComponent (constructor)
// Address: 0x008d91d0
// This function constructs a CSAPhoneComponent object, initializes its vtable, sets up message event registrations,
// and stores global data handles.

class CSAPhoneComponent : public SomeBaseClass {
public:
    // Constructor; param_2 is likely an identifier or parent pointer passed to the base class.
    CSAPhoneComponent(int param_2);
};

CSAPhoneComponent::CSAPhoneComponent(int param_2) {
    // Call base class constructor (FUN_008d8190) with the provided parameter
    baseClassConstructor(param_2);

    // Set vtable pointer to the class-specific vtable
    *(void**)this = &CSAPhoneComponent_vtable;

    // Initialize offset 0x3C (0xF*4) through 0x58 (0x16*4) with event handler/label pointers
    // These are likely function table pointers or string IDs for event dispatching.
    this->field_0x3C = &label_at_0x00d7dca0;
    this->field_0x48 = &label_at_0x00d7dc9c;
    this->field_0x50 = &label_at_0x00d7dc98;
    this->field_0x54 = &label_at_0x00d7dc38;
    this->field_0x58 = &label_at_0x00d7dbd0;

    // Set magic debug markers to detect memory corruption
    this->magicMarker1 = 0xbadbadba;     // @ offset 0x68 (0x1A0)
    this->magicMarker2 = 0xbeefbeef;     // @ offset 0x69 (0x1A4)
    this->magicMarker3 = 0xeac15a55;     // @ offset 0x6A (0x1A8)
    this->magicMarker4 = 0x91100911;     // @ offset 0x6B (0x1AC)
    this->magicMarker5 = 0;              // @ offset 0x6C
    this->magicMarker6 = 0;              // @ offset 0x6D
    this->magicMarker7 = 0;              // @ offset 0x6E
    this->magicMarker8 = 0;              // @ offset 0x6F

    // Initialize message registration fields (offsets 0x74, 0x75, 0x76, etc.)
    this->messageRegField1 = 0;               // @ offset 0x74
    *reinterpret_cast<short*>(&this->messageRegField1 + 2) = 0;  // @ offset 0x76 partial
    this->messageRegField2 = 0;               // @ offset 0x76 (actually after the short)
    // But the decompiled shows separate assignment at 0x76 (int) and then short at 0x77 and at 0x1DE.
    // Let's align with the original offsets:
    // Actually the code: param_1[0x74] = 0; *(undefined2 *)(param_1 + 0x75) = 0; (0x75 is two bytes after 0x74)
    // Then param_1[0x76] = 0; *(undefined2 *)(param_1 + 0x77) = 0; (0x77 after 0x76)
    // So we have two pairs: (int at 0x74, short at 0x75) and (int at 0x76, short at 0x77)
    // Also there's a short at 0x1DE = 0x77*4? No, 0x1DE is not aligned; it's probably a separate field.
    // For simplicity, we'll treat as bitfields or two 6-byte structures.

    this->activateEventHandle = 0;    // offset 0x74 (int)
    this->activateEventPad1 = 0;      // short at 0x75
    this->deactivateEventHandle = 0;  // offset 0x76 (int)
    this->deactivateEventPad2 = 0;    // short at 0x77
    this->someOtherShort = 0;         // short at offset 0x1DE (0x1DE = 0x77*4 + 2? Actually 0x1DE is 478 decimal, not standard offset)

    // More magic markers at offsets 0x78-0x81
    this->field_0x78 = 0;
    this->field_0x79 = 0;
    this->field_0x7A = 0;
    this->field_0x7B = 0;
    this->field_0x7C = 0;
    this->field_0x7D = 0;
    this->field_0x7E = 0;
    this->field_0x7F = 0;
    this->field_0x80 = 0;
    this->field_0x81 = 0;

    // Second set of magic markers at offsets 0x85-0x88
    this->magicMarker9 = 0xbadbadba;
    this->magicMarker10 = 0xbeefbeef;
    this->magicMarker11 = 0xeac15a55;
    this->magicMarker12 = 0x91100911;

    // More fields cleared at offsets 0x89-0x97
    this->field_0x89 = 0;
    this->field_0x8A = 0;
    this->field_0x8B = 0;
    this->field_0x8C = 0;
    this->field_0x8F = 0;
    this->field_0x90 = 0;
    this->field_0x91 = 0;
    this->field_0x92 = 0;
    this->field_0x93 = 0;
    this->field_0x94 = 0;
    this->field_0x95 = 0;
    this->field_0x96 = 0;
    this->field_0x97 = 0;

    // Register global events (if the global pointers are non-null)
    if (g_CSAEvent1 != 0) {
        registerEvent(this + 0x3C, g_CSAEvent1, 0x8000); // FUN_00408900(&this->field_0x3C, &g_CSAEvent1, 0x8000)
    }
    if (g_CSAEvent2 != 0) {
        registerEvent(this + 0x3C, g_CSAEvent2, 0x8000);
    }

    // Resolve and register phone activate/deactivate events
    int* activatePtr = this + 0x74; // offset 0x74
    int* deactivatePtr = this + 0x76; // offset 0x76

    *activatePtr = getMessageID("iMsgCSAPhoneActivateEvent"); // FUN_00408240
    if (*activatePtr != 0) {
        registerEvent(this + 0x3C, activatePtr, 0x8000);
    }

    *deactivatePtr = getMessageID("iMsgCSAPhoneDeActivateEvent");
    if (*deactivatePtr != 0) {
        registerEvent(this + 0x3C, deactivatePtr, 0x8000);
    }

    if (g_CSAEvent3 != 0) {
        registerEvent(this + 0x3C, g_CSAEvent3, 0x8000);
    }

    // Store global data handles
    this->globalData1 = g_someGlobal1;    // DAT_00d5e288
    this->globalData2 = g_someGlobal2;    // DAT_00d5f6c8
    int globalHandle = g_someGlobal3;     // DAT_00d5833c

    // Set various flags to 0
    *(char*)&this->field_0x60 = 0;        // byte at offset 0x60
    *(char*)&this->field_0x64 = 0;        // byte at offset 0x64 (100 decimal = 0x64)
    this->field_0x65 = 0;
    this->field_0x67 = 0;
    this->field_0x66 = 0;
    this->field_0x8D = 0;
    this->field_0x73 = 0;
    this->field_0x72 = 0;
    this->field_0x8E = globalHandle;       // offset 0x8E
}