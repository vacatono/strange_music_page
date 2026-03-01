<?
require_once("DB.php");

$dsn = "mysql://apache:molemole@localhost/xmusic";
$dbobj = DB::connect($dsn);
if(DB::isError($dbobj)) {
	die ($dbobj->getMessage());
}

$dbobj->setFetchMode(DB_FETCHMODE_ASSOC);


$sql = "select * from album";
$data = $dbobj->getAssoc($sql);

print('<pre>');
print_r($data);
print_r($dbobj);


?>
