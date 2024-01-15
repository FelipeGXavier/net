package org.example;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class UdpSocketServer {

    public static void main(String[] args) {

        try (var server = new DatagramSocket(3090)) {
            byte[] requestBuffer = new byte[1024];
            while (true) {
                DatagramPacket requestPacket = new DatagramPacket(requestBuffer, requestBuffer.length);
                server.receive(requestPacket);
                InetAddress inetAddress = requestPacket.getAddress();
                String requestMessage = new String(requestPacket.getData(), 0, requestPacket.getLength());
                System.out.println("Message received " + requestMessage + " from address " + inetAddress);
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
