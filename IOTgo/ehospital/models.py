from django.db import models

# Create your models here.
class User(models.Model):
    username = models.CharField(max_length=20, verbose_name='用户名')
    phone= models.CharField(max_length=20, verbose_name='电话号码')
    password = models.CharField(max_length=20, verbose_name='密码')
    email =models.CharField(max_length=50,verbose_name='电子邮箱',null=True)
    room_numb =models.CharField(max_length=10,verbose_name='房间号')
    identity=models.IntegerField(default=1,verbose_name='身份属性')
    class Meta:
        verbose_name = '用户'
        verbose_name_plural = verbose_name
    def __str__(self):
        return self.username

class room(models.Model):
    roomnumber = models.CharField(max_length=10, verbose_name='房间号码')
    state = models.IntegerField(default=0,verbose_name='房间状态')
    class Meta:
        verbose_name = '房间'
        verbose_name_plural = verbose_name
    def __str__(self):
        return self.roomnumber

class message(models.Model):
    username = models.CharField(max_length=30, verbose_name='留言人名称')
    roomnum = models.CharField(max_length=10,verbose_name='留言人房间号')
    text = models.CharField(max_length=100, verbose_name='留言信息')
    class Meta:
        verbose_name = '留言'
        verbose_name_plural = verbose_name
    def __str__(self):
        return self.username


class device_state(models.Model):
   room_num =  models.CharField(max_length=20, verbose_name='房间号码')
   d01 = models.IntegerField(default=0,verbose_name='风扇')
   d02 = models.IntegerField(default=0, verbose_name='窗帘')
   d03 = models.IntegerField(default=0, verbose_name='自动门锁')
   d04 = models.IntegerField(default=0,verbose_name='可调颜色灯泡')
   d05 = models.IntegerField(default=0,verbose_name='可调亮度灯泡')
   d06 = models.IntegerField(default=0, verbose_name='病床（舵机）')
   d07 = models.IntegerField(default=1, verbose_name='报警灯（LED灯）')
   d08 = models.IntegerField(default=1, verbose_name='报警器（喇叭）')
   d09 = models.IntegerField(default=1, verbose_name='甲烷传感器')
   d10 = models.IntegerField(default=1, verbose_name='温湿度传感器')
   d11 = models.IntegerField(default=1, verbose_name='光照传感器')
   d12 = models.IntegerField(default=1, verbose_name='CO2传感器')
   d13 = models.IntegerField(default=1, verbose_name='PM2.5传感器')
   d14 = models.IntegerField(default=1, verbose_name='紫外线传感器')
   d15 = models.IntegerField(default=1, verbose_name='烟雾传感器')
   d16 = models.IntegerField(default=1, verbose_name='火光传感器',null=True)
   d17 = models.IntegerField(default=1, verbose_name='红外传感器',null=True)
   class Meta:
        verbose_name = '设备状态'
        verbose_name_plural = verbose_name
   def __str__(self):
        return self.room_num

class Table_color(models.Model):
    room_num = models.CharField(max_length=20, verbose_name='房间号码')
    data = models.CharField(max_length=20, verbose_name='颜色选择')
    class Meta:
        verbose_name = '可调颜色灯泡'
        verbose_name_plural = verbose_name

    def __str__(self):
        return self.room_num

class Table_liangdu(models.Model):
    room_num = models.CharField(max_length=20, verbose_name='房间号码')
    data = models.CharField(max_length=20, verbose_name='亮度选择')
    class Meta:
        verbose_name = '可调亮度灯泡'
        verbose_name_plural = verbose_name
    def __str__(self):
        return self.room_num

class Table_bedheight(models.Model):
    room_num = models.CharField(max_length=20, verbose_name='房间号码')
    data = models.CharField(max_length=20, verbose_name='病床高度选择')
    class Meta:
        verbose_name = '可调高度病床'
        verbose_name_plural = verbose_name
    def __str__(self):
        return self.room_num

