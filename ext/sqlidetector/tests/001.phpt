--TEST--
Check if is_sqli() returns true in presence of an SQL injection
--SKIPIF--
<?php if (!extension_loaded("sqlidetector")) print "skip"; ?>
--FILE--
<?php
if (is_sqli("-1' and 1=1 union/* foo */select load_file('/etc/passwd')--")) {
    echo "SQL injection found";
} else {
    echo "No SQL injection found";
}
--EXPECT--
SQL injection found
