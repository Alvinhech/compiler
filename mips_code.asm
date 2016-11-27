jal main
j _end
Fib :
addiu $sp,$sp,-48
sw  $ra,44($sp)
sw  $s7,40($sp)
move    $s7,$sp
lw  $t0,48($sp)
sw  $t0,4($sp)
lw $t1,4($s7)
li $t2,0
bne $t1,$t2,_lable0
li $t1,1
move $v0,$t1
lw  $ra,44($sp)
lw  $s7,40($sp)
addiu $sp,$sp,48
jr  $ra
_lable0 :
lw $t1,4($s7)
li $t2,1
bne $t1,$t2,_lable1
li $t1,1
move $v0,$t1
lw  $ra,44($sp)
lw  $s7,40($sp)
addiu $sp,$sp,48
jr  $ra
j  _lable2
_lable1 :
lw $t1,4($s7)
li $t2,2
sub $t0,$t1,$t2
sw $t0,12($s7)
lw $t1,12($s7)
sw $t1,0($s7)
jal  Fib
move $t0,$v0
sw $t0,16($s7)
move $sp,$s7
lw $t1,4($s7)
li $t2,1
sub $t0,$t1,$t2
sw $t0,24($s7)
lw $t1,24($s7)
sw $t1,0($s7)
jal  Fib
move $t0,$v0
sw $t0,28($s7)
move $sp,$s7
lw $t1,16($s7)
lw $t2,28($s7)
add $t0,$t1,$t2
sw $t0,32($s7)
lw $t1,32($s7)
move $v0,$t1
lw  $ra,44($sp)
lw  $s7,40($sp)
addiu $sp,$sp,48
jr  $ra
_lable2 :
lw  $ra,44($sp)
lw  $s7,40($sp)
addiu $sp,$sp,48
jr  $ra
main :
addiu $sp,$sp,-24
sw  $ra,20($sp)
sw  $s7,16($sp)
move    $s7,$sp
la $a0,_string0
li $v0,4
syscall
li $a0 10
li $v0 11
syscall
li $v0,5
syscall
move $t0,$v0
sw $t0,4($s7)
lw $t1,4($s7)
sw $t1,0($s7)
jal  Fib
move $t0,$v0
sw $t0,8($s7)
move $sp,$s7
lw $t1,8($s7)
addiu $t0,$t1,0
sw $t0,4($s7)
la $a0,_string1
li $v0,4
syscall
li $a0 10
li $v0 11
syscall
lw $a0,4($s7)
li $v0,1
syscall
li $a0 10
li $v0 11
syscall
lw  $ra,20($sp)
lw  $s7,16($sp)
addiu $sp,$sp,24
jr  $ra
_end:
.data
_string0:  .asciiz  "Input the Fibonacci number you want to know:"
_string1:  .asciiz  "Fib number is:"
