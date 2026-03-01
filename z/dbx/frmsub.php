<?
require_once('./class/showmain.php');
$shows = new ShowMain();
?>
<html>
<head>
<link rel="stylesheet" type="text/css" href="style.css">
<meta http-equiv="content-type" content="text/html; charset=euc-jp">
<title>strange music::db</title>
</head>
<body>
<form name="form" action="frmsub.php" method="get">
<center>
<table border="0" cellpadding="5" cellspacing="5" width="100%">
<tr><td><a href="frmsub.php?main=<?= $_GET[main] ?>&nt=1">all list</a></td>
<td align="right"><font color="#ff3300">strange music::db (rev.0.2)</font></td>
</tr>
<td id="left" valign="top" colspan="2" class="white">
<input type="text" name="navi" value="<?= urldecode(stripslashes($_GET[navi])) ?>" class="i_lit">
<input type="submit" name="search" value="search">
<?
if($_GET[nt]==1){
	$shows->ShowList($_GET[navi],"frmsub.php","index");
}elseif($_GET[nt]==2){
	$shows->ShowArtist($_GET[navi],"frmmain.php","main");
}elseif($_GET[lb]==2){
	$shows->ShowLabel($_GET[navi],"frmmain.php","main");
}elseif($_GET[navi]){
	$shows->ShowPerson($_GET[navi],"frmmain.php","main");
}else{
	$shows->ShowNew($_POST[start],"frmmain.php","main");
}
?>

</td>
</tr>
</table>
</center>
</form>
<script language="javascript" src="http://polkaskij.dip.jp/stats/php-stats.js.php"></script>
<noscript><img src="http://polkaskij.dip.jp/stats/php-stats.php" border="0" alt=""></noscript>
</body>
</html>
