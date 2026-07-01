// FUNC_NAME: CoverHintNode::CoverHintNode
// Constructor at 0x0078dce0 for AI cover hint node
// Initializes all fields to default values (0, -1 for sentinel values)
// Base class call to FUN_0046c590 likely initializes parent fields

CoverHintNode* __thiscall CoverHintNode::CoverHintNode(CoverHintNode* this, uint32_t baseArg)
{
    // Call base class constructor (e.g., some kind of Node or Entity)
    BaseClassConstructor(baseArg);

    // Set vtable pointer
    this->vtable = (void*)0x00d69b54;                           // +0x00

    // Virtual function table pointers for sub-objects (multiple inheritance or interface)
    this->field_0x3C = (void*)0x00d69b44;                      // +0x3C
    this->field_0x48 = (void*)0x00d69b40;                      // +0x48

    // Flags or state (all zero)
    this->field_0x50 = 0;                                      // +0x50
    this->field_0x54 = 0;                                      // +0x54
    this->field_0x58 = 0;                                      // +0x58
    this->field_0x68 = 0;                                      // +0x68
    this->field_0x64 = 0;                                      // +0x64
    this->field_0x60 = 0;                                      // +0x60
    this->field_0x5C = 0;                                      // +0x5C
    this->field_0x6C = 0;                                      // +0x6C
    this->field_0x70 = 0;                                      // +0x70
    this->field_0x8C = 0;                                      // +0x8C
    this->field_0x88 = 0;                                      // +0x88
    this->field_0x84 = 0;                                      // +0x84
    this->field_0x80 = 0;                                      // +0x80
    this->field_0x7C = 0;                                      // +0x7C
    this->field_0x74 = 0xFFFFFFFF;                             // +0x74 (sentry value -1)
    this->field_0x78 = 0xFFFFFFFF;                             // +0x78 (sentry value -1)
    this->field_0x90 = 0;                                      // +0x90
    this->field_0x94 = 0;                                      // +0x94
    this->field_0x98 = 0xFFFFFFFF;                             // +0x98
    this->field_0x9C = 0xFFFFFFFF;                             // +0x9C
    this->field_0xA0 = 0;                                      // +0xA0
    this->field_0xB0 = 0;                                      // +0xB0
    this->field_0xAC = 0;                                      // +0xAC
    this->field_0xA8 = 0;                                      // +0xA8
    this->field_0xA4 = 0;                                      // +0xA4
    this->field_0xB4 = 0;                                      // +0xB4
    this->field_0xB8 = 0;                                      // +0xB8
    this->field_0xBC = 0xFFFFFFFF;                             // +0xBC
    this->field_0xC0 = 0xFFFFFFFF;                             // +0xC0
    this->field_0xC4 = 0;                                      // +0xC4
    this->field_0xD4 = 0;                                      // +0xD4
    this->field_0xD0 = 0;                                      // +0xD0
    this->field_0xCC = 0;                                      // +0xCC
    this->field_0xC8 = 0;                                      // +0xC8
    this->field_0xD8 = 0;                                      // +0xD8
    this->field_0xDC = 0;                                      // +0xDC
    this->field_0xE0 = 0xFFFFFFFF;                             // +0xE0
    this->field_0xE4 = 0xFFFFFFFF;                             // +0xE4
    this->field_0xE8 = 0xFFFFFFFF;                             // +0xE8
    this->field_0xEC = 0xFFFFFFFF;                             // +0xEC
    this->field_0xF0 = 0;                                      // +0xF0
    this->field_0xF4 = 0;                                      // +0xF4
    this->field_0xF8 = 0;                                      // +0xF8
    this->field_0xFC = 0;                                      // +0xFC
    this->field_0x10C = 0;                                     // +0x10C
    this->field_0x108 = 0;                                     // +0x108
    this->field_0x104 = 0;                                     // +0x104
    this->field_0x100 = 0;                                     // +0x100
    this->field_0x110 = 0;                                     // +0x110
    this->field_0x114 = 0;                                     // +0x114
    this->field_0x118 = 0xFFFFFFFF;                            // +0x118
    this->field_0x11C = 0xFFFFFFFF;                            // +0x11C
    this->field_0x120 = 0xFFFFFFFF;                            // +0x120
    this->field_0x124 = 0xFFFFFFFF;                            // +0x124
    this->field_0x128 = 0;                                     // +0x128
    this->field_0x12C = 0;                                     // +0x12C
    this->field_0x130 = 0;                                     // +0x130
    this->field_0x134 = 0;                                     // +0x134
    this->field_0x144 = 0;                                     // +0x144
    this->field_0x140 = 0;                                     // +0x140
    this->field_0x13C = 0;                                     // +0x13C
    this->field_0x138 = 0;                                     // +0x138
    this->field_0x148 = 0;                                     // +0x148
    this->field_0x14C = 0;                                     // +0x14C
    this->field_0x150 = 0xFFFFFFFF;                            // +0x150
    this->field_0x154 = 0xFFFFFFFF;                            // +0x154
    this->field_0x158 = 0xFFFFFFFF;                            // +0x158
    this->field_0x15C = 0xFFFFFFFF;                            // +0x15C
    this->field_0x160 = 0;                                     // +0x160
    this->field_0x164 = 0;                                     // +0x164
    this->field_0x168 = 0;                                     // +0x168
    this->field_0x16C = 0;                                     // +0x16C
    this->field_0x170 = 0;                                     // +0x170
    this->field_0x174 = 0;                                     // +0x174
    *(uint16_t*)((uint8_t*)this + 0x178) = 0;                  // +0x178 (2 bytes)
    *(uint16_t*)((uint8_t*)this + 0x17A) = 0;                  // +0x17A (2 bytes)
    this->field_0x17C = 0;                                     // +0x17C
    this->field_0x180 = 0;                                     // +0x180
    *(uint8_t*)((uint8_t*)this + 0x184) = 0;                   // +0x184 (1 byte)
    this->field_0x188 = 0;                                     // +0x188
    return this;
}