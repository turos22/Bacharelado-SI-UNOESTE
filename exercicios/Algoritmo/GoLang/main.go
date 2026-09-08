package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func Criptografar(texto string){
    for i := 0; i<len(texto); i++{
        fmt.Println(texto[i] - 'a' + 1)
    }
}

func main() {
    fmt.Println("Hello, World!");
    reader := bufio.NewReader(os.Stdin)

    fmt.Print("Digite a string que deseja converter: ")
    texto, err := reader.ReadString('\n')
    if err == nil {
        fmt.Print("Li a string");
        Criptografar(strings.TrimSpace(strings.ToLower(texto)));
    }
}