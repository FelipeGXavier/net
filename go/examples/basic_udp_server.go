package examples

import (
	"fmt"
	"log"
	"net"
	"time"
)

func UdpServer() {
	server, err := net.ListenPacket("udp", ":3090")
	if err != nil {
		log.Fatal(err)
	}

	defer server.Close()

	for {
		buffer := make([]byte, 1024)
		_, addr, err := server.ReadFrom(buffer)
		fmt.Println("Received a packet")
		if err != nil {
			log.Fatal(err)
			continue
		}
		go handleUdpPacket(server, addr, buffer)
	}
}

func handleUdpPacket(server net.PacketConn, addr net.Addr, buffer []byte) {
	time := time.Now().Format(time.ANSIC)
	responseStr := fmt.Sprintf("time received: %v. Your message: %v!", time, string(buffer))
	server.WriteTo([]byte(responseStr), addr)
}