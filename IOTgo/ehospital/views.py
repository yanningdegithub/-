from django.shortcuts import render
from ehospital import  send_mail
from django.http import HttpResponse
from django.core.mail import send_mail
from django.shortcuts import redirect
from . import models
import os
import random
import json
import socket
import threading
from django.contrib.messages import constants as messages
import time
import datetime
from django.utils.encoding import smart_str
# Create your views here.



#----------------------------------------------------------------------
#网关
from django.views.generic.base import View

# 接收网关数据。存储到服务器数据库
server_addr = ('127.0.0.1', 10001)
tcpSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# 绑定地址
tcpSocket.connect(server_addr)
tcpSocket.send((json.dumps({'first_dir':'DOWN'})+" END").encode())

def recv_sockdata(the_socket):
    # 因为socket每次收到的不一定是完整的数据帧，所以我这里规定的协议，收到END作为一段完整数据的结尾。因此这个函数循环读入数据，返回读到的完整数据帧。
    total_data = ""
    while True:
        data = the_socket.recv(1024).decode()
        if "END" in data:
            total_data += data[:data.index("END")]
            break
        total_data += data
    #print(total_data)
    print("-----------------")
    return total_data

# 线程类，处理和网关的数据交互
class MyThread(threading.Thread, object):
    def __init__(self, sock, addr):
        threading.Thread.__init__(self)
        self.sock = sock
        self.addr = addr
        self.direction = 'UP'
    def run(self):
        #print('Accept new connection from {}...'.format(self.addr))
        #self.link_to_send()
        try:
            self.recv_data()
            #print('Connection from {} closed.'.format(self.addr))
        except (ConnectionResetError,ConnectionAbortedError):
            print('Connection from {} closed.'.format(self.addr))
    def recv_data(self):
        while True:
            print('receiving messange ....')
            res_data = recv_sockdata(self.sock)
            try:
                data = json.loads(res_data, encoding="utf-8")
                # 这个地方的data就是网关传上来的数据，可以在此完成数据入库的操作，或者在此将数据推送到前端。
                print(data)  # 收到的数据
                #
                #
                #接收到数据根据数据的格式，进行判断
                #
                #
                #
                #data["board"]
                # board = data['board']
                # frametype = data['frametype']
                # device = data['device']
                # datalen = data['datalen']
                # content = data['data']
                # nowtime=time.strftime("%Y-%m-%d %H:%M:%S")
                # print(board, frametype, device, datalen, content, nowtime)
                # if(board == 'wenshidu'):
                #     wd = data['data1']
                #     sd= data['data2']
                #     newdata = models.Table_wsd(room_num='F1001',data1=wd,data12=sd,cur_time=nowtime)  #温湿度这里不太懂,还有其他房间的怎么办

                #     newdata.save()
                #     pass
                # elif(board == 'guangzhao'):
                #     newdata = models.Table_guangzhao(room_num='F1001', data=content, cur_time=nowtime)  # 温湿度这里不太懂
                #     newdata.save()
                #     pass
                # elif (board == 'CO2'):
                #     newdata = models.Table_CO2(room_num='F1001', data=content, cur_time=nowtime)  # 温湿度这里不太懂
                #     newdata.save()
                #     pass
                # elif (board == 'PM2.5'):
                #     newdata = models.Table_PM(room_num='F1001', data=content, cur_time=nowtime)  # 温湿度这里不太懂
                #     newdata.save()
                #     pass
                # elif (board == 'ziwaixian'):
                #     newdata = models.Table_ziwaixian(room_num='F1001', data=content, cur_time=nowtime)  # 温湿度这里不太懂
                #     newdata.save()
                #     pass
                # elif (board == 'yanwu'):
                #     newdata = models.Table_yanwu(room_num='F1001', test=content, cur_time=nowtime)  # 温湿度这里不太懂
                #     newdata.save()
                #     pass
                # elif (board == 'huoguang'):
                #     newdata = models.Table_huoguang(room_num='F1001', test=content, cur_time=nowtime)  # 温湿度这里不太懂
                #     newdata.save()
                #     pass
                # elif (board == 'hongwai'):
                #     newdata = models.Table_hongwai(room_num='F1001', test=content, cur_time=nowtime)  # 温湿度这里不太懂
                #     newdata.save()
                #     pass
                # elif (board == 'CH4'):
                #     newdata = models.Table_jiawan(room_num='F1001', data=content, cur_time=nowtime)  # 温湿度这里不太懂
                #     newdata.save()
                #     pass
                # elif (board == 'duishe'):#没有对射反射
                #     pass
                # elif (board == 'fanshe'):
                #     pass

            except json.decoder.JSONDecodeError as e:
                print("error data:" + res_data)
                continue
    # def link_to_send(self):  # 当有连接时，返回一个hello
    #     send_data = {}
    #     # send_data['time'] = time.asctime(time.localtime(time.time()))
    #     #send_data['direction'] = 'DOWN'
    #     #send_data['message'] = 'Welcome to visit Server !'
    #     #send_data['PS'] = 'YHS  NB !!!!!!'
    #     send_data['board'] = 'fengshan'
    #     send_data['frametype'] = 'fengshan'
    #     send_data['device'] = 'fengshan'
    #     send_data['datalen'] = 'fengshan'
    #     send_data['data'] = 'fs_open'
    #     #self.sock.send((json.dumps(send_data)).encode())
    #     print('OK~~----------')

# 创建Socket

# 监听端口，传入的参数指定等待连接的最大数量
# tcpSocket.listen(16)
# threads = []
# print('Waiting for connection...')
thread = MyThread(tcpSocket,server_addr[0])
thread.start()

# 服务器程序通过一个永久循环来接受来自客户端的连接
# def do_service():
#     while True:
#         # 接受一个新连接:
#         sock, addr = tcpSocket.accept()
#         # 创建新线程来处理TCP连接:每个连接都必须创建新线程（或进程）来处理，
#         # 否则，单线程在处理连接的过程中，无法接受其他客户端的连接：
#         mthread = MyThread(sock, addr)
#         mthread.start()
#         threads.append(mthread)
# 将阻塞接受新连接的逻辑放在线程中
#threading.Thread(target=do_service).start()


