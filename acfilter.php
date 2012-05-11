<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

echo "方法一:\n";//挨个加入禁词;
$ac=acfilter_new();
var_dump($ac);
acfilter_add_word($ac,"河边");
acfilter_add_word($ac,"狗屎");
acfilter_add_word($ac,",");
acfilter_add_word($ac,"工信部");
acfilter_prepare($ac);
print_r(acfilter_check_text($ac,"曾经有一个很狗屎的部门,叫工信部,到河边自杀了"));
acfilter_close($ac);

//方法二:加载词库;
echo "\n\n方法二:\n";
$ac=acfilter_new();
acfilter_load_dict($ac,"./dict.txt");
acfilter_prepare($ac);
print_r(acfilter_check_text($ac,"曾经有一个很狗屎的部门,叫工信部,到河边自杀了"));
acfilter_close($ac);

?>
