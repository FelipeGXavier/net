package examples

import (
	"fmt"
	"log"
	"net"
	"os"
)


func UdpClient() {
	server, err := net.ResolveUDPAddr("udp", ":3090")

	if err != nil {
		log.Fatal("ResolveUDPAddr failed:", err.Error())
		os.Exit(1)
	}

	conn, err := net.DialUDP("udp", nil, server)
	if err != nil {
		log.Fatal("Dial failed:", err.Error())
		os.Exit(1)
	}

	defer conn.Close()

	_, err = conn.Write([]byte("Request udp packet"))
	if err != nil {
		log.Fatal("Write failed:", err.Error())
		os.Exit(1)
	}

	buffer := make([]byte, 1024)
	_, err = conn.Read(buffer)
	if err != nil {
		println("Read data failed:", err.Error())
		os.Exit(1)
	}

	fmt.Println("Response: ", string(buffer))

}