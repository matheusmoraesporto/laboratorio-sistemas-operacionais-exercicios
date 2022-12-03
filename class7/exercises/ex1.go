package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	var n int

	for n < 0 || n > 10 {
		reader := bufio.NewReader(os.Stdin)
		fmt.Print("Informe a quantidade de threads que você deseja criar: ")
		text, _ := reader.ReadString('\n')
		n, _ = strconv.Atoi(text)
	}

}
