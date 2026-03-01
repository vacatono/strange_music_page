<?
# File  :  makeform.inc
# Date  :  2003-06-06日(金) 11:21:52
# Maker :  Kousuke Akiho

# Last modify : Kousuke Akiho / 2003-06-10日(火) 11:11:34 ---> Delete Bug...
# Last modify : Kousuke Akiho / 2003-06-09日(月) 11:11:34 ---> Finish File...
# Last modify : Kousuke Akiho / 2003-06-06日(金) 11:21:52 ---> New File...
//	Up.		ReturnValue追加 & 配列対応 (CheckBox除く).					by kousuke. [月  2月 16 15:52:35 JST 2004]




### **** フォーム作成 *****
class MakeForm {
	
	var $confirm;
	
	function MakeForm($confirm){
		$this->confirm = $confirm;
	}
	
	
	### **** フォームにダブルコーテーション又、シングルコーテーションに対応 ****
	function SP_ENT($VAL){
		return htmlspecialchars(stripslashes($VAL), ENT_QUOTES);
	}
	
	// 配列対応メソッド
	function ReturnValue($Name=""){
		if(ereg("(^[^\[]+)(.*)", $Name, $Paturn)){
			
			$value[0] = $Paturn[1];
			if($Paturn[2]){
				$Paturn[2] = ereg_replace("^\[", "", ereg_replace("\]$", "", $Paturn[2]));
				$value = array_merge($value, split("\]\[",$Paturn[2]));
			}
			
			$bool = $_POST;
			foreach($value as $val){
				$bool = $bool[$val];
			}
			return $bool;
		}else{
			return false;
		}
	}
	
	
	/* enum || setフィールドの値を配列にして返す  */
	function GET_ENUM($con="",$TABLE,$DATA_FIELD="",$DATA_BASE="pegasus"){
		
		if(!$con or !$TABLE or !$DATA_BASE){ return false; }
		# echo "table ---> " . $TABLE."<Br>";
		# echo "field ---> " . $DATA_FIELD."<Br>";
		
		if(!$DATA_FIELD){
			$sql = "show columns from {$TABLE}";
			$result = mysql_query($sql,$con) or die($sql);
			$num = mysql_numrows($result);
			for($i=0;$i<$num;$i++){
				if(eregi("enum|set",mysql_result($result,$i,"Type"))){$DATA_FIELD = mysql_result($result,$i,"Field");break;}
			}
		}
		if($DATA_FIELD){
			$sql = "show columns from {$TABLE} like '{$DATA_FIELD}'";
			$result = mysql_query($sql,$con) or die($sql);
			if(mysql_numrows($result)){
   	            $COLS = mysql_result($result,0,"Type");
				if(ereg("enum|set",$COLS)){
					$COLS = ereg_replace("enum\(\'|set\(\'","",$COLS);
					$COLS = ereg_replace("')$","",$COLS);
					$COLS_ARRAY = explode("','",$COLS);
				}
			}
			return $COLS_ARRAY;
		}
	}
	
	### **** テキストフォーム作成 ****
	function MakeText($Name="",$Default="",$Size="",$Max="", $Option=""){
		if(!$Name){ return false; }
		
		if($this->confirm){
			if($val = $this->ReturnValue($Name)){
				echo $val;
			}else{
				echo "&nbsp;";
			}
			echo "<input type=\"hidden\" name=\"{$Name}\" value=\"" . $this->SP_ENT($val) . "\">\n";
		}else{
			if($Size){ $Size = " size='{$Size}'"; }else{ $Size=""; }
			if($Max){ $Max = " maxlength='{$Max}'"; }else{ $Max=""; }
			echo "<input type=\"text\" name=\"{$Name}\" value=\"" . $this->SP_ENT($Default) . "\"{$Size}{$Max}{$Option}>";
		}
	}
		
