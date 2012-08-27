<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta name="language" content="en" />
    <!-- blueprint CSS framework -->
    <link rel="stylesheet" type="text/css" href="<?php echo Yii::app()->request->baseUrl; ?>/css/screen.css" media="screen, projection" />
    <link rel="stylesheet" type="text/css" href="<?php echo Yii::app()->request->baseUrl; ?>/css/print.css" media="print" />
    <!--[if lt IE 8]>
    <link rel="stylesheet" type="text/css" href="<?php echo Yii::app()->request->baseUrl; ?>/css/ie.css" media="screen, projection" />
    <![endif]-->
    <link rel="stylesheet" type="text/css" href="<?php echo Yii::app()->request->baseUrl; ?>/css/main.css" />
    <link rel="stylesheet" type="text/css" href="<?php echo Yii::app()->request->baseUrl; ?>/css/form.css" />
    <link rel="stylesheet" type="text/css" href="<?php echo Yii::app()->request->baseUrl; ?>/css/style.css" />
    <title><?php echo CHtml::encode($this->pageTitle); ?></title>
</head>
<body>
<div class="container" id="page">
    <div id="header">
        <div id="logo">
        <span><?php echo CHtml::encode(Yii::app()->name); ?></span></div>
        <div class="login">
            <div class="login-user">
                <span>您好，欢迎您</span>
                <?php if (Yii::app()->user->isGuest) : // 未登录状态?>
                <a id="login" href="#" onclick='$("#dialog-login").dialog("open"); return false;'>登录</a>
                <a id="regist" href="#">注册</a>
                <?php else : // 登录状态?>
                <span><?php echo Yii::app()->user->name?></span>
                <?php endif;?>
            </div>
            <div class="user-link">
                <a>我的账号</a> | 
                <a>充 值</a> | 
                <a>提 款</a>
            </div>
        </div>
    </div><!-- header -->
    <div class="clear"></div>
    <div class="databanner"></div>
    <div id="mainmenu">
        <?php $this->widget('zii.widgets.CMenu',array(
            'items'=>array(
                array('label'=>'赛事日历', 'url'=>array('/site/index')),
                array('label'=>'赛事中心', 'url'=>array('/site/page', 'view'=>'about')),
                array('label'=>'Contact', 'url'=>array('/site/contact')),
                array('label'=>'Login', 'url'=>array('/site/login'), 'visible'=>Yii::app()->user->isGuest),
                array('label'=>'Logout ('.Yii::app()->user->name.')', 'url'=>array('/site/logout'), 'visible'=>!Yii::app()->user->isGuest)
            ),
        )); ?>
    </div><!-- mainmenu -->
    <?php if(isset($this->breadcrumbs)):?>
        <?php $this->widget('zii.widgets.CBreadcrumbs', array('links'=>$this->breadcrumbs,)); ?><!-- breadcrumbs -->
    <?php endif?>
<?php $this->beginWidget('zii.widgets.jui.CJuiDialog', array(
    'id'=>'dialog-login',
    // additional javascript options for the dialog plugin
    'options'=>array(
        'title'=>'登录',
        'autoOpen'=>false,
        'modal'=>true,
        'resizable'=>false,
        'width' =>400,
    ),
    'htmlOptions' => array(
    ),
));?>

<?php $this->widget('CViewComponent', array(
    'id'           => 'user-login',
    'view'         => 'CLoginView',
    'params'       => array(
        'model' => $this->loginModel,
        'id'      => 'user-login-layout',
    ),
)); ?>

<?php $this->endWidget('zii.widgets.jui.CJuiDialog');?>

    <?php echo $content; ?>
    
    <div class="clear"></div>
    <div id="footer">
        <p id="product">
        <a href="#">广告服务</a> - 
        <a href="#">关于我们</a> - 
        <a href="#">联系方式</a>
        </p>
        <span id="copyright">Copyright &copy; <?php echo date('Y'); ?> Pesxp.cn Team. All Rights Reserved.</span>
    </div><!-- footer -->
</div><!-- page -->
</body>
</html>
