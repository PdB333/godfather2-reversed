// FUNC_NAME: SomeClass::initialize
void __fastcall SomeClass::initialize(SomeClass* this)
{
    // Call base class constructor/initializer (likely virtual or inherited)
    baseClassInit();

    // Initialize three consecutive fields at offsets 0x120, 0x124, 0x128 to zero
    // These likely represent an embedded sub-struct or three separate quantities (e.g., flags, counters)
    this->field_0x120 = 0;
    this->field_0x124 = 0;
    this->field_0x128 = 0;
}