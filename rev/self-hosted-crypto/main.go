package main

import "os"

func cipher(dat []byte) []byte {
	output := make([]byte, len(dat))
	for i, b := range dat {
		output[i] = b + 13
	}
	return output
}

func main() {
	dat, err := os.ReadFile(os.Args[1])
	if err != nil {
		panic(err)
	}

	encrypted := cipher(dat)
	err = os.WriteFile("encrypted", encrypted, 0644)
}
