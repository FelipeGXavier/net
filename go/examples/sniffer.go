package examples

import (
	"log"

	"github.com/google/gopacket"
	"github.com/google/gopacket/pcap"
)


func ParsePcapFile(fileName string) {
	handle, err := pcap.OpenOffline(fileName)
	if err != nil {
		log.Fatal(err)
	}
	defer handle.Close()

	packetSource := gopacket.NewPacketSource(handle, handle.LinkType())
	for packet := range packetSource.Packets() { 
		capturedAt := packet.Metadata().Timestamp
		log.Default().Println("Packet captured at: ", capturedAt, packet.Dump())
	}
}