import socket
import time

def main(dest_name):
    dest_addr = socket.gethostbyname(dest_name)
    port = 4950
    udp = socket.getprotobyname('udp')
    ttl = 1
    while True:
        send_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, udp)
        send_socket.setsockopt(socket.SOL_IP, socket.IP_TTL, ttl)
        send_socket.sendto('HI bro.. am done', (dest_name, port))
        time.sleep(3)

if __name__ == '__main__':
    main('192.168.29.32')
