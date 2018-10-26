<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('sqlidetector')) {
	dl('sqlidetector.' . PHP_SHLIB_SUFFIX);
}
$module = 'sqlidetector';
$functions = get_extension_funcs($module);
echo "Functions available in the test extension:$br\n";
foreach($functions as $func) {
    echo $func."$br\n";
}
echo "$br\n";

$strings = array(
    "Bob",
    "-1' and 1=1 union/* foo */select load_file('/etc/passwd')--",
    "75001"
);
foreach($strings as $str) {
    if(sqli_check($str)) {
        echo "\"$str\" contains an SQL injection\n";
    } else {
        echo "\"$str\" does not contain SQL injections\n";
    }
}

?>
