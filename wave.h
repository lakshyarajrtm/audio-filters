#ifndef WAVE_H
#define WAVE_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>



typedef struct HeadChunk{
    unsigned int FormatBlocID;
    unsigned int BlockSize;
    unsigned int AudioFormat;
    unsigned short Channels;
    unsigned int Frequency;
    unsigned int BytePerSec;
    unsigned short BytePerBloc;
    unsigned short BitsPerSample;

} HeadChunk;

typedef struct DataChunk{
    unsigned int DataBlocID;
    unsigned int DataSize;
}DataChunk;



HeadChunk readWaveHead(uint8_t* data, int size){
    HeadChunk chunk = {};
    unsigned int *p = NULL;

    while(true){
        if(p == NULL){
            
        }
        
    }
}



#endif 

