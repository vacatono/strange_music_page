<?
require_once("inc/config.inc");
require_once("inc/sqls.inc");

$dbobj = new sqls($DB,$DBUID,$DBUPW,$HOST);

//	全部の件数
$sql = "select count(*) as cnt from album";
$allcnt = $dbobj->getAssocOne($sql);

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
<td id="left" width="40%" valign="top" class="white">
<input type="text" name="navi" class="i_lit" value="<?= urldecode(stripslashes($_GET[navi])) ?>">
<input type="submit" name="search" value="search">
<?
if($_GET[nt]==1){
	$shows->ShowList($_GET[navi]);
}elseif($_GET[nt]==2){
	$shows->ShowArtist($_GET[navi]);
}elseif($_GET[nt]=='reg'){
	$st = abs($_GET['st']);
	$shows->ShowNewEdit($st);
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
ここは「俺の持ってるCDのクレジットをひたすら登録する」所です。<br>
<br>
ココはアレです「このCDに参加してるxxさんは他にどんな事をしているのだろう？」<br>
とかいう、自分がサイトはじめた時の目的を思い出して作っているサイトです。<br>
<br>
現在<font color="#009900"><?= number_format($allcnt['cnt']); ?>枚</font>分のデータが有るみたいです。<br>
<br>
こんどはサーバを燃やさないように気をつけます。バックアップも取ります。(2004.3.24)<br>
<br>
あんまり変わってないけど、せっかくサーバ代払ってるので、さくらのサーバに移しました。(2006.11.13)<br>
<? } ?>
</td>
</tr>
<tr>
<td colspan="2" align="right"><a href="http://vacatono.flop.jp">(strange music page)</a></td>
</table>
</center>
</form>
<div style="display:none;">
<script src="http://www.google-analytics.com/urchin.js" type="text/javascript">
</script>
<script type="text/javascript">
_uacct = "UA-769637-1";
urchinTracker();
</script>
</div>
</body>
</html>
