<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

echo "方法一:\n";//挨个加入禁词;
$ac=acfilter_new();
var_dump($ac);
acfilter_add_word($ac,"北京");
acfilter_add_word($ac,"南京");
acfilter_prepare($ac);
var_dump(acfilter_check_text($ac,"我爱北京",1));
acfilter_close($ac);

//方法二:加载词库;
echo "\n\n方法二:\n";
$ac=acfilter_new();
acfilter_load_dict($ac,"./dict.txt");
acfilter_prepare($ac);
var_dump(acfilter_check_text($ac,"南京",1));
acfilter_close($ac);

