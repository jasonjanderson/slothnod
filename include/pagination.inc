<?php

class Pagination {
  private $rows_per_page;
  private $page;
  private $url_base;
  private $total_rows;
  private $debug = false;
  private $max_pages;
  private $offset;

  public function __construct($page=1, $total_rows, $rows_per_page=10, $url_base='') {
    $this->max_pages = ceil($total_rows / $rows_per_page);
    if ($this->max_pages != 0 && (!is_numeric($page) || 0 > $page ||  $page > $this->max_pages)) {
      if ($url_base == '') {
        URL::redirect('/');
        exit;
      }
      URL::redirect($url_base);
      exit;
    }
    $this->page = $page;
    $this->total_rows = (int)$total_rows;
    $this->rows_per_page = (int)$rows_per_page;
    $this->url_base = $url_base;

    $this->max_pages = ceil($this->total_rows / $this->rows_per_page);
    $this->offset = $this->rows_per_page * ($this->page - 1);
  }

  public function __destruct() { }


  private function render_link($title, $link, $css_class=NULL) {
    if (isset($css_class)) {
      return '<a class="' . $css_class . '" href="' . $link . '">' . $title . '</a>';
    }
    return '<a href="' . $link . '">' . $title . '</a>';
  }


  private function render_element($content, $css_class=NULL) {
    if (isset($css_class)) {
      return '<li class="' . $css_class . '">' . $content . '</li>';
    }
    return '<li>' . $content . '</li>';
  }

  private function get_url_string($page) {
    return $this->url_base . '/' . $page;
  }


  public function render_first($title, $css_class_enabled=NULL, $css_class_disabled=NULL) {
    if ($this->total_rows == 0)
      return FALSE;

    if ($this->page == 1) {
      return $this->render_element(
        $content=$title,
        $css_class=$css_class_disabled
      );
    } else {
      return $this->render_element(
        $content=$this->render_link($title=$title,
          $link=$this->get_url_string('1')
        ),
        $css_class=$css_class_enabled
      );
    }
  }

  public function render_last($title, $css_class_enabled=NULL, $css_class_disabled=NULL) {
    if ($this->total_rows == 0)
      return FALSE;

    if ($this->page == $this->max_pages) {
      return $this->render_element(
        $content=$title,
        $css_class=$css_class_disabled
      );
    } else {
      return $this->render_element(
        $content=$this->render_link($title=$title,
          $link=$this->get_url_string($this->max_pages)
        ),
        $css_class=$css_class_enabled
      );
    }
  }

  public function render_next($title, $css_class_enabled=NULL, $css_class_disabled=NULL) {
    if ($this->total_rows == 0)
      return FALSE;
    
    if ($this->page < $this->max_pages) {
      return $this->render_element(
        $content=$this->render_link($title=$title,
          $link=$this->get_url_string($this->page + 1)
        ),
        $css_class=$css_class_enabled
      );
    } else {
      /*
      return $this->render_element(
        $content=$title,
        $css_class=$css_class_disabled
      );
       */
    }
  }


  public function render_previous($title, $css_class_enabled=NULL, $css_class_disabled=NULL) {
    if ($this->total_rows == 0)
      return FALSE;
    
    if ($this->page > 1) {
      return $this->render_element(
        $content=$this->render_link($title=$title,
          $link=$this->get_url_string($this->page - 1)
        ),
        $css_class=$css_class_enabled
      );
    } else {
      /*
      return $this->render_element(
        $content=$title,
        $css_class=$css_class_disabled
      );
       */
    }
  }

  public function render_page_number($num, $current, $css_class=NULL) {
    if ($current) {
      return $this->render_element(
        $content=$this->render_link($title=$num,
          $link=$this->get_url_string($num),
          $css_class=$css_class
        ),
        $css_class=$css_class
      );

    } else {
      return $this->render_element(
        $content=$this->render_link($title=$num,
          $link=$this->get_url_string($num)
        ),
        $css_class=$css_class
      );
   }
  }

