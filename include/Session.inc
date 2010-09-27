<?php

class Session
{
    function __construct($gc_maxlifetime=1400, $salt="", $table="session_data", $gc_probability=1, $gc_divisor=100) {
        if ($gc_maxlifetime != "" && is_integer($gc_maxlifetime)) {

            // set the new value
            @ini_set('session.gc_maxlifetime', $gc_maxlifetime);

        }

        // if $gc_probability is specified and is an integer number
        if ($gc_probability != "" && is_integer($gc_probability)) {

            // set the new value
            @ini_set('session.gc_probability', $gc_probability);

        }

        // if $gc_divisor is specified and is an integer number
        if ($gc_divisor != "" && is_integer($gc_divisor)) {

            // set the new value
            @ini_set('session.gc_divisor', $gc_divisor);

        }

        // get session lifetime
        $this->gc_maxlifetime = ini_get("session.gc_maxlifetime");

        // we'll use this later on in order to try to prevent HTTP_USER_AGENT spoofing
        $this->salt = $salt;

        $this->table = $table;

        // register the new handler
        session_set_save_handler(
            array(&$this, 'open'),
            array(&$this, 'close'),
            array(&$this, 'read'),
            array(&$this, 'write'),
            array(&$this, 'destroy'),
            array(&$this, 'gc')
        );
        register_shutdown_function('session_write_close');

        // start the session
        session_start();

    }

    /**
     *  Deletes all data related to the session
     *
     *  @since 1.0.1
     *
     *  @return void
     */
    function stop() {

        $this->regenerate_id();

        session_unset();

        session_destroy();

    }

    /**
     *  Regenerates the session id.
     *
     *  <b>Call this method whenever you do a privilege change!</b>
     *
     *  @return void
     */
    function regenerate_id() {
        // saves the old session's id
        $old_id= session_id();

        // regenerates the id
        // this function will create a new session, with a new id and containing the data from the old session
        // but will not delete the old session
        session_regenerate_id();

        // because the session_regenerate_id() function does not delete the old session,
        // we have to delete it manually
        $this->destroy($old_id);
    }

    /**
     *  Get the number of online users
     *
     *  @return integer     number of users currently online
     */
    function get_users_online() {

        // call the garbage collector
        $this->gc($this->gc_maxlifetime);

        // counts the rows from the database
        $result = @mysql_fetch_assoc(@mysql_query("

            SELECT
                COUNT(session_id) as count
            FROM " . $this->table . "

        "));

        // return the number of found rows
        return $result["count"];

    }

    /**
     *  Custom open() function
     *
     *  @access private
     */
    function open($save_path, $session_name) {
        return true;
    }

    /**
     *  Custom close() function
     *
     *  @access private
     */
    function close() {
        return true;
    }


    /**
     *  Custom read() function
     *
     *  @access private
     */
    function read($session_id) {
        // reads session data associated with the session id
        // but only
        // - if the HTTP_USER_AGENT is the same as the one who had previously written to this session AND
        // - if session has not expired
        $result = @mysql_query("
            SELECT
                session_data
            FROM
                " . $this->table . "
            WHERE
                session_id = '".mysql_real_escape_string($session_id)."' AND
                http_user_agent = '".mysql_real_escape_string(md5($_SERVER["HTTP_USER_AGENT"] . $this->salt))."' AND
                session_expire > '".time()."'
            LIMIT 1
        ");

        // if anything was found
        if (is_resource($result) && @mysql_num_rows($result) > 0) {

            // return found data
            $fields = @mysql_fetch_assoc($result);
            // don't bother with the unserialization - PHP handles this automatically
            return $fields["session_data"];

        }

        // if there was an error return an empty string - this HAS to be an empty string
        return "";

    }


    /**
     *  Custom write() function
     *
     *  @access private
     */
    function write($session_id, $session_data) {
        // insert OR update session's data - this is how it works:
        // first it tries to insert a new row in the database BUT if session_id is already in the database then just
        // update session_data and session_expire for that specific session_id
        // read more here http://dev.mysql.com/doc/refman/4.1/en/insert-on-duplicate.html
        $result = @mysql_query("
            INSERT INTO
                " . $this->table . " (
                    session_id,
                    http_user_agent,
                    session_data,
                    session_expire
                )
            VALUES (
                '".mysql_real_escape_string($session_id)."',
                '".mysql_real_escape_string(md5($_SERVER["HTTP_USER_AGENT"] . $this->salt))."',
                '".mysql_real_escape_string($session_data)."',
                '".mysql_real_escape_string(time() + $this->gc_maxlifetime)."'
            )
            ON DUPLICATE KEY UPDATE
                session_data = '".mysql_real_escape_string($session_data)."',
                session_expire = '".mysql_real_escape_string(time() + $this->gc_maxlifetime)."'
        ");

        // if anything happened
        if ($result) {

            // note that after this type of queries, mysql_affected_rows() returns
            // - 1 if the row was inserted
            // - 2 if the row was updated

            // if the row was updated
            if (@mysql_affected_rows() > 1) {

                // return TRUE
                return true;

            // if the row was inserted
            } else {

                // return an empty string
                return "";

            }

        }

        // if something went wrong, return false
        return false;

    }


    /**
     *  Custom destroy() function
     *
     *  @access private
     */
    function destroy($session_id) {
        // deletes the current session id from the database
        $result = @mysql_query("
            DELETE FROM
                " . $this->table . "
            WHERE
                session_id = '".mysql_real_escape_string($session_id)."'
        ");

        // if anything happened
        if (@mysql_affected_rows()) {

            // return true
            return true;

        }

        // if something went wrong, return false
        return false;

    }

    /**
     *  Custom gc() function (garbage collector)
     *
     *  @access private
     */
    function gc($maxlifetime) {
        // it deletes expired sessions from database
        $result = @mysql_query("
            DELETE FROM
                " . $this->table . "
            WHERE
                session_expire < '".mysql_real_escape_string(time() - $maxlifetime)."'
        ");
    }
}
?>