class Table_jiawan(models.Model):
    room_num = models.CharField(max_length=20, verbose_name='房间号码')
    data = models.CharField(max_length=20, verbose_name='浓度')
    cur_time = models.DateTimeField(verbose_name='时间')
    class Meta:
        verbose_name = '甲烷传感器'
        verbose_name_plural = verbose_name
        ordering = ['-cur_time']
    def __str__(self):
        return self.room_num

class Table_wsd(models.Model):
    room_num = models.CharField(max_length=20, verbose_name='房间号码')
    data1 = models.CharField(max_length=20, verbose_name='温度')
    data12 = models.CharField(max_length=20, verbose_name='湿度')
    cur_time = models.DateTimeField(verbose_name='时间')
    class Meta:
        verbose_name = '温湿度传感器'
        verbose_name_plural = verbose_name
        ordering = ['-cur_time']
    def __str__(self):
        return self.room_num

class Table_guangzhao(models.Model):
    room_num = models.CharField(max_length=20, verbose_name='房间号码')
    data = models.CharField(max_length=20, verbose_name='光强')
    cur_time = models.DateTimeField(verbose_name='时间')
    class Meta:
        verbose_name = '光照传感器'
        verbose_name_plural = verbose_name
        ordering = ['-cur_time']
    def __str__(self):
        return self.room_num

class Table_CO2(models.Model):
    room_num = models.CharField(max_length=20, verbose_name='房间号码')
    data = models.CharField(max_length=20, verbose_name='CO2浓度')
    cur_time = models.DateTimeField(verbose_name='时间')
    class Meta:
        verbose_name = 'CO2传感器'
        verbose_name_plural = verbose_name
        ordering = ['-cur_time']
    def __str__(self):
        return self.room_num

class Table_PM(models.Model):
    room_num = models.CharField(max_length=20, verbose_name='房间号码')
    data = models.CharField(max_length=20, verbose_name='PM2.5浓度')
    cur_time = models.DateTimeField(verbose_name='时间')

    class Meta:
        verbose_name = 'PM2.5传感器'
        verbose_name_plural = verbose_name
        ordering = ['-cur_time']
    def __str__(self):
        return self.room_num

class Table_ziwaixian(models.Model):
    room_num = models.CharField(max_length=20, verbose_name='房间号码')
    data = models.CharField(max_length=20, verbose_name='紫外线强度')
    cur_time = models.DateTimeField(verbose_name='时间')
    class Meta:
        verbose_name = '紫外线传感器'
        verbose_name_plural = verbose_name
        ordering = ['-cur_time']
    def __str__(self):
        return self.room_num


class Table_yanwu(models.Model):
    room_num = models.CharField(max_length=20, verbose_name='房间号码')
    test = models.IntegerField(verbose_name='有无烟雾')
    cur_time = models.DateTimeField(verbose_name='时间')
    class Meta:
        verbose_name = '烟雾传感器'
        verbose_name_plural = verbose_name
        ordering = ['-cur_time']
    def __str__(self):
        return self.room_num

class Table_huoguang(models.Model):
    room_num = models.CharField(max_length=20, verbose_name='房间号码')
    test = models.IntegerField(verbose_name='有无火光')
    cur_time = models.DateTimeField(verbose_name='时间')
    class Meta:
        verbose_name = '火光传感器'
        verbose_name_plural = verbose_name
        ordering = ['-cur_time']
    def __str__(self):
        return self.room_num

class Table_hongwai(models.Model):
    room_num = models.CharField(max_length=20, verbose_name='房间号码')
    test = models.IntegerField(verbose_name='有无人感应')
    cur_time = models.DateTimeField(verbose_name='时间')
    class Meta:
        verbose_name = '红外传感器'
        verbose_name_plural = verbose_name
        ordering = ['-cur_time']
    def __str__(self):
        return self.room_num

class Table_tishi(models.Model):
    user_name = models.CharField(max_length=20,verbose_name='用户名')
    room_num = models.CharField(max_length=20, verbose_name='房间号码')
    option = models.CharField(max_length=30,verbose_name='操作种类')
    cur_time = models.DateTimeField(verbose_name='时间')
    class Meta:
        verbose_name = '提示'
        verbose_name_plural = verbose_name
        ordering = ['-cur_time']
    def __str__(self):
        return self.room_num