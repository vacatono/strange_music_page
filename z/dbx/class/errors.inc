<?
//	エラー処理用クラス
class errors{
	
	function ErrorBack($msg,$title="エラー処理",$style="style.css"){
		print('<html><head>');
		print('<meta http-equiv="content-type" content="text/html; charset=euc-jp">');
		print("<title>$title</title>");
		print('<link type="text/css" rel="stylesheet" href="'.$style.'">');
		print("</head>");
		print("<body>\n");
		print("<center>\n");
		print("<br>\n");
		print("<br>\n");
		print($msg);
		print("<br>\n");
		print("<br>\n");
		print("<input type='button' value=' 戻る ' name='back' onClick='history.back();'>\n");
		print("</center>\n");
		print("</body>\n");
		print("</html>\n");
		die();
	}
	
}
?>
