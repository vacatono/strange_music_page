<?
require_once("sqls.inc");
class ShowMain extends sqls
{
	//	変数定義
	var $DBUID = "vacatono";
	var $DBUPW = "molemole";
	var $DB = "vacatono";
	var $HOST = "mysql3.db.sakura.ne.jp";
	var $dbobj;

	// コンストラクタ
	function ShowMain(){
		$this->dbobj = new sqls($this->DB,$this->DBUID,$this->DBUPW,$this->HOST);
	}

	// Album Shows
	function GetAlbum($id){
		$sql = "select * from album where id='$id'";
		$album_data = $this->dbobj->getAssocOne($sql);
		return $album_data;
	}

	function GetSongs($id){
		$sql = "select * from songs where album='$id' order by disc,track";
		$data = $this->dbobj->getAssoc($sql);
		if($data){
		foreach($data as $val){
			$songs_data[$val[disc]][$val[track]] = $val[name];
		}}
		return $songs_data;
	}

	function GetPlayers($id){
		$sql = "select * from players where album='$id' order by number";
		$players_data = $this->dbobj->getAssoc($sql);
		return $players_data;
	}
	function GetReview($id){
		$sql = "select * from review where album='$id' order by reg_date";
		$review_data = $this->dbobj->getAssoc($sql);
		return $review_data;
	}


	//	メイン画面、アルバム表示
	function ShowAlbum($id,$link="main.php",$target="_self"){
		//	とりあえず各データ取得
		$album_data = $this->GetAlbum($id);
		$review_data = $this->GetReview($id);
		$songs_data = $this->GetSongs($id);
		$players_data = $this->GetPlayers($id);

		//	表示 -
		print("<h4>");
		if($album_data[artist]){ 
			$subject = $album_data[artist] . " / " . $album_data[title];
		}else{
			$subject = $album_data[title];
		}
		print($subject);
		print("</h4>\n");

		//	reviewデータの表示
		if($review_data){
		foreach($review_data as $val){
			if(strlen(chop($val))){
				print(nl2br($val[review])."\n");
			}
			if($val[reg_date]>'2004-04-01'){ 
				print("(".str_replace("-",".",substr($val[reg_date],0,10)).")"); 
			}
			print('<a href="javascript:void(0)" onClick="window.open('."'revedit.php?id={$id}&rev={$val[id]}','revedit','height=400,width=500,scrollbars=yes,resizable=yes');".'">*</a>');
			print("<br>\n");
		}}
	

		if($album_data[image]){
			if(is_file($album_data[image])){
				print("<img src=\"{$album_data[image]}\" align=\"right\" alt=\"{$subject}\" height=\"100\" width=\"100\">\n");
			}
		}
		if($songs_data){
			foreach($songs_data as $disc => $val){
				print("<ol>\n");
				foreach($val as $track => $name){
					print("<li>".$name."\n");
				}
				print("</ol>\n");
			}
		}
		if($album_data[addinfo]){
			print("<div class=\"addinfo\">\n");
			print(nl2br($album_data[addinfo]) . "<br>\n");
			print("</div>\n");
		}
		if($players_data){
			foreach($players_data as $val){
				print("<div class='list2'>");
				print('<font color="#cc99cc">- </font>');
				print("<a href=\"{$link}?main=".$album_data[id]."&navi=".urlencode(stripslashes($val[name]))."\" target=\"{$target}\">");
				print($val[name]."</a>");
				if($val[info]){ print(" ({$val[info]})\n"); }
				print("</div>\n");
			}
			print("<br />\n");
		}
		if($album_data[maker]){ 
			$labels = split("/",$album_data[maker]);
			for($i=0;$i<count($labels);$i++){
				if($i){ print("/"); }
				print("<a href=\"{$link}?main=".$album_data[id]."&navi=".urlencode(stripslashes($labels[$i]))."&lb=2\" target=\"{$target}\">");
				print($labels[$i]); 
				print("</a>");
			}
		} 
		if($album_data[code]){ print(": ".$album_data[code]); }
		if($album_data[sales_date]!='0000-00-00'){ 
			print(" (".str_replace('-','.',str_replace('-00','',$album_data[sales_date])).")"); 
		}
		//	ローカルから見てる時だけエディット可。
		print('<div align="right">');
		print('<a href="javascript:void(0)" onClick="window.open('."'revedit.php?id={$id}','revedit','height=400,width=500,scrollbars=yes,resizable=yes');".'">*</a> ');
		print('<a href="./admin/edit.php?id=' . $id . '">edit</a>');
		print('</div>');
	}

