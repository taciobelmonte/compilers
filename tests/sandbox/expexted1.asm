.data

.text

_f_print:
    lw $a0, 4($sp)
    li $v0, 1
    syscall
    li $v0, 11
    li $a0, 0x0a
    syscall
    #addiu $sp, $sp, 4 + 4*1#
    addiu $sp, $sp, 4+4
    lw $fp, 0($sp)
    j $ra

_f_main:
    move $fp, $sp
    sw $ra, 0($sp)
    addiu $sp, $sp, -4
    # -- #
    sw $fp, 0($sp)
    addiu $sp, $sp, -4
    # -- #
    li $a0, 4
    sw $a0, 0($sp)
    addiu $sp, $sp, -4
    li $a0, 5
    lw $t1, 4($sp)
    addiu $sp, $sp, 4
    add $a0, $t1, $a0
    # -- #
    sw $a0, 0($sp)
    addiu $sp, $sp, -4
    # -- #
    jal _f_print
    # -- #
    lw $ra, 4($sp)
    #addiu $sp, $sp, 2*4+4*0#
    addiu $sp, $sp, 8
    lw $fp 0($sp)
    j $ra

main:
    sw $fp, 0($sp)
    addiu $sp, $sp, -4
    jal _f_main
    li $v0, 10
    syscall