	### **** パスワード作成 ****
	function MakePassword($Name="",$Default="",$Size="",$Max="", $Option=""){
		if(!$Name){ return false; }
		
		if($this->confirm){
			if($val = $this->ReturnValue($Name)){
				echo str_repeat("*", strlen($val)) . "\n";
			}else{
				echo "&nbsp;";
			}
			echo "<input type=\"hidden\" name=\"{$Name}\" value=\"" . $this->SP_ENT($val) . "\">\n";
		}else{
			if($Size){ $Size = " size={$Size}"; }else{ $Size=""; }
			if($Max){ $Max = " maxlength={$Max}"; }else{ $Max=""; }
			echo "<input type=\"password\" name=\"{$Name}\" value=\"" . $this->SP_ENT($Default) . "\"{$Size}{$Max}{$Option}>\n";
		}
	}
	
	### **** テキストエリア作成 ****
	function MakeTextarea($Name="",$Default="",$Rows="",$Cols=""){
		if(!$Name){ return false; }
			
		if($this->confirm){
			if($val = $this->ReturnValue($Name)){
				echo nl2br($this->SP_ENT($val));
			}else{
				echo "&nbsp;\n";
			}
			echo "<input type=\"hidden\" name=\"{$Name}\" value=\"" . $this->SP_ENT($val) . "\">\n";
		}else{
			if($Rows){ $Rows = " rows={$Rows}"; }
			if($Cols){ $Cols = " cols={$Cols}"; }
		//	echo "<textarea name=\"{$Name}\"{$Rows}{$Cols}>" . $this->SP_ENT($Default) . "</textarea>\n";
			echo "<textarea name=\"{$Name}\"{$Rows}{$Cols}>" . $Default . "</textarea>\n";
		}
	}

	### **** ラジオボタン作成 ****
	function MakeRadio($Name="",$Default="",$Data="",$Rows="1",$Show="", $Option=""){
		if(!$Name){ return false; }
		
		$width = " width=\"" . round((100/$Rows),3) . "%\""; /* width 設定 */
		
		if($this->confirm){
			if($_POST[$Name]){
				if($Show){
					foreach($Data as $key => $val){ if($_POST[$Name] == $val){ $Show_key = $key; } }
					echo $Show[$Show_key];
				}else{
					echo $_POST[$Name]."\n";
				}
			}else{ echo "&nbsp;\n";
			}
			echo "<input type=\"hidden\" name=\"{$Name}\" value=\"" . $this->SP_ENT($_POST[$Name]) . "\">\n";
		}else{
			
			echo "<table border=0 cellpadding=2 cellspacing=1 width=\"100%\">\n";
			for($i=0;$i<count($Data);$i++){
				if($i%$Rows == 0){ echo "<tr>\n"; }
				
				echo "<td{$width}>\n";
				if(($Default == $Data[$i]) or (!$Default and $i == 0)){
					echo "<input type=\"radio\" name=\"{$Name}\" value=\"{$Data[$i]}\" id=\"{$Name}_{$i}\" checked{$Option}>\n";
				}else{
					echo "<input type=\"radio\" name=\"{$Name}\" value=\"{$Data[$i]}\" id=\"{$Name}_{$i}\"{$Option}>\n";
				}
				if($Show[$i]){
					echo "<label for=\"{$Name}_{$i}\">{$Show[$i]}</label>\n";
				}else{
					echo "<label for=\"{$Name}_{$i}\">{$Data[$i]}</label>\n";
				}
				echo "&nbsp;</td>\n";
				if($i%$Rows == ($Rows - 1)){ echo "</tr>\n"; }
			}
			if($i%$Rows == ($Rows - 1)){ print('</tr>'); }
			echo "</table>\n";
		}
	}
	
