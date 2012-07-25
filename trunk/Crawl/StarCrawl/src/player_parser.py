# coding=utf-8
'''
Created on 2010-5-23

@author: 游枭
'''

import urllib2, re, threading, time
from db_manager import DataBaseManager
from star_manager import PlayerItem
from tool import Tool

#
# 代理服务器列表
#
proxy_list = [
              "218.201.21.175",
              "125.64.94.68:808"
              ]

class Parser():
    def __init__(self, url):
        """构造函数，得到要解析的url地址"""
        self._url        = url
        self._tool       = Tool()
        self._is_proxy   = False
        self._proxy_list = []
    
    def AddProxyServer(self):
        """添加代理服务器"""
        for server_url in proxy_list:
            proxy_server = ProxyServer(server_url)
            self._proxy_list.append(proxy_server)
            
    def GetProxyServer(self):
        """获得还未使用的代理服务器地址"""
        for proxy_server in self._proxy_list:
            if proxy_server._is_used == False:
                proxy_server._is_used = True
                return proxy_server._server_address
        
        return None
    
    def SendRequest(self):
        """向服务器发送请求"""
        try:
            if self._is_proxy == False:
                req = urllib2.Request(self._url)
            else:
                #
                # 使用代理服务器
                #
                proxy_server_url = self.GetProxyServer()
                if proxy_server_url == None:
                    return None
                
                print "更换代理服务器(%s)重新进行请求" % proxy_server_url
                
                proxy_support = urllib2.ProxyHandler({'http' : proxy_server_url})  
                opener = urllib2.build_opener(proxy_support, urllib2.HTTPHandler)  
                urllib2.install_opener(opener)
                req = urllib2.Request(self._url)
                
            response = urllib2.urlopen(req)
            
            if response == None:
                return None
            else:
                html = response.read()
                response.close()
                return html
        except urllib2.HTTPError, e:
            print e
            print 'urllib2.HTTPError'
            return None
        except urllib2.URLError, e:
            print e
            print 'urllib2.URLError'
            #
            # 改使用代理服务器请求
            #
            if self._is_proxy == False:
                self._is_proxy = True
                self.AddProxyServer()
            
            return -1
        except Exception, e:
            print e
            print 'Exception'
            #
            # 改使用代理服务器请求
            #
            if self._is_proxy == False:
                self._is_proxy = True
                self.AddProxyServer()
            
            return -1

