package main

import (
	"fmt"
	"os/exec"
	"syscall"
)

func myexec() {
	cmd := exec.Command("echo", "Jennifer", "linda")

	stdout, err := cmd.Output()
	if err != nil {
		fmt.Println("ocorreu um erro", err)
		syscall.Exit(0)
	}

	stringStdout := string(stdout)
	fmt.Println(stringStdout)
}
