package org.Demo;

import org.eclipse.jetty.server.Server;

import java.net.InetSocketAddress;

public class SimpleServer {
    public static void main(String[] argv) throws Exception {
        Server server = new Server(new InetSocketAddress("127.0.0.1", 8080));
        server.setHandler(new HelloHandler());
        server.start();
        server.join();
    }
}
