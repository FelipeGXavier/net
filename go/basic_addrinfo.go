package main

import (
	"fmt"
	"net"
)


func addressInfo() {
	hostname := "example.com"
	
	ips, err := net.LookupIP(hostname)

	if err != nil {
		fmt.Printf("Error resolving IP %s \n", err)
	}

	for _, ip := range ips {
		fmt.Println(ip.String())
	}
}