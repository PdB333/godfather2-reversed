// FUNC_NAME: Pool::destroy
void __fastcall Pool::destroy(int *pool)
{
    int *current;
    int *next;

    current = (int *)*pool; // head
    while (current != (int *)0x0) {
        next = (int *)current[6]; // +0x18 next
        if (current[4] != 0) { // +0x10 resource pointer
            FUN_004daf90(current + 4); // release resource at offset +0x10
        }
        if (*current != 0) { // +0x00 data pointer
            (*(void (**)(int))current[3])(*current); // call destructor at +0x0c
        }
        // call virtual function at vtable+0x04: deallocate node
        (**(void (__fastcall **)(int, int))(*(int *)pool[4] + 4))(current, 0);
        current = next;
    }
    // handle an extra node?
    if (pool[3] != 0) {
        (**(void (__fastcall **)(int, int))(*(int *)pool[4] + 4))(pool[3], 0);
    }
    // final destruction call at vtable+0x0c
    (**(void (__fastcall **)(void))(*(int *)pool[4] + 12))();
}