package org.example;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class SocketServer {

    public static void main(String[] args) throws IOException {
        try (var server = new ServerSocket(3090)) {
            while (true) {
                Socket connection = server.accept();

                ObjectInputStream inputStream = new ObjectInputStream(connection.getInputStream());
                byte[] buffer = new byte[1024];
                StringBuilder requestData = new StringBuilder();

                while (inputStream.read(buffer) != -1) {
                    requestData.append(new String(buffer));
                }

                System.out.println(">>Request received" + requestData);

                ObjectOutputStream outputStream = new ObjectOutputStream(connection.getOutputStream());
                outputStream.writeObject("Hello World");

                inputStream.close();
                outputStream.close();
                connection.close();
            }
        }
    }
}
