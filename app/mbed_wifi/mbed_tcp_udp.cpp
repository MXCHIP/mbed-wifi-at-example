/* WiFi Example
 * Copyright (c) 2016 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mbed.h"
#include "TCPSocket.h"
#include "UDPSocket.h"
#include "config.h"
#include "MXCHIPInterface.h"

MXCHIPInterface wifi(D1, D0);
static SocketAddress udp_server( "192.168.20.110", 4001 );
static SocketAddress *addr;


static void http_demo(NetworkInterface *net)
{
    TCPSocket tcpsocket;

    printf("Sending HTTP request to www.arm.com...\r\n");

    // Open a socket on the network interface, and create a TCP connection to www.arm.com
    tcpsocket.open(net);
    printf("finish open()\r\n");
    int value=tcpsocket.connect("www.arm.com", 80);
    if(!value)
    	printf("connect to ww.arm.com successfully\r\n");
    // Send a simple http request
    char sbuffer[] = "GET / HTTP/1.1\r\nHost: www.arm.com\r\n\r\n";
    int scount = tcpsocket.send(sbuffer, sizeof sbuffer);
    printf("sent %d [%.*s]\r\n", scount, strstr(sbuffer, "\r\n")-sbuffer, sbuffer);

    // Recieve a simple http response and print out the response line
    char rbuffer[64];
    int rcount = tcpsocket.recv(rbuffer, sizeof rbuffer);
    printf("recv %d [%.*s]\r\n", rcount, strstr(rbuffer, "\r\n")-rbuffer, rbuffer);

    // Close the socket to return its memory and bring down the network interface
    tcpsocket.close();
}


static void udp_demo(NetworkInterface *net){
	char buffer[] = "hello UDP!\r\n";
	UDPSocket udpsocket;
	int n=0;
	char buf[20];

	addr=&udp_server;
   printf("udpsocket.open() status:%d\r\n",udpsocket.open( &wifi ));
   while(1){
	   udpsocket.sendto( SocketAddress("192.168.20.110", 4001), buffer, sizeof(buffer) );
	   wait(2);
	   n++;
	   if(n==3){
           n=0;
		   while(true){
			   memset(buf, 0, sizeof(buf));
			   udpsocket.recvfrom(addr,buf,sizeof(buf));
			   printf("recv from remote udp :%s\r\n",buf);
			   wait(0.5);
		   }
	   }
   }
}


static void tcp_demo(NetworkInterface *net)
{
	  char buffer[]="hello world!\r\n";
	   char buf[20];
	   int n=0;
	   TCPSocket tcpsocket;
	   nsapi_error_t ns_ret;

	   tcpsocket.open( net );

	   ns_ret = tcpsocket.connect( SocketAddress("192.168.20.110", 4001) );
	   if ( ns_ret != NSAPI_ERROR_OK ) {
	       printf( "\r\n TCP Connection error:%d\r\n",ns_ret );
	       goto a;
	   }

	      printf("Connect to server successfully.\r\n");
	a:   while(1)
	   {
	      // tcp_send( &tcpsocket, buffer, sizeof(buffer) );
		 tcpsocket.send(buffer,sizeof(buffer));
	       wait(1);
	       n++;
	       if(n==5)
           {
	    	   while(true)
               {
                   memset(buf, 0x00, sizeof(buf));
	    		   tcpsocket.recv(buf,20);
	    		   printf("recv :%s\r\n",buf);
	    		   wait(1);
	    	   }
	    	   tcpsocket.close();
	       }
	   }
}


int app_mbed_wifi()
{
    printf("WiFi example\r\n\r\n");

    printf("\r\nConnecting...\r\n");

    int ret = wifi.connect( MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2, 0 );
    if (ret != 0) {
        printf("\r\nConnection error\r\n");
        return -1;
    }

    printf("Success\r\n\r\n");
    printf("MAC: %s\r\n", wifi.get_mac_address());
    printf("IP: %s\r\n", wifi.get_ip_address());
    printf("RSSI: %d\r\n\r\n", wifi.get_rssi());

    http_demo(&wifi);
    // udp_demo(&wifi);
    // tcp_demo(&wifi);

    wifi.disconnect();

    printf("\r\nDone\r\n");

    return 0;
}

