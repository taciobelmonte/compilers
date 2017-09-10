#ifndef CODEGEN_H
#define CODEGEN_H

/* pefixes */

const char def_funcion_prefix[] = "_f_";
const char global_system_prefix[] = "_";
const char global_var_prefix[] = "__";

/* codegen templates */

const char codegen_variable[] =
"\tvar_%s: .word 0\n";

const char mips_datas[] =
".data\n";

const char mips_head[] =
"\n.text\n\n";

const char deff_print[] =
"_f_print:\n"
    "\tlw $a0, 4($sp)\n"
    "\tli $v0, 1\n"
    "\tsyscall\n"
    "\tli $v0, 11\n"
    "\tli $a0, 0x0a\n"
    "\tsyscall\n"
    "\taddiu $sp, $sp, 4\n"
    "\tlw $fp, 4($sp)\n"
    "\taddiu $sp, $sp, 4\n"
    "\tj $ra\n\n";

const char call_main1[] =
"\nmain:\n";

const char call_main2[] =
    "\tsw $fp, 0($sp)\n"
    "\taddiu $sp, $sp, -4\n"
    "\tjal _f_main\n"
    "\tli $v0, 10\n"
    "\tsyscall\n";

const char push_ra[] =
"\tsw $ra, 0($sp)\n"
"\taddiu $sp, $sp, -4\n";

const char push_fp[] =
"\tsw $fp, 0($sp)\n"
"\taddiu $sp, $sp, -4\n";

const char push_a0[] =
"\tsw $a0, 0($sp)\n"
"\taddiu $sp, $sp, -4\n";

const char push_t1[] =
"\tsw $t1, 0($sp)\n"
"\taddiu $sp, $sp, -4\n";

const char top_a0[] =
"\tlw $a0, 4($sp)\n";

const char top_fp[] =
"\tlw $fp, 4($sp)\n";

const char top_ra[] =
"\tlw $ra, 4($sp)\n";

const char top_t1[] =
"\tlw $t1, 4($sp)\n";

const char pop[] =
"\taddiu $sp, $sp, 4\n";

const char load_int[] =
"\tli $a0, %d\n";

//ao chamar x tem que passar um inteiro referente a sua posição na pilha
const char load_x[] =
"\tlw $a0, %d($fp)          #load x\n";

const char save_x[] =
"\tsw $a0, %d($fp)          #save x\n";

//ao chamar var tem que passar uma string com seu nome
const char load_var[] =
"\tlw $a0, var_%s           #load var\n";

const char save_var[] =
"\tsw $a0, var_%s           #save var\n";

//onde %d deve ser passado como argumento, em função de quantos paramentro vieram na definicao
//"\taddiu $sp, $sp, 8+4*%d\n";
const char pop_paramlis[] =
"\taddiu $sp, $sp, 8+%d\n";

/* unop exp */

//TODO ver se tem forma melhor que com is-less-then-imediate-unsigned
const char cgen_not[] =
"\tsltiu $a0, $a0, 1\n";

const char cgen_unminus[] =
"\tnegu $a0, $a0\n";

/* binop exp */
const char cgen_add[] =
"\tadd $a0, $t1, $a0\n";

const char cgen_sub[] =
"\tsub $a0, $t1, $a0\n";

const char cgen_mul[] =
"\tmul $a0, $t1, $a0\n";

const char cgen_div[] =
"\tdiv $a0, $t1, $a0\n";

//if some operand is zero, return zero
const char cgen_and[] =
"\tsne $a0, $a0, $0\n"
"\tsne $t1, $t1, $0\n"
"\tand $a0, $t1, $a0\n";

const char cgen_or[] =
"\tor $a0, $t1, $a0\n"
"\tsne $a0, $a0, $0\n";

const char cgen_sgt[] =
"\tsgt $a0, $t1, $a0\n";

const char cgen_slt[] =
"\tslt $a0, $t1, $a0\n";

const char cgen_seq[] =
"\tseq $a0, $t1, $a0\n";

const char cgen_sneq[] =
"\tsne $a0, $t1, $a0\n";

const char cgen_sge[] =
"\tsge $a0, $t1, $a0\n";

const char cgen_sle[] =
"\tsle $a0, $t1, $a0\n";

/* codegens flexiveis */

/* codegen decfunc */
const char codegen_decfunc[] =
"_f_%s:\n"
    "\tmove $fp, $sp\n"
    "\tsw $ra, 0($sp)\n"
    "\taddiu $sp, $sp, -4\n";

//min of jumps on pop is 8 (fp and ra)
const char codegen_decfunc_sufix[] =
"end_function_%s:\n"
    "\tlw $ra, 4($sp)\n"
    "\taddiu $sp, $sp, %d\n"
    "\tlw $fp 0($sp)\n"
    "\tj $ra\n";

const char codegen_return_token[] =
"\tb end_function_%s\n";

/* codegen funccall */
const char codegen_funccall[] =
    "\tsw $fp, 0($sp)           #comeca empilhar fp pra comecar uma call\n"
    "\taddiu $sp, $sp, -4\n";

const char codegen_funccall_sufix[] =
    "\tjal _f_%s\n";

/* codegen from ifs statments */

const char codegen_if_comp[] =
"\tbnez $a0, true_branch_%d\n";

const char codegen_false_branch[] =
"false_branch_%d:\n";

const char codegen_b_endif[] =
"\tb end_if_%d\n";

const char codegen_true_branch[] =
"true_branch_%d:\n"
    "\tbeqz $a0, end_if_%d\n";

const char codegen_endif[] =
"end_if_%d:\n";

#endif
