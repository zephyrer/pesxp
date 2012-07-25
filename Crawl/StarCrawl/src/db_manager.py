# coding=utf-8
# 版权所有 2010南京恒为网络科技有限公司
#
# 管理所有的数据库操作
#

import sqlite3, time
import traceback

class DataBaseManager:
    def __init__(self):       
        self._conn              = sqlite3.connect("pesxp.db")
        self._conn.text_factory = str 
        self._conn.row_factory  = self.dict_factory
        self._cursor            = self._conn.cursor()

    def dict_factory(self, cursor, row):
        """优化sqlite3.row类型，使获取的数据保护字段列表名称"""
        d = {}
        for idx, col in enumerate(cursor.description):
            d[col[0]] = row[idx]
        return d

    def GetCursor(self):
        """ 获取数据库连接的游标 """
        return self._cursor
        
    def Close(self):
        """ 关闭数据库 """
        self._conn.close()
        
    def InitializeTables(self, build_init=False):
        """ 对数据库进行所有的初始化操作 """
        try:
            cur = self._conn.cursor()

#            str_continents_sql = """
#                -- 删除老表
#                DROP TABLE IF EXISTS continents;
#                
#                -- 创建新的表字段
#                CREATE TABLE continents(
#                    id integer primary key,
#                    name NVARCHAR(32) NOT NULL
#                    );
#                """
#            cur.executescript(str_continents_sql)

