package main

import (
	"fmt"
	"os/exec"
)

func main() {
	cmd := exec.Command("echo", "sou o processo pai")
	cmd.Run()
	fmt.Printf("%d\n", cmd.Process.Pid)

	// pid, err := syscall.ForkExec("echo", "sou o processo filho", )
	// if err != nil {
	// 	syscall.Exit(0)
	// }

}
