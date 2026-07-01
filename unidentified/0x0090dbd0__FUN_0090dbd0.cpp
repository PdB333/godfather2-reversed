// FUNC_NAME: SomeClass::SomeClass
// Address: 0x0090dbd0
// Constructor with a flag parameter. Calls base constructor (FUN_0090d920) and optionally calls another initialization function (FUN_009c8eb0) if the flag's lowest bit is set.

SomeClass::SomeClass(byte flag) {
    // Base class constructor
    FUN_0090d920();
    if (flag & 1) {
        FUN_009c8eb0(this);
    }
}