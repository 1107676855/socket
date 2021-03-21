from socket import *
from time import ctime

HOST = '192.168.199.245'
POST = 8888
BUFSIZ = 1024
ADDR = (HOST, POST)

tcpCliSock = socket(AF_INET, SOCK_STREAM)
tcpCliSock.connect(ADDR)

while True:
    data = tcpCliSock.recv(BUFSIZ)
    if not data:
        break
    print("[%s]: %s" % (ctime(), data.decode()))