	### **** ラジオボタン作成 ****
	function MakeRadio_Hash($Name="",$Default="",$DataHash="",$Rows="1",$Option=""){
		if(!$Name){ return false; }
		
		$width = " width=\"" . round((100/$Rows),3) . "%\""; /* width 設定 */
		
		if($this->confirm){
			if($_POST[$Name]){
				echo $DataHash[$_POST[$Name]];
			}else{
				echo "&nbsp;\n";
			}
			echo "<input type=\"hidden\" name=\"{$Name}\" value=\"" . $this->SP_ENT($_POST[$Name]) . "\">\n";
		}else{
			$i = 0;
			
			echo "<table border=0 cellpadding=2 cellspacing=1 width=\"100%\">\n";
			foreach($DataHash as $key => $val){
				if($i%$Rows == 0){ echo "<tr>\n"; }
				
				echo "<td{$width}>\n";
				if(($Default == $key) or (!$Default and $i == 0)){
					echo "<input type=\"radio\" name=\"{$Name}\" value=\"" . $key . "\" id=\"{$Name}_{$i}\" checked{$Option}>\n";
				}else{
					echo "<input type=\"radio\" name=\"{$Name}\" value=\"" . $key . "\" id=\"{$Name}_{$i}\"{$Option}>\n";
				}
				echo "<label for=\"{$Name}_{$i}\">" . $val . "</label>\n";
				echo "</td>\n";
				if($i%$Rows == ($Rows - 1)){ echo "</tr>\n"; }
				
				$i++;
			}
			if($i%$Rows == ($Rows - 1)){ print('</tr>'); }
			echo "</table>\n";
		}
	}
	
	### **** ラジオボタン作成 ****
	function MakeRadio2($Name="",$Default="",$DataHash="",$Rows="1",$Option=""){
		if(!$Name){ return false; }
		
		$width = " width=\"" . round((100/$Rows),3) . "%\""; /* width 設定 */
		
		if($this->confirm){
			if($val = $this->ReturnValue($Name)){
				echo $DataHash[$val];
			}else{
				echo "&nbsp;";
			}
			echo "<input type=\"hidden\" name=\"{$Name}\" value=\"" . $this->SP_ENT($val) . "\">\n";
		}else{
			$i = 0;
			
			echo "<table border=0 cellpadding=2 cellspacing=1 width=\"100%\">\n";
			foreach($DataHash as $key => $val){
				if($i%$Rows == 0){ echo "<tr>\n"; }
				
				echo "<td{$width}>\n";
				if(($Default == $key) or (!$Default and $i == 0)){
					echo "<input type=\"radio\" name=\"{$Name}\" value=\"" . $key . "\" id=\"{$Name}_{$i}\" checked{$Option}>\n";
				}else{
					echo "<input type=\"radio\" name=\"{$Name}\" value=\"" . $key . "\" id=\"{$Name}_{$i}\"{$Option}>\n";
				}
				echo "<label for=\"{$Name}_{$i}\">" . $val . "</label>\n";
				echo "</td>\n";
				if($i%$Rows == ($Rows - 1)){ echo "</tr>\n"; }
				
				$i++;
			}
			if($i%$Rows == ($Rows - 1)){ print('</tr>'); }
			echo "</table>\n";
		}
	}
	
	function MakeRadio0($Name,$Default="",$Hash=array(),$Opt=""){
		if($this->confirm){
			if($val = $this->ReturnValue($Name)){
				echo $Hash[$val];
			}else{
				echo "&nbsp;";
			}
			print('<input type="hidden" name="'.$Name.'" value="'.$this->SP_ENT($val) . '">');
		}else{
			$cnt = 0;
			foreach($Hash as $k => $v){
				$cnt++;
				if($Default==$k || (!$Default && $cnt==0)){
					print('<input type="radio" name="'.$Name.'" value="'.$k.'" id="'.$Name.$k.'" checked>');
				}else{
					print('<input type="radio" name="'.$Name.'" value="'.$k.'" id="'.$Name.$k.'">');
				}
				print('<label for="'.$Name.$k.'">'.$v.'</label>');
			}
		}
	}
	
