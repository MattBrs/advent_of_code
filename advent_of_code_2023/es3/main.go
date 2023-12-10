package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func main() {
	file, err := os.Open("input.txt")
	if err != nil {
		panic(err)
	}

	size := 0
	{
		scanner := bufio.NewScanner(file)
		scanner.Scan()
		size = len(scanner.Text())
		file.Seek(0, 0)
	}

	matrix := make([][]string, size)
	for i := range matrix {
		matrix[i] = make([]string, size)
	}

	scanner := bufio.NewScanner(file)

	for i := 0; i < size; i++ {
		scanner.Scan()
		line := scanner.Text()
		for j := 0; j < size; j++ {
			matrix[i][j] = string(line[j])
		}
	}

	sum := 0
	for i := 1; i < size-1; i++ {
		for j := 1; j < size-1; j++ {
			if isSymbol(matrix[i][j]) {
				sum += calcEdges(matrix, i, j)
			}
		}
	}

	fmt.Println(sum)
	file.Close()
}

func calcEdges(matrix [][]string, i int, j int) int {
	sum := 1
	numbers := make(map[int]bool)
	countNumbers := 0

	for k := i - 1; k < i+2; k++ {
		for l := j - 1; l < j+2; l++ {
			if (k == i && l == j) || matrix[k][l] == "." {
				continue
			}

			_, err := strconv.Atoi(matrix[k][l])
			if err == nil {
				curr := matrix[k][l]
				left := seekLeft(matrix[k], l-1)
				right := seekRight(matrix[k], l+1)

				number, _ := strconv.Atoi(left + curr + right)
				_, found := numbers[number]
				if !found {
					countNumbers++
					numbers[number] = true
				}
			}
		}
	}

	if countNumbers < 2 {
		return 0
	}

	for item := range numbers {
		sum *= item
	}

	return sum
}

func seekLeft(row []string, j int) string {
	if j < 0 || isSymbol(row[j]) || row[j] == "." {
		return ""
	}

	return seekLeft(row, j-1) + row[j]
}

func seekRight(row []string, j int) string {
	if j >= len(row) || isSymbol(row[j]) || row[j] == "." {
		return ""
	}

	return row[j] + seekRight(row, j+1)
}

func isSymbol(char string) bool {
	_, err := strconv.Atoi(char)
	return err != nil && char != "." && char == "*"
}
