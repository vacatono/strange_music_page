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
<form name="form" action="main.php" method="get">
<center>
<table border="0" cellpadding="5" cellspacing="5" width="90%">
<tr><td>
	<a href="main.php">top</a> | 
	<a href="main.php?main=<?= $_GET[main] ?>&nt=reg">new edit</a> |
	<a href="main.php?main=<?= $_GET[main] ?>&nt=1">list</a>
</td>
<td align="right"><font color="#ff3300">strange music::db (rev.0.2)</font></td>
</tr>
<? if($_GET[dt]!='frame'){ ?>
<td id="left" width="30%" valign="top" class="white">
<input type="text" name="navi" class="i_lit" value="<?= urldecode(stripslashes($_GET[navi])) ?>">
<input type="submit" name="search" value="search">
<?
if($_GET[nt]==1){
	$shows->ShowList($_GET[navi]);
}elseif($_GET[nt]==2){
	$shows->ShowArtist($_GET[navi]);
}elseif($_GET[nt]=='reg'){
	$shows->ShowNewEdit();
}elseif($_GET[lb]==2){
	$shows->ShowLabel($_GET[navi]);
}elseif($_GET[navi]){
	$shows->ShowSomethin($_GET[navi]);
}else{
	$shows->ShowNew($_POST[start]);
}
?>
</td>
<? } ?>
<td id="main" valign="top" class="white"<? if($_GET[dt]=='frame'){ print(' colspan="2"'); } ?>>
<?
if($_GET[main]){
	$shows->ShowAlbum($_GET[main]);
}else{
?>
えーと、そんな訳で現在修復中です。<br>
見にくいですか？見にくいですね。徐々に直していきます。<br>
<br>
ココはアレです「このCDに参加してるxxさんは他にどんな事をしているのだろう？」<br>
とかいう、自分がサイトはじめた時の目的を思い出して作っているサイトです。<br>
<br>
PHP+MySQLで作ってます。とりあえず<a href="http://vacatono.flop.jp">元サイト</a>のデータをインポートしてみまいたが、ベタベタの手書きHTMLをインポートしたので、ヘンな部分がまだ沢山有ります。<br>
<br>
こんどはサーバを燃やさないように気をつけます。バックアップも取ります。(2004.3.24)
<?
}
?>

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
