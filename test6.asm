lw $1, $zero
lw $2, $zero
lw $3, $zero
addi $1 ,$1 ,10
beq	$1 ,$2, 10
add	$3, $3 ,$2
add	$2, $2 ,1
j 5
lw $31 ,$3
END CODE