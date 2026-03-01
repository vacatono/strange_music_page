<?
require_once("config.php");
require_once("paging.php");
require_once("disp.php");
require_once("mysql.php");

// initialize mysql
$db_obj = new mysql("xmusic","kei","molemole","localhost");
$sql = "select count(*) as cnt from album";
$data = $db_obj->getRow($sql);
$all = $data[cnt];

$pg_obj = new pager($all); 
$sql = "select * from album limit {$pg_obj->start},{$pg_obj->range}";
$data_arr = $db_obj->getAssoc($sql);

$disp_arr = array("id","artist","title","anchor","sales_date","maker","code");
?>
<? disp::DispHeader() ?>
<form name="form" method="post" action="list.php">
<h1>xmusic::albums</h1>
<center>
<div align="right">
<input type="text" size="8" name="start_chg"><input type="button" onClick="document.form.start.value=document.form.start_chg.value;document.form.submit();" value=" Go ">
<? $pg_obj->PrevBtn(); $pg_obj->NextBtn(); ?>
</div>

<table border="1" width="100%">
<tr><? foreach($disp_arr as $val){ print("<td>{$val}</td>\n"); } ?></tr>
<?
foreach($data_arr as $data){
	print('<tr>');
	print('<td><a href="edit.php?id='.$data[id].'" >'.$data[id]."</a></td>");
	print("<td>".$data[artist]."</td>");
	print("<td>".$data[title]."</td>");
	print("<td>".$data[anchor]."</td>");
	print("<td>".$data[sales_date]."</td>");
	print("<td>".$data[maker]."</td>");
	print("<td>".$data[code]."</td>");
//	print("<td>".nl2br($data[addinfo])."</td>");
	print("</tr>\n");
}
print("</table>\n");
?>
<div align="right"><? $pg_obj->PrevBtn(); $pg_obj->NextBtn(); ?></div>
<? $pg_obj->MakeHidden(); ?>
</center>
</form>
<? disp::DispFooter(); ?>
