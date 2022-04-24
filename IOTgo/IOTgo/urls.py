"""IOTgo URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/1.11/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  url(r'^$', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  url(r'^$', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.conf.urls import url, include
    2. Add a URL to urlpatterns:  url(r'^blog/', include('blog.urls'))
"""
from django.conf.urls import url
from django.contrib import admin
from ehospital import views
urlpatterns = [
    #网页接口
    url(r'^admin/', admin.site.urls),
    url(r'^index/', views.index),
    url(r'^indexadmin/', views.indexadmin),
    url(r'^login/$', views.login),
    url(r'^datashow/$', views.datashow),
    url(r'^password/$', views.password,name="my_view_name"),
    url(r'^newpassword/$', views.newpassword),
    url(r'^roomcontral/$', views.roomcontral),
    url(r'^datashowsingle/$', views.datashowsingle),
    url(r'^control/$', views.control),
    url(r'^$', views.startwin),

    #微信接口
    url(r'^wx_login/$',views.wx_login),
    url(r'^wx_userinfo/$',views.wx_userinfo),
    url(r'^wx_room/$',views.wx_room),
    url(r'^wx_data/$',views.wx_data),
    url(r'^wx_control_bulb1/$',views.wx_control_bulb1),
    url(r'^wx_control_bulb2/$',views.wx_control_bulb2),
    url(r'^wx_control_fan/$',views.wx_control_fan),
    url(r'^wx_control_curtain/$',views.wx_control_curtain),
    url(r'^wx_control_lock/$',views.wx_control_lock),
    url(r'^wx_control_bed/$',views.wx_control_bed),
    url(r'^wx_user_name/$',views.wx_user_name),
    url(r'^wx_user_email/$',views.wx_user_email),
    url(r'^wx_user_phone/$',views.wx_user_phone),
    url(r'^wx_user_password/$',views.wx_user_password),



    #网关接口
  #  url(r'^gate/$', views.control),
   # url(r'^guan_cd/$', views.guan_cd),


    #测试
    url(r'^try2/$', views.try2),



]