# 这个control就是普通的视图函数，和大家平时写的index，login函数一样。
# def control(request):
#     print(request.POST)
#     # 这里从POST收到了你前端的数据。
#     # 把数据进行整理后（这里模拟了数据），通过与网关的连接发送给网关。
#     send_data = {}
#     # send_data['gateid'] = request.POST.get('gateid')
#     # send_data['direction'] = 'DOWN'
#     # send_data['nodeid'] = request.POST.get('nodeid')
#     # send_data['type'] = request.POST.get('type')
#     # send_data['data'] = request.POST.get('data')
#     # send_data['time'] = request.POST.get('time')
#     # 将数据发送给已经连接上来的网关
#     for thread in threads:
#         print('send msg!')
#         # thread.sock.send((json.dumps(send_data)+" END").encode())
#         thread.sock.send((json.dumps(send_data)).encode())
#     return HttpResponse(status=200, content='OK')


# def guan_cd(request):
#     print(request.POST)
#     senddata={}
#
#     for thread in threads:
#         print('sendmsg')
#         thread.sock.send((json.dumps(senddata)).encode())
#     return render(request,"control.html")



def wy_deng1_Y():
    senddata={}
    senddata['board'] = 'deng1'
    senddata['frametype'] = 'deng1'
    senddata['device'] = 'deng1'
    senddata['datalen'] = 'deng1'
    senddata['data'] = 'deng1_Y'
    print('sendmsg')
    thread.sock.send((json.dumps(senddata)+"END").encode())
    print('send wydeng1_Y success')

def wy_deng1_G():
    senddata={}
    senddata['board'] = 'deng1'
    senddata['frametype'] = 'deng1'
    senddata['device'] = 'deng1'
    senddata['datalen'] = 'deng1'
    senddata['data'] = 'deng1_G'
    print('sendmsg')
    thread.sock.send((json.dumps(senddata)+"END").encode())
    print('send wy_deng1_G success')

def wy_deng1_R():
    senddata={}
    senddata['board'] = 'deng1'
    senddata['frametype'] = 'deng1'
    senddata['device'] = 'deng1'
    senddata['datalen'] = 'deng1'
    senddata['data'] = 'deng1_R'
    print('sendmsg')
    thread.sock.send((json.dumps(senddata)+"END").encode())
    print('send wydeng1_R success')

def wy_deng1_close():
    senddata={}
    senddata['board'] = 'deng1'
    senddata['frametype'] = 'deng1'
    senddata['device'] = 'deng1'
    senddata['datalen'] = 'deng1'
    senddata['data'] = 'deng1_close'
    print('sendmsg')
    thread.sock.send((json.dumps(senddata)+"END").encode())
    print('send wy_deng1_close success')

def wy_fs_open():
    senddata={}
    senddata['board'] = 'fengshan'
    senddata['frametype'] = 'fengshan'
    senddata['device'] = 'fengshan'
    senddata['datalen'] = 'fengshan'
    senddata['data'] = 'fs_open'
    print('sendmsg')
    thread.sock.send((json.dumps(senddata)+"END").encode())
    print('send fs_open success')

def wy_fs_close():
    senddata={}
    senddata['board'] = 'fengshan'
    senddata['frametype'] = 'fengshan'
    senddata['device'] = 'fengshan'
    senddata['datalen'] = 'fengshan'
    senddata['data'] = 'fs_close'
    print('sendmsg')
    thread.sock.send((json.dumps(senddata)+"END").encode())
    print('send fs_close success')

def wy_cl_open():
    senddata={}
    senddata['board'] = 'chuanglian'
    senddata['frametype'] = 'chuanglian'
    senddata['device'] = 'chuanglian'
    senddata['datalen'] = 'chuanglian'
    senddata['data'] = 'cl_open'
    print('sendmsg')
    thread.sock.send((json.dumps(senddata)+"END").encode())
    print('send cl_open success')

def wy_cl_close():
    senddata={}
    senddata['board'] = 'chuanglian'
    senddata['frametype'] = 'chuanglian'
    senddata['device'] = 'chuanglian'
    senddata['datalen'] = 'chuanglian'
    senddata['data'] = 'cl_close'
    print('sendmsg')
    thread.sock.send((json.dumps(senddata)+"END").encode())
    print('send cl_close success')


def wy_ms():
    senddata={}
    senddata['board'] = 'mensuo'
    senddata['frametype'] = 'mensuo'
    senddata['device'] = 'mensuo'
    senddata['datalen'] = 'mensuo'
    senddata['data'] = 'ms'
    print('sendmsg')
    thread.sock.send((json.dumps(senddata)+"END").encode())
    print('send ms success')


def wy_deng2_close():
    senddata={}
    senddata['board'] = 'deng2'
    senddata['frametype'] = 'deng2'
    senddata['device'] = 'deng2'
    senddata['datalen'] = 'deng2'
    senddata['data'] = 'deng2_close'
    print('sendmsg')
    thread.sock.send((json.dumps(senddata)+"END").encode())
    print('send deng2_close success')

def wy_deng2_slight():
    senddata={}
    senddata['board'] = 'deng2'
    senddata['frametype'] = 'deng2'
    senddata['device'] = 'deng2'
    senddata['datalen'] = 'deng2'
    senddata['data'] = 'deng2_slight'
    print('sendmsg')
    thread.sock.send((json.dumps(senddata)+"END").encode())
    print('send deng2_slight success')

def wy_deng2_middle():
    senddata={}
    senddata['board'] = 'deng2'
    senddata['frametype'] = 'deng2'
    senddata['device'] = 'deng2'
    senddata['datalen'] = 'deng2'
    senddata['data'] = 'deng2_middle'
    print('sendmsg')
    thread.sock.send((json.dumps(senddata)+"END").encode())
    print('send deng2_middle success')

def wy_deng2_strong():
    senddata={}
    senddata['board'] = 'deng2'
    senddata['frametype'] = 'deng2'
    senddata['device'] = 'deng2'
    senddata['datalen'] = 'deng2'
    senddata['data'] = 'deng2_strong'
    print('sendmsg')
    thread.sock.send((json.dumps(senddata)+"END").encode())
    print('send deng2_strong success')


