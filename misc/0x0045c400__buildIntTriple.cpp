// FUNC_NAME: buildIntTriple
struct IntTriple {
    int field0; // +0x00
    int field4; // +0x04
    int field8; // +0x08
};

void buildIntTriple(int* param1, int param2, int param3)
{
    IntTriple triple;
    triple.field0 = *param1;        // Copy value pointed to by param1
    triple.field4 = param2;         // Store param2
    triple.field8 = 0;              // Zero third field (null terminator or flag)
    FUN_00408a00(&triple, param3); // Process the triple with additional param3
}