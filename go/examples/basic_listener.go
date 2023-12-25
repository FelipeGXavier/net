package examples

import (
	"fmt"
	"log"
	"net"
)

func Listener() {
	port := ":3090"
	listener, err := net.Listen("tcp", port)
	if err != nil {
		panic(err)
	}

	fmt.Println("Listening on port ", port)

	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Fatalf("Error while accepting socket connection %v", err)
		}
		fmt.Println(conn)
	}
}