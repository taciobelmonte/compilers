#ifndef CODEGEN_H
#define CODEGEN_H

/* pefixes */

const char def_funcion_prefix[] = "_f_";
const char global_system_prefix[] = "_";
const char global_var_prefix[] = "__";

/* codegen templates */

const char mips_head[] =
".data\n\n"
".text\n\n";

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

const char call_main[] =
"\nmain:\n"
    "\tsw $fp, 0($sp)\n"
    "\taddiu $sp, $sp, -4\n"
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

const char cgen_and[] =
"\tand $a0, $t1, $a0\n";

const char cgen_or[] =
"\tor $a0, $t1, $a0\n";

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

const char codegen_decfunc[] =
"%s%s:\n"
    "\tmove $fp, $sp\n"
    "\tsw $ra, 0($sp)\n"
    "\taddiu $sp, $sp, -4\n";

const char codegen_decfunc_sufix[] =
    "\tlw $ra, 4($sp)\n"
    "\taddiu $sp, $sp, 8\n"
    "\tlw $fp 0($sp)\n"
    "\tj $ra\n";

const char codegen_funccall[] =
    "\tsw $fp, 0($sp)\n"
    "\taddiu $sp, $sp, -4\n";

const char codegen_funccall_sufix[] =
    "\tjal _f_%s\n";

#endif