class PlayerParser(Parser):
    """球员数据解析"""
    def Parse(self, player_item):
        """解析请求到的HTML源代码"""
        while True:
            response = self.SendRequest()
            if response == None:
                return None
            #
            # 出现异常的时候更换代理服务器
            #
            if response == -1:
                continue
            #
            # 正常返回则跳出循环
            #
            break
        #
        # 解析球员基本信息
        #
        regex = re.compile(r'\<table class="player_base"(.*?)</table>', re.DOTALL)
        tables = regex.search(response)
        if not tables:
            return None

        table = tables.group(0)
        #
        # 解析tr标签
        #
        rows = re.findall(r"(?s)<td(.*?)</td>", table)
        item_index = 0
        for row in rows:
            #
            # 解析td标签
            #
            cells = re.findall(r'\<span id=(.*?)>(.*?)</span>', row)

            for cell in cells:
                key  = cell[0]
                val  = cell[1]
                
                if item_index == 0:
                    key = u"姓名"
                    player_item.name = val
                elif item_index == 1:
                    key = u"默认位置"
                    player_item.default_position = val
                elif item_index == 2:
                    key = u"综合值"
                    player_item.default_complex_value = val
                elif item_index == 3:
                    key = u"实况名"
                    player_item.we_name = val
                elif item_index == 4:
                    key = u"国家队位置"
                    player_item.country_position = val
                elif item_index == 5:
                    key = u"综合值"
                    player_item.country_complex_value = val
                elif item_index == 6:
                    key = u"国籍"
                    player_item.country = val
                elif item_index == 7:
                    key = u"俱乐部位置"
                    player_item.club_position = val
                elif item_index == 8:
                    key = u"综合值"
                    player_item.club_complex_value = val
                elif item_index == 9:
                    key = u"国家队"
                    player_item.country_team = val
                elif item_index == 10:
                    key = u"俱乐部队"
                    player_item.club = val
                elif item_index == 11:
                    key = u"生日"
                    player_item.birth = val
                elif item_index == 12:
                    key = u"星座"
                    player_item.constellation = val
                elif item_index == 13:
                    key = u"年龄"
                    player_item.age = val
                elif item_index == 14:
                    key = u"身高"
                    player_item.hight = val
                elif item_index == 15:
                    key = u"体重"
                    player_item.weight = val
                elif item_index == 16:
                    key = u"擅长边路"
                    player_item.favoured_side = val
                elif item_index == 17:
                    key = u"擅长脚"
                    player_item.foot = val

                print "%s: %s" % (key, val)

                item_index += 1
        #
        # 解析球员属性
        # TODO 球员适合位置暂时不解析
        #
        regex = re.compile(r'\<table class="abilities"(.*?)</table>', re.DOTALL)
        tables = regex.search(response)
        if not tables:
            return None

        table = tables.group(0)
        #
        # 解析tr标签
        #
        item_index = 0
        rows = re.findall(r'(?s)width="50">(.*?)</td>', table)
        for row in rows:
            key = ""
            val = str(row).strip()

            if item_index == 0:
                key = u"进攻"
                player_item.attack = val
            elif item_index == 1:
                key = u"射门力量"
                player_item.shot_power = val
            elif item_index == 2:
                key = u"防守"
                player_item.defend = val
            elif item_index == 3:
                key = u"射门技术"
                player_item.shot_skill = val
            elif item_index == 4:
                key = u"平衡"
                player_item.balance = val
            elif item_index == 5:
                key = u"任意球精度"
                player_item.free_kick_accuracy = val
            elif item_index == 6:
                key = u"体力"
                player_item.physical = val
            elif item_index == 7:
                key = u"弧度"
                player_item.radian = val
            elif item_index == 8:
                key = u"速度"
                player_item.speed = val
            elif item_index == 9:
                key = u"头球"
                player_item.header = val
            elif item_index == 10:
                key = u"加速"
                player_item.speed_up = val
            elif item_index == 11:
                key = u"弹跳"
                player_item.bounce = val
            elif item_index == 12:
                key = u"反应"
                player_item.reaction = val
            elif item_index == 13:
                key = u"技术"
                player_item.skill = val
            elif item_index == 14:
                key = u"敏捷"
                player_item.agile = val
            elif item_index == 15:
                key = u"进攻性"
                player_item.offensive = val
            elif item_index == 16:
                key = u"带球精度"
                player_item.precision_ball = val
            elif item_index == 17:
                key = u"精神"
                player_item.spirit = val
            elif item_index == 18:
                key = u"带球速度"
                player_item.ball_speed = val
            elif item_index == 19:
                key = u"守门技术"
                player_item.gk_skill = val
            elif item_index == 20:
                key = u"短传精度"
                player_item.short_pass_accuracy = val
            elif item_index == 21:
                key = u"配合"
                player_item.assort = val
            elif item_index == 22:
                key = u"短传速度"
                player_item.short_pass_speed = val
            elif item_index == 23:
                key = u"状态稳定度"
                player_item.state_stability = val
            elif item_index == 24:
                key = u"长传精度"
                player_item.long_pass_accuracy = val
            elif item_index == 25:
                key = u"逆足精度"
                player_item.weak_foot_accuracy = val
            elif item_index == 26:
                key = u"长传速度"
                player_item.long_pass_speed = val
            elif item_index == 27:
                key = u"逆足频度"
                player_item.weak_foot_frequency = val
            elif item_index == 28:
                key = u"射门精度"
                player_item.shot_accuracy = val
            elif item_index == 29:
                key = u"受伤"
                player_item.injured = val

            print "%s: %s" % (key, val)

            item_index += 1
        #
        # 解析球员卡片
        # TODO 球员适合位置暂时不解析
        #
        regex = re.compile(r'\<table class="PindexBox"(.*?)</table>', re.DOTALL)
        tables = regex.search(response)
        if not tables:
            return None

        table = tables.group(0)
        #
        # 解析tr标签
        #
        item_index = 0
        rows = re.findall(r'(?s)5px;">(.*?)</div>', table)
        skill = ""
        for row in rows:
            val = str(row).strip()
            skill += " "
            skill += val
        if skill == "":
            skill = u"无"
        player_item.special_ability = skill
        print u"特殊能力:%s" % skill

