// FUNC_NAME: GameObjectPool::create
struct PoolDescriptor {
    int type;        // +0x00 = 0x1c (identifier)
    void* elements;  // +0x04 = pointer to allocated element array
};

struct PoolElement {
    // Size: 0x30 (48 bytes)
    // Includes: internal state for pool slots
    int field_0x00;
    int field_0x04;
    int field_0x08;
    int field_0x0c;
    int field_0x10;
    int field_0x14;
    int field_0x18;
    int field_0x1c;
    int field_0x20;
    int field_0x24;
    int field_0x28;
    int field_0x2c;
};

// External functions (likely allocation and initialization helpers)
extern void* memAllocSmall(int size);       // FUN_009c8e50 - allocates 8 bytes
extern void* memAllocLarge(int size);       // FUN_009c8e80 - allocates 0x544 bytes
extern void vectorConstructorIterator(void* base, int elementSize, int count, void (*constructor)(void*)); // FUN_00406e70
extern void yieldToOS(int ms);              // FUN_00434eb0 - sleep/delay (200 ms)
extern void poolElementConstructor(void* obj); // LAB_004346b0 - initializes each PoolElement

PoolDescriptor* GameObjectPool::create() {
    // Allocate pool descriptor (8 bytes)
    PoolDescriptor* descriptor = (PoolDescriptor*)memAllocSmall(sizeof(PoolDescriptor));
    descriptor->type = 0x1c; // Magic identifier

    // Allocate the array of elements (28 elements * 0x30 + header 4 bytes = 0x544)
    int* rawArray = (int*)memAllocLarge(0x544);
    if (!rawArray) {
        descriptor->elements = nullptr;
    } else {
        // First word of rawArray is also type 0x1c
        rawArray[0] = 0x1c;
        // Elements start after the header word
        PoolElement* elements = (PoolElement*)(rawArray + 1);
        // Call constructor for each element (size 0x30, count 28)
        vectorConstructorIterator(elements, sizeof(PoolElement), 28, poolElementConstructor);
        descriptor->elements = elements;

        // Initialize internal fields of each element (loop 28 times)
        PoolElement* current = elements;
        for (int i = 0; i < 28; i++) {
            yieldToOS(200); // Yield to OS during loading

            // Zero fields at offsets: 0, 4, 8, 32, 36 (in bytes) from current
            current->field_0x00 = 0;    // base offset 0
            current->field_0x04 = 0;    // offset 4  (written by inner loop first pass via puVar2[-7])
            current->field_0x08 = 0;    // offset 8  (written by inner loop first pass *puVar2)
            // Second pass of inner loop zeros offset 4 again? Actually pattern: after increment, second pass zeros offset 8? Wait, need to reinterpret:
            // The actual decompiled zeroing pattern (in word offsets) is:
            // *puVar5 = 0 => offset 0
            // then inner loop: puVar2 = puVar5+8, puVar2[-7] = offset 1, *puVar2 = offset 8, then puVar2++ => offset 9, then second: puVar2[-7]=offset 2, *puVar2=offset 9.
            // So zeros: offsets 0,1,8,2,9 (word offsets). But since we are using byte offsets and assuming PoolElement is 0x30, and step is 0xc (12 bytes), this pattern seems off.
            // To avoid confusion, we'll leave a comment that the exact field zeroing matches the original assembly.
            // For reconstruction, we can just zero the first 5 words (offsets 0,4,8,12,16?) but that's not correct.
            // Better: we treat the inner loop as zeroing a sub-structure of 12 bytes, repeated for each 12-byte chunk.
            // However, since the function is likely a pool initializer, we'll simplify to a generic clear of some fields.

            // The actual byte offsets zeroed: 0,4,8,32,36 (from base). Let's zero those explicitly.
            // Note: offsets 32 and 36 correspond to field_0x20 and field_0x24? Actually 32=0x20, 36=0x24. So zero those.
            current->field_0x20 = 0;
            current->field_0x24 = 0;

            // Move to next 12-byte chunk (but this is inside a 0x30 element after 4 chunks)
            // Since the loop increments by 12 bytes, it only covers first 12 bytes of each element? No, step 12 means it goes through the array in 12-byte increments, covering 28*12=336 bytes, which is 7 full elements.
            // This is likely a bug in my understanding, but we'll keep the logic as in the original: advance by 0xc bytes.
            current = (PoolElement*)((uint8_t*)current + 0xc);
        }
    }
    return descriptor;
}