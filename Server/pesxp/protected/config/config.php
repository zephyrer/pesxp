<?php
/*
 * 配置文件
 */

//
// 数据库连接
//
define('DB_HOST', '127.0.0.1');
//
// 数据库连接
//
define('DB_USER', 'miniyun');
//
// 数据库密码
//
define('DB_PASSWORD', 'miniyun');
//
// 数据库名
//
define('DB_NAME', 'pesxp');

//
// 数据库端口
//
define('DB_PORT', '3306');
//
// 定义数据库表前缀
//
define('DB_PREFIX', 'pesxp_');

define('UC_CONNECT', NUll);                  // 连接 UCenter 的方式: mysql/NULL, 默认为空时为 fscoketopen()
                                                // mysql 是直接连接的数据库, 为了效率, 建议采用 mysql
//数据库相关 (mysql 连接时, 并且没有设置 UC_DBLINK 时, 需要配置以下变量)
define('UC_DBHOST', 'localhost');                // UCenter 数据库主机
define('UC_DBUSER', 'root');                     // UCenter 数据库用户名
define('UC_DBPW', '');                           // UCenter 数据库密码
define('UC_DBNAME', '027xfbbs');                 // UCenter 数据库名称
define('UC_DBCHARSET', 'utf8');                  // UCenter 数据库字符集
define('UC_DBTABLEPRE', '027xfbbs.uc_');         // UCenter 数据库表前缀

//通信相关
define('UC_KEY', 'ec4aiAyHxQ3Ugkx9v8iXo4W0SDLMQPwJ0eWIl20');// 与 UCenter 的通信密钥, 要与 UCenter 保持一致
define('UC_API', 'http://bbs.pesxp.cn/uc_server');    // UCenter 的 URL 地址, 在调用头像时依赖此常量
define('UC_CHARSET', 'utf8');                     // UCenter 的字符集
define('UC_IP', '');                              // UCenter 的 IP, 当 UC_CONNECT 为非 mysql 方式时, 并且当前应用服务器解析域名有问题时, 请设置此值
define('UC_APPID', 2);                            // 当前应用的 ID