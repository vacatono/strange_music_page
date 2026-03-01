<?
//	データ登録、更新
//

require_once("config.inc");
require_once("sqls.inc");
require_once("cform.inc");

// initialize mysql
$dbobj = new sqls($DB,$DBUID,$DBUPW,$HOST);

$disp_arr = array("artist","title","title_e","sales_date","maker","code","url1","url1_words","addinfo","reg_date");
	

$id = abs($_GET['id']);


if($_POST['regist']){
	//	POSTした配列をコピって要らないのを抜く
	$alb['artist'] = $_POST['artist'];
	$alb['title'] = $_POST['title'];
	$alb['title_e'] = $_POST['title_e'];
	$alb['maker'] = $_POST['maker'];
	$alb['code'] = $_POST['code'];
	$alb['url1'] = $_POST['url1'];
	$alb['url1_words'] = $_POST['url1_words'];
	$alb['addinfo'] = $_POST['addinfo'];
	$alb['reg_date'] = $_POST['reg_date'];
	$alb['sales_date'] = $_POST['sales_date'];
	
	if($_POST['duplicate']){
		unset($id);
	}

	if($id){
		$dbobj->Update("album",$alb,"id='{$id}'");
	}else{
		$alb['reg_date'] = 'now()';
		$id = $dbobj->Regist("album",$alb,array("debug"=>"0"));
	}


	// player data
	$sql = "delete from players where album='{$id}'";
	$dbobj->Query($sql);
	
	if($_POST[player]){
	foreach($_POST[player] as $key => $val){
		if($val){
			$sql = "insert into players (album,number,name,info)
			values ('{$id}','{$key}','{$val}','{$_POST[player_i][$key]}')";
			$dbobj->Query($sql);
		}
	}}

	// song data
	$sql = "delete from songs where album='{$id}'";
	$dbobj->Query($sql);
	if($_POST[track]){
	foreach($_POST[track] as $disc => $val){
		if($val){
			foreach($val as $track => $name){ 
				if($name){
					$sql = "insert into songs (album,disc,track,name)
						values ('{$id}','{$disc}','{$track}','{$name}')";
					$dbobj->Query($sql);
				}
			}
		}
	}}

	header("Location: edit.php?id=".$id);
	die();
}

// データ取得 - - - - - 

// albumデータ
$sql = "select * from album where id='{$id}'";
$data = $dbobj->getAssocOne($sql); 

// songデータ
$sql = "select * from songs where album='{$id}' order by disc,track";
$sdata = $dbobj->getAssoc($sql);
if($sdata){
foreach($sdata as $val){
	$songdata[$val[disc]][$val[track]] = $val['name'];
}}

// playerデータ
$sql = "select * from players where album='{$id}' order by number";
$playerdata = $dbobj->getAssocPri($sql,"number");



?>
<html>
<head>
<link rel="stylesheet" type="text/css" href="style.css">
<meta http-equiv="content-type" content="text/html; charset=euc-jp">
</head>
<form name="form" action="<?= $_SERVER['REQUEST_URI'] ?>" method="post">
<h1>xmusic::album::<?= $id ?></h1>
<a href="list.php?start=<?= $_GET[id]-1 ?>">return list</a> | 
<a href="../main.php?main=<?= $_GET[id] ?>">confirm</a> |
<a href="edit.php">new</a> |
<input type="checkbox" name="duplicate">duplicate |
<input type="submit" name="regist" value=" edit "> | 

<hr>
<table border="0">
<tr>
<td valign="top">
	basic:
	<table border="1">
	<? foreach($disp_arr as $key){ ?>
		<tr>
		<td><?= $key ?></td>
		<td>
		<? if($key=='addinfo'){ ?>
			<textarea name="<?= $key ?>" rows="6" cols="30"><?= htmlspecialchars($data[$key]) ?></textarea>
		<? }else{ ?>
			<input type="text" name="<?= $key ?>" value="<?= htmlspecialchars($data[$key]) ?>">
		<? } ?>
		</td>
		</tr>
	<? } ?>
	</table>
</td>
	<? for($i=1;$i<count($songdata)+2;$i++){ ?>
		<td valign="top">
		song data: <?= $i ?>
		<table border="1">
		<? for($j=1;$j<count($songdata[$i])+20;$j++){ ?>
			<tr>
			<td><?= $j ?></td>
			<td><input type="text" name="track[<?= $i ?>][<?= $j ?>]" value="<?= htmlspecialchars($songdata[$i][$j]) ?>"></td>
			</tr>
		<? } ?>
	</table>
	</td>
	<? } ?>
<td valign="top">
	players:
	<table border="1">
	<? for($i=0; $i<count($playerdata)+20; $i++){ ?>
		<tr>
		<td><?= $i ?></td>
		<td><input type="text" name="player[<?= $i ?>]" value="<?= htmlspecialchars($playerdata[$i][name]) ?>"></td>
		<td><input type="text" name="player_i[<?= $i ?>]" value="<?= htmlspecialchars($playerdata[$i][info]) ?>"></td>
		</tr>
	<? } ?>
	</table>
</td>
</tr>
</table>
</body>
</html>
