package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	maxCubesByGame := make(map[string]map[string]int)

	file, error := os.Open("input.txt")
	if error != nil {
		fmt.Println(error)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		columnIndex := strings.Index(line, ":")
		spaceIndex := strings.Index(line, " ")
		gameID := strings.Trim(line[spaceIndex:columnIndex], " ")
		maxCubesByGame[gameID] = make(map[string]int)

		games := strings.Split(line[columnIndex+1:], ";")

		for _, game := range games {
			draws := strings.Split(game, ", ")

			for _, draw := range draws {
				draw := strings.Trim(draw, " ")

				pair := strings.Split(draw, " ")
				color := pair[1]
				number, err := strconv.Atoi(pair[0])
				if err != nil {
					fmt.Println("it's not a number: ", err)
					panic(err)
				}

				if maxCubesByGame[gameID][color] == 0 || maxCubesByGame[gameID][color] < number {
					maxCubesByGame[gameID][color] = number
				}
			}
		}

	}

	sum := 0
	for _, maxCubes := range maxCubesByGame {
		gamePower := 1

		for _, number := range maxCubes {
			gamePower *= number
		}
		sum += gamePower
	}

	fmt.Println(sum)
}
