package org.example;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class UdpSocketClient {

    public static void main(String[] args) {
        try (var client = new DatagramSocket()) {
            client.setSoTimeout(10000);
            var message = "Hello World";
            InetAddress inetAddress = InetAddress.getLocalHost();
            DatagramPacket sendPacket = new DatagramPacket(message.getBytes(), message.length(), inetAddress, 3090);
            client.send(sendPacket);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

    }
}
