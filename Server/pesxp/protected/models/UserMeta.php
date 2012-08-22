<?php
/**
 * 
 * 用户模型
 * @author jimmy
 *
 */
class UserMeta extends CActiveRecord {
    /**
     * 
     * model入口
     * @param string $className
     */
    public static function model($className=__CLASS__)
    {
        return parent::model($className);
    }
    
    /**
     * (non-PHPdoc)
     * @see CActiveRecord::tableName()
     */
    public function tableName()
    {
        return DB_PREFIX .'users';
    }
    
    /**
     * 存储前的时间补全, 密码加密
     * @see CActiveRecord::beforeSave()
     */
    public function beforeSave()
    {
        if ($this->isNewRecord)
        {
            $this->created_at = new CDbExpression('NOW()');
        }
        $this->updated_at = new CDbExpression('NOW()');
        return true;
    }
}