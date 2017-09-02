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
"main:\n"
    "\tsw $fp, 0($sp)\n"
    "\taddiu $sp, $sp, -4\n"
    "\tjal _f_main\n"
    "\tli $v0, 10\n"
    "\tsyscall\n";

