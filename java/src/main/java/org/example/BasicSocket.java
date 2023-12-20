package org.example;

import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.UnknownHostException;

public class BasicSocket {

    public static void main(String[] args) throws IOException {
        try (Socket socket = new Socket()) {
            InetSocketAddress inetSocketAddress = getInetAddress();
            socket.connect(inetSocketAddress);
            var pid = ProcessHandle.current().pid();
            System.out.println("PID: " + pid);
            while (true) {

            }
        }
    }

    private static InetSocketAddress getInetAddress() {
        var hostname = "example.com";
        try {
            InetAddress[] addresses = InetAddress.getAllByName(hostname);
            var firstAdress = addresses[0];
            return new InetSocketAddress(firstAdress.getHostAddress(), 80);
        } catch (UnknownHostException e) {
            e.printStackTrace();
            return null;
        }
    }
}
