<?
require_once("config.inc");
require_once("sqls.inc");

$dbobj = new sqls($DB,$DBUID,$DBUPW,$HOST);

$sql = "select * from album order by artist";
$data = $dbobj->getAssoc($sql);

?>
<html>
<head>
<link rel="stylesheet" type="text/css" href="style.css">
<meta http-equiv="content-type" content="text/html; charset=euc-jp">
<title>strange music::db</title>
</head>
<body>
<table border=1>
<? foreach($data as $v){ ?>
<tr>
<td><?= $v['artist'] ?></td>
<td><?= $v['title'] ?></td>
<td><?= $v['maker'] ?></td>
<td><?= $v['sales_date'] ?></td>
</tr>
<? } ?>
</table>

</body>
</html>
