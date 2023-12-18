package org.example;

import java.net.InetAddress;
import java.net.UnknownHostException;

public class BasicAddrInfo {

    public static void main(String[] args) {
        var hostname = "example.com";
        try {
            InetAddress[] addresses = InetAddress.getAllByName(hostname);
            for (var address : addresses) {
                System.out.println(address);
            }
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }
    }
}
