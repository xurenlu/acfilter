<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

$ac=acfilter_new();
var_dump($ac);
//acfilter_load_dict($ac,"/home/renlu/dict.txt");
acfilter_add_word($ac,"河边");
acfilter_prepare($ac);
var_dump(acfilter_check_text($ac,"我们一起来到河边"));
acfilter_close($ac);
//var_dump(array_experiments());
?>