	// ノーマル
	function MakeRadio_array($Name="",$Default="",$Data="",$Rows="1",$Option=""){
		if(!$Name){ return false; }
		
		$width = " width=\"" . round((100/$Rows),3) . "%\""; /* width 設定 */
		
		if($this->confirm){
			if($val = $this->ReturnValue($Name)){
				echo $val;
			}else{
				echo "&nbsp;";
			}
			print('<input type="hidden" name="'.$Name.'" value="'.$this->SP_ENT($val) . '">');
		}else{
			
			echo "<table border=0 cellpadding=2 cellspacing=1 width=\"100%\">\n";
			$i = 0;
			foreach($Data as $val){
				if($i%$Rows == 0){ echo "<tr>\n"; }
				
				echo "<td{$width}>\n";
				if(($Default == $val) or (!$Default and $i == 0)){
					echo "<input type=\"radio\" name=\"{$Name}\" value=\"{$val}\" id=\"{$Name}_{$i}\" checked{$Option}>\n";
				}else{
					echo "<input type=\"radio\" name=\"{$Name}\" value=\"{$val}\" id=\"{$Name}_{$i}\"{$Option}>\n";
				}
				echo "<label for=\"{$Name}_{$i}\">{$val}</label>\n";
				echo "&nbsp;</td>\n";
				if($i%$Rows == ($Rows - 1)){ echo "</tr>\n"; }
				$i ++;
			}
			if($i%$Rows == ($Rows - 1)){ print('</tr>'); }
			echo "</table>\n";
		}
	}
	
	
	### **** チェックボックス ****
	function MakeCheckbox($Name="",$Default="",$Data="",$Rows=""){
		if(!$Name){ return false; }
			
		$width = " width=\"" . round((100/$Rows),3) . "%\""; /* width 設定 */
		if(!is_array($default)){ $default = explode(",",$Default); } /* カンマ区切りのデータを配列に */
		if(!is_array($_POST[$Name])){ $_POST[$Name] = explode(",",$_POST[$Name]); } /* カンマ区切りのデータを配列に */
		
		if($this->confirm){
			if($_POST[$Name]){
				echo "<table border=0 cellpadding=0 cellspacing=0 width=\"100%\">\n";
				for($i=0;$i<count($_POST[$Name]);$i++){
					if($i%$Rows == 0){ echo "<tr>\n"; }
					echo "<td{$width}>" . $_POST[$Name][$i] . "</td>\n";
					if($i%$Rows == ($Rows - 1)){ echo "</tr>\n"; }
				}
				if($i%$Rows == ($Rows - 1)){ print('</tr>'); }
				echo "</table>\n";
			}else{
				echo "&nbsp;\n";
			}
			echo "<input type=\"hidden\" name=\"{$Name}\" value=\"" . @join(",",$_POST[$Name]) . "\">\n";
		}else{
			echo "<table border=0 cellpadding=2 cellspacing=1 width=\"100%\">\n";
			for($i=0;$i<count($Data);$i++){
				
				if($i%$Rows == 0){ echo "<tr>\n"; }
				echo "<td{$width}>\n";
				if(@in_array($Data[$i],$Default)){
					echo "<input type=\"checkbox\" name=\"{$Name}[]\" value=\"{$Data[$i]}\" id=\"{$Name}_{$i}\" checked>\n";
				}else{
					echo "<input type=\"checkbox\" name=\"{$Name}[]\" value=\"{$Data[$i]}\" id=\"{$Name}_{$i}\">\n";
				}
				echo "<label for=\"{$Name}_{$i}\">{$Data[$i]}</label>\n";
				echo "</td>\n";
				if($i%$Rows == ($Rows - 1)){ echo "</tr>\n"; }
				
			}
			if($i%$Rows == ($Rows - 1)){ print('</tr>'); }
			echo "</table>\n";
		}
	}

