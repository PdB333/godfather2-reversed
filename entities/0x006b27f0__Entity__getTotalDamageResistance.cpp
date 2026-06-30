// FUNC_NAME: Entity::getTotalDamageResistance
// Address: 0x006b27f0
// Role: Calculates total damage resistance for a given resistance type (stored at this+0x16c). 
//        Sums base resistance (this+0x170) with values from a global linked list of modifiers.
//        For resistance types 2,3,4 (bullet, fire, explosion?), multiplies each modifier by a
//        factor obtained from FUN_008c7710 (called with this+0x40, likely health or similar).
//        Returns the rounded integer total.

#include <cmath> // for std::round (optional, but we use manual rounding)

// Global table of modifier nodes; each node is 0x10 bytes.
// First dword (offset 0x00): next node index (linked list), 0 = end.
// Second dword (offset 0x04): float modifier value.
struct ModifierNode {
    int nextIndex;   // +0x00
    float value;     // +0x04
    // Padding to 0x10
};

extern ModifierNode gModifierTable[]; // Address: 0x00e50d0c

// External function returning a multiplier (80-bit float, treated as double here).
// Called with (this+0x40) as argument; possibly returns a health factor or damage scalar.
extern double __fastcall FUN_008c7710(int param);

int __fastcall Entity::getTotalDamageResistance(int this_ptr) {
    float total = 0.0f;

    // Resistance type identifier (e.g., 2=bullet, 3=fire, 4=explosion)
    int resistanceType = *(int*)(this_ptr + 0x16c);
    if (resistanceType != 0) {
        // Base resistance value for this type
        total = *(float*)(this_ptr + 0x170);

        // Walk the linked list of modifiers, starting from the global entry for this type
        int currentNodeIdx = gModifierTable[resistanceType].nextIndex; // first node index
        while (currentNodeIdx != 0) {
            float modValue = gModifierTable[currentNodeIdx].value;

            // Get multiplier from external function (e.g., current health ratio)
            double multiplier = FUN_008c7710(*(int*)(this_ptr + 0x40));
            if (multiplier > 0.0) {
                // Only apply multiplier to specific resistance types (bullet/fire/explosion)
                if (resistanceType == 2 || resistanceType == 3 || resistanceType == 4) {
                    modValue *= (float)multiplier;
                }
            }

            total += modValue;
            currentNodeIdx = gModifierTable[currentNodeIdx].nextIndex; // next node in chain
        }
    }

    // Round to nearest integer (ROUND in original)
    return (int)(total + 0.5f);
}