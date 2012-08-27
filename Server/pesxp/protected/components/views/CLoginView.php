<div class="form">
<?php $form=$this->beginWidget('CActiveForm', array(
    'id'=>$id,
    'enableClientValidation'=>true,
    'clientOptions'=>array(
        'validateOnSubmit'=>true,
    ),
    'action' => Yii::app()->createUrl('site/login'),
)); ?>
<!--    <p class="note">Fields with <span class="required">*</span> are required.</p>-->
    <div class="row">
        <div class="login-p">
        <?php echo $form->labelEx($model,'username',array('class'=>'login-username')); ?>
        <?php echo $form->textField($model,'username',array('class'=>'login-username-input')); ?>
        </div>
<!--        <?php echo $form->error($model,'username'); ?>-->
    </div>
    <div class="clear"></div>
    <div class="row">
        <div class="login-p">
        <?php echo $form->labelEx($model,'password',array('class'=>'login-password')); ?>
        <?php echo $form->passwordField($model,'password',array('class'=>'login-password-input')); ?>
        </div>
<!--        <?php echo $form->error($model,'password'); ?>-->
    </div>
    <div class="clear"></div>
    <div class="row rememberMe">
        <?php echo $form->checkBox($model,'rememberMe'); ?>
        <?php echo $form->label($model,'rememberMe'); ?>
<!--        <?php echo $form->error($model,'rememberMe'); ?>-->
    </div>
    <div class="row buttons">
        <?php echo CHtml::submitButton('登录'); ?>
    </div>
<?php $this->endWidget(); ?>
</div><!-- form -->