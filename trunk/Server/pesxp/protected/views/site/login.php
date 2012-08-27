<?php echo $script;?>
<?php
$this->pageTitle=Yii::app()->name . ' - Login';
$this->breadcrumbs=array(
    'Login',
);
?>

<h1>Login</h1>

<p>Please fill out the following form with your login credentials:</p>
<?php $this->widget('CViewComponent', array(
    'id'           => 'user-login',
    'view'         => 'CLoginView',
    'params'       => array(
        'model' => $this->loginModel,
        'id'    => 'user-login-view'
    ),
)); ?>
