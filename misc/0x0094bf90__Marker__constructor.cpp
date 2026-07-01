// FUNC_NAME: Marker::constructor
// Function: 0x0094bf90 - Constructor for Marker object (EA EARS engine)
// Initializes marker with ID, parent, position, flags, radius, and audio settings.

#include <stdio.h> // For __snprintf

// Forward declarations of called functions
void function_005c0a30(); // Unused? called but no purpose visible
void function_0094b290(uint param_7); // Initialize some subsystem with param_7
void function_00948b20(uint param_10); // Initialize other subsystem with param_10
void function_009496d0(int* nodePtr); // Insert this marker into a linked list (param_4 is parent/list head)
bool function_0094b9b0(); // Check if marker should be active (returns 0 to force flag 0x40000)

// External globals (likely engine state)
extern int DAT_00d5780c; // +0x1D8 initial value? 
extern int DAT_00d5ccf8; // +0x1E4 initial value?
extern const char* PTR_s_marker__00e56a54; // String "marker"

class Marker {
public:
    // Constructor
    Marker* __thiscall constructor(uint id, uint param_3, int* parentNode, float* position, 
                                   uint flags, uint param_7, float radius, float radiusSquared, 
                                   uint param_10) {
        // Initialize core fields
        this->field_0x04 = param_3;     // +0x04: param_3 (unknown purpose)
        this->field_0x00 = id;           // +0x00: ID

        this->field_0x118 = 1;           // +0x118: unknown counter/flag
        this->field_0x11C = flags;       // +0x11C: main flags (bit field)
        this->field_0x120 = 0;           // +0x120: unknown
        this->field_0x124 = radiusSquared * radiusSquared; // +0x124: squared radius squared? (unusual)

        // Linked list insertion: if parentNode is not null, offset by 0x48 to get next pointer
        int* listNodePtr = 0;
        if (parentNode != 0) {
            listNodePtr = parentNode + 0x48 / 4; // Convert byte offset 0x48 to int offset (0x48/4=18)
        }
        this->listNext = listNodePtr;             // +0x154
        this->listPrev = 0;                       // +0x158
        if (listNodePtr != 0) {
            // Insert after listNodePtr: set prev of next, then set next of listNodePtr to us
            this->listPrev = *(int*)((char*)listNodePtr + 4); // Assume offset 4 is previous pointer in node
            *(int**)((char*)listNodePtr + 4) = &this->listNext;
        }

        // Zero out a large block from offsets 0x190 to 0x1D8 (approximately)
        this->field_0x190 = 0;
        this->field_0x194 = 0;
        this->field_0x198 = 0;
        this->field_0x19C = 0;
        // ... many more zeroes (offsets 0x1A0 to 0x1D4)
        this->field_0x1A0 = 0;
        this->field_0x1A4 = 0;
        this->field_0x1A8 = 0;
        this->field_0x1AC = 0;
        this->field_0x1B0 = 0;
        this->field_0x1B4 = 0;
        this->field_0x1B8 = 0;
        this->field_0x1BC = 0;
        this->field_0x1C0 = 0;
        this->field_0x1C4 = 0;
        this->field_0x1C8 = 0;
        this->field_0x1CC = 0;
        this->field_0x1D0 = 0;
        this->field_0x1D4 = 0;
        this->field_0x1D8 = DAT_00d5780c; // +0x1D8: from global

        // Set byte flags
        *(char*)&this->field_0x1DC = 1;   // +0x1DC: byte flag = 1
        *(char*)((int)this + 0x1DD) = 0;  // +0x1DD: byte = 0

        // +0x1E0: unknown (maybe a repeat of field_0x1DC as int?)
        this->field_0x1E0 = 0;
        this->field_0x1E4 = DAT_00d5ccf8; // +0x1E4: from global
        this->field_0x1E8 = DAT_00d5ccf8; // +0x1E8: same

        // Zero another block (offsets 0x200 to 0x21C)
        this->field_0x200 = 0;
        this->field_0x1FC = 0; // Actually 0x1FC-0x210: five zeros
        this->field_0x1F8 = 0;
        this->field_0x1F4 = 0;
        this->field_0x1F0 = 0;

        // More zeros (offsets 0x210 to 0x21C)
        this->field_0x210 = 0;
        this->field_0x214 = 0;
        this->field_0x218 = 0;
        this->field_0x21C = 0;

        // Generate name: "marker<ID>"
        char name[16];
        __snprintf(name, 16, "%s%u", PTR_s_marker__00e56a54, id);
        // name is stored starting at offset 0x08 (since param_1+2 means pointer to field at offset 8 bytes)
        // We'll assume field_0x08 is char name[16]
        for (int i = 0; i < 16; i++) this->name[i] = name[i];

        // Terminate name? Actually __snprintf writes null, so fine
        *(char*)(&this->field_0x18) = 0; // Byte after name set to 0

        // If position pointer is NULL, set position to zero (vec4)
        if (position == 0) {
            this->position.x = 0; // +0x140
            this->position.y = 0; // +0x144
            this->position.z = 0; // +0x148
            this->position.w = 0; // +0x14C
        } else {
            // Copy vec4 from position pointer
            this->position.x = position[0];
            this->position.y = position[1];
            this->position.z = position[2];
            this->position.w = position[3];
        }

        // Call initialization functions
        function_0094b290(param_7);
        function_00948b20(param_10);

        // If radius (param_8) differs from stored radius, update and set flag bit 0x200000
        if (*(float*)&this->field_0x120 != radius) { // field_0x120 is stored as int but used as float later
            this->field_0x120 = *(int*)&radius; // reinterpret the float as int storage
            this->field_0x11C |= 0x200000; // Set bit 21
        }

        // Insert into linked list using parentNode pointer (passed again)
        function_009496d0(parentNode);

        // Conditionally set flag based on multiplayer check
        if (((this->field_0x11C >> 7) & 1) == 0) { // Bit 7 clear?
            bool active = function_0094b9b0();
            if (!active) {
                this->field_0x11C |= 0x40000; // Set bit 18
            }
        }

        // Clear a few bytes
        *(char*)((int)this + 0x153) = 0;
        *(char*)((int)this + 0x152) = 0;
        *(char*)((int)this + 0x151) = 0;
        *(char*)((int)this + 0x150) = 0; // +0x150 byte (field_0x54 as byte)

        return this;
    }

    // Fields (selected, not complete)
    uint field_0x00;    // +0x00: ID
    uint field_0x04;    // +0x04: param_3
    char name[16];      // +0x08: name string
    // +0x18: byte terminator
    // ... (padding)
    // +0x118: unknown (set to 1)
    // +0x11C: flags
    // +0x120: radius stored as int (float reinterpret)
    // +0x124: radiusSquared * radiusSquared (float)
    // +0x140: vec4 position (x,y,z,w)
    // +0x154: listNext (int*)
    // +0x158: listPrev (int*)
    // +0x190 to +0x1D4: many zero fields
    // +0x1D8: some global value
    // +0x1DC: byte flag
    // +0x1E0: int
    // +0x1E4: global value
    // +0x1E8: global value
    // +0x1F0-0x21C: zeros
    // +0x150-0x153: bytes set to 0 at end
};

// Note: The offsets are guessed and may not exactly match, but the reconstruction captures the logic.