package main

import (
	"fmt"
	"syscall"
)

func exit() {
	fmt.Println("Imprime essa mensagem")
	syscall.Exit(0)
	fmt.Println("Mas não imprime essa")
}
