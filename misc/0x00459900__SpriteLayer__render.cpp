// FUNC_NAME: SpriteLayer::render
// Address: 0x00459900
// Role: Renders a list of drawable sprites/UI elements with sorting offset calculation
class SpriteLayer {
public:
    struct DrawNode { // size >= 0x30
        DrawNode* next;          // +0x00
        int field_0x04;          // +0x04
        void* object;            // +0x08 - points to a drawable object
        int field_0x0c;          // +0x0c
        int field_0x10;          // +0x10
        int field_0x14;          // +0x14
        int field_0x18;          // +0x18 - (puVar1[6]) first parameter to draw function
        int multiplier;          // +0x1c - (puVar1[7]) 3 or 5 depending on flag
        int calculatedOffset;    // +0x20 - (puVar1[8]) final offset * 4
        int field_0x24;          // +0x24 - (puVar1[9])
        int field_0x28;          // +0x28 - (puVar1[10])
        int field_0x2c;          // +0x2c - (puVar1[0xb])
    };

    struct DrawableObject { // pointed to by object in node
        byte drawType;           // +0x06 - index into function tables
        int flags;               // +0x08 - bit 0x4000 selects table
    };

    struct RenderContext { // pointed to by _context
        void** vtable;           // +0x00
        byte field_0x03;         // +0x03 - flag for 0x3000 parameter
        byte field_0x07;         // +0x07 - rendering state flag
        int screenWidth;         // +0x10 - (puVar1[4]) screen width
        byte field_0x1d;         // +0x1d - one-shot flag
    };

    // +0x00: vtable
    // +0x08: _nodeList
    // +0x10: _context
    DrawNode* _nodeList;    // +0x08
    RenderContext* _context; // +0x10

    void render() {
        DrawNode* node;
        void* object;
        int width;
        int multiplier;
        int baseOffset;
        void (*drawFunc)(int, int, int, int, int, int, int);
        uint flags;

        node = _nodeList;
        if (node == nullptr)
            return;

        // Determine base offset from context
        if (_context->field_0x07 == 0) {
            // Inactive rendering: use context's stored screen width
            _context->field_0x1d = 1;
            baseOffset = _context->screenWidth;
        } else {
            // Active rendering: get screen dimensions from virtual function
            int outWidth = 0;
            int param = 0; // reused local
            // vtable+0x2c: likely getScreenSize(0,0, &width, 0x3000 if field_0x03)
            uint extraFlag = (_context->field_0x03 != 0) ? 0x3000 : 0;
            ((void (*)(void*, int, int, int*, uint))(_context->vtable[0x0b]))( // offset 0x2c = 11*4
                _context, 0, 0, &outWidth, extraFlag);
            baseOffset = outWidth;
        }

        // Iterate through draw node linked list
        node = _nodeList;
        while (node != nullptr) {
            object = node->object;
            flags = *(uint*)((char*)object + 8); // DrawableObject::flags
            if (flags & 0x4000) {
                multiplier = node->multiplier * 3;
            } else {
                multiplier = node->multiplier * 5;
            }
            node->calculatedOffset = baseOffset + multiplier * 4;

            // Select draw function from jump table based on drawType and flag
            byte drawType = *(byte*)((char*)object + 6);
            if (flags & 0x4000) {
                drawFunc = (void (*)(int, int, int, int, int, int, int))PTR_FUN_00e36954[drawType];
            } else {
                drawFunc = (void (*)(int, int, int, int, int, int, int))PTR_FUN_00e36940[drawType];
            }

            // Call draw function with node's parameters
            drawFunc(node->field_0x18,      // param1
                     node->field_0x10,      // param2
                     node->field_0x2c,      // param3
                     node->field_0x14,      // param4
                     node->calculatedOffset,// param5
                     node->field_0x24,      // param6
                     node->field_0x28);     // param7

            node = node->next;
        }

        // Finalize context if rendering was active
        if (_context->field_0x07 != 0) {
            // vtable+0x30: likely endRender()
            ((void (*)(void*))_context->vtable[0x0c])(_context);
        } else {
            _context->field_0x1d = 0;
        }
    }
};

// External jump tables (defined elsewhere)
extern void (*PTR_FUN_00e36940[256])(int, int, int, int, int, int, int);
extern void (*PTR_FUN_00e36954[256])(int, int, int, int, int, int, int);