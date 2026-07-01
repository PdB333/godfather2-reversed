// FUNC_NAME: Player::~Player
// Address: 0x00877c50
// Destructor for Player class. Removes from a linked list at offset 0x48 and releases reference at offset 0xbac.

void __fastcall Player::~Player(int this)
{
    // Stack-based vtable pointer (debugging?)
    void** local_18 = &PTR_FUN_00e31e2c; // static function table
    // local_8 = &local_18 (unused)

    // Get pointer to list node at offset 0x48 (likely a linked list node embedded in the object)
    int* listNode = (this != 0) ? (int*)(this + 0x48) : 0;

    // Remove node from linked list (singly linked? The code reads next pointer and sets it to point to local variable)
    int nextPtr = 0;
    if (listNode != 0) {
        nextPtr = *(int*)(listNode + 4); // read next pointer (offset 0x4C from this)
        *(int**)(listNode + 4) = &listNode; // set next pointer to address of local variable (stack)
    }

    // Release reference count at offset 0xbac
    int refCount = *(int*)(this + 0xbac);
    FUN_00408a00(&refCount, 0); // likely decrement reference count and possibly delete

    // Remove from list (second call, takes address of listNode)
    if (listNode != 0) {
        FUN_004daf90(&listNode);
    }
}