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
<form name="form" action="frmmain.php" method="get">
<center>
<table border="0" cellpadding="5" cellspacing="5" width="100%">
<tr>
  <td></td>
  <td align="right"><font color="#ff3300">strange music::db (rev.0.2)</font></td>
</tr>
<td id="main" valign="top" class="white" colspan="2">
<? if($_GET[main]){ 
	$shows->ShowAlbum($_GET[main],"frmsub.php","index");
}else{ ?>

<? } ?>

</td>
</tr>
<tr>
<td colspan="2" align="right"><a href="http://vacatono.flop.jp">(strange music page)</a></td>
</table>
</center>
</form>
<script language="javascript" src="http://polkaskij.dip.jp/stats/php-stats.js.php"></script>
<noscript><img src="http://polkaskij.dip.jp/stats/php-stats.php" border="0" alt=""></noscript>
</body>
</html>
