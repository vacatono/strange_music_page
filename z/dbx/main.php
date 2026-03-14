<?
require_once("inc/config.inc");
require_once("inc/sqls.inc");

$dbobj = new sqls($DB,$DBUID,$DBUPW,$HOST);

//	ﾁｴﾉﾎｷ・・$sql = "select count(*) as cnt from album";
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
､ｨ｡ｼ､ﾈ｡｢､ｽ､ﾊﾌﾇｸｽｺﾟｽ､ﾉ・讀ﾇ､ｹ｡｣<br>
､ｳ､ｳ､ﾏ｡ﾖｲｶ､ﾎｻ､ﾃ､ﾆ､・D､ﾎ･ｯ･・ｸ･ﾃ･ﾈ､ﾒ､ｿ､ｹ､鯒ﾐﾏｿ､ｹ､・ﾗｽ熙ﾇ､ｹ｡｣<br>
<br>
･ｳ･ｳ､ﾏ･｢･・ﾇ､ｹ｡ﾖ､ｳ､ﾎCD､ﾋｻｲｲﾃ､ｷ､ﾆ､・x､ｵ､ﾏﾂｾ､ﾋ､ﾉ､ﾊｻｷ､ﾆ､､､・ﾎ､ﾀ､惕ｦ｡ｩ｡ﾗ<br>
､ﾈ､ｫ､､､ｦ｡｢ｼｫﾊｬ､ｬ･ｵ･､･ﾈ､ﾏ､ｸ､皃ｿｻ､ﾎﾌﾜﾅｪ､ﾗ､､ｽﾐ､ｷ､ﾆｺ釥ﾃ､ﾆ､､､・ｵ･､･ﾈ､ﾇ､ｹ｡｣<br>
<br>
ｸｽｺﾟ<font color="#009900"><?= number_format($allcnt['cnt']); ?>ﾋ・/font>ﾊｬ､ﾎ･ﾇ｡ｼ･ｿ､ｬﾍｭ､・ﾟ､ｿ､､､ﾇ､ｹ｡｣<br>
<br>
､ｳ､ﾉ､ﾏ･ｵ｡ｼ･ﾐ､ｳ､荀ｵ､ﾊ､､､隍ｦ､ﾋｵ､､ﾄ､ｱ､ﾞ､ｹ｡｣･ﾐ･ﾃ･ｯ･｢･ﾃ･ﾗ､箴隍熙ﾞ､ｹ｡｣(2004.3.24)<br>
<br>
､｢､ﾞ､・ﾑ､・ﾃ､ﾆ､ﾊ､､､ｱ､ﾉ｡｢､ｻ､ﾃ､ｫ､ｯ･ｵ｡ｼ･ﾐﾂ衞ｧ､ﾃ､ﾆ､・ﾎ､ﾇ｡｢､ｵ､ｯ､鬢ﾎ･ｵ｡ｼ･ﾐ､ﾋｰﾜ､ｷ､ﾞ､ｷ､ｿ｡｣(2006.11.13)<br>
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
