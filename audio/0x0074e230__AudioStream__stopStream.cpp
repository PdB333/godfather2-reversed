// FUNC_NAME: AudioStream::stopStream
void __fastcall AudioStream::stopStream( AudioStream* this ) {
    int* pBufferLink = (int*)(this + 0xA4); // linked list node pointer
    if ( *(int*)(this + 0xA4) == 0 || *(int*)(this + 0xA4) == 0x48 ) {
        int* newBuffer = getStreamBuffer();
        if ( newBuffer == 0 ) {
            newBuffer = 0;
        } else {
            newBuffer = (int*)((char*)newBuffer + 0x48);
        }
        if ( *pBufferLink != newBuffer ) {
            if ( *pBufferLink != 0 ) {
                operator_delete( pBufferLink );
            }
            *pBufferLink = newBuffer;
            if ( newBuffer != 0 ) {
                *(int*)(this + 0xA8) = *(int*)(newBuffer + 4);
                *(int**)((char*)newBuffer + 4) = pBufferLink;
            }
        }
    }
    bool bFadeOut = false;
    if ( ( *(uint32_t*)(this + 0xE4) >> 6 & 1 ) != 0 ) {
        bFadeOut = true;
        if ( *(int*)(this + 0x88) != 0 && *(int*)(this + 0x94) != 0 ) {
            if ( *(int*)(this + 0x8C) != 0 ) {
                operator_delete( (void*)(this + 0x8C) );
                *(int*)(this + 0x8C) = 0;
            }
            stopStream( 0, *(void**)(this + 0x88) );
        }
    }
    if ( *(int*)(this + 0xD8) != 0 ) {
        operator_delete( (void*)(this + 0xD8) );
        *(int*)(this + 0xD8) = 0;
    }
    *(int*)(this + 0xE0) = 0;
    *(uint32_t*)(this + 0xE4) &= 0xFFFFFDFB; // clear bits 2 and 3
    if ( ( *(uint32_t*)(this + 0xE4) >> 1 & 1 ) == 0 ) {
        playStopSound( 0x59 ); // stop music
    } else {
        playStopSound( 0x47 ); // stop speech
        stopAllSounds();
    }
    if ( ( *(uint32_t*)(this + 0xE4) >> 1 & 1 ) != 0 ) {
        if ( isStreamStopped() == 0 ) {
            *(uint32_t*)(this + 0xE4) |= 0x50; // set bits 4 and 6
            return;
        }
    }
    finalizeStop( bFadeOut );
    *(uint32_t*)(this + 0xE4) |= 0x40; // set bit 6
}