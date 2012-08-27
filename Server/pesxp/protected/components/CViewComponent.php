<?php
/**
 * 
 * Enter description here ...
 * @author jimmy
 *
 */
class CViewComponent extends CWidget {
    public $view;
    public $params;
    /**
     * (non-PHPdoc)
     * @see CWidget::run()
     */
    public function run() {
        if (empty($this->params)) {
            $this->params =array();
        }
        $this->render($this->view, $this->params);
    }
}