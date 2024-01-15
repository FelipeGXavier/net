package examples

import (
	"fmt"
	"net"
)

func Client() {
	port := ":3090"
	client, err := net.Dial("tcp", port)
	if err != nil {
		panic(err)
	}

	client.Write([]byte("Request sent"))

	buffer := make([]byte, 1024)

	_, err = client.Read(buffer)

	if err != nil {
		panic(err)
	}

	fmt.Println("Response from server: ", string(buffer))

	defer client.Close()

	
}