	//	人名検索
	function ShowSomethin($name,$link="main.php",$target="_self"){
		// 検索
		$sql = "select album.artist,album.title,album.id 
			from players 
			left join album on players.album=album.id
			where players.name like '{$name}%' or album.title like '{$name}%' or album.artist like '{$name}%'
			group by album.id
			order by album.sales_date";
		$data = $this->dbobj->getAssoc($sql);
		
		if($data){
		foreach($data as $val){
			if($val[artist]==''){ $val[artist]="v.a."; }
			$ldata[$val[artist]][] = $val;
		}}

		// 書き出し
		print("<h4>".stripslashes($name)."</h4>");

		if($ldata){
			foreach($ldata as $key => $val){
				print("&nbsp;".$key."<br>\n");
				foreach($val as $vval){
					print("&nbsp;&nbsp;&nbsp;");
					print("<a href=\"{$link}?main=".$vval[id]."&navi=".urlencode(stripslashes($name))."\" target=\"{$target}\">\n");
					print($vval[title]."</a><br>\n");
				}
			}
		}elseif($data){
			foreach($data as $val){
				print("&nbsp;&nbsp;&nbsp;");
				print("<a href=\"{$link}?main=".$val[id]."&navi=".urlencode(stripslashes($name))."\" target=\"{$target}\">\n");
				if($val[artist]){ print($val[artist]."/"); };
				print($val[title]."</a><br>\n");
			}
		}
	}
	
	//	人名検索
	function ShowPerson($name,$link="main.php",$target="_self"){
		// 検索
		$sql = "select album.artist,album.title,album.id 
			from players 
			left join album on players.album=album.id
			where players.name like '%{$name}%'
			order by players.number,album.sales_date";
		$data = $this->dbobj->getAssoc($sql);
		
		if($data){
		foreach($data as $val){
			if($val[artist]==''){ $val[artist]="v.a."; }
			$ldata[$val[artist]][] = $val;
		}}

		// 書き出し
		print("<h4>".stripslashes($name)."</h4>");

		if($ldata){
			foreach($ldata as $key => $val){
				print("&nbsp;".$key."<br>");	
				foreach($val as $vval){
					print("&nbsp;&nbsp;&nbsp;<a href=\"{$link}?main=".$vval[id]."&navi=".urlencode(stripslashes($name))."\" target=\"{$target}\">\n");
					print($vval[title]."</a><br>\n");
				}
			}
		}elseif($data){
			print("<ul>\n");
			foreach($data as $val){
				print("<li>");
				print("<a href=\"{$link}?main=".$val[id]."&navi=".urlencode(stripslashes($name))."\" target=\"{$target}\">\n");
				if($val[artist]){ print($val[artist]."/"); };
				print($val[title]."</a>\n");
			}
			print("</ul>\n");
		}
	}

	function ShowNew($start=0,$link="main.php",$target="_self"){

		//	年度を取る
		$sql ="select left(sales_date,4) as y from album group by y order by y";
		$yarr = $this->dbobj->getAssoc($sql);

		if($_GET['y']){ $defy = $_GET['y']; }else{ $defy = date("Y"); }
		$sql = "select album.artist,album.title,album.id 
			from album 
			where sales_date like '{$defy}%'
			order by sales_date desc";
		$data = $this->dbobj->getAssoc($sql);

		print('<select name="y" onChange="document.form.submit();">');
		foreach($yarr as $y){
			if($y[y]==$defy){
				print("<option value='{$y[y]}' selected>{$y[y]}</a>\n");
			}else{
				print("<option value='{$y[y]}'>{$y[y]}</a>\n");
			}
		}
		print("</select>\n");

		print("<hr>");
		if($data){
			foreach($data as $val){
				print('<div class="list1">');
				print('<font color="#ff0099">- </font>');
				print("<a href=\"{$link}?main=".$val[id]."&y={$defy}\" target=\"{$target}\">\n");
				if($val[artist]){ print($val[artist]."/"); };
				print($val[title]."</a>\n");
				print("</div>\n");
			}
		}
	}