	// ハッシュ対応チェックボックス
	function MakeCheckbox2($Name="",$Default="",$Hash="",$Rows="", $Option=""){
		if(!$Name){ return false; }
			
		$width = " width=\"" . round((100/$Rows),3) . "%\""; /* width 設定 */
		if(!is_array($default)){ $default = explode(",",$Default); } /* カンマ区切りのデータを配列に */
		if(!is_array($_POST[$Name])){ $_POST[$Name] = explode(",",$_POST[$Name]); } /* カンマ区切りのデータを配列に */
		
		if($this->confirm){
			if($_POST[$Name]){
				echo "<table border=0 cellpadding=0 cellspacing=0 width=\"100%\">\n";
				for($i=0;$i<count($_POST[$Name]);$i++){
					if($i%$Rows == 0){ echo "<tr>\n"; }
					echo "<td{$width}>";
					echo $_POST[$Name][$i];
					echo "</td>\n";
					if($i%$Rows == ($Rows - 1)){ echo "</tr>\n"; }
				}
				if($i%$Rows == ($Rows - 1)){ print('</tr>'); }
				echo "</table>\n";
			}else{
				echo "&nbsp;\n";
			}
			echo "<input type=\"hidden\" name=\"{$Name}\" value=\"" . @join(",",$_POST[$Name]) . "\">\n";
		}else{
			
			echo "<table border=0 cellpadding=2 cellspacing=1 width=\"100%\">\n";
			$i = 0;		// counter
			foreach($Hash as $key => $val){
				if($i%$Rows == 0){ echo "<tr>\n"; }
				echo "<td{$width}>\n";
				if(@in_array($key,$Default)){
					echo "<input type=\"checkbox\" name=\"{$Name}[]\" value=\"{$key}\" id=\"{$Name}_{$key}\" checked{$Option}>\n";
				}else{
					echo "<input type=\"checkbox\" name=\"{$Name}[]\" value=\"{$key}\" id=\"{$Name}_{$key}\"{$Option}>\n";
				}
				echo "<label for=\"{$Name}_{$key}\">{$val}</label>\n";
				echo "</td>\n";
				if($i%$Rows == ($Rows - 1)){ echo "</tr>\n"; }
				$i++;	// increment
			}
			if($i%$Rows == ($Rows - 1)){ print('</tr>'); }
			echo "</table>\n";
		}
	}
	
	### **** セレクトフォーム ****
	function MakeSelect($Name="",$Default="",$Data="", $Option=""){
			
		if($this->confirm){
			if($val = $this->ReturnValue($Name)){
				echo $val;
			}else{
				echo "&nbsp;";
			}
			echo "<input type=\"hidden\" name=\"{$Name}\" value=\"" . $this->SP_ENT($val) . "\">\n";
		}else{
			if($Option){
				echo "<Select name=\"{$Name}\"{$Option}>\n";
			}else{
				echo "<Select name=\"{$Name}\">\n";
			}
			// echo "<option value=\"\"></option>\n";
			for($i=0;$i<count($Data);$i++){
				if($Default == $Data[$i]){
					echo "<option value=\"{$Data[$i]}\" selected>{$Data[$i]}</option>\n";
				}else{
					echo "<option value=\"{$Data[$i]}\">{$Data[$i]}</option>\n";
				}
			}
			echo "</Select>\n";
		}
	}
	### **** セレクトフォーム2 (Hash 対応)****
	function MakeSelect2($Name="",$Default="",$Data="", $Option=""){
		
		if($this->confirm){
			if($val = $this->ReturnValue($Name)){
				echo $Data[$val];
			}else{
				echo "&nbsp;";
			}
			echo "<input type=\"hidden\" name=\"{$Name}\" value=\"" . $this->SP_ENT($val) . "\">\n";
		}else{
			if($Option){
				echo "<select name=\"{$Name}\"{$Option}>\n";
			}else{
				echo "<select name=\"{$Name}\">\n";
			}
			foreach($Data as $key => $val){
				if($Default == $key){
					echo "<option value=\"{$key}\" selected>{$val}</option>\n";
				}else{
					echo "<option value=\"{$key}\">{$val}</option>\n";
				}
			}
			echo "</Select>\n";
		}
	}
	
