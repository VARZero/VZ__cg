#ifndef __VZ32_OPCODE__
#define __VZ32_OPCODE__

#define OPC_ALU 0x0
#define OPC_MUL 0x2
#define OPC_LOGIC 0x4
    #define OPC_IMM 0x1

#define OPC_MEM 0x6
    #define OPC_MEM_ST 0x1

#define OPC_BRANCH 0x8
    #define OPC_BR_REG 0x1
    #define OPC_BR_INT 0x2
    #define OPC_BR_FP_S 0x4
    #define OPC_BR_FP_D 0x6
        #define OPC_BR_EQ 0x0
        #define OPC_BR_CD 0x1

#define OPC_FP_S 0x10
#define OPC_FP_D 0x11
    #define OPC_FALU 0x0
    #define OPC_FMUL 0x2
    #define OPC_FSQRT 0x4
#define OPC_I2F 0x16
#define OPC_F2I 0x17

#define OPC_SYSTEM 0x18

struct vz32_opcode{
    const char* name;
    const char type;
    const char B_opc;
    const char B_func;
};

enum optype{
    R = 1,
    I, M = 2,
    BR,
    B
}OpType;

const struct vz32_opcode vz32_list_opcodes[] = {
    {"ADD", R, OPC_ALU, 0},
    {"SUB", R, OPC_ALU, 1},
    {"ADD-IMM", I, OPC_ALU | OPC_IMM, 0},
    {"SUB-IMM", I, OPC_ALU | OPC_IMM, 1},

    {"MUL", R, OPC_MUL, 0},
    {"DIV", R, OPC_MUL, 1},
    {"MUL-IMM", I, OPC_MUL | OPC_IMM, 0},
    {"DIV-IMM", I, OPC_MUL | OPC_IMM, 1},
    {"SHIFT-L", I, OPC_MUL | OPC_IMM, 2},
    {"SHIFT-R", I, OPC_MUL | OPC_IMM, 3},

    {"AND", R, OPC_LOGIC, 0},
    {"OR", R, OPC_LOGIC, 1},
    {"XOR", R, OPC_LOGIC, 2},
    {"NOT", R, OPC_LOGIC, 3},
    {"AND-IMM", I, OPC_LOGIC | OPC_IMM, 0},
    {"OR-IMM", I, OPC_LOGIC | OPC_IMM, 1},
    {"XOR-IMM", I, OPC_LOGIC | OPC_IMM, 2},
    {"NOT-IMM", I, OPC_LOGIC | OPC_IMM, 3},

    {"LOAD-INT-SIGNED", M, OPC_MEM, 0},
    {"LOAD-INT-UNSIGNED", M, OPC_MEM, 1},
    {"LOAD-FP", M, OPC_MEM, 2},
    {"POP", M, OPC_MEM, 3}, 
    {"STORE-INT-SIGNED", M, OPC_MEM | OPC_MEM_ST, 0},
    {"STORE-INT-UNSIGNED", M, OPC_MEM | OPC_MEM_ST, 1},
    {"STORE-FP", M, OPC_MEM | OPC_MEM_ST, 2},
    {"PUSH", M, OPC_MEM | OPC_MEM_ST, 3},

    {"BRANCH-DIRECT", B, OPC_BRANCH, 0},
    {"BRANCH-SUBROUTINE", B, OPC_BRANCH, 1},
    {"RETURN", B, OPC_BRANCH, 2},
    {"BRANCH-DIRECT", I, OPC_BRANCH | OPC_BR_REG, 0},
    {"BRANCH-SUBROUTINE", I, OPC_BRANCH | OPC_BR_REG, 1},
    {"BRANCH-INT-EQUAL", R, OPC_BRANCH | OPC_BR_INT | OPC_BR_EQ, 0},
    {"BRANCH-INT-NOTEQUAL", R, OPC_BRANCH | OPC_BR_INT | OPC_BR_EQ, 1},
    {"BRANCH-INT-LEFTEQCD", R, OPC_BRANCH | OPC_BR_INT | OPC_BR_CD, 0},
    {"BRANCH-INT-LEFTCD", R, OPC_BRANCH | OPC_BR_INT | OPC_BR_CD, 1},
    {"BRANCH-INT-RIGHTEQCD", R, OPC_BRANCH | OPC_BR_INT | OPC_BR_CD, 2},
    {"BRANCH-INT-RIGHTCD", R, OPC_BRANCH | OPC_BR_INT | OPC_BR_CD, 3}, 
    {"BRANCH-FP-S-EQUAL", R, OPC_BRANCH | OPC_BR_FP_S | OPC_BR_EQ, 0},
    {"BRANCH-FP-S-NOTEQUAL", R, OPC_BRANCH | OPC_BR_FP_S | OPC_BR_EQ, 1},
    {"BRANCH-FP-S-LEFTEQCD", R, OPC_BRANCH | OPC_BR_FP_S | OPC_BR_CD, 0},
    {"BRANCH-FP-S-LEFTCD", R, OPC_BRANCH | OPC_BR_FP_S | OPC_BR_CD, 1},
    {"BRANCH-FP-S-RIGHTEQCD", R, OPC_BRANCH | OPC_BR_FP_S | OPC_BR_CD, 2},
    {"BRANCH-FP-S-RIGHTCD", R, OPC_BRANCH | OPC_BR_FP_S | OPC_BR_CD, 3},
    {"BRANCH-FP-D-EQUAL", R, OPC_BRANCH | OPC_BR_FP_D | OPC_BR_EQ, 0},
    {"BRANCH-FP-D-NOTEQUAL", R, OPC_BRANCH | OPC_BR_FP_D | OPC_BR_EQ, 1},
    {"BRANCH-FP-D-LEFTEQCD", R, OPC_BRANCH | OPC_BR_FP_D | OPC_BR_CD, 0},
    {"BRANCH-FP-D-LEFTCD", R, OPC_BRANCH | OPC_BR_FP_D | OPC_BR_CD, 1},
    {"BRANCH-FP-D-RIGHTEQCD", R, OPC_BRANCH | OPC_BR_FP_D | OPC_BR_CD, 2},
    {"BRANCH-FP-D-RIGHTCD", R, OPC_BRANCH | OPC_BR_FP_D | OPC_BR_CD, 3},
     
    {"FP-S-ADD", R, OPC_FP_S | OPC_FALU, 0},
    {"FP-S-SUB", R, OPC_FP_S | OPC_FALU, 1},
    {"FP-D-ADD", R, OPC_FP_D | OPC_FALU, 0},
    {"FP-D-SUB", R, OPC_FP_D | OPC_FALU, 1},
    {"FP-S-MUL", R, OPC_FP_S | OPC_FMUL, 0},
    {"FP-S-DIV", R, OPC_FP_S | OPC_FMUL, 1},
    {"FP-D-MUL", R, OPC_FP_D | OPC_FMUL, 0},
    {"FP-D-DIV", R, OPC_FP_D | OPC_FMUL, 1},
    {"FP-S-SQRT", BR, OPC_FP_S | OPC_FSQRT, 0},
    {"FP-D-SQRT", BR, OPC_FP_D | OPC_FSQRT, 1}, 
    {"INT2FP-S", M, OPC_I2F, 0},
    {"INT2FP-D", M, OPC_I2F, 1},
    {"FP2INT-S", M, OPC_F2I, 0},
    {"FP2INT-D", M, OPC_F2I, 1},

    {"NOP", B, OPC_SYSTEM | 0x3, 0},
    {"MMU-SET", B, OPC_SYSTEM | 0x4, 0},
    {"INTERRUPT-TYPE", BR, OPC_SYSTEM | 0x5, 0},
    {"SET-TYPE", B, OPC_SYSTEM | 0x6, 0},
    {"SYSTEM-CALL", B, OPC_SYSTEM | 0x7, 0}
};



#endif