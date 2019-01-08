#!/usr/bin/python
# -*- coding: utf-8 -*-

import socket
import threading

HOST = ''
PORT = 41400

def cli_fun(conn):
    with conn:
        # close the socket after recv() timeout
        conn.settimeout(60);
        print('Connected by ', addr)
        while True:
            try: 
                data = conn.recv(100)
            except socket.timeout:
                conn.close()
                conn = None
                break

            if not data: break
            print("R:%s > %s" % (addr, str(data, encoding='utf-8')))
            msg = "Reply -> " + str(data, encoding='utf-8').split(':', maxsplit=1)[0]
            print(msg)
            conn.sendall(bytes(msg, encoding='utf-8'))

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind((HOST, PORT))
    s.listen(1)
    while 1:
        conn, addr = s.accept()
        c = threading.Thread(target = cli_fun, args = (conn,))
        c.start()


