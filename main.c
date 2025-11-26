#include "MKL05Z4.h"
#include "InitPWM.c"
#include "InitUART.c"

struct r_engine{
    in1 = 0;
    in2 = 0;
    en = 0;  
};
    
struct l_engine{
    in3 = 0;
    in4 = 0;
    en = 0;  
};

void forward(){
    r_engine.in1 = 1;
    r_engine.in2 = 0;
    l_engine.in3 = 1;
    l_engine.in4 = 0;

    r_engine.en = 1;
    l_engine.en = 1;
}

void backward(){
    r_engine.in1 = 0;
    r_engine.in2 = 1;
    l_engine.in3 = 0;
    l_engine.in4 = 1;

    r_engine.en = 1;
    l_engine.en = 1;
}

void stop(){
    r_engine.in1 = 0;
    r_engine.in2 = 0;
    l_engine.in3 = 0;
    l_engine.in4 = 0;

    r_engine.en = 0;
    l_engine.en = 0;
}

int main(){
    InitPWM();
    InitUART();
    //InitDrive(); in progress
    
    return 0;
}