def wy_chuang_0():
    senddata={}
    senddata['board'] = 'chuang'
    senddata['frametype'] = 'chuang'
    senddata['device'] = 'chuang'
    senddata['datalen'] = 'chuang'
    senddata['data'] = 'chuang_0'
    print('sendmsg')
    thread.sock.send((json.dumps(senddata)+"END").encode())
    print('send chuang_0 success')

def wy_chuang_30():
    senddata={}
    senddata['board'] = 'chuang'
    senddata['frametype'] = 'chuang'
    senddata['device'] = 'chuang'
    senddata['datalen'] = 'chuang'
    senddata['data'] = 'chuang_30'
    print('sendmsg')
    thread.sock.send((json.dumps(senddata)+"END").encode())
    print('send chuang_30 success')

def wy_chuang_60():
    senddata={}
    senddata['board'] = 'chuang'
    senddata['frametype'] = 'chuang'
    senddata['device'] = 'chuang'
    senddata['datalen'] = 'chuang'
    senddata['data'] = 'chuang_60'
    print('sendmsg')
    thread.sock.send((json.dumps(senddata)+"END").encode())
    print('send chuang_60 success')


def wy_chuang_90():
    senddata={}
    senddata['board'] = 'chuang'
    senddata['frametype'] = 'chuang'
    senddata['device'] = 'chuang'
    senddata['datalen'] = 'chuang'
    senddata['data'] = 'chuang_90'
    print('sendmsg')
    thread.sock.send((json.dumps(senddata)+"END").encode())
    print('send chuang_90 success')



#------------------------------------
#---------------网页------------

def startwin(requst):
    return render(requst,"startwin.html")

def login(request):
    if request.method == 'POST':
        user_name = request.POST.get('username', 'USERNAME')
        tel_number = request.POST.get('tel_number', 'TEL_NUMBER')
        pass_word = request.POST.get('Password', 'PASSWORD')
        email_num = request.POST.get('email_number', 'EMAIL')
        room_num=models.room.objects.filter(state=0)
        print(user_name,tel_number,pass_word,email_num,room_num)
        #用户注册插入到数据库中，把对应房间设置为有人“1”
        newUser = models.User(username=user_name, phone=tel_number, password=pass_word, email=email_num, room_numb=room_num[0].roomnumber, identity=1)
        newUser.save()
        models.room.objects.filter(roomnumber=room_num[0].roomnumber).update(state=1)
        #注册完成后再转入login，把这三个数据添加入数据库
        print(user_name,tel_number,pass_word,email_num,room_num[0].roomnumber)
        return render(request, "login.html")
    if request.method == 'GET':
        return render(request,"login.html")

def index(request):
    if request.method == 'POST':
        tel_num = request.POST.get('tel_num', 'TEL_NUM')
        pass_wd = request.POST.get('password', 'PASSWORD')
        print(tel_num,pass_wd)
        # try:
        #     user =models.User.objects.get(phone=tel_num,password=pass_wd)
        #     print(user)
        #     if user.identity == 1:
        #         print('进入用户界面')
        #         #msg={'check':"userok",'name':user.username,'room':user.room_numb}
        #         #print(msg)
        #         #return HttpResponse(msg)
        #         return HttpResponse('userok')
        #     elif user.identity == 0:
        #         print('进入管理员界面')
        #         return HttpResponse("adminok")
        #     else:
        #         return render(request,"login.html")
        # except models.User.DoesNotExist:
        #     return HttpResponse("false")
        check=models.User.objects.filter(phone=tel_num)
        #先判断身份，如果是管理源，则进入roomcontral，否则
        #得到登陆的账号密码以后，与数据库进行交互验证，如果没有不对则返回，如果正确则继续将其账号和用户房间号放到界面上
        if len(check) == 0:
            print("输入错误")
            return render(request, "login.html")
        if check[0].password==pass_wd and int(check[0].identity) == 0:
            print('进入管理员界面')
            return render(request, "roomcontral.html")
        elif check[0].password==pass_wd:
            print("进入用户界面")
            print(tel_num,pass_wd)
            roomnumber=check[0].room_numb
            check2 = models.device_state.objects.filter(room_num=roomnumber)
            tishi= models.Table_tishi.objects.filter(room_num=roomnumber)

            print(check2[0].d01,check2[0].d02,check2[0].d03,check2[0].d04,check2[0].d05,check2[0].d06)
            #check3 = models.Table_tishi.objects.filter(user_name=check[0].username)
            #print(check3[0].room_num,check3[0].user_name)
            return render(request,"index.html",{'username':check[0].username,'roomnumber':check[0].room_numb,
                                                'tishi0':tishi[0].option,'tishi1': tishi[1].option,'tishi2': tishi[2].option,
                                                'tishi3':tishi[3].option,'tishi4': tishi[4].option})
        else:
            print("账号对密码不对")
            return render(request, "login.html")
    if request.method == 'GET':
        room_num = request.GET['room_num']
        name = request.GET['contact_name']
        message = request.GET['contact_message']
        check = models.User.objects.filter(room_numb=room_num)
        newmessage = models.message(username=name,roomnum=room_num,text=message)
        newmessage.save()
        return render(request,"index.html",{'username':check[0].username,'roomnumber':check[0].room_numb})
    return render(request, "index.html")

def indexadmin(request):
    if request.method == 'GET':
        id = request.GET['id']
        print(id)
        check = models.User.objects.filter(room_numb__contains=id)
        roomnumber='F'+str(id)
        tishi = models.Table_tishi.objects.filter(room_num=roomnumber)
        if len(check) == 0:
            return render(request, "indexadmin.html", {'username': 'No User', 'roomnumber': 'F' + id})
        else:
            return render(request, "indexadmin.html", {'username': check[0].username, 'roomnumber': check[0].room_numb,'tishi0':tishi[0].option,'tishi1': tishi[1].option,'tishi2': tishi[2].option,
                                                'tishi3':tishi[3].option,'tishi4': tishi[4].option})
    return render(request,"indexadmin.html")

