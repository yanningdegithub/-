import os
from django.core.mail import send_mail

os.environ['DJANGO_SETTINGS_MODULE'] = 'IOTgo.settings'
# send_mail(
#         '同学你好', #邮件主题subject
#         '丢雷老母,IOTgo给你的验证码是0632',   #邮件具体内容
#         'chs646268684@sina.com',  #第三个参数是邮件发送方，需要和你settings中的一致；
#         ['a'],   # 第四个参数是接受方的邮件地址列表。
#    )