  public function render_navigation($num_adjacent=3, $css_class=NULL, $css_class_current=NULL) {
    if ($this->total_rows == 0)
      return FALSE;

    $nav = '';
    if ($this->max_pages <= (($num_adjacent * 4) + 1)) {
      for ($i = 1; $i <= $this->max_pages; $i++) {
        if ($i == $this->page) {
          $nav .= $this->render_page_number($num=$i, $current=TRUE, $css_class_current);
        } else {
          $nav .= $this->render_page_number($num=$i, $current=FALSE, $css_class);
        }
      }
      return $nav;
    } 

    for ($i = 1; $i <= $num_adjacent; $i++) {
      if ($i == $this->page) {
        $nav .= $this->render_page_number($num=$i, $current=TRUE, $css_class_current);
      } else {
        $nav .= $this->render_page_number($num=$i, $current=FALSE, $css_class);
      }
    }


    if ($this->page > (($num_adjacent * 2) + 1)) {
     // $nav .= $this->render_element($content='...', $current=TRUE, $css_class=$css_class);
      $nav .= '<li><a class="active" href="#">...</a></li>';
    } else {
      for ($i = ($num_adjacent + 1); $i <= ($num_adjacent * 3) + 1; $i++) {
        if ($i == $this->page) {
          $nav .= $this->render_page_number($num=$i, $current=TRUE, $css_class_current);
        } else {
          $nav .= $this->render_page_number($num=$i, $current=FALSE, $css_class);
        }
      }
    }

    if ($this->page > (($num_adjacent * 2) + 1) && $this->page <= ($this->max_pages - (($num_adjacent * 2) + 1))) {
      for ($i = ($this->page - $num_adjacent); $i <= ($this->page + $num_adjacent); $i++) {
        if ($i == $this->page) {
          $nav .= $this->render_page_number($num=$i, $current=TRUE, $css_class_current);
        } else {
          $nav .= $this->render_page_number($num=$i, $current=FALSE, $css_class);
        }
      }
    }
   

    if ($this->page <= ($this->max_pages - (($num_adjacent * 2) + 1))) {
     // $nav .= $this->render_element($content='...', $current=TRUE, $css_class=$css_class);
      $nav .= '<li><a class="active" href="#">...</a></li>';
    } else {
      for ($i = $this->max_pages - ($num_adjacent * 3); $i <= ($this->max_pages - $num_adjacent); $i++) {
        if ($i == $this->page) {
          $nav .= $this->render_page_number($num=$i, $current=TRUE, $css_class_current);
        } else {
          $nav .= $this->render_page_number($num=$i, $current=FALSE, $css_class);
        }
      }
    }
 

    for ($i = ($this->max_pages - $num_adjacent + 1); $i <= $this->max_pages; $i++) {
      if ($i == $this->page) {
        $nav .= $this->render_page_number($num=$i, $current=TRUE, $css_class_current);
      } else {
        $nav .= $this->render_page_number($num=$i, $current=FALSE, $css_class);
      }
    }

    return $nav;
  }


  public function render_full(
    $num_adjacent=3,
    $css_class_first_enabled=NULL, 
    $css_class_first_disabled=NULL,
    $css_class_previous_enabled=NULL,
    $css_class_previous_disabled=NULL,
    $css_class_current=NULL,
    $css_class_next_enabled=NULL,
    $css_class_next_disabled=NULL,
    $css_class_last_enabled=NULL,
    $css_class_last_disabled=NULL) {

      return $this->render_first('First', $css_class_enabled=$css_class_first_enabled, $css_class_disabled=$css_class_first_disabled) 
        . $this->render_previous('Previous', $css_class_enabled=$css_class_previous_enabled, $css_class_disabled=$css_class_previous_disabled)
        . $this->render_navigation($num_adjacent=$num_adjacent, $css_class_current=$css_class_current)
        . $this->render_next('Next', $css_class_enabled=$css_class_next_enabled, $css_class_disabled=$css_class_next_disabled)
        . $this->render_last('Last', $css_class_enabled=$css_class_last_enabled, $css_class_disabled=$css_class_last_disabled);
  }


  public function render(
    $num_adjacent=3,
    $css_class_previous_enabled=NULL,
    $css_class_previous_disabled=NULL,
    $css_class_current=NULL,
    $css_class_next_enabled=NULL,
    $css_class_next_disabled=NULL) {
      if ($this->max_pages <= 1) {
        return '';
      }

      return $this->render_previous('Back', $css_class_enabled=$css_class_previous_enabled, $css_class_disabled=$css_class_previous_disabled)
        . $this->render_navigation($num_adjacent=$num_adjacent, $css_class=NULL, $css_class_current=$css_class_current)
        . $this->render_next('Next', $css_class_enabled=$css_class_next_enabled, $css_class_disabled=$css_class_next_disabled);
  }


  public function get_limit_clause() {
    return 'LIMIT ' . (int)$this->offset . ', ' . (int)$this->rows_per_page;
  }

}

?>
