// FUNC_NAME: SomeManager::constructor
// Address: 0x0064f490
// Calls base constructor at 0x0064dfe0, initializes various zero fields
void SomeManager::constructor()
{
    // Call base class constructor (likely EARS object base)
    FUN_0064dfe0();

    // Set vtable pointer (from PTR_LAB_00e42f48)
    this->vtable = (SomeManagerVTable*)&PTR_LAB_00e42f48;

    // Initialize fields at various offsets
    // +0x1FC (unaff_ESI[0x7f]) - likely a 4-byte integer
    this->field_0x1FC = 0;                    // unaff_ESI[0x7f]

    // +0x200 (unaff_ESI[0x80]) - 4-byte integer
    this->field_0x200 = 0;                    // unaff_ESI[0x80]

    // +0x208 (unaff_ESI[0x82]) - byte
    this->byteField_0x208 = 0;                // *(undefined1 *)(unaff_ESI + 0x82)

    // +0x20C (unaff_ESI[0x83]) - 4-byte integer
    this->field_0x20C = 0;                    // unaff_ESI[0x83]

    // +0x209 - byte (note: within the same int range as above but separate)
    this->byteField_0x209 = 0;                // *(undefined1 *)((int)unaff_ESI + 0x209)

    // +0x210 (unaff_ESI[0x84]) - 4-byte integer
    this->field_0x210 = 0;                    // unaff_ESI[0x84]

    // +0x214 (unaff_ESI[0x85]) - 4-byte integer
    this->field_0x214 = 0;                    // unaff_ESI[0x85]

    // +0x218 (unaff_ESI[0x86]) - 4-byte integer
    this->field_0x218 = 0;                    // unaff_ESI[0x86]

    // +0x21C (unaff_ESI[0x87]) - 4-byte integer (set twice in original)
    this->field_0x21C = 0;                    // unaff_ESI[0x87] (first assignment)
    this->field_0x21C = 0;                    // unaff_ESI[0x87] (second assignment, redundant)
}