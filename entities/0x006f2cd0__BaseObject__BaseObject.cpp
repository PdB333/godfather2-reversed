// FUNC_NAME: BaseObject::BaseObject
class BaseObject
{
public:
    // +0x00: virtual function table pointer for this class
    void **vtable;

    // Unknown fields between +0x04 and +0x3C

    // +0x3C: vtable pointer for interface A (e.g., IStreamable)
    void *interfaceAVtable;
    // +0x48: vtable pointer for interface B (e.g., IUpdateable)
    void *interfaceBVtable;

    // +0x50: some state integer (initialized to 0)
    int someState;
    // +0x54: some count or mode (initialized to 2)
    int someCount;

    // Array of 4 slots, each containing an int and two shorts
    // Slot offsets:
    //   slot[0]: int at +0x58, short1 at +0x5C, short2 at +0x5E
    //   slot[1]: int at +0x60, short1 at +0x64, short2 at +0x66
    //   slot[2]: int at +0x68, short1 at +0x6C, short2 at +0x6E
    //   slot[3]: int at +0x70, short1 at +0x74, short2 at +0x76
    // We combine them in a structure for clarity.
    struct Slot {
        int slotInt;      // +0x00 (relative to slot start)
        short slotShort1; // +0x04
        short slotShort2; // +0x06
    } slots[4];

    // Additional integer fields after the slots:
    // +0x7C, +0x80, +0x84, +0x88 (4 ints)
    int extraInts[4];

    // Constructor
    // param_2 is an identifier/ID passed to base constructor
    BaseObject(int objectId)
    {
        // Call base class constructor (FUN_0046c590)
        BaseObject::baseConstructor(objectId);

        // Set vtable to this class's vtable
        vtable = (void**)0x00d605f0; // PTR_FUN_00d605f0

        // Set interface vtable pointers
        interfaceAVtable = (void*)0x00d605e0; // PTR_LAB_00d605e0
        interfaceBVtable = (void*)0x00d605dc; // PTR_LAB_00d605dc

        // Initialize all slots to zero
        for (int i = 0; i < 4; ++i)
        {
            slots[i].slotInt   = 0;
            slots[i].slotShort1 = 0;
            slots[i].slotShort2 = 0;
        }

        // Initialize extra ints to zero
        extraInts[0] = 0;
        extraInts[1] = 0;
        extraInts[2] = 0;
        extraInts[3] = 0;

        // Call additional initialization (FUN_006f2410)
        // (This likely sets up default values for other fields)
        this->additionalInit(); // placeholder name

        // Set remaining fields
        someState = 0;
        someCount = 2;
    }

    // Stub for the base constructor; actual implementation elsewhere
    void baseConstructor(int id);

    // Stub for the additional init function
    void additionalInit();
};