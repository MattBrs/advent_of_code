package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	numbers := []string{"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"}

	file, error := os.Open("input.txt")
	if error != nil {
		fmt.Println("There was an error: ", error)
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)
	sum := 0
	for scanner.Scan() {
		line := scanner.Text()

		for i := 0; i < len(numbers); i++ {

			line = strings.Replace(line, numbers[i], numbers[i]+strconv.Itoa(i+1)+numbers[i], -1)
		}

		sum += (srcTop(line, 0) * 10) + srcBot(line, len(line)-1)
	}

	fmt.Println(sum)
}

func srcTop(line string, pos int) int {
	if pos > len(line) {
		return 0
	}

	number, err := strconv.Atoi(string(line[pos]))
	if err != nil {
		return srcTop(line, pos+1)
	}

	return number
}

func srcBot(line string, pos int) int {
	if pos < 0 {
		return 0
	}

	number, err := strconv.Atoi(string(line[pos]))
	if err != nil {
		return srcBot(line, pos-1)
	}

	return number
}
