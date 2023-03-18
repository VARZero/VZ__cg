#include "vz32-opcodes.h"
#include <stdio.h>
#include <string.h>

bool command_syntax(char* line, char* outputBin, char* error){
    // Opcode 확인 및 추가
        char op[30] = strtok(line, " ,");
        vz32_opcode* nowOp;
        error[0] = "P";
        for(short OpIdx = 0; OpIdx < vz32_opcode_count; OpIdx++){
            if (strcmp(op, vz32_list_opcodes[OpIdx]) == 0){
                nowOp = &vz32_list_opcodes[OpIdx];
                outputBin = vz32_list_opcodes[OpIdx].B_opc & 0b11111 
                    + vz32_list_opcodes[OpIdx].B_func & 0b11;
                error[0] = "C"; break;
            }
        }
        if (error[0] == "P"){
            error = strcat(op, " is not vz32 opcode.");
            return 0;
        }

    // Opcode에 맞는 타입인가?
        for(short RegCnt = 0; RegCnt <= ) // 작성중

    return 1;
}

int main(int argc, char* argv){
    open();
}