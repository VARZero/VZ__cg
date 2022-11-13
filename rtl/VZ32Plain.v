module vz32_decoder(ir, micro_op, rn, r1, r2, imm);
    input [31:0] ir;
    output [4:0] micro_op; // [4:0] - Micro OP / [?:5] - Func
    output [4:0] rn;
    output [4:0] r1;
    output [4:0] r2;
    output [24:0] imm;

    
endmodule

module regfile_32x32(clk, rst, regt, indata, outdata);

endmodule

module regfile_16x64(clk, rst, regt, indata, outdata);

endmodule

module alu(ImicroOp, r1V, r2V, result);

endmodule

module fp(FmicroOp, r1V, r2V, result);

endmodule

module mem();

endmodule

module branch();

endmodule

module vz32_plain();

endmodule