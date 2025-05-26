package main

import (
	"fmt"
	"math/rand"
	"sort"
	"time"
)

// Генератор случайных чисел (использует текущее время для инициализации)
func init() {
	rand.Seed(time.Now().UnixNano())
}

// Функция для генерации случайного целого числа в диапазоне [min, max]
func randomInt(min, max int) int {
	return rand.Intn(max-min+1) + min
}

// Создает и выводит массив из n случайных чисел
func mas(n int) []int {
	arr := make([]int, n)
	// Заполнение массива случайными числами
	for i := 0; i < n; i++ {
		arr[i] = randomInt(10, 100)
	}

	// Вывод массива с форматированием (8 чисел в строке)
	fmt.Printf("1. Исходный массив (%d элементов):\n", n)
	for i := 0; i < n; i++ {
		fmt.Printf("%4d", arr[i])
		if (i+1)%8 == 0 || i == n-1 {
			fmt.Println()
		}
	}
	return arr
}

// Находит два наименьших элемента и сумму остатков от деления всех элементов на минимальный
func minElements(arr []int) {
	min1, min2 := 101, 101 // Инициализация 101, т.к. в массиве числа в диапазоне до 100

	// Поиск двух наименьших элементов
	for _, num := range arr {
		if num < min1 {
			min2 = min1
			min1 = num
		} else if num < min2 && num != min1 {
			min2 = num
		}
	}

	// Вычисление суммы остатков от деления на минимальный элемент
	sum := 0
	for _, num := range arr {
		sum += num % min1
	}

	fmt.Printf("\n2. Два наименьших элемента: %d и %d\n", min1, min2)
	fmt.Printf("   Сумма остатков от деления на %d: %d\n", min1, sum)
}

// Находит самую длинную возрастающую последовательность в массиве
func longestSequence(arr []int) {
	var longest, current []int // Текущая и самая длинная последовательности

	for i := 0; i < len(arr); i++ {
		// Если последовательность продолжает расти
		if i == 0 || arr[i] > arr[i-1] {
			current = append(current, arr[i])
		} else {
			// Если текущая последовательность длиннее найденной
			if len(current) > len(longest) {
				longest = make([]int, len(current))
				copy(longest, current)
			}
			current = []int{arr[i]} // Начинаем новую последовательность
		}
	}
	// Проверка последней последовательности
	if len(current) > len(longest) {
		longest = make([]int, len(current))
		copy(longest, current)
	}

	// Вывод результата
	fmt.Printf("\n3. Самая длинная возрастающая последовательность (%d элементов):\n", len(longest))
	for i := 0; i < len(longest); i++ {
		fmt.Printf("%4d", longest[i])
		if (i+1)%8 == 0 || i == len(longest)-1 {
			fmt.Println()
		}
	}
}

// Выводит числа по специальному шаблону
func specialPrint(N int) {
	const start = 2000      // Начальное значение
	const step = 10         // Шаг между элементами
	const elLine = 8        // Элементов в строке
	totalElements := N * elLine // Всего элементов

	// Создание массива чисел
	arr := make([]int, totalElements)
	for i := 0; i < totalElements; i++ {
		arr[i] = start + i*step
	}

	fmt.Printf("\n4. Вывод по специальному шаблону (N = %d):\n", N)

	// Первый вариант вывода
	fmt.Println("Вывод 1:")
	for i := 0; i < N; i++ {
		for j := 0; j < elLine; j++ {
			fmt.Printf("%5d", arr[i*elLine+j])
		}
		fmt.Println()
	}

	// Второй вариант вывода
	fmt.Println("\nВывод 2:")
	sortedArr := make([]int, len(arr))
	copy(sortedArr, arr)
	// Сортировка по убыванию
	sort.Slice(sortedArr, func(i, j int) bool {
		return sortedArr[i] > sortedArr[j]
	})

	for i := 0; i < N; i++ {
		if i%2 == 1 { // Четные строки (индексация с 0) - по возрастанию
			for j := 0; j < elLine; j++ {
				fmt.Printf("%5d", sortedArr[i*elLine+j])
			}
		} else { // Нечетные строки - по убыванию
			for j := elLine - 1; j >= 0; j-- {
				fmt.Printf("%5d", sortedArr[i*elLine+j])
			}
		}
		fmt.Println()
	}
}

func main() {
	// Ввод длины массива с проверкой (n >= 10)
	var n int
	for {
		fmt.Print("Введите длину массива (n >= 10): ")
		fmt.Scan(&n)
		if n >= 10 {
			break
		}
	}

	// Создание и обработка массива
	arr := mas(n)
	minElements(arr)
	longestSequence(arr)

	// Дополнительное задание с выводом по шаблону
	var N int
	fmt.Print("\nВведите N для задания 4: ")
	fmt.Scan(&N)
	specialPrint(N)
}
