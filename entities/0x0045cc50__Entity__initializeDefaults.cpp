// FUNC_NAME: Entity::initializeDefaults
// Address: 0x0045cc50
// Role: Initializes an entity to default state, setting three fields to a global default value and zeroing out four fields at the end.

void __fastcall Entity::initializeDefaults(Entity *this)
{
    Entity::baseInit(); // calls base class or common initialization routine at 0x0045cbe0

    int defaultVal = DAT_00e2b1a4; // global default value (likely a sentinel or invalid index)

    this->field0 = defaultVal;  // +0x00
    this->field20 = defaultVal; // +0x14 (index 5)
    this->field40 = defaultVal; // +0x28 (index 10)

    this->field48 = 0; // +0x30 (index 12)
    this->field52 = 0; // +0x34 (index 13)
    this->field56 = 0; // +0x38 (index 14)
    this->field60 = 0; // +0x3C (index 15)
}