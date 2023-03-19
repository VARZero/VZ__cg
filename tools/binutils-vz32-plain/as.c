#include "vz32-opcodes.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

char get_Register_out_Bin(char* RegName, char* error){
    // 레지스터 이름을 바이너리로 변환해서 반환
        for(short regc = 0; regc < 32; regc++){
            if (strcmp(RegName, vz32_name_normal_opcode[regc]) == 0){return regc;}
            if (strcmp(RegName, vz32_name_functional_opcode[regc]) == 0){return regc;}
        }
        error = "Invalid Regster name.";
        return 0xFF;
}

bool command_syntax(char* line, uint32_t* outputBin, char* error){
    // Opcode 확인 및 추가
        char op[30];
        strcpy(op, strtok(line, " "));
         
        const struct vz32_opcode* nowOp;
        error[0] = 'P';
        for(short OpIdx = 0; OpIdx < vz32_opcode_count; OpIdx++){
            if (strcmp(op, vz32_list_opcodes[OpIdx].name) == 0){
                nowOp = &vz32_list_opcodes[OpIdx];
                *outputBin = vz32_list_opcodes[OpIdx].B_opc & 0b11111 
                    | ((vz32_list_opcodes[OpIdx].B_func & 0b11) << 5);
                error[0] = 'C'; break;
            }
        }
        if (error[0] == 'P'){
            error = strcat(op, " is not vz32 opcode.\0");
            return 0;
        }

    // Opcode에 맞는 타입인가?
        char Rn[3][10];
        char IMM[50];
        for(short RegCnt = 0; RegCnt < nowOp->type; RegCnt++){
            strcpy(Rn[RegCnt], strtok(NULL, " ,"));
            if (Rn[RegCnt] == NULL){
                error = "Lack Argument.\0";
                return 0;
            }
            *outputBin = *outputBin | (get_Register_out_Bin(Rn[RegCnt], error) << ( 7 + RegCnt*5 ));
            if (error[0] == 'I'){return 0;}
        }
        strcpy(IMM, strtok(NULL, " ,"));
        *outputBin = *outputBin | ( atoi(IMM) << ( 7 + nowOp->type*5 ));

        error = " ";
        if (strtok(NULL, " ,") != NULL){
            // 추가적으로 입력된 레지스터가 있어서 경고
            error = "Too many argument.\0";
        }
    
    return 1;
}

int main(/*int argc, char* argv*/){
    //open();
    char line[2][50] = {"ADD-IMM tm1, tm2, 3", "SUB i0, i2, i14"};
    uint32_t outBin[2] = {0, 0};
    char error[50];
    for (char i = 0; i < 2; i++){
        if (command_syntax(line[i], &outBin[i], error) != 1){
            printf("%s\n", error);
        }
    }
    for (char i = 0; i < 2; i++){
        printf("%s %X\n", line[2], outBin[2]);
    }
    return 0;
}