def datashow(request):
    id = request.GET['id']
    roomnumber=request.GET['roomnum']
    print(id,roomnumber)
    #逻辑是每一次进入点击传感器，先去硬件拿取，然后存储在数据库中，再去数据库查询
    if id == '2':
        #二氧化碳
        #print("222222222222222")
        data = models.Table_CO2.objects.filter(room_num=roomnumber)
        print(data[0].data,data[1].data,data[2].data,data[3].data,data[4].data)
        data2 = {"data": data[0].data,"data1": data[1].data,"data2": data[2].data,"data3": data[3].data,"data4": data[4].data,
                 "time": data[0].cur_time.strftime('%H:%M'), "time1": data[1].cur_time.strftime('%H:%M'),
                 "time2": data[2].cur_time.strftime('%H:%M'),
                 "time3": data[3].cur_time.strftime('%H:%M'), "time4": data[4].cur_time.strftime('%H:%M'),
                 "id": id , "roomnumber":roomnumber
                 }
        return render(request, "datashow.html", data2)
    elif id == '3':
        #温湿度
        data = models.Table_wsd.objects.filter(room_num=roomnumber)
        data2 = {"data": data[0].data1,"data1": data[1].data1,"data2": data[2].data1,"data3": data[3].data1,"data4": data[4].data1,
                 "time": data[0].cur_time.strftime('%H:%M'), "time1": data[1].cur_time.strftime('%H:%M'), "time2": data[2].cur_time.strftime('%H:%M'),
                 "time3": data[3].cur_time.strftime('%H:%M'), "time4": data[4].cur_time.strftime('%H:%M'),
                 "id": id, "roomnumber": roomnumber
                 }
        return render(request, "datashow.html", data2)
    elif id == '4':
        #光照传感器
        data = models.Table_guangzhao.objects.filter(room_num=roomnumber)
        data2 = {"data": data[0].data,"data1": data[1].data,"data2": data[2].data,"data3": data[3].data,"data4": data[4].data,
                  "time": data[0].cur_time.strftime('%H:%M'), "time1": data[1].cur_time.strftime('%H:%M'), "time2": data[2].cur_time.strftime('%H:%M'),
                 "time3": data[3].cur_time.strftime('%H:%M'), "time4": data[4].cur_time.strftime('%H:%M'),
                 "id": id, "roomnumber": roomnumber}
        return render(request, "datashow.html", data2)
    elif id == '5':
        #pm2.5
        data = models.Table_PM.objects.filter(room_num=roomnumber)
        data2 = {"data": data[0].data,"data1": data[1].data,"data2": data[2].data,"data3": data[3].data,"data4": data[4].data,
                  "time": data[0].cur_time.strftime('%H:%M'), "time1": data[1].cur_time.strftime('%H:%M'), "time2": data[2].cur_time.strftime('%H:%M'),
                 "time3": data[3].cur_time.strftime('%H:%M'), "time4": data[4].cur_time.strftime('%H:%M'),
                 "id": id, "roomnumber": roomnumber}
        return render(request, "datashow.html", data2)
    elif id == '6':
        #甲烷传感器
        data = models.Table_jiawan.objects.filter(room_num=roomnumber)
        data2 = {"data": data[0].data,"data1": data[1].data,"data2": data[2].data,"data3": data[3].data,"data4": data[4].data,
                  "time": data[0].cur_time.strftime('%H:%M'), "time1": data[1].cur_time.strftime('%H:%M'), "time2": data[2].cur_time.strftime('%H:%M'),
                 "time3": data[3].cur_time.strftime('%H:%M'), "time4": data[4].cur_time.strftime('%H:%M'),
                 "id": id, "roomnumber": roomnumber}
        return render(request, "datashow.html", data2)
    elif id == '10':
        #紫外传感器
        data = models.Table_ziwaixian.objects.filter(room_num=roomnumber)
        data2 = {"data": data[0].data,"data1": data[1].data,"data2": data[2].data,"data3": data[3].data,"data4": data[4].data,
                  "time": data[0].cur_time.strftime('%H:%M'), "time1": data[1].cur_time.strftime('%H:%M'), "time2": data[2].cur_time.strftime('%H:%M'),
                 "time3": data[3].cur_time.strftime('%H:%M'), "time4": data[4].cur_time.strftime('%H:%M'),
                 "id": id, "roomnumber": roomnumber}
        return render(request, "datashow.html", data2)
    return render(request,"datashow.html")

def datashowsingle(request):
    id = request.GET['id']
    roomnumber = request.GET['roomnum']
    print(id, roomnumber)
    # 逻辑是每一次进入点击传感器，先去硬件拿取，然后存储在数据库中，再去数据库查询
    if id == '1':
        # 人体红外
        #
        # 直接在数据库中查找就好
        #
        data = models.Table_hongwai.objects.filter(room_num=roomnumber)
        if int(data[0].test) == 0:
            data2 = {"data": "正常","id": id, "roomnumber": roomnumber}
        else:
            data2 = {"data": "超标","id": id, "roomnumber": roomnumber}
        print(data[0].test)
        return render(request, "datashowsingle.html", data2)
    elif id == '7':
        # 烟雾传感器
        data = models.Table_yanwu.objects.filter(room_num=roomnumber)
        print(data[0].test)
        if int(data[0].test) == 0:
            data2 = {"data": "正常","id": id, "roomnumber": roomnumber}
        else:
            data2 = {"data": "超标","id": id, "roomnumber": roomnumber}
        print(data[0].test)
        return render(request, "datashowsingle.html", data2)
    elif id == '8':
        # 火光传感器
        data = models.Table_huoguang.objects.filter(room_num=roomnumber)
        if int(data[0].test) == 0:
            data2 = {"data": "正常","id": id, "roomnumber": roomnumber}
        else:
            data2 = {"data": "超标","id": id, "roomnumber": roomnumber}
        print(data[0].test)
        return render(request, "datashowsingle.html", data2)
    return render(request,"datashowsingle.html")

def password(request):
    if request.method == 'POST':
        email = request.POST.get('oldemail', None)
        os.environ['DJANGO_SETTINGS_MODULE'] = 'IOTgo.settings'
        a = random.randint(1000, 9999)
        send_mail(
            '同学你好',  # 邮件主题subject
            '丢雷老母,IOTgo给你的验证码是:' + str(a),  # 邮件具体内容
            'chs646268684@sina.com',  # 第三个参数是邮件发送方，需要和你settings中的一致；
            [email],  # 第四个参数是接受方的邮件地址列表。
        )
        # Do your stuff ,calling whatever you want from set_gpio.py
        return render(request, "password.html", {'email': email})
        # return redirect("/password/")
    return render(request,"password.html")

