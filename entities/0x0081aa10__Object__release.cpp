// FUNC_NAME: Object::release
void __fastcall Object::release( Object* this ) {
    // Offset +4: pointer to owned child object or delegate
    if ( this->field4 != 0 ) {
        // vtable+4: release/delete function for the owned object
        // Called with the owned object as first arg and 0 as second
        ( *(void (__fastcall*)(void*, int) ) ( (*((int**)this)[0][1] ) )( this->field4, 0 );
        this->field4 = 0;
    }
    // vtable+12: final cleanup (e.g., destructor or shutdown)
    ( *(void (__fastcall*)(void) ) ( (*((int**)this)[0][3] ) ) )();
}