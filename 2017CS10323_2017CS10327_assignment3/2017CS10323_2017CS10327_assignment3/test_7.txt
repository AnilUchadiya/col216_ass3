lw $1, $zero
lw $2, $zero
lw $3 ,$zero
addi $1, $1 ,10
addi $2 ,$2, 5
slt $3 ,$1, $2
bne $3, $0, 5
END CODE