def newpassword(request):
    #
    if request.method == 'GET':
        email = request.GET['email']
        print(email)
        return render(request,"newpassword.html",{'email':email})
    if request.method=='POST':
        newpassword = request.POST.get('newpassword')
        print(newpassword)
        #在数据库中进行插入，根据邮箱
        return render(request, 'login.html')

def roomcontral(request):
    #当管理员一进来就是roomcontrol

    return render(request,"roomcontral.html")



def control(request):
    global roomnumber
    if request.method == 'GET':
        roomnumber = request.GET['roomnum']
        print(roomnumber)
    if request.method == 'POST':
        s = request.POST.get('s')
        print(s,roomnumber)
        #控制就是要先改变数据库，然后发送一个消息
        if(s =='11'):
            #黄灯
            models.device_state.objects.filter(room_num=roomnumber).update(d04=1)
            deng=models.Table_color.objects.filter(room_num=roomnumber).update(data='Y')
            wy_deng1_Y()
            #然后发指令
        elif(s=='10'):
            #关灯
            models.device_state.objects.filter(room_num=roomnumber).update(d04=0)
            # 然后发指令
            wy_deng1_close()
        elif(s=='12'):
            #绿灯
            models.device_state.objects.filter(room_num=roomnumber).update(d04=1)
            models.Table_color.objects.filter(room_num=roomnumber).update(data='G')
            # 然后发指令
            wy_deng1_G()
        elif(s=='13'):
            #红灯
            models.device_state.objects.filter(room_num=roomnumber).update(d04=1)
            models.Table_color.objects.filter(room_num=roomnumber).update(data='R')
            # 然后发指令
            wy_deng1_R()
        elif (s == '20'):
            # 关灯
            models.device_state.objects.filter(room_num=roomnumber).update(d05=0)
            wy_deng2_close()
        elif (s == '21'):
            # 弱光
            models.device_state.objects.filter(room_num=roomnumber).update(d05=1)
            models.Table_liangdu.objects.filter(room_num=roomnumber).update(data='10')
            # 然后发指令
            wy_deng2_slight()
        elif (s == '22'):
            # 中光
            models.device_state.objects.filter(room_num=roomnumber).update(d05=1)
            models.Table_liangdu.objects.filter(room_num=roomnumber).update(data='20')
            # 然后发指令
            wy_deng2_middle()
        elif (s == '23'):
            # 强光
            models.device_state.objects.filter(room_num=roomnumber).update(d05=1)
            models.Table_liangdu.objects.filter(room_num=roomnumber).update(data='30')
            # 然后发指令
            wy_deng2_strong()
        elif (s == '30'):
            # 0°
            models.device_state.objects.filter(room_num=roomnumber).update(d06=0)
            models.Table_bedheight.objects.filter(room_num=roomnumber).update(data='0')
            # 然后发指令
            wy_chuang_0()
        elif (s == '31'):
            # 30°
            models.device_state.objects.filter(room_num=roomnumber).update(d06=1)
            models.Table_bedheight.objects.filter(room_num=roomnumber).update(data='30')
            # 然后发指令
            wy_chuang_30()
        elif (s == '32'):
            # 60°
            models.device_state.objects.filter(room_num=roomnumber).update(d06=1)
            models.Table_bedheight.objects.filter(room_num=roomnumber).update(data='60')
            # 然后发指令
            wy_chuang_60()
        elif (s == '33'):
            # 90°
            models.device_state.objects.filter(room_num=roomnumber).update(d06=1)
            models.Table_bedheight.objects.filter(room_num=roomnumber).update(data='90')
            # 然后发指令
            wy_chuang_90()
        elif (s == '40'):
            # 关窗帘
            models.device_state.objects.filter(room_num=roomnumber).update(d02=0)
            # 然后发指令
            wy_cl_close()
        elif (s == '41'):
            # 开窗帘
            models.device_state.objects.filter(room_num=roomnumber).update(d02=1)
            # 然后发指令
            wy_cl_open()
        elif (s == '50'):
            # 关门
            models.device_state.objects.filter(room_num=roomnumber).update(d03=0)
            # 然后发指令
            wy_ms()
        elif (s == '51'):
            # 开门
            models.device_state.objects.filter(room_num=roomnumber).update(d03=1)
            # 然后发指令
            wy_ms()
        elif (s == '60'):
            # 关风扇
            models.device_state.objects.filter(room_num=roomnumber).update(d01=0)
            # 然后发指令
            wy_fs_close()
        elif (s == '61'):
            # 开风扇
            models.device_state.objects.filter(room_num=roomnumber).update(d01=1)
            # 然后发指令
            wy_fs_open()
        else:
            pass
    return render(request,"control.html")









#----------------------------------------
#--------微信--------------------------






WEIXIN_TOKEN = 'write-a-value'
#为微信进行的接口

def wx_login(request):
    # def wx_login(request):
    #     if request.method == 'POST':
    #         print(json.loads(request.body.decode()))
    #         email = '111'
    #         spassword = '222'
    #         res = {"result": "1", "email": email, "password": spassword}
    #         return HttpResponse(content=json.dumps(res), content_type=json)
    #     else:
    #         return HttpResponse('GET')
    #
    #
    #
    #    打印出{'email': '869177378@qq.com'}
    #
    if request.method == "POST":
        srcdata=json.loads(request.body.decode())
        email=srcdata["email"]
        pasword=srcdata["password"]
        print(email,pasword)
        result=models.User.objects.filter(email=email,password=pasword)
        if len(result) == 0:
            #返回结果失败
            result2 = '0'
            userid = 'None'
            identity='None'
        else:
            #返回结果成功
            result2 = '1'
            userid = str(result[0].id)
            identity = str(result[0].identity)
        res={"result":result2,"userid":userid,"identity":identity}
        #要记得用json格式传递
        #src_data = {"name": "Tacey", "age": 13, "sex": "male", "interst": ("Programing", "Reading")}
        # print repr(src_data)
        #print (json.dumps(src_data))
        #json_data = json.dumps(src_data)
        #print(json.loads(json_data)["name"])
        return  HttpResponse(content=json.dumps(res), content_type=json)


