jal main
j _end
f1 :
addiu $sp,$sp,-28
sw  $ra,24($sp)
sw  $s7,20($sp)
move    $s7,$sp
lw  $t0,28($sp)
sw  $t0,0($sp)
lw  $t0,32($sp)
sw  $t0,4($sp)
li $t1,1
lw $t2,0($s7)
add $t0,$t1,$t2
sw $t0,12($s7)
lw $t1,12($s7)
move $v0,$t1
lw  $ra,24($sp)
lw  $s7,20($sp)
addiu $sp,$sp,28
jr  $ra
lw  $ra,24($sp)
lw  $s7,20($sp)
addiu $sp,$sp,28
jr  $ra
f2 :
addiu $sp,$sp,-48
sw  $ra,44($sp)
sw  $s7,40($sp)
move    $s7,$sp
lw  $t0,48($sp)
sw  $t0,0($sp)
lw  $t0,52($sp)
sw  $t0,4($sp)
li $t1,0
addiu $t0,$t1,0
sw $t0,8($s7)
li $t1,12
neg $t0,$t1
sw $t0,32($s7)
lw $t1,32($s7)
addiu $t0,$t1,0
sw $t0,12($s7)
li $t1,320
addiu $t0,$t1,0
sw $t0,16($s7)
li $t1,45
addiu $t0,$t1,0
sw $t0,0($s7)
li $t1,50
addiu $t0,$t1,0
sw $t0,4($s7)
li $t1,47
addiu $t0,$t1,0
sw $t0,20($s7)
li $t1,95
addiu $t0,$t1,0
sw $t0,24($s7)
li $t1,97
move $v0,$t1
lw  $ra,44($sp)
lw  $s7,40($sp)
addiu $sp,$sp,48
jr  $ra
lw  $ra,44($sp)
lw  $s7,40($sp)
addiu $sp,$sp,48
jr  $ra
recursion :
addiu $sp,$sp,-36
sw  $ra,32($sp)
sw  $s7,28($sp)
move    $s7,$sp
lw  $t0,36($sp)
sw  $t0,4($sp)
lw $t1,4($s7)
li $t2,1
bne $t1,$t2,_lable0
li $t1,1
move $v0,$t1
lw  $ra,32($sp)
lw  $s7,28($sp)
addiu $sp,$sp,36
jr  $ra
j  _lable1
_lable0 :
lw $t1,4($s7)
li $t2,1
sub $t0,$t1,$t2
sw $t0,12($s7)
lw $t1,12($s7)
sw $t1,0($s7)
jal  recursion
move $t0,$v0
sw $t0,16($s7)
move $sp,$s7
lw $t1,4($s7)
lw $t2,16($s7)
add $t0,$t1,$t2
sw $t0,20($s7)
lw $t1,20($s7)
move $v0,$t1
lw  $ra,32($sp)
lw  $s7,28($sp)
addiu $sp,$sp,36
jr  $ra
_lable1 :
lw  $ra,32($sp)
lw  $s7,28($sp)
addiu $sp,$sp,36
jr  $ra
f3 :
addiu $sp,$sp,-136
sw  $ra,132($sp)
sw  $s7,128($sp)
move    $s7,$sp
li $t1,0
li $t2,0
addi $t7,$s7,24
mul $t1,$t1,4
add $t7,$t7,$t1
sw $t2,($t7)
li $t2,0
addi $t7,$s7,24
mul $t2,$t2,4
add $t7,$t7,$t2
lw $t1,($t7)
addiu $t0,$t1,0
sw $t0,52($s7)
lw $t1,52($s7)
li $t2,5
add $t0,$t1,$t2
sw $t0,60($s7)
li $t1,1
lw $t2,60($s7)
addi $t7,$s7,24
mul $t1,$t1,4
add $t7,$t7,$t1
sw $t2,($t7)
li $t1,0
li $t2,49
addi $t7,$s7,36
mul $t1,$t1,4
add $t7,$t7,$t1
sw $t2,($t7)
li $t1,1
li $t2,50
addi $t7,$s7,36
mul $t1,$t1,4
add $t7,$t7,$t1
sw $t2,($t7)
li $t1,1
addiu $t0,$t1,0
sw $t0,8($s7)
li $t1,2
addiu $t0,$t1,0
sw $t0,12($s7)
li $t1,-3
addiu $t0,$t1,0
sw $t0,16($s7)
li $t2,1
addi $t7,$s7,36
mul $t2,$t2,4
add $t7,$t7,$t2
lw $t1,($t7)
addiu $t0,$t1,0
sw $t0,48($s7)
lw $t1,48($s7)
addiu $t0,$t1,0
sw $t0,32($s7)
lw $t1,8($s7)
lw $t2,12($s7)
add $t0,$t1,$t2
sw $t0,44($s7)
lw $t1,16($s7)
lw $t2,12($s7)
sub $t0,$t1,$t2
sw $t0,48($s7)
lw $t1,44($s7)
lw $t2,48($s7)
mul $t0,$t1,$t2
sw $t0,52($s7)
li $t2,0
addi $t7,$s7,24
mul $t2,$t2,4
add $t7,$t7,$t2
lw $t1,($t7)
addiu $t0,$t1,0
sw $t0,60($s7)
li $t2,1
addi $t7,$s7,24
mul $t2,$t2,4
add $t7,$t7,$t2
lw $t1,($t7)
addiu $t0,$t1,0
sw $t0,68($s7)
lw $t1,60($s7)
lw $t2,68($s7)
sub $t0,$t1,$t2
sw $t0,72($s7)
lw $t1,52($s7)
lw $t2,72($s7)
sub $t0,$t1,$t2
sw $t0,76($s7)
li $t2,0
addi $t7,$s7,36
mul $t2,$t2,4
add $t7,$t7,$t2
lw $t1,($t7)
addiu $t0,$t1,0
sw $t0,84($s7)
lw $t1,84($s7)
lw $t2,12($s7)
add $t0,$t1,$t2
sw $t0,88($s7)
lw $t1,88($s7)
lw $t2,32($s7)
add $t0,$t1,$t2
sw $t0,92($s7)
lw $t1,76($s7)
lw $t2,92($s7)
div $t0,$t1,$t2
sw $t0,96($s7)
lw $t1,96($s7)
neg $t0,$t1
sw $t0,100($s7)
lw $t1,100($s7)
lw $t2,8($s7)
mul $t0,$t1,$t2
sw $t0,104($s7)
lw $t1,104($s7)
neg $t0,$t1
sw $t0,108($s7)
lw $t1,32($s7)
li $t2,-3
div $t0,$t1,$t2
sw $t0,116($s7)
lw $t1,108($s7)
lw $t2,116($s7)
sub $t0,$t1,$t2
sw $t0,120($s7)
lw $t1,120($s7)
addiu $t0,$t1,0
sw $t0,20($s7)
lw $a0,20($s7)
li $v0,1
syscall
li $a0 10
li $v0 11
syscall
lw $t1,8($s7)
sw $t1,0($s7)
lw $t1,32($s7)
sw $t1,4($s7)
jal  f1
move $t0,$v0
sw $t0,44($s7)
move $sp,$s7
lw $t1,44($s7)
addiu $t0,$t1,0
sw $t0,16($s7)
lw  $ra,132($sp)
lw  $s7,128($sp)
addiu $sp,$sp,136
jr  $ra
main :
addiu $sp,$sp,-72
sw  $ra,68($sp)
sw  $s7,64($sp)
move    $s7,$sp
li $v0,5
syscall
move $t0,$v0
sw $t0,16($s7)
li $v0,5
syscall
move $t0,$v0
sw $t0,20($s7)
li $t1,97
addiu $t0,$t1,0
sw $t0,44($s7)
lw $t1,16($s7)
li $t2,0
bne $t1,$t2,_lable2
la $a0,.string0
li $v0,4
syscall
li $a0 10
li $v0 11
syscall
j  _lable3
_lable2 :
la $a0,.string1
li $v0,4
syscall
li $a0 10
li $v0 11
syscall
_lable3 :
lw $t1,20($s7)
li $t2,0
beq $t1,$t2,_lable4
la $a0,.string2
li $v0,4
syscall
li $a0 10
li $v0 11
syscall
_lable4 :
li $t1,2
addiu $t0,$t1,0
sw $t0,16($s7)
li $t1,0
addiu $t0,$t1,0
sw $t0,20($s7)
_lable5 :
lw $t1,16($s7)
li $t2,1
sub $t0,$t1,$t2
sw $t0,52($s7)
lw $t1,52($s7)
addiu $t0,$t1,0
sw $t0,16($s7)
lw $t1,20($s7)
lw $t2,16($s7)
addi $t7,$s7,24
mul $t1,$t1,4
add $t7,$t7,$t1
sw $t2,($t7)
lw $t1,20($s7)
li $t2,1
add $t0,$t1,$t2
sw $t0,52($s7)
lw $t1,52($s7)
addiu $t0,$t1,0
sw $t0,20($s7)
lw $t1,16($s7)
li $t2,0
bgt $t1,$t2,_lable5
li $v0,5
syscall
move $t0,$v0
sw $t0,20($s7)
li $t1,0
addiu $t0,$t1,0
sw $t0,16($s7)
_lable6 :
lw $t1,16($s7)
lw $t2,20($s7)
bge $t1,$t2,_lable7
lw $t1,16($s7)
lw $t2,20($s7)
add $t0,$t1,$t2
sw $t0,52($s7)
lw $a0,52($s7)
li $v0,1
syscall
li $a0 10
li $v0 11
syscall
lw $t1,16($s7)
li $t2,1
add $t0,$t1,$t2
sw $t0,16($s7)
j  _lable6
_lable7 :
lw $t1,20($s7)
lw $t2,16($s7)
add $t0,$t1,$t2
sw $t0,48($s7)
lw $t1,48($s7)
sw $t1,0($s7)
li $t1,97
sw $t1,4($s7)
jal  f1
move $t0,$v0
sw $t0,56($s7)
move $sp,$s7
lw $t1,56($s7)
addiu $t0,$t1,0
sw $t0,16($s7)
lw $a0,16($s7)
li $v0,1
syscall
li $a0 10
li $v0 11
syscall
lw $t1,16($s7)
sw $t1,0($s7)
lw $t1,12($s7)
sw $t1,4($s7)
jal  f2
move $t0,$v0
sw $t0,48($s7)
move $sp,$s7
lw $t1,48($s7)
addiu $t0,$t1,0
sw $t0,44($s7)
lw $a0,44($s7)
li $v0,11
syscall
li $a0 10
li $v0 11
syscall
jal  f3
move $t0,$v0
sw $t0,48($s7)
move $sp,$s7
li $t1,1
sw $t1,0($s7)
jal  recursion
move $t0,$v0
sw $t0,52($s7)
move $sp,$s7
lw $t1,52($s7)
addiu $t0,$t1,0
sw $t0,16($s7)
lw $a0,16($s7)
li $v0,1
syscall
li $a0 10
li $v0 11
syscall
li $t1,3
sw $t1,0($s7)
jal  recursion
move $t0,$v0
sw $t0,52($s7)
move $sp,$s7
lw $t1,52($s7)
addiu $t0,$t1,0
sw $t0,16($s7)
lw $a0,16($s7)
li $v0,1
syscall
li $a0 10
li $v0 11
syscall
lw  $ra,68($sp)
lw  $s7,64($sp)
addiu $sp,$sp,72
jr  $ra
_end:
.data
c1:  .word  -5
c2:  .word  0
c3:  .word  6
c4:  .word  'a'
c5:  .word  '-'
c6:  .word  '*'
a1:  .word  
a2:  .word  
a:  .word  
f:  .space  20
d1:  .word  
d2:  .word  
d:  .word  
g:  .space  24
.string0:  .asciiz  "i=0"
.string1:  .asciiz  "i!=0"
.string2:  .asciiz  "j!=0"
