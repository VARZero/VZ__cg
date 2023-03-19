#include "vz32-opcodes.h"
#include <stdio.h>
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

bool command_syntax(char* line, char* outputBin, char* error){
    // Opcode 확인 및 추가
        char op[30] = strtok(line, " ");
        vz32_opcode* nowOp;
        error[0] = "P";
        for(short OpIdx = 0; OpIdx < vz32_opcode_count; OpIdx++){
            if (strcmp(op, vz32_list_opcodes[OpIdx]) == 0){
                nowOp = &vz32_list_opcodes[OpIdx];
                outputBin = vz32_list_opcodes[OpIdx].B_opc & 0b11111 
                    | ((vz32_list_opcodes[OpIdx].B_func & 0b11) << 5);
                error[0] = "C"; break;
            }
        }
        if (error[0] == "P"){
            error = strcat(op, " is not vz32 opcode.\0");
            return 0;
        }

    // Opcode에 맞는 타입인가?
        char Rn[3][10];
        for(short RegCnt = 0; RegCnt < nowOp.type; RegCnt++){
            Rn[RegCnt] = strtok(NULL, " ,");
            if (Rn[RegCnt] == NULL){
                error = "Lack Argument.\0";
                return 0;
            }
            outputBin = outputBin | (get_Register_out_Bin(Rn[RegCnt], error) << ( 7 + RegCnt*5 ));
            if (error[0] == "I"){return 0;}
        }
        char IMM[50] = strtok(NULL, " ,");

        error = " ";
        if (strtok(NULL, " ,") != NULL){
            // 추가적으로 입력된 레지스터가 있어서 경고
            error = "Too many argument.\0";
        }
    
    return 1;
}

int main(int argc, char* argv){
    open();
}