def wx_userinfo(request):
    if request.method == 'POST' :
        srcdata = json.loads(request.body.decode())
        userid=srcdata["userid"]
        model=models.User.objects.filter(id=userid)
        room=model[0].room_numb
        ph=model[0].phone
        email=model[0].email
        identity=model[0].identity
        name=model[0].username
        res={"room":room,"ph":ph,"email":email,"identity":identity,"name":name}
        return HttpResponse(content=json.dumps(res), content_type=json)


def wx_room(request):
    if request.method == 'POST':
        srcdata= json.loads(request.body.decode())
        roomid = srcdata["roomid"]
        model = models.device_state.objects.filter(room_num=roomid)
        #
        #
        #
        #不用去底层问了，因为他们定时跟新了数据库，然后更新数据库
        #
        #
        #
        #要记得变成字符串
        fan = model[0].d01   #风扇
        curtain = model[0].d02 #窗帘
        lock = model[0].d03 #门锁
        #下面要数据,还有火光和紫外线没有
        #bulb1 = models.Table_color.objects.filter(room_num=roomid)[0].data   #可调颜色
        #bulb2 = models.Table_liangdu.objects.filter(room_num=roomid)[0].data #可调亮度
        bulb1=model[0].d04
        bulb2=model[0].d05
        bed = models.Table_bedheight.objects.filter(room_num=roomid)[0].data  #床
        wd = models.Table_wsd.objects.filter(room_num=roomid)[0].data1  # 温度
        sd = models.Table_wsd.objects.filter(room_num=roomid)[0].data12  #湿度
        wsd =wd+'/'+sd
        eyht = models.Table_CO2.objects.filter(room_num=roomid)[0].data  # co2
        hwx = models.Table_hongwai.objects.filter(room_num=roomid)[0].test  # 红外线
        gz = models.Table_guangzhao.objects.filter(room_num=roomid)[0].data  # 光照
        pm = models.Table_PM.objects.filter(room_num=roomid)[0].data  # pm2.5
        jw = models.Table_jiawan.objects.filter(room_num=roomid)[0].data  # 甲烷
        yw = models.Table_yanwu.objects.filter(room_num=roomid)[0].test  # 烟雾
        res = {"bulb1": str(bulb1), "bulb2": str(bulb2), "bed": bed, "wsd":wsd,"eyht":eyht,"hwx":hwx, "gz":gz,"pm":pm,"jw":jw, "yw":yw ,"fan": str(fan), "curtain": str(curtain),"lock": str(lock)}
        return HttpResponse(content=json.dumps(res), content_type=json)

