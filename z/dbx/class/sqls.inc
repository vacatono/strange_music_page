<?
class sqls
{
	var $con;	## コネクションリソース
	var $inputenc;		## update/insertの時の入力エンコーディング
	
	function closeDB(){
		mysql_close($this->con);
	}

	### コンストラクタ
	function sqls($DB='',$USER='',$PASS='',$HOST='localhost',$sep=0,$inputenc=''){
		if(!$DB){ return false; }

		if($inputencoding){
			$this->inputenc = $inputenc;
		}
		
		$this->con = mysql_connect($HOST,$USER,$PASS,$sep);
		$res = mysql_select_db($DB,$this->con) or die("Sorry, Could not select Db : " . mysql_error($this->con) . "<br>");

		// デストラクタの登録
		// register_shutdown_function($this->closeDB());

		if($res){
			return true;
		}else{
			return false;
		}
	}

	### データ取得
	function getAssoc($sql){
		if($this->inputenc){
			$sql = mb_convert_encoding($sql,"EUC-JP",$this->inputenc);
		}

		$res = mysql_query($sql,$this->con);
		while($data = @mysql_fetch_assoc($res)){
			$assox[] = $data;
		}
		@mysql_free_result($res);
		if($assox){
			return $assox;
		}else{
			return false;
		}
	}
	
	### データ取得
	function getAssocPri($sql, $key=""){
		if($this->inputenc){
			$sql = mb_convert_encoding($sql,"EUC-JP",$this->inputenc);
		}
		$res = mysql_query($sql,$this->con);
		while($data = @mysql_fetch_assoc($res)){
			$assox[$data[$key]] = $data;
		}
		@mysql_free_result($res);
		if($assox){
			return $assox;
		}else{
			return false;
		}
	}

	### データ取得してHASH返し
	function getAssocPri2($sql,$key="",$val=""){
		if($this->inputenc){
			$sql = mb_convert_encoding($sql,"EUC-JP",$this->inputenc);
		}
		$res = mysql_query($sql,$this->con);
		while($data = @mysql_fetch_assoc($res)){
			$assox[$data[$key]] = $data[$val];
		}
		@mysql_free_result($res);
		if($assox){
			return $assox;
		}else{
			return false;
		}
	}
	
	function getAssocOne($sql){
		if($this->inputenc){
			$sql = mb_convert_encoding($sql,"EUC-JP",$this->inputenc);
		}
		$res = mysql_query($sql,$this->con);
		$data = @mysql_fetch_assoc($res);
		@mysql_free_result($res);
		if($data){
			return $data;
		}else{
			return false;
		}
	}
	
	function getRows($sql){
		if($this->inputenc){
			$sql = mb_convert_encoding($sql,"EUC-JP",$this->inputenc);
		}
		$res = mysql_query($sql, $this->con);
		return @mysql_num_rows($res);
	}

	### クエリー
	function Query($sql,$debug=""){
		if($this->inputenc){
			$sql = mb_convert_encoding($sql,"EUC-JP",$this->inputenc);
		}
		$res = mysql_query($sql,$this->con);
		if($debug){
			echo "<Br>" . $sql . "<Br>";
		}
		if($res){
			return true;
		}else{
			return false;
		}
	}

	function QueryTest($sql){
		if($this->inputenc){
			$sql = mb_convert_encoding($sql,"EUC-JP",$this->inputenc);
		}
		print(__LINE__ . ": " . $sql . "<br><br>\n");
	}
	
	/** Registration
	 *	
	 *	$opt
	 *	[debug]		debugモード
	 *	[escape]	mysql_escape_stringモード
	 *	[mail]		insertが失敗したときメールを送信
	 *	
	 */
	function Regist($Table="", $Fields=array(), $opt=array()){
		
		if(!$Table){
			echo "Please, select table...";
			return false;
		}
		if(!$Fields){
			echo "Please, select Field...";
			return false;
		}
		
		$isql = "insert into {$Table} set ";
		foreach($Fields as $key => $val){
			if(eregi("^(now\(\)|null)$", $val)){
				$isql .= $key . "=" . $val . ",";
			}else{
				if($opt['escape']){
					$isql .= $key . "='" . mysql_escape_string($val) . "',";
				}else{
					$isql .= $key . "='" . $val . "',";
				}
			}
		}
		$isql = substr($isql,0,-1);
		// $isql = "insert into {$Table} (" . join(",",array_keys($Fields)) . ") values ('" . join("','",array_values($Fields)) . "')";
		if($this->inputenc){
			$isql = mb_convert_encoding($isql,"EUC-JP",$this->inputenc);
		}
		
		if($opt[debug]){
			print($isql."<hr>");
			mysql_query($isql,$this->con) or die($isql);
			return mysql_insert_id($this->con);
		}else{
			if($ires = mysql_query($isql,$this->con)){
				return mysql_insert_id($this->con);
			}else{
				if($opt['mail']){
					mail($opt['mail'],$_SERVER['PHP_SELF']."regist err.",$isql);
				}
				return false;
			}
		}
	}
	
