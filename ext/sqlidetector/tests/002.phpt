--TEST--
Check if is_sqli() returns false in case no SQL injection is found
--SKIPIF--
<?php if (!extension_loaded("sqlidetector")) print "skip"; ?>
--FILE--
<?php
if (is_sqli("SELECT * from users;")) {
    echo "SQL injection found";
} else {
    echo "No SQL injection found";
}
--EXPECT--
No SQL injection found