def wx_data(request):
    if request.method == 'POST':
        srcdata= json.loads(request.body.decode())
        data = srcdata["data"]
        if data == 'wsd':
            room1=models.Table_wsd.objects.filter(room_num='F1001')
            room2 = models.Table_wsd.objects.filter(room_num='F1002')
            room3 = models.Table_wsd.objects.filter(room_num='F1003')
            room4 = models.Table_wsd.objects.filter(room_num='F1004')
            room5 = models.Table_wsd.objects.filter(room_num='F1005')
            room6 = models.Table_wsd.objects.filter(room_num='F1006')
            room7 = models.Table_wsd.objects.filter(room_num='F1007')
            room8 = models.Table_wsd.objects.filter(room_num='F1008')
            room9 = models.Table_wsd.objects.filter(room_num='F1009')
            room10 = models.Table_wsd.objects.filter(room_num='F1010')
            res={"wsd1":room1[0].data1+'/'+room1[0].data12,"wsd2":room2[0].data1+'/'+room2[0].data12,"wsd3":room3[0].data1+'/'+room3[0].data12,
                 "wsd4":room4[0].data1+'/'+room4[0].data12,"wsd5":room5[0].data1+'/'+room5[0].data12,"wsd6":room6[0].data1+'/'+room6[0].data12
                ,"wsd7":room7[0].data1+'/'+room7[0].data12,"wsd8":room8[0].data1+'/'+room8[0].data12,
                 "wsd9":room9[0].data1+'/'+room9[0].data12,"wsd10":room10[0].data1+'/'+room10[0].data12}
            return HttpResponse(content=json.dumps(res), content_type=json)
        elif data == 'eyht':
            room1 = models.Table_CO2.objects.filter(room_num='F1001')
            room2 = models.Table_CO2.objects.filter(room_num='F1002')
            room3 = models.Table_CO2.objects.filter(room_num='F1003')
            room4 = models.Table_CO2.objects.filter(room_num='F1004')
            room5 = models.Table_CO2.objects.filter(room_num='F1005')
            room6 = models.Table_CO2.objects.filter(room_num='F1006')
            room7 = models.Table_CO2.objects.filter(room_num='F1007')
            room8 = models.Table_CO2.objects.filter(room_num='F1008')
            room9 = models.Table_CO2.objects.filter(room_num='F1009')
            room10 = models.Table_CO2.objects.filter(room_num='F1010')
            res = {"wsd1": room1[0].data , "wsd2": room2[0].data,
                   "wsd3": room3[0].data ,"wsd4": room4[0].data, "wsd5": room5[0].data,
                   "wsd6": room6[0].data, "wsd7": room7[0].data, "wsd8": room8[0].data,
                   "wsd9": room9[0].data, "wsd10": room10[0].data }
            return HttpResponse(content=json.dumps(res), content_type=json)
        elif data == 'hwx':
            room1 = models.Table_hongwai.objects.filter(room_num='F1001')
            room2 = models.Table_hongwai.objects.filter(room_num='F1002')
            room3 = models.Table_hongwai.objects.filter(room_num='F1003')
            room4 = models.Table_hongwai.objects.filter(room_num='F1004')
            room5 = models.Table_hongwai.objects.filter(room_num='F1005')
            room6 = models.Table_hongwai.objects.filter(room_num='F1006')
            room7 = models.Table_hongwai.objects.filter(room_num='F1007')
            room8 = models.Table_hongwai.objects.filter(room_num='F1008')
            room9 = models.Table_hongwai.objects.filter(room_num='F1009')
            room10 = models.Table_hongwai.objects.filter(room_num='F1010')
            res = {"wsd1": room1[0].test, "wsd2": room2[0].test,
                   "wsd3": room3[0].test, "wsd4": room4[0].test, "wsd5": room5[0].test,
                   "wsd6": room6[0].test, "wsd7": room7[0].test, "wsd8": room8[0].test,
                   "wsd9": room9[0].test, "wsd10": room10[0].test}
            return HttpResponse(content=json.dumps(res), content_type=json)
        elif data == 'gz':
            room1 = models.Table_guangzhao.objects.filter(room_num='F1001')
            room2 = models.Table_guangzhao.objects.filter(room_num='F1002')
            room3 = models.Table_guangzhao.objects.filter(room_num='F1003')
            room4 = models.Table_guangzhao.objects.filter(room_num='F1004')
            room5 = models.Table_guangzhao.objects.filter(room_num='F1005')
            room6 = models.Table_guangzhao.objects.filter(room_num='F1006')
            room7 = models.Table_guangzhao.objects.filter(room_num='F1007')
            room8 = models.Table_guangzhao.objects.filter(room_num='F1008')
            room9 = models.Table_guangzhao.objects.filter(room_num='F1009')
            room10 = models.Table_guangzhao.objects.filter(room_num='F1010')
            res = {"wsd1": room1[0].data, "wsd2": room2[0].data,
                   "wsd3": room3[0].data, "wsd4": room4[0].data, "wsd5": room5[0].data,
                   "wsd6": room6[0].data, "wsd7": room7[0].data, "wsd8": room8[0].data,
                   "wsd9": room9[0].data, "wsd10": room10[0].data}
            return HttpResponse(content=json.dumps(res), content_type=json)
        elif data == 'pm':
            room1 = models.Table_PM.objects.filter(room_num='F1001')
            room2 = models.Table_PM.objects.filter(room_num='F1002')
            room3 = models.Table_PM.objects.filter(room_num='F1003')
            room4 = models.Table_PM.objects.filter(room_num='F1004')
            room5 = models.Table_PM.objects.filter(room_num='F1005')
            room6 = models.Table_PM.objects.filter(room_num='F1006')
            room7 = models.Table_PM.objects.filter(room_num='F1007')
            room8 = models.Table_PM.objects.filter(room_num='F1008')
            room9 = models.Table_PM.objects.filter(room_num='F1009')
            room10 = models.Table_PM.objects.filter(room_num='F1010')
            res = {"wsd1": room1[0].data, "wsd2": room2[0].data,
                   "wsd3": room3[0].data, "wsd4": room4[0].data, "wsd5": room5[0].data,
                   "wsd6": room6[0].data, "wsd7": room7[0].data, "wsd8": room8[0].data,
                   "wsd9": room9[0].data, "wsd10": room10[0].data}
            return HttpResponse(content=json.dumps(res), content_type=json)
        elif data == 'jw':
            room1 = models.Table_jiawan.objects.filter(room_num='F1001')
            room2 = models.Table_jiawan.objects.filter(room_num='F1002')
            room3 = models.Table_jiawan.objects.filter(room_num='F1003')
            room4 = models.Table_jiawan.objects.filter(room_num='F1004')
            room5 = models.Table_jiawan.objects.filter(room_num='F1005')
            room6 = models.Table_jiawan.objects.filter(room_num='F1006')
            room7 = models.Table_jiawan.objects.filter(room_num='F1007')
            room8 = models.Table_jiawan.objects.filter(room_num='F1008')
            room9 = models.Table_jiawan.objects.filter(room_num='F1009')
            room10 = models.Table_jiawan.objects.filter(room_num='F1010')
            res = {"wsd1": room1[0].data, "wsd2": room2[0].data,
                   "wsd3": room3[0].data, "wsd4": room4[0].data, "wsd5": room5[0].data,
                   "wsd6": room6[0].data, "wsd7": room7[0].data, "wsd8": room8[0].data,
                   "wsd9": room9[0].data, "wsd10": room10[0].data}
            return HttpResponse(content=json.dumps(res), content_type=json)
        elif data == 'yw':
            room1 = models.Table_yanwu.objects.filter(room_num='F1001')
            room2 = models.Table_yanwu.objects.filter(room_num='F1002')
            room3 = models.Table_yanwu.objects.filter(room_num='F1003')
            room4 = models.Table_yanwu.objects.filter(room_num='F1004')
            room5 = models.Table_yanwu.objects.filter(room_num='F1005')
            room6 = models.Table_yanwu.objects.filter(room_num='F1006')
            room7 = models.Table_yanwu.objects.filter(room_num='F1007')
            room8 = models.Table_yanwu.objects.filter(room_num='F1008')
            room9 = models.Table_yanwu.objects.filter(room_num='F1009')
            room10 = models.Table_yanwu.objects.filter(room_num='F1010')
            res = {"wsd1": room1[0].test, "wsd2": room2[0].test,
                   "wsd3": room3[0].test, "wsd4": room4[0].test, "wsd5": room5[0].test,
                   "wsd6": room6[0].test, "wsd7": room7[0].test, "wsd8": room8[0].test,
                   "wsd9": room9[0].test, "wsd10": room10[0].test}
            return HttpResponse(content=json.dumps(res), content_type=json)
        else:
            return HttpResponse("None")
    return HttpResponse("GET")


def wx_control_bulb1(request):
    if request.method == 'POST':
        srcdata=json.loads(request.body.decode())
        roomid = srcdata["roomid"]
        bulb1_status = srcdata["bulb1_status"]
        #接收到以后要先设置数据库，然后向底层发请求
        models.device_state.objects.filter(room_num=roomid).update(d04 = int(bulb1_status))
        if int(bulb1_status) == 1 :
            wy_deng1_R() #开灯默认为红灯
        else:
            wy_deng1_close()
            #关彩灯或者开彩灯
        res = {"result": 'yes'}
        return  HttpResponse(content=json.dumps(res), content_type=json)
    return HttpResponse("sa")


def wx_control_bulb2(request):
    if request.method == 'POST':
        srcdata = json.loads(request.body.decode())
        roomid = srcdata["roomid"]
        bulb2_status = srcdata["bulb2_status"]
        #  接收到以后要先设置数据库，然后向底层发请求
        models.device_state.objects.filter(room_num=roomid).update(d05=int(bulb2_status))
        # 控制亮度灯状态
        if int(bulb2_status) == 1 :
            wy_deng2_strong() #开启
        else:
            wy_deng2_close()
    #    这里要跳转到传输指令的def函数，那怎么跳转回来继续发送呢
        res = {"result": 'yes'}
        return HttpResponse(content=json.dumps(res), content_type=json)
    return HttpResponse("sa")