class TeamParser(Parser):
    """球队数据解析"""
    def Parse(self, team_item):
        while True:
            #response = self.SendRequest()
            file = open(self._url, "r")
            response = file.read()
            if response == None:
                return None
            #
            # 出现异常的时候更换代理服务器
            #
            if response == -1:
                continue
            #
            # 正常返回则跳出循环
            #
            break
        #
        # 解析球员基本信息
        #
        regex = re.compile(r'\<xptable(.*?)</xptable>', re.DOTALL)
        tables = regex.search(response)
        if not tables:
            return None

        table = tables.group(0)
        
        rows = re.findall(r'<td width="105"(?s)(.*?)</td>', table)
        for row in rows:
            if str(row).find("img") > 0:
                continue
            #
            # 解析td标签
            #
            cells = re.findall(r'(?s)<a href=(?s)(.*?)</a>', row)
            team_name = cells[0]
            team_name = team_name[team_name.find(">") + 1 :]
            team_name = self._tool.ConverToChinese(team_name)
            print team_name

        #
        # 解析球员属性
        # TODO 球员适合位置暂时不解析
        #
        regex = re.compile(r'\<table class="abilities"(.*?)</table>', re.DOTALL)
        tables = regex.search(response)
        if not tables:
            return None

        table = tables.group(0)
        #
        # 解析tr标签
        #
        item_index = 0
        rows = re.findall(r'(?s)width="50">(.*?)</td>', table)
        for row in rows:
            key = ""
            val = str(row).strip()

            print "%s: %s" % (key, val)

            item_index += 1
    

class ProxyServer:
    """代理服务器数据结构"""
    def __init__(self, proxy_url):
        self._server_address = proxy_url
        self._is_used = False
        
class PlayerParserThread():
    """球员爬虫线程"""
    def __init__(self):
        self._db_manager = DataBaseManager()
        
    def start(self):
        index = 11531
        start_time = time.time()
        while index <= 15000:
            try:
                request_url = "http://www.welovewe.com/player/player_cn.aspx?id=%d" % index
                player = PlayerParser(request_url)
                
                print "当前正在请求第 %d 条球员记录" % index
    
                player_item = PlayerItem()
                player.Parse(player_item)
                if len(player_item.name) > 0:
    #                download_url = "http://www.welovewe.com/showClubImg.aspx?id=%d" % self._player_index
    #                content = PlayerParser(download_url).SendRequest()
    #                file = open("face/%d" % index, "wb")
    #                file.write(content)
    #                file.close()
    #                index += 1

                    self._db_manager.AddPlayerItem(player_item)

                time.sleep(0.05)
                
                index += 1
            except Exception, ex:
                print "================= index:%d" % index
                print ex
                time.sleep(10)
                
        print "used time:%d" % (time.time() - start_time)
        
class TeamParserThread(threading.Thread):
    """球队爬虫线程"""
    def __init__(self):
        threading.Thread.__init__(self)
        self._db_manager  = DataBaseManager()
        
    def run(self):
        request_url = "D:\\team.html"#"http://www.welovewe.com/index.aspx"
        team = TeamParser(request_url)

        star_item = PlayerItem()
        if team.Parse(star_item) != None:
            self._db_manager.SaveStarInfo(star_item)
    
        time.sleep(0.1)
        
        self._player_index += 1
            
        self._db_manager.Close()