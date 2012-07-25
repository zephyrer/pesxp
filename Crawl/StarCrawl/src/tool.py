# coding=utf-8
'''
Created on 2010-5-24

@author: 游枭
'''

class Tool:
    """ 管理系统内部的所有资源信息以及临界变量 """

    # =============================================
    # 唯一实例开始位置
    # =============================================
    class __impl:
        """ Implementation of the singleton interface """

    # storage for the instance reference
    __instance = None
    
    def __getattr__(self, attr):
        """ Delegate access to implementation """
        return getattr(self.__instance, attr)

    def __setattr__(self, attr, value):
        """ Delegate access to implementation """
        return setattr(self.__instance, attr, value)
    # =============================================
    # 唯一实例结束位置
    # =============================================
    

    def __init__(self):
        """ Create singleton instance """
        # Check whether we already have an instance
        if Tool.__instance is None:
            # Create and remember instance
            Tool.__instance          = Tool.__impl()
            
    def ConverToChinese(self, value):
        """ 将字符串转换成中文 """
        converted = False
        try:
            if isinstance(value, str):
                value = value.decode("gb2312", 'ignore').encode('utf-8')
                converted = True
        except Exception, ex:
            pass
            
        if converted:
            return value
    
        try:
            value = value.decode('gbk', 'ignore').encode('utf-8')
            converted = True
        except Exception, ex:
            pass
    
        return value
    
    def GetCnFirstLetter(self, str, codec = "UTF8"):
        """获得中文的首字母"""
        try:
            if codec != "GBK":
                if codec != "unicode":
                    str = str.decode(codec)
                    index = str.find("・")
                    if index > -1:
                        str = str[ : index]
                str = str.encode("GBK")
            
            if str < "\xb0\xa1" or str > "\xd7\xf9":
                #
                # 对于数字或字母返回他们的首字符
                #
                if str[0].isalnum():
                    return str[0]
                else:
                    return ""
            if str < "\xb0\xc4":
                return "a"
            if str < "\xb2\xc0":
                return "b"
            if str < "\xb4\xed":
                return "c"
            if str < "\xb6\xe9":
                return "d"
            if str < "\xb7\xa1":
                return "e"
            if str < "\xb8\xc0":
                return "f"
            if str < "\xb9\xfd":
                return "g"
            if str < "\xbb\xf6":
                return "h"
            if str < "\xbf\xa5":
                return "j"
            if str < "\xc0\xab":
                return "k"
            if str < "\xc2\xe7":
                return "l"
            if str < "\xc4\xc2":
                return "m"
            if str < "\xc5\xb5":
                return "n"
            if str < "\xc5\xbd":
                return "o"
            if str < "\xc6\xd9":
                return "p"
            if str < "\xc8\xba":
                return "q"
            if str < "\xc8\xf5":
                return "r"
            if str < "\xcb\xf9":
                return "s"
            if str < "\xcd\xd9":
                return "t"
            if str < "\xce\xf3":
                return "w"
            if str < "\xd1\x88":
                return "x"
            if str < "\xd4\xd0":
                return "y"
            if str < "\xd7\xf9":
                return "z"
            
        except Exception, ex:
            return ""

if __name__ == '__main__':
    tool = Tool()
    name = "周杰伦"
    print tool.GetCnFirstLetter(name)