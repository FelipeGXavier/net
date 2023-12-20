package main

import (
	"errors"
	"fmt"
	"log"
	"net"
	"os"

	"golang.org/x/sys/unix"
)


func basicSocket() {
	hostname := "example.com"
	
	ips, err := net.LookupIP(hostname)

	if err != nil {
		fmt.Printf("Error resolving IP %s \n", err)
	}

	var ipv4 *string = nil;

	for _, ip := range ips {
		if ip.To4() != nil {
			ipConverted := ip.To4().String()
			ipv4 = &ipConverted
			break
		} 
	}

	if ipv4 != nil {
		socket, err := net.Dial("tcp", fmt.Sprintf("%s:%s", *ipv4, "80"))
		if err != nil {
			panic(err)
		}

		defer socket.Close()

		pid := os.Getpid()

		fd, err := getFdFromConn(socket)
		

		fmt.Println("PID: ", pid, " fd: ", fd)
		for {

		}
	}

}


func unixSocketFromScratch() {
	socketFd, err := unix.Socket(unix.AF_INET, unix.SOCK_STREAM, unix.IPPROTO_IP)
	if err != nil {
		log.Fatal("Error creating socket")
		panic(err)
	}

	serverAddress := unix.SockaddrInet4{
		Port: 9041,
		Addr: [4]byte{127, 0, 0, 1},
	}

	defer unix.Close(socketFd)

	err = unix.Bind(socketFd, &serverAddress)

	if err != nil {
		log.Fatal("Error binding socket")
		panic(err)
	}
	
}

func getFdFromConn(c net.Conn) (uintptr, error) {
	file, err := c.(*net.TCPConn).File()
	if err != nil {
		return 0, errors.New("Cant find fd from connection")
	}
	fd := file.Fd()
	return fd, nil
}