	/* Update */
	function Update($Table="", $Fields=array(), $Where="", $opt=array()){
		
		if(!$Table){
			echo "Please, select table...";
			return false;
		}
		if(!$Fields){
			echo "Please, select Field...";
			return false;
		}
		
		if($Where){
			$usql = "update {$Table} set ";
			foreach($Fields as $key => $val){
				if(eregi("^(now\(\)|null)$", $val)){
					$usql .= $key . "=" . $val . ",";
				}else{
					if($opt['escape']){
						$usql .= $key . "='" . mysql_escape_string($val) . "',";
					}else{
						$usql .= $key . "='" . $val . "',";
					}
				}
			}
			$usql = substr($usql,0,-1) . " where " . $Where;

			if($this->inputenc){
				$usql = mb_convert_encoding($usql,"EUC-JP",$this->inputenc);
			}
			
			if($opt['debug']){
				echo "<hr>".$usql.";<br><hr>";
				$ures = mysql_query($usql,$this->con) or die($usql);
			}else{
				if($ures = mysql_query($usql,$this->con)){
					return $ures;
				}else{
					return false;
				}
			}
		}
	}

	// enumを配列にして返す
	function enum2arr($TABLE,$FIELD){
		$sql = "show columns from $TABLE like '$FIELD'";
		$data = $this->getAssocOne($sql);
		if(!$data){
			return false;
		}elseif(!ereg("enum|set",$data[Type])){
			return false;
		}else{
			$COLS = ereg_replace("enum\(\'|set\(\'","",$data[Type]);
			$COLS = ereg_replace("')$","",$COLS);
			$COLS_ARRAY = explode("','",$COLS);
			return $COLS_ARRAY;
		}
	}

	function enum2arr2($TABLE,$FIELD){
		$sql = "show columns from $TABLE like '$FIELD'";
		$data = $this->getAssocOne($sql);
		if(!$data){
			return false;
		}elseif(!ereg("enum|set",$data[Type])){
			return false;
		}else{
			$COLS = ereg_replace("enum\(\'|set\(\'","",$data[Type]);
			$COLS = ereg_replace("')$","",$COLS);
			$COLS_ARRAY = explode("','",$COLS);
			foreach($COLS_ARRAY as $val){
				$COLS_ARRAY2[$val] = $val;
			}
			return $COLS_ARRAY2;
		}
	}


	// テーブル内のフィールド情報を連想配列にして返す
	function getFields($DB,$TABLE){
		if(!$DB || !$TABLE){return false;}
		@$fres = mysql_list_fields($DB,$TABLE,$this->con);
		if(!$fres){return false;}
		$fcnt = mysql_num_fields($fres);
		for($i=0;$i<$fcnt;$i++){
			$FLDs[$i][NAME] = mysql_field_name($fres,$i);
			$FLDs[$i][TYPE] = mysql_field_type($fres,$i);
			$FLDs[$i][LEN] = mysql_field_len($fres,$i);
			$FLDs[$i][FLAGS] = mysql_field_flags($fres,$i);
		}
		return $FLDs;
	}

	function getFieldNames($DB,$TABLE){
		if(!$DB || !$TABLE){return false;}
		@$fres = mysql_list_fields($DB,$TABLE,$this->con);
		if(!$fres){return false;}
		$fcnt = mysql_num_fields($fres);
		for($i=0;$i<$fcnt;$i++){
			$FLDs[] = mysql_field_name($fres,$i);
		}
		return $FLDs;
	}
}
?>