def wx_control_fan(request):
    if request.method == 'POST':
        srcdata = json.loads(request.body.decode())
        roomid = srcdata["roomid"]
        fan_status = srcdata["fan_status"]
        #  接收到以后要先设置数据库，然后向底层发请求
        models.device_state.objects.filter(room_num=roomid).update(d01=int(fan_status))
        # 控制风扇状态
        if int(fan_status) == 1 :
            wy_fs_open() #开风扇
        else:
            wy_fs_close()

        res = {"result": 'yes'}
        return HttpResponse(content=json.dumps(res), content_type=json)
    return HttpResponse("sa")


def wx_control_curtain(request):
    if request.method == 'POST':
        srcdata = json.loads(request.body.decode())
        roomid = srcdata["roomid"]
        curtain_status = srcdata["curtain_status"]
        #  接收到以后要先设置数据库，然后向底层发请求
        models.device_state.objects.filter(room_num=roomid).update(d02=int(curtain_status))
        # 控制风扇状态
        if int(curtain_status) == 1 :
            wy_cl_open() #开窗帘
        else:
            wy_cl_close()
        res = {"result": 'yes'}
        return HttpResponse(content=json.dumps(res), content_type=json)
    return HttpResponse("sa")


def wx_control_lock(request):
    if request.method == 'POST':
        srcdata = json.loads(request.body.decode())
        roomid = srcdata["roomid"]
        lock_status = srcdata["lock_status"]
        #  接收到以后要先设置数据库，然后向底层发请求
        models.device_state.objects.filter(room_num=roomid).update(d03=int(lock_status))
        if int(lock_status) == 1 :
            wy_ms() #开锁
        else:
            wy_ms()
    #    这里要跳转到传输指令的def函数，那怎么跳转回来继续发送呢
        res = {"result": 'yes'}
        return HttpResponse(content=json.dumps(res), content_type=json)
    return HttpResponse("sa")


def wx_control_bed(request):
    if request.method == 'POST':
        srcdata = json.loads(request.body.decode())
        roomid = srcdata["roomid"]
        bed_status = srcdata["bed_status"]
        #  接收到以后要先设置数据库，然后向底层发请求
        models.Table_bedheight.objects.filter(room_num=roomid).update(data=bed_status)
        if bed_status == '0':
            wy_chuang_0()
        elif bed_status == '30':
            wy_chuang_30()
        elif bed_status == '60':
            wy_chuang_60()
        elif bed_status == '90':
            wy_chuang_90()
    #    这里要跳转到传输指令的def函数，那怎么跳转回来继续发送呢
        res = {"result": 'yes'}
        return HttpResponse(content=json.dumps(res), content_type=json)
    return HttpResponse("sa")


def wx_user_name(request):
    if request.method == 'POST':
        srcdata = json.loads(request.body.decode())
        userid = srcdata["userid"]
        newname = srcdata["newname"]
        models.User.objects.filter(id=userid).update(username=newname)
        res = {"result": 'yes'}
        return HttpResponse(content=json.dumps(res), content_type=json)
    return HttpResponse("sa")


def wx_user_email(request):
    if request.method == 'POST':
        srcdata = json.loads(request.body.decode())
        userid = srcdata["userid"]
        newemail = srcdata["newemail"]
        models.User.objects.filter(id=userid).update(email=newemail)
        res = {"result": 'yes'}
        return HttpResponse(content=json.dumps(res), content_type=json)
    return HttpResponse("sa")

def wx_user_phone(request):
    if request.method == 'POST':
        srcdata = json.loads(request.body.decode())
        userid = srcdata["userid"]
        newphone = srcdata["newphone"]
        models.User.objects.filter(id=userid).update(phone=newphone)
        res = {"result": 'yes'}
        return HttpResponse(content=json.dumps(res), content_type=json)
    return HttpResponse("sa")


def wx_user_password(request):
    if request.method == 'POST':
        srcdata = json.loads(request.body.decode())
        userid = srcdata["userid"]
        newpassword = srcdata["newpassword"]
        models.User.objects.filter(id=userid).update(password=newpassword)
        res = {"result": 'yes'}
        return HttpResponse(content=json.dumps(res), content_type=json)
    return HttpResponse("sa")


def wx_warn(request):
    #好像这个warn只能对一个房间来说。。。。
    if request.method == 'POST':
        srcdata = json.loads(request.body.decode())
        check = srcdata["check"]
        # time1 = int(time.time())
        # min_time = time1-20
        # max_time = time1+20
        # curtime_min= time.strftime("%Y-%m-%d %H:%M:%S")
        # curtime_max=str((time.time())+20)
        # print(curtime_min,curtime_max)
        jiawan=models.Table_jiawan.objects.filter()
        yanwu=models.Table_yanwu.objects.filter(cur_time__range=(curtime_min,curtime_max))
        huoguang=models.Table_jiawan.objects.filter()
        #甲烷、烟雾、火光、对射、反射
        if  len(yanwu) != 0:
            #烟雾传感器报警，
            #逻辑
            #首先得到一个当时的时间，然后与数据库中最上面一条数据进行时间差比较，若小于20s（定时器时间间隔15s）则定义为近期数据
            #返回一个1
            res = {"result": "1"}
        elif len(jiawan) != 0:
            #甲烷传感器报警
            res = {"result": "2"}
        elif len(huoguang) != 0:
            #火光开关报警
            res = {"result": "3"}
        else:
            res={"result":"0"}
        return HttpResponse(content=json.dumps(res), content_type=json)


def try2(request):
    curtime_hour = time.strftime("%H")
    curtime_min = time.strftime("%M")
    curtime_sec = time.strftime("%S")
    jiawan=models.Table_jiawan.objects.filter()[0].cur_time
    jiawan_hour =jiawan.strftime("%H")
    jiawan_min = jiawan.strftime("%M")
    jiawan_sec = jiawan.strftime("%S")
    print(curtime_hour,curtime_min,curtime_sec,jiawan_hour,jiawan_min,jiawan_sec)
    if curtime_hour==jiawan_hour and curtime_min == jiawan_min and int(curtime_sec)-20<=int(jiawan_sec):
        print("22")
    else:
        print("11")
    return HttpResponse("ok")






