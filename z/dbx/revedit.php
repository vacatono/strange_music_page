<?
require_once("config.inc");
require_once('sqls.inc');
$dbobj = new sqls($DB,$DBUID,$DBUPW,$HOST);


if($_POST[send] && $_POST[rev_id]){
	$sql = "update review set
		user='{$_POST[name]}',
		review='{$_POST[review]}',
		reg_date='{$_POST[reg_date]}'
		where id='{$_POST[rev_id]}'";
	$res = $dbobj->Query($sql);

}elseif($_POST[send]){
	$sql = "insert into review (album,user,review,reg_date) values
	('{$_GET[id]}',
	'".htmlspecialchars($_POST[name])."',
	'".htmlspecialchars($_POST[review])."',
	now())";
	$res = $dbobj->Query($sql);
}
	print($sql);
$sql = "select * from album where id='$_GET[id]'";
$albumdata = $dbobj->getAssocOne($sql);

if($_GET[rev]){
	$sql = "select * from review where id='{$_GET[rev]}'";
	$rdata = $dbobj->getAssocOne($sql);
}

if(!$albumdata || $res){
	?>
	<html>
	<head>
	<script language="javascript">
	<!--
	window.close();
	//-->
	</script>
	</head>
	<body>
	<br>
	</body>
	</html>
	<?
	die();
}
?>
<html>
<head>
<link rel="stylesheet" type="text/css" href="style.css">
<meta http-equiv="content-type" content="text/html; charset=euc-jp">
<title>strange music::db</title>
</head>
<body onLoad="focus();">
<form name="form" action="revedit.php?id=<?= $_GET[id] ?>" method="post">
<center>
<table border="0" cellpadding="5" cellspacing="5" width="90%">
<tr>
<td>
	<b><? if($albumdata[artist]){ print($albumdata[artist].' / '); } ?>
	<?= $albumdata[title] ?></b>
</td>
<tr><td class="white">
name:<br>
<input type="text" name="name" value="<?= $rdata[user] ?>"><br>
review:<br>
<textarea name="review" cols="60" rows="8"><?= $rdata[review] ?></textarea>
<? if($rdata){ ?>
	<br>
	<input type="text" name="reg_date" value="<?= $rdata[reg_date] ?>" size="40">
	<input type="hidden" name="rev_id" value="<?= $rdata[id] ?>">
<? } ?>
</td>
</tr>
<tr>
<td align="right"><input type="submit" name="send" value=" write "></td></tr>
</table>
</center>
</form>
</body>
</html>
