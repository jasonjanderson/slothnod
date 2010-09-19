<?php
class Pagination {
  private $connection;
  private $sql;
  private $rows_per_page;
  private $num_adjacent;
  private $page_url_name;
  private $page;
  private $url_base;
  private $total_rows;
  private $debug = false;
  private $max_pages;
  private $offset;
  private $url_parameters;

  public function __construct($connection, $sql, $rows_per_page=10, $num_adjacent=5, $page_url_name='p', $url_base='./') {
    $this->connection = $connection;
    $this->sql = $sql;
    $this->rows_per_page = (int)$rows_per_page;
    $this->num_adjacent = (int)$num_adjacent;
    $this->page_url_name = $page_url_name;
    $this->url_base = $url_base;

    $this->url_parameters = $this->get_url_parameter_string();

    if (isset($_GET[$this->page_url_name])) {
      $this->page = (int)$_GET[$this->page_url_name];
    } else {
      $this->page = 1;
    }

    if (!$this->connection || ! is_resource($this->connection)) {
      if ($this->debug) {
        echo "MySQL Connection missing<br />";
      }
      return;
    }

    $result_all = @mysql_query($this->sql);
    if (!$result_all) {
      if ($this->debug)
        echo "SQL query failed. Check your query.<br /><br />Error Returned: " . mysql_error();
      return;
    }

    $this->total_rows = mysql_num_rows($result_all);
    $this->max_pages = ceil($this->total_rows / $this->rows_per_page);
    $this->offset = $this->rows_per_page * ($this->page - 1);
    $this->result = @mysql_query($this->sql . " LIMIT {$this->offset}, {$this->rows_per_page}");

    if (!$this->result) {
      if ($this->debug)
        echo "SQL query failed. Check query.<br /><br />Error Returned: " . mysql_error();
      return;
    }
  }

  public function __destruct() {

  }


  public function get_result() {
    return $this->result;
  }


  private function render_link($title, $link) {
    return '<a href="' . $link . '">' . $title . '</a>';
  }


  private function render_element($content, $css_class=NULL) {
    if (isset($css_class)) {
      return '<li class="' . $css_class . '">' . $content . '</li>';
    }
    return '<li>' . $content . '</li>';
  }

  private function get_url_string($page) {
    return $this->url_base . '?' . $this->page_url_name . '=' . $page . $this->url_parameters;
  }

  private function get_url_parameter_string() {
    $url_string = '';
    foreach ($_GET as $k => $v) {
      if (!$k == $this->page_url_name) {
        $url_string .= '&' . $k . '=' . urlencode($v);
      }
    }
    return $url_string;
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
      return $this->render_element(
        $content=$title,
        $css_class=$css_class_disabled
      );
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
      return $this->render_element(
        $content=$title,
        $css_class=$css_class_disabled
      );
    }
  }

  public function render_page_number($num, $current, $css_class=NULL) {
    if ($current) {
      return $this->render_element(
        $content=$num,
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

  public function render_navigation($css_class=NULL, $css_class_current=NULL) {
    if ($this->total_rows == 0)
      return FALSE;

    $nav = '';
    if ($this->max_pages <= (($this->num_adjacent * 4) + 1)) {
      for ($i = 1; $i <= $this->max_pages; $i++) {
        if ($i == $this->page) {
          $nav .= $this->render_page_number($num=$i, $current=TRUE, $css_class_current);
        } else {
          $nav .= $this->render_page_number($num=$i, $current=FALSE, $css_class);
        }
      }
      return $nav;
    } 

    for ($i = 1; $i <= $this->num_adjacent; $i++) {
      if ($i == $this->page) {
        $nav .= $this->render_page_number($num=$i, $current=TRUE, $css_class_current);
      } else {
        $nav .= $this->render_page_number($num=$i, $current=FALSE, $css_class);
      }
    }


    if ($this->page > (($this->num_adjacent * 2) + 1)) {
      $nav .= $this->render_element($content='...', $css_class=$css_class);
    } else {
      for ($i = ($this->num_adjacent + 1); $i <= ($this->num_adjacent * 3) + 1; $i++) {
        if ($i == $this->page) {
          $nav .= $this->render_page_number($num=$i, $current=TRUE, $css_class_current);
        } else {
          $nav .= $this->render_page_number($num=$i, $current=FALSE, $css_class);
        }
      }
    }

    if ($this->page > (($this->num_adjacent * 2) + 1) && $this->page <= ($this->max_pages - (($this->num_adjacent * 2) + 1))) {
      for ($i = ($this->page - $this->num_adjacent); $i <= ($this->page + $this->num_adjacent); $i++) {
        if ($i == $this->page) {
          $nav .= $this->render_page_number($num=$i, $current=TRUE, $css_class_current);
        } else {
          $nav .= $this->render_page_number($num=$i, $current=FALSE, $css_class);
        }
      }
    }
   

    if ($this->page <= ($this->max_pages - (($this->num_adjacent * 2) + 1))) {
      $nav .= $this->render_element($content='...', $css_class=$css_class);
    } else {
      for ($i = $this->max_pages - ($this->num_adjacent * 3); $i <= ($this->max_pages - $this->num_adjacent); $i++) {
        if ($i == $this->page) {
          $nav .= $this->render_page_number($num=$i, $current=TRUE, $css_class_current);
        } else {
          $nav .= $this->render_page_number($num=$i, $current=FALSE, $css_class);
        }
      }
    }
 


    for ($i = ($this->max_pages - $this->num_adjacent + 1); $i <= $this->max_pages; $i++) {
      if ($i == $this->page) {
        $nav .= $this->render_page_number($num=$i, $current=TRUE, $css_class_current);
      } else {
        $nav .= $this->render_page_number($num=$i, $current=FALSE, $css_class);
      }
    }

    return $nav;
  }


  public function render_full(
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
        . $this->render_navigation($css_class_current=$css_class_current)
        . $this->render_next('Next', $css_class_enabled=$css_class_next_enabled, $css_class_disabled=$css_class_next_disabled)
        . $this->render_last('Last', $css_class_enabled=$css_class_last_enabled, $css_class_disabled=$css_class_last_disabled);
  }


  public function render(
    $css_class_previous_enabled=NULL,
    $css_class_previous_disabled=NULL,
    $css_class_current=NULL,
    $css_class_next_enabled=NULL,
    $css_class_next_disabled=NULL) {

      return $this->render_previous('Previous', $css_class_enabled=$css_class_previous_enabled, $css_class_disabled=$css_class_previous_disabled)
        . $this->render_navigation($css_class=NULL, $css_class_current=$css_class_current)
        . $this->render_next('Next', $css_class_enabled=$css_class_next_enabled, $css_class_disabled=$css_class_next_disabled);
  }


  /**
  * Set debug mode
  *
  * @access public
  * @param bool $debug Set to TRUE to enable debug messages
  * @return void
  */
  function setDebug($debug) {
    $this->debug = $debug;
  }
}
?>
