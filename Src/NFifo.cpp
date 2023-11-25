//==============================================================================
#include "NFifo.h"

//-----------------------------------
#define __NFIFO_BUFFER_FIRST 	((uint32_t)  0)
#define __NFIFO_LINE_SIZE 	 	((uint32_t)  65)
#define __NFIFO_LINES_NUMBER 	((uint32_t)  10)
#define __NFIFO_LINE_LENGTH_MAX	((uint32_t)	255)
#define __NFIFO_LINE_NUMBER_MAX ((uint32_t)  20)

//------------------------------------------------------------------------------
void NFifo::AllocateMemory(uint32_t length, uint32_t depth){

    if((length < 2L)||(depth < 2L)) return;
    line_size = length; lines = depth;
    if((length == 0L)||(length > __NFIFO_LINE_LENGTH_MAX)) line_size = __NFIFO_LINE_SIZE;
	if((depth < 2L) || (depth > __NFIFO_LINE_NUMBER_MAX)) lines = __NFIFO_LINES_NUMBER;

    line_size = line_size + sizeof(uint32_t);

	data = new unsigned char[line_size * lines];

    for(uint32_t y = 0L; y < lines; y++){
        for(uint32_t x = 0L; x < line_size; x++){
			*(data + (y*line_size + x)) = 0L;
		}
	}
}

//------------------------------------------------------------------------------
NFifo::NFifo(void){
    Flush(); data = (uint8_t*)0;

	AllocateMemory(__NFIFO_LINE_SIZE, __NFIFO_LINES_NUMBER);

    LockOnOverflow = false;
}

//------------------------------------------------------------------------------
NFifo::NFifo(uint32_t LineSize, uint32_t Lines){
	Flush(); data = (uint8_t*)0;

	AllocateMemory(LineSize, Lines);

    LockOnOverflow = false;
}

//------------------------------------------------------------------------------
NFifo::~NFifo(void){
    Flush(); delete data;
}

//------------------------------------------------------------------------------
void NFifo::GetControl(PARAMS* fifo_struct){
    *fifo_struct = params;
    return;
}

//------------------------------------------------------------------------------
bool NFifo::Put(uint8_t* ext_buffer_addr, uint32_t ext_buffer_len){
    bool result = false;
    uint8_t size[4]; *(int32_t*)size = ext_buffer_len;

    if(ext_buffer_len > (line_size-4)){ return(result);}

    if(!LockOnOverflow || (params.counter < lines)){

        if((params.counter>0)&&(params.head == params.tail)){
            if(++params.tail >= lines){ params.tail = __NFIFO_BUFFER_FIRST;}
        }

        uint32_t next_line = params.head * line_size;
        for(uint32_t i = 0; i < 4; i++){ data[next_line + i] = size[i];}
        uint32_t current_line_size = ext_buffer_len + 4;
        for(uint32_t i = 4, j=0; i < current_line_size; i++, j++){ data[next_line + i] = ext_buffer_addr[j];}

        if(++params.head >= lines){ params.head = __NFIFO_BUFFER_FIRST;}

        if(++params.counter > lines){
            params.counter = lines;  flags.overflow = 1;
        }
        result = true;
    }
    return(result);
}

//------------------------------------------------------------------------------
uint32_t NFifo::Get(uint8_t* ext_buffer_addr){
    uint8_t size[4];
    uint32_t result = 0;

    if(params.counter == 0) return(0);

    uint32_t next_line = params.tail * line_size;
    for(uint32_t i = 0; i < 4; i++){ size[i] = data[next_line + i];}

    result = *(uint32_t*)size;
    uint32_t current_line_size = result + 4;
    if(current_line_size <= line_size){
    	for(uint32_t i = 4, j=0; i < current_line_size; i++, j++){ ext_buffer_addr[j] = data[next_line + i];}
    } else { result = 0;}

	if(++params.tail >= lines){ params.tail = __NFIFO_BUFFER_FIRST;}

   	if(params.tail == params.head){ params.counter = 0;}
    else { params.counter--;}

    if(params.counter == 0){ flags.overflow = 0;}

    return(result);
}

//------------------------------------------------------------------------------
void NFifo::Flush(){
    params.head = 0; params.tail = params.counter = 0L;
    *(uint32_t*)&flags = 0;
}

//------------------------------------------------------------------------------
void NFifo::ClearOverflow(){
	flags.overflow = 0;
}

//------------------------------------------------------------------------------
uint32_t NFifo::Counter(){
    return(params.counter);
}

//------------------------------------------------------------------------------
uint32_t NFifo::GetSize(){
	uint32_t* pt_depth;

	pt_depth = (uint32_t*)(data + (params.tail * line_size));
	return(*pt_depth);
}

//==============================================================================
