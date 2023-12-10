package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strings"
)

func main() {
	file, err := os.Open("input.txt")
	if err != nil {
		panic(err)
	}

	scanner := bufio.NewScanner(file)
	sum := 0
	for scanner.Scan() {
		line := scanner.Text()
		columnIndex := strings.Index(line, ":")
		cards := strings.Split(line[columnIndex+1:], "|")

		winningNumbers := map[string]bool{}
		{
			tempWinning := strings.Split(cards[0], " ")
			for item := range tempWinning {
				if tempWinning[item] == "" {
					continue
				}

				winningNumbers[tempWinning[item]] = true
			}
		}

		countNumbers := 0
		{
			tempMine := strings.Split(cards[1], " ")

			for i := range tempMine {
				_, found := winningNumbers[tempMine[i]]
				if found {
					countNumbers++
				}
			}
		}

		sum += int(math.Pow(2, float64(countNumbers-1)))
	}

	fmt.Println(sum)
}
