import pickle
import socket
import threading
import time
import json
import sys
from threading import Thread

SERVER_IP = "127.0.0.1"
SERVER_PORT = 2022


def padMsg(msg, size):
    while len(msg) < size:
        msg = "0" + msg
    return msg


def CreateLogin():
    username = input("enter username: ")
    password = input("enter password: ")
    loginInfo = '{"username":"' + username + '","password":"' + password + '"}'
    msgLen = padMsg(str(len(loginInfo)), 4)
    send_str = '1' + msgLen + loginInfo
    byteStream = bytearray(send_str, 'utf-8')
    return byteStream


def CreateSignup():
    username = input("enter username: ")
    password = input("enter password: ")
    email = input("enter email: ")
    phoneNum = input("enter phone number: ")
    address = input("enter address: ")
    birthday = input("enter date of birth: ")
    signupInfo = '{"username":"' + username + '","password":"' + password + '","email":"' + email + '","phoneNumber":"' + phoneNum + '","address":"' + address + '","date":"' + birthday + '"}'
    print(signupInfo)
    msgLen = padMsg(str(len(signupInfo)), 4)
    send_str = '0' + msgLen + signupInfo
    byteStream = bytearray(send_str, 'utf-8')
    return byteStream


def connect():
    # Create a TCP/IP socket
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # Connecting to local machine at port 2022
    print("Connecting to localhost at port ", SERVER_PORT, "...")
    server_address = (SERVER_IP, SERVER_PORT)
    sock.connect(server_address)
    print("Sock connected")
    return sock


def recvMsg(sock):
    while True:
        server_msg = sock.recv(1024)
        server_msg = server_msg.decode()
        print("Received message from server: ", server_msg)


def main():
    sock = connect()
    new_thread = Thread(target=recvMsg, args=(sock,))
    new_thread.start()
    msg = ""
    while True:
        userChoice = input("1 - Send login\n2- Send signup\n")
        if userChoice == '1': # login
            msg = CreateLogin()
        elif userChoice == '2':  # signup
            msg = CreateSignup()
        sock.sendall(msg)



if __name__ == '__main__':
    main()