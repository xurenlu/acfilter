#! /Applications/XAMPP/xamppfiles/bin/php
<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

echo "方法一:\n";//挨个加入禁词;
$ac=acfilter_new();
var_dump($ac);
acfilter_add_word($ac,"河边");
acfilter_add_word($ac,"曾经");
acfilter_add_word($ac,"徐仁禄");
acfilter_prepare($ac);
print_r(acfilter_check_text($ac,"曾|经有部门叫河边本扩展的作者是徐|}仁||=fd8禄",0));
print "\n";
print_r(acfilter_check_text($ac,"曾|经有部门叫河边本扩展的作者是徐|}仁||=fd8禄",2));
print "\n";
print_r(acfilter_check_text($ac,"曾|经有部门叫河边本扩展的作者是徐|}仁||=fd8禄",8));
print "\n";
acfilter_close($ac);

exit();
//方法二:加载词库;
echo "\n\n方法二:\n";
$ac=acfilter_new();
acfilter_load_dict($ac,"./dict.txt");
acfilter_prepare($ac);
print_r(acfilter_check_text($ac,"曾经有一个叫工信部"));
acfilter_close($ac);

?>
