// FUNC_NAME: SomeClass::updateAdjustment

void __thiscall SomeClass::updateAdjustment(float param_2, float param_3)
{
    // Call base class initializer / common setup
    BaseInit();

    // Reference a static function pointer table (often used for polymorphic dispatch)
    void** const functionTable = &PTR_LAB_00e407e8;

    // +0x10, +0x14, +0x18 likely correspond to X, Z, Y velocity or scale factors
    float x = *(float*)(this + 0x10);   // +0x10: horizontal component
    float y = *(float*)(this + 0x14);   // +0x14: vertical component
    float scale = *(float*)(this + 0x18); // +0x18: scaling factor for param_2

    // Compute a scaled and offset value: param_2 * scale + param_3
    float adjusted = param_2 * scale + param_3;

    // Build a temporary 2D vector (stored as {x, 0, y} with padding zero)
    struct Vec2WithPad {
        float x;   // local_c
        uint pad;  // local_8 = 0
        float y;   // local_4
    } vec = { x, 0, y };

    // Call the processing function with vector, function table pointer, and squared result
    ApplyProcessor(&vec, &functionTable, adjusted * adjusted);
    // FUN_005fcf80 presumably uses the function table to apply the vector and squared distance
}