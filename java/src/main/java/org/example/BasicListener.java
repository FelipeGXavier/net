package org.example;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class BasicListener {

    public static void main(String[] args) throws IOException {
        int port = 3090;
        try (final ServerSocket serverSocket = new ServerSocket(port)) {
            System.out.println("Listening on port 3090 ");
            while (true) {
                Socket connection = serverSocket.accept();
                System.out.println(connection);
            }
        }
    }
}