#            str_teams_sql = """
#                -- 删除老表
#                DROP TABLE IF EXISTS teams;
#                
#                -- 创建新的表字段
#                CREATE TABLE teams(
#                    id integer primary key,
#                    continent_id integer DEFAULT 0 NOT NULL,
#                    name NVARCHAR(32) NOT NULL
#                    );
#                """
#            cur.executescript(str_teams_sql)

            str_players_sql = """
                -- 删除老表
                DROP TABLE IF EXISTS players;
                
                -- 创建新的表字段
                CREATE TABLE players(
                    id integer primary key,
                    team_id integer DEFAULT 0 NOT NULL,
                    name NVARCHAR(32) NOT NULL,
                    default_position NVARCHAR(8) NOT NULL,
                    default_complex_value integer DEFAULT 0 NOT NULL,
                    we_name NVARCHAR(32) NOT NULL,
                    country_position NVARCHAR(8) NOT NULL,
                    country_complex_value integer DEFAULT 0 NOT NULL,
                    country NVARCHAR(16) NOT NULL,
                    club_position NVARCHAR(8) NOT NULL,
                    club_complex_value integer DEFAULT 0 NOT NULL,
                    country_team NVARCHAR(16) NOT NULL,
                    club NVARCHAR(16) NOT NULL,
                    birth NVARCHAR(8) NOT NULL,
                    constellation NVARCHAR(8) NOT NULL,
                    age integer DEFAULT 0 NOT NULL,
                    hight integer DEFAULT 0 NOT NULL,
                    weight integer DEFAULT 0 NOT NULL,
                    favoured_side NVARCHAR(16) NOT NULL,
                    foot NVARCHAR(8) NOT NULL,
                    attack integer DEFAULT 0 NOT NULL,
                    shot_power integer DEFAULT 0 NOT NULL,
                    defend integer DEFAULT 0 NOT NULL,
                    shot_skill integer DEFAULT 0 NOT NULL,
                    balance integer DEFAULT 0 NOT NULL,
                    free_kick_accuracy integer DEFAULT 0 NOT NULL,
                    physical integer DEFAULT 0 NOT NULL,
                    radian integer DEFAULT 0 NOT NULL,
                    speed integer DEFAULT 0 NOT NULL,
                    header integer DEFAULT 0 NOT NULL,
                    speed_up integer DEFAULT 0 NOT NULL,
                    bounce integer DEFAULT 0 NOT NULL,
                    reaction integer DEFAULT 0 NOT NULL,
                    skill integer DEFAULT 0 NOT NULL,
                    agile integer DEFAULT 0 NOT NULL,
                    offensive integer DEFAULT 0 NOT NULL,
                    precision_ball integer DEFAULT 0 NOT NULL,
                    spirit integer DEFAULT 0 NOT NULL,
                    ball_speed integer DEFAULT 0 NOT NULL,
                    gk_skill integer DEFAULT 0 NOT NULL,
                    short_pass_accuracy integer DEFAULT 0 NOT NULL,
                    assort integer DEFAULT 0 NOT NULL,
                    short_pass_speed integer DEFAULT 0 NOT NULL,
                    state_stability integer DEFAULT 0 NOT NULL,
                    long_pass_accuracy integer DEFAULT 0 NOT NULL,
                    weak_foot_accuracy integer DEFAULT 0 NOT NULL,
                    long_pass_speed integer DEFAULT 0 NOT NULL,
                    weak_foot_frequency integer DEFAULT 0 NOT NULL,
                    shot_accuracy integer DEFAULT 0 NOT NULL,
                    injured integer DEFAULT 0 NOT NULL,
                    special_ability NVARCHAR(64) NOT NULL
                    );
                """
            cur.executescript(str_players_sql)

        except Exception, ex:
            return None

    def Commit(self, str_sql, str_params = None):
        try:
            if str_params == None:
                self._cursor.execute(str_sql)
            else:
                self._cursor.execute(str_sql, str_params)
            self._conn.commit()
            
        except Exception, ex:
            raise ex

        
    def AddPlayerItem(self, player_item):
        """ 将新产生的事件保存到数据库 """
        try:
            str_params  = {}
            str_sql = """insert into players(team_id,name,default_position,default_complex_value,we_name,country_position,country_complex_value,country,club_position,club_complex_value,country_team,club,birth,constellation,age,hight,weight,favoured_side,foot,attack,shot_power,defend,shot_skill,balance,free_kick_accuracy,physical,radian,speed,header,speed_up,bounce,reaction,skill,agile,offensive,precision_ball,spirit,ball_speed,gk_skill,short_pass_accuracy,assort,short_pass_speed,state_stability,long_pass_accuracy,weak_foot_accuracy,long_pass_speed,weak_foot_frequency,shot_accuracy,injured,special_ability) 
                values (:team_id, :name, :default_position, :default_complex_value, :we_name, :country_position, :country_complex_value, :country, :club_position, :club_complex_value, :country_team, :club, :birth, :constellation, :age, :hight, :weight, :favoured_side, :foot, :attack, :shot_power, :defend, :shot_skill, :balance, :free_kick_accuracy, :physical, :radian, :speed, :header, :speed_up, :bounce, :reaction, :skill, :agile, :offensive, :precision_ball, :spirit, :ball_speed, :gk_skill, :short_pass_accuracy, :assort, :short_pass_speed, :state_stability, :long_pass_accuracy, :weak_foot_accuracy, :long_pass_speed, :weak_foot_frequency, :shot_accuracy, :injured, :special_ability)"""
            str_params['team_id'] = player_item.team_id
            str_params['name'] = player_item.name
            str_params['default_position'] = player_item.default_position
            str_params['default_complex_value'] = player_item.default_complex_value
            str_params['we_name'] = player_item.we_name
            str_params['country_position'] = player_item.country_position
            str_params['country_complex_value'] = player_item.country_complex_value
            str_params['country'] = player_item.country
            str_params['club_position'] = player_item.club_position
            str_params['club_complex_value'] = player_item.club_complex_value
            str_params['country_team'] = player_item.country_team
            str_params['club'] = player_item.club
            str_params['birth'] = player_item.birth
            str_params['constellation'] = player_item.constellation
            str_params['age'] = player_item.age
            str_params['hight'] = player_item.hight
            str_params['weight'] = player_item.weight
            str_params['favoured_side'] = player_item.favoured_side
            str_params['foot'] = player_item.foot
            str_params['attack'] = player_item.attack
            str_params['shot_power'] = player_item.shot_power
            str_params['defend'] = player_item.defend
            str_params['shot_skill'] = player_item.shot_skill
            str_params['balance'] = player_item.balance
            str_params['free_kick_accuracy'] = player_item.free_kick_accuracy
            str_params['physical'] = player_item.physical
            str_params['radian'] = player_item.radian
            str_params['speed'] = player_item.speed
            str_params['header'] = player_item.header
            str_params['speed_up'] = player_item.speed_up
            str_params['bounce'] = player_item.bounce
            str_params['reaction'] = player_item.reaction
            str_params['skill'] = player_item.skill
            str_params['agile'] = player_item.agile
            str_params['offensive'] = player_item.offensive
            str_params['precision_ball'] = player_item.precision_ball
            str_params['spirit'] = player_item.spirit
            str_params['ball_speed'] = player_item.ball_speed
            str_params['gk_skill'] = player_item.gk_skill
            str_params['short_pass_accuracy'] = player_item.short_pass_accuracy
            str_params['assort'] = player_item.assort
            str_params['short_pass_speed'] = player_item.short_pass_speed
            str_params['state_stability'] = player_item.state_stability
            str_params['long_pass_accuracy'] = player_item.long_pass_accuracy
            str_params['weak_foot_accuracy'] = player_item.weak_foot_accuracy
            str_params['long_pass_speed'] = player_item.long_pass_speed
            str_params['weak_foot_frequency'] = player_item.weak_foot_frequency
            str_params['shot_accuracy'] = player_item.shot_accuracy
            str_params['injured'] = player_item.injured
            str_params['special_ability'] = player_item.special_ability 
            self.Commit(str_sql, str_params)
        except Exception, ex:
            return None 

    def AddContinentItem(self, name):
        """ 将新产生的事件保存到数据库 """
        try:
            str_params  = {}
            str_sql = """insert into continents(name) 
                values (:name)"""
            str_params['name'] = name
            self.Commit(str_sql, str_params)
        except Exception, ex:
            return None 

    def AddTeamItem(self, continent_id ,name):
        """ 将新产生的事件保存到数据库 """
        try:
            str_params  = {}
            str_sql = """insert into teams(continent_id, name) 
                values (:continent_id, :name)"""
            str_params['continent_id'] = continent_id
            str_params['name'] = name
            self.Commit(str_sql, str_params)
        except Exception, ex:
            return None

if __name__ == '__main__':
    db_manager = DataBaseManager()
    db_manager.InitializeTables()
#    file = open(u"C:\\Users\\NesTa.xP\\Desktop\\pes2011球队列表.txt", "r")
#    teams = []
#    continents = []
#    continent_id = 0
#    for line in file.readlines():
#        if line.find(":") > -1:
#            line = line.replace(":\n", "")
#            continents.append(line)
#            continent_id += 1
#        else:
#            line = line.replace("\n", "")
#            line = line.decode("gbk")
#            line = line.strip()
#            teams.append(line)
#            db_manager.AddTeamItem(continent_id, line)
#    for team in teams:
#        print team