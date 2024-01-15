package org.example;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

public class SocketClient {

    public static void main(String[] args) throws UnknownHostException {
        InetAddress host = InetAddress.getLocalHost();
        try (var client = new Socket(host.getHostName(), 3090)) {
            ObjectOutputStream outputStream = new ObjectOutputStream(client.getOutputStream());
            System.out.println("Sending data to server ");
            outputStream.writeObject("Request");

            ObjectInputStream inputStream = new ObjectInputStream(client.getInputStream());
            System.out.println("Response: " + inputStream.readObject());

            outputStream.close();
            inputStream.close();
        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        }
    }
}
