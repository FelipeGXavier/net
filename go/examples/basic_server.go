package examples

import (
	"fmt"
	"log"
	"net"
)

func Listener() {
	port := ":3090"
	server, err := net.Listen("tcp", port)
	if err != nil {
		panic(err)
	}

	fmt.Println("Listening on port ", port)

	for {
		conn, err := server.Accept()
		if err != nil {
			log.Fatalf("Error while accepting socket connection %v", err)
		}
		go handleRequest(conn)
	}
}

func handleRequest(conn net.Conn) {
	defer conn.Close()
	buffer := make([]byte, 1024)
	_, err := conn.Read(buffer)
	if err != nil {
		fmt.Println("Error while reading request", err)
	}
	fmt.Println("Request data: ", string(buffer))
	conn.Write([]byte("Hello World"))
}