	### **** 日付用セレクトフォーム ****
	function MakeDate($Name="",$Default="",$Start="",$End="",$Show="",$Sort="",$noval="",$option=""){
		
		### **** 引数チェック ****
		# if(!$Name or !$Start or !$End or !is_numeric($Start) or !is_numeric($End)){ return false; }
			
		if($this->confirm){
			if($val = $this->ReturnValue($Name)){
				echo $val . "&nbsp;" . $Show;
			}else{
				echo "&nbsp;";
			}
			echo "<input type=\"hidden\" name=\"{$Name}\" value=\"" . $this->SP_ENT($val) . "\">\n";
		}else{
			echo "<select name=\"{$Name}\"{$option}>\n";
			if(!$noval){
				if($Show=='none'){
					// 何も無し
					$Show='';
				}elseif($Show){
					echo "<option value=\"\">----{$Show}</option>\n";
				}else{
					echo "<option value=\"\"></option>\n";
				}
			}
			
			if(!$Sort){
				for($i=$Start; $i<=$End; $i++){
					if($Default == $i){
						echo "<option value=\"{$i}\" selected>{$i}{$Show}</option>\n";
					}else{
						echo "<option value=\"{$i}\">{$i}{$Show}</option>\n";
					}
				}
			}else{
				for($i=$End; $i>=$Start; $i--){
					if($Default == $i){
						echo "<option value=\"{$i}\" selected>{$i}{$Show}</option>\n";
					}else{
						echo "<option value=\"{$i}\">{$i}{$Show}</option>\n";
					}
				}
			}
			echo "</Select>\n";
		}
	}

	//	日付セット
	function MakeDateset($HeadName="",$Default="",$YearRange="",$DispOpt=""){
		if(!$Default){	$Default=date("Y-m-d");	}
		if(!$YearRange){
			for($i=2003;$i<=date("Y")+1;$i++){
				$YearRange[] = $i;
			}
		}
		if($DispOpt=="1"){
			$Yopt = "年";
			$Mopt = "月";
			$Dopt = "日";
		}
		list($DefY,$DefM,$DefD) = split("-",$Default);

		if($this->confirm){
			
			echo $_POST[$HeadName . "Y"] . "年";
			echo $_POST[$HeadName . "M"] . "月";
			echo $_POST[$HeadName . "D"] . "日";
			print('
				<input type="hidden" name="'.$HeadName.'" value="'.$_POST[$HeadName.'Y'].'-'.$_POST[$HeadName.'M'].'-'.$_POST[$HeadName.'D'].'">
			');

		}else{
			//	年
			print('<select name="'.$HeadName.'Y">');
			foreach($YearRange as $val){
				if($DefY==$val){
					print('<option value="'.$val.'" selected>'.$val.$Yopt.'</option>');
				}else{
					print('<option value="'.$val.'">'.$val.$Yopt.'</option>');
				}
			}
			print('</select>/');

			//	月
			print('<select name="'.$HeadName.'M">');
			for($i=1;$i<=12;$i++){
				if(abs($DefM)==$i){
					print('<option value="'.$i.'" selected>'.$i.$Mopt.'</option>');
				}else{
					print('<option value="'.$i.'">'.$i.$Mopt.'</option>');
				}
			}
			print('</select>/');

			//	日
			print('<select name="'.$HeadName.'D">');
			for($i=1;$i<=31;$i++){
				if(abs($DefD)==$i){
					print('<option value="'.$i.'" selected>'.$i.$Dopt.'</option>');
				}else{
					print('<option value="'.$i.'">'.$i.$Dopt.'</option>');
				}
			}
			print('</select>');
		}
	}

	//	MakeDatesetのデータを Y-m-d にして返す。
	function RetDateset($HeadName){
		$Yf = $HeadName.'Y';
		$Mf = $HeadName.'M';
		$Df = $HeadName.'D';
		return($_POST[$Yf].'-'.$_POST[$Mf].'-'.$_POST[$Df]);
	}
	

	// 隠しフォーム
	function MakeHidden($Name="",$Value=""){
		$val = $this->ReturnValue($Name);
		print('<input type="hidden" name="'.$Name.'" value="'.$this->SP_ENT($Value).'">');
	}

}	
?>
