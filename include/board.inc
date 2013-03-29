<?php

abstract class Board {

  protected $elements = array();

  public function __construct() { }

  public function __destruct() { }

  final public function render() {
    foreach ($this->elements as $element) {
      $element->render();
    }
  }

  final public function add_element($element) {
    if (!($element instanceof BoardElement)) {
      throw new Exception('Argument "element" is not of type BoardElement');
    }
    array_push($this->elements, $element);
  }

}

?>
