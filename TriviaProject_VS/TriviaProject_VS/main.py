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
    
    birthday = input("enter date of birth: ")
    signupInfo = '{"username":"' + username + '","password":"' + password + '","email":"' + email + '","phoneNumber":"' + phoneNum +'","date":"' + birthday + '"}'
    # print(signupInfo)
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


def sendMsgByid(msgid):
    msgTypeDict = {"0": '0', "1": '1', "2": '2', "3": '3',
                   "4": '4', "5": '5', "6": '6', "7": '7',
                   "8": '8', "9": '9'}
    msg = ""
    msgLen = padMsg(str(len(msg)), 4)
    send_str = msgTypeDict[str(msgid)] + msgLen + msg
    byteStream = bytearray(send_str, 'utf-8')
    return byteStream


def createRoom():
    roomname = input("Enter name of room to create: ")
    maxusers = input("Enter max users: ")
    questioncount = input("Enter question count: ")
    answertimeout = input("Enter answer timeout: ")
    createInfo = '{"roomName":"' + roomname + '","maxUsers":"' + maxusers + '","questionCount":"' + questioncount + '","answerTimeout":"' + answertimeout + '"} '
    msgLen = padMsg(str(len(createInfo)), 4)
    send_str = '4' + msgLen + createInfo
    byteStream = bytearray(send_str, 'utf-8')
    return byteStream


def sendWithRoomId(id):
    msgTypeDict = {"0": '0', "1": '1', "2": '2', "3": '3',
                   "4": '4', "5": '5', "6": '6', "7": '7',
                   "8": '8', "9": '9'}
    roomid = input("enter room id to join: ")
    joinInfo = '{"roomId":"' + roomid + '"}'
    msgLen = padMsg(str(len(joinInfo)), 4)
    send_str = msgTypeDict[str(id)] + msgLen + joinInfo
    byteStream = bytearray(send_str, 'utf-8')
    return byteStream


def main():
    msgTypeDict = {"0": '0', "1": '1', "2": '2', "3": '3',
                   "4": '4', "5": '5', "6": '6', "7": '7',
                   "8": '8', "9": '9'}
    sock = connect()
    new_thread = Thread(target=recvMsg, args=(sock,))
    new_thread.start()
    msg = ""
    while True:
        msg = ""
        userChoice = input("0 - Send signup\n1 - Send login\n2 - logout(after login only)"
                           "\n3 - sign out(after login only)\n4 - Create room\n5 - join room\n"
                           "6 - get players in room\n7 - get rooms\n8 - get user stats\n9 - get high score\n")
        if userChoice == msgTypeDict["1"]:  # login
            msg = CreateLogin()
        elif userChoice == msgTypeDict["0"]:  # signup
            msg = CreateSignup()
        elif userChoice == msgTypeDict["2"]:  # logout
            msg = sendMsgByid(2)
        elif userChoice == msgTypeDict["3"]:  # sign-out
            msg = sendMsgByid(3)
        elif userChoice == msgTypeDict["4"]:  # create room
            msg = createRoom()
        elif userChoice == msgTypeDict["5"]:  # join room
            msg = sendWithRoomId(5)
        elif userChoice == msgTypeDict["6"]:  # get players in room
            msg = sendWithRoomId(6)
        elif userChoice == msgTypeDict["7"]:  # get rooms
            msg = sendMsgByid(7)
        elif userChoice == msgTypeDict["8"]:  # get stats of user
            msg = sendMsgByid(8)
        elif userChoice == msgTypeDict["9"]:  # get high score
            msg = sendMsgByid(9)

        sock.sendall(msg)


if __name__ == '__main__':
    main()
