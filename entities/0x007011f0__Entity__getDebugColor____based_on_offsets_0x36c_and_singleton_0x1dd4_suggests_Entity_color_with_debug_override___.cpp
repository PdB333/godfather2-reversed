// FUNC_NAME: Entity::getDebugColor /* based on offsets 0x36c and singleton 0x1dd4 suggests Entity color with debug override */

// Reconstructed from 007011f0
// Entity::getDebugColor(Color& outColor) - retrieves the entity's base color and optionally overrides it
// with a global debug highlight color stored in GodfatherGameManager (offset 0x1DD4).

struct Color {
    unsigned int r, g, b, a;
};

// Assume this singleton getter exists (call at FUN_007079c0)
extern GodfatherGameManager* GetGameManager();

// Sentinel values representing "no override" or "invalid"
const unsigned int kOverride_invalid0 = 0xBABDBDBAu; // -0x45245246
const unsigned int kOverride_invalid1 = 0xBEEFEEEFu; // -0x41104111
const unsigned int kOverride_invalid2 = 0xEAC15A55u; // -0x153ea5ab
const unsigned int kOverride_invalid3 = 0x91100911u; // -0x6eeff6ef

Color* __thiscall Entity::getDebugColor(Entity* this, Color* outColor) {
    // Copy the entity's base color (16 bytes at this+0x36C)
    *(unsigned long long*)outColor = *(unsigned long long*)((char*)this + 0x36C);
    *((unsigned long long*)outColor + 1) = *(unsigned long long*)((char*)this + 0x374);

    GodfatherGameManager* gm = GetGameManager();
    if (gm != nullptr) {
        unsigned int overrideR = *(unsigned int*)((char*)gm + 0x1DD4);
        unsigned int overrideG = *(unsigned int*)((char*)gm + 0x1DD8);
        unsigned int overrideB = *(unsigned int*)((char*)gm + 0x1DDC);
        unsigned int overrideA = *(unsigned int*)((char*)gm + 0x1DE0);

        // Check if the override is the "no override" sentinel (all zero or all known sentinels)
        bool noOverride = false;
        if (overrideR == 0) {
            if (overrideG == 0 && overrideB == 0 && overrideA == 0) {
                noOverride = true;
            }
        } else if (overrideR == kOverride_invalid0 &&
                   overrideG == kOverride_invalid1 &&
                   overrideB == kOverride_invalid2 &&
                   overrideA == kOverride_invalid3) {
            noOverride = true;
        }

        if (!noOverride) {
            // Apply the debug override color
            outColor->r = overrideR;
            outColor->g = overrideG;
            outColor->b = overrideB;
            outColor->a = overrideA;
        }
    }

    return outColor;
}