	function ShowNewEdit($start=0,$link="main.php",$target="_self"){
		if(!abs($start)){ $start=0; }
		$sql = "select album.artist,album.title,album.id 
			from album 
			left join review on album.id=review.album
			where review.id is not null
			order by review.reg_date desc limit {$start},20";
		$data = $this->dbobj->getAssoc($sql);
		print("<br> * 新着 - - - - - <br>");

		if($data){
			if($start){
				$prev = ($start-20);
				$next = ($start+20);
			}else{
				$next = 20;
			}
			foreach($data as $val){
				print('<div class="list1">');
				print('<font color="#ff0099">- </font>');
				print("<a href=\"{$link}?nt=reg&main=".$val[id]."\" target=\"{$target}\">\n");
				if($val[artist]){ print($val[artist]."/"); };
				print($val[title]."</a>\n");
				print("<br />\n");
				print("</div>\n");
			}
			print('<div align="right">');
			if(isset($prev)){
			print("<a href=\"{$link}?nt=reg&main={$_GET['main']}&st={$prev}\" target=\"{$target}\">\n");
			print("&lt;&lt;</a>");
			}
			print("<a href=\"{$link}?nt=reg&main={$_GET['main']}&st={$next}\" target=\"{$target}\">\n");
			print("&gt;&gt;</a>");
		}
	}

	function ShowLabel($name,$link="main.php",$target="_self"){
		$sql = "select album.artist,album.title,album.id,album.code from album 
			where maker like '%{$name}%'
			order by code";
		$data = $this->dbobj->getAssoc($sql);
		print("<h4>".stripslashes($name)."</h4>");
		if($data){
			print("<table>\n");
			foreach($data as $val){
				print("<tr><td nowrap>".$val[code]." </td>");
				print("<td><a href=\"{$link}?main=".$val[id]."&navi=".urlencode(stripslashes($name))."&lb=2\" target=\"{$target}\">\n");
				if($val[artist]){ print($val[artist]."/"); };
				print($val[title]."</a></td></tr>\n");
			}
			print("</table>\n");
		}
	}

	function ShowArtist($name,$link="main.php",$target="_self"){
		// 検索
		$sql = "select album.artist,album.title,album.id from album 
			where artist='{$name}'
			order by sales_date";
		$data = $this->dbobj->getAssoc($sql);

		print("<h4>".stripslashes($name)."</h4>");
		if($data){
			print("<ul>\n");
			foreach($data as $val){
				print("<li>");
				print("<a href=\"{$link}?main=".$val[id]."&navi=".urlencode(stripslashes($name))."&nt=2\" target=\"{$target}\">\n");
				if($val[artist]){ print($val[artist]."/"); };
				print($val[title]."</a>\n");
			}
			print("</ul>\n");
		}
	}

	function ShowList($name,$link="main.php",$target="_self"){
		$sql = "select artist,count(id) as cnt from album where artist like '%{$name}%' group by artist";
		$data = $this->dbobj->getAssoc($sql);

		if($data){
			print("<ul>\n");
			foreach($data as $val){
				print("<li>");
				print("<a href=\"{$link}?main=".$_GET[main]."&navi=".urlencode($val[artist])."&nt=2\" target=\"{$target}\">\n");
				if($val[artist]){ print($val[artist]); }else{ print('v.a.'); }
				print('(' . $val[cnt] . ")</a>\n");
			}
			print("</ul>\n");
		}
	}

			

}	// end of class [ShowMain]
?>
