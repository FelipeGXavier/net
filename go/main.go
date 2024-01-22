package main

import (
	"log"
	"netsample/examples"
	"path/filepath"
)

func main() {
	pcapFile, err := filepath.Abs("bin/docker_bridge.pcap")
	if err != nil {
		log.Fatal("Could not find pcap file", err)
		panic(err)
	}
	examples.ParsePcapFile(pcapFile)
	// examples.UdpServer()
	// examples.UdpClient()
}