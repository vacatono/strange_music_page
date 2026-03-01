<?php
require("./qrcode_img.php");
//require("../pdftest/writepdf.inc");
//Header("Content-type: image/png");
//Header("Content-type: image/jpeg");

$data="$_POST[nam]";
//$data="01234567";

$z=new Qrcode_image;

#$z->set_qrcode_version(1);           # set qrcode version 1
#$z->set_qrcode_error_correct("H");   # set ecc level H
#$z->set_module_size(3);              # set module size 3pixel
#$z->set_quietzone(5);                # set quietzone width 5 modules

// RANDOM KEY GENERATOR


 $prefix = 'qrcode'; // a universal prefix prefix
 $my_random_id = $prefix;
 $my_random_id .= chr(rand(65,90));
 $my_random_id .= time();
 $my_rancom_id .= uniqid($prefix);


//$z->qrcode_image_out($data,"png","$my_random_id.png");

$z->qrcode_image_out($data,"jpeg","img/$my_random_id.jpg");
if($z)
{
header("Location: http://hyoga.japal.co.jp/~saroj/pdftest/samplephp/pdf_test.php?name=$my_random_id");
}
#$z->image_out($z->cal_qrcode($data),"png");   #old style

?>
