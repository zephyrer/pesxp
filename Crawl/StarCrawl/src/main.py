# coding=utf-8
'''
Created on 2010-5-25

@author: 游枭
'''

import time, threading
from db_manager import DataBaseManager
from player_parser import PlayerParserThread, TeamParserThread
def main():
#    db_manager = DataBaseManager()
#    #
#    # 清空数据库数据
#    #
#    db_manager.InitializeTables()
    
    player_parser = PlayerParserThread()
    player_parser.start()
if __name__ == '__main__':
    main()
